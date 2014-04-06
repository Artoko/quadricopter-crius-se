/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"
#include "DrvServo.h"


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//index du servo controllé lors de l'IT
volatile Int8S pin_servo = -1;
//tableau des servos actifs
volatile servo_t MesServos[ MAX_SERVOS ];
Int16U ServoPosTics = 0U;
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
		MesServos[ index_servo ].ticks = TICKS_MIN_PULSE_WIDTH;
		PORT_DIR_SERVO |= (1 << index_servo);
	}
	ServoPosTics = 0U;
	//on init le timer 1 tick = 0.5us
	TCCR1A	= 0U;             
    TCCR1B	|= PRESCALER_8 ;
    TIMSK1	|= _BV(OCIE1A) ;
    TCNT1	= 0U;  
	
	return TRUE;             
}

/************************************************************************/
/*Bouge le servo a la position voulu                                    */
/************************************************************************/
Boolean DrvServoUpdate( Int8U index, Int16U power)
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
	Int16U next_ticks = 0U;
	//on met la pin du servo au GND pour chaque servo
	if( pin_servo < MAX_SERVOS )
	{
		PORT_SERVO &=~ ( 1U << MesServos[pin_servo].pin );
	}
	
	//on change de servo
	pin_servo++;
	
	//on a fait le tour des servos dispos
	if(pin_servo != MAX_SERVOS)
	{
		if(pin_servo > MAX_SERVOS)
		{
			pin_servo = 0;
		}
		//on met la pin du servo au VCC pour chaque servo
		PORT_SERVO |= ( 1<< MesServos[pin_servo].pin);
		//on charge le temp avant la prochaine IT pour le prochain servo
		next_ticks = MesServos[pin_servo].ticks ;
	}
	else
	{
		//on charge le temp avant la prochaine IT pour le rafraichissement
		next_ticks = TICKS_PERIOD_SERVO_MAX - ServoPosTics ;
	}	
	
	OCR1A += next_ticks;
	ServoPosTics += next_ticks;
	if(ServoPosTics >= TICKS_PERIOD_SERVO_MAX)
	{
		ServoPosTics = 0;
	}
}