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
#define COEFF_COMPLEMENTARY_FILTER_GYRO 0.95F
#define COEFF_COMPLEMENTARY_FILTER_ACC (1.0F - COEFF_COMPLEMENTARY_FILTER_GYRO)

#define NB_SMOOTH_ROLL_PITCH	2U
#define NB_SMOOTH_YAW			10U
////////////////////////////////////////PRIVATE STRUCTURES///////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

void ComplementaryFilter2orderRoll(float accData, float gyrData, float looptime);
void ComplementaryFilter2orderPitch(float accData, float gyrData, float looptime);
void ComplementaryFilter2orderYaw(float accData, float gyrData, float looptime);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////

//variables de timming
float interval_ekf = 0.0F;
Int32U lastread_ekf = 0U;

//variables de filtre complementaire d'ordre 2
float readings_roll[NB_SMOOTH_ROLL_PITCH];
Int8U index_roll = 0;
float total_roll = 0;
float y1_roll = 0;

float readings_pitch[NB_SMOOTH_ROLL_PITCH];
Int8U index_pitch = 0;
float total_pitch = 0;
float y1_pitch = 0;

float readings_yaw[NB_SMOOTH_YAW];
Int8U index_yaw = 0;
float total_yaw = 0;
float y1_yaw = 0;

/************************************************************************/
/*Initialisation des composants                                         */
/************************************************************************/
Boolean SrvImuInit( void )
{
	interval_ekf = 0.0F;
	lastread_ekf = 0U;
	y1_roll = 0;
	index_roll = 0;
	total_roll = 0;
	y1_pitch = 0;
	index_pitch = 0;
	total_pitch = 0;
	y1_yaw = 0;
	index_yaw = 0;
	total_yaw = 0;
	for(Int8U loop = 0U ; loop < NB_SMOOTH_ROLL_PITCH ; loop ++)
	{
		readings_yaw[loop]		= 0.0;
		readings_pitch[loop]	= 0.0;
	}
	for(Int8U loop = 0U ; loop < NB_SMOOTH_YAW ; loop ++)
	{
		readings_roll[loop]	= 0.0;
	}
	
	return TRUE;
}

/************************************************************************/
/*Dispatcher d'evenements                                               */
/************************************************************************/
void SrvImuDispatcher (Event_t in_event)
{
	// ********************* Calcul du temps de cycle *************************
	interval_ekf = (float)(DrvTickGetTimeUs() - (float)lastread_ekf) / (float)1000000.0F;
	lastread_ekf = DrvTickGetTimeUs();
	
	// ********************* Mise à jour roulis tangage lacet *****************
	ComplementaryFilter2orderRoll(imu_reel.acc_angles.roulis, imu_reel.gyr_angles.roulis, interval_ekf);
	ComplementaryFilter2orderPitch(imu_reel.acc_angles.tangage, imu_reel.gyr_angles.tangage, interval_ekf);
	ComplementaryFilter2orderYaw(imu_reel.angles.nord, imu_reel.gyr_angles.lacet,interval_ekf);
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

void ComplementaryFilter2orderRoll(float accData, float gyrData, float looptime)
{	
	float angle = (float)imu_reel.angles.roulis;
	float x1_roll = (accData - angle)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_roll = looptime*x1_roll + y1_roll;
	float x2_roll = y1_roll + (accData - angle)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
		
	total_roll = total_roll - readings_roll[index_roll];       
	readings_roll[index_roll] = (float)(looptime*x2_roll + angle);
	total_roll = total_roll + readings_roll[index_roll];       
	index_roll = index_roll + 1;
	if (index_roll >= NB_SMOOTH_ROLL_PITCH)
	{
		index_roll = 0; 
	}                          
	imu_reel.angles.roulis = (Int16S)(total_roll / NB_SMOOTH_ROLL_PITCH);  
}


/************************************************************************/
/*filtre complementaire de l'axe de tangage                             */
/************************************************************************/
void ComplementaryFilter2orderPitch(float accData, float gyrData, float looptime)
{	
	float angle = (float)imu_reel.angles.tangage;
	float x1_pitch = (accData - angle)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_pitch = looptime*x1_pitch + y1_pitch;
	float x2_pitch = y1_pitch + (accData - angle)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
	total_pitch = total_pitch - readings_pitch[index_pitch];       
	readings_pitch[index_pitch] = (float)(looptime*x2_pitch + angle);
	total_pitch = total_pitch + readings_pitch[index_pitch];       
	index_pitch = index_pitch + 1;
	if (index_pitch >= NB_SMOOTH_ROLL_PITCH)
	{
		index_pitch = 0; 
	}                          
	imu_reel.angles.tangage = (Int16S)(total_pitch / NB_SMOOTH_ROLL_PITCH);  
}

/************************************************************************/
/*filtre complementaire de l'axe de lacet                               */
/************************************************************************/
void ComplementaryFilter2orderYaw(float accData, float gyrData, float looptime)
{
	float angle = (float)imu_reel.angles.lacet;
	float x1_yaw = (accData - angle)*COEFF_COMPLEMENTARY_FILTER*COEFF_COMPLEMENTARY_FILTER;
	y1_yaw = looptime*x1_yaw + y1_yaw;
	float x2_yaw = y1_yaw + (accData - angle)*2*COEFF_COMPLEMENTARY_FILTER + gyrData;
	total_yaw = total_yaw - readings_yaw[index_yaw];
	readings_yaw[index_yaw] = (float)(looptime*x2_yaw + angle);
	total_yaw = total_yaw + readings_yaw[index_yaw];
	index_yaw = index_yaw + 1;
	if (index_yaw >= NB_SMOOTH_YAW)
	{
		index_yaw = 0;
	}
	imu_reel.angles.lacet = (Int16S)(total_yaw / NB_SMOOTH_YAW);
}