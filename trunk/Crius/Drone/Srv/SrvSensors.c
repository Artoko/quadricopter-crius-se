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

//variables de timming
Int32U lastread_gyro = 0U;
Int32U lastread_baro = 0U;

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

//dispatcher d'evenements
void SrvSensorsDispatcher (Event_t in_event)
{
	Int32U now = 0U;
	float interval_baro = 0.0F;
	float interval_gyro = 0.0F;
	
	// ********************* Calcul du temps de cycle *************************
	now = DrvTimerGetTimeUs();
	interval_gyro = (float)(now - lastread_gyro) / 1000000.0F;
	lastread_gyro = now;
	
	// ********************* Mesure des capteurs ******************************			
	//read gyro
	SrvSensorsReadGyroscopeSensor( &imu_reel.gyr_angles, interval_gyro, &imu_reel.sensors.gyr );
	//read acc
	SrvSensorsReadAccelerometerSensor( &imu_reel.acc_angles, &imu_reel.sensors.acc );
	//read mag
	SrvSensorsReadMagnetometerSensor( &imu_reel.angles, &imu_reel.sensors.mag );

	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_50MS ) == TRUE)
	{
		now = DrvTimerGetTimeUs();
		interval_baro = (float)(now - lastread_baro) / 1000000.0F;
		lastread_baro = now;
		// *********************Mise à jour du barometre **************************
		CmpBMP085StateMachine();
		imu_reel.sensors.bar.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.sensors.bar.pressure = CmpBMP085GetPressure();
		imu_reel.sensors.bar.altitude = (Int16S)CmpBMP085GetAltitude(imu_reel.sensors.bar.pressure);
		
		if( ( imu_reel.sensors.bar.weather == WEATHER_NONE ) && ( imu_reel.sensors.bar.pressure != 0) )
		{
			imu_reel.sensors.bar.weather = CmpBMP085GetWeather(imu_reel.sensors.bar.pressure, imu_reel.sensors.bar.altitude);
		}
		imu_reel.pid_error.altitude	= SrvPIDCompute( 3U , imu_desire.altitude, imu_reel.sensors.bar.altitude	, interval_baro);
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
		//calib accelerometer
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
	} while ((!calibrate_acc) && (!calibrate_gyr));
	
	DrvEepromConfigure();
}

/************************************************************************/
/*Lecture accelerometer                                                 */
/************************************************************************/
void SrvSensorsReadAccelerometerSensor( S_Acc_Angles *acc_angles, S_Acc_Sensor *sensors )
{
	Boolean acc_read_ok = FALSE;
	
	#if ( ACC_BMA180 == 1 )
	acc_read_ok = CmpBMA180GetAcceleration( sensors );
	sensors->x *= -1;
	sensors->y *= -1;
	sensors->z *= 1;
	#endif

	//ACC
	if(acc_read_ok != FALSE)
	{
		
		//Roll & Pitch 
		acc_angles->x  = (float)atan2((double)(sensors->x) , (double)sqrt((double)(pow((double)sensors->y,2)+pow((double)sensors->z,2))));
        acc_angles->y = (float)atan2((double)(sensors->y) , (double)sqrt((double)(pow((double)sensors->x,2)+pow((double)sensors->z,2))));
		
		acc_angles->x = ToDeg(acc_angles->x);
		acc_angles->y = ToDeg(acc_angles->y);
		acc_angles->z = sensors->z;
	}
}

/************************************************************************/
/*Lecture Gyroscope                                                     */
/************************************************************************/
void SrvSensorsReadGyroscopeSensor( S_Gyr_Angles *gyr_angles, float interval, S_Gyr_Sensor *sensors )
{
	Boolean gyr_read_ok = FALSE;
	
	float gyroRate = 0;
		
	#if ( GYR_ITG3205 == 1 )
	gyr_read_ok = CmpITG3205GetRotation( sensors );
	sensors->x *= -1;
	sensors->y *= 1;
	sensors->z *= -1;
	#endif
	
	
	
	//GYR
	//sensitivity	=>	14.375
	if(gyr_read_ok != FALSE)
	{
		#if ( GYR_L3G4200D == 1 )
		gyroRate = sensors->x * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate = sensors->x * 0.06956 ;// 14.375 ;
		#endif
		gyr_angles->x += (float)((float)((gyroRate * interval)));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate = sensors->y * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate = sensors->y * 0.06956 ;// 14.375 ;
		#endif
		gyr_angles->y += (float)((float)((gyroRate * interval) ));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate = sensors->z * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate = sensors->z * 0.06956 ;// 14.375 ;
		#endif
		gyr_angles->z += (float)((float)((gyroRate * interval)));
	}
}

/************************************************************************/
/*Lecture Magnetometer                                                  */
/************************************************************************/
void SrvSensorsReadMagnetometerSensor( S_angles *angles, S_Mag_Sensor *sensors )
{
	Boolean mag_read_ok = FALSE;
		
	#if ( GYR_ITG3205 == 1 )
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
			
			
			float heading = atan2(Yh, Xh);
			//float heading = atan2(sensors->y, sensors->x);
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
