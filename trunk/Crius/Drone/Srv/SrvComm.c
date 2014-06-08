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
#include "SrvPID.h"

#include "Drv/DrvUart.h"
#include "Drv/DrvTick.h"
#include "Drv/DrvEeprom.h"

#include "Cmps/CmpITG3205.h"
#include "Cmps/CmpHMC5883.h"
#include "Cmps/CmpBMP085.h"
//ACC
#if defined( ACC_LIS331DLH )
#include "Cmps/CmpLIS331DLH.h"
#elif defined( ACC_BMA180 )
#include "Cmps/CmpBMA180.h"
#endif

////////////////////////////////////////PRIVATE DEFINES///////////////////////////////////////////
#define NB_CHAR_MAX		100U

////////////////////////////////////////PRIVATE FONCTIONS/////////////////////////////////////////
//execute message entrant
static void SrvCommExecute ( void );

//on repporte les donnees
static void SrvCommRepportData( void) ;
////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////
//passage des params de la trame
static STrame ma_trame_comm;

static Boolean want_repport_data = TRUE;

/************************************************************************/
/*init de la communication                                              */
/************************************************************************/
Boolean SrvCommInit (void) 
{
	for( Int8U loop = 0U; loop < NB_PARAM ; loop++)
	{
		ma_trame_comm.param[ loop ] = 0U;
	}
	want_repport_data = TRUE;
	return TRUE;
}	

/************************************************************************/
/*dispatcher d'evenements                                               */
/************************************************************************/
Int8U buffer[ BUFFER_MAX ];
Int8U buffer_size = 0U;

void SrvCommDispatcher (Event_t in_event) 
{
	/*if( DrvEventTestEvent(in_event, CONF_EVENT_MSG_RCV))
	{
		//reception de la trame
		DrvUart0ReadMessage(&ma_trame_comm);
		//dispatche trame
		SrvCommExecute();
	}
	
	else */
	
	//if( DrvEventTestEvent(in_event, CONF_EVENT_TIMER_10MS))
	{
		
		//on lit le buffer
		DrvUart0ReadBuffer(buffer ,&buffer_size);
		
		if(buffer_size > 3U)
		{
			Int8S signe = 1;
			Char field_in_message[ 10U ];
			Int8U cpt_message = 0U;
			Int8U cpt_field = 0U;
			//on parcours le buffer 
			for (Int8U loop = 1U ; loop < buffer_size ; loop++)
			{
				if(( buffer[ loop - 1U ] == '#' ) && ( buffer[ loop ] == '#' ) && ( buffer[ 0U ] == '*' ))
				{
					//on reset pour la prochaine trame
					DrvUart0ResetBuffer(loop + 1U);
		
					//dispatche trame
					SrvCommExecute();
				}
				else
				{
					//on cherche le + ou le -
					if( ! ( ( buffer[ loop ] == '-' ) || ( buffer[ loop ] == '+' ) || ( buffer[ loop ] == '#' ) ) )
					{
						field_in_message[ cpt_message ] = buffer[ loop ];
						cpt_message ++;
						//on efface au fur et à mesure
						buffer[ loop ] = 0U ;
					}
					else
					{
						field_in_message[ cpt_message ] = '\0';
						ma_trame_comm.param[ cpt_field ] = atoi(field_in_message) * signe;
						//on met a zero le compteur
						cpt_message = 0;
						//on incremente pour remplir le prochain champ
						cpt_field++;
						//on determine le signe du prochain champ
						if( buffer[ loop ] == '-' )
						{
							signe = -1;
						}
						else
						{
							signe = 1;
						}
					}
				}
			}
		}
		else if( want_repport_data == TRUE )
		{
			SrvCommRepportData();
		}
	}
}

