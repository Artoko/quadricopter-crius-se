/*
 * drv_event.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include <util/atomic.h>
#include "Conf/conf_hard.h"

#include "DrvEvent.h"

////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define TIMER2_OFFSET_COMPA		0xF9

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

volatile Int16U tick_counter_20ms = 0U;
volatile Int16U tick_counter_50ms = 0U;
volatile Int8U tick_counter_100ms = 0U;
volatile Int8U tick_counter_1s = 0U;
volatile Int8U tick_counter_5s = 0U;
volatile Int8U tick_counter_10s = 0U;
volatile Int32U drv_event_tick_counter_1ms = 0;

static Event_t event_flags = 0U;
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Event 
void DrvEventInit( void )
{
	event_flags = 0U;
	TCCR2A	= 0;             
    TCCR2B	|= _BV(CS22) ;     
    TCNT2	= 0;       
	OCR2A   = TIMER2_OFFSET_COMPA;     
    TIFR2	|= _BV(OCF2A);     
    TIMSK2	|= _BV(OCIE2A) ;
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

inline void DrvEventTickReset(void)
{
	cli();
	drv_event_tick_counter_1ms = 0;
	tick_counter_20ms = 0U;
	tick_counter_50ms = 0U;
	tick_counter_100ms = 0U;
	tick_counter_1s = 0U;
	tick_counter_5s = 0U;
	tick_counter_10s = 0U;
	TCNT2 = 0U;
	sei();
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR timer event 1ms
ISR(TIMER2_COMPA_vect)
{
	OCR2A = TCNT2 + TIMER2_OFFSET_COMPA ;
	
	if(tick_counter_20ms++ == 19)
	{
		tick_counter_20ms = 0;
		DrvEventAddEvent(CONF_EVENT_TIMER_20MS);
		if(tick_counter_100ms++ == 2)
		{
			tick_counter_100ms = 0;
			DrvEventAddEvent(CONF_EVENT_TIMER_100MS);
			if(tick_counter_1s++ == 9)
			{
				tick_counter_1s = 0;
				DrvEventAddEvent(CONF_EVENT_TIMER_1S);
				if(tick_counter_5s++ == 4)
				{
					tick_counter_5s = 0;
					DrvEventAddEvent(CONF_EVENT_TIMER_5S);
					if(tick_counter_10s++ == 1)
					{
						tick_counter_10s = 0;
						DrvEventAddEvent(CONF_EVENT_TIMER_10S);
					}
				}
			}
		}
	}			
}