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
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////


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
	
	
	Boolean eep_config = DrvEepromIsConfigured();
	
	if( eep_config == TRUE )
	{
		//on lit les valeurs 
		DrvEepromReadStartupMotorFrontRight( &imu_reel.moteurs.front_right_startup );
		DrvEepromReadStartupMotorRearRight( &imu_reel.moteurs.rear_right_startup );
		DrvEepromReadStartupMotorFrontLeft( &imu_reel.moteurs.front_left_startup );
		DrvEepromReadStartupMotorRearLeft( &imu_reel.moteurs.rear_left_startup );
	}
	else
	{
		//on ecrit les valeurs nulles
		DrvEepromWriteStartupMotorFrontRight( 0U );
		DrvEepromWriteStartupMotorRearRight( 0U );
		DrvEepromWriteStartupMotorFrontLeft( 0U );
		DrvEepromWriteStartupMotorRearLeft( 0U );
		
		imu_reel.moteurs.front_right_startup = MOTOR_OFF_COMMAND;
		imu_reel.moteurs.front_left_startup = MOTOR_OFF_COMMAND;
		imu_reel.moteurs.rear_right_startup = MOTOR_OFF_COMMAND;
		imu_reel.moteurs.rear_left_startup = MOTOR_OFF_COMMAND;
	}	
	imu_reel.moteurs.throttle		= MOTOR_OFF_COMMAND;
	imu_reel.moteurs.rear_right		= MOTOR_OFF_COMMAND;
	imu_reel.moteurs.front_right	= MOTOR_OFF_COMMAND;
	imu_reel.moteurs.rear_left		= MOTOR_OFF_COMMAND;
	imu_reel.moteurs.front_left		= MOTOR_OFF_COMMAND;
	
	return TRUE;
}	

//dispatcher d'evenements
void SrvMotorDispatcher (Event_t in_event)
{
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_10MS ) == TRUE)
	{	
		// *********************Mise à jour des Moteurs ***************************
		SrvMotorUpdate( imu_reel.pid_error );
	}
}


/************************************************************************/
/*Commande des moteurs en fonction de l'angle                           */
/************************************************************************/
void SrvMotorUpdate(S_pid pid_error)
{
	if( ( imu_reel.moteurs.throttle > MOTOR_OFF_COMMAND) && ( imu_reel.moteurs.throttle <= MOTOR_MAX_COMMAND) )
	{
		// calcul de la vitesse pour chaque moteur
		#ifdef BI
		
		//motor[0] = PIDMIX(+1, 0, 0); //LEFT
		//motor[1] = PIDMIX(-1, 0, 0); //RIGHT
		
		imu_reel.moteurs.rear_right		= SetLimitsInt16S(imu_reel.moteurs.throttle - pid_error.roulis + pid_error.tangage,
															 imu_reel.moteurs.rear_right_startup, MOTOR_MAX_COMMAND);
		imu_reel.moteurs.front_left		= SetLimitsInt16S(imu_reel.moteurs.throttle + pid_error.roulis - pid_error.tangage,
															 imu_reel.moteurs.front_left_startup, MOTOR_MAX_COMMAND);
		
		DrvServoUpdate( 0U , imu_reel.moteurs.rear_right );
		DrvServoUpdate( 3U , imu_reel.moteurs.front_left );
		
		#endif
		
		#ifdef QUADX 
		
		//motor[0] = PIDMIX(-1,+1,-1); //REAR_R
		//motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
		//motor[2] = PIDMIX(+1,+1,+1); //REAR_L
		//motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
		
		imu_reel.moteurs.rear_right		= SetLimitsInt16S(imu_reel.moteurs.throttle - pid_error.roulis + pid_error.tangage - pid_error.lacet, 
															 imu_reel.moteurs.rear_right_startup, MOTOR_MAX_COMMAND);
		imu_reel.moteurs.front_right	= SetLimitsInt16S(imu_reel.moteurs.throttle - pid_error.roulis - pid_error.tangage + pid_error.lacet, 
															 imu_reel.moteurs.front_right_startup, MOTOR_MAX_COMMAND);
		imu_reel.moteurs.rear_left		= SetLimitsInt16S(imu_reel.moteurs.throttle + pid_error.roulis + pid_error.tangage + pid_error.lacet,
															 imu_reel.moteurs.rear_left_startup, MOTOR_MAX_COMMAND);
		imu_reel.moteurs.front_left		= SetLimitsInt16S(imu_reel.moteurs.throttle + pid_error.roulis - pid_error.tangage - pid_error.lacet, 
															 imu_reel.moteurs.front_left_startup, MOTOR_MAX_COMMAND);
		
		DrvServoUpdate( 0U , imu_reel.moteurs.rear_right );
		DrvServoUpdate( 1U , imu_reel.moteurs.front_right );
		DrvServoUpdate( 2U , imu_reel.moteurs.rear_left );
		DrvServoUpdate( 3U , imu_reel.moteurs.front_left );
		
		#endif
	}
	else
	{
		//on met la vitesse de tout les moteurs à zeros 
		SrvPIDResetValues();
		imu_reel.moteurs.rear_right	= MOTOR_OFF_COMMAND;
		imu_reel.moteurs.front_right	= MOTOR_OFF_COMMAND;
		imu_reel.moteurs.rear_left	= MOTOR_OFF_COMMAND;
		imu_reel.moteurs.front_left	= MOTOR_OFF_COMMAND;
		DrvServoUpdate( 0U , MOTOR_OFF_COMMAND );
		DrvServoUpdate( 1U , MOTOR_OFF_COMMAND );
		DrvServoUpdate( 2U , MOTOR_OFF_COMMAND );
		DrvServoUpdate( 3U , MOTOR_OFF_COMMAND );
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
	Boolean o_success = FALSE;
	if( speed <= MOTOR_MAX_COMMAND )
	{
		imu_reel.moteurs.throttle = speed;
		o_success = TRUE;
	}
	return o_success;
}

/************************************************************************/
/*applique une vitesse relative aux moteurs                             */
/************************************************************************/
Boolean SrvMotorApplyRelativeSpeed(Int16S speed)
{
	Boolean o_success = FALSE;
	//la somme doit etre inferieur 
	if( (imu_reel.moteurs.throttle + speed) <= MOTOR_MAX_COMMAND )
	{
		imu_reel.moteurs.throttle += speed;
		o_success = TRUE;
	}
	return o_success;
}
