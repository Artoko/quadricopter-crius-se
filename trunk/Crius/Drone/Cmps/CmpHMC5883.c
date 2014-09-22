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
#define HMC5883_1_3GA_SCALE			0.92

#define MAG0MAX 603
#define MAG0MIN -578
#define MAG1MAX 542
#define MAG1MIN -701
#define MAG2MAX 547
#define MAG2MIN -556
////////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////

Boolean calibration_hmc5883_done = FALSE;
float  mag_calib_hmc5883_offset[ 3U ] ={ (MAG0MAX + MAG0MIN) / 2, (MAG1MAX + MAG1MIN) / 2, (MAG2MAX + MAG2MIN) / 2 };
double mag_calib_hmc5883_gain[ 3U ] = { 0, 0, 0 };
////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpHMC5883Init(void)
{
	Boolean o_success = FALSE;
	calibration_hmc5883_done = FALSE;
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_MODE,HMC5883_CONTINUOUS);
	DrvTimerDelayMs(5);
	o_success = TRUE;
	return o_success;
}

Boolean CmpHMC5883Calibrate(void)
{
	if( calibration_hmc5883_done == FALSE )
	{
		S_Mag_Sensor magnetometer;
		DrvTwiWriteReg(HMC5883_ADDRESS, 0x00, 0x11);
		DrvTimerDelayMs(100); // Wait for sensor to get ready
		CmpHMC5883GetHeading(&magnetometer); // Read positive bias values

		int16_t magPosOff[3] = { magnetometer.x, magnetometer.y, magnetometer.z };

		DrvTwiWriteReg(HMC5883_ADDRESS, 0x00, 0x12);
		DrvTimerDelayMs(100); // Wait for sensor to get ready
		CmpHMC5883GetHeading(&magnetometer); // Read negative bias values

		int16_t magNegOff[3] = { magnetometer.x, magnetometer.y, magnetometer.z };

		DrvTwiWriteReg(HMC5883_ADDRESS, 0x00, 0x10); // Back to normal

		mag_calib_hmc5883_gain[0] = -2500 / (float)(magNegOff[0] - magPosOff[0]);
		mag_calib_hmc5883_gain[1] = -2500 / (float)(magNegOff[1] - magPosOff[1]);
		mag_calib_hmc5883_gain[2] = -2500 / (float)(magNegOff[2] - magPosOff[2]);
		
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
		mag->x = (Int16S)((Int16U)(buffer[ 0U ] << 8U) | (Int16U)(buffer[ 1U ]));
		mag->y = (Int16S)((Int16U)(buffer[ 4U ] << 8U) | (Int16U)(buffer[ 5U ]));
		mag->z = (Int16S)((Int16U)(buffer[ 2U ] << 8U) | (Int16U)(buffer[ 3U ]));
		
		if( calibration_hmc5883_done == TRUE )
		{
			mag->x *= mag_calib_hmc5883_gain[0];
			mag->y *= mag_calib_hmc5883_gain[1];
			mag->z *= mag_calib_hmc5883_gain[2];

			mag->x -= mag_calib_hmc5883_offset[0];
			mag->y -= mag_calib_hmc5883_offset[1];
			mag->z -= mag_calib_hmc5883_offset[2];
		}

		/*mag->x = mag->x * HMC5883_1_3GA_SCALE;
		mag->y = mag->y * HMC5883_1_3GA_SCALE;
		mag->z = mag->z * HMC5883_1_3GA_SCALE;*/
		
		return TRUE;
	}
}
