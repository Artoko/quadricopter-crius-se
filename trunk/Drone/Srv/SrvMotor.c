/*
 * SrvMotor.c
 *
 * Created: 31/05/2012 16:04:33
 *  Author: berryer
 */ 

#include "SrvMotor.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvServo.h"
#include "Drv/DrvTick.h"



#define OFFCOMMAND 1000
#define MAXCOMMAND 1500


static Int16U frontMotor_R = 0U;
static Int16U frontMotor_L = 0U;
static Int16U rearMotor_R = 0U;
static Int16U rearMotor_L = 0U;

static Int16U throttle = 0U;



//init des moteurs
void SrvMotorInit (void) 
{
	//init des variateurs brushless
	DrvServo();
	throttle = OFFCOMMAND;
}	


//Commande des moteurs en fonction de l'angle
void SrvMotorUpdate(Int16S roulis, Int16S tangage,Int16S lacet)
{
	if( throttle > OFFCOMMAND)
	{
		#define QUAD_X_MIX(X,Y,Z) (throttle + roulis * X + tangage * Y + lacet * lacet * Z)
		// Calculate motor commands
		/*
		rearMotor_R	= constrain(QUAD_X_MIX(-1,+1,+1), OFFCOMMAND, MAXCOMMAND);
		frontMotor_R = constrain(QUAD_X_MIX(-1,-1,-1), OFFCOMMAND, MAXCOMMAND);
		rearMotor_L  = constrain(QUAD_X_MIX(+1,+1,-1), OFFCOMMAND, MAXCOMMAND);
		frontMotor_L = constrain(QUAD_X_MIX(+1,-1,+1), OFFCOMMAND, MAXCOMMAND);
		*/
		rearMotor_R	 = constrain(throttle - tangage /*- roulis*/ - lacet, OFFCOMMAND, MAXCOMMAND);
		//frontMotor_R = constrain(throttle + roulis + tangage + lacet, OFFCOMMAND, MAXCOMMAND);
		//rearMotor_L  = constrain(throttle - roulis - tangage + lacet, OFFCOMMAND, MAXCOMMAND);
		frontMotor_L = constrain(throttle + tangage /*+ roulis*/ - lacet, OFFCOMMAND, MAXCOMMAND);
		
		DrvServoMoveToPosition(0,(rearMotor_R -OFFCOMMAND)/10);
		//DrvServoMoveToPosition(1,(frontMotor_R-OFFCOMMAND)/10);
		//DrvServoMoveToPosition(2,(rearMotor_L -OFFCOMMAND)/10);
		DrvServoMoveToPosition(3,(frontMotor_L-OFFCOMMAND)/10);
	}
	else
	{
		//on met tout les moteurs à zeros
		DrvServoMoveToPosition(0,0);
		DrvServoMoveToPosition(1,0);
		DrvServoMoveToPosition(2,0);
		DrvServoMoveToPosition(3,0);
	}
}	

//recupere une vitesse des moteurs
Int16U SrvMotorGetSpeed( void ) 
{
	return throttle;
}

//applique une vitesse aux moteurs
void SrvMotorApplyAbsoluteSpeed(Int8U speed)
{
	throttle = (speed * 10U) + OFFCOMMAND;
}

//applique une vitesse aux moteurs
void SrvMotorApplyRelativeSpeed(Int8U speed)
{
	throttle += speed;
}
