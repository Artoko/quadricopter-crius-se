/*
 * drv_event.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include <util/atomic.h>
#include "Conf/conf_hard.h"

#include "DrvEvent.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


static Event_t event_flags = 0;
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Event 
void DrvEventInit( void )
{
	event_flags = 0;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//
inline void DrvEventKillEvent(Event_t in_event) 
{
	ATOMIC(
		event_flags = ~(in_event | ~event_flags);
	)
}

//
inline Event_t DrvEventGetEvent(void)
{
  return event_flags;
}

//
inline Boolean DrvEventTestEvent(Event_t in_event,Int8U conf_event ) 
{
	if (( in_event & ( 1 << conf_event)) > 0 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//
inline Boolean DrvEventAddEvent(Event_t event)
{
	event_flags |= (1<<event) ;
	return TRUE;
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////