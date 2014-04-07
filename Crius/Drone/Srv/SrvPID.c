/*
 * SrvPID.c
 *
 * Created: 24/09/2012 14:48:34
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "Srv/SrvPID.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"



////////////////////////////////////////PRIVATE STRUCTURES/////////////////////////////////////////


static S_IMU_PID pid[ 4U ] ;



void SrvPIDInit(void )
{
	float P;
	float I;
	float D;
	//roulis
	DrvEepromReadPID(0U,&P,&I,&D);
	pid[0U].P = P;
	pid[0U].I = I;
	pid[0U].D = D;
	pid[0U].lastPosition = 0;
	pid[0U].integratedError = 0;
	//tangage
	DrvEepromReadPID(1U,&P,&I,&D);
	pid[1U].P = P;
	pid[1U].I = I;
	pid[1U].D = D;
	pid[1U].lastPosition = 0;
	pid[1U].integratedError = 0;
	//lacet
	DrvEepromReadPID(2U,&P,&I,&D);
	pid[2U].P = P;
	pid[2U].I = I;
	pid[2U].D = D;
	pid[2U].lastPosition = 0;
	pid[2U].integratedError = 0;
	//altitude
	DrvEepromReadPID(3U,&P,&I,&D);
	pid[3U].P = P;
	pid[3U].I = I;
	pid[3U].D = D;
	pid[3U].lastPosition = 0;
	pid[3U].integratedError = 0;
	
	
}


static Int32S error = 0;
static Int32S p_term = 0;
static Int32S i_term = 0;
static Int32S d_term = 0;

Int16S SrvPIDCompute(Int8U index, Int16S targetPosition, Int16S currentPosition )
{
	//determine l'erreur
	error = targetPosition - currentPosition;
	
	//Calcul du terme P
	p_term = pid[index].P * error;
	
	//calcul de l'erreur intégré
	pid[index].integratedError += error;


	//limit de l'erreur
	float windupgaurd = 1000;//4.0 / pid[index].I;
	if (pid[index].integratedError > windupgaurd)
	{
		pid[index].integratedError = windupgaurd;
	}
	else if (pid[index].integratedError < -windupgaurd)
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

