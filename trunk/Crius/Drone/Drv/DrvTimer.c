/*
 * Drv_timer.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "DrvTimer.h"
#include "DrvEvent.h"

////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////
//structure configuration initial des timers
typedef struct SSTimer
{
	Boolean enable;
	Int16U delay;
	Int16U cpt_delay;
	ETimerMode mode;
	Boolean reload;
	ptrfct_Isr_Callback_Timer ptrfct;
} STimer ;

////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define TIMER2_OFFSET_COMPA		0x18U
#define TIMER2_OFFSET_COMPB		0xF9U
#define MACRO_NULL_TIMER {\
							.enable = FALSE,\
							.delay = 0U,\
							.cpt_delay = 0U,\
							.mode = E_TIMER_MODE_NONE,\
							.ptrfct = NULL,\
						}\

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//configuration initial des leds
volatile STimer MesTimers[ E_NB_TIMER ];

volatile Int16U tick_counter_100us = 0U;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
// fait tourner le timer 0 compA a 1 ms
void DrvTimerInitSystemTimer( void ) ;
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Timer 
void DrvTimerInit( void )
{
	//on configure les timers autre que le timer event
	for(Int8U loop_index = 0U; loop_index < E_NB_TIMER ; loop_index++ )
	{
		MesTimers[ loop_index ].enable = FALSE;
		MesTimers[ loop_index ].ptrfct = NULL;
	}		
	//on init le timer
	TCCR2A	= 0;
	TCCR2B	|= _BV(CS22) ;
	TCNT2	= 0;
	OCR2A   = TIMER2_OFFSET_COMPA;
	OCR2B   = TIMER2_OFFSET_COMPB;
	//100us
	TIFR2	|= _BV(OCF2A);
	TIMSK2	|= _BV(OCIE2A) ;
	//1ms
	TIFR2	|= _BV(OCF2B);
	TIMSK2	|= _BV(OCIE2B) ;
}

	
//fct qui parametre le timer
void DrvTimerAddTimer( Int8U index_timer, Int16U delay_ms, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct )
{
	MesTimers[ index_timer ].delay = delay_ms;
	MesTimers[ index_timer ].cpt_delay = 0U;
	MesTimers[ index_timer ].mode = mode;
	MesTimers[ index_timer ].ptrfct = ptrfct;
	MesTimers[ index_timer ].enable = TRUE;
}

//fct qui met en pause le timer
void DrvTimerPauseTimer( Int8U index_timer )
{	
	MesTimers[ index_timer ].enable = FALSE;
}

//fct qui remet a zero les parametres du timer
void DrvTimerStopTimer( Int8U index_timer )
{	
	MesTimers[ index_timer ].enable    = FALSE;
	MesTimers[ index_timer ].delay     = 0U ;
	MesTimers[ index_timer ].cpt_delay = 0U;
	MesTimers[ index_timer ].mode      = E_TIMER_MODE_NONE;
	MesTimers[ index_timer ].ptrfct    = NULL;
}

//fct qui reseter le timer
void DrvTimerResetTimer( Int8U index_timer )
{
	MesTimers[ index_timer ].cpt_delay = 0U;	
}

//fct qui fixe un delay au timer
void DrvTimerDelayTimer( Int8U index_timer , Int16U delay)
{
	MesTimers[ index_timer ].cpt_delay = 0U;	
	MesTimers[ index_timer ].delay	  = delay;
}

//on reset tt les timers
void DrvTimerTickReset(void)
{
	//on configure les timers autre que le timer event
	for(Int8U loop_index = 0U; loop_index < E_NB_TIMER ; loop_index++ )
	{
		MesTimers[ loop_index ].cpt_delay = 0U;	
	}
	TCNT2	= 0U;
	OCR2A   = TIMER2_OFFSET_COMPA;
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR timer event 1ms
ISR(TIMER2_COMPB_vect)
{
	for(Int8U loop_index = 0U; loop_index < E_NB_TIMER ; loop_index++ )
	{
		//si le timer est activé
		if( MesTimers[ loop_index ].enable == TRUE )
		{
			//on incremente le compteur
			MesTimers[ loop_index ].cpt_delay++;
			
			//on test par rapport a la valeur utilisateur
			if(MesTimers[ loop_index ].cpt_delay == MesTimers[ loop_index ].delay )
			{
				if( MesTimers[ loop_index ].mode != E_TIMER_MODE_NONE )
				{
					//on remet a zero le compteur
					MesTimers[ loop_index ].cpt_delay = 0U;
					
					//si on est en mode ONE SHOT 
					//on atteind le temp, on supprime le timer
					if (MesTimers[ loop_index ].mode == E_TIMER_MODE_ONE_SHOT)
					{
						//on garde la fonction a ppelé avant de tt effacer
						ptrfct_Isr_Callback_Timer ptrfct = MesTimers[ loop_index ].ptrfct;
						//on supprime le timer One Shot
						DrvTimerStopTimer( loop_index );
						//on appelle la fonction
						if( ptrfct != NULL )
						{
							ptrfct();
						}
					}
					else
					{
						//on appelle la fonction
						if( MesTimers[ loop_index ].ptrfct != NULL )
						{
							MesTimers[ loop_index ].ptrfct();
						}
					}
				}
			}
		}			
	}
}	
//ISR timer event 100us
ISR(TIMER2_COMPA_vect)
{
	//reenclanche le timer dans 100us
	OCR2A = TCNT2 + TIMER2_OFFSET_COMPA ;
	
	tick_counter_100us++;
	if(tick_counter_100us % 50U == 0 )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_5MS);
	}
	if(tick_counter_100us % 100U == 0 )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_10MS);
	}
	if(tick_counter_100us % 200U == 0)
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_20MS );
	}
	if(tick_counter_100us % 500U == 0)
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_50MS );
	}
	if(tick_counter_100us % 1000U == 0U )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_100MS );
	}
	if(tick_counter_100us % 2500U == 0U )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_250MS );
	}
	if(tick_counter_100us % 5000U == 0U )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_500MS );
	}
	if(tick_counter_100us % 10000U == 0U )
	{
		DrvEventAddEvent(CONF_EVENT_TIMER_1S );
		tick_counter_100us=0;
	}
}
