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

#define PRESCALER				8U

#define MIN_PULSE_WIDTH			1000U   //us  
#define MAX_PULSE_WIDTH			2000U   //us  
 
#define REFRESH_INTERVAL		20000U * PRESCALER  //us

#define OFFSET_TIMER			7U
	
#define MAX_SERVOS				4U

#define PORT_DIR_SERVO			DDRC
#define PORT_SERVO				PORTC



/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct {
	Int16U pin;
	Int16U ticks;
	Int16U ticks_consigne;
} servo_t;

/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Servo 
void DrvServo( void ) ;

// bouge le servo a la position voulu en angle
Boolean DrvServoMoveToPosition( Int8U index, Int8U angle) ;


#endif /* DRV_SERVO_H_ */