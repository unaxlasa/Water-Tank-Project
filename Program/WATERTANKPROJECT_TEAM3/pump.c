/*
 * pump.c
 *
 * Created: 15/12/2021 13:46:46
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <math.h>			// Math library. For calculations like round
#include <stdio.h>			// Include std. library file
#include "gpio.h"			// GPIO library from class.	

void PumpToggle(uint16_t data[]){
	data[2]=!data[2];						// We toggle the value of the data matrix form setting 2
	if(data[2]==1){							// If it is equal to 1
		GPIO_write_high(&PORTD,1);			// We activate the relee for the pump
	}
	else{									// if it is not 1
		GPIO_write_low(&PORTD,1);			// We deactivate the relee
	}
}
