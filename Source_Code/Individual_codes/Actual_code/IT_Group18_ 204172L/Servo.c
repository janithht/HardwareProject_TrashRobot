#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
   DDRB |= (1<<PB3);	/* Make OC0 pin as output */
   DDRD |= (1<<PD7);
   TCNT0 = 0;		/* Set timer0 count zero */
   ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */
   
   DDRA = DDRA & (~(1<<4));		//Make PA4 as input pin
   DDRA = DDRA & (~(1<<5));		//Make PA5 as input pin
   
   /* Set Fast PWM, TOP in ICR1, Clear OC0on compare match, clk/64 */
   TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<CS00)|(1<<CS01)|(1<<COM01);
   TCCR2 = (1<<WGM20)|(1<<WGM21)|(1<<CS20)|(1<<CS21)|(1<<COM21);
 
    while (1) 
    {
		
		if (PINA & (1<<4))
		{
			_delay_us(1000);
			OCR0 = 175;	/* Set servo shaft at 0� position */
			OCR0 = 300;	/* Set servo at +90� position */
		    
			OCR0 = 175;	/* Set servo shaft at 0� position */
			
			
			
			

		}
		if (PINA & (1<<5))
		{
			_delay_us(1000);
			OCR2 = 175;	/* Set servo shaft at 0� position */
			OCR2 = 65;	/* Set servo shaft at -90� position */
			
			OCR2 = 175;	/* Set servo shaft at 0� position */
			
			
		}
		
		
    }
}









