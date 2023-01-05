/*
 * OBAvo.c
 *
 * Created: 11/25/2021 10:03:39 AM
 * Author : Janith Hathnagoda
 */ 

#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "buzzer.h"
#include "LCD.h"

volatile uint16_t countLeft = 0;
volatile uint16_t countRight = 0;
uint32_t disLeft = 0;
uint32_t disRight = 0;
uint32_t speedRight;
uint32_t speedLeft;
#define Init_ticks 100
#define Time_Interval 0.01
#define PPR 20.0
#define R 6.5
#define WHEELCIRCUMFERENCE 40.84
#define GearRatio 73.6

void EncoderInit(void);
void init_system();

int main()
{
	init_system();
	LCD_Init();
	
	while(1){
		

		char numberString[4];
		LCD_SetCursor(1, 1);
		LCD_Print("DISTANCE:");
		LCD_SetCursor(10, 1);
		itoa(disLeft, numberString, 10);
		LCD_Print(numberString);
		
		
		if (disLeft <= 1000)
		{
			if(disLeft < 500){
				
				//Start Moving Forward
				MotorA(MOTOR_CW,255);
				MotorB(MOTOR_CCW,255);
				uint8_t wheelspeed;
				
				if(disLeft > 380){
					
					wheelspeed = 10 * ((500 - disLeft)/10);
					if(wheelspeed < 5){
						wheelspeed = 0;
					}
					MotorA(MOTOR_CW,wheelspeed);
					MotorB(MOTOR_CCW,wheelspeed);
				}
				
			}
			else if (500 <= disLeft && disLeft < 580)
			{
				MotorA(MOTOR_STOP,0);
				MotorB(MOTOR_CCW,150);
			}
			else if(disLeft == 580)
			{
				MotorA(MOTOR_STOP,0);
				MotorB(MOTOR_STOP,0);
				//Start Moving Forward
				MotorA(MOTOR_CW,255);
				MotorB(MOTOR_CCW,255);
			}
			else{
				//Start Moving Forward
				MotorA(MOTOR_CW,255);
				MotorB(MOTOR_CCW,255);
			}
		}
		else{
			MotorA(MOTOR_STOP,0);
			MotorB(MOTOR_STOP,0);
			buzzer();
		}
		
	} 

	return 0;
}

void EncoderInit(void)
{
	//set pins as input
	DDRD &= ~((1<<PD2)|(1<<PD3));
	//enable interrnal pullups;
	PORTD |= (1<<PD2)|(1<<PD3);
}

void CheckEncoders(void)
{
	disRight += (countRight/PPR) * WHEELCIRCUMFERENCE;
	disLeft += (countLeft/PPR) * WHEELCIRCUMFERENCE;
	speedRight = ((countRight/(Time_Interval*GearRatio))/PPR)*60.0;   // Speed equation
	speedLeft= ((countLeft/(Time_Interval*GearRatio))/PPR)*60.0;
	countRight = 0;
	countLeft = 0;
	TCNT0 = Init_ticks;
	
}

void Timer0_Start(void)
{
	TCNT0 = Init_ticks;  		/* Load TCNT0, count for 10ms*/
	TCCR0 = (1<<CS02) | (1<<CS00); /* Start timer0 with /1024 prescaler*/
	TIMSK=(1<<TOIE0);  	/* Enable Timer0 overflow interrupts */
}

ISR(TIMER0_OVF_vect)
{
	//reading Encoders
	CheckEncoders();
}

/* Interrupt Service Routine for INT0 to count each pulse from encoder */
ISR(INT0_vect)
{
	countRight++;
	
}

/* EX PIN ISR to count each pulse from encoder */
ISR(INT1_vect)
{
	countLeft++;
	
}

void init_system(){
	
	//Initialize motor subsystem
	MotorInit();
	EncoderInit();
	sei();
	GICR = 1<<INT0;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	
	GICR = 1<<INT1;		/* Enable INT1*/
	MCUCR = 1<<ISC11 | 1<<ISC10;  /* Trigger INT1 on rising edge */
	
	Timer0_Start();
	
}

