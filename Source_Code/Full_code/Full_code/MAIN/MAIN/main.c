#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "USART.h"
#include "motor.h"
#include "GSM.h"

int distances[2] = {31,31};
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
void receiveData();
void init_system();
void EncoderInit(void);
void Timer0_Start(void);
void CheckEncoders(void);
void obstacle_detect();

int main(void)
{
	DDRC = 0x01;
	DDRB |= (1<<0);
	DDRB |= (1<<1);
	DDRD |= (1 << PIND6);   //make b0 output pin
	//PORTB &= (~(1<<0));
	//PORTB &= (~(1<<1));//to communicate with other atmega32
	USART_init(9600);
	init_system();
	while (1)
	{
		PORTB &= (~(1<<0));
		PORTB &= (~(1<<1));//to communicate with other atmega32
		receiveData();
		_delay_ms(10);
		
		//received data is printed to make sure its received successfully
		char buffer[100];
		sprintf(buffer,"%d,%d\n",distances[0],distances[1]);//prepare data and store in buffer
		USART_SendString(buffer); //send the prepared data
		
		if (disLeft <= 1580)
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
			PORTB &= (~(1<<0));
			PORTB |= (1<<1);//to communicate with GSM
			USART_Init1(9600);
			sendSMS();//GSM message
		}
		
	}
}

void receiveData(){
	USART_SendString("\rD\r");//send special character to get data from the other atmega
	char recChar = USART_RxChar();
	char data[5];
	int count = 0;
	while(recChar!=','){//read until first comma
		data[count++] = recChar;
		recChar = USART_RxChar();
	}
	data[count] = '\0';
	distances[0] = atoi(data);
	memset(data, 0, 5);//clear data char array
	count =0;
	recChar = USART_RxChar();
	while(recChar!='\n'){//read until new line
		data[count++] = recChar;
		recChar = USART_RxChar();
	}
	data[count] = '\0';
	distances[1] = atoi(data);
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
void obstacle_detect(void){
	if (distances[0] <= 30 || distances[1] <= 30 )
	{
		MotorA(MOTOR_STOP,0);
		MotorB(MOTOR_STOP,0);
		PORTD |= (1 << PIND6); //To sound the buzzer
	}
	else{	
		PORTD &= ~(1 << PIND6); 
	}

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
	obstacle_detect();
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
	GICR = 1<<INT0;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	
	GICR = 1<<INT1;		/* Enable INT1*/
	MCUCR = 1<<ISC11 | 1<<ISC10;  /* Trigger INT1 on rising edge */
	
	Timer0_Start();
	
}

