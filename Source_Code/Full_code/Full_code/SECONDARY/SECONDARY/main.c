
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "LCD.h"
#include "Ultrasonic.h"

void sendData();
void Lidopen(void);

void sendData(){
	char buffer[100];
	sprintf(buffer,"%d,%d\n",distances[0],distances[1]);//prepare data and store in buffer
	USART_SendString(buffer); //send the prepared data
}


ISR(USART_RXC_vect)
{
	if(USART_RxChar()=='D'){
		sendData();
	}
}


int main(){
	DDRC = 0x01;
	sei();
	USART_init(9600);
	LCD_Init();				// Initializing the LCD
	while (1)
	{
		readDistances();
		_delay_us(10);
	}
}

void Lidopen(void){
	if (PINA & (1<<4))
	{
		_delay_us(1000);
		OCR0 = 175;	/* Set servo shaft at 0? position */
		OCR0 = 300;	/* Set servo at +90? position */
		
		OCR0 = 175;	/* Set servo shaft at 0? position */
		
	}
	if (PINA & (1<<5))
	{
		_delay_us(1000);
		OCR2 = 175;	/* Set servo shaft at 0? position */
		OCR2 = 65;	/* Set servo shaft at -90? position */
		
		OCR2 = 175;	/* Set servo shaft at 0? position */
	}
}