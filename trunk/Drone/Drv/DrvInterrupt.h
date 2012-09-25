/*
 * drv_interrupt.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_INTERRUPT_H_
#define DRV_INTERRUPT_H_

#include "Tools/tools_typedefs.h"



////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////


/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////


/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// On clear toutes les ITs 
void DrvInterruptClearAllInterrupts( void ) ;

// On clear toutes les ITs 
void DrvInterruptSetAllInterrupts( void ) ;

#endif /* DRV_INTERRUPT_H_ */