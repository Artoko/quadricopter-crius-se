/*
 * SrvPID.c
 *
 * Created: 24/09/2012 14:48:34
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Srv/SrvPID.h"
#include "SrvMotor.h"

#include "Drv/DrvTick.h"



//calculs les angles target
static Int16S SrvPIDCompute(Int8U index,float targetPosition, float currentPosition );

////////////////////////////////////////PRIVATE STRUCTURES/////////////////////////////////////////
typedef struct
{
	float P, I, D;
	float lastPosition;
	float integratedError;
}S_IMU_PID;

static S_IMU_PID pid[ 4U ] ;

//erreur retournee par le calcul du PID
static Int16S pid_erreur_roulis;
static Int16S pid_erreur_tangage;
static Int16S pid_erreur_lacet;
static Int16S pid_erreur_altitude;

void SrvPIDInit (Int8U index,float P, float I, float D)
{
	pid[index].P = P;
	pid[index].I = I;
	pid[index].D = D;
	pid[index].lastPosition = 0;
	pid[index].integratedError = 0;
	pid_erreur_roulis = 0;
	pid_erreur_tangage = 0;
	pid_erreur_lacet = 0;
	pid_erreur_altitude = 0;
	imu_reel.maintient_altitude = FALSE;
}


//dispatcher d'evenements
void SrvPIDDispatcher (Event_t in_event)
{
	//on calcul toutes les 20 millisecondes
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_20MS ) == TRUE)
	{
		// ********************* PID **********************************************
		pid_erreur_roulis	= SrvPIDCompute( 0, imu_desire.roulis					, imu_reel.roulis);
		pid_erreur_tangage	= SrvPIDCompute( 1, imu_desire.tangage					, imu_reel.tangage);
		pid_erreur_lacet	= SrvPIDCompute( 2, imu_reel.lacet + imu_desire.lacet	, imu_reel.lacet);
		if(imu_reel.maintient_altitude == TRUE)
		{
			pid_erreur_altitude	= SrvPIDCompute( 3, imu_desire.altitude, imu_reel.altitude);
			SrvMotorApplyRelativeSpeed(pid_erreur_altitude);
		}
		// ********************* Moteurs ******************************************
		SrvMotorUpdate(pid_erreur_roulis, pid_erreur_tangage, pid_erreur_lacet);
		speed = SrvMotorGetSpeed();
	}		
}	



static Int16S SrvPIDCompute(Int8U index, float targetPosition, float currentPosition )
{
	float error = targetPosition - currentPosition;
	
	pid[index].integratedError += error;

	// Limit the integrated error by the windupGuard
	if (pid[index].integratedError < -1000) {
		pid[index].integratedError = -1000;
	} else if (pid[index].integratedError > 1000) {
		pid[index].integratedError = 1000;
	}
	
	int dTerm = (pid[index].D * (currentPosition - pid[index].lastPosition)) / 10;
	pid[index].lastPosition = currentPosition;
	return (Int16S)(((pid[index].P * error) / 10) + ((pid[index].I * pid[index].integratedError) / 10) + dTerm);
}
