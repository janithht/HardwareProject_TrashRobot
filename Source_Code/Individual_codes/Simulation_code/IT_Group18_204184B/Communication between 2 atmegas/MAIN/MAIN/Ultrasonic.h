#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


#define US1_TRIG_POS PA0         // Trigger pin on PA0
#define US1_ECHO_POS PA6         // Echo pin on PA6

#define US3_TRIG_POS PA2         // Trigger pin on PA2
#define US3_ECHO_POS PC6         // Echo pin on PA6

#define US2_TRIG_POS PA1        // Trigger pin on PA1
#define US2_ECHO_POS PB2         // Echo pin on PB2

#define US4_TRIG_POS PA3        // Trigger pin on PA3
#define US4_ECHO_POS PC7         // Echo pin on PC7

#define	US_NO_OBSTACLE	-2

// Function Prototypes
void HCSR04Init();
void HCSR04Trigger1();
void HCSR04Trigger2();
uint16_t GetPulseWidth1();
uint16_t GetPulseWidth2();
void HCSR04Trigger3();
void HCSR04Trigger4();
uint16_t GetPulseWidth3();
uint16_t GetPulseWidth4();

void HCSR04Init()						// Ultrasonic sensor initialization
{
	DDRA|=(1<<US1_TRIG_POS);			// Trigger pin as output
	DDRA|=(1<<US2_TRIG_POS);
	DDRA|=(1<<US3_TRIG_POS);			// Trigger pin as output
	DDRA|=(1<<US4_TRIG_POS);
}


void HCSR04Trigger1()					// Trigger pulse
{
	PORTA |= (1<<US1_TRIG_POS);		//high
	_delay_us(15);						//wait 15uS
	PORTA &= ~(1<<US1_TRIG_POS);		//low
}


void HCSR04Trigger2()					// Trigger pulse
{
	PORTA |= (1<<US2_TRIG_POS);		//high
	_delay_us(15);						//wait 15uS
	PORTA &= ~(1<<US2_TRIG_POS);		//low
}


uint16_t GetPulseWidth1()				// Measure the pulse duration
{
	uint32_t i,result;

	for(i=0;i<600000;i++)				// Checking whether ultrasonic sensor is working
	{
		if(!(PINA & (1<<US1_ECHO_POS)))
		continue;						//Line is still low
		else
		break;							//High edge detected
	}

	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);					// Resolution of the timer
	TCNT1=0x00;							// Start counting time

	for(i=0;i<600000;i++)				// Almost 40 milliseconds
	{
		if(PINA & (1<<US1_ECHO_POS))
		{
			if(TCNT1 > 60000)
			break;						// No object in the range
			else
			continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;				//Time out

	result=TCNT1;						//Falling edge found
	
	TCCR1B=0x00;						//Stop Timer

	if(result > 60000)
	return US_NO_OBSTACLE;				//No obstacle
	else
	return (result>>1);
}


uint16_t GetPulseWidth2()				// Measure the pulse duration
{
	uint32_t i,result;

	for(i=0;i<600000;i++)				// Checking whether ultrasonic sensor is working
	{
		if(!(PINB & (1<<US2_ECHO_POS)))
		continue;						//Line is still low
		else
		break;							//High edge detected
	}

	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);					// Resolution of the timer
	TCNT1=0x00;							// Start counting time

	for(i=0;i<600000;i++)				// Almost 40 milliseconds
	{
		if(PINB & (1<<US2_ECHO_POS))
		{
			if(TCNT1 > 60000)
			break;						// No object in the range
			else
			continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;				//Time out

	result=TCNT1;						//Falling edge found
	
	TCCR1B=0x00;						//Stop Timer

	if(result > 60000)
	return US_NO_OBSTACLE;				//No obstacle
	else
	return (result>>1);
}


void HCSR04Trigger3()					// Trigger pulse
{
	PORTA |= (1<<US3_TRIG_POS);		//high
	_delay_us(15);						//wait 15uS
	PORTA &= ~(1<<US3_TRIG_POS);		//low
}


void HCSR04Trigger4()					// Trigger pulse
{
	PORTA |= (1<<US4_TRIG_POS);		//high
	_delay_us(15);						//wait 15uS
	PORTA &= ~(1<<US4_TRIG_POS);		//low
}

uint16_t GetPulseWidth3()				// Measure the pulse duration
{
	uint32_t i,result;

	for(i=0;i<600000;i++)				// Checking whether ultrasonic sensor is working
	{
		if(!(PINC & (1<<US3_ECHO_POS)))
		continue;						//Line is still low
		else
		break;							//High edge detected
	}
	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);					// Resolution of the timer
	TCNT1=0x00;							// Start counting time

	for(i=0;i<600000;i++)				// Almost 40 milliseconds
	{
		if(PINC & (1<<US3_ECHO_POS))
		{
			if(TCNT1 > 60000)
			break;						// No object in the range
			else
			continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;				//Time out

	result=TCNT1;						//Falling edge found
	
	TCCR1B=0x00;						//Stop Timer

	if(result > 60000)
	return US_NO_OBSTACLE;				//No obstacle
	else
	return (result>>1);
}

uint16_t GetPulseWidth4()				// Measure the pulse duration
{
	uint32_t i,result;

	for(i=0;i<600000;i++)				// Checking whether ultrasonic sensor is working
	{
		if(!(PINC & (1<<US4_ECHO_POS)))
		continue;						//Line is still low
		else
		break;							//High edge detected
	}

	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);					// Resolution of the timer
	TCNT1=0x00;							// Start counting time

	for(i=0;i<600000;i++)				// Almost 40 milliseconds
	{
		if(PINC & (1<<US4_ECHO_POS))
		{
			if(TCNT1 > 60000)
			break;						// No object in the range
			else
			continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;				//Time out

	result=TCNT1;						//Falling edge found
	
	TCCR1B=0x00;						//Stop Timer

	if(result > 60000)
	return US_NO_OBSTACLE;				//No obstacle
	else
	return (result>>1);
}

#endif /* ULTRASONIC_H_ */