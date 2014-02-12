/*
 * CmpITG3205.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpITG3205.h"
 
#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpITG3205Init(void)
{
	if (DrvTwiReadReg(ITG3205_TWI_ADDRESS,ITG3205_RA_WHO_AM_I) == ITG3205_RA_I_AM)
	{
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_PWR_MGM, ITG3205_PWR_H_RESET_BIT);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_DLPF_FS, FS_RANGE_2000 | LPFBW_98HZ );
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_PWR_MGM, PLL_ZGYRO_REF );
		DrvTimerDelayUs(200);
		
		return TRUE;
	}		
	else
	{
		return FALSE;
	}
	
}



//Rotation X Y Z
Boolean CmpITG3205GetRotation(S_Gyr_Angle *rot)
{	
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
		
	if(DrvTwiReadRegBuf(ITG3205_TWI_ADDRESS, ITG3205_RA_GYRO_XOUT_H, buffer, 6U) != 6U)
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