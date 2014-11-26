////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"

#include "DrvButton.h"
#include "DrvTimer.h"
#include "DrvEvent.h"
#include "DrvIo.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define BUTTON_DEBOUNCE_PERIOD	5U
////////////////////////////////////////PRIVATE STRUCTURES////////////////////////////////////////
//structure configuration initial des leds
typedef struct SSButton
{
	EIoPin pin;
	Boolean enable;
	Int8U debounce_cpt;
	EButtonState state;
	ptrfct_Isr_Callback_Button ptrfct;
} SButton ;

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//fct appele par le timer
static void DrvButtonIsrCallbackTimer( void ) ;

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//ptr de fonction lors de l'appui sur un bouton
ptrfct_Isr_Callback_Button ptrfct = NULL;
//configuration initial des leds
volatile SButton MesButtons[ E_NB_BUTTON ];

////////////////////////////////////////PUBILC FUNCTIONS//////////////////////////////////////////


//Fonction d'initialisation
//return : TRUE si ok
Boolean DrvButtonInit ( void ) 
{
	Boolean o_success = TRUE;
	
	//init de la callback du debounce des boutons
	DrvTimerAddTimer(E_TIMER_BUTTON, BUTTON_DEBOUNCE_PERIOD, E_TIMER_MODE_PERIODIC, DrvButtonIsrCallbackTimer);

	return o_success;
}

//Fonction d'ajout d'un bouton
Boolean DrvButtonAddButton ( Int8U id_button, EIoPin io_button ,ptrfct_Isr_Callback_Button ptr)
{
	Boolean o_success = FALSE;
	
	if( id_button < E_NB_BUTTON )
	{
		MesButtons[ id_button ].pin = io_button;
		MesButtons[ id_button ].enable = TRUE;
		MesButtons[ id_button ].debounce_cpt = 0U;
		MesButtons[ id_button ].state = E_BUTTON_STATE_RELEASED;
		MesButtons[ id_button ].ptrfct = ptr;
		o_success = DrvIoSetPinInput( io_button );
	}
	return o_success;
}

//Fonction qui retourne l'etat du bouton
EButtonState DrvButtonGetState( Int8U id_button )
{
	return MesButtons[ id_button ].state;
}

/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//fct appele par le timer
static void DrvButtonIsrCallbackTimer( void )
{
	EIOLevel state ;
	//pour tout les boutons
	for( Int8U i = 0U ; i < E_NB_BUTTON ; i++)
	{	//si actif
		if( MesButtons[ i ].enable == TRUE )
		{
			//si released
			if(MesButtons[ i ].state == E_BUTTON_STATE_RELEASED)
			{
				state = DrvIoGetPinState(MesButtons[ i ].pin);
				//test du debounce
				if(state == IO_LEVEL_LOW)
				{
					//debounce
					MesButtons[ i ].debounce_cpt++;
					//superieur a 50ms
					if( MesButtons[ i ].debounce_cpt >= 10U )
					{
						MesButtons[ i ].state = E_BUTTON_STATE_PUSHED;
						//appelle de la fonction
						if(MesButtons[ i ].ptrfct != NULL)
						{
							MesButtons[ i ].ptrfct( MesButtons[ i ].state );
						}
						//reset du cpt
						MesButtons[ i ].debounce_cpt = 0U;
						//add event
						DrvEventAddEvent(CONF_EVENT_BUTTON);
					}
				}
				else
				{
					//reset du debounce
					MesButtons[ i ].debounce_cpt = 0;
				}
			}
			//si pushed
			else
			{
				state = DrvIoGetPinState(MesButtons[ i ].pin);
				//test du debounce
				if(state == IO_LEVEL_HIGH)
				{
					//debounce
					MesButtons[ i ].debounce_cpt++;
					//superieur a 50ms
					if( MesButtons[ i ].debounce_cpt >= 10U )
					{
						MesButtons[ i ].state = E_BUTTON_STATE_RELEASED;
						//appelle de la fonction
						if(MesButtons[ i ].ptrfct != NULL)
						{
							MesButtons[ i ].ptrfct( MesButtons[ i ].state );
						}
						//reset du cpt
						MesButtons[ i ].debounce_cpt = 0U;
						//add event
						DrvEventAddEvent(CONF_EVENT_BUTTON);
					}
				}
				else
				{
					//reset du debounce
					MesButtons[ i ].debounce_cpt = 0;
				}
			}
		}
	}
	
}