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

#include "Srv/SrvImu.h"
#include "Srv/SrvComm.h"
#include "Srv/SrvStartEngine.h"
#include "Srv/SrvPID.h"
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

/*FUSES = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_SPIEN & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE  & FUSE_JTAGEN)
        .extended = EFUSE_DEFAULT,
    };*/

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
	
	// ********************* General variables init *************************************************
	imu_reel.roulis				= 0;
	imu_reel.tangage			= 0;
	imu_reel.lacet				= 0;
	imu_reel.altitude			= 0;
	imu_reel.temperature		= 0;
	imu_reel.pressure			= 0;  
	imu_reel.weather		    = 0;
	imu_reel.maintient_altitude	=FALSE;
	
	imu_desire.roulis				= 0;
	imu_desire.tangage				= 0;
	imu_desire.lacet				= 0;
	imu_desire.altitude				= 0;
	imu_desire.temperature			= 0;
	imu_desire.pressure				= 0;  
	imu_desire.weather				= 0;
	imu_desire.maintient_altitude	=FALSE;
	
	// ********************* Drivers init *********************************************
	DrvEventInit();
	DrvTickInit();
	DrvTwiInit();
	DrvUartInit();
	DrvEepromInit();
	
	// ********************* Interrupt Enable *****************************************
	DrvInterruptSetAllInterrupts();
	
	// ********************* Composants init ******************************************
	SrvCommInit();
	SrvTimerInit();
	SrvImuInit();
	
	//Wait 2 sec for sensors init
	DrvTimerDelayMs(3000);
	LED_OFF();
		
	// ********************* Calibration sensors **************************************
	SrvImuSensorsCalibration();
	
	//Wait 2 sec for sensors
	DrvTimerDelayMs(1000);
	
	//stop Initialisation
	LED_ON();
	
	// ********************* Reset time ***********************************************
	SrvTimerTickReset();
	
	// ********************* Start Heartbeat ******************************************
	SrvTimerAddTimer(CONF_TIMER_HEARTBEAT, 500U, E_TIMER_MODE_PERIODIC, HeartbeatIsrCallbackTimer);
	
    while(TRUE)
    {			
		current_main_event = DrvEventGetEvent( current_main_event );
		// ********************* Compute sensors **************************************
		SrvImuDispatcher(current_main_event);
		// ********************* Receive UART data ************************************
		SrvCommDispatcher(current_main_event);
	}		
}

//fct appele par le timer
void HeartbeatIsrCallbackTimer( void)
{
	//heartbeat
	LED_TOGGLE();
}