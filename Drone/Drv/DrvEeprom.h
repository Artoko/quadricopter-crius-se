/*
 * DrvEeprom.h
 *
 * Created: 14/11/2011 15:18:48
 *  Author: berryer
 */ 
////////////////////////////////////////INCLUDES//////////////////////////////////////////////////
#ifndef DRV_EEPROM_H_
#define DRV_EEPROM_H_

#include "Tools/tools_typedefs.h"

#include "Drv/DrvEvent.h"

////////////////////////////////////////PUBLIC DEFINES////////////////////////////////////////////

////////////////////////////////////////PUBLIC ENUMS//////////////////////////////////////////////

////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////

////////////////////////////////////////PUBLIC FUNCTIONS//////////////////////////////////////////
//Fonction d'initialisation
Boolean DrvEepromInit ( void ) ;

//retourne l'etat de config de l'eeprom
Boolean DrvEepromIsConfigured ( void ) ;

//ecrit l'etat de config de l'eeprom
void DrvEepromConfigure ( void );

//retourne les config de l'accelerometre
void DrvEepromReadAcc ( Int16U calib[ 3U ] );

//enregistre les config de l'accelerometre
void DrvEepromWriteAcc ( Int16U calib[ 3U ] );

//retourne les config du gyroscope
void DrvEepromReadGyro ( Int16U calib[ 3U ] );

//enregistre les config du gyroscope
void DrvEepromWriteGyro ( Int16U calib[ 3U ] );

#endif /* DRV_EEPROM_H_ */