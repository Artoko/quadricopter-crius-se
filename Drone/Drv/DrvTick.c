/*
 * DrvTick.c
 *
 * Created: 03/07/2012 11:56:56
 *  Author: berryer
 */ 
#include "Conf/conf_hard.h"

#include "DrvTick.h"
#include "DrvEvent.h"

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
volatile Int32U drv_timer_start_delay = 0;
volatile Int32U drv_timer_tick_counter_10us = 0;

volatile Int16U tick_counter_20ms = 0U;
volatile Int16U tick_counter_50ms = 0U;
volatile Int8U tick_counter_100ms = 0U;
volatile Int8U tick_counter_1s = 0U;
volatile Int8U tick_counter_5s = 0U;
volatile Int8U tick_counter_10s = 0U;

#define TIMER0_OFFSET_COMPA		0x78U
///////////////////////////////////////////PUBLIC FUNCTIONS////////////////////////////////////////
//on init le driver
void DrvTickInit(void)
{	
	drv_timer_tick_counter_10us= 0;
	//on init le timer 1 tick = 10us
	TCCR0A	= 0;             
    TCCR0B	|= _BV(CS00);     
    TCNT0	= 0;            
	OCR0A   = TIMER0_OFFSET_COMPA;   
    TIFR0	|= _BV(OCF0A);     
    TIMSK0	|= _BV(OCIE0A) ;
	
}

void DrvTickReset(void)
{
	cli();
		drv_timer_start_delay = 0;
		drv_timer_tick_counter_10us = 0;
		tick_counter_20ms = 0U;
		tick_counter_50ms = 0U;
		tick_counter_100ms = 0U;
		tick_counter_1s = 0U;
		tick_counter_5s = 0U;
		tick_counter_10s = 0U;
	sei();
}	

//get the tick counter
Int32U DrvTimerGetTime(void)
{
	Int32U loc_var;
	cli();
	loc_var = drv_timer_tick_counter_10us;
	sei();
	return loc_var;
}

void DrvTimerDelayMs( Int32U delay_ms )
{
	drv_timer_start_delay = DrvTimerGetTime() ;
	while (DrvTimerGetTime() < (Int32U)(drv_timer_start_delay + (delay_ms * 100)) );
}

void DrvTimerDelay10Us( Int16U delay_us )
{
	drv_timer_start_delay = DrvTimerGetTime() ;
	while (DrvTimerGetTime() < (Int32U)(drv_timer_start_delay + delay_us) );
}


///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
//ISR timer system 10us
ISR(TIMER0_COMPA_vect)
{
	OCR0A = TCNT0 + TIMER0_OFFSET_COMPA ;
	drv_timer_tick_counter_10us += 1U;
	
	if(tick_counter_20ms++ == 1999)
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
				//DrvEventAddEvent(CONF_EVENT_TIMER_1S);
				if(tick_counter_5s++ == 4)
				{
					tick_counter_5s = 0;
					//DrvEventAddEvent(CONF_EVENT_TIMER_5S);
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