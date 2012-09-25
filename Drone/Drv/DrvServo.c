/*
 * drv_servo.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "DrvServo.h"


#define ConvertPowerToTick(power) 16 * map(power,0,100,1000,2000)
#define ConvertTickToPower(tick)  map(tick,1000,2000,0,100) / 16

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static volatile Int8S pin_servo = -1;

static volatile servo_t MesServos[ MAX_SERVOS ];

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv servo 
void DrvServo( void )
{
	for(Int8U n = 0; n < MAX_SERVOS ; n++)
	{	
		MesServos[ n ].pin = n;
		MesServos[ n ].ticks = ConvertPowerToTick(0U);
		MesServos[ n ].ticks_consigne = MesServos[ n ].ticks;
		PORT_DIR_SERVO |= (1<<n);
	}
	
	//on init le timer 1 tick = 1us
	TCCR1A	= 0;             
    TCCR1B	|= _BV(CS10);     
    TCNT1	= 0;               
    TIFR1	|= _BV(OCF1A);     
    TIMSK1	|= _BV(OCIE1A) ;
}

// bouge le servo a la position voulu 
Boolean DrvServoMoveToPosition( Int8U index, Int8U power)
{
	Boolean ret = FALSE; 
	
	//consigne
	MesServos[ index ].ticks_consigne = ConvertPowerToTick(power);
	if( MesServos[ index ].ticks_consigne != MesServos[index].ticks )
	{	
		MesServos[index].ticks = MesServos[index].ticks_consigne ;
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
		if( pin_servo < MAX_SERVOS )
		{
			PORT_SERVO |= ( 1<< MesServos[pin_servo].pin);
			//servo en mouvement
			if( MesServos[pin_servo].ticks != MesServos[pin_servo].ticks_consigne )
			{
				//on souhaite atteindre la consigne
				if( MesServos[pin_servo].ticks < MesServos[pin_servo].ticks_consigne )
				{
					//on applique la nouvelle consigne				
					MesServos[pin_servo].ticks ++;					
				}
				else if( MesServos[pin_servo].ticks > MesServos[pin_servo].ticks_consigne )
				{
					//on applique la nouvelle consigne				
					MesServos[pin_servo].ticks--;	
				}				
			}
		}
	}
	else
	{
		if( pin_servo == MAX_SERVOS )
		{
			OCR1A = (unsigned int)0xBFFF; 
			pin_servo = -5; 
		}
	}			
}