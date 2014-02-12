////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#include "Conf\conf_hard.h"

#include "DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define ADDR_EEPROM_CHECK_EEPROM	( Int8U *)0U
#define ADDR_EEPROM_ACC_CALIB_X		( Int8U *)1U
#define ADDR_EEPROM_ACC_CALIB_Y		( Int8U *)3U
#define ADDR_EEPROM_ACC_CALIB_Z		( Int8U *)5U
#define ADDR_EEPROM_GYRO_CALIB_X	( Int8U *)7U
#define ADDR_EEPROM_GYRO_CALIB_Y	( Int8U *)9U
#define ADDR_EEPROM_GYRO_CALIB_Z	( Int8U *)11U
#define ADDR_EEPROM_PID_X_P			( Int8U *)13U
#define ADDR_EEPROM_PID_X_I			( Int8U *)17U
#define ADDR_EEPROM_PID_X_D			( Int8U *)21U
#define ADDR_EEPROM_PID_Y_P			( Int8U *)25U
#define ADDR_EEPROM_PID_Y_I			( Int8U *)29U
#define ADDR_EEPROM_PID_Y_D			( Int8U *)33U
#define ADDR_EEPROM_PID_Z_P			( Int8U *)37U
#define ADDR_EEPROM_PID_Z_I			( Int8U *)41U
#define ADDR_EEPROM_PID_Z_D			( Int8U *)45U
#define ADDR_EEPROM_PID_ALT_P		( Int8U *)49U
#define ADDR_EEPROM_PID_ALT_I		( Int8U *)53U
#define ADDR_EEPROM_PID_ALT_D		( Int8U *)57U
#define ADDR_EEPROM_ALTITUDE		( Int8U *)60U


#define VAL_EEPROM_CHECK_OK			0U
#define VAL_EEPROM_CHECK_NOK		0xFFU

////////////////////////////////////////PRIVATE STRUCTURES////////////////////////////////////////

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//Fonction de lecture eeprom
static Int8U DrvEepromReadByte ( const Int8U * addr );
//Fonction d ecriture eeprom
static void DrvEepromWriteByte ( Int8U * addr, Int8U byte);
//Fonction de lecture eeprom
static Int16U DrvEepromReadShort( const Int8U * addr );
//Fonction d ecriture eeprom
static void DrvEepromWriteShort ( Int8U *addr, Int16U byte);
//Fonction de lecture eeprom
static float DrvEepromReadFloat( const Int8U * addr );
//enregistre les config du pid
static void DrvEepromWriteFloat ( Int8U *addr, float value);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Boolean eeprom_is_configured = FALSE;
static Int8U val = 0U;

////////////////////////////////////////PUBILC FUNCTIONS//////////////////////////////////////////
//Fonction d'initialisation
//return : TRUE si ok
Boolean DrvEepromInit ( void )
{
	Boolean o_success = FALSE;
	
	val = DrvEepromReadByte( ADDR_EEPROM_CHECK_EEPROM );
	if( val == VAL_EEPROM_CHECK_OK )
	{
		eeprom_is_configured = TRUE;
		//eeprom_is_configured = FALSE;
		o_success = TRUE;	
	}
	else
	{
		eeprom_is_configured = FALSE;
	}
	return o_success;
}

//ecrit l'etat de config de l'eeprom
void DrvEepromDeconfigure ( void )
{	
	for(Int16U loop=0 ; loop < 1024 ; loop++)
	{
		DrvEepromWriteByte(( Int8U *)loop,VAL_EEPROM_CHECK_NOK);
	}
}

//ecrit l'etat de config de l'eeprom
void DrvEepromConfigure ( void )
{
	DrvEepromWriteByte(ADDR_EEPROM_CHECK_EEPROM,VAL_EEPROM_CHECK_OK);
}

//retourne l'etat de config de l'eeprom
Boolean DrvEepromIsConfigured ( void )
{
	return eeprom_is_configured;
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

//retourne les config du pid
void DrvEepromReadPID(Int8U index,float *P, float *I, float *D)
{
	if( index == 0 )
	{
		*P = DrvEepromReadFloat(ADDR_EEPROM_PID_X_P);
		*I = DrvEepromReadFloat(ADDR_EEPROM_PID_X_I);
		*D = DrvEepromReadFloat(ADDR_EEPROM_PID_X_D);
	}
	else if( index == 1 )
	{
		*P = DrvEepromReadFloat(ADDR_EEPROM_PID_Y_P);
		*I = DrvEepromReadFloat(ADDR_EEPROM_PID_Y_I);
		*D = DrvEepromReadFloat(ADDR_EEPROM_PID_Y_D);
	}
	else if( index == 2 )
	{
		*P = DrvEepromReadFloat(ADDR_EEPROM_PID_Z_P);
		*I = DrvEepromReadFloat(ADDR_EEPROM_PID_Z_I);
		*D = DrvEepromReadFloat(ADDR_EEPROM_PID_Z_D);
	}
	else if( index == 3 )
	{
		*P = DrvEepromReadFloat(ADDR_EEPROM_PID_ALT_P);
		*I = DrvEepromReadFloat(ADDR_EEPROM_PID_ALT_I);
		*D = DrvEepromReadFloat(ADDR_EEPROM_PID_ALT_D);
	}
}

//enregistre les config du pid
void DrvEepromWritePID (Int8U index,float P, float I, float D)
{
	if( index == 0 )
	{
		DrvEepromWriteFloat(ADDR_EEPROM_PID_X_P, P);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_X_I, I);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_X_D, D);
	}
	else if( index == 1 )
	{
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Y_P, P);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Y_I, I);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Y_D, D);
	}
	else if( index == 2 )
	{
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Z_P, P);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Z_I, I);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_Z_D, D);
	}
	else if( index == 3 )
	{
		DrvEepromWriteFloat(ADDR_EEPROM_PID_ALT_P, P);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_ALT_I, I);
		DrvEepromWriteFloat(ADDR_EEPROM_PID_ALT_D, D);
	}
}


//retourne les config du altitude
void DrvEepromReadAltitude( Int16U *altitude)
{
	*altitude = DrvEepromReadShort(ADDR_EEPROM_ALTITUDE);
}

//enregistre les config du altitude
void DrvEepromWriteAltitude ( Int16U altitude)
{
	DrvEepromWriteShort(ADDR_EEPROM_ALTITUDE, altitude);
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//Fonction de lecture eeprom
static Int8U DrvEepromReadByte ( const Int8U * addr )
{
	return eeprom_read_byte(addr);
}

//Fonction d ecriture eeprom
static void DrvEepromWriteByte ( Int8U * addr, Int8U byte)
{
	eeprom_write_byte(addr,byte);
}

//Fonction de lecture eeprom
static Int16U DrvEepromReadShort( const Int8U * addr )
{
	Int16U ret = 0;
	ret = eeprom_read_byte(addr) ;
	ret = ret << 8U ;
	ret |= eeprom_read_byte((addr + 1));
	return ret;
}
	
//Fonction d ecriture eeprom
static void DrvEepromWriteShort ( Int8U *addr, Int16U byte)
{
	eeprom_write_byte((addr), (Int8U)(byte >> 8U) );
	eeprom_write_byte((addr + 1) ,(Int8U)(byte));
}

//Fonction de lecture eeprom
static float DrvEepromReadFloat( const Int8U * addr )
{
	return eeprom_read_float((float*)addr);
}
	
//Fonction d ecriture eeprom
static void DrvEepromWriteFloat ( Int8U *addr, float value)
{
	eeprom_write_float((float*)(addr), value );
}
