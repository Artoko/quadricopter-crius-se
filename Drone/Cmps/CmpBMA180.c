/*
 * BMA180.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpBMA180.h"

#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_TO_CALIB_BMA180	100
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int8U loop_calibration_bma180 = 0;
static Int16S accel_calib[3] = {0,0,0};
	
 ////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


 /////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpBMA180Init(void)
{
	Int8U control;
	Boolean conf;
	Boolean o_success = FALSE;
	if(BMA180_CHIP_ID == DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_CHIP_ID))
	{
		DrvTimerDelayUs(200);
		//Write on EEPROM enable
		DrvTwiWriteReg(BMA180_ADDRESS,BMA180_REG_CTRL_REG0,1<<4);
		DrvTimerDelayUs(200);
		//Bandwidth filters: 20Hz
		control = DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_BW_TCS);
		control = control & 0x0F;        
		control = control | (0x01 << 4); 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_BW_TCS, control);
		DrvTimerDelayUs(200);
		//Mode: Low-Noise
		control = DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_TC0_Z);
		control = control & 0xFC;
		control = control | 0x00; 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_TC0_Z, control);
		DrvTimerDelayUs(200);
		//Range: +-8G
		control = DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_OFFSET_LSB1);
		control = control & 0xF1;
		control = control | (0x05 << 1); 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_OFFSET_LSB1, control);
		DrvTimerDelayUs(200);
		
		//Calibration du capteur
		//si l'eeprom est configué
		conf = DrvEepromIsConfigured();
		if(conf == FALSE)	
		{
			loop_calibration_bma180 = NB_SAMPLE_TO_CALIB_BMA180;
			accel_calib[0] = 0;
			accel_calib[1] = 0;
			accel_calib[2] = 0;
		}	
		else
		{
			loop_calibration_bma180 = 0;
			DrvEepromReadAcc(accel_calib);
		}	
		o_success = TRUE;
	}
	return o_success;
}

Boolean CmpBMA180IsCalibrate(void)
{
	if(loop_calibration_bma180 == 0)
	{
		DrvEepromWriteAcc(accel_calib);
		return TRUE;
	}
	return FALSE;
}


//Rotation X Y Z
Boolean CmpBMA180GetAcceleration(S_Acc_Angle *acc)
{
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};

	if(DrvTwiReadRegBuf(BMA180_ADDRESS, BMA180_REG_ACC_X_LSB, buffer, 6U) != 6U)
	{
		return FALSE;
	}
	else
	{
		acc->x = (Int16S)(((buffer[1]<<8) | buffer[0])/16);
		acc->y = (Int16S)(((buffer[3]<<8) | buffer[2])/16);
		acc->z = (Int16S)(((buffer[5]<<8) | buffer[4])/16);
		
		if(loop_calibration_bma180 > 0)
		{
			if( loop_calibration_bma180 == 1 )
			{
				accel_calib[0] = accel_calib[0] / NB_SAMPLE_TO_CALIB_BMA180;
				accel_calib[1] = accel_calib[1] / NB_SAMPLE_TO_CALIB_BMA180;
				accel_calib[2] = accel_calib[2] / NB_SAMPLE_TO_CALIB_BMA180;
				accel_calib[2] -= BMA180_ACC_1G;
			}
			else
			{
				accel_calib[0] += acc->x;
				accel_calib[1] += acc->y;
				accel_calib[2] += acc->z;
			}
			loop_calibration_bma180--;
		}
		else
		{
			acc->x  -= accel_calib[0];
			acc->y  -= accel_calib[1];
			acc->z  -= accel_calib[2];
		}
		return TRUE;
	}
}
