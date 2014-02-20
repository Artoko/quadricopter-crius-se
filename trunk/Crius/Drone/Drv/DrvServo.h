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

//calcule la vitesse en fonction de la puissance desiré
#define ConvertPowerToTick(power_const) (Int16U)(map( power_const , 0U		,1000U	,MIN_PULSE_WIDTH	,MAX_PULSE_WIDTH ) / 4U)

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

#define MIN_PULSE_WIDTH			1000U   //us  
#define MAX_PULSE_WIDTH			2000U   //us  

#define PERIOD_SERVO_MAX		ConvertPowerToTick( 500 + ( MAX_SERVOS * MAX_PULSE_WIDTH ) );   //ticks  => 5ms period 0.02 / ( ( 1/16000000 ) * 64)
 	
#define MAX_SERVOS				4U

#define PORT_DIR_SERVO			DDRC
#define PORT_SERVO				PORTC



/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	Int16U pin;
	Int16U ticks;
} servo_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Servo 
Boolean DrvServo( void ) ;

// bouge le servo a la position voulu en angle
Boolean DrvServoMoveToPosition( Int8U index, Int16U angle) ;


#endif /* DRV_SERVO_H_ */