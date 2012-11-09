/*
 * DrvTwi.h
 *
 * Created: 03/07/2012 10:23:09
 *  Author: berryer
 */

 #ifndef DRVTWI_H_
 #define DRVTWI_H_

 #include "Tools/tools_typedefs.h"


 //on init le driver
 void DrvTwiInit(void);
 //on lit plusieurs octets
Int8U DrvTwiReadRegBuf(uint8_t add, uint8_t reg, void *buf, Int8U size) ;
uint8_t DrvTwiReadReg(uint8_t add, uint8_t reg);
void DrvTwiWriteReg(uint8_t add, uint8_t reg, uint8_t val);

#endif /* DRVTWI_H_ */