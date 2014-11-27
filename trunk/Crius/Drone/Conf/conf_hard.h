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

#ifdef DAISY_7 
	#define ACC_LIS331DLH	
	#define GYR_L3G4200D	
	#define MAG_HMC5883		
	#define BAR_BMP085		
#else
#ifdef CRIUS 
	#define ACC_BMA180		
	#define GYR_ITG3205		
	#define MAG_HMC5883		
	#define BAR_BMP085		
#endif
#endif

//-----------------------------------------------------------------------------------------------//

/////////////////////////////////////PUBLIC LED MANAGMENT///////////////////////////////////////////
typedef enum
{
	E_LED_OK,
	E_LED_WARNING,
	E_LED_ERROR,
	//----------------- Alaways at end -----------------------
	E_NB_LED,
	E_LED_NONE
}ELed;

/////////////////////////////////////PUBLIC BOUTON MANAGMENT///////////////////////////////////////////
typedef enum
{
	E_BUTTON_SETUP,
	//----------------- Alaways at end -----------------------
	E_NB_BUTTON,
	E_BUTTON_NONE
}EButton;

////////////////////////////////////////PUBLIC FREQUENCE OSC///////////////////////////////////////
#define		CONF_FOSC_MHZ				16UL
#define		CONF_FOSC_HZ				CONF_FOSC_MHZ * 1000000UL
//-----------------------------------------------------------------------------------------------//


////////////////////////////////////////////PUBLIC TIMER///////////////////////////////////////////
typedef enum
{
	E_TIMER_BUTTON,
	E_TIMER_LED,
	//----------------- Alaways at end -----------------------
	E_NB_TIMER,
	E_TIMER_NONE
}ETimer;


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
#define		CONF_EVENT_BUTTON			( 1U << 9U )

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
	Int32U			loop_time;
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