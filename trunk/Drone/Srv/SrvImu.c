/*
 * Srvc
 *
 * Created: 06/07/2012 17:29:19
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvImu.h"
#include "SrvMotor.h"
#include "SrvKalman.h"
#include "Srv/SrvPID.h"

#include "Drv/DrvTick.h"

#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"


////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_MAX  130

////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
static void SrvImuComputeSensors(Int32U interval);

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//angle donne par les capteurs accelerometre et gyroscope
static float accXangle;
static float accYangle;
static float accZangle;
static float gyroXAngle;
static float gyroYAngle;
static float gyroZAngle;

//direction par rapport au nord
static Int16U direction;

//erreur retournee par le calcul du PID
static Int16S pid_erreur_roulis;
static Int16S pid_erreur_tangage;
static Int16S pid_erreur_lacet;
static Int16S pid_erreur_altitude;

//variables de timming
static Int32U temp_actuel;
static Int32U temp_dernier_cycle;
static Int32U temp_max_cycle;

//maintient de l'alitude
static Boolean maintient_altitude;
static Int16U altitude_depart;
	
static Int16U alti_tab[NB_SAMPLE_MAX];
static Int32U altitude_moyenne;

//initialisation des composants
void SrvImuInit( void )
{
	//init des variables priv�es
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
	temp_actuel = 0;
	temp_dernier_cycle = 0;
	temp_max_cycle = 0;
	direction = 0;
	maintient_altitude = FALSE;
	altitude_depart = 0;
	
	//init des composants	
	CmpHMC5883Init();
	CmpBMA180Init();
	CmpITG3205Init();
	CmpBMP085Init();
	
}

//dispatcher d'evenements
void SrvImuDispatcher (Event_t in_event)
{
	//on calcul toutes les 20 millisecondes
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_20MS ) == TRUE)
	{
		// ********************* Calcul du temps de cycle *************************
		temp_dernier_cycle = DrvTimerGetTime() - temp_actuel;
		temp_actuel = DrvTimerGetTime();
		
		// ********************* Mesure des capteurs ******************************
		SrvImuComputeSensors( temp_dernier_cycle );
		
		// ********************* Fusion des capteurs ******************************
		angle_reel.roulis  = SrvKalmanFilterX( accXangle, gyroXAngle, temp_dernier_cycle );
		angle_reel.tangage = SrvKalmanFilterY( accYangle, gyroYAngle, temp_dernier_cycle );
		angle_reel.lacet   = SrvKalmanFilterZ( direction, gyroZAngle, temp_dernier_cycle );
		angle_reel.altitude= altitude_moyenne;
		
		
		// ********************* PID **********************************************
		pid_erreur_roulis	= SrvPIDCompute( 0, angle_desire.roulis						, angle_reel.roulis);
		pid_erreur_tangage	= SrvPIDCompute( 1, angle_desire.tangage					, angle_reel.tangage);
		pid_erreur_lacet	= SrvPIDCompute( 2, angle_reel.lacet + angle_desire.tangage	, angle_reel.lacet);
		if(maintient_altitude == TRUE)
		{
			pid_erreur_altitude	= SrvPIDCompute( 3, angle_desire.altitude, angle_reel.altitude);
			SrvMotorApplyRelativeSpeed(pid_erreur_altitude);
		}
		
		// ********************* Moteurs ******************************************
		SrvMotorUpdate(pid_erreur_roulis, pid_erreur_tangage, pid_erreur_lacet);
		speed = SrvMotorGetSpeed();
		
		//heartbeat
		LED_TOGGLE();
	}	
	
	//BARO
	for(Int8U loop = 0; loop < NB_SAMPLE_MAX - 1 ; loop++)
	{
		alti_tab[loop] = alti_tab[loop + 1];
		altitude_moyenne += alti_tab[loop];
	}
	alti_tab[NB_SAMPLE_MAX - 1 ] = CmpBMP085StateMachine();
	altitude_moyenne += alti_tab[NB_SAMPLE_MAX - 1 ];
	altitude_moyenne /= NB_SAMPLE_MAX;
}

//Enregistre l altitude de depart
void SrvImuSensorsSetAltitudeDepart( void )
{
	altitude_depart = angle_reel.altitude;
}

//Enregistre l altitude de maintient
void SrvImuSensorsSetAltitudeMaintient( Int8U altitude )
{
	if(altitude != 0U)
	{
		maintient_altitude = TRUE;
		angle_desire.altitude = altitude_depart + altitude;
	}
	else
	{
		maintient_altitude = FALSE;
	}
}

//Calibration des capteurs
void SrvImuSensorsCalibration( void )
{
	S_Gyr_Angle rotation;
	S_Acc_Angle acceleration;
	S_Mag_Angle magnet;

	Boolean calibrate = FALSE;
	Int8U sens = 0;
	do
	{
		//ACC
		CmpBMA180GetAcceleration(&acceleration);
		//GYR
		CmpITG3205GetRotation(&rotation);
		//MAG
		CmpHMC5883GetHeading(&magnet);
		
		sens |= CmpITG3205IsCalibrate();
		sens |= CmpBMA180IsCalibrate() << 1;
		sens |= CmpHMC5883IsCalibrate() << 2;
		
		if(	sens == 7 )
		{
			calibrate = TRUE;
			DrvEepromConfigure();
		}
		else
		{
			DrvTimerDelay10Us(STD_LOOP_TIME);
		}
	} while (!calibrate);
}

//on met a jours les angles
void SrvImuComputeSensors(Int32U interval)
{
	float gyroRate = 0;	
	
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
	
	//ACC
	if(CmpBMA180GetAcceleration(&acceleration) != FALSE)
	{
		//#define ACC_ORIENTATION(X, Y, Z)  {accADC[ROLL]  = -X; accADC[PITCH]  = -Y; accADC[YAW]  =  Z;}
		acceleration.x *= -1;
		acceleration.y *= -1;
		acceleration.z *= 1;
		accXangle		= (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle		= (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
	
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
		accZangle = acceleration.z;		
	}
			
	//GYR
	//sensitivity	=>	14.375
	if(CmpITG3205GetRotation(&rotation) != FALSE)
	{	
		//#define GYRO_ORIENTATION(X, Y, Z) {gyroADC[ROLL] =  Y; gyroADC[PITCH] = -X; gyroADC[YAW] = -Z;}
		rotation.x *= -1;
		rotation.y *= 1;
		rotation.z *= -1;
			
		gyroRate				=	(float)(rotation.x / 14.375) ;
		gyroYAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		
		gyroRate				=	rotation.y / 14.375 ;
		gyroXAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		
		gyroRate				=	rotation.z / 14.375 ;
		gyroZAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		if(gyroZAngle < 0)
		{
			gyroZAngle += 360.0;
		}
		if(gyroZAngle > 360)
		{
			gyroZAngle -= 360.0;
		}

	}		
	//MAG
	if(CmpHMC5883GetHeading(&magnet) != FALSE)
	{
		//#define MAG_ORIENTATION(X, Y, Z)  {magADC[ROLL]  =  X; magADC[PITCH]  =  Y; magADC[YAW]  = -Z;}
		magnet.x *= 1;
		magnet.y *= 1;
		magnet.z *= -1;	

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
			float heading = atan2(Yh, Xh) + (LOCAL_MAGNETIC_DECLINAISON / 1000);
			if(heading < 0)
			{
				heading += 2*M_PI;
			}
			if(heading > 2*M_PI)
			{
				heading -= 2*M_PI;
			}
			direction = ToDeg(heading);
		}	
	}
}

