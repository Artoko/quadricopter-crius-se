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
#include "Drv/DrvLed.h"
#include "Drv/DrvButton.h"
#include "Drv/DrvEvent.h"
#include "Drv/DrvEeprom.h"
#include "Drv/DrvTimer.h"
#include "Drv/DrvInterrupt.h"

#include "Srv/SrvKalman.h"
#include "Srv/SrvImu.h"
#include "Srv/SrvComm.h"
#include "Srv/SrvStartEngine.h"
#include "Srv/SrvPID.h"
#include "Srv/SrvMotor.h"
#include "Srv/SrvSensors.h"

#include "Cmps/CmpBMP085.h"


////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
//Fonction appelle lors d'une action sur le bouton
void ActionButton (  EButtonState state  );

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
	DrvTimerInit();
	DrvButtonInit();
	DrvLedInit();
	DrvEventInit();
	DrvEepromInit();
	DrvTickInit();
	DrvUartInit( UART_0, UART_SPEED_115200 );
	DrvTwiInit( TWI_SPEED_400K );
	
	// ********************* Led init *************************************************
	DrvLedAddLed(E_LED_OK, EIO_PIN_B_1);
	DrvLedAddLed(E_LED_WARNING, EIO_PIN_B_2);
	DrvLedAddLed(E_LED_ERROR, EIO_PIN_B_3);
	
	DrvLedSetState(E_LED_OK, E_LED_ON);
	DrvLedSetState(E_LED_WARNING, E_LED_OFF);
	DrvLedSetState(E_LED_ERROR, E_LED_OFF);
	
	// ********************* Button ***************************************************
	DrvButtonAddButton(E_BUTTON_SETUP, EIO_PIN_B_0, ActionButton);
	
	// ********************* Interrupt Enable *****************************************
	DrvInterruptSetAllInterrupts();
	
	// ********************* Services init ********************************************
	SrvPIDInit();
	SrvMotorInit(); 
	SrvKalmanFilterInit();
	SrvImuInit();
	SrvCommInit();
	SrvSensorsInit();
	
	//Wait 1 sec for sensors init
	DrvTickDelayMs(1000);
		
	// ********************* Calibration sensors **************************************
	DrvLedSetState(E_LED_WARNING, E_LED_ON);
	SrvSensorsSensorsCalibration();
	DrvLedSetState(E_LED_WARNING, E_LED_OFF);
	
	// ********************* Reset time ***********************************************
	DrvLedSetBlinkMode(E_LED_OK,2,18);
	DrvTimerTickReset();
	
    while(TRUE)
    {		
		current_main_event = DrvEventGetEvent();	
		// ********************* Read sensors *****************************************
		SrvSensorsDispatcher(current_main_event);	//2.4ms
		// ********************* Compute sensors **************************************
		SrvImuDispatcher(current_main_event);		//1.6ms
		// ********************* PID compute ******************************************
		SrvPIDDispatcher(current_main_event);		//1.6ms
		// ********************* Update motors ******* ********************************
		SrvMotorDispatcher(current_main_event);		//0.2ms
		// ********************* Receive transmit data ********************************
		SrvCommDispatcher(current_main_event);
	}	
}


//Fonction appelle lors d'une action sur le bouton
void ActionButton ( EButtonState state )
{
	DrvLedSetToggle(E_LED_ERROR);
}






















/*FUSES = 
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_SPIEN & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE  & FUSE_JTAGEN)
        .extended = EFUSE_DEFAULT,
    };*/

