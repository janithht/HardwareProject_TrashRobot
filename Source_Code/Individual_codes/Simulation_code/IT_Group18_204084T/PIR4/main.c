#include <avr/io.h>
#define F_CPU 16000000UL

int main(void)
{
   DDRB = DDRB | (1<<3);		//Make PB3 as output pin
   DDRD = DDRD | (1<<7);		//Make PD7 as output pin
   DDRA = DDRA & (~(1<<4));		//Make PA4 as input pin
   DDRA = DDRA & (~(1<<5));		//Make PA5 as input pin
   
    while (1) 
    {
		if (PINA & (1<<4))
		{
			PORTB = PORTB | (1<<3);
		}
		else
		{
			PORTB = PORTB & (~(1<<3));
		}
		
		if (PINA & (1<<5))
		{
			PORTD = PORTD | (1<<7);
		}
		else
		{
			PORTD = PORTD & (~(1<<7));
		}
		
    }
}









