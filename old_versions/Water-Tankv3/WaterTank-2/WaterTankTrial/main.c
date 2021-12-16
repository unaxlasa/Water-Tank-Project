/***********************************************************************
 * 

 * 
 **********************************************************************/

#define F_CPU 16000000
#define PUMP_PIN PD1


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "twi.h"
#include "gpio.h"
#include "servo.h"
#include <math.h>
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h>		/* Include Delay header file */



//Data will store: Depth, Valve open %, Pump state, Pressure,Humdity
uint16_t data[5]= {60,0,0,0,70};	//Array storing the sensors measured values
int8_t setting = 0;	//Defines what the LCD while display
uint8_t repeat=0;
uint8_t check_period =0;
uint16_t FULL = 400; //The size of the tank in hight [m]



//Function Declaration:
int main();
uint16_t DistanceSensorValue(uint8_t FULL);
uint16_t PressureGetValue();
void Display(uint8_t setting);
void PumpToggle();
void ValveSet(uint8_t openper);
uint8_t ReadKeys( uint8_t setting, int value);
uint16_t HumidGetValue();
uint16_t DistanceValue(void);

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: LCD Display
 * Purpose:  Shows the data the user wants.
 * Returns:  none
 **********************************************************************/
 void Display(uint8_t setting){
 
	 char lcd_string[2] = " ";
	 lcd_gotoxy(0,1);
	 
	 switch (setting)					//Defines the display of each setting
	 {
		 case 0:		//Depth
			 data[0] = DistanceSensorValue(FULL);		//Update the water level
			 itoa(data[setting],lcd_string,10);
			 lcd_puts(lcd_string);
			 lcd_gotoxy(0,0);
			 lcd_puts("Depth:");
			 lcd_gotoxy(5,1);
			 lcd_puts("cm");
			 break;
		 case 1:		//Valve open ratio
			 itoa(data[setting],lcd_string,10);
			 lcd_puts(lcd_string);
			 if(data[setting]==95){
				lcd_gotoxy(2,1);
				lcd_puts(" "); 
			 }
			 if(data[setting]==5){
				 lcd_gotoxy(1,1);
				 lcd_puts(" ");
			 }
			 lcd_gotoxy(0,0);
			 lcd_puts("Valve:");
			 lcd_gotoxy(5,1);
			 lcd_puts("%");
			 break;
		 case 2:		//Pump state
			 itoa(data[setting],lcd_string,10);
			 if(data[setting]==1){
				 lcd_puts("On ");

			 }
			 else{
				 lcd_puts("Off");
			 }
			 lcd_gotoxy(0,0);
			 lcd_puts("Pump:");
			 break;
		 case 3:		//Pressure
			 data[3] = PressureGetValue();		//Update the pressure at the bottom of the tank
			 itoa(data[setting],lcd_string,10);
			 lcd_puts(lcd_string);
			 lcd_gotoxy(0,0);
			 lcd_puts("Pressure:");
			 lcd_gotoxy(5,1);
			 lcd_puts("Pa");
			 break;
		 case 4:
			 data[4] = HumidGetValue();
			 itoa(data[setting],lcd_string,10);
			 lcd_puts(lcd_string);
			 lcd_gotoxy(2,1);
			 lcd_puts(" ");
			 lcd_gotoxy(0,0);
			 lcd_puts("Humid:");
			 lcd_gotoxy(5,1);
			 lcd_puts("%");
			 break;
		 
	 } 
 }

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Get the value of the Pressure
 * Purpose:  Read the pressure at the bottom of the tank. Taking into account the water level
 * Returns:  The pressure at the bottom of the tank
 **********************************************************************/

uint16_t PressureGetValue(){
	static uint8_t preassure_addr = 0x77;
	uint8_t result;
	//uint8_t result2;
	static uint8_t adress = 0x01;
	//static uint8_t counter1 = 0xFD;			 //Counter for moving through I2C RAM registers
	//static uint8_t counter2 = 0xFE;
	if (repeat>20){
		//Starts i2c with 1st addr-->wanting to write
		twi_start((preassure_addr<<1) + TWI_WRITE);
		//Writing 0x0 to the sensor with addr
		twi_write(adress);
		//Nothing else has to be sent
		twi_stop();
		TIM2_overflow_16ms();
		//After giving the	order to the slave we want to read
		twi_start((preassure_addr<<1) + TWI_READ);
		//Read the temperature integer part
		result=twi_read_nack();
		twi_stop();
		repeat=0;
		uint8_t distance = DistanceSensorValue(FULL);
		return round(result+distance*9.8/100);
		//return result1<<8&result2;
	}
	else{
		repeat++;
	}

	return data[3];
}


uint16_t HumidGetValue(){
	
	static uint8_t humidity_addr = 0x77;
	uint8_t result;
	//uint8_t result2;
	static uint8_t counter = 0x00;
	//static uint8_t counter1 = 0xFD;			 //Counter for real demostration
	//static uint8_t counter2 = 0xFE;
	GPIO_write_high(&PORTC,PC3);
	if (repeat>20){
		//Starts i2c with 1st addr-->wanting to write
		twi_start((humidity_addr<<1) + TWI_WRITE);
		//Writing 0x0 to the sensor with addr
		twi_write(counter);
		//Nothing else has to be sent
		twi_stop();
		TIM2_overflow_16ms();
		//After giving the	order to the slave we want to read
		twi_start((humidity_addr<<1) + TWI_READ);
		//Read the temperature integer part
		result=twi_read_nack();
		twi_stop();
		repeat=0;
		return result;
		//return result1<<8&result2;				Repeat the same to obtain two results and do a BitShift to sume them for Real Sensor
	}
	else{
		repeat++;
	}

	return data[4];

}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/

