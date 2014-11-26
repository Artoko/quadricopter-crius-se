/*
 * DrvTick.c
 *
 * Created: 03/07/2012 11:56:56
 *  Author: berryer
 */ 
#include "Conf/conf_hard.h"

#include "DrvTick.h"
#include "DrvEvent.h"

////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define TIMER0_OVF				128
#define TIMER0_TICK				0.5
#define TIMER0_CST_PRECISION	10

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
volatile Int32U drv_timer_tick_counter = 0U;
volatile Int32U drv_timer_start_delay = 0;


///////////////////////////////////////////PUBLIC FUNCTIONS////////////////////////////////////////
//on init le driver
void DrvTickInit(void)
{	
	drv_timer_tick_counter = 0U;
	TCCR0A	= 0;      
	//100us       
    TCCR0B	|= _BV(CS01);     
    TCNT0	= 0;            
    TIFR0	|= _BV(OCF0A);     
    TIMSK0	|= _BV(TOIE0) ;
}

//get the tick counter
Int32U DrvTickGetTimeUs(void)
{
	Int8U tcnt = 0;
	ATOMIC
	(
		tcnt = TCNT0;
	);
	return (Int32U)((drv_timer_tick_counter * TIMER0_OVF) + (tcnt * TIMER0_TICK));
}

void DrvTickDelayMs( Int16U delay_ms )
{
	Int32U time_test = 0UL;
	drv_timer_start_delay = DrvTickGetTimeUs() ;
	time_test = (Int32U)((Int32U)drv_timer_start_delay + (Int32U)((Int32U)delay_ms * 1000UL));
	do 
	{
		if(DrvTickGetTimeUs() > time_test)
		{
			break;
		}
	} while (TRUE);
}

void DrvTickDelayUs( Int16U delay_us )
{
	Int32U time_test = 0UL;
	drv_timer_start_delay = DrvTickGetTimeUs() ;
	time_test = (Int32U)(drv_timer_start_delay + (Int32U)delay_us);
	do 
	{
		if(DrvTickGetTimeUs() > time_test)
		{
			break;
		}
	} while (TRUE);
}

Int32U DrvTickGetInterval( Int32U *last_interval )
{
	Int32U now = DrvTickGetTimeUs();
	Int32U interval = now - last_interval[ 0U ];
	last_interval[ 0U ] = now;
	return interval;
}


///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
//ISR timer system 128us
ISR(TIMER0_OVF_vect)
{
	drv_timer_tick_counter += 1U ;
}	

	