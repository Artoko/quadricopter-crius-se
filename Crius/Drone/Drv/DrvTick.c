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
Int32U DrvTimerGetTimeUs(void)
{
	Int8U tcnt = 0;
	ATOMIC
	(
		tcnt = TCNT0;
	);
	return (Int32U)((drv_timer_tick_counter * TIMER0_OVF) + (tcnt * TIMER0_TICK));
}

void DrvTimerDelayMs( Int16U delay_ms )
{
	Int32U time_test = 0UL;
	drv_timer_start_delay = DrvTimerGetTimeUs() ;
	time_test = (Int32U)((Int32U)drv_timer_start_delay + (Int32U)((Int32U)delay_ms * 1000UL));
	do 
	{
		if(DrvTimerGetTimeUs() > time_test)
		{
			break;
		}
	} while (TRUE);
}

void DrvTimerDelayUs( Int16U delay_us )
{
	Int32U time_test = 0UL;
	drv_timer_start_delay = DrvTimerGetTimeUs() ;
	time_test = (Int32U)(drv_timer_start_delay + (Int32U)delay_us);
	do 
	{
		if(DrvTimerGetTimeUs() > time_test)
		{
			break;
		}
	} while (TRUE);
}


///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
//ISR timer system 128us
ISR(TIMER0_OVF_vect)
{
	drv_timer_tick_counter += 1U ;
}	

	