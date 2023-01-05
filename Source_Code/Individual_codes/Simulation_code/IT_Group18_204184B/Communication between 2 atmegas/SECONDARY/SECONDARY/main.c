
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

	/* Replace with your application code */
	while (1)
	{
		readDistances();
	}
}

