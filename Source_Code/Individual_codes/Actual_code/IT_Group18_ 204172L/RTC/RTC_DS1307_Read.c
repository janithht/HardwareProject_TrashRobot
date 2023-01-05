#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"
#include <avr/sleep.h>

#define Device_Write_address	0xD0
#define Device_Read_address		0xD1
#define TimeFormat12			0x40
#define AMPM					0x20


int second,minute,hour,day,date,month,year;

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);				/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);
	I2C_Repeated_Start(Device_Read_address);

	second = I2C_Read_Ack();
	minute = I2C_Read_Ack();
	hour = I2C_Read_Nack();							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	day = I2C_Read_Ack();
	date = I2C_Read_Ack();
	month = I2C_Read_Ack();
	year = I2C_Read_Nack();
	I2C_Stop();
}

int main(void)
{
	
	I2C_Init();										/* Initialize I2C */


    while(1)
    {
		RTC_Read_Clock(0);							/* Read the clock with second address i.e location is 0 */
		if (hour & TimeFormat12)	
		{
			if(hour=9 & AMPM){
			sleep_disable();	
			}if(hour=12 & AMPM){
			sleep_disable();
			}

		}

    }
}