/*
 * CmpL3G4200D.h
 *
 * Created: 03/07/2012 13:49:01
 *  Author: berryer
 */ 


#ifndef CMPL3G4200D_H_
#define CMPL3G4200D_H_



#include "Tools/tools_typedefs.h"

////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////*
#define L3G4200D_ADDRESS				0x68

// Register Address Map
#define L3G4200D_WHO_AM_I				0x0F
#define L3G4200D_CTRL_REG1              0x20
#define L3G4200D_CTRL_REG2              0x21
#define L3G4200D_CTRL_REG3              0x22
#define L3G4200D_CTRL_REG4              0x23
#define L3G4200D_CTRL_REG5              0x24
#define L3G4200D_STATUS_REG             0x27
#define L3G4200D_OUT_X_L                0x28
#define L3G4200D_OUT_X_H                0x29
#define L3G4200D_OUT_Y_L                0x2A
#define L3G4200D_OUT_Y_H                0x2B
#define L3G4200D_OUT_Z_L                0x2C
#define L3G4200D_OUT_Z_H                0x2D

// The register addresses are all 0x7F masked
// For multibyte read/write the address can be set to auto increment via the MSB
#define L3G4200D_AUTO_INCREMENT         0x80

//CTRL_REG1: Data rates
#define L3G4200D_DR_100HZ		0x00
#define L3G4200D_DR_200HZ		0x40
#define L3G4200D_DR_400HZ		0x80
#define L3G4200D_DR_800HZ		0xC0
//CTRL_REG1: Enables
#define L3G4200D_PD			0x08
#define L3G4200D_ZEN			0x04
#define L3G4200D_YEN 			0x02
#define L3G4200D_XEN			0x01
//CTRL_REG3: Interrupts
#define L3G4200D_H_LACTIVE 		0x20
#define L3G4200D_I2_DRDY		0x08
//CTRL_REG4: Scale
#define L3G4200D_FS_250DPS		0x00
#define L3G4200D_FS_500DPS		0x10
#define L3G4200D_FS_2000DPS		0x30
//STATUS_REG
#define L3G4200D_ZYXDA			0x08
#define L3G4200D_ZYXOR			0x80

#define L3G4200D_WHO_I_AM					0xD3
//#define L3G4200D_CTRL_REG1_400HZ_50LPF		0xAF
#define L3G4200D_CTRL_REG1_400HZ_50LPF		0x8F
#define L3G4200D_CTRL_REG2_NO_HI_PASS		0x20
#define L3G4200D_CTRL_REG3_NO_INTERRUPT		0x00
#define L3G4200D_CTRL_REG4_DEFAULT			0x00
#define L3G4200D_CTRL_REG5_DISABLE_LPF2		0x00
#define L3G4200D_CTRL_REG5_ENABLE_LPF2		0x02

////////////////////////////////////////PUBLIC STRUCTURES////////////////////////////////////////
typedef struct 
{
	Int16S x; 
	Int16S y; 
	Int16S z;
}S_Gyr_Angle;

////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////

//fonction init du capteur
Boolean CmpL3G4200DInit(void);
//Rotation X Y Z
Boolean CmpL3G4200DGetRotation(S_Gyr_Angle *rot);

#endif /*CMPL3G4200D_H_*/
