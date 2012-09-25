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
void SrvPIDInit (Int8U index,Int8S P, Int8S I, Int8S D);
//calculs les angles target
Int16S SrvPIDCompute(Int8U index,Int16S targetPosition, Int16S currentPosition );



#endif /* SRVPID_H_ */