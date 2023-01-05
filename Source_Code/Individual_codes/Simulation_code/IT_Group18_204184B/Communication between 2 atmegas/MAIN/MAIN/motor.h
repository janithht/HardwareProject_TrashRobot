#include <avr/io.h>

#ifndef MOTOR_H
#define MOTOR_H

#define OC1A_PORT D
#define OC1A_PIN PD5

#define OC1B_PORT D
#define OC1B_PIN PD4


#define DDR(a) __CONCAT(DDR,a)
#define PORT(a) __CONCAT(PORT,a)
#define PIN(a) __CONCAT(PIN,a)


#define MOTOR_STOP 	0
#define MOTOR_CW	1
#define MOTOR_CCW	2

void MotorInit();
void MotorA(uint8_t dir,uint8_t speed);
void MotorB(uint8_t dir,uint8_t speed);

#endif
