/*
 * DrvTick.h
 *
 * Created: 03/07/2012 11:57:04
 *  Author: berryer
 */ 


#ifndef DRVTICK_H_
#define DRVTICK_H_

#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"

//on init le driver
void DrvTickInit(void);

//on reset les compteurs
void DrvTickReset(void);

//get the tick counter
Int32U DrvTickGetTimeUs(void);

//wait for delay
void DrvTickDelayUs( Int16U delay_us );
void DrvTickDelayMs( Int16U delay_ms );

//get time interval
Int32U DrvTickGetInterval( Int32U *last_interval );

#endif /* DRVTICK_H_ */