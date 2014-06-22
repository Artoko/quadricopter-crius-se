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

//ecrit l'etat de config de l'eeprom
void DrvEepromDeconfigure ( void ) ;

//retourne l'etat de config de l'eeprom
Boolean DrvEepromIsConfigured ( void ) ;

//ecrit l'etat de config de l'eeprom
void DrvEepromConfigure ( void );

//retourne le numero de version
void DrvEepromReadVersion ( Int8U *verison );

//retourne les config de l'accelerometre
void DrvEepromReadAcc ( Int16S *calib );

//enregistre les config de l'accelerometre
void DrvEepromWriteAcc ( Int16S calib[ 3U ] );

//retourne les config du gyroscope
void DrvEepromReadGyro ( Int16S *calib );

//enregistre les config du gyroscope
void DrvEepromWriteGyro ( Int16S calib[ 3U ] );

//retourne les config du pid
void DrvEepromReadPID(Int8U index,float *P, float *I, float *D);

//enregistre les config du pid
void DrvEepromWritePID (Int8U index,float P, float I, float D);

//retourne les config du altitude
void DrvEepromReadAltitude( Int16S *altitude);

//enregistre les config du altitude
void DrvEepromWriteAltitude ( Int16U altitude);


#endif /* DRV_EEPROM_H_ */