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

Int16S error = 0, p_term = 0, i_term = 0, d_term = 0;

//Init des valeurs du pid
void SrvPIDInit( void )
{
	float p,i,d = 0.0;
	Boolean eep_config = DrvEepromIsConfigured();
	
	for(Int8U loop_pid = 0 ; loop_pid < NB_PID ; loop_pid++ )
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
		SrvPIDResetValues( loop_pid ) ;
	}
}

//Set des valeurs du pid
void SrvPIDSetValues( Int8U index, float p, float i, float d )
{
	pid[index].P = p ;
	pid[index].I = i ;
	pid[index].D = d ;
}

//Reset des valeurs du pid
void SrvPIDResetValues( Int8U index )
{
	pid[index].integratedError = 0 ;
	pid[index].lastPosition = 0 ;
}

Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition )
{
	//determine l'erreur
	error = targetPosition - currentPosition;
	
	//Calcul du terme P
	p_term = (Int16S)( pid[index].P * error );
	
	//calcul de l'erreur intégré
	pid[index].integratedError += error;

	//limit de l'erreur
	float windupgaurd = 1000.0;//pid[index].I * 1000.0;
	if(pid[index].integratedError > windupgaurd)
	{
		pid[index].integratedError = windupgaurd;
	}
	else if(pid[index].integratedError < -windupgaurd)
	{
		pid[index].integratedError = -windupgaurd;
	}
	
	//Calcul du terme I
	i_term = (Int16S)( pid[index].I * pid[index].integratedError );

	//Calcul du terme D
	d_term = (Int16S)( pid[index].D * ( currentPosition - pid[index].lastPosition ) );
	
	//on conserve la position actuel
	pid[index].lastPosition = currentPosition;
	
	//retourne le calcul PID
	return (Int16S)(p_term + i_term + d_term);
}

