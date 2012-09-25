/*
 * SrvKalman.h
 *
 * Created: 06/07/2012 16:35:15
 *  Author: berryer
 */ 


#ifndef SRVKALMAN_H_
#define SRVKALMAN_H_


#include "Tools/tools_typedefs.h"

double SrvKalmanFilterX(double newAngle, double newRate, double dtime) ;
double SrvKalmanFilterY(double newAngle, double newRate, double dtime) ;
double SrvKalmanFilterZ(double newAngle, double newRate, double dtime) ;

#endif /* SRVKALMAN_H_ */