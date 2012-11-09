/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"
#include "DrvServo.h"

//calcule la vitesse en fonction de la puissance desiré
#define ConvertPowerToTick(power_const) (Int16U)(map( power_const , 0U		,1000U	,MIN_PULSE_WIDTH	,MAX_PULSE_WIDTH ) / 4U)

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//index du servo controllé lors de l'IT
static volatile Int8S pin_servo = -1;
//tableau des servos actifs
static volatile servo_t MesServos[ MAX_SERVOS ];

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
/************************************************************************/
/*Init du Drv servo                                                     */
/************************************************************************/
Boolean DrvServo( void )
{
	for(Int8U index_servo = 0; index_servo < MAX_SERVOS ; index_servo++)
	{	
		MesServos[ index_servo ].pin = index_servo;
		MesServos[ index_servo ].ticks = ConvertPowerToTick( 0U );
		PORT_DIR_SERVO |= (1 << index_servo);
	}
	
	//on init le timer 1 tick = 4us
	TCCR1A	= 0U;             
    TCCR1B	|= PRESCALER_64 ; //64
    TIMSK1	|= _BV(OCIE1A) ;
    TCNT1	= 0U;  
	
	return TRUE;             
}

/************************************************************************/
/*Bouge le servo a la position voulu                                    */
/************************************************************************/
Boolean DrvServoMoveToPosition( Int8U index, Int16U power)
{
	//consigne
	MesServos[ index ].ticks = ConvertPowerToTick(power);
	return TRUE;
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

///////////////////////////////////////////ISR FUNCTIONS//////////////////////////////////////////
/************************************************************************/
/*IT Timer 1 comparateur A : change pour chaque servo                   */
/************************************************************************/
SIGNAL (TIMER1_COMPA_vect) 
{ 
	//on remet a jour le cpt timer pour les 20ms 
	if(pin_servo < 0)
	{
		TCNT1 = 0U;
	}
	else
	{
		//on met la pin du servo au GND pour chaque servo
		if( pin_servo < MAX_SERVOS )
		{
			PORT_SERVO &=~ ( 1U << MesServos[pin_servo].pin );
		}
	}
	
	//on change de servo
	pin_servo++;
	if(pin_servo < MAX_SERVOS)
	{
		//on charge le temp avant la prochaine IT pour le prochain servo
		OCR1A = TCNT1 + MesServos[pin_servo].ticks ;
		//on met la pin du servo au VCC pour chaque servo
		PORT_SERVO |= ( 1<< MesServos[pin_servo].pin);
	}
	else
	{
		//on charge le temp avant la prochaine IT pour le rafraichissement
		if( pin_servo == MAX_SERVOS )
		{
			OCR1A =  5000U ; //20ms
			pin_servo = -1; 
		}
	}		
}