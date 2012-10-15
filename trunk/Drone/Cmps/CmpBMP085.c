/*
 * BMP085.c
 *
 * Created: 03/07/2012 13:48:49
 *  Author: berryer
 */
/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "CmpBMP085.h"
 
#include "Drv/DrvTwi.h"
#include "Drv/DrvTick.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////

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
	} 
	ut; //uncompensated T
	union 
	{
		Int32U val;
		Int8U raw[4U];
	} 
	up; //uncompensated P
	Int8U  state;
	Int32U timeout;
} s_barometer;  

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
static void CmpBMP085ReadCalibration( void );
static void CmpBMP085Compute( void );
static void CmpBMP085StartUT( void ) ;
static void CmpBMP085ReadUT( void );
static void CmpBMP085StartUP( void ) ;
static void CmpBMP085ReadUP( void );

/////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Int32U pressure;
static Int32U BaroAlt;
static Int32U BaroAltmin;
static Int32U BaroAltmax;
static Boolean StartBaro;


//Initialisation du barometre
Boolean CmpBMP085Init( void )
{
	Boolean o_success = FALSE;
	StartBaro = FALSE;
	pressure = 0U;
	BaroAlt = 0U;
	BaroAltmin = 0U;
	BaroAltmax = 0U;
	//on laisse un delai pour l'init du barometre
	DrvTimerDelayMs(1000);
	CmpBMP085ReadCalibration();
	CmpBMP085StartUT();
	DrvTimerDelayMs(5);
	CmpBMP085ReadUT();
	o_success = TRUE;
	return o_success;
}

//
void CmpBMP085StartCapture( void )
{
	StartBaro = TRUE;
}

//Get altitude du barometre
Int16S CmpBMP085GetAltitude( void )
{	 
	CmpBMP085StateMachine();
	return BaroAlt;	
}	


//on update la temerature et la pression
void CmpBMP085StateMachine( void )
{
	if(StartBaro == TRUE)
	{
		Int32U currentTime = DrvTimerGetTime();
		if (currentTime >= s_barometer.timeout) 
		{	
			s_barometer.timeout = currentTime;
			switch (s_barometer.state)
			{
				case 0:
				{
					CmpBMP085StartUT();
					s_barometer.state++;
					s_barometer.timeout += 4600; //4.6 ms
					break;
				}
				case 1:
				{
					CmpBMP085ReadUT();
					s_barometer.state++;
					break;
				}
				case 2:
				{
					CmpBMP085StartUP();
					s_barometer.state++;
					s_barometer.timeout += 14000; //14 ms
					break;
				}
				case 3:
				{
					CmpBMP085ReadUP();
					CmpBMP085Compute();
					s_barometer.state = 0;
					BaroAlt = ((1.0f - pow(pressure/101325.0F, 0.190295F)) * 4433000.0F); //centimeter;
					StartBaro = FALSE;
				}
				break;
			}
		}	
	}	
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
  for (p = &s_barometer.ac1; p <= &s_barometer.md; p++) {
    swap_endianness(p, sizeof(*p));
  }
}

// read uncompensated temperature value: send command first
static void CmpBMP085StartUT( void ) 
{
	//read uncompensated temperature      
	DrvTwiWriteReg(BMP085_ADDRESS, CONTROL, READ_TEMPERATURE);
}	

// read uncompensated pressure value: send command first
static void CmpBMP085StartUP( void ) 
{
	DrvTwiWriteReg(BMP085_ADDRESS, CONTROL, READ_PRESSURE + ( OSS << 6U ) );
}

// read uncompensated pressure value: read result bytes
// the datasheet suggests a delay of 25.5 ms (oversampling settings 3) after the send command
static void CmpBMP085ReadUP( void ) 
{
	Int8U buffer[ 3U ] = {0U, 0U, 0U};
	DrvTwiReadRegBuf(BMP085_ADDRESS, CONTROL_OUTPUT, buffer, 3U);
	s_barometer.up.raw[2] = buffer[ 0U ];
	s_barometer.up.raw[1] = buffer[ 1U ];
	s_barometer.up.raw[0] = buffer[ 2U ];
}

// read uncompensated temperature value: read result bytes
// the datasheet suggests a delay of 4.5 ms after the send command
static void CmpBMP085ReadUT( void )
{
	Int8U buffer[ 2U ] = {0U, 0U};
	DrvTwiReadRegBuf(BMP085_ADDRESS, CONTROL_OUTPUT, buffer, 2U);
	s_barometer.ut.val = (Int16U)(buffer[ 0U ] << 8U | buffer[ 1U ]);
}

static void CmpBMP085Compute( void ) 
{
  int32_t  x1, x2, x3, b3, b5, b6, p, tmp;
  uint32_t b4, b7;
  // Temperature calculations
  x1 = ((int32_t)s_barometer.ut.val - s_barometer.ac6) * s_barometer.ac5 >> 15;
  x2 = ((int32_t)s_barometer.mc << 11) / (x1 + s_barometer.md);
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
  b4 = (s_barometer.ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t) (s_barometer.up.val >> (8-OSS)) - b3) * (50000 >> OSS);
  p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  pressure = p + ((x1 + x2 + 3791) >> 4);
  pression =pressure;
}



