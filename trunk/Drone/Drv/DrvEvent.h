/*
 * drv_event.h
 *
 * Created: 14/11/2011 15:18:48
 *  Author: berryer
 */ 


#ifndef DRV_EVENT_H_
#define DRV_EVENT_H_


#include "Tools/tools_typedefs.h"


#define NB_MAX_EVENT 5

////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////



/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


typedef Int16U Event_t;

// Init du Drv Event 
void DrvEventInit( void ) ;
Event_t DrvEventGetEvent(Event_t in_event) ;
Boolean DrvEventTestEvent(Event_t in_event,Int8U conf_event ) ;
Boolean DrvEventEventExist(Event_t event) ;
Boolean DrvEventAddEvent(Event_t event) ;

#endif /* DRV_EVENT_H_ */