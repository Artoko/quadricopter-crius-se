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

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_MAX_ALT_TAB			3
/////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////
static struct SS_BMP085
{
	Int16S  ac1, ac2, ac3;
	Int16U ac4, ac5, ac6;
	Int16S  b1, b2, mb, mc, md;
	union 
	{
		Int16U val;
		Int8U raw[2U]; 
	} ut; //uncompensated T
	union 
	{
		Int32U val;
		Int8U raw[4U];
	}up; //uncompensated P
	Int32U timeout;
	Boolean init;
} s_barometer;  

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CmpBMP085ReadCalibration( void ) ;
static void CmpBMP085Compute( void ) ;
static void CmpBMP085StartUT( void ) ;
static void CmpBMP085ReadUT( void ) ;
static void CmpBMP085StartUP( void ) ;
static void CmpBMP085ReadUP( void ) ;
static void CmpBMP085IsrCallbackReadUP( void) ;
static void CmpBMP085IsrCallbackReadUT( void) ;
/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int32U pressure;

static Int32U BaroAlt = 0U;
static Int8U baro_index;
static Int32U BaroAltTab[NB_MAX_ALT_TAB];



//Initialisation du barometre
Boolean CmpBMP085Init( void )
{
	Boolean o_success = FALSE;
	pressure = 0U;
	s_barometer.init = FALSE;
	CmpBMP085ReadCalibration();
	o_success = TRUE;
	return o_success;
}

//Get altitude du barometre
Int32U CmpBMP085GetAltitude( void )
{	 
	if(baro_index == NB_MAX_ALT_TAB)
	{
		for (Int8U loop = 0U; loop< NB_MAX_ALT_TAB ; loop++)
		{
			BaroAlt += BaroAltTab[ loop ];
			BaroAltTab[ loop ] = 0;
		}	
		BaroAlt = BaroAlt / (NB_MAX_ALT_TAB + 1);
		baro_index = 0;
	}	
	return BaroAlt;
}

//on start la capture du baro
void CmpBMP085StartCapture( void )
{ 
	if( s_barometer.init == TRUE )
	{
		CmpBMP085Compute();
		pression = pressure;
		if(baro_index < NB_MAX_ALT_TAB)
		{
			BaroAltTab[ baro_index ] = (1.0f - pow(pressure/101325.0f, 0.190295f)) * 443300.0f;;
			baro_index++;
		}
	}
	else
	{
		s_barometer.init = TRUE;
	}
	CmpBMP085StartUT();
	SrvTimerAddTimer(CONF_TIMER_START_BMP085, 45U, E_TIMER_MODE_ONE_SHOT, CmpBMP085IsrCallbackReadUT);
}

//fct appele par le timer
static void CmpBMP085IsrCallbackReadUT( void )
{
	CmpBMP085ReadUT();
	SrvTimerReloadTimer(CONF_TIMER_START_BMP085, 140U, E_TIMER_MODE_ONE_SHOT, CmpBMP085IsrCallbackReadUP);
	CmpBMP085StartUP();
}

//fct appele par le timer
static void CmpBMP085IsrCallbackReadUP( void)
{
	CmpBMP085ReadUP();
	SrvTimerStopTimer(CONF_TIMER_START_BMP085);
}	

//read all value
static void CmpBMP085ReadCalibration( void )
{
  DrvTimerDelayMs(10);
  //read calibration data in one go
  size_t s_bytes = (uint8_t*)&s_barometer.md - (uint8_t*)&s_barometer.ac1 + sizeof(s_barometer.ac1);
  DrvTwiReadRegBuf(BMP085_ADDRESS, CAL_AC1, &s_barometer.ac1, s_bytes);
  // now fix endianness
  int16_t *p;
  for (p = &s_barometer.ac1; p <= &s_barometer.md; p++)
  {
    swap_endianness(p, sizeof(*p));
  }
}

// read uncompensated temperature value: send command first
static void CmpBMP085StartUT( void ) 
{
	//read uncompensated temperature      
	DrvTwiWriteReg(BMP085_ADDRESS, CONTROL, READ_TEMPERATURE);
}	

// read uncompensated temperature value: read result bytes
static void CmpBMP085ReadUT( void )
{
	Int8U buffer[ 2U ] = {0U, 0U};
	DrvTwiReadRegBuf(BMP085_ADDRESS, CONTROL_OUTPUT, buffer, 2U);
	s_barometer.ut.raw[1] = buffer[ 0U ];
	s_barometer.ut.raw[0] = buffer[ 1U ];
}

// read uncompensated pressure value: send command first
static void CmpBMP085StartUP( void ) 
{
	DrvTwiWriteReg(BMP085_ADDRESS, CONTROL, READ_PRESSURE + ( OSS << 6U ) );
}

// read uncompensated pressure value: read result bytes
static void CmpBMP085ReadUP( void ) 
{
	Int8U buffer[ 3U ] = {0U, 0U, 0U};
	DrvTwiReadRegBuf(BMP085_ADDRESS, CONTROL_OUTPUT, buffer, 3U);
	s_barometer.up.raw[2] = buffer[ 0U ];
	s_barometer.up.raw[1] = buffer[ 1U ];
	s_barometer.up.raw[0] = buffer[ 2U ];
}

//on calcul la pression
static void CmpBMP085Compute( void ) 
{
  Int32S  x1, x2, x3, b3, b5, b6, p, tmp;
  Int32U b4, b7;
  // Temperature calculations
  x1 = ((Int32S)s_barometer.ut.val - s_barometer.ac6) * s_barometer.ac5 >> 15;
  x2 = ((Int32S)s_barometer.mc << 11) / (x1 + s_barometer.md);
  b5 = x1 + x2;
  temperature = (b5 + 8)>>4;
  // Pressure calculations
  b6 = b5 - 4000;
  x1 = (s_barometer.b2 * (b6 * b6 >> 12)) >> 11; 
  x2 = s_barometer.ac2 * b6 >> 11;
  x3 = x1 + x2;
  tmp = s_barometer.ac1;
  tmp = (tmp*4 + x3) << OSS;
  b3 = (tmp+2)/4;
  x1 = s_barometer.ac3 * b6 >> 13;
  x2 = (s_barometer.b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (s_barometer.ac4 * (Int32U)(x3 + 32768)) >> 15;
  b7 = ((Int32U) (s_barometer.up.val >> (8-OSS)) - b3) * (50000 >> OSS);
  p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  pressure = p + ((x1 + x2 + 3791) >> 4);
}


