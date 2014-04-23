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
static void SrvCommRepportData( void) ;
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//passage des params de la trame
static STrame ma_trame_comm;

static Boolean want_repport_data = TRUE;

/************************************************************************/
/*init de la communication                                              */
/************************************************************************/
Boolean SrvCommInit (void) 
{
	for( Int8U loop = 0U; loop < NB_PARAM ; loop++)
	{
		ma_trame_comm.param[ loop ] = 0U;
	}
	want_repport_data = TRUE;
	return TRUE;
}	

/************************************************************************/
/*dispatcher d'evenements                                               */
/************************************************************************/
void SrvCommDispatcher (Event_t in_event) 
{
	if( DrvEventTestEvent(in_event, CONF_EVENT_MSG_RCV))
	{
		//reception de la trame
		DrvUart0ReadMessage(&ma_trame_comm);
		//dispatche trame
		SrvCommExecute();
	}
	
	else if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_20MS))
	{
		if( want_repport_data == TRUE )
		{
			SrvCommRepportData();
		}
	}
}

/************************************************************************/
/*execute message entrant                                               */
/************************************************************************/
static void SrvCommExecute ( void )
{
	if(ma_trame_comm.param[PARAM_0] == COMM_MOTOR )
	{ 
		//controle validit� data
		if(
		   ( ma_trame_comm.param[PARAM_1] >= 0U ) &&
		   ( ma_trame_comm.param[PARAM_1] <= 1000U ) 
		  )
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(ma_trame_comm.param[PARAM_1]);
			DrvUart0SendMessage( "OK\n" , strlen("OK\n") );
		}
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ANGLE )
	{ 
		//applique les angle souhait�
		imu_desire.angles.roulis	= (Int16S)ma_trame_comm.param[PARAM_1];
		SetLimits((float)imu_desire.angles.roulis, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.tangage	= (Int16S)ma_trame_comm.param[PARAM_2];
		SetLimits((float)imu_desire.angles.tangage, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.lacet		= (Int16S)ma_trame_comm.param[PARAM_3];
		DrvUart0SendMessage( "OK\n" , 3U );
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ALTITUDE )
	{ 
		if(  ma_trame_comm.param[PARAM_1] == 1 )
		{
			//on enregistre l'altitude de depart
			SrvImuSensorsSetAltitudeDepart();
			DrvUart0SendMessage( "OK\n" , strlen("OK\n") );
		}
		else if(  ma_trame_comm.param[PARAM_1] == 2 )
		{
			Char weather_message[ 20U ];
			Int8U lenght = 0;
			lenght = sprintf(weather_message
			,"WEATHER:%i\n"
			,imu_reel.weather);
			DrvUart0SendMessage( weather_message , lenght );
		}	
		else if(  ma_trame_comm.param[PARAM_1] == 3 )
		{
			//on enregistre l'altitude relative a la position de depart
			SrvImuSensorsSetAltitudeMaintient(ma_trame_comm.param[PARAM_2]);
			DrvUart0SendMessage( "OK\n" , strlen("OK\n") );
		}		
		
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_PID )
	{
		//Write PID
		if(  ma_trame_comm.param[PARAM_1] == 1 )
		{
			Int8U index = 0;
			float P = 0;
			float I = 0;
			float D = 0;
			index = ma_trame_comm.param[PARAM_2];
			P = (float)( ma_trame_comm.param[PARAM_3] / 1000.0 );
			I = (float)( ma_trame_comm.param[PARAM_4] / 1000.0 );
			D = (float)( ma_trame_comm.param[PARAM_5] / 1000.0 );
			DrvEepromWritePID( index, P, I, D );
			SrvPIDSetValues( index, P, I, D );
			DrvUart0SendMessage( "OK\n" , strlen("OK\n") );
		}
		//Read PID
		else
		{
			Int8U index = 0;
			float P = 0;
			float I = 0;
			float D = 0;
			index = ma_trame_comm.param[PARAM_2];
			DrvEepromReadPID(index,&P,&I,&D);
			
			Char pid_message[ 20U ];
			Int8U lenght = 0;
			lenght = sprintf(pid_message
			,"PID:%i,%i,%i,%i\n"
			,index
			,(Int16S)( P * 1000 )
			,(Int16S)( I * 1000 )
			,(Int16S)( D * 1000 )
			);
			DrvUart0SendMessage( pid_message , lenght );
		}
		
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_EEPROM )
	{
		if( ma_trame_comm.param[PARAM_1] == 1U)
		{
			DrvEepromDeconfigure();
		}
		DrvUart0SendMessage( "OK\n" , 3U );
		RESET_SOFT();
	}
	else if (ma_trame_comm.param[PARAM_0]  == COMM_REPPORT)
	{
		if (want_repport_data == TRUE)
		{
			want_repport_data = FALSE;
		}
		else
		{
			want_repport_data = TRUE;
		}
		DrvUart0SendMessage( "OK\n" , 3U );
	}
}	

/************************************************************************/
/*on repporte les donnees                                               */
/************************************************************************/
static void SrvCommRepportData( void )
{
	Char o_message[ 50U ];
	Int8U lenght = 0;

	lenght = sprintf(       o_message
					,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n"
					,imu_reel.angles.roulis
					,imu_reel.angles.tangage
					,imu_reel.angles.lacet
					,imu_reel.angles.nord
					,imu_reel.altitude
					,imu_reel.pid_error.roulis
					,imu_reel.pid_error.tangage
					,imu_reel.pid_error.lacet
					,imu_reel.moteurs.frontMotor_R - 1000
					,imu_reel.moteurs.frontMotor_L - 1000
					,imu_reel.moteurs.rearMotor_R - 1000
					,imu_reel.moteurs.rearMotor_L - 1000
					,SrvMotorGetSpeed() - 1000
					,(Int16U)(imu_reel.pressure / 10)
					,(Int16S)imu_reel.temperature
					);
	DrvUart0SendMessage( o_message , lenght );
}