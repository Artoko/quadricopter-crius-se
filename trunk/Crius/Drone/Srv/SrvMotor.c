/*
 * SrvMotor.c
 *
 * Created: 31/05/2012 16:04:33
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvMotor.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvServo.h"
#include "Drv/DrvTick.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define OFFCOMMAND 1000U
#define MAXCOMMAND 2000U

////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int16U throttle		= 0U;


/************************************************************************/
/* init des moteurs                                                     */
/************************************************************************/
Boolean SrvMotorInit (void) 
{
	//init des variateurs brushless
	DrvServo();
	throttle = OFFCOMMAND;
	rearMotor_R	 = throttle;
	frontMotor_R = throttle;
	rearMotor_L  = throttle;
	frontMotor_L = throttle;
	return TRUE;
}	

/************************************************************************/
/*Commande des moteurs en fonction de l'angle                           */
/************************************************************************/
void SrvMotorUpdate(Int16S roulis, Int16S tangage,Int16S lacet)
{
	if( throttle > OFFCOMMAND)
	{

		//#define QUAD_X_MIX(X,Y,Z) throttle + roulis * X + tangage * Y + lacet * Z
		//motor[0] = PIDMIX(-1,+1,-1); //REAR_R
		//motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
		//motor[2] = PIDMIX(+1,+1,+1); //REAR_L
		//motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
		
		// calcul de la vitesse pour chaque moteur
		rearMotor_R	 = constrain(throttle - roulis + tangage - lacet, OFFCOMMAND, MAXCOMMAND);
		frontMotor_R = constrain(throttle - roulis - tangage + lacet, OFFCOMMAND, MAXCOMMAND);
		rearMotor_L  = constrain(throttle + roulis + tangage + lacet, OFFCOMMAND, MAXCOMMAND);
		frontMotor_L = constrain(throttle + roulis - tangage - lacet, OFFCOMMAND, MAXCOMMAND);
		
		DrvServoMoveToPosition( 0U , (rearMotor_R  - OFFCOMMAND) );
		DrvServoMoveToPosition( 1U , (frontMotor_R - OFFCOMMAND) );
		DrvServoMoveToPosition( 2U , (rearMotor_L  - OFFCOMMAND) );
		DrvServoMoveToPosition( 3U , (frontMotor_L - OFFCOMMAND) );
	}
	else
	{
		//on met la vitesse de tout les moteurs à zeros 
		rearMotor_R	 = throttle;
		frontMotor_R = throttle;
		rearMotor_L  = throttle;
		frontMotor_L = throttle;
		DrvServoMoveToPosition( 0U , 0U );
		DrvServoMoveToPosition( 1U , 0U );
		DrvServoMoveToPosition( 2U , 0U );
		DrvServoMoveToPosition( 3U , 0U );
	}
}	


/************************************************************************/
/*recupere la vitesse des moteurs                                       */
/************************************************************************/
Int16U SrvMotorGetSpeed( void ) 
{
	return throttle;
}

/************************************************************************/
/*applique une vitesse absolue aux moteurs                              */
/************************************************************************/
Boolean SrvMotorApplyAbsoluteSpeed(Int16U speed)
{
	if( speed <= OFFCOMMAND )
	{
		throttle = speed + OFFCOMMAND;
	}
	return TRUE;
}

/************************************************************************/
/*applique une vitesse relative aux moteurs                             */
/************************************************************************/
Boolean SrvMotorApplyRelativeSpeed(Int16U speed)
{
	//la somme doit etre inferieur 
	if( (throttle + speed) <= MAXCOMMAND )
	{
		throttle += speed;
	}
	return TRUE;
}
