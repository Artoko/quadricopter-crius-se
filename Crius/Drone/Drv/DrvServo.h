/*
 * drv_servo.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_SERVO_H_
#define DRV_SERVO_H_

#include "Tools/tools_typedefs.h"

////////////////////////////////////////////PUBLIC DEFINES///////////////////////////////////////////


#define MIN_ANGLE				0U      
#define MAX_ANGLE				180U 

#define PRESCALER_NO			0U
#define PRESCALER_1				_BV(CS10)
#define PRESCALER_8			    _BV(CS11)
#define PRESCALER_64			(_BV(CS11) | _BV(CS10))
#define PRESCALER_256			_BV(CS12)
#define PRESCALER_1024			(_BV(CS12) | _BV(CS10))
#define PRESCALER_TX_FALL		(_BV(CS12) | _BV(CS11))
#define PRESCALER_TX_RISE		(_BV(CS12) | _BV(CS11) | _BV(CS10))

#define TIMER1_TICKS_PER_US		2 //2 ticks pour 1 µs

#define MIN_PULSE_WIDTH			1000U  //us  
#define MAX_PULSE_WIDTH			2000U  //us  
#define TICKS_MIN_PULSE_WIDTH	MIN_PULSE_WIDTH * TIMER1_TICKS_PER_US  
#define TICKS_MAX_PULSE_WIDTH	MAX_PULSE_WIDTH * TIMER1_TICKS_PER_US  

#define PERIOD_SERVO_MAX		10000U 
#define TICKS_PERIOD_SERVO_MAX	PERIOD_SERVO_MAX * TIMER1_TICKS_PER_US   
 	
#define MAX_SERVOS				4U

//calcule la vitesse en fonction de la puissance desiré
#define ConvertPowerToTick(power_const) (Int16U)(SetRange( power_const , 0U		,1000U	,TICKS_MIN_PULSE_WIDTH	,TICKS_MAX_PULSE_WIDTH ) )

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	Int16U pin;
	Int16U ticks;
} servo_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Servo 
Boolean DrvServo( void ) ;

// bouge le servo a la position voulu en angle
Boolean DrvServoUpdate( Int8U index, Int16U angle ) ;

#endif /* DRV_SERVO_H_ */