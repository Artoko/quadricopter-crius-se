////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"

#include "DrvLed.h"
#include "DrvTimer.h"
#include "DrvIo.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define LED_PERIOD	1U
////////////////////////////////////////PRIVATE STRUCTURES////////////////////////////////////////
//structure configuration initial des leds
typedef struct SSLed
{
	EIoPin pin;
	Boolean enable;
	ELedState state;
	ELedMode mode;
	Int8U cpt_on_stop;
	Int8U cpt_on;
	Int8U cpt_off;
	Int8U cpt_off_stop;
} SLed ;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//fct appele par le timer
static void DrvLedIsrCallbackTimer( void ) ;

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//configuration initial des leds
volatile SLed MesLeds[ E_NB_LED ];

////////////////////////////////////////PUBILC FUNCTIONS//////////////////////////////////////////


//Fonction d'initialisation
//return : TRUE si ok
Boolean DrvLedInit ( void )
{
	Boolean o_success = TRUE;
	
	//init de la callback du debounce des boutons
	DrvTimerAddTimer(E_TIMER_LED, LED_PERIOD, E_TIMER_MODE_PERIODIC, DrvLedIsrCallbackTimer);

	return o_success;
}


//Fonction d'ajout de led
Boolean DrvLedAddLed ( Int8U id_led, EIoPin io_led )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		MesLeds[ id_led ].pin = io_led;
		MesLeds[ id_led ].enable = TRUE;
		MesLeds[ id_led ].state = E_LED_OFF;
		MesLeds[ id_led ].mode = E_LED_ON_OFF;
		MesLeds[ id_led ].cpt_on_stop = 0U;
		MesLeds[ id_led ].cpt_on = 0U;
		MesLeds[ id_led ].cpt_off = 0U;
		MesLeds[ id_led ].cpt_off_stop = 0U;
		o_success = DrvIoSetPinOutput( io_led );
	}
	return o_success;
}

//Fonction de modification d'etat de la led en ON
Boolean DrvLedSetOn ( Int8U id_led )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		MesLeds[ id_led ].state = E_LED_ON;
		DrvIoSetPinState(MesLeds[ id_led ].pin,TRUE);
	}
	return o_success;
}

//Fonction de modification d'etat de la led en OFF
Boolean DrvLedSetOff ( Int8U id_led )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		MesLeds[ id_led ].state = E_LED_OFF;
		DrvIoSetPinState(MesLeds[ id_led ].pin,FALSE);
	}
	return o_success;
}

//Fonction de modification d'etat de la led en TOGGLE
Boolean DrvLedSetToggle ( Int8U id_led )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		if( MesLeds[ id_led ].state == E_LED_ON )
		{
			MesLeds[ id_led ].state = E_LED_OFF;
			DrvIoSetPinState(MesLeds[ id_led ].pin,FALSE);
		}
		else if( MesLeds[ id_led ].state == E_LED_OFF )
		{
			MesLeds[ id_led ].state = E_LED_ON;
			DrvIoSetPinState(MesLeds[ id_led ].pin,TRUE);
		}
	}
	return o_success;
}

//Fonction de modification d'etat de la led
Boolean DrvLedSetState ( Int8U id_led, ELedState state )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		if( MesLeds[ id_led ].state == E_LED_ON )
		{
			MesLeds[ id_led ].state = E_LED_ON;
			DrvIoSetPinState(MesLeds[ id_led ].pin,TRUE);
		}
		else if( MesLeds[ id_led ].state == E_LED_OFF )
		{
			MesLeds[ id_led ].state = E_LED_OFF;
			DrvIoSetPinState(MesLeds[ id_led ].pin,FALSE);
		}
	}
	return o_success;
}


//Fonction de modification du mode de la led
Boolean DrvLedSetMode ( Int8U id_led, ELedMode mode )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		MesLeds[ id_led ].mode = mode;
	}
	return o_success;
}


//Fonction de modification du mode de la led
Boolean DrvLedSetBlinkMode ( Int8U id_led, Int8U delay_on , Int8U delay_off )
{
	Boolean o_success = FALSE;
	
	if( id_led < E_NB_LED )
	{
		MesLeds[ id_led ].mode = E_LED_BLINK;
		MesLeds[ id_led ].cpt_on_stop = delay_on;
		MesLeds[ id_led ].cpt_on = 0U;
		MesLeds[ id_led ].cpt_off = 0U;
		MesLeds[ id_led ].cpt_off_stop = delay_off;
	}
	return o_success;
}

/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//fct appele par le timer
static void DrvLedIsrCallbackTimer( void )
{
	//pour tout les boutons
	for( Int8U id_led = 0U ; id_led < E_NB_LED ; id_led++)
	{	
		//si actif
		if( MesLeds[ id_led ].enable == TRUE )
		{	
			//mode est blink
			if( MesLeds[ id_led ].mode == E_LED_BLINK )
			{
				//si on est ON
				if( MesLeds[ id_led ].state == E_LED_ON )
				{
					if( MesLeds[ id_led ].cpt_on++ > MesLeds[ id_led ].cpt_on_stop )
					{
						MesLeds[ id_led ].state = E_LED_OFF;
						DrvIoSetPinState(MesLeds[ id_led ].pin,FALSE);
						MesLeds[ id_led ].cpt_on = 0;
					}
				}
				//si on est OFF
				if( MesLeds[ id_led ].state == E_LED_OFF )
				{
					if( MesLeds[ id_led ].cpt_off++ > MesLeds[ id_led ].cpt_off_stop )
					{
						MesLeds[ id_led ].state = E_LED_ON;
						DrvIoSetPinState(MesLeds[ id_led ].pin,TRUE);
						MesLeds[ id_led ].cpt_off = 0;
					}
				}
			}
		}
	}
	
}