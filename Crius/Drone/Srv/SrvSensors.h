/*
 * SrvHeartbeat.h
 *
 * Created: 06/07/2012 16:35:15
 *  Author: berryer
 */ 


#ifndef SRVSENSORS_H_
#define SRVSENSORS_H_

#include "Conf/conf_hard.h"
#include "Tools/tools_typedefs.h"
#include "Drv/DrvEvent.h"


//Init du hearbeat
Boolean SrvSensorsInit( void ) ;

//dispatcher d'evenements
void SrvSensorsDispatcher (Event_t in_event) ;

void SrvSensorsSensorsCalibration( void ) ;

void SrvSensorsReadMagnetometerSensor( S_angles *angles, S_Mag_Sensor *sensors );
void SrvSensorsReadGyroscopeSensor( S_Gyr_Angles *gyr_angles, float interval, S_Gyr_Sensor *sensors );
void SrvSensorsReadAccelerometerSensor( S_Acc_Angles	*acc_angles, S_Acc_Sensor *sensors );

#endif /* SRVSENSORS_H_ */