#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD.h"
#include "Ultrasonic.h"

int distance1, previous_distance1, percentage1, distance2, previous_distance2, percentage2, distance3, previous_distance3, distance4, previous_distance4;

int main()
{
	LCD_Init();							// Initializing the LCD

	char numberString1[4], numberString2[4];
	
	DDRD = 0xFF;

	while(1)
	{
		uint16_t r1,r2,r3,r4;
		
		_delay_ms(100);

		HCSR04Init();					// Initializing the Ultrasonic Sensor

		while(1)
		{
			HCSR04Trigger1();			// Sending trigger pulse
			r1 = GetPulseWidth1();		// Getting pulse duration
			
			HCSR04Trigger2();
			r2 = GetPulseWidth2();

			distance1=(r1*0.034/2.0);
			percentage1= distance1*100/75;
			
			if (distance1 != previous_distance1)
			{
				LCD_Clear();
			}
			
			LCD_SetCursor(1, 1);
			LCD_Print("Bin 01:");
			LCD_SetCursor(9, 1);
			itoa(percentage1, numberString1, 10);
			LCD_Print(numberString1);
			LCD_SetCursor(12, 1);
			LCD_Print("%");
			
			previous_distance1 = distance1;
			_delay_ms(30);
			
			
			distance2=(r2*0.034/2.0);
			percentage2= distance2*100/75;
			
			if (distance2 != previous_distance2)
			{
				LCD_Clear();
			}
			
			LCD_SetCursor(1, 2);
			LCD_Print("Bin 02:");
			LCD_SetCursor(9, 2);
			itoa(percentage2, numberString2, 10);
			LCD_Print(numberString2);
			LCD_SetCursor(12, 2);
			LCD_Print("%");
			
			previous_distance2 = distance2;
			_delay_ms(30);
			
			HCSR04Trigger3();			// Sending trigger pulse
			r3 = GetPulseWidth3();		// Getting pulse duration
			
			HCSR04Trigger4();
			r4 = GetPulseWidth4();

			distance3=(r3*0.035/2.0);
			
			previous_distance3 = distance3;
			_delay_ms(30);
			
			distance4=(r4*0.035/2.0);
			
			previous_distance4 = distance4;
			_delay_ms(30);
			
			if (distance3 < 30.0 || distance4 < 30.0)
			{
				PORTD = 0xFF;
			}
			else{
				PORTD= 0x00;
			}
		}
		
	}
}