/*
 * HMC5883.h
 *
 * Created: 03/07/2012 13:49:01
 *  Author: berryer
 */ 


#ifndef HMC5883_H_
#define HMC5883_H_


#include "Conf/conf_hard.h"

////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////

#define LOCAL_MAGNETIC_DECLINAISON		0.01774

#define HMC5883_ADDRESS			0x1E

//Values Config A
#define HMC5883_15HZ			0x70

//Values Config B
#define HMC5883_1_3GA			0x20

//Values MODE
#define HMC5883_CONTINUOUS   0x00
#define HMC5883_SINGLE	     0x01

#define HMC5883_CONFIG_A     0x00
#define HMC5883_CONFIG_B     0x01
#define HMC5883_MODE         0x02
#define HMC5883_X_MSB        0x03
#define HMC5883_X_LSB        0x04
#define HMC5883_Z_MSB        0x05
#define HMC5883_Z_LSB        0x06
#define HMC5883_Y_MSB        0x07
#define HMC5883_Y_LSB        0x08
#define HMC5883_STATUS       0x09
#define HMC5883_IDENT_A      0x0A
#define HMC5883_IDENT_B      0x0B
#define HMC5883_IDENT_C      0x0C

////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////

////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpHMC5883Init(void);
//mag X Y Z
Boolean CmpHMC5883GetHeading(S_Mag_Sensor *mag);
Boolean CmpHMC5883Calibrate(void);
#endif /*BMA180_H_*/
