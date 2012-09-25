/*
 * BMA180.h
 *
 * Created: 03/07/2012 13:49:01
 *  Author: berryer
 */ 


#ifndef BMA180_H_
#define BMA180_H_


#include "Conf/conf_hard.h"

////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
#define BMA180_ADDRESS		0x40

#define BMA180_CHIP_ID		0x03

#define BMA180_ACC_1G		255

#define BMA180_REG_CHIP_ID		0x00
#define BMA180_REG_ACC_X_LSB	0x02
#define BMA180_REG_CTRL_REG0	0x0D
#define BMA180_REG_BW_TCS		0x20
#define BMA180_REG_TC0_Z		0x30
#define BMA180_REG_OFFSET_LSB1	0x35

////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct 
{
	Int16S x; 
	Int16S y; 
	Int16S z;
}S_Acc_Angle;

////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////



//fonction init du capteur
Boolean CmpBMA180Init(void);
//Acceleration X Y Z
Boolean CmpBMA180GetAcceleration(S_Acc_Angle *acc);
Boolean CmpBMA180IsCalibrate(void);

#endif /*BMA180_H_*/
