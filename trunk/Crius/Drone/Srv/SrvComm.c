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

#include "Drv/DrvUart.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpBMP085.h"

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
	ma_trame_comm.param[PARAM_0] = 0U;
	ma_trame_comm.param[PARAM_1] = 0U;
	ma_trame_comm.param[PARAM_2] = 0U;
	ma_trame_comm.param[PARAM_3] = 0U;
	ma_trame_comm.param[PARAM_4] = 0U;
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
	
	if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_100MS))
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
		   ( ma_trame_comm.param[PARAM_1] <= 1000U ) &&
		   ( ma_trame_comm.param[PARAM_2] <= 0U ) &&
		   ( ma_trame_comm.param[PARAM_3] <= 0U ) &&
		   ( ma_trame_comm.param[PARAM_4] <= 0U )
		  )
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(ma_trame_comm.param[PARAM_1]);
			DrvUart0SendMessage( "OK\n" , 3U );
		}
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ANGLE )
	{ 
		//applique les angle souhait�
		imu_desire.roulis = (Int16S)ma_trame_comm.param[PARAM_1];
		imu_desire.tangage = (Int16S)ma_trame_comm.param[PARAM_2];
		imu_desire.lacet = (Int16S)ma_trame_comm.param[PARAM_3];
		DrvUart0SendMessage( "OK\n" , 3U );
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ALTITUDE )
	{ 
		//on enregistre l'altitude de depart
		SrvImuSensorsSetAltitudeDepart();
		
		//on enregistre l'altitude relative a la position de depart
		SrvImuSensorsSetAltitudeMaintient(ma_trame_comm.param[PARAM_1]);
		DrvUart0SendMessage( "OK\n" , 3U );
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
			P = (float)(Int16S)( ma_trame_comm.param[PARAM_3]);
			I = (float)(Int16S)( ma_trame_comm.param[PARAM_4]);
			I /= 10;
			D = (float)(Int16S)( ma_trame_comm.param[PARAM_5]);
			DrvEepromWritePID(index,P,I,D);
			SrvPIDInit();
			DrvUart0SendMessage( "OK\n" , 3U );
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
			,"PID:%i,%i,%i\n"
			,(Int16S)P
			,(Int16S)(I*10)
			,(Int16S)D
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
	Char o_message[ 30U ];
	Int8U lenght = 0;
	
	lenght = sprintf(	o_message	
						,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n"
						,imu_reel.roulis
						,imu_reel.tangage
						,imu_reel.lacet	
						,imu_reel.altitude
						,pid_erreur_roulis
						,pid_erreur_tangage
						,pid_erreur_lacet
						,frontMotor_R	
						,frontMotor_L	
						,rearMotor_R	
						,rearMotor_L	
						,SrvMotorGetSpeed()
					);
	DrvUart0SendMessage( o_message , lenght );
}
