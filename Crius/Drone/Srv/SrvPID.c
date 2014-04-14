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
S_IMU_PID pid[ NB_PID ] ;

Int32S error = 0;
Int32S p_term = 0;
Int32S i_term = 0;
Int32S d_term = 0;


//Init des valeurs du pid
void SrvPIDInit( void )
{
	float p,i,d;
	
	for(Int8U loop_pid = 0 ; loop_pid < NB_PID ; loop_pid++ )
	{
		DrvEepromReadPID( loop_pid, &p, &i, &d );
		SrvPIDSetValues( loop_pid, p, i, d );
	}
}

//Set des valeurs du pid
void SrvPIDSetValues( Int8U index, float p, float i, float d )
{
	pid[index].P = p;
	pid[index].I = i;
	pid[index].D = d;
}

Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition )
{
	//determine l'erreur
	error = targetPosition - currentPosition;
	
	//Calcul du terme P
	p_term = pid[index].P * error;
	
	//calcul de l'erreur intégré
	pid[index].integratedError += error;


	//limit de l'erreur
	float windupgaurd = 4.0 / pid[index].I;
	if(pid[index].integratedError > windupgaurd)
	{
		pid[index].integratedError = windupgaurd;
	}
	else if(pid[index].integratedError < -windupgaurd)
	{
		pid[index].integratedError = -windupgaurd;
	}
	
	//Calcul du terme I
	i_term = pid[index].I * pid[index].integratedError;

	//Calcul du terme D
	d_term = pid[index].D *( currentPosition - pid[index].lastPosition );
	
	//on conserve la position actuel
	pid[index].lastPosition = currentPosition;
	
	//retourne le calcul PID
	return (Int16S)(p_term + i_term - d_term);
}

