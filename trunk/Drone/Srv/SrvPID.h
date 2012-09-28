/*
 * SrvPID.h
 *
 * Created: 24/09/2012 14:48:50
 *  Author: berryer
 */ 


#ifndef SRVPID_H_
#define SRVPID_H_



#include "Tools/tools_typedefs.h"

//init des valeurs du PID
void SrvPIDInit (Int8U index,float P, float I, float D);
//calculs les angles target
float SrvPIDCompute(Int8U index,float targetPosition, float currentPosition );



#endif /* SRVPID_H_ */