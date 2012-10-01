////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"

#include "DrvAdc.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////

////////////////////////////////////////PRIVATE STRUCTURES////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int16U adc_conv = 0U;

////////////////////////////////////////PUBILC FUNCTIONS//////////////////////////////////////////
//Fonction d'initialisation
//return : TRUE si ok
Boolean DrvAdcInit ( void )
{
	Boolean o_success = FALSE;
	ADMUX |= (1<<REFS0);
	ADMUX |= (1<<MUX1);
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADIE);
	adc_conv = 0U;
	return o_success;
}

//Fonction de dispatching d'evenements
void DrvAdcDispatcher ( Event_t in_event )
{
	//on fais une mesure toutes les 100 ms
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		ADCSRA |= (1<<ADSC);
	}		
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//ISR 
ISR(ADC_vect)
{
	adc_conv = ADC;
	imu_reel.adc_conv  = adc_conv;
}	