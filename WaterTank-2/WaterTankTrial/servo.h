/*
 * IncFile1.h
 *
 * Created: 11/12/2021 12:51:34
 *  Author: ander
 */ 


#ifndef SERVO_H
#define SERVO_H


void setupServo(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t porcentage);

/*Moves the servo using the delay, changing the porcentage to time*/

#endif
