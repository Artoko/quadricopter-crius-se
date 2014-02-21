/*
 * DrvTwi.h
 *
 * Created: 03/07/2012 10:23:09
 *  Author: berryer
 */

 #ifndef DRVTWI_H_
 #define DRVTWI_H_

 #include "Tools/tools_typedefs.h"


////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////

#define TWI_SPEED_100K		100U
#define TWI_SPEED_400K		400U

//on init le driver
Boolean DrvTwiInit( Int16U speed );
//read register
Boolean DrvTwiReadReg( Int8U slave_address , Int8U slave_register, Int8U *data ) ;
//write register
Boolean DrvTwiWriteReg( Int8U slave_address , Int8U slave_register, Int8U data ) ;
//read many register
Boolean DrvTwiReadRegBuf(Int8U slave_address, Int8U slave_register, Int8U *buffer, Int8U buffer_size) ;
//write many register
Boolean DrvTwiWriteRegBuf(Int8U slave_address, Int8U slave_register, Int8U *buffer, Int8U buffer_size) ;

#endif /* DRVTWI_H_ */