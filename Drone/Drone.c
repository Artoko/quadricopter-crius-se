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
#include "Drv/DrvAdc.h"
#include "Drv/DrvEvent.h"
#include "Drv/DrvEeprom.h"
#include "Drv/DrvInterrupt.h"

#include "Srv/SrvImu.h"
#include "Srv/SrvComm.h"
#include "Srv/SrvStartEngine.h"
#include "Srv/SrvPID.h"
#include "Srv/SrvMotor.h"


////////////////////////////////////////PRIVATE VARIABLES////////////////////////////////////////
//event main
volatile Event_t current_main_event = 0;

Simu imu_desire;
Simu imu_reel;

Int16U speed;
Int32U pression;
Int16S temperature;

int main(void)
{
	
	// ********************* Interrupt Disable ****************************************
	DrvInterruptClearAllInterrupts();
	
	// ********************* Led init *************************************************
	CONFIGURE_LED_PIN();
	//start Initialisation
	LED_ON();
	imu_desire.roulis	= 0;
	imu_desire.tangage  = 0;
	imu_desire.lacet	= 0;
	imu_reel.altitude	= 0;
	imu_reel.roulis	    = 0;
	imu_reel.tangage	= 0;
	imu_reel.lacet	    = 0;
	imu_reel.altitude	= 0;
	speed				= 0;
	pression			= 0;
	temperature			= 0;
	
	// ********************* Drivers init *********************************************
	DrvEventInit();
	DrvTickInit();
	DrvTwiInit();
	DrvAdcInit();
	DrvUartInit();
	DrvEepromInit();
	
	// ********************* PID init *************************************************
	SrvPIDInit(0,12,0.5,-180); //roulis
	SrvPIDInit(1,12,0.5,-180); //tangage
	SrvPIDInit(2,10,0,0);  //lacet
	SrvPIDInit(3,1,0,0);   //altitude
	
	// ********************* Interrupt Enable *****************************************
	DrvInterruptSetAllInterrupts();
	
	// ********************* Composants init ******************************************
	SrvImuInit();
	
	//Wait 2 sec for sensors init
	DrvTimerDelayMs(2000);
		
	// ********************* Calibration sensors **************************************
	SrvImuSensorsCalibration();
	
	//Wait 2 sec for sensors
	DrvTimerDelayMs(2000);
	
	// ********************* Initialisation services **********************************
	SrvMotorInit();
	SrvStartEngineInit();
	SrvCommInit();	
	
	//stop Initialisation
	LED_OFF();
	
	// ********************* Reset time ***********************************************
	DrvEventTickReset();
	
    while(TRUE)
    {			
		
		current_main_event = DrvEventGetEvent( current_main_event );
		// ********************* Compute sensors **************************************
		SrvImuDispatcher(current_main_event);
		//DrvAdcDispatcher(current_main_event);
		// ********************* Receive UART data ************************************
		SrvCommDispatcher(current_main_event);
		
		// *********************Allumage progressif ***********************************
		//SrvStartEngineDispatcher(current_main_event);
		
		
	}		
}

