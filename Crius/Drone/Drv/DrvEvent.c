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
inline Event_t DrvEventGetEvent( void )
{
	Event_t temp_added_flags = 0U;
	ATOMIC
	(
		//on kill
		temp_added_flags = event_flags ;
		event_flags = 0U;
	);
	return temp_added_flags;
}

/************************************************************************/
/*On test l'evenement en cours                                          */
/************************************************************************/
inline Boolean DrvEventTestEvent( Event_t in_event, Int8U conf_event ) 
{
	if (( in_event & conf_event) > 0 )
	{
		return TRUE;
	}
	return FALSE;
}

/************************************************************************/
/*On ajoute un evenement aux evenements en cours                        */
/************************************************************************/
inline Boolean DrvEventAddEvent(Event_t in_event)
{
	ATOMIC
	(
		event_flags |= in_event ;
	);
	return TRUE;
}




