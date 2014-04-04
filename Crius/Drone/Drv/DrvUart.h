/*
 * drv_uart.h
 *
 * Created: 28/06/2011 15:53:09
 *  Author: berryer
 */ 


#ifndef DRV_UART_H_
#define DRV_UART_H_

#include "Tools/tools_typedefs.h"

#include "Conf/conf_hard.h"


////////////////////////////////////////////PUBLIC DEFINES/////////////////////////////////////////
#define UART_0	0U
#define UART_1	1U

#define PARAM_0	0U
#define PARAM_1	1U
#define PARAM_2	2U
#define PARAM_3	3U
#define PARAM_4	4U
#define PARAM_5	5U

#define NB_PARAM	6U

#define UART_SPEED_9600			9600U
#define UART_SPEED_38400		38400U
#define UART_SPEED_76800		76800U
#define UART_SPEED_115200		115200U

#define BUFFER_MAX				75U


#define ComputeBaudRate( baud )				( CONF_FOSC_HZ / ( baud * 16 ) - 1 )
#define ComputeBaudRateDoubleSpeed( baud )	( CONF_FOSC_HZ / ( baud * 8 ) - 1 )

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct SSTrame
{
	Int16S param[6U];
}STrame;
////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////

//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////




/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUartInit( Int8U index_uart, Int32U baud_rate ) ;

//************************************
// Method:    DrvUart0SendMessage
// FullName:  DrvUart0SendMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U byte_to_send		//taille du message a recuperer 
//************************************
void DrvUart0SendMessage( Char *i_message, Int8U i_message_len ) ;
void DrvUart0SendDirectMessage( Char *i_message, Int8U i_message_len );
//************************************
// Method:    DrvUart1SendMessage
// FullName:  DrvUart1SendMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U i_message_len		//taille du message a recuperer 
//************************************
void DrvUart1SendMessage( Char *i_message, Int8U i_message_len ) ;

//************************************
// Method:    DrvUart0ReadMessage
// FullName:  DrvUart0ReadMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
//**********************************
void DrvUart0ReadMessage( STrame *trame );

//************************************
// Method:    DrvUart1ReadMessage
// FullName:  DrvUart1ReadMessage
// Access:    public 
// Returns:   void
// Qualifier: on recupere le message
// Parameter: Int8U i_message[50U]		//message a recuperer
// Parameter: Int8U i_message_len		//taille du message a recuperer 
//************************************
Int8U DrvUart1ReadMessage( Char *i_message ) ;

#endif /* DRV_UART_H_ */
