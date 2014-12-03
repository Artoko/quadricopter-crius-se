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
//samples to calib
#define NB_SAMPLE_TO_CALIB_L3G4200	250
//limit for glitch
#define GYRO_GLITCH_LIMIT	800
//value for smoothing
#define GYRO_SMOOTHING_X	20
#define GYRO_SMOOTHING_Y	20
#define GYRO_SMOOTHING_Z	3
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int16S previous_reading_l3g4200[ 3U ] = { 0U, 0U, 0U };
Int16S gyro_smooth_value_l3g4200[ 3U ] = { 0U, 0U, 0U };
Int8U loop_calibration_l3g4200 = 0U;
Int16S gyro_calib_l3g4200[ 3U ] = { 0, 0, 0 };
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpL3G4200DInit(void)
{
	Boolean conf = FALSE;
	Boolean o_success = FALSE;
	Int8U datum = 0U;
	
	DrvTwiReadReg(L3G4200D_ADDRESS, L3G4200D_WHO_AM_I, &datum );
	if(L3G4200D_WHO_I_AM == datum)
	{
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG1, L3G4200D_CTRL_REG1_DR_400HZ	|
															 L3G4200D_CTRL_REG1_PD	|
															 L3G4200D_CTRL_REG1_ZEN	|
															 L3G4200D_CTRL_REG1_YEN |
															 L3G4200D_CTRL_REG1_XEN	);
		DrvTickDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG2, L3G4200D_CTRL_REG2_NO_HI_PASS);
		DrvTickDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG3, L3G4200D_CTRL_REG3_NO_INTERRUPT);
		DrvTickDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG4, L3G4200D_CTRL_REG4_FS_2000DPS | L3G4200D_CTRL_REG4_BDU_ENABLE);
		DrvTickDelayUs(200);
		DrvTwiWriteReg(L3G4200D_ADDRESS, L3G4200D_CTRL_REG5, L3G4200D_CTRL_REG5_DISABLE_LPF2);
		DrvTickDelayUs(200);
		
		//Calibration du capteur
		//si l'eeprom est configué
		conf = DrvEepromIsConfigured();
		if(conf == FALSE)
		{
			loop_calibration_l3g4200 = NB_SAMPLE_TO_CALIB_L3G4200;
			gyro_calib_l3g4200[ 0U ] = 0;
			gyro_calib_l3g4200[ 1U ] = 0;
			gyro_calib_l3g4200[ 2U ] = 0;
		}
		else
		{
			loop_calibration_l3g4200 = 0U;
			DrvEepromReadGyro(gyro_calib_l3g4200);
		}
		o_success = TRUE;
	}
	return o_success;
}


Boolean CmpL3G4200DIsCalibrate(void)
{
	if(loop_calibration_l3g4200 == 0)
	{
		DrvEepromWriteGyro(gyro_calib_l3g4200);
		return TRUE;
	}
	return FALSE;
}



//Rotation X Y Z
Boolean CmpL3G4200DGetRotation(S_Gyr_Sensor *rot)
{
	Int8U buffer[ 6U ] = { 0, 0, 0, 0, 0, 0 };

	if(DrvTwiReadRegBuf(L3G4200D_ADDRESS, L3G4200D_OUT_X_L | L3G4200D_AUTO_INCREMENT, buffer, 6U) != TRUE )
	{
		return FALSE;
	}
	else
	{
		//read gyro value
		rot->x = (Int16S)((Int16U) buffer[1U] << 8U) | ((Int16U) buffer[0U]);
		rot->y = (Int16S)((Int16U) buffer[3U] << 8U) | ((Int16U) buffer[2U]);
		rot->z = (Int16S)((Int16U) buffer[5U] << 8U) | ((Int16U) buffer[4U]);
		//anti gyro glitch
		//rot->x = SetLimits( rot->x, previous_reading_l3g4200[ 0 ] - GYRO_GLITCH_LIMIT ,previous_reading_l3g4200[ 0 ] + GYRO_GLITCH_LIMIT );
		//rot->y = SetLimits( rot->y, previous_reading_l3g4200[ 1 ] - GYRO_GLITCH_LIMIT ,previous_reading_l3g4200[ 1 ] + GYRO_GLITCH_LIMIT );
		//rot->z = SetLimits( rot->z, previous_reading_l3g4200[ 2 ] - GYRO_GLITCH_LIMIT ,previous_reading_l3g4200[ 2 ] + GYRO_GLITCH_LIMIT );
		
		if(loop_calibration_l3g4200 > 0U)
		{
			if( loop_calibration_l3g4200 == 1U )
			{
				gyro_calib_l3g4200[0U] = gyro_calib_l3g4200[0U] / (NB_SAMPLE_TO_CALIB_L3G4200 - 1);
				gyro_calib_l3g4200[1U] = gyro_calib_l3g4200[1U] / (NB_SAMPLE_TO_CALIB_L3G4200 - 1);
				gyro_calib_l3g4200[2U] = gyro_calib_l3g4200[2U] / (NB_SAMPLE_TO_CALIB_L3G4200 - 1);
			}
			else
			{
				gyro_calib_l3g4200[0U] += rot->x;
				gyro_calib_l3g4200[1U] += rot->y;
				gyro_calib_l3g4200[2U] += rot->z;
			}
			loop_calibration_l3g4200--;
		}
		else
		{
			//read data - zero offset
			rot->x  -= gyro_calib_l3g4200[0U];
			rot->y  -= gyro_calib_l3g4200[1U];
			rot->z  -= gyro_calib_l3g4200[2U];
			
			//smooth gyro value
			/*rot->x = (Int16S) ( ( (Int32S)((Int32S)gyro_smooth_value_l3g4200[0] * (GYRO_SMOOTHING_X - 1) ) + rot->x + 1 ) / GYRO_SMOOTHING_X);
			gyro_smooth_value_l3g4200[0] = rot->x;
			
			rot->y = (Int16S) ( ( (Int32S)((Int32S)gyro_smooth_value_l3g4200[1] * (GYRO_SMOOTHING_Y - 1) ) + rot->y + 1 ) / GYRO_SMOOTHING_Y);
			gyro_smooth_value_l3g4200[1] = rot->y;
			
			rot->z = (Int16S) ( ( (Int32S)((Int32S)gyro_smooth_value_l3g4200[2] * (GYRO_SMOOTHING_Z - 1) ) + rot->z + 1 ) / GYRO_SMOOTHING_Z);
			gyro_smooth_value_l3g4200[2] = rot->z;*/
		}
		
		return TRUE;
	}
}



//Get temperature
Int8S CmpL3G4200DGetTemperature(void)
{
	Int8S temp = 0U;
	DrvTwiReadReg(L3G4200D_ADDRESS, L3G4200D_TEMP_OUT_REG, (Int8U *)&temp);
	return (Int8S)(temp | 0x10);
	
}
