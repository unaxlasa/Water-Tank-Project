/***********************************************************************
 * 

 * 
 **********************************************************************/

#define F_CPU 16000000
#define SERVO_PIN PB2
#define PUMP_PIN PD1

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "bme280.h"			//add Library to control the BME
#include "hc-sr04.h"
#include "gpio.h"
#include "servo.h"
#include <math.h>
#include <stdio.h>		/* Include std. library file */
#include <util/delay.h>		/* Include Delay header file */


uint8_t full = 100; //The size of the tank in hight [m]
//Data will store: Depth, Valve open %, Pump state, Pressure
uint16_t data[5]= {60,80,0,0,70};	//Array storing the sensors measured values
int8_t setting = 1;	//Defines what the LCD while display
uint8_t repeat=0;
uint8_t check_period =0;


//Function Declaration:
void main();
int8_t DistanceSensorValue(uint8_t full);
uint16_t PressureGetValue();
void Display(uint8_t setting);
void PumpToggle();
void ValveSet(uint8_t openper);
uint8_t ReadKeys( uint8_t setting, int value);
uint16_t HumidGetValue();


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
			 data[0] = DistanceSensorValue(full);		//Update the water level
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
			 lcd_gotoxy(2,1);
			 lcd_puts(" ");
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
	if (repeat>20){
		data[0]=DistanceSensorValue(full);
		TIM1_stop();
		bme280_init();
		float distance = bme280_readPressure(); //Presure in Pa
		TIM1_stop();
		lcd_init(LCD_DISP_ON);
		repeat=0;
		return round((data[0]-distance)*9.8); //Formula to get the pressure at the bottom of the tank (supposing 10m) [KPa]
	}
	else{
		repeat++;
	}
	return data[3];
}

uint16_t HumidGetValue(){
	if (repeat>10){
		float humid;
		TIM1_stop();
		bme280_init();
		//humid = bme280_readHumiditiy(); //Presure in Pa
		TIM1_stop();
		lcd_init(LCD_DISP_ON);
		repeat=0;
		if(humid>98){
			lcd_gotoxy(0,6);
			lcd_puts("RAIN!");
		}
		else{
			lcd_gotoxy(0,6);
			lcd_puts("      ");
		}
		return round(humid); //Formula to get the pressure at the bottom of the tank (supposing 10m) [KPa]
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
	setupServo(openper);
	GPIO_write_high(&PORTB,SERVO_PIN);
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


int8_t DistanceSensorValue(uint8_t full){
	if (repeat>10){
		repeat=0;
		TIM1_stop();
		init_ultrasonic_sensor();
		float distance = get_dist();
		TIM1_stop();
		lcd_init(LCD_DISP_ON);
		return round((full -distance)/10);
		
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
void main(void){
	init_ultrasonic_sensor();
	lcd_init(LCD_DISP_ON);
	GPIO_config_output(&DDRD, PUMP_PIN);
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

	
	while(1){
		
		ADCSRA |= (1<<ADSC);
		setting=ReadKeys(setting, ADC);
		_delay_ms(200);
		Display(setting);			//Update the displayz
		ValveSet(data[1]);
		
		if(check_period > 6){					//Even if the setting is not meassure all values in backgraunds every 20 loops (6*10/3)
			data[0]= DistanceSensorValue(full);
			data[3]=PressureGetValue();
			data[4]=HumidGetValue();
			check_period++;
		}
		else{
			check_period=0;
		}
	}
}


