#define F_CPU 16000000UL
#ifndef USART_H_
#define USART_H_

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_init(unsigned long USART_BAUDRATE)				/* USART initialize function */
{
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	/* Enable USART transmitter and receiver */
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRRL = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRRH = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
}

unsigned char USART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0); /*Do nothing until data have been received*/
	return(UDR);				/* return the byte*/
}

void USART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE))); /*Wait for empty transmit buffer*/
	UDR = ch ;
}

void USART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)	/*send string up to null */
	{
		USART_TxChar(str[j]);
		j++;
	}
}



#endif /* USART_H_ */