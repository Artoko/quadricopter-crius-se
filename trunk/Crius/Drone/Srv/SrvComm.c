/*
 * SrvComm.c
 *
 * Created: 31/05/2012 16:04:33
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "SrvComm.h"
#include "SrvMotor.h"
#include "SrvImu.h"
#include "SrvPID.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
//ACC
#if defined( ACC_LIS331DLH )
#include "Cmps/CmpLIS331DLH.h"
#elif defined( ACC_BMA180 )
#include "Cmps/CmpBMA180.h"
#endif

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_CHAR_MAX		100U

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
//execute message entrant
static void SrvCommExecute ( void );

//on repporte les donnees
static void SrvCommRepportGeneral( Int8U comm_type_general );

static void SrvCommRepportMotors( Int8U comm_type_motor, Int16U motor_speed );

static void SrvCommRepportAngles( Int8U comm_type_angle, Int16S angles_roulis, Int16S angles_tangage, Int16S angles_lacet);

static void SrvCommRepportSensors( Int8U comm_type_sensor );

static void SrvCommRepportPID( Int8U comm_type_pid, Int8U index, Int16S pid_p, Int16S pid_i, Int16S pid_d );

static void SrvCommWriteAllData( Int16U motor_speed, Int16S angles_roulis, Int16S angles_tangage, Int16S angles_lacet );

static void SrvCommRepportData( void) ;

static void SrvCommRepportError( void) ;





////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//passage des params de la trame
static STrame ma_trame_comm;

/************************************************************************/
/*init de la communication                                              */
/************************************************************************/
Boolean SrvCommInit (void) 
{
	for( Int8U loop = 0U; loop < NB_PARAM ; loop++)
	{
		ma_trame_comm.param[ loop ] = 0U;
	}
	return TRUE;
}	

/************************************************************************/
/*dispatcher d'evenements                                               */
/************************************************************************/
static Int8U buffer[ BUFFER_MAX ];
Int8U buffer_size = 0U;

void SrvCommDispatcher (Event_t in_event) 
{
	//on lit le buffer
	if( TRUE == DrvUart0ReadBuffer(buffer ,&buffer_size) )
	{
		//dispatche trame
		SrvCommExecute();
	}
}
/************************************************************************/
/*execute message entrant                                               */
/************************************************************************/
static void SrvCommExecute ( void )
{
	buffer[ 2U ] = buffer[ 2U ] - 0x30;
	Int16U motor_speed ;
	Int16S angles_roulis ;
	Int16S angles_tangage;
	Int16S angles_lacet ;
	if( buffer[ 2U ] == COMM_GENERAL )
	{
		buffer[ 4U ] = buffer[ 4U ] - 0x30;
		SrvCommRepportGeneral( buffer[ 4U ] );
	}
	else if( buffer[ 2U ] == COMM_MOTORS )
	{
		buffer[ 4U ] = buffer[ 4U ] - 0x30;
		motor_speed = (buffer[ 6U ] << 8U) | (buffer[ 7U ]); 
		SrvCommRepportMotors(buffer[ 4U ] , motor_speed);
	}
	else if( buffer[ 2U ] == COMM_ANGLES )
	{
		buffer[ 4U ] = buffer[ 4U ] - 0x30;
		angles_roulis = (buffer[ 6U ] << 8U) | (buffer[ 7U ]);
		angles_tangage = (buffer[ 9U ] << 8U) | (buffer[ 10U ]);
		angles_lacet = (buffer[ 12U ] << 8U) | (buffer[ 13U ]);
		SrvCommRepportAngles( buffer[ 4U ], angles_roulis, angles_tangage, angles_lacet);
	}
	else if( buffer[ 2U ] == COMM_SENSORS )
	{
		buffer[ 4U ] = buffer[ 4U ] - 0x30;
		SrvCommRepportSensors( buffer[ 4U ] );
	}
	else if( buffer[ 2U ] == COMM_PID )
	{
		buffer[ 4U ] = buffer[ 4U ] - 0x30;
		Int8U pid_index = buffer[ 6U ] - 0x30;
		Int16S pid_P = (buffer[ 8U ] << 8U) | (buffer[ 9U ]);
		Int16S pid_I = (buffer[ 11U ] << 8U) | (buffer[ 12U ]);
		Int16S pid_D = (buffer[ 14U ] << 8U) | (buffer[ 15U ]);
		SrvCommRepportPID( buffer[ 4U ], pid_index, pid_P, pid_I, pid_D);
	}
	else if( buffer[ 2U ] == COMM_WRITE_ALL )
	{
		motor_speed = (buffer[ 4U ] << 8U) | (buffer[ 5U ]);
		angles_roulis = (buffer[ 7U ] << 8U) | (buffer[ 8U ]);
		angles_tangage = (buffer[ 10U ] << 8U) | (buffer[ 11U ]);
		angles_lacet = (buffer[ 13U ] << 8U) | (buffer[ 14U ]);
		SrvCommWriteAllData(motor_speed, angles_roulis, angles_tangage, angles_lacet);
	}
	else
	{
		SrvCommRepportError();
	}
}	


