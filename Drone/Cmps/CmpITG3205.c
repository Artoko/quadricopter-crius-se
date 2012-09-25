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

 ////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

#define NB_SAMPLE_TO_CALIB_ITG3205	100
Int8U loop_calibration_ITG3205 = 0;
static Int16S gyro_calib[3] = {0,0,0};
	
 ////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


 /////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpITG3205Init(void)
{
	if (DrvTwiReadReg(ITG3205_TWI_ADDRESS,ITG3205_RA_WHO_AM_I) == ITG3205_RA_I_AM)
	{
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_PWR_MGM, ITG3205_PWR_H_RESET_BIT);
		DrvTimerDelay10Us(20);
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_DLPF_FS, FS_RANGE_2000 | LPFBW_98HZ );
		DrvTimerDelay10Us(20);
		DrvTwiWriteReg(ITG3205_TWI_ADDRESS, ITG3205_RA_PWR_MGM, PLL_ZGYRO_REF );
		DrvTimerDelay10Us(100);
		//Calibration du capteur
		loop_calibration_ITG3205 = NB_SAMPLE_TO_CALIB_ITG3205;
		gyro_calib[0] = 0;
		gyro_calib[1] = 0;
		gyro_calib[2] = 0;
		return TRUE;
	}		
	else
	{
		return FALSE;
	}
	
}

Boolean CmpITG3205IsCalibrate(void)
{
	if(loop_calibration_ITG3205 == 0)
	{
		return TRUE;
	}
	return FALSE;
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
		
		if(( rot->z > -6 ) && ( rot->z < 6 ))
		{
			rot->z = 0U;
		}
		if(loop_calibration_ITG3205 > 0U)
		{
			if( loop_calibration_ITG3205 == 1U )
			{
				gyro_calib[0U] = gyro_calib[0U] / NB_SAMPLE_TO_CALIB_ITG3205;
				gyro_calib[1U] = gyro_calib[1U] / NB_SAMPLE_TO_CALIB_ITG3205;
				gyro_calib[2U] = gyro_calib[2U] / NB_SAMPLE_TO_CALIB_ITG3205;
			}
			else
			{
				gyro_calib[0U] += rot->x;
				gyro_calib[1U] += rot->y;
				gyro_calib[2U] += rot->z;
			}
			loop_calibration_ITG3205--;
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