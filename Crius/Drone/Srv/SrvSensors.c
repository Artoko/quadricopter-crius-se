/*
* SrvHeartbeat.c
*
* Created: 06/07/2012 16:34:50
*  Author: berryer
*/
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvSensors.h"
#include "SrvPID.h"

#include "Drv/DrvEeprom.h"
#include "Drv/DrvTick.h"

#if defined( DAISY_7 )
#include "Cmps/CmpLIS331DLH.h"
#include "Cmps/CmpL3G4200D.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#elif defined( CRIUS )
#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#endif


////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////


////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////


////////////////////////////////////////PRIVATE VARIABLES///////////////////////////////////////


//Init des valeurs d'allumage moteurs
Boolean SrvSensorsInit( void )
{
	
	//init des composants
	#if defined( DAISY_7 )
	
	CmpLIS331DLHInit();
	CmpL3G4200DInit();
	CmpHMC5883Init();
	CmpBMP085Init();
	
	#elif defined( CRIUS )
	
	CmpBMA180Init();
	CmpITG3205Init();
	CmpHMC5883Init();
	CmpBMP085Init();
	
	#endif
	
	return TRUE;
}

float interval_gyro = 0.0F;
	

//dispatcher d'evenements
void SrvSensorsDispatcher (Event_t in_event)
{
	// ********************* Mesure des capteurs ******************************			
	//read gyro
	SrvSensorsReadGyroscopeSensor( &imu_reel.gyr_angles, &imu_reel.sensors.gyr );
	//read acc
	SrvSensorsReadAccelerometerSensor( &imu_reel.acc_angles, &imu_reel.sensors.acc );
	//read mag
	//SrvSensorsReadMagnetometerSensor( &imu_reel.angles, &imu_reel.sensors.mag );
	//read baro
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_50MS ) == TRUE)
	{
		// *********************Mise à jour du barometre **************************
		CmpBMP085StateMachine();
		imu_reel.sensors.bar.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.sensors.bar.pressure = CmpBMP085GetPressure();
		imu_reel.sensors.bar.altitude = (Int16S)CmpBMP085GetAltitude(imu_reel.sensors.bar.pressure);
		
		if( ( imu_reel.sensors.bar.weather == WEATHER_NONE ) && ( imu_reel.sensors.bar.pressure != 0) )
		{
			imu_reel.sensors.bar.weather = CmpBMP085GetWeather(imu_reel.sensors.bar.pressure, imu_reel.sensors.bar.altitude);
		}
	}
}


/************************************************************************/
/*Calibration des capteurs                                              */
/************************************************************************/
void SrvSensorsSensorsCalibration( void )
{
	S_Acc_Sensor acceleration;
	S_Gyr_Sensor rotation;

	Boolean calibrate_acc = FALSE;
	Boolean calibrate_gyr = FALSE;
	Boolean calibrate_mag = FALSE;
	do
	{
		#if defined( DAISY_7 )
		//calib accelerometer
		if( CmpLIS331DLHIsCalibrate() == FALSE)
		{
			CmpLIS331DLHGetAcceleration(&acceleration);
		}
		else
		{
			calibrate_acc = TRUE;
		}
		//calib gyroscope
		if( CmpL3G4200DIsCalibrate() == FALSE)
		{
			CmpL3G4200DGetRotation(&rotation);
		}
		else
		{
			calibrate_gyr = TRUE;
		}
		
		#elif defined( CRIUS )
		//calib accelerometer
		if( CmpBMA180IsCalibrate() == FALSE)
		{
			CmpBMA180GetAcceleration(&acceleration);
		}
		else
		{
			calibrate_acc = TRUE;
		}
		//calib gyroscope
		if( CmpITG3205IsCalibrate() == FALSE)
		{
			CmpITG3205GetRotation(&rotation);
		}
		else
		{
			calibrate_gyr = TRUE;
		}
		#endif
		
		//calib magnetometer
		calibrate_mag = CmpHMC5883Calibrate();
		
	} while ((!calibrate_acc) || (!calibrate_gyr) || (!calibrate_mag));
	
	
	
	DrvEepromConfigure();
}

