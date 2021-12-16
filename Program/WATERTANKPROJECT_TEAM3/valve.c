/*
 * valve.c
 *
 * Created: 15/12/2021 11:44:22
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include <math.h>			// Math library. For calculations like round
#include "servo.h"			// Library for controlling the servo

void ValveSet(uint8_t openper){						// Set the opening range of valve % form
	TIM1_stop();									// We stop TIM1
	setupServo(openper);							// We set up the servo
	lcd_init(LCD_DISP_ON);							// We initalize again the lcd
}