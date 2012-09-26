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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Tools/tools_typedefs.h"

//-----------------------------------------------------------------------------------------------//

#define LED_ON()			(PORTB	|=	0x20U)
#define LED_OFF()			(PORTB	&=~	0x20U)
#define LED_TOGGLE()		(PORTB	^=	0x20U)
#define CONFIGURE_LED_PIN() (DDRB	|=	0x20U)

////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_HZ				16000000UL
#define		STD_LOOP_TIME				1000			//10ms 
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_20MS		0U
#define		CONF_EVENT_TIMER_100MS		CONF_EVENT_TIMER_20MS	+ 1U
#define		CONF_EVENT_TIMER_1S			CONF_EVENT_TIMER_100MS	+ 1U
#define		CONF_EVENT_TIMER_5S			CONF_EVENT_TIMER_1S		+ 1U
#define		CONF_EVENT_TIMER_10S		CONF_EVENT_TIMER_5S		+ 1U
#define		CONF_EVENT_MSG_RCV			CONF_EVENT_TIMER_10S	+ 1U

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
#define		COMM_ACCELEROMETRE	0
#define		COMM_GYROSCOPE		1
#define		COMM_MAGNETOMETRE	2
#define		COMM_BAROMETRE		3
#define		COMM_PID			4
#define		COMM_MOTOR			5
#define		COMM_ANGLE			6
#define		COMM_DEBUG			7
//-----------------------------------------------------------------------------------------------//
typedef struct SSangles
{
	Int16S roulis;
	Int16S tangage;
	Int16S lacet;
	Int16U altitude;
}Sangles;

extern Sangles angle_desire;
extern Sangles angle_reel;
extern Int16U speed;
extern Int32U pression;
extern Int16S temperature;




#endif /* CONF_HARD_H_ */