/************************************************************************/
/*execute message entrant                                               */
/************************************************************************/
static void SrvCommExecute ( void )
{
	if(ma_trame_comm.param[PARAM_0] == COMM_MOTOR )
	{ 
		//controle validité data
		if(
		   ( ma_trame_comm.param[PARAM_1] >= 0U ) &&
		   ( ma_trame_comm.param[PARAM_1] <= 1000U ) 
		  )
		{
			//applique la vitesse au moteurs
			SrvMotorApplyAbsoluteSpeed(ma_trame_comm.param[PARAM_1]);
			Char o_message[ ] = { 'O','K','#','#','#','#' };
			DrvUart0SendMessage( o_message , 6U );
		}
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ANGLE )
	{ 
		//applique les angle souhaité
		imu_desire.angles.roulis	= (Int16S)ma_trame_comm.param[PARAM_1];
		SetLimits((float)imu_desire.angles.roulis, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.tangage	= (Int16S)ma_trame_comm.param[PARAM_2];
		SetLimits((float)imu_desire.angles.tangage, ANGLE_MIN, ANGLE_MAX);
		imu_desire.angles.lacet		= (Int16S)ma_trame_comm.param[PARAM_3];
		Char o_message[ ] = { 'O','K','#','#','#','#' };
		DrvUart0SendMessage( o_message , 6U );
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_ALTITUDE )
	{ 
		if(  ma_trame_comm.param[PARAM_1] == 1 )
		{
			//on enregistre l'altitude de depart
			SrvImuSensorsSetAltitudeDepart();
			Char o_message[ ] = { 'O','K','#','#','#','#' };
			DrvUart0SendMessage( o_message , 6U );
		}
		else if(  ma_trame_comm.param[PARAM_1] == 2 )
		{
			Char o_message[ ] = { 'W','E','A','T','H','E','R',':',imu_reel.weather,'#','#','#','#'};
			DrvUart0SendMessage( o_message , 13U );
		}	
		else if(  ma_trame_comm.param[PARAM_1] == 3 )
		{
			//on enregistre l'altitude relative a la position de depart
			SrvImuSensorsSetAltitudeMaintient(ma_trame_comm.param[PARAM_2]);
			Char o_message[ ] = { 'O','K','#','#','#','#' };
			DrvUart0SendMessage( o_message , 6U );
		}		
		
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_PID )
	{
		//Write PID
		if(  ma_trame_comm.param[PARAM_1] == 1 )
		{
			Int8U index = 0;
			float P = 0;
			float I = 0;
			float D = 0;
			index = ma_trame_comm.param[PARAM_2];
			P = (float)( ma_trame_comm.param[PARAM_3] / 1000.0 );
			I = (float)( ma_trame_comm.param[PARAM_4] / 1000.0 );
			D = (float)( ma_trame_comm.param[PARAM_5] / 1000.0 );
			DrvEepromWritePID( index, P, I, D );
			SrvPIDSetValues( index, P, I, D );
			Char o_message[ ] = { 'O','K','#','#','#','#' };
			DrvUart0SendMessage( o_message , 6U );
		}
		//Read PID
		else
		{
			Int8U index = 0;
			float P = 0;
			float I = 0;
			float D = 0;
			index = ma_trame_comm.param[PARAM_2];
			DrvEepromReadPID(index,&P,&I,&D);
			
			Char o_message[ ] = { 'P','I','D',':',0,0,0,0,0,0,0,'#','#','#','#'};
			
			o_message[ 4U ] = index;
			
			o_message[ 5U ] = (Int8U)((Int16S)( P * 1000 ) >> 8U);
			o_message[ 6U ] = (Int8U)((Int16S)(P * 1000 ));
			
			o_message[ 7U ] = (Int8U)((Int16S)( I * 1000 ) >> 8U);
			o_message[ 8U ] = (Int8U)((Int16S)(I * 1000 ));
			
			o_message[ 9U ] = (Int8U)((Int16S)(D * 1000 ) >> 8U);
			o_message[ 10U ] = (Int8U)((Int16S)(D * 1000 ));
			DrvUart0SendMessage( o_message , 15U );
		}
		
	}
	else if(ma_trame_comm.param[PARAM_0] == COMM_EEPROM )
	{
		if( ma_trame_comm.param[PARAM_1] == 1U)
		{
			DrvEepromDeconfigure();
		}
		Char o_message[ ] = { 'O','K','#','#','#','#' };
		DrvUart0SendMessage( o_message , 6U );
		RESET_SOFT();
	}
	else if (ma_trame_comm.param[PARAM_0]  == COMM_REPPORT)
	{
		if (want_repport_data == TRUE)
		{
			want_repport_data = FALSE;
		}
		else
		{
			want_repport_data = TRUE;
		}
		
		Char o_message[ ] = { 'O','K','#','#','#','#' };
		DrvUart0SendMessage( o_message , 6U );
	}
}	

/************************************************************************/
/*on repporte les donnees                                               */
/************************************************************************/
static void SrvCommRepportData( void )
{
	Char o_message[ 34U ];
	Int8U lenght = 0;
					
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.roulis >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.roulis;	
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.tangage >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.tangage;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.lacet >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.lacet;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.angles.nord >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.angles.nord;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.altitude >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.altitude;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.roulis >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.roulis;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.tangage >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.tangage;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.pid_error.lacet >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.pid_error.lacet;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.frontMotor_R >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.frontMotor_R;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.frontMotor_L >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.frontMotor_L;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.rearMotor_R >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.rearMotor_R;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.rearMotor_L >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.rearMotor_L;
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.moteurs.throttle >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.moteurs.throttle;
	
	o_message[ lenght++ ] = (Int8U)(((Int16U)imu_reel.pressure) >> 8U);
	o_message[ lenght++ ] = (Int8U)((Int16U)imu_reel.pressure);
	
	o_message[ lenght++ ] = (Int8U)(imu_reel.temperature >> 8U);
	o_message[ lenght++ ] = (Int8U)imu_reel.temperature;
	
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	o_message[ lenght++ ] = '#';
	
	DrvUart0SendMessage( o_message , lenght );
}

