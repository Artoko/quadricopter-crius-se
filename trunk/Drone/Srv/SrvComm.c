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

static void SrvCommExecute (SCommTrame trame);
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
		SrvCommExecute(ma_trame_comm);
	}
	
	if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_100MS))
	{
		SrvCommRepportData();
	}
}

//execute message
static void SrvCommExecute (SCommTrame trame)
{
	if(trame.param[WHO].val == COMM_MOTOR )
	{ 
		//applique la vitesse au moteurs
		SrvMotorApplySpeed(trame.param[PARAM_1].val);
	}
	else if(trame.param[WHO].val == COMM_ANGLE )
	{ 
		//applique les angle souhaité
		angle_desire.roulis = trame.param[PARAM_1].val;
		angle_desire.tangage = trame.param[PARAM_2].val;
		angle_desire.lacet = trame.param[PARAM_3].val;
	}
	
	//on ecrit si besoin
	if(write_serial == TRUE)
	{	
		lenght = strlen(message);
		DrvUart0SendMessage( message , lenght );
	}
}	

//on traite le message recu et on le transforme en SCommTrame
static void SrvCommReceiveMessage (SCommTrame *ma_trame_recu)
{
	Char i_message[ NB_CHAR_MAX ];
	Int8U i_message_lenght = 0U;
	Int8U index_param = 0U;
	Int8U decade = 1U;
	
	ma_trame_recu->param[WHO].val = 0U;
	ma_trame_recu->param[PARAM_1].val = 0U;
	ma_trame_recu->param[PARAM_2].val = 0U;
	ma_trame_recu->param[PARAM_3].val = 0U;
	ma_trame_recu->param[PARAM_4].val = 0U;
	//on recupere le message entrant
	i_message_lenght = DrvUart0ReadMessage(i_message);
	
	//on enleve les ## de la fin de la trame
	i_message_lenght -= 2U; 
	
	Int8U loop = 1U;
	for(loop = 1U; loop < i_message_lenght ; loop++)
	{
		if( i_message[ loop ] == '-' )
		{
			index_param++;		
			decade = 1U;	
		}
		else
		{
			ma_trame_recu->param[index_param].val *= decade;	
			ma_trame_recu->param[index_param].val += i_message[ loop ] - 0x30;
			decade *= 10;	
		}		
	}
	
	//on prend les data du message
	/*if(i_message_lenght < 20U)
	{
		ma_trame_recu->param[0U].val = (i_message[1U] - 0x30);
		ma_trame_recu->param[1U].val = (((i_message[3U] - 0x30) * 10 )+ (i_message[4U] - 0x30));
	}*/
}

//on repporte les donnees
static void SrvCommRepportData( void )
{
	Char o_message[ 40U ];
	Int8U lenght = 0;
	lenght = sprintf(	o_message	
						,"%i, %i, %i, %i\n"
						,/*(Int16U)(pression/10)//*/angle_reel.roulis
						,/*(Int16U)(temperature/10)//*/angle_reel.tangage
						,angle_reel.lacet	
						,/*(Int16U)(altitude/10)//*/speed - 1000
					);
	DrvUart0SendDirectMessage( o_message , lenght );
}
