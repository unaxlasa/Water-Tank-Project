/*
 * CFile1.c
 *
 * Created: 11/12/2021 11:40:13
 *  Author: ander
 */ 

#define F_CPU 16000000	/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h>		/* Include Delay header file */
#include <math.h>


void setupServoTimer(volatile uint8_t *reg_name, uint8_t pin_num)
{
	*reg_name = *reg_name | (1<<pin_num); /*Set up as output*/
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 39999;		/* Set TOP count for timer1 in ICR1 register */
	TCCR1A =  (1 << COM1A1) | (0 << COM1A0) ; // When the compare match is the same we set it low
	TCCR1A |=  (1 << WGM11) | (0 << WGM10) ; // Fast PWM: TOP: ICR1
	TCCR1B = (1 << WGM13) | (1 << WGM12); // // Fast PWM: TOP: ICR1
	TCCR1B |= (0 << CS12) | (1 << CS11) | ( 0 << CS10 ); // Preesc = 8
}
void moveServoTimer(uint8_t porcentage)
{
	uint8_t timePWM;
	timePWM = round((porcentage*2000)/90);
	OCR1B = timePWM;
}
/* void moveServoDelay(volatile uint8_t *reg_name, uint8_t pin_num, uint8_t porcentage)
{
	int8_t timePWM2;
	timePWM2 = round((porcentage*1)/90);
	*reg_name = *reg_name | (1<<pin_num);HIGH
	_delay_ms(timePWM2);
	*reg_name = *reg_name & ~(1<<pin_num);LOW
	_delay_ms(20-timePWM2);
}
*/