static void SrvCommRepportError( void ) 
{ 
	Char o_message[ ] = { '*', 0x00 , COMM_ERROR , '*' };
	o_message[ 1U ] = sizeof(o_message);
	DrvUart0SendMessage( o_message , sizeof(o_message) );
}

/************************************************************************/
/*on repporte les donnees                                               */
/************************************************************************/
//report general commands
static void SrvCommRepportGeneral( Int8U comm_type_general )
{		
	//read version
	if( comm_type_general == COMM_GENERAL_VERSION)
	{
		//read eeprom
		Int8U version = 0U;
		DrvEepromReadVersion(&version);
		Char o_message[ ] = { '*', 0x00, '1', '+', '1', '+', version, '*' };
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else if( comm_type_general == COMM_GENERAL_RESET)
	{
		//reset
		Char o_message[ ] = { '*', 0x00, '1', '+', '2', '*' };
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
		//wait for reset
		DrvTimerDelayMs(10);
		RESET_SOFT();
	}
	else if( comm_type_general == COMM_GENERAL_FULL_RESET)
	{
		//deconfigure eeprom
		DrvEepromDeconfigure();
		Char o_message[ ] = { '*', 0x00, '1', '+', '3', '*' };
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
		//wait for reset
		DrvTimerDelayMs(10);
		RESET_SOFT();
	}
	else
	{
		SrvCommRepportError();
	}
}

//report or write motors values
static void SrvCommRepportMotors( Int8U comm_type_motor, Int16U motor_speed )
{
	if( comm_type_motor == COMM_MOTOR_WRITE)
	{
		//write puissance
		//controle validité data
		if(
			( motor_speed >= 0U ) &&
			( motor_speed <= 1000U )
		)
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(motor_speed);
			Char o_message[ ] = { '*', 0x00, '2', '+', '1', '*'};
			o_message[ 1U ] = sizeof(o_message);
			DrvUart0SendMessage( o_message , sizeof(o_message) );
		}
		else
		{
			SrvCommRepportError();
		}
	}
	else if( comm_type_motor == COMM_MOTOR_READ)
	{
		//read motors
		Char o_message[ ] = { '*', 0x00, '2', '+', '2', '+',
							 (Int8U)(imu_reel.moteurs.frontMotor_R >> 8U),
							 (Int8U)imu_reel.moteurs.frontMotor_R,
							 '+',
							 (Int8U)(imu_reel.moteurs.frontMotor_L >> 8U),
							 (Int8U)imu_reel.moteurs.frontMotor_L,
							 '+',
							 (Int8U)(imu_reel.moteurs.rearMotor_R >> 8U),
							 (Int8U)imu_reel.moteurs.rearMotor_R,
							 '+',
							 (Int8U)(imu_reel.moteurs.rearMotor_L >> 8U),
							 (Int8U)imu_reel.moteurs.rearMotor_L,
							 '+',
							 (Int8U)(imu_reel.moteurs.throttle >> 8U),
							 (Int8U)imu_reel.moteurs.throttle,
							 '*'		 
						 };
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else
	{
		SrvCommRepportError();
	}
}

static void SrvCommRepportAngles( Int8U comm_type_angle, Int16S angles_roulis, Int16S angles_tangage, Int16S angles_lacet)
{
	//report angles
	if( comm_type_angle == COMM_ANGLE_WRITE)
	{
		//applique les angle souhaité
		imu_desire.angles.roulis	= angles_roulis;
		SetLimits((float)imu_desire.angles.roulis, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.tangage	= angles_tangage;
		SetLimits((float)imu_desire.angles.tangage, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.lacet		= angles_lacet;
		Char o_message[ ] = { '*', 0x00, '3', '+', '1' , '*' };
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else if( comm_type_angle == COMM_ANGLE_READ)
	{
		Char o_message[ ] = { '*', 0x00, '3', '+', '2',
							(Int8U)(imu_reel.angles.roulis >> 8U),
							(Int8U)imu_reel.angles.roulis,
							'+',
							(Int8U)(imu_reel.angles.tangage >> 8U),
							(Int8U)imu_reel.angles.tangage,
							'+',
							(Int8U)(imu_reel.angles.lacet >> 8U),
							(Int8U)imu_reel.angles.lacet,
							'*'			 
							};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else
	{
		SrvCommRepportError();
	}
}

static void SrvCommRepportSensors( Int8U comm_type_sensor )
{
	//report acc angles 
	if( comm_type_sensor == COMM_SENSOR_ACC_READ)
	{		
		Char o_message[ ] = { '*', 0x00, '4', '+', '1',
							(Int8U)(imu_reel.sensors.acc.x >> 8U),
							(Int8U)imu_reel.sensors.acc.x,
							'+',
							(Int8U)(imu_reel.sensors.acc.y >> 8U),
							(Int8U)imu_reel.sensors.acc.y,
							'+',
							(Int8U)(imu_reel.sensors.acc.z >> 8U),
							(Int8U)imu_reel.sensors.acc.z,
							'*'
							};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	//report gyr angles 
	else if( comm_type_sensor == COMM_SENSOR_GYR_READ)
	{
		Char o_message[ ] = { '*', 0x00, '4', '+', '2',
							(Int8U)(imu_reel.sensors.gyr.x >> 8U),
							(Int8U)imu_reel.sensors.gyr.x,
							'+',
							(Int8U)(imu_reel.sensors.gyr.y >> 8U),
							(Int8U)imu_reel.sensors.gyr.y,
							'+',
							(Int8U)(imu_reel.sensors.gyr.z >> 8U),
							(Int8U)imu_reel.sensors.gyr.z,
							'*'
							};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	//report mag angles 
	else if( comm_type_sensor == COMM_SENSOR_MAG_READ)
	{
		Char o_message[ ] = { '*', 0x00, '4', '+', '3',
							(Int8U)(imu_reel.sensors.mag.x >> 8U),
							(Int8U)imu_reel.sensors.mag.x,
							'+',
							(Int8U)(imu_reel.sensors.mag.y >> 8U),
							(Int8U)imu_reel.sensors.mag.y,
							'+',
							(Int8U)(imu_reel.sensors.mag.z >> 8U),
							(Int8U)imu_reel.sensors.mag.z,
							'*'
							};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	//report baro angles 
	else if( comm_type_sensor == COMM_SENSOR_BAR_READ)
	{
		Char o_message[ ] = { '*', 0x00, '4', '+', '4',
							(Int8U)(imu_reel.sensors.bar.altitude >> 8U),
							(Int8U)imu_reel.sensors.bar.altitude,
							'+',
							(Int8U)(imu_reel.sensors.bar.temperature >> 8U),
							(Int8U)imu_reel.sensors.bar.temperature,
							'+',
							(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 24U),
							(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 16U),
							(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 8U),
							(Int8U)((Int32U)imu_reel.sensors.bar.pressure),
							'+',
							(Int8U)imu_reel.sensors.bar.weather,
							'*'
							};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else
	{
		SrvCommRepportError();
	}
}

static void SrvCommRepportPID( Int8U comm_type_pid, Int8U index, Int16S pid_p, Int16S pid_i, Int16S pid_d )
{		
	//report pid
	if( comm_type_pid == COMM_PID_WRITE)
	{
		//applique les PIDs souhaité
		float P = 0;
		float I = 0;
		float D = 0;
		if( index < NB_PID )
		{
			P =  (float)( pid_p / 1000.0 );
			I =  (float)( pid_i / 1000.0 );
			D =  (float)( pid_d / 1000.0 );
			DrvEepromWritePID( index, P, I, D );
			SrvPIDSetValues( index, P, I, D );
			//on renvoie les valeures PID
			DrvEepromReadPID(index,&P,&I,&D);
			Char o_message[ ] = { '*', 0x00, '5', '+', '1', '+',
								index,
								'+',
								(Int8U)((Int16S)( P * 1000 ) >> 8U),
								(Int8U)((Int16S)( P * 1000 )),
								'+',
								(Int8U)((Int16S)( I * 1000 ) >> 8U),
								(Int8U)((Int16S)( I * 1000 )),
								'+',
								(Int8U)((Int16S)( D * 1000 ) >> 8U),
								(Int8U)((Int16S)( D * 1000 )),
								'*'		 
								};
			o_message[ 1U ] = sizeof(o_message);
			DrvUart0SendMessage( o_message , sizeof(o_message) );
		}
		else
		{
			SrvCommRepportError();
		}
	}
	else if( comm_type_pid == COMM_PID_READ)
	{	
		float P = 0;
		float I = 0;
		float D = 0;
		
		if( index < NB_PID )
		{
			DrvEepromReadPID(index,&P,&I,&D);
			Char o_message[ ] = { '*', 0x00, '5', '+', '2', '+',
								index,
								'+',
								(Int8U)((Int16S)( P * 1000 ) >> 8U),
								(Int8U)((Int16S)( P * 1000 )),
								'+',
								(Int8U)((Int16S)( I * 1000 ) >> 8U),
								(Int8U)((Int16S)( I * 1000 )),
								'+',
								(Int8U)((Int16S)( D * 1000 ) >> 8U),
								(Int8U)((Int16S)( D * 1000 )),
								'*'		 
								};
			o_message[ 1U ] = sizeof(o_message);
			DrvUart0SendMessage( o_message , sizeof(o_message) );
		}
		else
		{
			SrvCommRepportError();
		}
		
	}
	else
	{
		SrvCommRepportError();
	}
}

static void SrvCommWriteAllData( Int16U motor_speed, Int16S angles_roulis, Int16S angles_tangage, Int16S angles_lacet )
{
	if(
		( motor_speed >= 0U ) &&
		( motor_speed <= 1000U )
	)
	{
		//applique la vitesse au moteurs
		SrvMotorApplyAbsoluteSpeed(motor_speed);
		Char o_message[ ] = { '*', 0x00, '2', '+', '1', '*'};
		o_message[ 1U ] = sizeof(o_message);
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	//applique les angles souhaités
	imu_desire.angles.roulis	= angles_roulis;
	SetLimits((float)imu_desire.angles.roulis, ANGLE_MIN, ANGLE_MAX);
	imu_desire.angles.tangage	= angles_tangage;
	SetLimits((float)imu_desire.angles.tangage, ANGLE_MIN, ANGLE_MAX);
	imu_desire.angles.lacet		= angles_lacet;
	SrvCommRepportData();
	
}

static void SrvCommRepportData( void )
{
	Char o_message[ ] = { '*', 0x00, '6', '+', 
				(Int8U)(imu_reel.angles.roulis >> 8U),
				(Int8U)imu_reel.angles.roulis,
				(Int8U)(imu_reel.angles.tangage >> 8U),
				(Int8U)imu_reel.angles.tangage,
				(Int8U)(imu_reel.angles.lacet >> 8U),
				(Int8U)imu_reel.angles.lacet,
				(Int8U)(imu_reel.angles.nord >> 8U),
				(Int8U)imu_reel.angles.nord,
				(Int8U)(imu_reel.sensors.bar.altitude >> 8U),
				(Int8U)imu_reel.sensors.bar.altitude,
				(Int8U)(imu_reel.moteurs.throttle >> 8U),
				(Int8U)imu_reel.moteurs.throttle,
				(Int8U)(imu_reel.moteurs.frontMotor_L >> 8U),
				(Int8U)imu_reel.moteurs.frontMotor_L,
				(Int8U)(imu_reel.moteurs.frontMotor_R >> 8U),
				(Int8U)imu_reel.moteurs.frontMotor_R,
				(Int8U)(imu_reel.moteurs.rearMotor_L >> 8U),
				(Int8U)imu_reel.moteurs.rearMotor_L,
				(Int8U)(imu_reel.moteurs.rearMotor_R >> 8U),
				(Int8U)imu_reel.moteurs.rearMotor_R,
				(Int8U)(imu_reel.sensors.bar.temperature >> 8U),
				(Int8U)imu_reel.sensors.bar.temperature,
				(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 24U),
				(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 16U),
				(Int8U)(((Int32U)imu_reel.sensors.bar.pressure) >> 8U),
				(Int8U)((Int32U)imu_reel.sensors.bar.pressure),
				(Int8U)(imu_reel.sensors.acc.x >> 8U),
				(Int8U)imu_reel.sensors.acc.x,
				(Int8U)(imu_reel.sensors.acc.y >> 8U),
				(Int8U)imu_reel.sensors.acc.y,
				(Int8U)(imu_reel.sensors.acc.z >> 8U),
				(Int8U)imu_reel.sensors.acc.z,
				(Int8U)(imu_reel.sensors.gyr.x >> 8U),
				(Int8U)imu_reel.sensors.gyr.x,
				(Int8U)(imu_reel.sensors.gyr.y >> 8U),
				(Int8U)imu_reel.sensors.gyr.y,
				(Int8U)(imu_reel.sensors.gyr.z >> 8U),
				(Int8U)imu_reel.sensors.gyr.z,
				(Int8U)(imu_reel.sensors.mag.x >> 8U),
				(Int8U)imu_reel.sensors.mag.x,
				(Int8U)(imu_reel.sensors.mag.y >> 8U),
				(Int8U)imu_reel.sensors.mag.y,
				(Int8U)(imu_reel.sensors.mag.z >> 8U),
				(Int8U)imu_reel.sensors.mag.z,
				'*',
			};
	o_message[ 1U ] = sizeof(o_message);
	DrvUart0SendMessage( o_message , sizeof(o_message) );
}


