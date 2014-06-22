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
static void SrvCommRepportGeneral( void );

static void SrvCommRepportMotors( void );

static void SrvCommRepportAngles( void );

static void SrvCommRepportSensors( void );

static void SrvCommRepportBarometer( void );

static void SrvCommRepportPID( void );

static void SrvCommRepportEEPROM( void );

static void SrvCommRepportData( void) ;






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
Int8U buffer[ BUFFER_MAX ];
Int8U buffer_size = 0U;

void SrvCommDispatcher (Event_t in_event) 
{
	//on lit le buffer
	DrvUart0ReadBuffer(buffer ,&buffer_size);
		
	//si le buffer est suffisament rempli
	if(buffer_size > 3U)
	{
		Int8S signe = 1;
		Char field_in_message[ 10U ];
		Int8U cpt_message = 0U;
		Int8U cpt_field = 0U;
		//on parcours le buffer 
		for (Int8U loop = 1U ; loop < buffer_size ; loop++)
		{
			if(( buffer[ loop - 1U ] == '#' ) && ( buffer[ loop ] == '#' ) && ( buffer[ 0U ] == '*' ))
			{
				//on reset pour la prochaine trame
				DrvUart0ResetBuffer(loop + 1U);
		
				//dispatche trame
				SrvCommExecute();
			}
			else
			{
				//on cherche le + ou le -
				if( ! ( ( buffer[ loop ] == '-' ) || ( buffer[ loop ] == '+' ) || ( buffer[ loop ] == '#' ) ) )
				{
					field_in_message[ cpt_message ] = buffer[ loop ];
					cpt_message ++;
					//on efface au fur et � mesure
					buffer[ loop ] = 0U ;
				}
				else
				{
					field_in_message[ cpt_message ] = '\0';
					ma_trame_comm.param[ cpt_field ] = atoi(field_in_message) * signe;
					//on met a zero le compteur
					cpt_message = 0;
					//on incremente pour remplir le prochain champ
					cpt_field++;
					//on determine le signe du prochain champ
					if( buffer[ loop ] == '-' )
					{
						signe = -1;
					}
					else
					{
						signe = 1;
					}
				}
			}
		}
	}
}

/************************************************************************/
/*execute message entrant                                               */
/************************************************************************/
static void SrvCommExecute ( void )
{
	if( ma_trame_comm.param[PARAM_0] == COMM_GENERAL )
	{
		SrvCommRepportGeneral();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_MOTORS )
	{
		SrvCommRepportMotors();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_ANGLES )
	{
		SrvCommRepportAngles();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_SENSORS )
	{
		SrvCommRepportSensors();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_BAROMETER )
	{
		SrvCommRepportBarometer();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_PID )
	{
		SrvCommRepportPID();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_EEPROM )
	{
		SrvCommRepportEEPROM();
	}
	else if( ma_trame_comm.param[PARAM_0] == COMM_REPPORT )
	{
		SrvCommRepportData();
	}
	else
	{
		Char o_message[ ] = { '*', COMM_ERROR,'#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	
}	

/************************************************************************/
/*on repporte les donnees                                               */
/************************************************************************/
//report general commands
static void SrvCommRepportGeneral( void )
{	
	//read version
	if( ma_trame_comm.param[PARAM_1] == COMM_GENERAL_VERSION)
	{
		//read eeprom
		Int8U version = 0U;
		DrvEepromReadVersion(&version);
		Char o_message[ ] = { '*', '1', '+', '1', '+', version ,'#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else if( ma_trame_comm.param[PARAM_1] == COMM_GENERAL_RESET)
	{
		//reset
		Char o_message[ ] = { '*', '1', '+', '2', '#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
		//wait for reset
		DrvTimerDelayMs(10);
		RESET_SOFT();
	}
	else if( ma_trame_comm.param[PARAM_1] == COMM_GENERAL_FULL_RESET)
	{
		//deconfigure eeprom
		DrvEepromDeconfigure();
		Char o_message[ ] = { '*', '1', '+', '3', '#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
		//wait for reset
		DrvTimerDelayMs(10);
		RESET_SOFT();
	}
	else
	{
		Char o_message[ ] = { '*', COMM_ERROR,'#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
}

//report or write motors values
static void SrvCommRepportMotors( void )
{
	if( ma_trame_comm.param[PARAM_1] == COMM_MOTOR_WRITE)
	{
		//write puissance
		//controle validit� data
		if(
			( ma_trame_comm.param[PARAM_2] >= 0U ) &&
			( ma_trame_comm.param[PARAM_2] <= 1000U )
		)
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(ma_trame_comm.param[PARAM_2]);
			Char o_message[ ] = { '*', '2', '+', '1', '#','#' };
			DrvUart0SendMessage( o_message , sizeof(o_message) );
		}
		else
		{
			Char o_message[ ] = { '*', COMM_ERROR,'#', '#' };
			DrvUart0SendMessage( o_message , sizeof(o_message) );
		}
	}
	else if( ma_trame_comm.param[PARAM_1] == COMM_MOTOR_READ)
	{
		//read motors
		Char o_message[ ] = { '*', '2', '+', '2',
							 (Int8U)(imu_reel.moteurs.frontMotor_R >> 8U),
							 (Int8U)imu_reel.moteurs.frontMotor_R,
							 (Int8U)(imu_reel.moteurs.frontMotor_L >> 8U),
							 (Int8U)imu_reel.moteurs.frontMotor_L,
							 (Int8U)(imu_reel.moteurs.rearMotor_R >> 8U),
							 (Int8U)imu_reel.moteurs.rearMotor_R,
							 (Int8U)(imu_reel.moteurs.rearMotor_L >> 8U),
							 (Int8U)imu_reel.moteurs.rearMotor_L,
							 (Int8U)(imu_reel.moteurs.throttle >> 8U),
							 (Int8U)imu_reel.moteurs.throttle,			 
							 '#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
	else
	{
		Char o_message[ ] = { '*', COMM_ERROR,'#', '#' };
		DrvUart0SendMessage( o_message , sizeof(o_message) );
	}
}

static void SrvCommRepportAngles( void )
{
	
}

static void SrvCommRepportSensors( void )
{
	
}

static void SrvCommRepportBarometer( void )
{
	
}

static void SrvCommRepportPID( void )
{
	
}

static void SrvCommRepportEEPROM( void )
{
	
}

static void SrvCommRepportData( void )
{
	Char o_message[ 36U ];
	Int8U lenght = 0;
					
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.roulis >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.roulis;	
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.tangage >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.tangage;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.lacet >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.lacet;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.nord >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.nord;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.altitude >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.altitude;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.roulis >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.roulis;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.tangage >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.tangage;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.lacet >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.lacet;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.frontMotor_R >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.frontMotor_R;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.frontMotor_L >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.frontMotor_L;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.rearMotor_R >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.rearMotor_R;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.rearMotor_L >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.rearMotor_L;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.throttle >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.throttle;
	
	o_message[ lenght++ ] = (Int8U)(((Int32U)imu_reel.pressure) >> 24U);
	o_message[ lenght++ ] = (Int8U)(((Int32U)imu_reel.pressure) >> 16U);
	o_message[ lenght++ ] = (Int8U)(((Int32U)imu_reel.pressure) >> 8U);
	o_message[ lenght++ ] = (Int8U)((Int32U)imu_reel.pressure);
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.temperature >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.temperature;
	
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	
	DrvUart0SendMessage( o_message , lenght );
}

