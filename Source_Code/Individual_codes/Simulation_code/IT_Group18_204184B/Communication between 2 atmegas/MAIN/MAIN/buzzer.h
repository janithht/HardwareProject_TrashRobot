/*
 * buzzer.h
 *
 * Created: 12/2/2021 8:20:34 AM
 *  Author: Janith Hathnagoda
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
void buzzer();

//buzzer tone
void buzzer()
{
	DDRD |= (1 << PIND6);  
	while (1)
	{
		PORTD |= (1 << PIND6);
	}
}





#endif /* BUZZER_H_ */