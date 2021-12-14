/*
 * sensor.c
 *
 * Created: 14/12/2021 10:14:09
 *  Author: ander
 */ 
#ifndef F_CPU
#define F_CPU 16000000
#endif
#include "i2c.h"
#include "twi.h"            // TWI library for AVR-GCC
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function

uint8_t ReadHumidity(){
	static uint8_t humidity_addr=0x23;
	uint8_t result;
	static uint8_t counter = 0x00;			 //Counter for moving through I2C RAM registers
	  //Starts i2c with 1st addr-->wanting to write
	  twi_start((humidity_addr<<1) + TWI_WRITE);
	  //Writing 0x0 to the sensor with addr
	  twi_write(counter);
	  //Nothing else has to be sent
	  twi_stop();
	   //After giving the	order to the slave we want to read
	   twi_start((humidity_addr<<1) + TWI_READ);
	   //Read the temperature integer part
	   result=twi_read_nack();
	   twi_stop();
	   return result;
}