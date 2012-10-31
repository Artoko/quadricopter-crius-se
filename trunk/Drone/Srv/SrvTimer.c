/*
 * Srv_timer.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "SrvTimer.h"

#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////
//structure configuration initial des leds
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
#define TIMER2_OFFSET_COMPA		0x18U//0xF9U
#define MACRO_NULL_TIMER {\
							.enable = FALSE,\
							.delay = 0U,\
							.cpt_delay = 0U,\
							.mode = E_TIMER_MODE_NONE,\
							.ptrfct = NULL,\
							.reload = NULL,\
						}\

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//configuration initial des leds
STimer MesTimer[ CONF_TIMER_NB ];

volatile Int16U tick_counter_20ms = 0U;
volatile Int16U tick_counter_50ms = 0U;
volatile Int8U tick_counter_100ms = 0U;
volatile Int8U tick_counter_1s = 0U;
volatile Int8U tick_counter_5s = 0U;
volatile Int8U tick_counter_10s = 0U;
volatile Int32U drv_event_tick_counter_1ms = 0;


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
// fait tourner le timer 0 compA a 1 ms
void SrvTimerInitSystemTimer( void ) ;
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Srv Timer 
void SrvTimerInit( void )
{
	//on configure les timers autre que le timer event
	for(Int8U loop_index = 0U; loop_index < CONF_TIMER_NB ; loop_index++ )
	{
		MesTimer[ loop_index ].enable = FALSE;
		MesTimer[ loop_index ].reload = FALSE;
		MesTimer[ loop_index ].ptrfct = NULL;
	}		
	//on init le timer system a 1 ms
	TCCR2A	= 0;
	TCCR2B	|= _BV(CS22) ;
	TCNT2	= 0;
	OCR2A   = TIMER2_OFFSET_COMPA;
	TIFR2	|= _BV(OCF2A);
	TIMSK2	|= _BV(OCIE2A) ;
}

	
//fct qui parametre le timer
void SrvTimerAddTimer( Int8U index_timer, Int16U delay_100us, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct )
{
	MesTimer[ index_timer ].delay = delay_100us;
	MesTimer[ index_timer ].cpt_delay = 0U;
	MesTimer[ index_timer ].mode = mode;
	MesTimer[ index_timer ].ptrfct = ptrfct;
	MesTimer[ index_timer ].enable = TRUE;
	MesTimer[ index_timer ].reload = FALSE;
}

//fct qui reparametre le timer
void SrvTimerReloadTimer( Int8U index_timer, Int16U delay_100us, ETimerMode mode, ptrfct_Isr_Callback_Timer ptrfct )
{
	MesTimer[ index_timer ].delay = delay_100us;
	MesTimer[ index_timer ].cpt_delay = 0U;
	MesTimer[ index_timer ].mode = mode;
	MesTimer[ index_timer ].ptrfct = ptrfct;
	MesTimer[ index_timer ].enable = TRUE;
	MesTimer[ index_timer ].reload = TRUE;
}

//fct qui met en pause le timer
void SrvTimerPauseTimer( Int8U index_timer )
{	
	MesTimer[ index_timer ].enable = FALSE;
}

//fct qui remet a zero les parametres du timer
void SrvTimerStopTimer( Int8U index_timer )
{	
	MesTimer[ index_timer ].enable    = FALSE;
	MesTimer[ index_timer ].delay     = 0U ;
	MesTimer[ index_timer ].cpt_delay = 0U;
	MesTimer[ index_timer ].mode      = E_TIMER_MODE_NONE;
	MesTimer[ index_timer ].ptrfct    = NULL;
	MesTimer[ index_timer ].reload	  = FALSE;
}

//fct qui reseter le timer
void SrvTimerResetTimer( Int8U index_timer )
{
	MesTimer[ index_timer ].cpt_delay = 0U;	
}


//fct qui fixe un delay au timer
void SrvTimerDelayTimer( Int8U index_timer , Int16U delay)
{
	MesTimer[ index_timer ].cpt_delay = 0U;	
	MesTimer[ index_timer ].delay	  = delay;
}

//on reset tt les timers
void SrvTimerTickReset(void)
{
	cli();
	//on configure les timers autre que le timer event
	for(Int8U loop_index = 0U; loop_index < CONF_TIMER_NB ; loop_index++ )
	{
		MesTimer[ loop_index ].cpt_delay = 0U;	
	}
	drv_event_tick_counter_1ms = 0;
	tick_counter_20ms = 0U;
	tick_counter_50ms = 0U;
	tick_counter_100ms = 0U;
	tick_counter_1s = 0U;
	tick_counter_5s = 0U;
	tick_counter_10s = 0U;
	TCNT2	= 0U;
	OCR2A   = TIMER2_OFFSET_COMPA;
	sei();
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//ISR timer event 1ms
ISR(TIMER2_COMPA_vect)
{
	OCR2A = TCNT2 + TIMER2_OFFSET_COMPA ;
	if(tick_counter_20ms++ == 199)
	{
		tick_counter_20ms = 0;
		DrvEventAddEvent(CONF_EVENT_TIMER_20MS);
		if(tick_counter_100ms++ == 4)
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
	
	for(Int8U loop_index = 0U; loop_index < CONF_TIMER_NB ; loop_index++ )
	{
		//si le timer est activé
		if( MesTimer[ loop_index ].enable == TRUE )
		{
			//on incremente le compteur
			MesTimer[ loop_index ].cpt_delay++;
			
			//on test par rapport a la valeur utilisateur
			if(MesTimer[ loop_index ].cpt_delay == MesTimer[ loop_index ].delay )
			{
				if( MesTimer[ loop_index ].mode != E_TIMER_MODE_NONE )
				{
					//on remet a zero le compteur
					MesTimer[ loop_index ].cpt_delay = 0U;
					
					//on appelle la fonction
					if( MesTimer[ loop_index ].ptrfct != NULL )
					{
						MesTimer[ loop_index ].ptrfct();
					}
					
					//si on est en mode ONE SHOT 
					//on vient d'excecuter la fct
					if (MesTimer[ loop_index ].mode == E_TIMER_MODE_ONE_SHOT)
					{
						if( MesTimer[ loop_index ].reload == FALSE )
						{
							//on reinit le timer
							SrvTimerStopTimer( loop_index );
						}
					}
				}
			}
		}			
	}
}