/*
 * SrvPID.c
 *
 * Created: 24/09/2012 14:48:34
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Drv/DrvTick.h"

////////////////////////////////////////PRIVATE STRUCTURES/////////////////////////////////////////
typedef struct
{
	float P, I, D;
	float lastPosition;
	float integratedError;
}S_IMU_PID;

static S_IMU_PID pid[ 4U ] ;

void SrvPIDInit (Int8U index,float P, float I, float D)
{
	pid[index].P = P;
	pid[index].I = I;
	pid[index].D = D;
	pid[index].lastPosition = 0;
	pid[index].integratedError = 0;
}

Int16S SrvPIDCompute(Int8U index, float targetPosition, float currentPosition )
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
