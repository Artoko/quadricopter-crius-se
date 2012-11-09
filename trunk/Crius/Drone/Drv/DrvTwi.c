/*
 * DrvTwi.c
 *
 * Created: 26/04/2012 14:32:07
 *  Author: berryer
 */ 



#include "Conf\conf_hard.h"
#include "util\twi.h"
#include "DrvTwi.h"


uint8_t rawADC[6];

void WaitTransmissionI2C(void);

void DrvTwiInit(void) 
{
  TWSR = 0;                                    // no prescaler => prescaler = 1
  TWBR = ((CONF_FOSC_HZ / 400000) - 16) / 2;   // change the I2C clock rate
  TWCR = 1<<TWEN;                              // enable twi module, no interrupt
}

void DrvTwiRepStart(uint8_t address) 
{
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; // send REPEAT START condition
  WaitTransmissionI2C();                       // wait until transmission completed
  TWDR = address;                              // send device address
  TWCR = (1<<TWINT) | (1<<TWEN);
  WaitTransmissionI2C();                       // wail until transmission completed
}

void DrvTwiStop(void) 
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  //  while(TWCR & (1<<TWSTO));                // <- can produce a blocking state with some WMP clones
}

void DrvTwiWrite(uint8_t data ) 
{	
  TWDR = data;                                 // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  WaitTransmissionI2C();
}

uint8_t DrvTwiRead(uint8_t ack) 
{
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);
  WaitTransmissionI2C();
  uint8_t r = TWDR;
  if (!ack) DrvTwiStop();
  return r;
}

uint8_t DrvTwiReadAck() 
{
  return DrvTwiRead(1);
}

uint8_t DrvTwireadNak(void) 
{
  return DrvTwiRead(0);
}

void WaitTransmissionI2C() 
{
  uint16_t count = 255;
  while (!(TWCR & (1<<TWINT))) {
    count--;
    if (count==0) {              //we are in a blocking state => we don't insist
      TWCR = 0;                  //and we force a reset on TWINT register
      break;
    }
  }
}

Int8U DrvTwiReadToBuf(uint8_t add, void *buf, Int8U size) 
{
  DrvTwiRepStart((add<<1) | 1);	// I2C read direction
  Int8U bytes_read = 0;
  uint8_t *b = (uint8_t*)buf;
  while (size--) {
    /* acknowledge all but the final byte */
    *b++ = DrvTwiRead(size > 0);
    /* TODO catch I2C errors here and abort */
    bytes_read++;
  }
  return bytes_read;
}

Int8U DrvTwiReadRegBuf(uint8_t add, uint8_t reg, void *buf, Int8U size) 
{
  DrvTwiRepStart(add<<1); // I2C write direction
  DrvTwiWrite(reg);        // register selection
  return DrvTwiReadToBuf(add, buf, size);
}




void DrvTwiWriteReg(uint8_t add, uint8_t reg, uint8_t val)
 {
  DrvTwiRepStart(add<<1); // I2C write direction
  DrvTwiWrite(reg);        // register selection
  DrvTwiWrite(val);        // value to write in register
  DrvTwiStop();
}

uint8_t DrvTwiReadReg(uint8_t add, uint8_t reg)
 {
  uint8_t val;
  DrvTwiReadRegBuf(add, reg, &val, 1);
  return val;
}