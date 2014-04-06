/*
 * SrvKalman.c
 *
 * Created: 06/07/2012 16:34:50
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"
		
#include "SrvKalman.h"


////////////////////////////////////////PRIVATE VARIABLES////////////////////////////////////////
/* Kalman filter variables and constants */
const double Q_angleX = 0.001; // Process noise covariance for the accelerometer - Sw
const double Q_gyroX = 0.003; // Process noise covariance for the gyro - Sw
const double R_angleX = 0.03; // Measurement noise covariance - Sv

double angleX = 0; // The angle output from the Kalman filter
double biasX = 0; // The gyro bias calculated by the Kalman filter
double PX_00 = 0, PX_01 = 0, PX_10 = 0, PX_11 = 0;
double dtX, yX, SX;
double KX_0, KX_1;

////////////////////////////////////////PUBLIC FONCTIONS////////////////////////////////////////
double SrvKalmanFilterX(double newAngle, double newRate, double dtime)
{
	dtX = dtime / 1000000.0; // Convert from microseconds to seconds

	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	angleX += dtX * (newRate - biasX);

	// Update estimation error covariance - Project the error covariance ahead
	PX_00 += -dtX * (PX_10 + PX_01) + Q_angleX * dtX;
	PX_01 += -dtX * PX_11;
	PX_10 += -dtX * PX_11;
	PX_11 += +Q_gyroX * dtX;

	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	SX = PX_00 + R_angleX;
	KX_0 = PX_00 / SX;
	KX_1 = PX_10 / SX;

	// Calculate angle and resting rate - Update estimate with measurement zk
	yX = newAngle - angleX;
	angleX += KX_0 * yX;
	biasX += KX_1 * yX;

	// Calculate estimation error covariance - Update the error covariance
	PX_00 -= KX_0 * PX_00;
	PX_01 -= KX_0 * PX_01;
	PX_10 -= KX_1 * PX_00;
	PX_11 -= KX_1 * PX_01;

	return angleX;
}

/* Kalman filter variables and constants */
const double Q_angleY = 0.001; // Process noise covariance for the accelerometer - Sw
const double Q_gyroY = 0.003; // Process noise covariance for the gyro - Sw
const double R_angleY = 0.03; // Measurement noise covariance - Sv

double angleY = 0; // The angle output from the Kalman filter
double biasY = 0; // The gyro bias calculated by the Kalman filter
double PY_00 = 0, PY_01 = 0, PY_10 = 0, PY_11 = 0;
double dtY, yY, SY;
double KY_0, KY_1;

double SrvKalmanFilterY(double newAngle, double newRate, double dtime)
{
	dtY = dtime / 1000000.0; // Convert from microseconds to seconds

	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	angleY += dtY * (newRate - biasY);

	// Update estimation error covariance - Project the error covariance ahead
	PY_00 += -dtY * (PY_10 + PY_01) + Q_angleY * dtY;
	PY_01 += -dtY * PY_11;
	PY_10 += -dtY * PY_11;
	PY_11 += +Q_gyroY * dtY;

	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	SY = PY_00 + R_angleY;
	KY_0 = PY_00 / SY;
	KY_1 = PY_10 / SY;

	// Calculate angle and resting rate - Update estimate with measurement zk
	yY = newAngle - angleY;
	angleY += KY_0 * yY;
	biasY += KY_1 * yY;

	// Calculate estimation error covariance - Update the error covariance
	PY_00 -= KY_0 * PY_00;
	PY_01 -= KY_0 * PY_01;
	PY_10 -= KY_1 * PY_00;
	PY_11 -= KY_1 * PY_01;

	return angleY;
}



/* Kalman filter variables and constants */
const double Q_angleZ = 1; // Process noise covariance for the magnetometer - Sw
const double Q_gyroZ = 0.0001; // Process noise covariance for the gyro - Sw
const double R_angleZ = 0.03; // Measurement noise covariance - Sv

double angleZ = 0; // The angle output from the Kalman filter
double biasZ = 0; // The gZro bias calculated bZ the Kalman filter
double PZ_00 = 0, PZ_01 = 0, PZ_10 = 0, PZ_11 = 0;
double dtZ, ZZ, SZ;
double KZ_0, KZ_1;

double SrvKalmanFilterZ(double newAngle, double newRate, double dtime)
{
	dtZ = dtime / 1000000.0; // Convert from microseconds to seconds

	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	angleZ += dtZ * (newRate - biasZ);

	// Update estimation error covariance - Project the error covariance ahead
	PZ_00 += -dtZ * (PZ_10 + PZ_01) + Q_angleZ * dtZ;
	PZ_01 += -dtZ * PZ_11;
	PZ_10 += -dtZ * PZ_11;
	PZ_11 += +Q_gyroZ * dtZ;

	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	SZ = PZ_00 + R_angleZ;
	KZ_0 = PZ_00 / SZ;
	KZ_1 = PZ_10 / SZ;

	// Calculate angle and resting rate - Update estimate with measurement zk
	ZZ = newAngle - angleZ;
	angleZ += KZ_0 * ZZ;
	biasZ += KZ_1 * ZZ;

	// Calculate estimation error covariance - Update the error covariance
	PZ_00 -= KZ_0 * PZ_00;
	PZ_01 -= KZ_0 * PZ_01;
	PZ_10 -= KZ_1 * PZ_00;
	PZ_11 -= KZ_1 * PZ_01;

	return angleZ;
}


/* Kalman filter variables and constants */
const double Q_baroALT = 0.01; // Process noise covariance for the barometer - Sw
const double Q_accelALT = 1; // Process noise covariance for the accelerometer - Sw
const double R_angleALT = 0.01; // Measurement noise covariance - Sv

double angleALT = 0; // The angle output from the Kalman filter
double biasALT = 0; // The gZro bias calculated bZ the Kalman filter
double PALT_00 = 0, PALT_01 = 0, PALT_10 = 0, PALT_11 = 0;
double dtALT, ZALT, SALT;
double KALT_0, KALT_1;

double SrvKalmanFilterAlt(double newAngle, double newRate, double dtime)
{
	dtALT = dtime / 1000000.0; // Convert from microseconds to seconds

	// Discrete Kalman filter time update equations - Time Update ("Predict")
	// Update xhat - Project the state ahead
	angleALT += dtALT * (newRate - biasALT);

	// Update estimation error covariance - Project the error covariance ahead
	PALT_00 += -dtALT * (PALT_10 + PALT_01) + Q_baroALT * dtALT;
	PALT_01 += -dtALT * PALT_11;
	PALT_10 += -dtALT * PALT_11;
	PALT_11 += +Q_accelALT * dtALT;

	// Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
	// Calculate Kalman gain - Compute the Kalman gain
	SALT = PALT_00 + R_angleALT;
	KALT_0 = PALT_00 / SALT;
	KALT_1 = PALT_10 / SALT;

	// Calculate angle and resting rate - Update estimate with measurement zk
	ZALT = newAngle - angleALT;
	angleALT += KALT_0 * ZALT;
	biasALT += KALT_1 * ZALT;

	// Calculate estimation error covariance - Update the error covariance
	PALT_00 -= KALT_0 * PALT_00;
	PALT_01 -= KALT_0 * PALT_01;
	PALT_10 -= KALT_1 * PALT_00;
	PALT_11 -= KALT_1 * PALT_01;

	return angleALT;
}