/*
 * SrvPID.h
 *
 * Created: 24/09/2012 14:48:50
 *  Author: berryer
 */ 


#ifndef SRVPID_H_
#define SRVPID_H_



#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"

#include "Drv/DrvEvent.h"

typedef struct
{
	float P, I, D;
	float lastPosition;
	float integratedError;
}S_IMU_PID;

//init des valeurs du PID
void SrvPIDInit(void );

Int16S SrvPIDCompute(Int8U index, float targetPosition, float currentPosition );


#endif /* SRVPID_H_ */