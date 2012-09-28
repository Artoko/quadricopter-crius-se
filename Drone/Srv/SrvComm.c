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

#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpBMP085.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_CHAR_MAX		100U

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

static void SrvCommExecute (STrame trame);

//on repporte les donnees
static void SrvCommRepportData(void);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////



//init de la communication exterieur
void SrvCommInit (void) 
{

}	

//dispatcher d'evenements
void SrvCommDispatcher (Event_t in_event) 
{
	if( DrvEventTestEvent(in_event, CONF_EVENT_MSG_RCV))
	{
		STrame ma_trame_comm;
		//reception de la trame
		DrvUart0ReadMessage(&ma_trame_comm);
		//dispatche trame
		SrvCommExecute(ma_trame_comm);
	}
	
	if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_100MS))
	{
		SrvCommRepportData();
	}
}

//execute message
static void SrvCommExecute (STrame trame)
{
	if(trame.param[PARAM_0] == COMM_MOTOR )
	{ 
		//applique la vitesse au moteurs
		SrvMotorApplyAbsoluteSpeed(trame.param[PARAM_1]);
	}
	else if(trame.param[PARAM_0] == COMM_ANGLE )
	{ 
		//applique les angle souhaité
		angle_desire.roulis = trame.param[PARAM_1];
		angle_desire.tangage = trame.param[PARAM_2];
		angle_desire.lacet = trame.param[PARAM_3];
	}
	else if(trame.param[PARAM_0] == COMM_ALTITUDE )
	{ 
		//on enregistre l'altitude de depart
		SrvImuSensorsSetAltitudeDepart();
		
		//on enregistre l'altitude relative a la position de depart
		SrvImuSensorsSetAltitudeMaintient(trame.param[PARAM_1]);
	}
}	


//on repporte les donnees
static void SrvCommRepportData( void )
{
	Char o_message[ 40U ];
	Int8U lenght = 0;
	lenght = sprintf(	o_message	
						,"%i, %i, %i, %i\n"
						,angle_reel.roulis
						,angle_reel.tangage
						,angle_reel.lacet	
						,angle_reel.altitude
					);
	DrvUart0SendMessage( o_message , lenght );
}
