/*
 * bme280simu.c
 *
 * Created: 15/12/2021 11:14:38
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 
/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <math.h>			// Math library. For calculations like round
#include <stdio.h>			// Include std. library file
#include "twi.h"			// Twi library. Needed for controlling i2c ram. Humidity and Preassure

/* Variables ----------------------------------------------------------*/
uint8_t repeatings =0;		// A variable for doing all measurement 20 times a display the 22th

uint16_t PressureGetValue(uint16_t data[],uint8_t FULL){
	static uint8_t preassure_addr = 0x77;			// We set the preassure adress of the bme280		
	uint8_t result;									// A variable for the result value
	//uint8_t result2;								// In case of Real Simulation we need to set another result for measured values as we have to measure adressses
	static uint8_t adress = 0x01;					// Adress for I2C RAM registers
	//static uint8_t cadress1 = 0xFD;				// In case of real simulation
	//static uint8_t adress2 = 0xFE;
	if (repeatings>20){									// If the repeat value is 21, enters the if
															
		twi_start((preassure_addr<<1) + TWI_WRITE);		// Starts i2c with 1st addr-->wanting to write
		twi_write(adress);								// Writing 0x0 to the sensor with addr
		twi_stop();										// Nothing else has to be sent
		TIM2_overflow_16ms();							// A little delay
		twi_start((preassure_addr<<1) + TWI_READ);		// After giving the	order to the slave we want to read
		result=twi_read_nack();							// Read the preassure intreger part
		twi_stop();										// We end the twi
		repeatings=0;									// Repeats is set to zero
		return result;									// Returns the result value
		//return result1<<8&result2;					// In case of real simulation
	}
	else{
		repeatings++;									// Repeating is increased by one
	}

	return data[3];										// Without measuring sends the previous value
}
uint16_t HumidGetValue(uint16_t data[],uint8_t FULL){
	
	static uint8_t humidity_addr = 0x77;				// If the repeat value is 21, enters the if
	uint8_t result;										// A variable for the result value
	//uint8_t result2;									// In case of Real Simulation we need to set another result for measured values as we have to measure adressses
	static uint8_t adress = 0x00;						// Adress for I2C RAM registers
	//static uint8_t counter1 = 0xFD;					//Counter for real demostration
	//static uint8_t counter2 = 0xFE;
	if (repeatings>20){
		twi_start((humidity_addr<<1) + TWI_WRITE);		// Starts i2c with 1st addr-->wanting to write
		twi_write(adress);								// Writing 0x0 to the sensor with addr
		twi_stop();										// Nothing else has to be sent
		TIM2_overflow_16ms();							// A little delay
		twi_start((humidity_addr<<1) + TWI_READ);		// After giving the	order to the slave we want to read
		result=twi_read_nack();							// Read the humidity integrer part
		twi_stop();										// We end the twi
		repeatings=0;									// Repeats is set to zero
		return result;									// Returns the result value
		//return result1<<8&result2;					//Repeat the same to obtain two results and do a BitShift to sume them for Real Sensor and obtain 16bits
	}
	else{
		repeatings++;									// Repeating is increased by one
	}

	return data[4];										// Without measuring sends the previous value

}
