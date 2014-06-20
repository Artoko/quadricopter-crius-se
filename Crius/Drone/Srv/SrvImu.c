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
static float SrvImuReadMagnetometerSensor( void );
static void SrvImuReadGyroscopeSensor( void );
static void SrvImuReadAccelerometerSensor( void );
static void SrvImuFusionSensorsRollPitchYaw( void );
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


//variables de timming
float interval = 0.0F;
Int32U lastread = 0U;
Int32U now = 0U;


//angle donne par les capteurs accelerometre et gyroscope
static float accXangle;
static float accYangle;
static float accZangle;
static float gyroXAngle;
static float gyroYAngle;
static float gyroZAngle;
static float heading_deg;


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
	// ********************* Calcul du temps de cycle *************************
	now = DrvTimerGetTimeUs();
	interval = (float)(now - lastread) / 1000000.0F;
	lastread = now;
	
	// ********************* Mesure des capteurs ******************************	
	SrvImuReadGyroscopeSensor();
	SrvImuReadAccelerometerSensor();
	SrvImuReadMagnetometerSensor();
		
	// ********************* Mise à jour roulis tangage lacet *****************
	SrvImuFusionSensorsRollPitchYaw();
	
	// ********************* PID **********************************************
	imu_reel.pid_error.roulis	= SrvPIDCompute( 0U , imu_desire.angles.roulis	, imu_reel.angles.roulis	, interval);
	imu_reel.pid_error.tangage	= SrvPIDCompute( 1U , imu_desire.angles.tangage	, imu_reel.angles.tangage	, interval);
	imu_reel.pid_error.lacet	= SrvPIDCompute( 2U , (imu_reel.angles.lacet + imu_desire.angles.lacet)	, imu_reel.angles.lacet	, interval);
	imu_reel.pid_error.altitude	= SrvPIDCompute( 3U , imu_desire.altitude, imu_reel.altitude	, interval);
	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_10MS ) == TRUE)
	{	
		// *********************Mise à jour des Moteurs ***************************
		SrvMotorUpdate( imu_reel.pid_error );
	}
	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		// *********************Mise à jour du barometre **************************
		CmpBMP085LaunchReading();
		imu_reel.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.weather = CmpBMP085GetWeather(imu_reel.pressure, imu_reel.altitude);
		imu_reel.pressure = CmpBMP085GetPressure();
		imu_reel.altitude = (Int16S)CmpBMP085GetAltitude(imu_reel.pressure);
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
				calibrate_acc = TRUE;
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
static void SrvImuFusionSensorsRollPitchYaw( void )
{
	imu_reel.angles.roulis   = (Int16S)SrvKalmanFilterX( accXangle, gyroYAngle, interval ) ;
	imu_reel.angles.tangage  = (Int16S)SrvKalmanFilterY( accYangle, gyroXAngle, interval ) ;
	imu_reel.angles.lacet	 = (Int16S)SrvKalmanFilterZ( heading_deg, gyroZAngle, interval );
	
	if(imu_reel.angles.lacet < 0.0)
	{
		imu_reel.angles.lacet += 360.0;
	}
	else if(imu_reel.angles.lacet > 360.0)
	{
		imu_reel.angles.lacet -= 360.0;
	}
}


/************************************************************************/
/*Lecture accelerometer                                                 */
/************************************************************************/
static void SrvImuReadAccelerometerSensor( void )
{
	Boolean acc_read_ok = FALSE;
	
	S_Acc_Angle acceleration;
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;
	
	acc_read_ok = CmpBMA180GetAcceleration(&acceleration);
	acceleration.x *= -1;
	acceleration.y *= -1;
	acceleration.z *= 1;
	
	//ACC
	if(acc_read_ok != FALSE)
	{
		accXangle = (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle = (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
		
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
		accZangle = acceleration.z;
	}
}

/************************************************************************/
/*Lecture Gyroscope                                                     */
/************************************************************************/
static void SrvImuReadGyroscopeSensor( void )
{
	Boolean gyr_read_ok = FALSE;
	float gyroRate = 0;	
	S_Gyr_Angle rotation;
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	
	gyr_read_ok = CmpITG3205GetRotation(&rotation);
	rotation.x *= -1;
	rotation.y *= 1;
	rotation.z *= -1;
	
	//GYR
	//sensitivity	=>	14.375
	if(gyr_read_ok != FALSE)
	{
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.x * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.x / 14.375 ;
		#endif
		gyroXAngle	+=	(float)((float)((gyroRate * interval)));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.y * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.y / 14.375 ;
		#endif
		gyroYAngle	+=	(float)((float)((gyroRate * interval) ));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.z * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.z / 14.375 ;
		#endif
		gyroZAngle	+=	(float)((float)((gyroRate * interval)));
	}
}

/************************************************************************/
/*Lecture Magnetometer                                                  */
/************************************************************************/
static float SrvImuReadMagnetometerSensor( void )
{
	Boolean mag_read_ok = FALSE;
	
	S_Mag_Angle magnet;
	magnet.x = 0;
	magnet.y = 0;
	magnet.z = 0;
	
	mag_read_ok = CmpHMC5883GetHeading(&magnet);
	magnet.x *= -1;
	magnet.y *= 1;
	magnet.z *= -1;
	
	//MAG
	if(mag_read_ok != FALSE)
	{
		//on doit etre en dessous des 40 deg
		if(!(accXangle > 40 || accXangle < -40 || accYangle > 40 || accYangle < -40))
		{
			//compensation avec l'accelerometre
			float cosRoll  = cos( ToRad( accYangle ) );
			float sinRoll  = sin( ToRad( accYangle ) );
			float cosPitch = cos( ToRad( accXangle ) );
			float sinPitch = sin( ToRad( accXangle ) );
			
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
			heading_deg = ToDeg(heading);
			imu_reel.angles.nord = heading_deg;
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
