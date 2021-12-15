/*
 * main.c
 *
 *  Created on: Jun 13, 2017
 *      Author: Mina G. Sadek
 */

#ifdef F_CPU
#undef F_CPU
#endif
#define F_CPU 1600000

#define TRIG_PIN 0
#define ECHO_PIN 2
#define TRIG_PORT PORTD
#define TRIG_DDR  DDRD
#define ECHO_IN   PIND
#define ECHO_DDR  DDRD

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>

static volatile int pulse_time = 0;


uint16_t DistanceValue(void)
{
	uint8_t distance= 0;


	while(distance==0){
		GPIO_write_high(&PORTD,PD0);
		_delay_us(20);						// trigger the ultrasonic module for 15usec
		GPIO_write_low(&PORTD,PD0);
		_delay_ms(10);
		distance = round(pulse_time * 0.0343 / 2);	// calculate the distance
	}
	return distance;
	
}

// This ISR is called automatically when a change on the INT0 pin happens due to the change of the echo pin from the ultrasonic module
ISR(INT0_vect)
{
	if ((ECHO_IN & (1<<ECHO_PIN)) == 0)
	{
		// echo changed from HIGH to LOW
		TCCR1B = 0;		//disabling counter
		pulse_time = TCNT1;	//count memory is updated to integer
		TCNT1 = 0;		//resetting the counter memory
	} else {
		// echo changed change from LOW to HIGH
		TCCR1B |= (1<<CS10);//enabling counter
	}
}