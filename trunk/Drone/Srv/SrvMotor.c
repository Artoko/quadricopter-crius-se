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
#define MAXCOMMAND 2000


Int16U frontMotor_R = 0U;
Int16U frontMotor_L = 0U;
Int16U rearMotor_R = 0U;
Int16U rearMotor_L = 0U;
Int16U throttle = 0U;



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
	#define QUAD_X_MIX(X,Y,Z) throttle + roulis * X + tangage * Y + lacet * lacet * Z
	// Calculate motor commands
	rearMotor_R	= constrain(QUAD_X_MIX(-1,+1,+1), OFFCOMMAND, MAXCOMMAND);
	frontMotor_R = constrain(QUAD_X_MIX(-1,-1,-1), OFFCOMMAND, MAXCOMMAND);
	rearMotor_L  = constrain(QUAD_X_MIX(+1,+1,-1), OFFCOMMAND, MAXCOMMAND);
	frontMotor_L = constrain(QUAD_X_MIX(+1,-1,+1), OFFCOMMAND, MAXCOMMAND);
		
		
	DrvServoMoveToPosition(0,(rearMotor_R -OFFCOMMAND)/10);
	DrvServoMoveToPosition(1,(frontMotor_R-OFFCOMMAND)/10);
	DrvServoMoveToPosition(2,(rearMotor_L -OFFCOMMAND)/10);
	DrvServoMoveToPosition(3,(frontMotor_L-OFFCOMMAND)/10);
}	

//recupere une vittesse des moteurs
Int16U SrvMotorGetSpeed( void ) 
{
	return throttle;
}

//applique une vittesse aux moteurs
void SrvMotorApplySpeed(Int8U speed)
{
	throttle = (speed * 10U) + OFFCOMMAND;
}
