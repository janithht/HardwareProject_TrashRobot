/*
 * zap.c
 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#include "USART.h"
void USART_Transmit(char data );
void senddata(char string[16]);
void USART_Init();
void delay_ms(unsigned int de);
void sendSMS();

int main(){
	DDRC = 0x01;
	sei();
	
	
	while (1)
	{
		sendSMS();
		
	}
}



void sendSMS()
{
	senddata("AT+CMGD=1");
	USART_Transmit(13);
	USART_Transmit(10);
	delay_ms(1000);
	
	senddata("AT+CMGF=1");
	USART_Transmit(13);
	USART_Transmit(10);
	delay_ms(1000);
	
	senddata("AT+CMGW=");
	USART_Transmit(34);
	senddata("+94331234567");  //Enter Your Mobile number
	USART_Transmit(34);
	USART_Transmit(13);
	USART_Transmit(10);
	delay_ms(1000);
	
	senddata("Robot is here");
	USART_Transmit(13);
	USART_Transmit(10);
	delay_ms(1000);

	USART_Transmit(26); //Cntrl+Z
	delay_ms(1000);
	delay_ms(1000);

	senddata("AT+CMSS=1");
	USART_Transmit(13);
	USART_Transmit(10);
	delay_ms(1000);
}

void delay_ms(unsigned int de)
{
	unsigned int rr,rr1;
	for (rr=0;rr<de;rr++)
	{
		
		for(rr1=0;rr1<30;rr1++)  
		{
			asm("nop");
		}
		
	}
}


void USART_Transmit(char data )
{
	UDR = data;
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
}

void senddata(char string[16])
{
	int len,count;
	len = strlen(string);

	for (count=0;count<len;count++)
	{
		USART_Transmit(string[count]);
	}
}

void USART_Init()
{
	/* Set baud rate */
	UBRRH = 0x00;  //12, 9600 Baud At 1MHz
	UBRRL =12;
	//Set double speed enabled
	UCSRA |= (1<<U2X);
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	//Set interrupt on RX
	//  UCSRB |= (1<<RXCIE);
}







