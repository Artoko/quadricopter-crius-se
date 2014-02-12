/*
 * SrvImu.h
 *
 * Created: 06/07/2012 17:29:08
 *  Author: berryer
 */ 


#ifndef SRVIMU_H_
#define SRVIMU_H_


#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"

#include "Drv/DrvEvent.h"


////////////////////////////////////////PUBLIC FONCTIONS/////////////////////////////////////////
Boolean SrvImuInit( void );
void SrvImuDispatcher (Event_t in_event);
void SrvImuSensorsCalibration( void );
void SrvImuSensorsSetAltitudeDepart( void );
void SrvImuSensorsSetAltitudeMaintient( Int8U altitude );

#endif /* DRVIMU_H_ */