void PumpToggle(){
	data[2]=!data[2];
	if(data[2]==1){
		GPIO_write_high(&PORTD,1);
	}
	else{
		GPIO_write_low(&PORTD,1);
	}
}

void ValveSet(uint8_t openper){ //Set the opening range of valve % form
	TIM1_stop();
	setupServo(openper);
	lcd_init(LCD_DISP_ON);
	
	
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Read biutton state
 * Purpose:  Proccess the press of the button, by changing the data when is posible.
 * Returns:  The setting value the user wants to see.
 **********************************************************************/

uint8_t ReadKeys( uint8_t setting, int value){
	 
	uint8_t newset = setting;	

	if(value>80 && value<120){ //Up
		if(newset<1||newset>50){
			newset= 4;
		}
		else{
			newset = newset -1;		//UP is pressed 120. Change the display setting.
		}
		lcd_gotoxy(0,0);
		lcd_puts("                                                                                                       "); //Resets screen
	}
	
	if(value>200 && value< 300){ //DOWN
		if(newset>3){
			newset = 0;
		}
		else{
			newset= setting + 1;
		}
		lcd_gotoxy(0,0);
		lcd_puts("                                                                                                       "); //Resets screen
	}
	
	if(value>390 && value<430){ //LEFT //When left button is pressed 410.
		if (setting==1 && data[setting] != 0 ){
			data[setting]=data[setting]-5;	//If it is possible to effit the number is bigger than 5 decrease the value in jumps of 5
			ValveSet(data[setting]);
		}
		if(setting==2){
			PumpToggle();
		}
	}
	
	if(value < 80){ //Right
		if(data[setting] != 100 && setting==1){
			data[setting]=data[setting]+5;	//If it is possible to edit increase the value
			ValveSet(data[setting]);
		}
		if(setting==2){
			PumpToggle();
		}
	}
	return newset;
	
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/


uint16_t DistanceSensorValue(uint8_t FULL){
	if (repeat>20){
		repeat=0;
		data[0]= DistanceValue();
		lcd_gotoxy(0,1);
		lcd_puts("        ");
	}
	else{
		repeat++;
	}
	return data[0];
}




/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/

#define TRIG_PIN 1
#define ECHO_PIN 6

int main(void){
	
	
	// Configure ADC to convert PC0[A0] analog value
	lcd_init(LCD_DISP_ON);
	GPIO_config_output(&DDRD, PUMP_PIN);
	GPIO_config_output(&DDRB,PB5);
	GPIO_config_input_nopull(&DDRD,ECHO_PIN);
	
	// Set ADC reference to AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	// Set input channel to ADC0
	ADMUX &= ~(1<<MUX3|1<<MUX2|1<<MUX1|1<<MUX0);
	// Enable ADC module
	ADCSRA |= (1<<ADEN);
	// Enable conversion complete interrupt
	sei();
	twi_init();

	
	while(1){
		ADCSRA |= (1<<ADSC);
		setting=ReadKeys(setting, ADC);
		_delay_ms(200);
		Display(setting);			//Update the displayz
		if(check_period > 6){					//Even if the setting is not meassure all values in backgraunds every 40 loops (6*20/3)
			data[0]= DistanceSensorValue(FULL);
			data[3]=PressureGetValue();
			data[4]=HumidGetValue();
			check_period++;
		}
		else{
			check_period=0;
		}
	}
}



#define TRIG_PORT PORTB
#define TRIG_DDR  DDRD
#define ECHO_IN   PIND
#define ECHO_DDR  DDRD

int echoFlag = 0;
uint8_t loop = 0;
uint8_t pulse;
uint16_t distance = 0;




uint16_t DistanceValue(void)
{
	
	EIMSK |= (1<<INT0);	// enable INT0
	EICRA |= (1<<ISC00);// setting interrupt trigger on any change
	EICRA &= ~(1<<ISC01);
	
	TCCR2A = 0x00; //Configure Timer0 for normal mode and no waveform generation
	TCCR2B = 0x05; //Set prescaler value to clk/1024 and turn off forced output comparator
	sei();
	pulse=1;
	while(pulse){
		GPIO_write_high(&PORTB,5);
		_delay_us(15);						// trigger the ultrasonic module for 15usec
		GPIO_write_low(&PORTB,5);
		_delay_ms(500);	
	}
	return distance;
	
}



// This ISR is called automatically when a change on the INT0 pin happens due to the change of the echo pin from the ultrasonic module
ISR(INT0_vect)
{	
	//if the flag is 0, start timer2 with no pre-scaler
	if(echoFlag == 0) {
		TCCR2B |= (1<<CS20);
		echoFlag = 1;	//set flag to 1
	}
	else {
		distance = TCNT2;	//pulse takes values of counter
		TCCR2B = 0;	//stop timer
		TCNT2 = 0;		//reset counter
		echoFlag = 0;		//reset flag
		loop++;
		if (loop>5){
			EIMSK  &= ~(1<<INT0);	// disable INT0
			pulse=0;
		}
	}
	
}