/*
 * Srvc
 *
 * Created: 06/07/2012 17:29:19
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "SrvImu.h"
#include "SrvMotor.h"
#include "SrvKalman.h"
#include "Srv/SrvPID.h"

#include "Drv/DrvTick.h"

#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"


////////////////////////////////////////PRIVATE STRUCTIURES////////////////////////////////////////

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
static void SrvImuComputeSensors(Int32U interval);

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static float accXangle;
static float accYangle;
static float gyroXAngle;
static float gyroYAngle;
static float gyroZAngle;
static Int16U direction;
static Int16S pid_angle_roulis;
static Int16S pid_angle_tangage;
static Int16S pid_angle_lacet;
static Int32U currentTime;
static Int32U cycleTime;


//initialistaion des composants
void SrvImuInit( void )
{
	roulis = 0;
	tangage = 0;
	lacet = 0;
	pid_angle_roulis = 0;
	pid_angle_tangage = 0;
	pid_angle_lacet = 0;
	currentTime = 0;
	cycleTime = 0;
	direction = 0;
	
	CmpHMC5883Init();
	CmpBMA180Init();
	CmpITG3205Init();
	CmpBMP085Init();
}

//dispatcher d'evenements
void SrvImuDispatcher (Event_t in_event)
{
	//BARO
	altitude = CmpBMP085Update();
	
	if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_20MS))
	{
		cycleTime = DrvTimerGetTime() - currentTime;
		currentTime = DrvTimerGetTime();
		
		// ********************* Mix sensors **************************************
		SrvImuComputeSensors(cycleTime);
		
		// ********************* kalman filter ************************************
		roulis  = SrvKalmanFilterX(accXangle, gyroXAngle, cycleTime );
		tangage = SrvKalmanFilterY(accYangle, gyroYAngle, cycleTime );
		lacet   = SrvKalmanFilterZ(direction, gyroZAngle, cycleTime );
		LED_TOGGLE();
		
	// ********************* PID **********************************************
	pid_angle_roulis	= SrvPIDCompute(0,0, roulis);
	pid_angle_tangage	= SrvPIDCompute(1,0, tangage);
	pid_angle_lacet		= SrvPIDCompute(2,lacet, lacet);
		
	// ********************* Motors *******************************************
	SrvMotorUpdate(pid_angle_roulis, pid_angle_tangage, pid_angle_lacet);
	speed = SrvMotorGetSpeed();
	
	}		
}

void SrvImuSensorsCalibration( void )
{
	S_Gyr_Angle rotation;
	S_Acc_Angle acceleration;
	S_Mag_Angle magnet;

	Boolean calibrate = FALSE;
	Int8U sens = 0;
	do
	{
		//ACC
		CmpBMA180GetAcceleration(&acceleration);
		//GYR
		CmpITG3205GetRotation(&rotation);
		//MAG
		CmpHMC5883GetHeading(&magnet);
		
		sens |= CmpITG3205IsCalibrate();
		sens |= CmpBMA180IsCalibrate() << 1;
		sens |= CmpHMC5883IsCalibrate() << 2;
		
		if(	sens == 7 )
		{
			calibrate = TRUE;
		}
		else
		{
			DrvTimerDelay10Us(STD_LOOP_TIME);
		}
	} while (!calibrate);
}

void SrvImuComputeSensors(Int32U interval)
{
	float gyroRate = 0;	
	
	S_Gyr_Angle rotation;
	S_Acc_Angle acceleration;
	S_Mag_Angle magnet;
	
	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	acceleration.x = 0;
	acceleration.y = 0;
	acceleration.z = 0;
	magnet.x = 0; 
	magnet.y = 0; 
	magnet.z = 0; 
	
	//ACC
	if(CmpBMA180GetAcceleration(&acceleration) != FALSE)
	{
		//#define ACC_ORIENTATION(X, Y, Z)  {accADC[ROLL]  = -X; accADC[PITCH]  = -Y; accADC[YAW]  =  Z;}
		acceleration.x *= -1;
		acceleration.y *= -1;
		acceleration.z *= 1;
		accXangle		= (float)atan2((double)(acceleration.x) , (double)sqrt((double)(pow((double)acceleration.y,2)+pow((double)acceleration.z,2))));
		accYangle		= (float)atan2((double)(acceleration.y) , (double)sqrt((double)(pow((double)acceleration.x,2)+pow((double)acceleration.z,2))));
	
		accXangle = ToDeg(accXangle);
		accYangle = ToDeg(accYangle);
	}
			
	//GYR
	//sensitivity	=>	14.375
	if(CmpITG3205GetRotation(&rotation) != FALSE)
	{	
		//#define GYRO_ORIENTATION(X, Y, Z) {gyroADC[ROLL] =  Y; gyroADC[PITCH] = -X; gyroADC[YAW] = -Z;}
		rotation.x *= -1;
		rotation.y *= 1;
		rotation.z *= -1;
			
		gyroRate				=	(float)(rotation.x / 14.375) ;
		gyroYAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		
		gyroRate				=	rotation.y / 14.375 ;
		gyroXAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		
		gyroRate				=	rotation.z / 14.375 ;
		gyroZAngle	+=	(float)((float)((gyroRate * interval) / 100000));
		if(gyroZAngle < 0)
		{
			gyroZAngle += 360.0;
		}
		if(gyroZAngle > 360)
		{
			gyroZAngle -= 360.0;
		}

	}		
	//MAG
	if(CmpHMC5883GetHeading(&magnet) != FALSE)
	{
		//#define MAG_ORIENTATION(X, Y, Z)  {magADC[ROLL]  =  X; magADC[PITCH]  =  Y; magADC[YAW]  = -Z;}
		magnet.x *= 1;
		magnet.y *= 1;
		magnet.z *= -1;	

		//on doit etre en dessous des 40 deg
		if(!(accXangle > 40 || accXangle < -40 || accYangle > 40 || accYangle < -40))
		{
			//compensation avec l'accelerometre
			float cosRoll = cos(ToRad(accYangle));
			float sinRoll = sin(ToRad(accYangle));  
			float cosPitch = cos(ToRad(accXangle));
			float sinPitch = sin(ToRad(accXangle));
			
			float Xh = magnet.x * cosPitch + magnet.z * sinPitch;
			float Yh = magnet.x * sinRoll * sinPitch + magnet.y * cosRoll - magnet.z * sinRoll * cosPitch;		
			float heading = atan2(Yh, Xh) + (LOCAL_MAGNETIC_DECLINAISON / 1000);
			if(heading < 0)
			{
				heading += 2*M_PI;
			}
			if(heading > 2*M_PI)
			{
				heading -= 2*M_PI;
			}
			direction = ToDeg(heading);
		}	
	}
}

