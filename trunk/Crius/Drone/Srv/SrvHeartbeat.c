/*
* SrvHeartbeat.c
*
* Created: 06/07/2012 16:34:50
*  Author: berryer
*/

#include "SrvTimer.h"
#include "SrvHeartbeat.h"



////////////////////////////////////////PRIVATE DEFINES/////////////////////////////////////////
#define HEARTBEAT_LIMIT		15U

#define HEARTBEAT_RAMP_UP	1U
#define HEARTBEAT_RAMP_DOWN	2U

#define HEARTBEAT_STATE_ON	1U
#define HEARTBEAT_STATE_OFF	2U


////////////////////////////////////////PRIVATE FUNCTIONS////////////////////////////////////////
//fct appele par le timer
static void HeartbeatIsrCallbackTimer( void ) ;

////////////////////////////////////////PRIVATE VARIABLES///////////////////////////////////////
Int8U heartbeat_delay = 0U;
Int8U heartbeat_state = 0U;
Int8U heartbeat_ramp = 0U;


//Init des valeurs d'allumage moteurs
void SrvHeartbeatInit( void )
{
	heartbeat_delay = 1U;
	heartbeat_ramp = HEARTBEAT_RAMP_UP;
	heartbeat_state = HEARTBEAT_STATE_OFF;
	
	//init de la callback
	SrvTimerAddTimer(CONF_TIMER_HEARTBEAT, HEARTBEAT_LIMIT, E_TIMER_MODE_PERIODIC, HeartbeatIsrCallbackTimer);
}

//dispatcher d'evenements
void SrvHeartbeatDispatcher (Event_t in_event)
{
	//toutes les 100ms
	if( DrvEventTestEvent( in_event, CONF_EVENT_TIMER_100MS ) == TRUE)
	{
		if( heartbeat_ramp == HEARTBEAT_RAMP_UP )
		{
			heartbeat_delay +=1U;
			if( heartbeat_delay > ( HEARTBEAT_LIMIT - 2U ) )
			{
				heartbeat_ramp = HEARTBEAT_RAMP_DOWN;
			}
		}
		else
		{
			heartbeat_delay -=1U;
			if( heartbeat_delay == 2U )
			{
				heartbeat_ramp = HEARTBEAT_RAMP_UP;
			}
		}
	}
}


/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////
//fct appele par le timer
void HeartbeatIsrCallbackTimer( void)
{
	if(heartbeat_state == HEARTBEAT_STATE_OFF)
	{
		LED_ON();
		heartbeat_state = HEARTBEAT_STATE_ON;
		SrvTimerDelayTimer( CONF_TIMER_HEARTBEAT, heartbeat_delay );
	}
	else
	{
		LED_OFF();
		heartbeat_state = HEARTBEAT_STATE_OFF;
		SrvTimerDelayTimer( CONF_TIMER_HEARTBEAT, HEARTBEAT_LIMIT - heartbeat_delay );
	}
}