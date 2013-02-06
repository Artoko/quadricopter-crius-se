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
#define		STD_LOOP_TIME				20			//20ms 
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define CONF_TIMER_HEARTBEAT			0U
#define CONF_TIMER_BMP085			1U
#define CONF_TIMER_NB					5U

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_20MS		( 1 << 0U )
#define		CONF_EVENT_TIMER_100MS		( 1 << 1U )
#define		CONF_EVENT_TIMER_500MS		( 1 << 2U )
#define		CONF_EVENT_TIMER_1S			( 1 << 3U )
#define		CONF_EVENT_TIMER_5S			( 1 << 4U )
#define		CONF_EVENT_TIMER_10S		( 1 << 5U )
#define		CONF_EVENT_MSG_RCV			( 1 << 6U )

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
#define		COMM_MOTOR			0U
#define		COMM_ANGLE			1U
#define		COMM_ALTITUDE		2U
#define		COMM_PID			3U
#define		COMM_EEPROM			4U
#define		COMM_REPPORT		5U



//-----------------------------------------------------------------------------------------------//
typedef struct SSangles
{
	Int16S roulis;
	Int16S tangage;
	Int16S lacet;
	Int16S nord;
	Int16U altitude;
	Int16U adc_conv;
	Boolean maintient_altitude;
}Simu;


extern Simu imu_desire;
extern Simu imu_reel;
extern Int16U speed;
extern Int32U pression;
extern Int16S temperature;
extern Int16U frontMotor_R;
extern Int16U frontMotor_L;
extern Int16U rearMotor_R;
extern Int16U rearMotor_L;

//erreur retournee par le calcul du PID
extern Int16S pid_erreur_roulis;
extern Int16S pid_erreur_tangage;
extern Int16S pid_erreur_lacet;
extern Int16S pid_erreur_altitude;



#endif /* CONF_HARD_H_ */