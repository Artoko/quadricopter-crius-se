/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"
#include "DrvServo.h"


#define ConvertPowerToTick(power_const) map( power_const , 0U		,100U	,1000U	,2000U ) / 4U
#define ConvertTickToPower(tick_const)  map( tick_const  , 1000U	,2000U	,0U		,100U  ) * 4U

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static volatile Int8S pin_servo = -1;

static volatile servo_t MesServos[ MAX_SERVOS ];

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv servo 
void DrvServo( void )
{
	for(Int8U index_servo = 0; index_servo < MAX_SERVOS ; index_servo++)
	{	
		MesServos[ index_servo ].pin = index_servo;
		MesServos[ index_servo ].ticks = ConvertPowerToTick( 0U );
		MesServos[ index_servo ].ticks_consigne = MesServos[ index_servo ].ticks;
		PORT_DIR_SERVO |= (1 << index_servo);
	}
	
	//on init le timer 1 tick = 4us
	TCCR1A	= 0U;             
    TCCR1B	|= _BV(CS11) ; //64
    TCCR1B	|= _BV(CS10) ; 
    TIMSK1	|= _BV(OCIE1A) ;
    TCNT1	= 0U;               
}

// bouge le servo a la position voulu 
Boolean DrvServoMoveToPosition( Int8U index, Int8U power)
{
	Boolean ret = FALSE; 
	//consigne
	MesServos[ index ].ticks_consigne = ConvertPowerToTick(power);
	if( MesServos[ index ].ticks_consigne != MesServos[ index ].ticks )
	{	
		MesServos[ index ].ticks = MesServos[ index ].ticks_consigne ;
	}
	else
	{
		ret = TRUE;
	}
	return ret;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
SIGNAL (TIMER1_COMPA_vect) 
{ 
	if(pin_servo < 0)
	{
		TCNT1 = 0U;
	}
	else
	{
		if( pin_servo < MAX_SERVOS )
		{
			PORT_SERVO &=~ ( 1<< MesServos[pin_servo].pin);
		}
	}
	
	pin_servo++;
	if(pin_servo < MAX_SERVOS)
	{
		OCR1A = TCNT1 + MesServos[pin_servo].ticks + OFFSET_TIMER ;
		PORT_SERVO |= ( 1<< MesServos[pin_servo].pin);
		//servo en mouvement
		if( MesServos[pin_servo].ticks != MesServos[pin_servo].ticks_consigne )
		{
			//on souhaite atteindre la consigne
			if( MesServos[pin_servo].ticks < MesServos[pin_servo].ticks_consigne )
			{
				//on applique la nouvelle consigne				
				MesServos[pin_servo].ticks += 1U;					
			}
			else if( MesServos[pin_servo].ticks > MesServos[pin_servo].ticks_consigne )
			{
				//on applique la nouvelle consigne				
				MesServos[pin_servo].ticks -= 1U;		
			}				
		}
	}
	else
	{
		if( pin_servo == MAX_SERVOS )
		{
			OCR1A = (unsigned int)0x0FA0 ; 
			pin_servo = -1; 
		}
	}		
}