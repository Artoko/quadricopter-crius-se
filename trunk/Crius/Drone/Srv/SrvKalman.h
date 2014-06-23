/*
 * SrvKalman.h
 *
 * Created: 06/07/2012 16:35:15
 *  Author: berryer
 */ 


#ifndef SRVKALMAN_H_
#define SRVKALMAN_H_


#include "Tools/tools_typedefs.h"

void SrvKalmanFilterInit( void );
double SrvKalmanFilterX(double newAngle, double newRate, float dtime) ;
double SrvKalmanFilterY(double newAngle, double newRate, float dtime) ;
double SrvKalmanFilterZ(double newAngle, double newRate, float dtime) ;
double SrvKalmanFilterAlt(double newAngle, double newRate, float dtime) ;
#endif /* SRVKALMAN_H_ */