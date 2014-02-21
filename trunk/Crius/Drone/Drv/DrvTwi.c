/*
 * drv_twi.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 
#include "Conf/conf_hard.h"
#include "util\twi.h"
#include "DrvTwi.h"

////////////////////////////////////////PRIVATE STRUCTURES/////////////////////////////////////////


////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//On attend la transmission   
static void DrvTwiWaitTransmission( void );
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
/************************************************************************/
/*Init du Drv Twi                                                       */
/************************************************************************/
Boolean DrvTwiInit( Int16U speed ) 
{
	Boolean o_success = TRUE;
	TWBR =  ((CONF_FOSC_HZ / (speed * 1000) ) - 16) / 2;	// change the I2C clock rate
	TWSR =  0U;	                                        	// Not used. Driver presumes prescaler to be 00.
	TWCR =	(1U<<TWEN) |                                	// Enable TWI-interface and release TWI pins.
			(0U<<TWIE) | (0U<<TWINT) |                    	// Disable Interupt.
			(0U<<TWEA) | (0U<<TWSTA) | (0U<<TWSTO) |      	// No Signal requests.
			(0U<<TWWC);  
	return o_success;		 
}


/************************************************************************/
/*Read register                                                         */
/************************************************************************/
Boolean DrvTwiReadReg( Int8U slave_address , Int8U slave_register, Int8U *data )
{
	Boolean read_no_error = FALSE;
	//Send start
	TWCR = (1U<<TWINT)|(1U<<TWSTA)|(1U<<TWEN);           
	DrvTwiWaitTransmission();

	if (((TWSR==TW_START) || (TWSR==TW_REP_START)) )
	{
		//send slave address write
		TWDR =  slave_address & TW_WRITE;
		TWCR = (1U<<TWINT) | (1U<<TWEN);
		DrvTwiWaitTransmission();

		if( (TWSR == TW_MT_SLA_ACK) )
		{
			//send register address
			TWDR = slave_register;
			TWCR = (1U<<TWINT) | (1U<<TWEN);
			DrvTwiWaitTransmission();

			if ( (TWSR == TW_MT_DATA_ACK) )
			{
				//repeat start
				TWCR = (1U<<TWINT)|(1U<<TWSTA)|(1U<<TWEN);
				DrvTwiWaitTransmission();
				
				//send slave address read
				if ( (TWSR == TW_REP_START) )
				{
					TWDR =  slave_address | TW_READ;                   
					TWCR = (1U<<TWINT) | (1U<<TWEN);
					DrvTwiWaitTransmission();
					
					//send clock 
					if ( (TWSR==TW_MT_SLA_ACK) )
					{
						TWCR = (1U<<TWINT) | (1U<<TWEN);                    
						DrvTwiWaitTransmission();
						
						//read data
						if ( ( TWSR==TW_MR_DATA_NACK) )
						{
							//record data
							data[ 0U ] = TWDR;
							
							//send stop
							TWCR = (1U<<TWINT) | (1U<<TWEN) | (1U<<TWSTO);
							if (TWSR==TW_NO_INFO)
							{
								//no error
								read_no_error = TRUE;
							}
						}
					}
				}
			}
		}
	}
	
	return read_no_error;
}

/************************************************************************/
/*Write register                                                        */
/************************************************************************/
Boolean DrvTwiWriteReg( Int8U slave_address , Int8U slave_register, Int8U data )
{
	Boolean write_no_error = FALSE;
	
	TWCR = (1U<<TWINT)|(1U<<TWSTA)|(1U<<TWEN);           // SEND START
	DrvTwiWaitTransmission();

	if  ( ((TWSR==TW_START) || (TWSR==TW_REP_START)) )
	{
		//send slave address
		TWDR =  slave_address & TW_WRITE;
		TWCR = (1U<<TWINT) | (1U<<TWEN);
		DrvTwiWaitTransmission();

		if ( (TWSR==TW_MT_SLA_ACK) )
		{
			//send register address
			TWDR = slave_register;
			TWCR = (1U<<TWINT) | (1U<<TWEN);
			DrvTwiWaitTransmission();

			if ( (TWSR==TW_MT_DATA_ACK) )
			{
				//write data to register
				TWDR = data;
				TWCR = (1U<<TWINT) | (1U<<TWEN);
				DrvTwiWaitTransmission();

				if ( (TWSR==TW_MT_DATA_ACK) )
				{
					//send stop
					TWCR = (1U<<TWINT)|(1U<<TWEN)| (1U<<TWSTO);

					if (TWSR==TW_NO_INFO)
					{
						write_no_error = TRUE;
					}
				}
			}
		}
	}
	
	return write_no_error;
}


/************************************************************************/
/*Read many register                                                    */
/************************************************************************/
Boolean DrvTwiReadRegBuf(Int8U slave_address, Int8U slave_register, Int8U *buffer, Int8U buffer_size) 
{
	Boolean o_success = TRUE;
	
	for( Int8U i = 0 ; i < buffer_size ; i++ )
	{
		Int8U datum = 0U;
		if( TRUE == DrvTwiReadReg( slave_address , slave_register + i , &datum ))
		{
			buffer[ i ] = datum;
		}
		else
		{
			o_success = FALSE;
			i = buffer_size;
		}
	}
	
	return o_success;
}

/************************************************************************/
/*Write many register                                                   */
/************************************************************************/
Boolean DrvTwiWriteRegBuf(Int8U slave_address, Int8U slave_register, Int8U *buffer, Int8U buffer_size)
{
	Boolean o_success = TRUE;
	
	for( Int8U i = 0 ; i < buffer_size ; i++ )
	{
		if( FALSE == DrvTwiWriteReg( slave_address , slave_register + i , buffer[ i ] ))
		{
			o_success = FALSE;
			i = buffer_size;
		}
	}
	
	return o_success;
}


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

/************************************************************************/
/*On attend la transmission                                             */
/************************************************************************/
static void DrvTwiWaitTransmission( void )
{
	Int8U count = 0xFFU;
	while ( ! (TWCR & (1<<TWINT) ) ) 
	{
		count--;
		if ( count == 0) 
		{
			TWCR = 0;
			break;
		}
	}
}