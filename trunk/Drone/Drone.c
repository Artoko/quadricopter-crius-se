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
#include "Drv/DrvInterrupt.h"

#include "Srv/SrvImu.h"
#include "Srv/SrvComm.h"
#include "Srv/SrvStartEngine.h"
#include "Srv/SrvPID.h"
#include "Srv/SrvMotor.h"





////////////////////////////////////////PRIVATE VARIABLES////////////////////////////////////////
//event main
volatile Event_t current_main_event = 0;

Int16S roulis;
Int16S tangage;
Int16S lacet;
Int16U speed;
Int32U pression;
Int16S temperature;
Int16U altitude;


int main(void)
{
	
	// ********************* Interrupt Disable ****************************************
	DrvInterruptClearAllInterrupts();
	
	// ********************* Led init *************************************************
	CONFIGURE_LED_PIN();
	//start Initialisation
	LED_ON();
	roulis		= 0;
	tangage		= 0;
	lacet		= 0;
	speed		= 0;
	pression	= 0;
	temperature = 0;
	altitude	= 0;
	
	// ********************* Drivers init *********************************************
	DrvEventInit();
	DrvTickInit();
	DrvTwiInit();
	DrvUartInit();
	
	// ********************* PID init *************************************************
	SrvPIDInit(0,3,0,0); //roulis
	SrvPIDInit(1,3,0,0); //tangage
	SrvPIDInit(2,2,0,0);  //lacet
	
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
	DrvTickReset();
	
    while(TRUE)
    {			
		current_main_event = DrvEventGetEvent();
		
		// ********************* Compute sensors **************************************
		SrvImuDispatcher(current_main_event);
		
		// ********************* Receive UART data ************************************
		SrvCommDispatcher(current_main_event);
		
		// *********************Allumage progressif ***********************************
		//SrvStartEngineDispatcher(current_main_event);
						
		// ********************* Kill event *******************************************	
		//on kill les event avant la nouvelle boucle
		DrvEventKillEvent(current_main_event);
	}		
}

