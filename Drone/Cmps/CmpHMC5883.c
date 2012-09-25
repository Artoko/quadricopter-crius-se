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
#define NB_SAMPLE_TO_CALIB_HMC5883 1U
////////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////
Int8U loop_calibration_hmc5883 = 0;
static Int8U mag_calib[3] = {0,0,0};

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpHMC5883Init(void)
{
	Boolean o_success = FALSE;
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_CONFIG_A,HMC5883_15HZ);
	DrvTimerDelay10Us(20);
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_CONFIG_B,HMC5883_1_3GA);
	DrvTimerDelay10Us(20);
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_MODE,HMC5883_CONTINUOUS);
	DrvTimerDelay10Us(20);
	loop_calibration_hmc5883 = NB_SAMPLE_TO_CALIB_HMC5883;
	DrvTimerDelay10Us(500);
	o_success = TRUE;
	return o_success;
}

Boolean CmpHMC5883IsCalibrate(void)
{
	if(loop_calibration_hmc5883 == 0)
	{
		return TRUE;
	}
	return FALSE;
}



//Mag X Y Z
Boolean CmpHMC5883GetHeading(S_Mag_Angle *mag)
{	
	Int8U buffer[ 6U ] = {0U, 0U, 0U, 0U, 0U, 0U};
	if(DrvTwiReadRegBuf(HMC5883_ADDRESS, HMC5883_X_MSB, buffer, 6U) != 6U)
	{
		return FALSE;
	}
	else
	{
		mag->x = (Int16S)((Int16U)(buffer[ 0U ] << 8U) | (Int16U)(buffer[ 1U ]));
		mag->y = (Int16S)((Int16U)(buffer[ 4U ] << 8U) | (Int16U)(buffer[ 5U ]));
		mag->z = (Int16S)((Int16U)(buffer[ 2U ] << 8U) | (Int16U)(buffer[ 3U ]));
		
		if(loop_calibration_hmc5883 > 0)
		{
			if( loop_calibration_hmc5883 == 1 )
			{
				mag_calib[0] = mag_calib[0] / NB_SAMPLE_TO_CALIB_HMC5883;
				mag_calib[1] = mag_calib[1] / NB_SAMPLE_TO_CALIB_HMC5883;
				mag_calib[2] = mag_calib[2] / NB_SAMPLE_TO_CALIB_HMC5883;
			}
			loop_calibration_hmc5883--;
		}
		else
		{
			mag->x -= mag_calib[0];
			mag->y -= mag_calib[1];
			mag->z -= mag_calib[2];
		}
		return TRUE;
	}
}
