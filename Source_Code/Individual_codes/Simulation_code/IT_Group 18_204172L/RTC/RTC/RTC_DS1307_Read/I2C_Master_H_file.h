
#ifndef I2C_MASTER_H_FILE_H_
#define I2C_MASTER_H_FILE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#define SCL_CLK 100000L
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
#define Device_Write_address	0xD0
#define Device_Read_address		0xD1
#define TimeFormat12			0x40
#define AMPM					0x20

void I2C_Init();
uint8_t  I2C_Start(char write_address);
uint8_t  I2C_Repeated_Start(char read_address);
void I2C_Stop();
void I2C_Start_Wait(char write_address);
uint8_t  I2C_Write(char data);
int I2C_Read_Ack();
int I2C_Read_Nack();


#endif