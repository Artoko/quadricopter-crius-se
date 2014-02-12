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
#include <avr/fuse.h> 
#include <avr/eeprom.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Tools/tools_typedefs.h"


////////////////////////////////////////PUBLIC SENSORS BOARD////////////////////////////////////////
#define DAISY_7		0
#define CRIUS		1


#if ( DAISY_7 == 1 )
	#define ACC_LIS331DLH	1
	#define GYR_L3G4200D	1
	#define MAG_HMC5883		1
	#define BAR_BMP085		1
#elif ( CRIUS == 1 )
	#define ACC_BMA180		1
	#define GYR_ITG3205		1
	#define MAG_HMC5883		1
	#define BAR_BMP085		1
#endif



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
#define		CONF_TIMER_HEARTBEAT			0U
#define		CONF_TIMER_NB					1U

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_20MS		( 1U << 0U )
#define		CONF_EVENT_TIMER_100MS		( 1U << 1U )
#define		CONF_EVENT_TIMER_500MS		( 1U << 2U )
#define		CONF_EVENT_TIMER_1S			( 1U << 3U )
#define		CONF_EVENT_TIMER_5S			( 1U << 4U )
#define		CONF_EVENT_TIMER_10S		( 1U << 5U )
#define		CONF_EVENT_MSG_RCV			( 1U << 6U )

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
	Int32U pressure;
	Int16S temperature;
	Int8U weather;
	Boolean maintient_altitude;
}Simu;


extern Simu imu_desire;
extern Simu imu_reel;



//erreur retournee par le calcul du PID
extern Int16S pid_erreur_roulis;
extern Int16S pid_erreur_tangage;
extern Int16S pid_erreur_lacet;
extern Int16S pid_erreur_altitude;



#endif /* CONF_HARD_H_ */