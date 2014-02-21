/*
 * CmpL3G4200D.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpL3G4200D.h"
 
#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

	
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpL3G4200DInit(void)
{
	Int8U datum = 0U;

	DrvTwiReadReg(L3G4200D_ADDRESS, L3G4200D_WHO_AM_I, &datum );
	if(L3G4200D_WHO_I_AM == datum)
	{
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG1, L3G4200D_CTRL_REG1_400HZ_50LPF);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG2, L3G4200D_CTRL_REG2_NO_HI_PASS);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG3, L3G4200D_CTRL_REG3_NO_INTERRUPT);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG4, L3G4200D_CTRL_REG4_DEFAULT);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG5, L3G4200D_CTRL_REG5_ENABLE_LPF2);
		DrvTimerDelayUs(200);
		
		return TRUE;
	}		
	else
	{
		return FALSE;
	}
	
}



//Rotation X Y Z
Boolean CmpL3G4200DGetRotation(S_Gyr_Angle *rot)
{	
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
		
	if(DrvTwiReadRegBuf(L3G4200D_ADDRESS, L3G4200D_OUT_X_L, buffer, 6U) != TRUE )
	{
		return FALSE;
	}
	else 
	{
		rot->x = (Int16S)((Int16U) buffer[0U] << 8U) | ((Int16U) buffer[1U]);    
		rot->y = (Int16S)((Int16U) buffer[2U] << 8U) | ((Int16U) buffer[3U]);   
		rot->z = (Int16S)((Int16U) buffer[4U] << 8U) | ((Int16U) buffer[5U]);  
		return TRUE;
	}	
}