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
#define NB_SAMPLE_TO_CALIB_L3G4200D	200
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int8U loop_calibration_L3G4200D = 0;
static Int16S gyro_calib[3] = {0,0,0};
	
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpL3G4200DInit(void)
{
	Boolean conf;
	if (DrvTwiReadReg(L3G4200D_ADDRESS, L3G4200D_WHO_AM_I) == L3G4200D_WHO_I_AM)
	{
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG1, L3G4200D_CTRL_REG1_400HZ_50LPF);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG2, L3G4200D_CTRL_REG2_NO_HI_PASS);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG3, L3G4200D_CTRL_REG3_NO_INTERRUPT);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG4, L3G4200D_CTRL_REG4_DEFAULT);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG5, L3G4200D_CTRL_REG5_DISABLE_LPF2);
		DrvTimerDelayUs(200);
		
		//Calibration du capteur
		//si l'eeprom est configué
		conf = DrvEepromIsConfigured();
		if(conf == FALSE)
		{
				loop_calibration_L3G4200D = NB_SAMPLE_TO_CALIB_L3G4200D;
				gyro_calib[0] = 0;
				gyro_calib[1] = 0;
				gyro_calib[2] = 0;
		}
		else
		{
			loop_calibration_L3G4200D = 0;
			DrvEepromReadGyro(gyro_calib);
		}
		return TRUE;
	}		
	else
	{
		return FALSE;
	}
	
}

Boolean CmpL3G4200DIsCalibrate(void)
{
	if(loop_calibration_L3G4200D == 0)
	{
		DrvEepromWriteGyro(gyro_calib);
		return TRUE;
	}
	return FALSE;
}


//Rotation X Y Z
Boolean CmpL3G4200DGetRotation(S_Gyr_Angle *rot)
{	
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
		
	if(DrvTwiReadRegBuf(L3G4200D_ADDRESS, L3G4200D_OUT_X_L, buffer, 6U) != 6U)
	{
		return FALSE;
	}
	else 
	{
		rot->x = (Int16S)((Int16U) buffer[0U] << 8U) | ((Int16U) buffer[1U]);    
		rot->y = (Int16S)((Int16U) buffer[2U] << 8U) | ((Int16U) buffer[3U]);   
		rot->z = (Int16S)((Int16U) buffer[4U] << 8U) | ((Int16U) buffer[5U]);  
		
		if(loop_calibration_L3G4200D > 0U)
		{
			if( loop_calibration_L3G4200D == 1U )
			{
				gyro_calib[0U] = gyro_calib[0U] / NB_SAMPLE_TO_CALIB_L3G4200D;
				gyro_calib[1U] = gyro_calib[1U] / NB_SAMPLE_TO_CALIB_L3G4200D;
				gyro_calib[2U] = gyro_calib[2U] / NB_SAMPLE_TO_CALIB_L3G4200D;
			}
			else
			{
				gyro_calib[0U] += rot->x;
				gyro_calib[1U] += rot->y;
				gyro_calib[2U] += rot->z;
			}
			loop_calibration_L3G4200D--;
		}
		else
		{
			rot->x  -= gyro_calib[0U];
			rot->y  -= gyro_calib[1U];
			rot->z  -= gyro_calib[2U];
		}
		return TRUE;
	}	
}