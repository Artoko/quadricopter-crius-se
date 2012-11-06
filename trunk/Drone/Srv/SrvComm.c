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
		SrvCommRepportData();
	}
}

/************************************************************************/
/*execute message entrant                                               */
/************************************************************************/
static void SrvCommExecute ( void )
{
	if(ma_trame_comm.param[PARAM_0] == COMM_MOTOR )
	{ 
		//controle validité data
		if(( ma_trame_comm.param[PARAM_1] >= 0U ) && ( ma_trame_comm.param[PARAM_1] <= 1000U ))
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(ma_trame_comm.param[PARAM_1]);
		}
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ANGLE )
	{ 
		//applique les angle souhaité
		imu_desire.roulis = ma_trame_comm.param[PARAM_1];
		imu_desire.tangage = -1*ma_trame_comm.param[PARAM_2];
		imu_desire.lacet = ma_trame_comm.param[PARAM_3];
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ALTITUDE )
	{ 
		//on enregistre l'altitude de depart
		//SrvImuSensorsSetAltitudeDepart();
		
		//on enregistre l'altitude relative a la position de depart
		//SrvImuSensorsSetAltitudeMaintient(ma_trame_comm.param[PARAM_1]);
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_PID )
	{
		
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_EEPROM )
	{
		DrvEepromDeconfigure();
		ptrfct_Isr_Callback tt = NULL;
		tt();
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
						,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n"
						,imu_reel.roulis
						,imu_reel.tangage
						,imu_reel.lacet	
						,imu_reel.altitude
						,pid_erreur_roulis
						,pid_erreur_tangage
						,frontMotor_R	
						,frontMotor_L	
						,rearMotor_R	
						,rearMotor_L	
						,SrvMotorGetSpeed()
					);
	DrvUart0SendMessage( o_message , lenght );
}