/************************************************************************/
/*Lecture accelerometer                                                 */
/************************************************************************/
void SrvSensorsReadAccelerometerSensor( S_Acc_Angles *acc_angles, S_Acc_Sensor *sensors )
{
	Boolean acc_read_ok = FALSE;
	
	#ifdef ACC_BMA180
	acc_read_ok = CmpBMA180GetAcceleration( sensors );
	sensors->x *= -1;
	sensors->y *= -1;
	sensors->z *= 1;
	#endif

	#ifdef ACC_LIS331DLH 
	acc_read_ok = CmpLIS331DLHGetAcceleration( sensors );
	sensors->x *= -1;
	sensors->y *= -1;
	sensors->z *= 1;
	#endif
	
	//ACC
	if(acc_read_ok != FALSE)
	{
		
		//Roll & Pitch 
		acc_angles->roulis = (float)atan2((double)sensors->y, (double)sensors->z) ;
		acc_angles->tangage  = (float)atan2((double)(sensors->x) , (double)sqrt((double)(pow((double)sensors->y,2)+pow((double)sensors->z,2))));
        
		acc_angles->roulis = ToDeg(acc_angles->roulis);
		acc_angles->tangage = ToDeg(acc_angles->tangage);
	}
}

/************************************************************************/
/*Lecture Gyroscope                                                     */
/************************************************************************/
void SrvSensorsReadGyroscopeSensor( S_Gyr_Angles *gyr_angles, S_Gyr_Sensor *sensors )
{
	#define NB_SAMPLES 10.0F
	Boolean gyr_read_ok = FALSE;
	float gyroRate_x = 0;
	float gyroRate_y = 0;
	float gyroRate_z = 0;
	
	//variables de timming
	Int32U lastread_gyro = 0U;
	Int32U now = 0U;
	
	for( int sample_gyro = 0U ; sample_gyro < NB_SAMPLES ; sample_gyro++ )
	{		
		// ********************* Calcul du temps de cycle *************************
		now = DrvTickGetTimeUs();
		interval_gyro = (float)(now - lastread_gyro) / 1000000.0F;
		lastread_gyro = now;
	

		#ifdef GYR_ITG3205
		gyr_read_ok = CmpITG3205GetRotation( sensors );
		sensors->x *= -1;
		sensors->y *= 1;
		sensors->z *= -1;
		#endif

		#ifdef GYR_L3G4200D
		gyr_read_ok = CmpL3G4200DGetRotation( sensors );
		sensors->x *= -1;
		sensors->y *= 1;
		sensors->z *= -1;
		#endif
		

		//GYR
		if(gyr_read_ok != FALSE)
		{
			//scaled
			//*************
			#ifdef GYR_L3G4200D 
			gyroRate_x = sensors->x * 0.07 ;
			gyroRate_y = sensors->y * 0.07 ;
			gyroRate_z = sensors->z * 0.07 ;
			#endif
			#ifdef GYR_ITG3205
			gyroRate_x = sensors->x * 0.06956 ;
			gyroRate_y = sensors->y * 0.06956 ;
			gyroRate_z = sensors->z * 0.06956 ;
			#endif
			
			gyr_angles->roulis	+= (float)( gyroRate_x * interval_gyro);
			gyr_angles->tangage += (float)( gyroRate_y * interval_gyro);
			gyr_angles->lacet	+= (float)( gyroRate_z * interval_gyro);
		}
	}
	gyr_angles->roulis		/= NB_SAMPLES;
	gyr_angles->tangage		/= NB_SAMPLES;
	gyr_angles->lacet		/= NB_SAMPLES;
	
}

/************************************************************************/
/*Lecture Magnetometer                                                  */
/************************************************************************/
void SrvSensorsReadMagnetometerSensor( S_angles *angles, S_Mag_Sensor *sensors )
{
	Boolean mag_read_ok = FALSE;
		
	#ifdef MAG_HMC5883
	mag_read_ok = CmpHMC5883GetHeading( sensors );	

	sensors->x *= -1;
	sensors->y *= 1;
	sensors->z *= -1;
	#endif
	
	//MAG
	if(mag_read_ok != FALSE)
	{
		//on doit etre en dessous des 40 deg
		if(!(angles->roulis > 40 || angles->roulis < -40 || angles->tangage > 40 || angles->tangage < -40))
		{
			//compensation avec l'accelerometre
			float cosRoll  = cos( ToRad( angles->tangage ) );
			float sinRoll  = sin( ToRad( angles->tangage ) );
			float cosPitch = cos( ToRad( angles->roulis ) );
			float sinPitch = sin( ToRad( angles->roulis ) );
			
			float Xh = sensors->x * cosPitch + sensors->z * sinPitch;
			float Yh = sensors->x * sinRoll * sinPitch + sensors->y * cosRoll - sensors->z * sinRoll * cosPitch;

			float heading = -1*atan2(Yh, Xh);
			heading += LOCAL_MAGNETIC_DECLINAISON;
			if(heading < 0)
			{
				heading += 2 * M_PI;
			}
			if(heading > 2 * M_PI)
			{
				heading -= 2 * M_PI;
			}
			angles->nord = (Int16S)ToDeg(heading);
		}
	}
}



/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
