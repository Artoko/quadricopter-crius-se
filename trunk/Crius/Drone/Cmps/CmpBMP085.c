/*
 * BMP085.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpBMP085.h"
 
 
#include "Srv/SrvTimer.h"
 
#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define SEA_PRESSURE	101325.0F
/////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////
Int16S ac1;
Int16S ac2;
Int16S ac3;
Int16U ac4;
Int16U ac5;
Int16U ac6;
Int16S b1;
Int16S b2;
Int16S mb;
Int16S mc;
Int16S md;
Int32S b5;  


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CmpBMP085ReadCalibration( void ) ;
static void CmpBMP085ReadUTReadUP( void ) ;
static Int16U CmpBMP085ReadUT ( void ) ;
static Int32U CmpBMP085ReadUP ( void ) ;
/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
Int16S temperature = 0;
Int32U pression = 0;
Int8U step_bmp085 = 0;
Int16U m_ut = 0;
Int32U m_up = 0;


//Initialisation du barometre
Boolean CmpBMP085Init( void )
{
	Boolean o_success = FALSE;
	CmpBMP085ReadCalibration();
	CmpBMP085LaunchReading();
	o_success = TRUE;
	return o_success;
}

//Get Altitude
Int16U CmpBMP085GetAltitude(float pressure)
{
	float A = pressure/101325.0;
	float B = 1.0/5.25588;
	float C = pow(A,B);
	C = 1 - C;
	C = C / 0.0000225577;
	return (Int16U)C;
}

//Get weather 
Int8U CmpBMP085GetWeather( float pressure , Int16U altitude )
{	
	static float ePressure = 0;
	// calcul de la presion attendu a notre altitude
	ePressure = SEA_PRESSURE * pow((1-altitude/44330.0), 5.255);
	// on compare par rapport a la pression mesurée
	Int16S weatherDiff = (Int16S)( (pressure / 10.0) - (ePressure / 10.0) );
	//on retourne le type de temps
	if(weatherDiff > 25)
	{
		return (Int8U)WEATHER_SUNNY;
	}
	else if ((weatherDiff <= 25) && (weatherDiff >= -25))
	{
		return (Int8U)WEATHER_CLOUDY;
	}
	else
	{
		return (Int8U)WEATHER_RAIN;
	}
}

//lance la lecture des variables du BMP085
 void CmpBMP085LaunchReading( void )
 {
	 CmpBMP085ReadUTReadUP();
 }

//Get Temperature
float CmpBMP085GetTemperature( void )
{
	return temperature;
}

//Get Pressure
Int32S CmpBMP085GetPressure( void )
{	
	return pression;
}



////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//read all value
static void CmpBMP085ReadCalibration( void )
{
  //read calibration
  Int8U datum = 0U;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC1, &datum );
  ac1 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC1 + 1, &datum );
  ac1 |= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC2, &datum );
  ac2 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC2 + 1, &datum );
  ac2 |= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC3, &datum );
  ac3 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC3 + 1, &datum );
  ac3 |= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC4, &datum );
  ac4 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC4 + 1, &datum );
  ac4 |= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC5, &datum );
  ac5 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC5 + 1, &datum );
  ac5 |= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC6, &datum );
  ac6 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_AC6 + 1, &datum );
  ac6|= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_B1, &datum );
  b1 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_B1 + 1, &datum );
  b1|= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_B2, &datum );
  b2 = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_B2 + 1, &datum );
  b2|= datum;
  
  b5 = 0;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MB, &datum );
  mb = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MB + 1, &datum );
  mb|= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MC, &datum );
  mc = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MC + 1, &datum );
  mc|= datum;
  
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MD, &datum );
  md = datum << 8;
  DrvTwiReadReg( BMP085_ADDRESS, CAL_MD + 1, &datum );
  md|= datum;
}

//read the two parameters UT and UP
static void CmpBMP085ReadUTReadUP( void ) 
{
	Int32S x1, x2, x3, b3, b6, p ;
	Int32U b4, b7;
	Int8U msb, lsb, xlsb;
	
	switch ( step_bmp085 )
	{
		case 0:
			CmpBMP085ReadUT();
			step_bmp085++;
		break;
		
		case 1:		
		
			// Read two uint8_ts from registers 0xF6 and 0xF7
			DrvTwiReadReg( BMP085_ADDRESS, CONTROL_OUTPUT, &msb );
			DrvTwiReadReg( BMP085_ADDRESS, CONTROL_OUTPUT + 1, &lsb );
			m_ut = (Int16U)(((Int16U) msb << 8) | ((Int16U)lsb) );
		
			x1 = (((Int32S)m_ut - (Int32S)ac6)*(Int32S)ac5) >> 15;
			x2 = ((Int32S)mc << 11)/(x1 + md);
			b5 = x1 + x2;
			
			float temp = ((b5 + 8)>>4);
			temp = temp / 10 - 1.5;
			
			temperature = (Int16S) temp ;
			CmpBMP085ReadUP();
			step_bmp085++;
		break;
		
		case 2:
		
			// Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
			DrvTwiReadReg( BMP085_ADDRESS, CONTROL_OUTPUT, &msb );
			DrvTwiReadReg( BMP085_ADDRESS, CONTROL_OUTPUT + 1, &lsb );
			DrvTwiReadReg( BMP085_ADDRESS, CONTROL_OUTPUT + 2, &xlsb );
		
			m_up = (((Int32U) msb << 16) | ((Int32U) lsb << 8) | (Int32U) xlsb) >> (8-OSS);
		
			b6 = b5 - 4000;
			// Calculate B3
			x1 = (b2 * (b6 * b6)>>12)>>11;
			x2 = (ac2 * b6)>>11;
			x3 = x1 + x2;
			b3 = (((((Int32S)ac1)*4 + x3)<<OSS) + 2)>>2;
		
			// Calculate B4
			x1 = (ac3 * b6)>>13;
			x2 = (b1 * ((b6 * b6)>>12))>>16;
			x3 = ((x1 + x2) + 2)>>2;
			b4 = (ac4 * (Int32U)(x3 + 32768))>>15;
		
			b7 = ((Int32U)(m_up - b3) * (50000>>OSS));
			if (b7 < 0x80000000)
			p = (b7<<1)/b4;
			else
			p = (b7/b4)<<1;
		
			x1 = (p>>8) * (p>>8);
			x1 = (x1 * 3038)>>16;
			x2 = (-7357 * p)>>16;
			p += (x1 + x2 + 3791)>>4;
			
			pression = p;
			
			//on reboucle
			step_bmp085 = 0;
		break;
		
	}
	
	
	
}

// Read the uncompensated temperature value
static Int16U CmpBMP085ReadUT ( void )
{
	// This requests a temperature reading
	DrvTwiWriteReg( BMP085_ADDRESS, CONTROL, READ_TEMPERATURE );
	
	// Wait at least 4.5ms
	return m_ut;
}

// Read the uncompensated pressure value
static Int32U CmpBMP085ReadUP ( void )
{
	// Write 0x34+(OSS<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	DrvTwiWriteReg( BMP085_ADDRESS, CONTROL, READ_PRESSURE + (OSS<<6) );
		
	// Wait for conversion, delay time dependent on OSS
	return m_up;
}
