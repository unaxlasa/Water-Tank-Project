/*
 * CFile1.c
 *
 * Created: 11/12/2021 11:40:13
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */

#define  PIN_NUM PD2
#define F_CPU 16000000	/* Define CPU Frequency e.g. here its 16MHz */

#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include <math.h>	// Math library. For calculations like round




void setupServo( uint8_t porcentage)
{
	lcd_init(LCD_DISP_OFF);								// We turn off the lcd
	DDRD |= (1<<PD5);								// Fast PWM output at OC0B pin
	
	OCR0A  = 255;			
	OCR0B = round(255-256*(0.030517*porcentage+9.15527)/100);		// The duty cicle formula depending on the percentage
	TCCR0A |= (1<<COM0B1) | (1<<COM0B0) | (1<<WGM01) | (1<<WGM00);			// Inverting Fast PWM mode 7
	TCCR0B |= (1<<WGM02) | (1<<CS00);
	TCCR0B |= (1<<WGM02) | (1<<CS02);					// Prescalar 1024

}
