/*
 * SrvPID.c
 *
 * Created: 24/09/2012 14:48:34
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Srv/SrvPID.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"



////////////////////////////////////////PRIVATE STRUCTURES/////////////////////////////////////////


static S_IMU_PID pid[ 4U ] ;



void SrvPIDInit(void )
{
	float P;
	float I;
	float D;
	//roulis
	DrvEepromReadPID(0U,&P,&I,&D);
	pid[0U].P = P;
	pid[0U].I = I;
	pid[0U].D = D;
	pid[0U].lastPosition = 0;
	pid[0U].integratedError = 0;
	//tangage
	DrvEepromReadPID(1U,&P,&I,&D);
	pid[1U].P = P;
	pid[1U].I = I;
	pid[1U].D = D;
	pid[1U].lastPosition = 0;
	pid[1U].integratedError = 0;
	//lacet
	DrvEepromReadPID(2U,&P,&I,&D);
	pid[2U].P = P;
	pid[2U].I = I;
	pid[2U].D = D;
	pid[2U].lastPosition = 0;
	pid[2U].integratedError = 0;
	//altitude
	DrvEepromReadPID(3U,&P,&I,&D);
	pid[3U].P = P;
	pid[3U].I = I;
	pid[3U].D = D;
	pid[3U].lastPosition = 0;
	pid[3U].integratedError = 0;
	
	
}

Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition )
{
	float error = targetPosition - currentPosition;
	
	pid[index].integratedError += error;

	// Limit the integrated error by the windupGuard
	if (pid[index].integratedError < -1000) 
	{
		pid[index].integratedError = -1000;
	} 
	else if (pid[index].integratedError > 1000) 
	{
		pid[index].integratedError = 1000;
	}
	
	int dTerm = (pid[index].D * (currentPosition - pid[index].lastPosition)) / 10;
	pid[index].lastPosition = currentPosition;
	return (Int16S)(((pid[index].P * error) / 10) + ((pid[index].I * pid[index].integratedError) / 10) + dTerm);
}

