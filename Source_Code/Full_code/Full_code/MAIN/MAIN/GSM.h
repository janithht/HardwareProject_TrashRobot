/*
 * GSM.h
 *
 * Created: 5/22/2022 10:32:56 AM
 *  Author: Janith Hathnagoda
 */ 


#ifndef GSM_H_
#define GSM_H_
#define _COMM_TX_INT TXIF


#define _COMM_RX_INT RCIF


extern void putch (char c);

extern char getch ();

extern void initUSART();
void USART_Transmit(char data );
void senddata(char string[16]);
void USART_Init1();
void delay_ms(unsigned int de);
void sendSMS();

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
	senddata("+919812345678");  //Enter Your Mobile number
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

void USART_Init1()
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




#endif /* GSM_H_ */