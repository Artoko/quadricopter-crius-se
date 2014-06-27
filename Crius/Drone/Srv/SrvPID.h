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
void SrvPIDInit( void ) ;

//Dispatcher d'evenements 
void SrvPIDDispatcher (Event_t in_event) ;

//set des valeurs du PID
void SrvPIDSetValues( Int8U index, float p, float i, float d ) ;

//Reset des valeurs du pid
void SrvPIDResetValues( void ) ;

//calcul des valeurs PID
Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition, float delta_time ) ;


#endif /* SRVPID_H_ */