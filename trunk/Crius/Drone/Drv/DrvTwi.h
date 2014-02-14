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
 void DrvTwiInit( Int16U speed );
 //on lit plusieurs octets
Int8U DrvTwiReadRegBuf(Int8U add, Int8U reg, void *buf, Int8U size) ;
Int8U DrvTwiReadReg(Int8U add, Int8U reg);
void DrvTwiWriteReg(Int8U add, Int8U reg, Int8U val);

#endif /* DRVTWI_H_ */