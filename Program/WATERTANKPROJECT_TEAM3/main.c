/*
 * WATERTANKPROJECT_TEAM3.c
 *
 * Created: 15/12/2021 17:05:17
 * Author : Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 

/* Defines ----------------------------------------------------------*/
#define F_CPU 16000000
#define SERVO_PIN PB2
#define PUMP_PIN PD1

#define TRIG_PORT PORTB
#define TRIG_DDR  DDRD
#define ECHO_IN   PIND
#define ECHO_DDR  DDRD

#define TRIG_PIN 1
#define ECHO_PIN 6

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "twi.h"			// Twi library. Needed for controlling i2c ram. Humidity and Preassure
#include "gpio.h"			// GPIO library from class.
#include "servo.h"			// Library for controlling the servo
#include <math.h>			// Math library. For calculations like round
#include <stdio.h>			// Include std. library file
#include <util/delay.h>		// Include Delay header file
#include "menu.h"			// Library created for controlling the LCD menu
#include "bme280simu.h"		// Library created for controlling the humidity and preasure measurement for simulation
#include "valve.h"			// Valve controller library
#include "pump.h"			// Pump controller library

/* Variables ----------------------------------------------------------*/
											// Data will store: Depth, Valve open %, Pump state, Pressure,Humdity
uint16_t data[5]= {60,0,0,0,70};			// Array storing the sensors measured values
int8_t setting = 1;							// Defines what the LCD while display
uint8_t check_period =0;					// Defines a check period for doing an actualization of all the values
int8_t FULL = 400;							// The size of the tank in hight [cm]
uint8_t repeat=0;							// A variable for doing all measurement 20 times a display the 22th
int echoFlag = 0;							// A variable to know echo state
uint8_t loop = 0;							// A variable like repeat but for the ISR, but this time 5 times
uint8_t pulse;								// Defines the counter value when it drops
uint16_t distance = 0;						// The measured distance



/* Fuction declaration ------------------------------------------------*/
															// We declare some functions here for later use, we defined two of them because of putting them in other libraries gived errors
int main();													// main
uint16_t DistanceValue(void);								// A function which returns the value measured with the ultrasonic sensor, the distance to the water, which is the not filled
uint16_t DistanceSensorValue(uint8_t FULL);					// A function which returns the deph of the filled part


/* Fuction declaration ------------------------------------------------*/


uint16_t DistanceValue(void)															
{
	
	EIMSK |= (1<<INT0);				// enable INT0
	EICRA |= (1<<ISC00);			// setting interrupt trigger on any change
	EICRA &= ~(1<<ISC01);			
	
	TCCR2A = 0x00;					// Configure Timer0 for normal mode and no waveform generation
	TCCR2B = 0x05;					// Set prescaler value to clk/1024 and turn off forced output comparator
	sei(); 
	pulse=1;						// To set a bucle while reading 5 times the distance value from the ISR
	while(pulse){					// Send signal and receive signal
		GPIO_write_high(&PORTB,5);			// Send signal
		_delay_us(15);						// Trigger the ultrasonic module for 15usec
		GPIO_write_low(&PORTB,5);			// Receive signal
		_delay_ms(500);						// Trigger the ultrasonic module for 500ms
	}
	return distance;						// We return the measured distance value
	
}


uint16_t DistanceSensorValue(uint8_t FULL){		
	if (repeat>20){										// If the repeat value is 21, enters the if
		repeat=0;										// Set the repeat to zero
		uint16_t distancevalue = DistanceValue();		// We get the distance value from the previous fuction
		return FULL-distancevalue;						// We return the difference between the full tank  and the measured value
	}
	else{
		repeat++;										// If repeat value is less than 20, we increase repeat by one and we return the previous value
	}
	return data[0];										
}
/* Main function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Define the main function of the program
 * Returns:  none
 **********************************************************************/

int main(void){
	lcd_init(LCD_DISP_ON);									// We initialize the LCD display
	GPIO_config_output(&DDRD, PUMP_PIN);					// We set the Pump pin as output in the PD!
	GPIO_config_output(&DDRD, PB5);							// We configure the trigger pin in the PB% as output
	GPIO_config_input_nopull(&DDRD,ECHO_PIN);				// We set the echo pin as no pull input
	
	EIMSK |= (1<<INT0);										// enable INT0
	EICRA |= (1<<ISC00);									// setting interrupt trigger on any change
															// Configure ADC to convert PC0[A0] analog value
	
															// Set ADC reference to AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
															// Set input channel to ADC0
	ADMUX &= ~(1<<MUX3|1<<MUX2|1<<MUX1|1<<MUX0);
															// Enable ADC module
	ADCSRA |= (1<<ADEN);
															// Enable conversion complete interrupt
	sei();
	twi_init();												// We initialize the twi for bme280

	
	while(1){												// Infinite loop				
		
		ADCSRA |= (1<<ADSC);
		setting=ReadKeys(setting, ADC, data);				// We set a new setting value for the menu
		_delay_ms(200);										// A little delay of 200ms
		Display(setting, data, FULL);						// Update the display
		
		if(check_period > 6){								// Even if the setting is not meassure all values in backgraunds every 40 loops (6*20/3)
			data[0]=DistanceSensorValue(FULL);				// The distance
			data[3]=PressureGetValue(data, FULL);			// The preassure
			data[4]=HumidGetValue(data, FULL);				// The humidity
			check_period=0;									// The check period is set to zero
		}
		else{
			check_period++;									// We sume the check perio is summed by one
		}
	}
}

/* This ISR is called automatically when a change on the INT0 pin happens due to the change of the echo pin from the ultrasonic module.............*/
ISR(INT0_vect)
{
														//if the flag is 0, start timer2 with no pre-scaler
	if(echoFlag == 0) {
		TCCR2B |= (1<<CS20);
		echoFlag = 1;									// Set flag to 1
	}
	else {
		distance = TCNT2;								// Pulse takes values of counter
		TCCR2B = 0;										// Stop timer
		TCNT2 = 0;										// Reset counter
		echoFlag = 0;									// Reset flag
		loop++;
		if (loop>5){
			EIMSK  &= ~(1<<INT0);						// Disable INT0
			pulse=0;
		}
	}
	
}



