/*
 * CmpLIS331DLH.c
 *
 * Created: 11/02/2014 12:00:01
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpLIS331DLH.h"

#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_SAMPLE_TO_CALIB_LIS331DLH	10
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

Int8U loop_calibration_liS331dlh = 0U;
Int32S accel_calib_liS331dlh[ 3U ] = { 0, 0, 0 };
	
 ////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


 /////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpLIS331DLHInit(void)
{
	Boolean conf;
	Boolean o_success = FALSE;
	Int8U datum = 0U;

	DrvTwiReadReg(LIS331DLH_ADDRESS, LIS331DLH_WHO_AM_I, &datum );
	if(LIS331DLH_WHO_I_AM == datum)
	{
		DrvTimerDelayUs(200);
		//400Hz
		//Normal Mode
		//Enable XYZ
		DrvTwiWriteReg(LIS331DLH_ADDRESS,LIS331DLH_CTRL_REG1,	LIS331DLH_CTRL_REG1_PM0 |
																	LIS331DLH_CTRL_REG1_DR1 |
																	LIS331DLH_CTRL_REG1_ZEN |
																	LIS331DLH_CTRL_REG1_YEN |
																	LIS331DLH_CTRL_REG1_XEN 
																	);
		DrvTimerDelayUs(200);
		DrvTwiWriteReg(LIS331DLH_ADDRESS,LIS331DLH_CTRL_REG4,	LIS331DLH_CTRL_REG4_BDU |
																 LIS331DLH_CTRL_REG4_BLE);
					 
					 
					 
		//Calibration du capteur
		//si l'eeprom est configué
		conf = DrvEepromIsConfigured();
		if(conf == FALSE)	
		{
			loop_calibration_liS331dlh = NB_SAMPLE_TO_CALIB_LIS331DLH;
			accel_calib_liS331dlh[0U] = 0;
			accel_calib_liS331dlh[1U] = 0;
			accel_calib_liS331dlh[2U] = 0;
		}	
		else
		{
			loop_calibration_liS331dlh = 0;
			DrvEepromReadAcc(accel_calib_liS331dlh);
		}	
		o_success = TRUE;
	}
	return o_success;
}

Boolean CmpLIS331DLHIsCalibrate(void)
{
	if(loop_calibration_liS331dlh == 0)
	{
		DrvEepromWriteAcc(accel_calib_liS331dlh);
		return TRUE;
	}
	return FALSE;
}


//Rotation X Y Z
Boolean CmpLIS331DLHGetAcceleration(S_Acc_Sensor *acc)
{
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
	if( DrvTwiReadRegBuf( LIS331DLH_ADDRESS, LIS331DLH_OUT_X_L | 0x80, buffer, 6U ) != TRUE )
	{
		return FALSE;
	}
	else
	{
		acc->x = (Int16S)((Int16U) buffer[0U] << 8U) | ((Int16U) buffer[1U]);
		acc->y = (Int16S)((Int16U) buffer[2U] << 8U) | ((Int16U) buffer[3U]);
		acc->z = (Int16S)((Int16U) buffer[4U] << 8U) | ((Int16U) buffer[5U]);
		if(loop_calibration_liS331dlh > 0U)
		{
			if( loop_calibration_liS331dlh == 1U )
			{
				accel_calib_liS331dlh[0U] = accel_calib_liS331dlh[0U] / (NB_SAMPLE_TO_CALIB_LIS331DLH - 1);
				accel_calib_liS331dlh[1U] = accel_calib_liS331dlh[1U] / (NB_SAMPLE_TO_CALIB_LIS331DLH - 1);
				accel_calib_liS331dlh[2U] = accel_calib_liS331dlh[2U] / (NB_SAMPLE_TO_CALIB_LIS331DLH - 1);
				accel_calib_liS331dlh[2U] -= LIS331DLH_ACC_1G_2G;
			}
			else
			{
				accel_calib_liS331dlh[0U] += acc->x;
				accel_calib_liS331dlh[1U] += acc->y;
				accel_calib_liS331dlh[2U] += acc->z;
			}
			loop_calibration_liS331dlh--;
		}
		else
		{
			acc->x  -= accel_calib_liS331dlh[0U];
			acc->y  -= accel_calib_liS331dlh[1U];
			acc->z  -= accel_calib_liS331dlh[2U];
		}
		return TRUE;
	}
}
