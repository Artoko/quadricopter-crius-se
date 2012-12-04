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
#define PARAM_0	0U
#define PARAM_1	1U
#define PARAM_2	2U
#define PARAM_3	3U
#define PARAM_4	4U

/////////////////////////////////////////PUBLIC STRUCTURES/////////////////////////////////////////
typedef struct SSTrame
{
	Int16S param[5U];
}STrame;
////////////////////////////////////////////PUBLIC ENUMS///////////////////////////////////////////

//////////////////////////////////////////PUBLIC PTR FCTS//////////////////////////////////////////




/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUartInit( void ) ;

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

