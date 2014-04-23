/*
 * SrvMotor.c
 *
 * Created: 31/05/2012 16:04:33
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvMotor.h"
#include "SrvPID.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvServo.h"
#include "Drv/DrvTick.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define OFFCOMMAND 1000U
#define MAXCOMMAND 2000U

////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

/************************************************************************/
/* init des moteurs                                                     */
/************************************************************************/
Boolean SrvMotorInit ( void ) 
{
	//init des variateurs brushless
	DrvServo();
	
	imu_reel.moteurs.throttle		= OFFCOMMAND;
	imu_reel.moteurs.rearMotor_R	= OFFCOMMAND;
	imu_reel.moteurs.frontMotor_R	= OFFCOMMAND;
	imu_reel.moteurs.rearMotor_L	= OFFCOMMAND;
	imu_reel.moteurs.frontMotor_L	= OFFCOMMAND;
	
	return TRUE;
}	

/************************************************************************/
/*Commande des moteurs en fonction de l'angle                           */
/************************************************************************/
void SrvMotorUpdate(S_pid pid_error)
{
	if( imu_reel.moteurs.throttle > OFFCOMMAND)
	{
		// calcul de la vitesse pour chaque moteur
		#ifdef BI
		
		//motor[0] = PIDMIX(+1, 0, 0); //LEFT
		//motor[1] = PIDMIX(-1, 0, 0); //RIGHT
		
		imu_reel.moteurs.rearMotor_R  = SetLimits(imu_reel.moteurs.throttle - pid_error.roulis + pid_error.tangage, OFFCOMMAND, MAXCOMMAND);
		imu_reel.moteurs.frontMotor_L = SetLimits(imu_reel.moteurs.throttle + pid_error.roulis - pid_error.tangage, OFFCOMMAND, MAXCOMMAND);
		
		DrvServoUpdate( 0U , (imu_reel.moteurs.rearMotor_R  - OFFCOMMAND) );
		DrvServoUpdate( 3U , (imu_reel.moteurs.frontMotor_L - OFFCOMMAND) );
		
		#endif
		
		#ifdef QUADX 
		
		//motor[0] = PIDMIX(-1,+1,-1); //REAR_R
		//motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
		//motor[2] = PIDMIX(+1,+1,+1); //REAR_L
		//motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
		
		imu_reel.moteurs.rearMotor_R	= SetLimits(imu_reel.moteurs.throttle - pid_error.roulis + pid_error.tangage - pid_error.lacet, OFFCOMMAND, MAXCOMMAND);
		imu_reel.moteurs.frontMotor_R	= SetLimits(imu_reel.moteurs.throttle - pid_error.roulis - pid_error.tangage + pid_error.lacet, OFFCOMMAND, MAXCOMMAND);
		imu_reel.moteurs.rearMotor_L	= SetLimits(imu_reel.moteurs.throttle + pid_error.roulis + pid_error.tangage + pid_error.lacet, OFFCOMMAND, MAXCOMMAND);
		imu_reel.moteurs.frontMotor_L	= SetLimits(imu_reel.moteurs.throttle + pid_error.roulis - pid_error.tangage - pid_error.lacet, OFFCOMMAND, MAXCOMMAND);
		
		DrvServoUpdate( 0U , (imu_reel.moteurs.rearMotor_R  - OFFCOMMAND) );
		DrvServoUpdate( 1U , (imu_reel.moteurs.frontMotor_R - OFFCOMMAND) );
		DrvServoUpdate( 2U , (imu_reel.moteurs.rearMotor_L  - OFFCOMMAND) );
		DrvServoUpdate( 3U , (imu_reel.moteurs.frontMotor_L - OFFCOMMAND) );
		
		#endif
	}
	else
	{
		//on met la vitesse de tout les moteurs à zeros 
		SrvPIDResetValues();
		imu_reel.moteurs.rearMotor_R	= OFFCOMMAND;
		imu_reel.moteurs.frontMotor_R	= OFFCOMMAND;
		imu_reel.moteurs.rearMotor_L	= OFFCOMMAND;
		imu_reel.moteurs.frontMotor_L	= OFFCOMMAND;
		DrvServoUpdate( 0U , 0U );
		DrvServoUpdate( 1U , 0U );
		DrvServoUpdate( 2U , 0U );
		DrvServoUpdate( 3U , 0U );
	}
}	


/************************************************************************/
/*recupere la vitesse des moteurs                                       */
/************************************************************************/
Int16U SrvMotorGetSpeed( void ) 
{
	return imu_reel.moteurs.throttle;
}

/************************************************************************/
/*applique une vitesse absolue aux moteurs                              */
/************************************************************************/
Boolean SrvMotorApplyAbsoluteSpeed(Int16U speed)
{
	if( speed <= OFFCOMMAND )
	{
		imu_reel.moteurs.throttle = speed + OFFCOMMAND;
	}
	return TRUE;
}

/************************************************************************/
/*applique une vitesse relative aux moteurs                             */
/************************************************************************/
Boolean SrvMotorApplyRelativeSpeed(Int16U speed)
{
	//la somme doit etre inferieur 
	if( (imu_reel.moteurs.throttle + speed) <= MAXCOMMAND )
	{
		imu_reel.moteurs.throttle += speed;
	}
	return TRUE;
}
