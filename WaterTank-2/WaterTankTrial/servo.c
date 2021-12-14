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
	counter=0;
	GPIO_config_output(&DDRD,PIN_NUM);
	TIM0_overflow_128us(); //16
	cicle_ON = 7;
	GPIO_write_high(&PORTD,PIN_NUM);
	
	while(counter!=0){}
}

ISR(TIMER0_OVF_vect){
	if(cicle_ON < counter){
		GPIO_write_low(&PORTD,PIN_NUM);
		counter=0;
		TIM0_stop();
	}
	counter++;
}


