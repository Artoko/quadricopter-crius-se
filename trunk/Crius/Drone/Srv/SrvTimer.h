/*
 * SrvTimer.h
 *
 * Created: 06/07/2012 16:35:15
 *  Author: berryer
 */ 

#ifndef SRVTIMER_H_
#define SRVTIMER_H_

#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"



//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////
typedef void (*ptrfct_Isr_Callback_Timer)( void);

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////
//mode fonctionnement du timer
typedef enum
{
  E_TIMER_MODE_ONE_SHOT,
  E_TIMER_MODE_PERIODIC,
  E_TIMER_MODE_NONE,
}ETimerMode;

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Srv Timer 
void SrvTimerInit( void ) ;

//fct qui parametre le timer
void SrvTimerAddTimer( Int8U index_timer, Int16U delay_ms, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct ) ;

//fct qui met en pause le timer
void SrvTimerPauseTimer( Int8U index_timer ) ;

//fct qui remet a zero les parametres du timer
void SrvTimerStopTimer( Int8U index_timer ) ;

//fct qui reseter le timer
void SrvTimerResetTimer( Int8U index_timer ) ;

//fct qui fixe un delay au timer
void SrvTimerDelayTimer( Int8U index_timer , Int16U delay) ;

//on reset tt les timers
void SrvTimerTickReset(void) ;
#endif /* SRVTIMER_H_ */