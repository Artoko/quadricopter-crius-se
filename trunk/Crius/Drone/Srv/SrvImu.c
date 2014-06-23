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
#include "SrvSensors.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"


////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_MAX  5U

////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
static void SrvImuFusionSensorsRollPitchYaw( S_angles *angles, float interval, S_Acc_Angles acc_angles, S_Gyr_Angles gyr_angles, Int16S nord );
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


//variables de timming
Int32U lastread = 0U;

/************************************************************************/
/*Initialisation des composants                                         */
/************************************************************************/
Boolean SrvImuInit( void )
{
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
	LED_ON();
	// ********************* Mesure des capteurs ******************************	
	SrvSensorsReadGyroscopeSensor( &imu_reel.gyr_angles, interval, &imu_reel.sensors.gyr );
	SrvSensorsReadAccelerometerSensor( &imu_reel.acc_angles, &imu_reel.sensors.acc );
	SrvSensorsReadMagnetometerSensor( &imu_reel.angles, &imu_reel.sensors.mag );
		
	// ********************* Mise à jour roulis tangage lacet *****************
	SrvImuFusionSensorsRollPitchYaw( &imu_reel.angles, interval, imu_reel.acc_angles, imu_reel.gyr_angles, imu_reel.angles.nord );
	
	// ********************* PID **********************************************
	imu_reel.pid_error.roulis	= SrvPIDCompute( 0U , imu_desire.angles.roulis	, imu_reel.angles.roulis	, interval);
	imu_reel.pid_error.tangage	= SrvPIDCompute( 1U , imu_desire.angles.tangage	, imu_reel.angles.tangage	, interval);
	imu_reel.pid_error.lacet	= SrvPIDCompute( 2U , (imu_reel.angles.lacet + imu_desire.angles.lacet)	, imu_reel.angles.lacet	, interval);
	LED_OFF();
	
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_10MS ) == TRUE)
	{	
		// *********************Mise à jour des Moteurs ***************************
		SrvMotorUpdate( imu_reel.pid_error );
	}	
}


/************************************************************************/
/*Enregistre la position de depart                                      */
/************************************************************************/
void SrvImuSensorsSetAltitudeDepart( void )
{
	DrvEepromWriteAltitude(imu_reel.sensors.bar.altitude);
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


Int32S  __attribute__ ((noinline)) mul(Int16S a, Int16S b)
{
	Int32S r;
	MultiS16X16to32(r, a, b);
	//r = (int32_t)a*b; without asm requirement
	return r;
}
