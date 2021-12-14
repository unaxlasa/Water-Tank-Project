/*
 * CFile1.c
 *
 * Created: 11/12/2021 11:40:13
 *  Author: 
 */

#define  PIN_NUM PD2
#define F_CPU 16000000	/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h>		/* Include Delay header file */
#include <math.h>
#include "timer.h"

uint16_t counter;
uint16_t cicle_ON;


void setupServo( uint8_t porcentage)
{
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 39999;		/* Set TOP count for timer1 in ICR1 register */
	TCCR2A =  (1 << COM1A1) | (0 << COM1A0) ; // When the compare match is the same we set it low
	TCCR2A |=  (1 << WGM11) | (0 << WGM10) ; // Fast PWM: TOP: ICR1
	TCCR2B = (1 << WGM13) | (1 << WGM12); // // Fast PWM: TOP: ICR1
	TCCR2B |= (0 << CS12) | (1 << CS11) | ( 0 << CS10 ); // Preesc = 8
	OCR2B=2000;
}

