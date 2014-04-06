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
//#define DAISY_7		
#define CRIUS		


#if defined( DAISY_7 )
	#define ACC_LIS331DLH	1
	#define GYR_L3G4200D	1
	#define MAG_HMC5883		1
	#define BAR_BMP085		1
#elif defined( CRIUS )
	#define ACC_BMA180		1
	#define GYR_ITG3205		1
	#define MAG_HMC5883		1
	#define BAR_BMP085		1
#endif

//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////PUBLIC LED MANAGMENT///////////////////////////////////////////
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
#define		CONF_TIMER_BMP085				1U
#define		CONF_TIMER_NB					2U

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_5MS		( 1U << 0U )
#define		CONF_EVENT_TIMER_10MS		( 1U << 1U )
#define		CONF_EVENT_TIMER_20MS		( 1U << 2U )
#define		CONF_EVENT_TIMER_100MS		( 1U << 3U )
#define		CONF_EVENT_TIMER_500MS		( 1U << 4U )
#define		CONF_EVENT_TIMER_1S			( 1U << 5U )
#define		CONF_EVENT_TIMER_5S			( 1U << 6U )
#define		CONF_EVENT_TIMER_10S		( 1U << 7U )
#define		CONF_EVENT_MSG_RCV			( 1U << 8U )

////////////////////////////////////PUBLIC SERVOS PORTS///////////////////////////////////////////
#if defined( DAISY_7 )
	#define PORT_DIR_SERVO			DDRB
	#define PORT_SERVO				PORTB
#elif defined( CRIUS )
	#define PORT_DIR_SERVO			DDRC
	#define PORT_SERVO				PORTC
#endif


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
#define		COMM_MOTOR			1U
#define		COMM_ANGLE			2U
#define		COMM_ALTITUDE		3U
#define		COMM_PID			4U
#define		COMM_EEPROM			5U
#define		COMM_REPPORT		6U

////////////////////////////////////////////ANGLES MIN MAX////////////////////////////////////////////
#define		ANGLE_MAX			40.0
#define		ANGLE_MIN			-40.0

//-----------------------------------------------------------------------------------------------//
typedef struct SS_moteur
{
	Int16U throttle;
	Int16U frontMotor_R;
	Int16U frontMotor_L;
	Int16U rearMotor_R;
	Int16U rearMotor_L;
}S_moteur;

//-----------------------------------------------------------------------------------------------//
typedef struct SS_pid
{
	Int16S roulis;
	Int16S tangage;
	Int16S lacet;
	Int16S altitude;
}S_pid;

//-----------------------------------------------------------------------------------------------//
typedef struct SS_angles
{
	Int16S roulis;
	Int16S tangage;
	Int16S lacet;
	Int16S nord;
}S_angles;

//-----------------------------------------------------------------------------------------------//
typedef struct SS_imu
{
	S_moteur	moteurs;
	S_pid		pid_error;
	S_angles	angles;
	Int16U		altitude;
	Int32U		pressure;
	Int16S		temperature;
	Int8U		weather;
}S_imu;

//-----------------------------------------------------------------------------------------------//
typedef struct SS_imu_desiree
{
	S_angles	angles;
	Int16S		altitude;
	Boolean		maintient_altitude;
}S_imu_desiree;




extern S_imu_desiree imu_desire;
extern S_imu imu_reel;



#endif /* CONF_HARD_H_ */