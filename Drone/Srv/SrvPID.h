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


//init des valeurs du PID
void SrvPIDInit (Int8U index,float P, float I, float D);

//dispatcher d'evenements
void SrvPIDDispatcher (Event_t in_event);


#endif /* SRVPID_H_ */