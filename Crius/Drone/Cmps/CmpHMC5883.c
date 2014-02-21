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
////////////////////////////////////////PRIVATE VARIABLES//////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpHMC5883Init(void)
{
	Boolean o_success = FALSE;
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_CONFIG_B,HMC5883_1_3GA);
	DrvTimerDelayUs(200);
	DrvTwiWriteReg(HMC5883_ADDRESS,HMC5883_MODE,HMC5883_CONTINUOUS);
	DrvTimerDelayMs(5);
	o_success = TRUE;
	return o_success;
}



//Mag X Y Z
Boolean CmpHMC5883GetHeading(S_Mag_Angle *mag)
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
		mag->x = mag->x * HMC5883_1_3GA_SCALE;
		mag->y = mag->y * HMC5883_1_3GA_SCALE;
		mag->z = mag->z * HMC5883_1_3GA_SCALE;
		
		return TRUE;
	}
}
