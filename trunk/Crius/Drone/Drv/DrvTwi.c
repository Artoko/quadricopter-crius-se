/*
 * DrvTwi.c
 *
 * Created: 26/04/2012 14:32:07
 *  Author: berryer
 */ 



#include "Conf\conf_hard.h"
#include "util\twi.h"
#include "DrvTwi.h"


void WaitTransmissionI2C(void);

void DrvTwiInit( Int16U speed ) 
{
  TWSR = 0;                                    // no prescaler => prescaler = 1
  TWBR = ((CONF_FOSC_HZ / (speed * 1000) ) - 16) / 2;   // change the I2C clock rate
  TWCR = 1<<TWEN;                              // enable twi module, no interrupt
}

void DrvTwiRepStart(Int8U address) 
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

void DrvTwiWrite(Int8U data ) 
{	
  TWDR = data;                                 // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  WaitTransmissionI2C();
}

Int8U DrvTwiRead(Int8U ack) 
{
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);
  WaitTransmissionI2C();
  Int8U r = TWDR;
  if (!ack) DrvTwiStop();
  return r;
}

Int8U DrvTwiReadAck() 
{
  return DrvTwiRead(1);
}

Int8U DrvTwireadNak(void) 
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

Int8U DrvTwiReadToBuf(Int8U add, void *buf, Int8U size) 
{
  DrvTwiRepStart((add<<1) | 1);	// I2C read direction
  Int8U bytes_read = 0;
  Int8U *b = (Int8U*)buf;
  while (size--) {
    /* acknowledge all but the final byte */
    *b++ = DrvTwiRead(size > 0);
    /* TODO catch I2C errors here and abort */
    bytes_read++;
  }
  return bytes_read;
}

Int8U DrvTwiReadRegBuf(Int8U add, Int8U reg, void *buf, Int8U size) 
{
  DrvTwiRepStart(add<<1); // I2C write direction
  DrvTwiWrite(reg);        // register selection
  return DrvTwiReadToBuf(add, buf, size);
}




void DrvTwiWriteReg(Int8U add, Int8U reg, Int8U val)
 {
  DrvTwiRepStart(add<<1); // I2C write direction
  DrvTwiWrite(reg);        // register selection
  DrvTwiWrite(val);        // value to write in register
  DrvTwiStop();
}

Int8U DrvTwiReadReg(Int8U add, Int8U reg)
 {
  Int8U val;
  DrvTwiReadRegBuf(add, reg, &val, 1);
  return val;
}