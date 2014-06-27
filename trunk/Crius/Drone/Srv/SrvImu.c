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

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//variables de timming
Int32U lastread_ekf = 0U;

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
	float interval_ekf = 0.0F;
	
	// ********************* Calcul du temps de cycle *************************
	now = DrvTimerGetTimeUs();
	interval_ekf = (float)(now - lastread_ekf) / 1000000.0F;
	lastread_ekf = now;
	
	// ********************* Mise � jour roulis tangage lacet *****************
	imu_reel.angles.roulis   = (Int16S)SrvKalmanFilterX( imu_reel.acc_angles.x, imu_reel.gyr_angles.y, interval_ekf ) ;
	imu_reel.angles.tangage  = (Int16S)SrvKalmanFilterY( imu_reel.acc_angles.y, imu_reel.gyr_angles.x, interval_ekf ) ;
	imu_reel.angles.lacet	 = (Int16S)SrvKalmanFilterZ( imu_reel.angles.nord, imu_reel.gyr_angles.z, interval_ekf );
	
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

Int32S  __attribute__ ((noinline)) mul(Int16S a, Int16S b)
{
	Int32S r;
	MultiS16X16to32(r, a, b);
	//r = (int32_t)a*b; without asm requirement
	return r;
}
