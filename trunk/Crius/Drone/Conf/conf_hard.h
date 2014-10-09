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

////////////////////////////////////////PUBLIC VERSION /////////////////////////////////////////////
//version 1.0
#define VERSION 0x10

////////////////////////////////////////PUBLIC SENSORS BOARD ///////////////////////////////////////
#define DAISY_7		
//#define CRIUS		

#define QUADX
//#define BI

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
#define LED_VERTE_PIN				PORTB1
#define LED_VERTE_ON()				(PORTB	|=	(1 << LED_VERTE_PIN))
#define LED_VERTE_OFF()				(PORTB	&=~	(1 << LED_VERTE_PIN))
#define LED_VERTE_TOGGLE()			(PORTB	^=	(1 << LED_VERTE_PIN))
#define CONFIGURE_VERTE_LED_PIN()	(DDRB	|=	(1 << LED_VERTE_PIN))

#define LED_ORANGE_PIN				PORTB2
#define LED_ORANGE_ON()				(PORTB	|=	(1 << LED_ORANGE_PIN))
#define LED_ORANGE_OFF()				(PORTB	&=~	(1 << LED_ORANGE_PIN))
#define LED_ORANGE_TOGGLE()			(PORTB	^=	(1 << LED_ORANGE_PIN))
#define CONFIGURE_ORANGE_LED_PIN()	(DDRB	|=	(1 << LED_ORANGE_PIN))

#define LED_ROUGE_PIN				PORTB3
#define LED_ROUGE_ON()				(PORTB	|=	(1 << LED_ROUGE_PIN))
#define LED_ROUGE_OFF()				(PORTB	&=~	(1 << LED_ROUGE_PIN))
#define LED_ROUGE_TOGGLE()			(PORTB	^=	(1 << LED_ROUGE_PIN))
#define CONFIGURE_ROUGE_LED_PIN()	(DDRB	|=	(1 << LED_ROUGE_PIN))
////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_MHZ				16UL
#define		CONF_FOSC_HZ				CONF_FOSC_MHZ * 1000000UL
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
#define		CONF_TIMER_HEARTBEAT			0U
#define		CONF_TIMER_BMP085				1U
#define		CONF_TIMER_NB					2U

////////////////////////////////////////////PUBLIC EVENT///////////////////////////////////////////
#define		CONF_EVENT_TIMER_5MS		( 1U << 0U )
#define		CONF_EVENT_TIMER_10MS		( 1U << 1U )
#define		CONF_EVENT_TIMER_20MS		( 1U << 2U )
#define		CONF_EVENT_TIMER_50MS		( 1U << 3U )
#define		CONF_EVENT_TIMER_100MS		( 1U << 4U )
#define		CONF_EVENT_TIMER_250MS		( 1U << 5U )
#define		CONF_EVENT_TIMER_500MS		( 1U << 6U )
#define		CONF_EVENT_TIMER_1S			( 1U << 7U )
#define		CONF_EVENT_MSG_RCV			( 1U << 8U )

////////////////////////////////////PUBLIC SERVOS PORTS///////////////////////////////////////////
#if defined( DAISY_7 )
	#define PORT_DIR_SERVO			DDRA
	#define PORT_SERVO				PORTA
#elif defined( CRIUS )
	#define PORT_DIR_SERVO			DDRC
	#define PORT_SERVO				PORTC
#endif

/////////////////////////////////////PUBLIC PID MANAGMENT///////////////////////////////////////////
#define PID_ROULIS			0U
#define PID_TANGAGE			1U
#define PID_LACET			2U
#define PID_ALTITUDE		3U
#define NB_PID				4U

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
#define		COMM_GENERAL							1U
	#define		COMM_GENERAL_VERSION					1U
	#define		COMM_GENERAL_RESET						2U
	#define		COMM_GENERAL_FULL_RESET					3U
#define		COMM_MOTORS								2U
	#define		COMM_MOTOR_WRITE						1U
	#define		COMM_MOTOR_READ							2U
	#define		COMM_MOTOR_STARTUP_F_R_READ				3U
	#define		COMM_MOTOR_STARTUP_F_R_WRITE			4U
	#define		COMM_MOTOR_STARTUP_R_R_READ				5U
	#define		COMM_MOTOR_STARTUP_R_R_WRITE			6U
	#define		COMM_MOTOR_STARTUP_F_L_READ				7U
	#define		COMM_MOTOR_STARTUP_F_L_WRITE			8U
	#define		COMM_MOTOR_STARTUP_R_L_READ				9U
	#define		COMM_MOTOR_STARTUP_R_L_WRITE			10U
#define		COMM_ANGLES								3U
	#define		COMM_ANGLE_WRITE						1U
	#define		COMM_ANGLE_READ							2U
#define		COMM_SENSORS							4U
	#define		COMM_SENSOR_ACC_READ					1U
	#define		COMM_SENSOR_GYR_READ					2U
	#define		COMM_SENSOR_MAG_READ					3U
	#define		COMM_SENSOR_BAR_READ					4U
#define		COMM_PID								5U
	#define		COMM_PID_WRITE							1U
	#define		COMM_PID_READ							2U
#define		COMM_WRITE_ALL							6U
#define		COMM_ERROR								0xFFU

////////////////////////////////////////////ANGLES MIN MAX////////////////////////////////////////////
#define		ANGLE_MAX			90.0
#define		ANGLE_MIN			-90.0

////////////////////////////////////////////MOTORS MIN MAX////////////////////////////////////////////
#define MOTOR_OFF_COMMAND 0
#define MOTOR_MAX_COMMAND 1000
//-----------------------------------------------------------------------------------------------//
typedef struct SS_moteur
{
	Int16U throttle;
	Int16U front_right;
	Int16U front_left;
	Int16U rear_right;
	Int16U rear_left;
	Int16U front_right_startup;
	Int16U front_left_startup;
	Int16U rear_right_startup;
	Int16U rear_left_startup;
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
typedef struct
{
	float roulis;
	float tangage;
}S_Acc_Angles;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	float roulis;
	float tangage;
	float lacet;
}S_Gyr_Angles;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	Int16S x;
	Int16S y;
	Int16S z;
}S_Acc_Sensor;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	Int16S x;
	Int16S y;
	Int16S z;
	Int16S noise;
}S_Gyr_Sensor;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	Int16S x;
	Int16S y;
	Int16S z;
}S_Mag_Sensor;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	Int16U			altitude;
	Int32U			pressure;
	Int16S			temperature;
	Int8U			weather;
}S_Bar_Sensor;

//-----------------------------------------------------------------------------------------------//
typedef struct
{
	S_Acc_Sensor acc;
	S_Gyr_Sensor gyr;
	S_Mag_Sensor mag;
	S_Bar_Sensor bar;
}S_Sensors;

//-----------------------------------------------------------------------------------------------//
typedef struct SS_imu
{
	S_Sensors		sensors;
	S_Acc_Angles	acc_angles;
	S_Gyr_Angles	gyr_angles;
	S_angles		angles;
	S_moteur		moteurs;
	S_pid			pid_error;
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