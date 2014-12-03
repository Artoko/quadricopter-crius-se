/*
 * CmpHMC5883.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpHMC5883.h"

#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"

////////////////////////////////////////PRIVATE DEFINES////////////////////////////////////////////
#define HMC5883_1_3GA_SCALE			0.92F

////////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////

Boolean calibration_hmc5883_done = FALSE;
double mag_calib_hmc5883_gain[ 3U ] = { 0, 0, 0 };
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpHMC5883Init(void)
{
	Boolean o_success = FALSE;
	calibration_hmc5883_done = FALSE;
	//scale 1.3G
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_CONFIG_B,HMC5883_1_3GA);
	
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_MODE,HMC5883_CONTINUOUS);
	DrvTickDelayMs(5);
	o_success = TRUE;
	return o_success;
}

Boolean CmpHMC5883Calibrate(void)
{
	if( calibration_hmc5883_done == FALSE )
	{		
		calibration_hmc5883_done = TRUE;
	}
	return TRUE;
}

//Mag X Y Z
Boolean CmpHMC5883GetHeading(S_Mag_Sensor *mag)
{	
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
	if(DrvTwiReadRegBuf(HMC5883_ADDRESS, HMC5883_X_MSB, buffer, 6U) != TRUE )
	{
		return FALSE;
	}
	else
	{
		mag->x = (Int16S)((float)(Int16S)((Int16U)(buffer[ 0U ] << 8U) | (Int16U)(buffer[ 1U ])) * (float)HMC5883_1_3GA_SCALE);
		mag->y = (Int16S)((float)(Int16S)((Int16U)(buffer[ 4U ] << 8U) | (Int16U)(buffer[ 5U ])) * (float)HMC5883_1_3GA_SCALE);
		mag->z = (Int16S)((float)(Int16S)((Int16U)(buffer[ 2U ] << 8U) | (Int16U)(buffer[ 3U ])) * (float)HMC5883_1_3GA_SCALE);
		
		return TRUE;
	}
}
