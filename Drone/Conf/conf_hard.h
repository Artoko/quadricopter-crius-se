/*
 * conf_hard.h
 *
 * Created: 12/07/2011 18:18:08
 *  Author: berryer
 */ 


#ifndef CONF_HARD_H_
#define CONF_HARD_H_

#include <util/atomic.h>
#include <avr/io.h> 
#include <avr/eeprom.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Tools/tools_typedefs.h"

//-----------------------------------------------------------------------------------------------//

#define LED_ON()			(PORTB	|=	(1 << PORTB5))
#define LED_OFF()			(PORTB	&=~	(1 << PORTB5))
#define LED_TOGGLE()		(PORTB	^=	(1 << PORTB5))
#define CONFIGURE_LED_PIN() (DDRB	|=	(1 << PORTB5))

////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_HZ				16000000UL
#define		CONF_FOSC_MHZ				16UL
#define		STD_LOOP_TIME				10			//10ms 
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define CONF_TIMER_HEARTBEAT			0U
#define CONF_TIMER_START_BMP085_1		1U
#define CONF_TIMER_START_BMP085_2		2U
#define CONF_TIMER_NB					5U

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_20MS		( 1 << 0U )
#define		CONF_EVENT_TIMER_100MS		( 1 << 1U )
#define		CONF_EVENT_TIMER_1S			( 1 << 2U )
#define		CONF_EVENT_TIMER_5S			( 1 << 3U )
#define		CONF_EVENT_TIMER_10S		( 1 << 4U )
#define		CONF_EVENT_MSG_RCV			( 1 << 5U )

//PINOUT CRIUS
// A0	PC0
// A1
// A2	//
// A3
// A6	PC6
// A7	PC7
//-----------------------------------------------------------------------------------------------//


/////////////////////////////////////////////PUBLIC UART///////////////////////////////////////////
#define		USE_UART_0		

////////////////////////////////////////////PUBLIC COMM////////////////////////////////////////////
#define		COMM_MOTOR			0
#define		COMM_ANGLE			1
#define		COMM_ALTITUDE		2



//-----------------------------------------------------------------------------------------------//
typedef struct SSangles
{
	Int16S roulis;
	Int16S tangage;
	Int16S lacet;
	Int16U altitude;
	Int16U adc_conv;
	Boolean maintient_altitude;
}Simu;

extern Simu imu_desire;
extern Simu imu_reel;
extern Int16U speed;
extern Int32U pression;
extern Int16S temperature;




#endif /* CONF_HARD_H_ */