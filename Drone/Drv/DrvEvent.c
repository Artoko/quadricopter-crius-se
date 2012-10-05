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


static Event_t event_flags = 0U;
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Event 
void DrvEventInit( void )
{
	event_flags = 0U;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

//
inline Event_t DrvEventGetEvent(Event_t in_event)
{
	ATOMIC
	(
		//on kill l'ancien event
		event_flags = ~(in_event | ~event_flags);
	)
	return event_flags;
}

//
inline Boolean DrvEventTestEvent(Event_t in_event,Int8U conf_event ) 
{
	if (( in_event & conf_event) > 0 )
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
	event_flags |= event ;
	return TRUE;
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////