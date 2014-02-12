/*
 * drv_uart.c
 *
 * Created: 28/06/2011 15:52:35
 *  Author: berryer
 */ 

#include "DrvUart.h"
#include "Conf/conf_hard.h"

#include "DrvEvent.h"

////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////

////////////////////////////////////////PRIVATE VARIABLES/////////////////////////////////////////


#ifdef USE_UART_0
	//UART 0
	//-------
	//message stocke
	volatile Int8U in_message_0[50U];
	volatile Int8U in_message_sent = 0U;
	volatile Int8U in_message_len_0 = 0U;
	
	//buffer de reception de message uart 0
	volatile Int8U buff_uart_0[50U];
	volatile Int8U ctr_buff_uart_0 = 0U;
	volatile Boolean start_frame_uart_0 = FALSE;
#endif

#ifdef USE_UART_1
	//UART 1
	//-------
	//message stocke
	volatile Int8U in_message_1[100U];
	volatile Int8U in_message_len_1 = 0U;
	//buffer de reception de message uart 0
	volatile Int8U buff_uart_1[100U];
	volatile Int8U ptr_buff_uart_1 = 0U;
	volatile Boolean start_frame_uart_1 = FALSE;
#endif

STrame trame_uart;
  
/////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////
// Init du Drv Uart 
void DrvUartInit( )
{
	//on fixe les registres
	#ifdef USE_UART_0
		//UBRR0L = 0x08U;		//115200 baud
		UBRR0L = 0x19U;		//38400 baud
		UCSR0B |= (1<<RXEN0);	//enable RX
		UCSR0B |= (1<<TXEN0);	//enable TX 
		UCSR0B |= (1<<RXCIE0);	//enable RX interrupt 
		UCSR0B |= (1<<TXCIE0);	//enable TX interrupt 
		UCSR0C|= (1<<UCSZ00); 	//8 bits, no parity, 1 stop 
		UCSR0C|= (1<<UCSZ01); 
	#endif
			
	#ifdef USE_UART_1
		UBRR1 = 0x000CU;		//38400 baud
		UCSR1B |= (1<<RXEN1);	//enable RX
		UCSR1B |= (1<<TXEN1);	//enable TX 
		UCSR1B |= (1<<RXCIE1);	//enable RX interrupt 
		UCSR1C|= (1<<UCSZ10); 	//8 bits, no parity, 1 stop 
		UCSR1C|= (1<<UCSZ11);  
	#endif
		
	for(Int8U loop = 0U; loop < NB_PARAM ; loop++)
	{
		trame_uart.param[loop] = 0;
	}
}

//on recupere le message
void DrvUart0ReadMessage( STrame *trame )
{
	for(Int8U loop = 0U; loop < NB_PARAM ; loop++)
	{
		trame->param[loop] = trame_uart.param[loop] ;
		trame_uart.param[loop] = 0;
	}
	
	//on attend le start frame
	start_frame_uart_0 = FALSE;
}
//on recupere le message
void DrvUart0SendMessage( Char *i_message, Int8U i_message_len )
{
	/*for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = i_message[ loop_send ];
	} */
	//on enregistre le message 
	for ( Int8U loop_send = in_message_len_0 ; loop_send < i_message_len ; loop_send++)
	{
		in_message_0[loop_send] = i_message[loop_send];
	} 
	
	in_message_len_0 += i_message_len ;
	in_message_0[in_message_len_0] = 0U;
	//premier message de la pile
	if(i_message_len == in_message_len_0)
	{
		//on envoie le premier caractere
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = in_message_0[ 0U ];
		in_message_sent = 1U;
	}
}
//on recupere le message
void DrvUart0SendDirectMessage( Char *i_message, Int8U i_message_len )
{
	//on enregistre le message
	for ( Int8U loop_send = 0U ; loop_send < i_message_len ; loop_send++)
	{
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = i_message[ loop_send ];
	}
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
//ISR uart octet recu
volatile Int8U decade = 1U;
volatile Int8U index_param = 0U;
volatile Char rcv_byte = 0U;
volatile Char last_rcv_byte = 0U;
volatile Int8S signe = 0;
ISR(USART_RX_vect)
{
	//on enregistre l'octet recu
	rcv_byte = UDR0;
	//si on a deja recu le start frame
	if( start_frame_uart_0 == FALSE )
    {
		//si c'est un debut de trame
		if(rcv_byte == '*' )
		{
			buff_uart_0[ 0U ] = '*';
			ctr_buff_uart_0 = 1U;
			//on a recu le start frame
			start_frame_uart_0 = TRUE;
			signe = 0;
		}
	}
	else
	{
		//on charge le message dans le buff_uart_0
		buff_uart_0[ctr_buff_uart_0] = rcv_byte;
		last_rcv_byte = buff_uart_0[ctr_buff_uart_0 - 1U];
		ctr_buff_uart_0++;	
			
		//si fin de trame
		if(( last_rcv_byte == '#' ) && ( rcv_byte == '#' ))
		{
			index_param = 0;
			decade = 1;
			//on lance l'event
			DrvEventAddEvent( CONF_EVENT_MSG_RCV );
		}
		else
		{
			//si on a pas recu de nouvelle '*'
			if(rcv_byte == '*' )
			{
				//on attend le start frame
				start_frame_uart_0 = FALSE;
				index_param = 0;
				decade = 1;
			}
			else
			{
				//on discossie les params
				if( last_rcv_byte == '+' )
				{
					index_param++;
					decade = 1;
					signe = 0;
				}
				else if( last_rcv_byte == '-' )
				{
					index_param++;
					decade = 1;		
					signe = 1;
				}
				else
				{
					if(last_rcv_byte != '*')
					{
						trame_uart.param[index_param] *= decade;
						if(signe == 1)
						{
							trame_uart.param[index_param] -= (last_rcv_byte - 0x30);
						}
						else
						{
							trame_uart.param[index_param] += (last_rcv_byte - 0x30);
						}
						decade = 10;
					}
				}
			}				
		}		
	}	
}	
#endif

//ISR uart octet envoyé 
ISR(USART_TX_vect)
{
	if( in_message_len_0 > 0U)
	{
		UDR0 = in_message_0[in_message_sent++];
		in_message_len_0--;
	}
	else
	{
		in_message_len_0 = 0;
		in_message_sent= 0;
	}
}	

#ifdef USE_UART_1
//UART1
//-------------------
//ISR uart octet recu 
ISR(USART1_RX_vect)
{
	
}
#endif