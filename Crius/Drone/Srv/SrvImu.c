/*
 * Srvc
 *
 * Created: 06/07/2012 17:29:19
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "SrvImu.h"
#include "SrvPID.h"
#include "SrvKalman.h"
#include "SrvMotor.h"
#include "SrvSensors.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"


////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define COEFF_COMPLEMENTARY_FILTER 10.0F
////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

//void ComplementaryFilter(S_Acc_Angles accData, S_Gyr_Angles gyrData);
void ComplementaryFilterRoll(float accData, float gyrData, float looptime);
void ComplementaryFilterPitch(float accData, float gyrData, float looptime);
void ComplementaryFilterYaw(float accData, float gyrData, float looptime);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//variables de timming
float interval_ekf = 0U;
Int32U lastread_ekf = 0.0F;
/************************************************************************/
/*Initialisation des composants                                         */
/************************************************************************/
Boolean SrvImuInit( void )
{
	return TRUE;
}

/************************************************************************/
/*Dispatcher d'evenements                                               */
/************************************************************************/
void SrvImuDispatcher (Event_t in_event)
{
	// ********************* Calcul du temps de cycle *************************
	interval_ekf = (float)(DrvTickGetTimeUs() - lastread_ekf) / 1000000.0F;
	lastread_ekf = DrvTickGetTimeUs();
	
	// ********************* Mise à jour roulis tangage lacet *****************
	ComplementaryFilterRoll(imu_reel.acc_angles.roulis, imu_reel.gyr_angles.roulis, interval_ekf);
	ComplementaryFilterPitch(imu_reel.acc_angles.tangage, imu_reel.gyr_angles.tangage, interval_ekf);
	ComplementaryFilterYaw(imu_reel.angles.nord, imu_reel.gyr_angles.lacet, interval_ekf);
	/*imu_reel.angles.lacet = imu_reel.gyr_angles.lacet;
	if(imu_reel.angles.lacet < 0.0)
	{
		imu_reel.angles.lacet += 360.0;
	}
	else if(imu_reel.angles.lacet > 360.0)
	{
		imu_reel.angles.lacet -= 360.0;
	}*/
	//ComplementaryFilter( imu_reel.acc_angles,imu_reel.gyr_angles);
	//imu_reel.angles.roulis   = (Int16S)(float)SrvKalmanFilterX( imu_reel.acc_angles.roulis, imu_reel.gyr_angles.roulis, interval_ekf ) ;
	//imu_reel.angles.tangage  = (Int16S)(float)SrvKalmanFilterY( imu_reel.acc_angles.tangage, imu_reel.gyr_angles.tangage, interval_ekf ) ;
	//imu_reel.angles.lacet = (Int16S)(float)SrvKalmanFilterZ(  imu_reel.gyr_angles.lacet,imu_reel.angles.nord, interval_ekf );
	
}


/************************************************************************/
/*Enregistre la position de depart                                      */
/************************************************************************/
void SrvImuSensorsSetAltitudeDepart( void )
{
	DrvEepromWriteAltitude(imu_reel.sensors.bar.altitude);
}

/************************************************************************/
/*Enregistre l altitude de maintient                                    */
/************************************************************************/
void SrvImuSensorsSetAltitudeMaintient( Int8U altitude )
{
	if(altitude != 0U)
	{
		Int16S alt = 0U;
		DrvEepromReadAltitude(&alt);
		imu_desire.maintient_altitude = TRUE;
		imu_desire.altitude = alt + altitude;
	}
	else
	{
		imu_desire.maintient_altitude = FALSE;
	}
}

/************************************************************************/
/*filtre complementaire de l'axe de roulis                              */
/************************************************************************/
void ComplementaryFilterRoll(float accData, float gyrData, float looptime)
{
	static float x1_roll = 0; 
	static float y1_roll = 0; 
	x1_roll = (accData - imu_reel.angles.roulis)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_roll = looptime*x1_roll + y1_roll;
	float x2_roll = y1_roll + (accData - imu_reel.angles.roulis)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
	imu_reel.angles.roulis = looptime*x2_roll + imu_reel.angles.roulis;
}

/************************************************************************/
/*filtre complementaire de l'axe de tangage                             */
/************************************************************************/
void ComplementaryFilterPitch(float accData, float gyrData, float looptime)
{
	static float x1_pitch = 0;
	static float y1_pitch = 0;
	x1_pitch = (accData - imu_reel.angles.tangage)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_pitch = looptime*x1_pitch + y1_pitch;
	float x2_pitch = y1_pitch + (accData - imu_reel.angles.tangage)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
	imu_reel.angles.tangage = looptime*x2_pitch + imu_reel.angles.tangage;
}

/************************************************************************/
/*filtre complementaire de l'axe de lacet                               */
/************************************************************************/
void ComplementaryFilterYaw(float accData, float gyrData, float looptime)
{
	static float x1_yaw = 0;
	static float y1_yaw = 0;
	x1_yaw = (accData - imu_reel.angles.lacet)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_yaw = looptime*x1_yaw + y1_yaw;
	float x2_yaw = y1_yaw + (accData - imu_reel.angles.lacet)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
	imu_reel.angles.lacet = looptime*x2_yaw + imu_reel.angles.lacet;
}
















/*Int32S  __attribute__ ((noinline)) mul(Int16S a, Int16S b)
{
	Int32S r;
	MultiS16X16to32(r, a, b);
	//r = (int32_t)a*b; without asm requirement
	return r;
}*/


/*void ComplementaryFilter(S_Acc_Angles accData, S_Gyr_Angles gyrData)
{
	#define gyr_poid 0.99
	#define acc_poid (100.0 - gyr_poid)
	Int16U forceMagnitudeApprox = abs(imu_reel.sensors.acc.x) + abs(imu_reel.sensors.acc.y) + abs(imu_reel.sensors.acc.z);
	if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
	{
		imu_reel.angles.tangage = (Int16S)((float)(gyrData.tangage * gyr_poid + accData.tangage * acc_poid)/100);
		imu_reel.angles.roulis = (Int16S)((float)(gyrData.roulis * gyr_poid + accData.roulis * acc_poid)/100);
	}
}*/
