/*
 * Srvc
 *
 * Created: 06/07/2012 17:29:19
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvImu.h"
#include "SrvPID.h"
#include "SrvKalman.h"
#include "SrvMotor.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

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



////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_MAX  5U

////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
static void SrvImuReadMagnetometerSensor( S_angles *angles );
static void SrvImuReadGyroscopeSensor( S_Gyr_Angles *gyr_angles, float interval );
static void SrvImuReadAccelerometerSensor( S_Acc_Angles	*acc_angles );
static void SrvImuFusionSensorsRollPitchYaw( S_angles *angles, float interval, S_Acc_Angles acc_angles, S_Gyr_Angles gyr_angles, Int16S nord );
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


//variables de timming
Int32U lastread = 0U;

/************************************************************************/
/*Initialisation des composants                                         */
/************************************************************************/
Boolean SrvImuInit( void )
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

/************************************************************************/
/*Dispatcher d'evenements                                               */
/************************************************************************/
void SrvImuDispatcher (Event_t in_event)
{
	Int32U now = 0U;
	float interval = 0.0F;
	// ********************* Calcul du temps de cycle *************************
	now = DrvTimerGetTimeUs();
	interval = (float)(now - lastread) / 1000000.0F;
	lastread = now;
	
	// ********************* Mesure des capteurs ******************************	
	SrvImuReadGyroscopeSensor( &imu_reel.gyr_angles, interval );
	SrvImuReadAccelerometerSensor( &imu_reel.acc_angles );
	SrvImuReadMagnetometerSensor( &imu_reel.angles );
		
	// ********************* Mise � jour roulis tangage lacet *****************
	SrvImuFusionSensorsRollPitchYaw( &imu_reel.angles, interval, imu_reel.acc_angles, imu_reel.gyr_angles, imu_reel.angles.nord );
	
	// ********************* PID **********************************************
	imu_reel.pid_error.roulis	= SrvPIDCompute( 0U , imu_desire.angles.roulis	, imu_reel.angles.roulis	, interval);
	imu_reel.pid_error.tangage	= SrvPIDCompute( 1U , imu_desire.angles.tangage	, imu_reel.angles.tangage	, interval);
	imu_reel.pid_error.lacet	= SrvPIDCompute( 2U , (imu_reel.angles.lacet + imu_desire.angles.lacet)	, imu_reel.angles.lacet	, interval);
	imu_reel.pid_error.altitude	= SrvPIDCompute( 3U , imu_desire.altitude, imu_reel.altitude	, interval);
	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_10MS ) == TRUE)
	{	
		// *********************Mise � jour des Moteurs ***************************
		SrvMotorUpdate( imu_reel.pid_error );
	}
	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		// *********************Mise � jour du barometre **************************
		CmpBMP085StateMachine();
		imu_reel.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.pressure = CmpBMP085GetPressure();
		imu_reel.altitude = (Int16S)CmpBMP085GetAltitude(imu_reel.pressure);
		
		if( ( imu_reel.weather == WEATHER_NONE ) && ( imu_reel.pressure != 0) )
		{
			imu_reel.weather = CmpBMP085GetWeather(imu_reel.pressure, imu_reel.altitude);
		}
	}	
	
	
}


