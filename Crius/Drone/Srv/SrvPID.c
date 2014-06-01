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

Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition, float delta_time )
{	
	//determine l'erreur
	error = (targetPosition - currentPosition );
	
	//Calcul du terme P
	p_term = (float)( pid[index].P * error );
	
	//calcul de l'erreur intégré
	pid[index].integratedError += error * delta_time ;

	//limitation de l'erreur
	float windupguard = 500.0F / pid[index].I ;
	
	if(pid[index].integratedError > windupguard)
	{
		pid[index].integratedError = windupguard;
	}
	else if(pid[index].integratedError < -windupguard)
	{
		pid[index].integratedError = -windupguard;
	}
	
	//Calcul du terme I
	i_term = (float)( pid[index].I * pid[index].integratedError );

	//Calcul du terme D
	d_term = (float)((float)( pid[index].D * (float)( currentPosition - pid[index].lastPosition ) ) / delta_time );
	
	//on conserve la position actuel
	pid[index].lastPosition = currentPosition;
	
	//retourne le calcul PID
	return (Int16S)(float)(p_term + i_term + d_term);
}

