/*
 * SrvPID.c
 *
 * Created: 24/09/2012 14:48:34
 *  Author: berryer
 */ 
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "Srv/SrvPID.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////

////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static S_IMU_PID pid[ NB_PID ] ;

float error = 0.0F;
float p_term = 0.0F;
float i_term = 0.0F;
float d_term = 0.0F;

//Init des valeurs du pid
void SrvPIDInit( void )
{
	float p,i,d = 0.0F;
	Boolean eep_config = DrvEepromIsConfigured();
	
	for(Int8U loop_pid = 0U ; loop_pid < NB_PID ; loop_pid++ )
	{
		if( eep_config == TRUE )
		{
			//on lit les valeurs enregistrés
			DrvEepromReadPID( loop_pid, &p, &i, &d );
		}
		else
		{
			//on ecrit les valeurs nulles
			DrvEepromWritePID( loop_pid, p, i, d );
		}
		//set actual values
		SrvPIDSetValues( loop_pid, p, i, d );
	}
	SrvPIDResetValues( ) ;
}

//Set des valeurs du pid
void SrvPIDSetValues( Int8U index, float p, float i, float d )
{
	pid[index].P = p ;
	pid[index].I = i ;
	pid[index].D = d ;
}

//Reset des valeurs du pid
void SrvPIDResetValues( void )
{
	for(Int8U loop_pid = 0 ; loop_pid < NB_PID ; loop_pid++ )
	{
		pid[ loop_pid ].integratedError = 0.0F ;
		pid[ loop_pid ].lastPosition = 0.0F ;
	}
}

//variables de timming
static float interval_pid = 0U;
static Int32U lastread_pid = 0;
static Int32U now_pid = 0;
Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition )
{
	// ********************* Calcul du temps de cycle *************************
	now_pid = DrvTimerGetTimeUs();
	interval_pid = (float)(now_pid - lastread_pid) / 1000000.0F;
	lastread_pid = now_pid;
	
	//determine l'erreur
	error = (targetPosition - currentPosition );
	
	//Calcul du terme P
	p_term = (float)( pid[index].P * error );
	
	//calcul de l'erreur intégré
	pid[index].integratedError += error * interval_pid ;

	//limit de l'erreur
	float windupgaurd = 100.0F;//pid[index].I * 1000.0;
	if(pid[index].integratedError > windupgaurd)
	{
		pid[index].integratedError = windupgaurd;
	}
	else if(pid[index].integratedError < -windupgaurd)
	{
		pid[index].integratedError = -windupgaurd;
	}
	
	//Calcul du terme I
	i_term = (float)( pid[index].I * pid[index].integratedError );

	//Calcul du terme D
	d_term = (float)( pid[index].D * ( currentPosition - pid[index].lastPosition ) /* interval_pid*/ );
	
	//on conserve la position actuel
	pid[index].lastPosition = currentPosition;
	
	//retourne le calcul PID
	return (Int16S)(float)(p_term + i_term + d_term);
}

