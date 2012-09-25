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

/////////////////////////////////////////////DEFINES///////////////////////////////////////////////

#define UPDATE_INTERVAL 25000    // 40hz update rate (20hz LPF on acc)
#define INIT_DELAY      4000000  // 4 sec initialization delay
#define BARO_TAB_SIZE   40

/////////////////////////////////////////PRIVATE STRUCTIURES///////////////////////////////////////
static struct SS_BMP085
{
	int16_t  ac1, ac2, ac3;
	uint16_t ac4, ac5, ac6;
	int16_t  b1, b2, mb, mc, md;
	union 
	{
		uint16_t val;
		uint8_t raw[2]; 
	} 
	ut; //uncompensated T
	union 
	{
		uint32_t val;
		uint8_t raw[4];
	} 
	up; //uncompensated P
	uint8_t  state;
	uint32_t deadline;
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

//Initialisation du barometre
Boolean CmpBMP085Init( void )
{
	Boolean o_success = FALSE;
	pressure = 0U;
	BaroAlt = 0U;
	DrvTimerDelayMs(10);
	CmpBMP085ReadCalibration();
	CmpBMP085StartUT();
	DrvTimerDelayMs(5);
	CmpBMP085ReadUT();
	o_success = TRUE;
	return o_success;
}

//on update la temerature et la pression
Int32U CmpBMP085Update( void )
{
	Int32U currentTime = DrvTimerGetTime();
	if (currentTime < s_barometer.deadline) 
	{
		return BaroAlt;
	}
	else
	{	
		s_barometer.deadline = currentTime;
		switch (s_barometer.state)
		{
			case 0:
			{
				CmpBMP085StartUT();
				s_barometer.state++;
				s_barometer.deadline += 460;
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
				s_barometer.deadline += 1400;
				break;
			}
			case 3:
			{
				CmpBMP085ReadUP();
				CmpBMP085Compute();
				BaroAlt = (1.0f - pow(pressure/101325.0f, 0.190295f)) * 4433000.0f; //centimeter
				s_barometer.state = 0;
				s_barometer.deadline += 500;
			}
			break;
		}
	}	
	return BaroAlt;
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
	pression = s_barometer.up.val/1000;
}

// read uncompensated temperature value: read result bytes
// the datasheet suggests a delay of 4.5 ms after the send command
static void CmpBMP085ReadUT( void )
{
	Int8U buffer[ 2U ] = {0U, 0U};
	DrvTwiReadRegBuf(BMP085_ADDRESS, CONTROL_OUTPUT, buffer, 2U);
	s_barometer.ut.raw[1] = buffer[ 0U ];
	s_barometer.ut.raw[0] = buffer[ 1U ];
	temperature = (Int16S)(s_barometer.ut.val/100);
}

static void CmpBMP085Compute( void ) 
{
  int32_t  x1, x2, x3, b3, b5, b6, p, tmp;
  uint32_t b4, b7;
  // Temperature calculations
  x1 = ((int32_t)s_barometer.ut.val - s_barometer.ac6) * s_barometer.ac5 >> 15;
  x2 = ((int32_t)s_barometer.mc << 11) / (x1 + s_barometer.md);
  b5 = x1 + x2;
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
}



