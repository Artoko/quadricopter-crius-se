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
    TCCR0B	|= _BV(CS01);     
    TCNT0	= 0;            
    TIFR0	|= _BV(OCF0A);     
    TIMSK0	|= _BV(TOIE0) ;
}

	

//get the tick counter
Int32U DrvTimerGetTime(void)
{
	Int32U loc_var = 0U;
	cli();
	loc_var = (Int32U)((drv_timer_tick_counter * TIMER0_OVF) + (TCNT0 * TIMER0_TICK));
	sei();
	return loc_var;
}

void DrvTimerDelayMs( Int16U delay_ms )
{
	drv_timer_start_delay = DrvTimerGetTime() ;
	while (DrvTimerGetTime() < (Int32U)(drv_timer_start_delay + (Int32U)(delay_ms * 1000)) );
}

void DrvTimerDelayUs( Int16U delay_us )
{
	drv_timer_start_delay = DrvTimerGetTime() ;
	while (DrvTimerGetTime() < (Int32U)(drv_timer_start_delay + delay_us) );
}


///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
//ISR timer system 128us
ISR(TIMER0_OVF_vect)
{
	drv_timer_tick_counter += 1 ;
}	

	