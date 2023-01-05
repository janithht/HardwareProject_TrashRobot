
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor.h"



void MotorInit()
{

	//set up pwm for speed control - fast PWM

	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); //different registers on same timer1

	//clk=fcpu/64

	TCCR1B=(1<<CS11)|(1<<CS10);

	//Set the corresponding port pin to output

	DDR(OC1A_PORT)|=(1<<OC1A_PIN);
	DDR(OC1B_PORT)|=(1<<OC1B_PIN);

	//Set the direction control PINs to OUT
	DDRC|=0X3C;	//PC2 to PC5 as output

}


void MotorA(uint8_t dir,uint8_t speed)
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTC&=(~(1<<PC2));
		PORTC&=(~(1<<PC3));
	}

	else if(dir == MOTOR_CCW)
	{
		PORTC&=(~(1<<PC2));
		PORTC|=(1<<PC3);
	}
	else if(dir == MOTOR_CW)
	{
		PORTC&=(~(1<<PC3));
		PORTC|=(1<<PC2);
	}

	//Speed
	uint8_t sreg=SREG; //store SREG value
	SREG |= 1<<7;
	cli();   //Disable Interrupts during times sequence

	OCR1A=speed;

	SREG=sreg;  //Restore SREG value(I-bit)
}


void MotorB(uint8_t dir,uint8_t speed)
{
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTC&=(~(1<<PC4));
		PORTC&=(~(1<<PC5));
	}

	else if(dir == MOTOR_CCW)
	{
		PORTC&=(~(1<<PC4)); //Define pull ups and set output low
		PORTC|=(1<<PC5);  //Define pull ups and set output high
	}
	else if(dir == MOTOR_CW)
	{
		PORTC&=(~(1<<PC5));
		PORTC|=(1<<PC4);
	}

	//Speed
	uint8_t sreg=SREG;
	SREG |= 1<<7;
	cli();

	OCR1B=speed;

	SREG=sreg;
}
	

	
