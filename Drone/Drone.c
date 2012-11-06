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
#include "Srv/SrvTimer.h"

////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//fct appele par le timer
static void HeartbeatIsrCallbackTimer( void ) ;

////////////////////////////////////////PRIVATE VARIABLES////////////////////////////////////////
//event main
volatile Event_t current_main_event = 0;

Simu imu_desire;
Simu imu_reel;
//erreur retournee par le calcul du PID
Int16S pid_erreur_roulis;
Int16S pid_erreur_tangage;
Int16S pid_erreur_lacet;
Int16S pid_erreur_altitude;

Int16U speed;
Int32U pression;
Int16S temperature;

Int16U frontMotor_R	= 0U;
Int16U frontMotor_L	= 0U;
Int16U rearMotor_R	= 0U;
Int16U rearMotor_L	= 0U;

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
	SrvPIDInit( 0U , 7  ,0.5 ,-18 );  //roulis
	SrvPIDInit( 1U , 7  ,0.5 ,-18 );  //tangage
	SrvPIDInit( 2U , 1  ,0   ,0   );  //lacet
	SrvPIDInit( 3U , 1  ,0   ,0   );  //altitude
	
	// ********************* Interrupt Enable *****************************************
	DrvInterruptSetAllInterrupts();
	
	// ********************* Composants init ******************************************
	SrvTimerInit();
	SrvImuInit();
	
	//Wait 2 sec for sensors init
	DrvTimerDelayMs(3000);
		
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
	SrvTimerTickReset();
	
	// ********************* Start Heartbeat ******************************************
	SrvTimerAddTimer(CONF_TIMER_HEARTBEAT, 5000U, E_TIMER_MODE_PERIODIC, HeartbeatIsrCallbackTimer);
	
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

//fct appele par le timer
void HeartbeatIsrCallbackTimer( void)
{
	//heartbeat
	LED_TOGGLE();
}