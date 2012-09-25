/*
 * SrvComm.c
 *
 * Created: 31/05/2012 16:04:33
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"
#include "SrvComm.h"
#include "SrvMotor.h"
#include "SrvImu.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvTick.h"

#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
#include "Cmps/CmpBMA180.h"
#include "Cmps/CmpBMP085.h"

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_CHAR_MAX		100U

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////

static void SrvCommDispatchMessage (SCommTrame trame);
//message
static void SrvCommReceiveMessage (SCommTrame *ma_trame_recu) ;

//on repporte les donnees
static void SrvCommRepportData(void);
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
static Char message[ 100U ];
static Int8U lenght = 0;
Int16S x=0,y=0,z=0;
Boolean write_serial = FALSE;
Int32S last_press = 0;
Int32S last_alt = 0;


//init de la communication exterieur
void SrvCommInit (void) 
{

}	

//dispatcher d'evenements
void SrvCommDispatcher (Event_t in_event) 
{
	if( DrvEventTestEvent(in_event, CONF_EVENT_MSG_RCV))
	{
		SCommTrame ma_trame_comm;
		//reception de la trame
		SrvCommReceiveMessage(&ma_trame_comm);
		//dispatche trame
		SrvCommDispatchMessage(ma_trame_comm);
	}
	
	if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_100MS))
	{
		SrvCommRepportData();
	}
}

static void SrvCommDispatchMessage (SCommTrame trame)
{
	if(trame.param[WHO].val == COMM_MOTOR )
	{ 
		//applique la vitesse au moteurs
		SrvMotorApplySpeed(trame.param[PARAM_1].val);
	}
	
	//on ecrit si besoin
	if(write_serial == TRUE)
	{	
		lenght = strlen(message);
		DrvUart0SendMessage( message , lenght );
	}
}	

//message 
static void SrvCommReceiveMessage (SCommTrame *ma_trame_recu)
{
	Char i_message[ NB_CHAR_MAX ];
	Int8U i_message_lenght = 0U;
	
	ma_trame_recu->param[0U].val = 0;
	ma_trame_recu->param[1U].val = 0;
	ma_trame_recu->param[2U].val = 0;
	//on recupere le message entrant
	i_message_lenght = DrvUart0ReadMessage(i_message);
	
	//on enleve les ## de la fin de la trame
	i_message_lenght -= 2U; 
	
	//on prend les data du message
	if(i_message_lenght < 20U)
	{
		ma_trame_recu->param[0U].val = (i_message[1U] - 0x30);
		ma_trame_recu->param[1U].val = (((i_message[3U] - 0x30) * 10 )+ (i_message[4U] - 0x30));
	}
}

//on repporte les donnees
static void SrvCommRepportData( void )
{
	Char o_message[ 40U ];
	Int8U lenght = 0;
	lenght = sprintf(	o_message	
						,"%d, %d, %d, %d\n"
						,roulis
						,tangage
						,lacet
						,speed - 1000
					);
	DrvUart0SendDirectMessage( o_message , lenght );
}