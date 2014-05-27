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
static void SrvImuReadAndComputeSensors( void );

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

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
	//init des variables privées
	accXangle = 0;
	accYangle = 0;
	accZangle = 0;
	gyroXAngle = 0;
	gyroYAngle = 0;
	gyroZAngle = 0;	
	heading_deg = 0;
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
	//on calcul toutes les 10 millisecondes
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_20MS ) == TRUE)
	{
		// ********************* Mesure des capteurs ******************************
		SrvImuReadAndComputeSensors();
		
		// ********************* PID **********************************************
		imu_reel.pid_error.roulis	= SrvPIDCompute( 0U , imu_desire.angles.roulis	, imu_reel.angles.roulis);
		imu_reel.pid_error.tangage	= SrvPIDCompute( 1U , imu_desire.angles.tangage	, imu_reel.angles.tangage);
		imu_reel.pid_error.lacet	= SrvPIDCompute( 2U , (imu_reel.angles.lacet + imu_desire.angles.lacet)	, imu_reel.angles.lacet);
		imu_reel.pid_error.altitude	= SrvPIDCompute( 3U , imu_desire.altitude, imu_reel.altitude);
		
		// *********************Mise à jour des Moteurs ***************************
		SrvMotorUpdate( imu_reel.pid_error );
	}
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		// *********************Mise à jour du  barometre *************************
		CmpBMP085LaunchReading();
		imu_reel.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.weather = CmpBMP085GetWeather(imu_reel.pressure, imu_reel.altitude);
		imu_reel.pressure = CmpBMP085GetPressure();
		//atm = pressure / 101325.0;
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
/*Recuperation des données des capteurs et mise en forme  des données   */
/************************************************************************/
//variables de timming
static float interval_gyro = 0U;
static Int32U lastread_gyro = 0U;
static Int32U now_gyro = 0U;
static float interval_ekf = 0U;
static Int32U lastread_ekf = 0U;
static Int32U now_ekf = 0U;

static void SrvImuReadAndComputeSensors( void )
{
	float gyroRate = 0;	
	
	Boolean acc_read_ok = FALSE;
	Boolean gyr_read_ok = FALSE;
	Boolean mag_read_ok = FALSE;
	
	S_Gyr_Angle rotation;
	S_Acc_Angle acceleration;
	S_Mag_Angle magnet;
	
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;
	magnet.x = 0; 
	magnet.y = 0; 
	magnet.z = 0; 
	
	
	/*now = DrvTimerGetTimeUs();
	interval = ((Int32U)(now - lastread)); 
	lastread = now;*/
	
	// ********************* Lecture des capteurs *****************************
	#if defined( DAISY_7 )
	
		acc_read_ok = CmpLIS331DLHGetAcceleration(&acceleration);
		gyr_read_ok = CmpL3G4200DGetRotation(&rotation);
		mag_read_ok = CmpHMC5883GetHeading(&magnet);
	
	#elif defined( CRIUS )
	
		acc_read_ok = CmpBMA180GetAcceleration(&acceleration);
		acceleration.x *= -1;
		acceleration.y *= -1;
		acceleration.z *= 1;
		
		gyr_read_ok = CmpITG3205GetRotation(&rotation);
		rotation.x *= -1;
		rotation.y *= 1;
		rotation.z *= -1;
		
		mag_read_ok = CmpHMC5883GetHeading(&magnet);
		magnet.x *= -1;
		magnet.y *= 1;
		magnet.z *= -1;
	
	#endif
	
	//ACC
	if(acc_read_ok != FALSE)
	{
		accXangle = (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle = (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
	
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
		accZangle = acceleration.z;		
	}
			
	//GYR
	//sensitivity	=>	14.375
	if(gyr_read_ok != FALSE)
	{
		// ********************* Calcul du temps de cycle *************************
		now_gyro = DrvTimerGetTimeUs();
		interval_gyro = (float)(now_gyro - lastread_gyro) / 1000000.0F;
		lastread_gyro = now_gyro;		
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.x * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )	
		gyroRate	=	rotation.x * 0.06956 ;
		#endif
		gyroYAngle	+=	(float)((float)((gyroRate * interval_gyro)));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.y * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.y * 0.06956 ;
		#endif
		gyroXAngle	+=	(float)((float)((gyroRate * interval_gyro) ));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.z * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.z * 0.06956 ;
		#endif
		gyroZAngle	+=	(float)((float)((gyroRate * interval_gyro)));
	}		
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
	
	// ********************* Fusion des capteurs ******************************
	
	// ********************* Calcul du temps de cycle *************************
	now_ekf = DrvTimerGetTimeUs();
	interval_ekf = (float)(now_ekf - lastread_ekf) / 1000000.0F;
	lastread_ekf = now_ekf;
	
	
	imu_reel.angles.roulis   = SrvKalmanFilterX( accXangle, gyroXAngle, interval_ekf ) * 10;
	imu_reel.angles.tangage  = SrvKalmanFilterY( accYangle, gyroYAngle, interval_ekf ) * 10;
	imu_reel.angles.lacet	 = SrvKalmanFilterZ( heading_deg, gyroZAngle, interval_ekf );
	if(imu_reel.angles.lacet < 0.0)
	{
		imu_reel.angles.lacet += 360.0;
	}
	else if(imu_reel.angles.lacet > 360.0)
	{
		imu_reel.angles.lacet -= 360.0;
	}
}


Int32S  __attribute__ ((noinline)) mul(Int16S a, Int16S b)
{
	Int32S r;
	MultiS16X16to32(r, a, b);
	//r = (int32_t)a*b; without asm requirement
	return r;
}
