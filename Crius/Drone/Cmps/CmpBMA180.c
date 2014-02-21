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
Int8U loop_calibration_bma180 = 0U;
static Int16S accel_calib[ 3U ] = { 0, 0, 0 };
	
 ////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


 /////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpBMA180Init(void)
{
	Boolean conf;
	Boolean o_success = FALSE;
	Int8U datum = 0U;

	DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_CHIP_ID, &datum );
	if(BMA180_CHIP_ID == datum)
	{
		DrvTimerDelayUs(200);
		//Write on EEPROM enable
		DrvTwiWriteReg(BMA180_ADDRESS,BMA180_REG_CTRL_REG0, 1U<<4U );
		DrvTimerDelayUs(200);
		//Bandwidth filters: 20Hz
		DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_BW_TCS, &datum );
		datum = datum & 0x0F;        
		datum = datum | (0x01 << 4); 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_BW_TCS, datum);
		DrvTimerDelayUs(200);
		//Mode: Low-Noise
		DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_TC0_Z, &datum );
		datum = datum & 0xFC;
		datum = datum | 0x00; 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_TC0_Z, datum);
		DrvTimerDelayUs(200);
		//Range: +-8G
		DrvTwiReadReg(BMA180_ADDRESS, BMA180_REG_OFFSET_LSB1, &datum );
		datum = datum & 0xF1;
		datum = datum | (0x05 << 1); 
		DrvTwiWriteReg(BMA180_ADDRESS, BMA180_REG_OFFSET_LSB1, datum);
		DrvTimerDelayUs(200);
		
		//Calibration du capteur
		//si l'eeprom est configué
		conf = DrvEepromIsConfigured();
		if(conf == FALSE)	
		{
			loop_calibration_bma180 = NB_SAMPLE_TO_CALIB_BMA180;
			accel_calib[0U] = 0;
			accel_calib[1U] = 0;
			accel_calib[2U] = 0;
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
	Int8U buffer[ 6U ] = { 0, 0, 0, 0, 0, 0 };

	if( DrvTwiReadRegBuf( BMA180_ADDRESS, BMA180_REG_ACC_X_LSB, buffer, 6U ) != TRUE )
	{
		return FALSE;
	}
	else
	{
		acc->x = (Int16S)(((buffer[1U]<<8) | buffer[0U])/16);
		acc->y = (Int16S)(((buffer[3U]<<8) | buffer[2U])/16);
		acc->z = (Int16S)(((buffer[5U]<<8) | buffer[4U])/16);
		
		if(loop_calibration_bma180 > 0U)
		{
			if( loop_calibration_bma180 == 1U )
			{
				accel_calib[0U] = accel_calib[0U] / (NB_SAMPLE_TO_CALIB_BMA180 - 1);
				accel_calib[1U] = accel_calib[1U] / (NB_SAMPLE_TO_CALIB_BMA180 - 1);
				accel_calib[2U] = accel_calib[2U] / (NB_SAMPLE_TO_CALIB_BMA180 - 1);
				accel_calib[2U] -= BMA180_ACC_1G;
			}
			else
			{
				accel_calib[0U] += acc->x;
				accel_calib[1U] += acc->y;
				accel_calib[2U] += acc->z;
			}
			loop_calibration_bma180--;
		}
		else
		{
			acc->x  -= accel_calib[0U];
			acc->y  -= accel_calib[1U];
			acc->z  -= accel_calib[2U];
		}
		return TRUE;
	}
}
