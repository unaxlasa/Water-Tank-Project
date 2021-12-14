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

uint8_t counter = 0;
uint8_t cicle_ON;
#define TOTAL_SIGNAL

void setupServo( uint8_t porcentage)
{
	GPIO_config_output(&DDRD,PIN_NUM);
	
	TIM0_overflow_16us(); //16
	cicle_ON= round(62.5 + 31.25*porcentage/100);
	TIM0_overflow_interrupt_enable();
	counter++;
	while(counter!=0){
		
	}
	
}

ISR(TIMER0_COMPA_vect){
	counter++;
	if(counter<cicle_ON){
		GPIO_write_high(&DDRD,PIN_NUM);
	}
	else{
		GPIO_write_low(&DDRD,PIN_NUM);
		counter=0;
	}
}

