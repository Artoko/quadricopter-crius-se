/*
 * SrvMotor.h
 *
 * Created: 31/05/2012 16:04:46
 *  Author: berryer
 */ 


#ifndef SRVMOTOR_H_
#define SRVMOTOR_H_

#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"

#include "Drv/DrvEvent.h"


//init des moteurs
Boolean SrvMotorInit( void ) ;

//dispatcher d'evenements
void SrvMotorDispatcher (Event_t in_event) ;

//Update des moteurs
void SrvMotorUpdate(S_pid pid_error) ;

//applique une vittesse aux moteurs
Boolean SrvMotorApplyAbsoluteSpeed(Int16U speed) ;

//applique une vittesse aux moteurs
Boolean SrvMotorApplyRelativeSpeed(Int16S speed);

//recupere une vittesse des moteurs
Int16U SrvMotorGetSpeed( void ) ;


#endif /* SRVMOTOR_H_ */