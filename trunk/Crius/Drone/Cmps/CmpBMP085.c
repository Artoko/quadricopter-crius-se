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
#define NB_MAX_ALT_TAB			10U

#define STEP_READ_UT			0U
#define STEP_READ_UP			1U
#define STEP_COMPUTE			2U
#define STEP_NONE				3U
/////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////
struct SS_BMP085
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
} s_barometer;  

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CmpBMP085ReadCalibration( void ) ;
static void CmpBMP085Compute( void ) ;
static void CmpBMP085StartUT( void ) ;
static void CmpBMP085CallbackUT( void ) ;
static void CmpBMP085ReadUT( void ) ;
static void CmpBMP085StartUP( void ) ;
static void CmpBMP085CallbackUP( void ) ;
static void CmpBMP085ReadUP( void ) ;
/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int32U pressure;

static Int32U BaroAlt = 0U;
static Int8U baro_index;
static Int32U BaroAltTab[NB_MAX_ALT_TAB];


static Int8U step_baro = STEP_NONE;


//Initialisation du barometre
Boolean CmpBMP085Init( void )
{
	Boolean o_success = FALSE;
	pressure = 0U;
	CmpBMP085ReadCalibration();
	o_success = TRUE;
	return o_success;
}

//Get altitude du barometre
Int32U CmpBMP085GetAltitude( void )
{
	return BaroAlt;
}	

void CmpBMP085ComputeAltitude( void )
{	
	if( step_baro == STEP_READ_UT )
	{
		CmpBMP085ReadUT();
		CmpBMP085StartUP();		
		step_baro = STEP_NONE;
	}
	else if( step_baro == STEP_READ_UP )
	{
		CmpBMP085ReadUP();
		step_baro = STEP_COMPUTE;
	}
	else if( step_baro == STEP_COMPUTE )
	{
		CmpBMP085Compute();
		pression = pressure;
		BaroAlt = (Int32U)((1.0f - pow(pressure/101325.0f, 0.190295f)) * 443300.0f);
		step_baro = STEP_NONE;
		/*Int8U loop = 0 ;
		for( loop = 0 ; loop < (NB_MAX_ALT_TAB - 1U) ; loop++ )
		{
			BaroAltTab[ loop ] = BaroAltTab[ loop + 1U ];	
		}
		
		BaroAltTab[ NB_MAX_ALT_TAB - 1U ] = BaroAlt;
		
		for( loop = 0 ; loop < NB_MAX_ALT_TAB ; loop++ )
		{
			BaroAlt	+= BaroAltTab[ loop ];
		}	
	    BaroAlt	/= NB_MAX_ALT_TAB;*/
	}
	else
	{
		//		
	}		
}

//on start la capture du baro
void CmpBMP085StartCapture( void )
{ 
	CmpBMP085StartUT();
	SrvTimerAddTimer( CONF_TIMER_BMP085 , 5U, E_TIMER_MODE_ONE_SHOT, CmpBMP085CallbackUT);
}

//callback timer 
static void CmpBMP085CallbackUT( void ) 
{
	step_baro = STEP_READ_UT;
	SrvTimerAddTimer( CONF_TIMER_BMP085 , 15U, E_TIMER_MODE_ONE_SHOT, CmpBMP085CallbackUP);
}

//callback timer
static void CmpBMP085CallbackUP( void )
{
	step_baro = STEP_READ_UP;
	SrvTimerStopTimer( CONF_TIMER_BMP085 );
}

//read all value
static void CmpBMP085ReadCalibration( void )
{
  //read calibration data in one go
  size_t s_bytes = (Int8U*)&s_barometer.md - (Int8U*)&s_barometer.ac1 + sizeof(s_barometer.ac1);
  DrvTwiReadRegBuf(BMP085_ADDRESS, CAL_AC1, &s_barometer.ac1, s_bytes);
  // now fix endianness
  Int16S *p;
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
  x1 = ((Int32S)s_barometer.ut.val - s_barometer.ac6) * s_barometer.ac5 >> 15U;
  x2 = ((Int32S)s_barometer.mc << 11U) / (x1 + s_barometer.md);
  b5 = x1 + x2;
  temperature = (b5 + 8U)>>4U;
  // Pressure calculations
  b6 = b5 - 4000U;
  x1 = (s_barometer.b2 * (b6 * b6 >> 12)) >> 11U; 
  x2 = s_barometer.ac2 * b6 >> 11U;
  x3 = x1 + x2;
  tmp = s_barometer.ac1;
  tmp = (tmp*4U + x3) << OSS;
  b3 = (tmp+2U)/4U;
  x1 = s_barometer.ac3 * b6 >> 13U;
  x2 = (s_barometer.b1 * (b6 * b6 >> 12U)) >> 16U;
  x3 = ((x1 + x2) + 2U) >> 2U;
  b4 = (s_barometer.ac4 * (Int32U)(x3 + 32768U)) >> 15U;
  b7 = ((Int32U) (s_barometer.up.val >> (8U-OSS)) - b3) * (50000U >> OSS);
  p = b7 < 0x80000000 ? (b7 * 2U) / b4 : (b7 / b4) * 2U;
  x1 = (p >> 8U) * (p >> 8U);
  x1 = (x1 * 3038U) >> 16U;
  x2 = (-7357 * p) >> 16U;
  pressure = p + ((x1 + x2 + 3791U) >> 4U);
}


