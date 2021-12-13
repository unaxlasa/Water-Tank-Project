/**
 * This file is part of HC-SR04 Ultrasonic sensor library.
 *
 * Copyright (C) 2019  Jean-Marcel Herzog
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"

#define HCSR_TRIGGER PORTB3
#define HCSR_TRIGGER_PORT PORTB
#define HCSR_TRIGGER_DDR DDRB

uint16_t rising, falling;
int counts;
float dist;
uint16_t us_per_count;

ISR(TIMER1_COMPA_vect)
{

    //Generate a 12us pulse to trigger the HC-SR04
    HCSR_TRIGGER_PORT ^= (1 << HCSR_TRIGGER);
    _delay_us(12);
    HCSR_TRIGGER_PORT ^= (1 << HCSR_TRIGGER);
}

ISR(TIMER1_CAPT_vect)
{

    if (TCCR1B & (1 << ICES1))
    {

        TCCR1B &= ~(1 << ICES1);
        rising = ICR1;
    }
    else
    {
        TCCR1B |= (1 << ICES1);
        falling = ICR1;
        counts = falling - rising;
        dist = (float)us_per_count * counts * 10 / 580;
    }
}

void init_ultrasonic_sensor()
{
    // Trigger pin as output, connected to the sensor Pin B3
    HCSR_TRIGGER_DDR |= (1 << HCSR_TRIGGER);

    //****TIMER1 INIT****//

    //noice reduction enable
    TCCR1B |= (1 << ICNC1);

    //Prescale to 64
    TCCR1B |= (1 << CS10) | (1 << CS11);

    //select CTC mode
    TCCR1B |= (1 << WGM12);

    //read Int. at: rising edge, falling edge
    TIMSK1 |= (1 << ICIE1) | (1 << OCIE1A);

    //read Int. at rising edge
    TCCR1B |= (1 << ICES1);

    //calculate TOP (70ms runtime for one cycle): 16MHz/64 = 25000 count/sec. = 25000/1000 = 2500 count/us / 100*70 = 17500 count/70ms
    OCR1A = 17500;

    //CPU-speed / Prescale = cycles/sec. 1sec/ freq./sec. = 4 (t= 4us/cycle)
    us_per_count = 4;

    //activate global interrupt
    sei();
}

float get_dist()
{
	
    return dist;
}