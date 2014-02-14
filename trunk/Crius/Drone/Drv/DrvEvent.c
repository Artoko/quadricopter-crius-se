/*
 * drv_event.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "Conf/conf_hard.h"

#include "DrvEvent.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
volatile Event_t event_flags = 0U;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
/************************************************************************/
/*Init du Drv Event                                                     */
/************************************************************************/
Boolean DrvEventInit( void )
{
	event_flags = 0U;
	return TRUE;
}

/************************************************************************/
/*On recupere l'evenement en cours                                      */
/************************************************************************/
inline Event_t DrvEventGetEvent(Event_t in_event)
{
	ATOMIC
	(
		//on kill l'ancien event
		event_flags = ~(in_event | ~event_flags);
	)
	return event_flags;
}

/************************************************************************/
/*On test l'evenement en cours                                          */
/************************************************************************/
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

/************************************************************************/
/*On ajoute un evenement aux evenements en cours                        */
/************************************************************************/
inline Boolean DrvEventAddEvent(Event_t event)
{
	event_flags |= event ;
	return TRUE;
}




