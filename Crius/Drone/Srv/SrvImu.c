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


#if ( DAISY_7 == 1 )
#include "Cmps/CmpLIS331DLH.h"
#include "Cmps/CmpL3G4200D.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#elif ( CRIUS == 1 )
#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#endif



////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_MAX  5U

////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
static void SrvImuComputeSensors( void );

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//angle donne par les capteurs accelerometre et gyroscope
static float accXangle;
static float accYangle;
static float accZangle;
static float gyroXAngle;
static float gyroYAngle;
static float gyroZAngle;


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
	pid_erreur_roulis = 0;
	pid_erreur_tangage = 0;
	pid_erreur_lacet = 0;
	pid_erreur_altitude = 0;
	
	
	//init des composants
	#if ( DAISY_7 == 1 )
	
		CmpLIS331DLHInit();
		CmpL3G4200DInit();
		CmpHMC5883Init();
		CmpBMP085Init();
		
	#elif ( CRIUS == 1 )
	
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
	//on calcul toutes les 20 millisecondes
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_20MS ) == TRUE)
	{		
		// ********************* Mesure des capteurs ******************************
		SrvImuComputeSensors();
		
		// ********************* PID **********************************************
		pid_erreur_roulis	= SrvPIDCompute( 0U , (float)imu_desire.roulis					, (float)imu_reel.roulis);
		pid_erreur_tangage	= SrvPIDCompute( 1U , (float)imu_desire.tangage					, (float)imu_reel.tangage);
		pid_erreur_lacet	= SrvPIDCompute( 2U , (float)(imu_reel.lacet + imu_desire.lacet), (float)imu_reel.lacet);
		if(imu_reel.maintient_altitude == TRUE)
		{
			pid_erreur_altitude	= SrvPIDCompute( 3U , imu_desire.altitude, imu_reel.altitude);
		}	
		
		// *********************Mise à jour des Moteurs ***************************
		SrvMotorUpdate(pid_erreur_roulis , pid_erreur_tangage,pid_erreur_lacet, pid_erreur_altitude )	;
	}	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		/*imu_reel.temperature = (Int16S)CmpBMP085GetTemperature();
		imu_reel.pressure = CmpBMP085GetPressure();
		//atm = pressure / 101325.0;
		imu_reel.altitude = (Int16U)CmpBMP085GetAltitude(imu_reel.pressure);
		imu_reel.weather = CmpBMP085GetWeather(imu_reel.pressure);*/
	}
}


/************************************************************************/
/*Calibration des capteurs                                              */
/************************************************************************/
void SrvImuSensorsCalibration( void )
{
	S_Acc_Angle acceleration;

	Boolean calibrate = FALSE;
	do
	{
		#if ( DAISY_7 == 1 )
			//calib accelerometer
			if( CmpLIS331DLHIsCalibrate() == FALSE)
			{
				CmpLIS331DLHGetAcceleration(&acceleration);
			}
			else
			{
				DrvEepromConfigure();
				calibrate = TRUE;
			}		
		#elif ( CRIUS == 1 )
			//calib accelerometer
			if( CmpBMA180IsCalibrate() == FALSE)
			{
				CmpBMA180GetAcceleration(&acceleration);
			}
			else
			{
				DrvEepromConfigure();
				calibrate = TRUE;
			}			
		#endif
	} while (!calibrate);
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
		Int16U alt = 0U;
		DrvEepromReadAltitude(&alt);
		imu_reel.maintient_altitude = TRUE;
		imu_desire.altitude = alt + altitude;
	}
	else
	{
		imu_reel.maintient_altitude = FALSE;
	}
}
////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
/************************************************************************/
/*Recuperation des données des capteurs et mise en forme  des données   */
/************************************************************************/
static void SrvImuComputeSensors( void )
{
	//variables de timming
	static Int32U previous_time;
	static Int32U interval;
	
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
	
	
	// ********************* Calcul du temps de cycle *************************
	interval = DrvTimerGetTime() - previous_time;
	
	// ********************* Lecture des capteurs *****************************
	#if ( DAISY_7 == 1 )
	
		acc_read_ok = CmpLIS331DLHGetAcceleration(&acceleration);
		gyr_read_ok = CmpL3G4200DGetRotation(&rotation);
		mag_read_ok = CmpHMC5883GetHeading(&magnet);
	
	#elif ( CRIUS == 1 )
	
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
		accXangle		= (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle		= (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
	
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
		accZangle = acceleration.z;		
	}
			
	//GYR
	//sensitivity	=>	14.375
	if(gyr_read_ok != FALSE)
	{
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.x * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )	
		gyroRate	=	rotation.x / 14.375 ;
		#endif
		gyroYAngle	+=	(float)((float)((gyroRate * interval) / 1000000.0));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.y * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.y / 14.375 ;
		#endif
		gyroXAngle	+=	(float)((float)((gyroRate * interval) / 1000000.0));
		
		#if ( GYR_L3G4200D == 1 )
		gyroRate	=	rotation.z * 0.00875 ;
		#elif ( GYR_ITG3205 == 1 )
		gyroRate	=	rotation.z / 14.375 ;
		#endif
		gyroZAngle	+=	(float)((float)((gyroRate * interval) / 1000000.0));
	}		
	//MAG
	if(mag_read_ok != FALSE)
	{
		//on doit etre en dessous des 40 deg
		if(!(accXangle > 40 || accXangle < -40 || accYangle > 40 || accYangle < -40))
		{
			//compensation avec l'accelerometre
			float cosRoll = cos(ToRad(accYangle));
			float sinRoll = sin(ToRad(accYangle));  
			float cosPitch = cos(ToRad(accXangle));
			float sinPitch = sin(ToRad(accXangle));
			
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
			imu_reel.nord  = ToDeg(heading);
		}
	}
	
	// ********************* Fusion des capteurs ******************************
	imu_reel.roulis   = SrvKalmanFilterX( accXangle, gyroXAngle, interval ) * 10;
	imu_reel.tangage  = SrvKalmanFilterY( accYangle, gyroYAngle, interval ) * 10;
	imu_reel.lacet	  = gyroZAngle;
	if(imu_reel.lacet < 0.0)
	{
		imu_reel.lacet += 360.0;
	}
	else if(imu_reel.lacet > 360.0)
	{
		imu_reel.lacet -= 360.0;
	}
	
	// ********************* Calcul du temps de cycle *************************
	previous_time = DrvTimerGetTime();
}