/************************************************************************/
/*Calibration des capteurs                                              */
/************************************************************************/
void SrvImuSensorsCalibration( void )
{
	S_Acc_Angle acceleration;
	S_Gyr_Angle rotation;

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
/*Enregistre la position de depart                                      */
/************************************************************************/
void SrvImuSensorsSetAltitudeDepart( void )
{
	DrvEepromWriteAltitude(imu_reel.altitude);
}

/************************************************************************/
/*Enregistre l altitude de maintient                                    */
/************************************************************************/
void SrvImuSensorsSetAltitudeMaintient( Int8U altitude )
{
	if(altitude != 0U)
	{
		Int16S alt = 0U;
		DrvEepromReadAltitude(&alt);
		imu_desire.maintient_altitude = TRUE;
		imu_desire.altitude = alt + altitude;
	}
	else
	{
		imu_desire.maintient_altitude = FALSE;
	}
}


////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
/************************************************************************/
/*Fusion des capteurs pour avoir Roll et Pitch                          */
/************************************************************************/
static void SrvImuFusionSensorsRollPitchYaw( S_angles *angles, float interval, S_Acc_Angles acc_angles, S_Gyr_Angles gyr_angles, Int16S nord )
{
	angles->roulis   = (Int16S)SrvKalmanFilterX( acc_angles.x, gyr_angles.y, interval ) ;
	angles->tangage  = (Int16S)SrvKalmanFilterY( acc_angles.y, gyr_angles.x, interval ) ;
	angles->lacet	 = (Int16S)SrvKalmanFilterZ( nord, gyr_angles.z, interval );
	
	if(angles->lacet < 0.0)
	{
		angles->lacet += 360.0;
	}
	else if(angles->lacet > 360.0)
	{
		angles->lacet -= 360.0;
	}
}


/************************************************************************/
/*Lecture accelerometer                                                 */
/************************************************************************/
static void SrvImuReadAccelerometerSensor( S_Acc_Angles	*acc_angles )
{
	Boolean acc_read_ok = FALSE;
	
	float accXangle;
	float accYangle;
	float accZangle;
	
	S_Acc_Angle acceleration;
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;

	#if ( ACC_BMA180 == 1 )
		acc_read_ok = CmpBMA180GetAcceleration( &acceleration );
		acceleration.x *= -1;
		acceleration.y *= -1;
		acceleration.z *= 1;
	#endif
	
	//ACC
	if(acc_read_ok != FALSE)
	{
		accXangle = (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle = (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
		
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
		accZangle = acceleration.z;
		
		acc_angles->x = accXangle;
		acc_angles->y = accYangle;
		acc_angles->z = accZangle;
	}
}

/************************************************************************/
/*Lecture Gyroscope                                                     */
/************************************************************************/
static void SrvImuReadGyroscopeSensor( S_Gyr_Angles *gyr_angles, float interval )
{
	Boolean gyr_read_ok = FALSE;
	
	float gyroRate = 0;	
	
	S_Gyr_Angle rotation;
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	
	#if ( GYR_ITG3205 == 1 )
		gyr_read_ok = CmpITG3205GetRotation(&rotation);
		rotation.x *= -1;
		rotation.y *= 1;
		rotation.z *= -1;
	#endif
	
	
	//GYR
	//sensitivity	=>	14.375
	if(gyr_read_ok != FALSE)
	{
		#if ( GYR_L3G4200D == 1 )
			gyroRate = rotation.x * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
			gyroRate = rotation.x / 14.375 ;
		#endif
		gyr_angles->x += (float)((float)((gyroRate * interval)));
		
		#if ( GYR_L3G4200D == 1 )
			gyroRate = rotation.y * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
			gyroRate = rotation.y / 14.375 ;
		#endif
		gyr_angles->y += (float)((float)((gyroRate * interval) ));
		
		#if ( GYR_L3G4200D == 1 )
			gyroRate = rotation.z * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
			gyroRate = rotation.z / 14.375 ;
		#endif
		gyr_angles->z += (float)((float)((gyroRate * interval)));
	}
}

/************************************************************************/
/*Lecture Magnetometer                                                  */
/************************************************************************/
static void SrvImuReadMagnetometerSensor( S_angles *angles )
{
	Boolean mag_read_ok = FALSE;
	
	S_Mag_Angle magnet;
	magnet.x = 0;
	magnet.y = 0;
	magnet.z = 0;
	
	#if ( GYR_ITG3205 == 1 )
		mag_read_ok = CmpHMC5883GetHeading(&magnet);
		magnet.x *= -1;
		magnet.y *= 1;
		magnet.z *= -1;
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
			
			float Xh = magnet.x * cosPitch + magnet.z * sinPitch;
			float Yh = magnet.x * sinRoll * sinPitch + magnet.y * cosRoll - magnet.z * sinRoll * cosPitch;
			float heading = atan2(Yh, Xh);
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


Int32S  __attribute__ ((noinline)) mul(Int16S a, Int16S b)
{
	Int32S r;
	MultiS16X16to32(r, a, b);
	//r = (int32_t)a*b; without asm requirement
	return r;
}
