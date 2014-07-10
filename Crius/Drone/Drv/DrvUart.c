/*
 * drv_uart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "Conf/conf_hard.h"

#include "DrvUart.h"
#include "DrvEvent.h"

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


#ifdef USE_UART_0
	//UART 0
	//-------
	//message stocke
	volatile Int8U in_message_0[ BUFFER_MAX ];
	volatile Int8U in_message_sent_0 = 0U;
	volatile Int8U in_message_len_0 = 0U;
	
	//buffer de reception de message uart 0
	volatile Int8U buff_uart_0[ BUFFER_MAX ];
	volatile Int8U ctr_buff_uart_0 = 0U;
#endif

#ifdef USE_UART_1
	//UART 1
	//-------
	//message stocke
	volatile Int8U in_message_1[ BUFFER_MAX ];
	volatile Int8U in_message_len_1 = 0U;
	//buffer de reception de message uart 0
	volatile Int8U buff_uart_1[BUFFER_MAX];
	volatile Int8U ptr_buff_uart_1 = 0U;
	volatile Boolean start_frame_uart_1 = FALSE;
#endif
  
  
volatile STrame m_trame;
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUartInit( Int8U index_uart, Int32U baud_rate )
{
	Int16U m_baud_rate = ComputeBaudRateDoubleSpeed(baud_rate);
	//on fixe les registres
	if(index_uart == UART_0)
	{
		UBRR0H = m_baud_rate >> 8;
		UBRR0L = m_baud_rate & 0x00FFU;
		UCSR0A |= (1<<U2X0);	//double speed mode
		UCSR0B |= (1<<RXEN0);	//enable RX
		UCSR0B |= (1<<TXEN0);	//enable TX 
		UCSR0B |= (1<<RXCIE0);	//enable RX interrupt 
		UCSR0B |= (1<<TXCIE0);	//enable TX interrupt 
		UCSR0C |= (1<<UCSZ00); 	//8 bits, no parity, 1 stop 
		UCSR0C |= (1<<UCSZ01); 
	}
	#if defined (__AVR_ATmega1284P__)
	if(index_uart == UART_1)
	{
		UBRR1H = m_baud_rate >> 8;
		UBRR1L = m_baud_rate & 0x00FFU;
		UCSR1B |= (1<<RXEN1);	//enable RX
		UCSR1B |= (1<<TXEN1);	//enable TX 
		UCSR1B |= (1<<RXCIE1);	//enable RX interrupt 
		UCSR1C|= (1<<UCSZ10); 	//8 bits, no parity, 1 stop 
		UCSR1C|= (1<<UCSZ11);  
	}
	#endif
}



Boolean DrvUart0ReadBuffer( Int8U *trame ,Int8U *lenght )
{
	Boolean o_success = FALSE;
	//commence par une '*'
	if(buff_uart_0[ 0U ] == '*') 
	{
		//termine par une '*'
		if( buff_uart_0[ buff_uart_0[ 1U ] - 1U ] == '*')
		{
			//on confirme termine par une '*'
			if(buff_uart_0[ ctr_buff_uart_0 - 1U ] == '*')
			{
				*lenght = buff_uart_0[ 1U ];
				//nb caract recu en [1] 
				for( Int8U loop = 0U; loop < *lenght ; loop++)
				{
					trame[ loop ] = buff_uart_0[ loop ];
					buff_uart_0[ loop ] = 0U;
				}
				ctr_buff_uart_0 = 0U;
				o_success = TRUE;
			}
		}
	}
	else
	{
		lenght[ 0U ] = 0U;
	}
	return o_success;
}

//on recupere le message
void DrvUart0SendMessage( Char *i_message, Int8U i_message_len )
{
	Int8U start_index = in_message_len_0;
	if( (start_index + i_message_len) <= BUFFER_MAX )
	{
		//on enregistre le message 
		for ( Int8U loop_send = 0 ; loop_send < i_message_len ; loop_send++)
		{
			in_message_0[ start_index + loop_send] = i_message[ loop_send ];
		} 
	
		start_index += i_message_len ;
		in_message_len_0 = start_index; 
		//premier message de la pile
		if( i_message_len == start_index )
		{
			in_message_sent_0 = 0U;
			//on envoie le premier caractere
			while ( !( UCSR0A & (1<<UDRE0)) );
			UDR0 = in_message_0[ 0U ];
			in_message_0[ 0U ] = 0;
			in_message_sent_0++;
		}
	}
	else
	{
		in_message_len_0 = 0;
		in_message_sent_0 = 0;
	}
}

//on recupere le message
void DrvUart0SendDirectMessage( Char *i_message, Int8U i_message_len )
{
	
	//UCSR0B &= ~(1<<TXCIE0);	//disable TX interrupt
	//on enregistre le message
	for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = i_message[ loop_send ];
	}
	//UCSR0B |= (1<<TXCIE0);	//enable TX interrupt
}

#ifdef USE_UART_1
//on recupere le message
Int8U DrvUart1ReadMessage( Char *i_message )
{
	Int8U temp_in_message_len_1 = 0;
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < in_message_len_1 ; loop_send++)
	{
		i_message[ loop_send ] = in_message_1[ loop_send ];
	}
	temp_in_message_len_1 = in_message_len_1;
	in_message_len_1 = 0U;
	return temp_in_message_len_1;
}

//on recupere le message
void DrvUart1SendMessage(Char *i_message,Int8U i_message_len )
{
	//on enregistre le message 
	for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR1A & (1<<UDRE1)) );
		UDR1 = i_message[ loop_send ];
	} 
}	
#endif

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

/////////////////////////////////////ISR PRIVATE FUNCTIONS////////////////////////////////////////

#ifdef USE_UART_0	
//UART0
//-------------------
//ISR uart
#if defined (__AVR_ATmega328P__)
ISR(USART_RX_vect)
#elif defined (__AVR_ATmega1284P__)
ISR(USART0_RX_vect)
#endif
{
	Int8U rcv_byte = UDR0 ;
	if( ctr_buff_uart_0 > 0 )
	{
		//on enregistre les octet recus
		buff_uart_0[ ctr_buff_uart_0 ] = rcv_byte;
		ctr_buff_uart_0++;
	}
	else if( rcv_byte == '*' )
	{
		buff_uart_0[ 0U ] = '*';
		ctr_buff_uart_0 = 1U;
	}
}
#endif
	
	

//ISR uart octet envoy� 
#if defined (__AVR_ATmega328P__)
ISR(USART_TX_vect)
#elif defined (__AVR_ATmega1284P__)
ISR(USART0_TX_vect)
#endif
{
	if( in_message_sent_0 < in_message_len_0)
	{
		UDR0 = in_message_0[in_message_sent_0];
		in_message_0[in_message_sent_0] = 0;
		in_message_sent_0++;
	}
	else
	{
		in_message_len_0 = 0;
		in_message_sent_0 = 0;
	}
}	

#ifdef USE_UART_1
//UART1
//-------------------
//ISR uart octet recu 
#if defined (__AVR_ATmega328P__)
ISR(USART_RX_vect)
#elif defined (__AVR_ATmega1284P__)
ISR(USART1_RX_vect)
#endif
{
	
}
#endif