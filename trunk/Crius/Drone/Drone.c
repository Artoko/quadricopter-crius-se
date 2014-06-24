/*
 * Drone.c
 *
 * Created: 03/07/2012 10:06:16
 *  Author: berryer
 */ 

/////////////////////////////////////////////INCLUDES/////////////////////////////////////////////
#include "Conf/conf_hard.h"

#include "Drv/DrvTick.h"
#include "Drv/DrvTwi.h"
#include "Drv/DrvUart.h"
#include "Drv/DrvEvent.h"
#include "Drv/DrvEeprom.h"
#include "Drv/DrvInterrupt.h"

#include "Srv/SrvKalman.h"
#include "Srv/SrvImu.h"
#include "Srv/SrvComm.h"
#include "Srv/SrvStartEngine.h"
#include "Srv/SrvPID.h"
#include "Srv/SrvMotor.h"
#include "Srv/SrvTimer.h"
#include "Srv/SrvHeartbeat.h"
#include "Srv/SrvSensors.h"

#include "Cmps/CmpBMP085.h"



////////////////////////////////////////PRIVATE VARIABLES////////////////////////////////////////
//event main
volatile Event_t current_main_event = 0;

S_imu_desiree imu_desire;
S_imu imu_reel;

//fonction principale
int main(void)
{	
	// ********************* Interrupt Disable ****************************************
	DrvInterruptClearAllInterrupts();
 
	// ********************* Stop Timers **********************************************
	TCCR0B = 0U;
	TCCR1B = 0U;
	TCCR2B = 0U;
	
	// ********************* Led init *************************************************
	CONFIGURE_LED_PIN();
	//start Initialisation
	LED_ON();
	
	// ********************* General variables init ***********************************
	imu_reel.angles.roulis		= 0;
	imu_reel.angles.tangage		= 0;
	imu_reel.angles.lacet		= 0;
	imu_reel.pid_error.altitude = 0;
	imu_reel.pid_error.roulis	= 0;
	imu_reel.pid_error.tangage	= 0;
	imu_reel.pid_error.lacet	= 0;
	
	imu_desire.angles.roulis		= 0;
	imu_desire.angles.tangage		= 0;
	imu_desire.angles.lacet			= 0;
	imu_desire.altitude				= 0;
	imu_desire.maintient_altitude	= FALSE;
	
	// ********************* Drivers init *********************************************
	DrvEventInit();
	DrvTickInit();
	DrvTwiInit( TWI_SPEED_400K );
	DrvUartInit( UART_0, UART_SPEED_115200 );
	DrvEepromInit();
	
	// ********************* Interrupt Enable *****************************************
	DrvInterruptSetAllInterrupts();
	
	// ********************* Services init ********************************************
	SrvCommInit();
	SrvTimerInit();
	SrvPIDInit();
	SrvKalmanFilterInit();
	SrvSensorsInit();
	SrvImuInit();
	SrvMotorInit(); 
	//SrvHeartbeatInit();
	
	//Wait 1 sec for sensors init
	DrvTimerDelayMs(1000);
		
	// ********************* Calibration sensors **************************************
	SrvSensorsSensorsCalibration();
	
	//Wait 2 sec for sensors
	DrvTimerDelayMs(1000);
	
	//stop Initialisation
	LED_OFF();
	
	// ********************* Reset time ***********************************************
	SrvTimerTickReset();
	
	
    while(TRUE)
    {			
		current_main_event = DrvEventGetEvent();
		// ********************* Read sensors ***************s*************************
		SrvSensorsDispatcher(current_main_event);
		// ********************* Compute sensors **************************************
		SrvImuDispatcher(current_main_event);
		// ********************* Receive transmit data ********************************
		SrvCommDispatcher(current_main_event);
		// ********************* Still alive  *****************************************
		//SrvHeartbeatDispatcher(current_main_event);
	}	
}
























/*FUSES = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_SPIEN & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE  & FUSE_JTAGEN)
        .extended = EFUSE_DEFAULT,
    };*/

