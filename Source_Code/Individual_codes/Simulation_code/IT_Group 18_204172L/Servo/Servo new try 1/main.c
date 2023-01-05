/*
 * Servo new try 1.c
 *
 * Created: 6/3/2022 7:57:09 PM
 * Author : Taraka Rambukkamage
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	PORTB= 0x00;	/* Make OC0 pin as output */
	DDRD = 0xff;
	PORTD= 0x00;
    

   
    while (1) 
    {
		PORTB = 0x08;
		_delay_us(1000);
		PORTB = 0x00;
		_delay_ms(2000);
		
		
		PORTB = 0x08;
		_delay_us(2500);
		PORTB = 0x00;
		_delay_ms(2000);
		
		
		
		PORTD= 0x80;
		_delay_us(1000);
		PORTD= 0x00;
		_delay_ms(2000);
		
		
		PORTD  = 0x80;
		_delay_us(2500);
		PORTD  = 0x00;
		_delay_ms(2000);
    }
}

