////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"

#include "DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define ADDR_EEPROM_CHECK_EEPROM	0U
#define ADDR_EEPROM_ACC_CALIB_X		1U
#define ADDR_EEPROM_ACC_CALIB_Y		3U
#define ADDR_EEPROM_ACC_CALIB_Z		5U
#define ADDR_EEPROM_GYRO_CALIB_X	7U
#define ADDR_EEPROM_GYRO_CALIB_Y	9U
#define ADDR_EEPROM_GYRO_CALIB_Z	11U


#define VAL_EEPROM_CHECK_OK			0U
#define VAL_EEPROM_CHECK_NOK		0xFFU

////////////////////////////////////////PRIVATE STRUCTURES////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//Fonction de lecture eeprom
static Int8U DrvEepromReadByte ( Int8U addr );
//Fonction d ecriture eeprom
static void DrvEepromWriteByte ( Int8U addr, Int8U byte);
//Fonction de lecture eeprom
static Int16U DrvEepromReadShort( Int8U addr );
//Fonction d ecriture eeprom
static void DrvEepromWriteShort ( Int8U addr, Int16U byte);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Boolean eeprom_est_configure;

////////////////////////////////////////PUBILC FUNCTIONS//////////////////////////////////////////
//Fonction d'initialisation
//return : TRUE si ok
Boolean DrvEepromInit ( void )
{
	Boolean o_success = FALSE;
	Int8U val = DrvEepromReadByte(ADDR_EEPROM_CHECK_EEPROM);
	if( val == VAL_EEPROM_CHECK_OK )
	{
		eeprom_est_configure = TRUE;
		o_success = TRUE;	
	}
	else
	{
		eeprom_est_configure = FALSE;
	}
	return o_success;
}

//ecrit l'etat de config de l'eeprom
void DrvEepromConfigure ( void )
{
	DrvEepromWriteByte(ADDR_EEPROM_CHECK_EEPROM,VAL_EEPROM_CHECK_OK);
}

//retourne l'etat de config de l'eeprom
Boolean DrvEepromIsConfigured ( void )
{
	return eeprom_est_configure;
}

//retourne les config de l'accelerometre
void DrvEepromReadAcc ( Int16S calib[ 3U ] )
{
	calib[ 0U ] = DrvEepromReadShort(ADDR_EEPROM_ACC_CALIB_X);
	calib[ 1U ] = DrvEepromReadShort(ADDR_EEPROM_ACC_CALIB_Y);
	calib[ 2U ] = DrvEepromReadShort(ADDR_EEPROM_ACC_CALIB_Z);
}

//enregistre les config de l'accelerometre
void DrvEepromWriteAcc ( Int16S calib[ 3U ] )
{
	DrvEepromWriteShort(ADDR_EEPROM_ACC_CALIB_X,calib[ 0U ]);
	DrvEepromWriteShort(ADDR_EEPROM_ACC_CALIB_Y,calib[ 1U ]);
	DrvEepromWriteShort(ADDR_EEPROM_ACC_CALIB_Z,calib[ 2U ]);
}

//retourne les config du gyroscope
void DrvEepromReadGyro ( Int16S calib[ 3U ] )
{
	calib[ 0U ] = DrvEepromReadShort(ADDR_EEPROM_GYRO_CALIB_X);
	calib[ 1U ] = DrvEepromReadShort(ADDR_EEPROM_GYRO_CALIB_Y);
	calib[ 2U ] = DrvEepromReadShort(ADDR_EEPROM_GYRO_CALIB_Z);
}

//enregistre les config du gyroscope
void DrvEepromWriteGyro ( Int16S calib[ 3U ] )
{
	DrvEepromWriteShort(ADDR_EEPROM_GYRO_CALIB_X,calib[ 0U ]);
	DrvEepromWriteShort(ADDR_EEPROM_GYRO_CALIB_Y,calib[ 1U ]);
	DrvEepromWriteShort(ADDR_EEPROM_GYRO_CALIB_Z,calib[ 2U ]);
}

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//Fonction de lecture eeprom
static Int8U DrvEepromReadByte ( Int8U addr )
{
	return eeprom_read_byte((Int8U*)addr);
}

//Fonction d ecriture eeprom
static void DrvEepromWriteByte ( Int8U addr, Int8U byte)
{
	eeprom_write_byte((Int8U*)addr,byte);
}

//Fonction de lecture eeprom
static Int16U DrvEepromReadShort( Int8U addr )
{
	Int16U ret = 0;
	ret = eeprom_read_byte((Int8U*)addr) ;
	ret = ret << 8U ;
	ret |= eeprom_read_byte((Int8U*)(addr + 1));
	return ret;
}
	
//Fonction d ecriture eeprom
static void DrvEepromWriteShort ( Int8U addr, Int16U byte)
{
	eeprom_write_byte((Int8U*)(addr), (Int8U)(byte >> 8U) );
	eeprom_write_byte((Int8U*)(addr + 1) ,(Int8U)(byte));
}
