/***********************************************************************
 * 

 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "bme280.h"			//add Library to control the BME
#include "hc-sr04.h"
uint8_t full = 10; //The size of the tank in hight [m]


uint8_t data[4];	//Array storing the sensors measured values
uint8_t setting = 0;	//Defines what the LCD while display

bme280_init();
init_ultrasonic_sensor();


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/
int main(void)
{
	setting = ReadKeys(setting);
	
	Display(setting,data[setting]);
	
	data[0] = DistanceSensorValue();
	data[3] = PressureGetValue(full);
	
	if(DistanceSensorValue >= full - 0,2){				//When tank is at the edge of overflow
		while(DistanceSensorValue >= full - 0,5){		//open valve to maintain it at 0,5m from overflow
			ValveSet(100);
		}
		ValveSet(data[1]);		//Return the valve to the preselected value
	}

}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD display every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(ADC_vect) //When the keypad is touched start the interrupt
{
	setting= ReadKeys(setting,data);
}

void Display(uint8_t setting,uint8_t value){
	
	char lcd_string[2] = " ";
	
	lcd_gotoxy(0,0);
	lcd_puts("                                       "); //Resets screen
	
	itoa(value,lcd_string,10);
	
	switch (setting)
	{
	case 0:		//Depth
		lcd_gotoxy(0,0);
		lcd_puts("Depth:");
		lcd_gotoxy(1,5);
		lcd_puts("m");
		break;
	case 1:		//Valve open ratio
		lcd_gotoxy(0,0);
		lcd_puts("Valve:");
		lcd_gotoxy(1,5);
		lcd_puts("%");
		break;
	case 2:		//Pump speed
		lcd_gotoxy(0,0);
		lcd_puts("Pump:");
		lcd_gotoxy(1,5);
		lcd_puts("%");
		break;
	case 3:		//Pressure
		lcd_gotoxy(0,0);
		lcd_puts("Pressure:");
		lcd_gotoxy(1,5);
		lcd_puts("Pa");
		break;
	}
	lcd_gotoxy(1,0);
	lcd_puts(lcd_string);
	
}

int ButtonGetUpDown(uint8_t currentset){	//Set the setting mode of the display hen button is pressed 
	int8_t newset;
	value = ADC;                  // Copy ADC result to 16-bit variable
	if(value>240){
		newset= currentset + 1;
		
	if(value>1000){
		
		
	if(newset<0){return 3;}
	if(newset>4){return 0;}
	return newset;
}

int8_t DistanceSensorValue(){
	return round(10 - measureDistanceCm()/100);
}

uint8_t PressureGetValue(uint8_t full){
	float distance = bme280_readPressure(); //Presure in Pa
	
	return round((full-distance)*9800/1000); //Formula to get the pressure at the bottom of the tank (supposing 10m) [KPa]
}

void PumpSet(uint8_t speed){ //Set the speed in a % form
	
}

void ValveSet(uint8_t openper){ //Set the opening range of valve % form
	
}

int8_t ReadKeys( int8_t setting, uint8_t *data[4]){
	int8_t newset;
	int8_t sel;
	if (value>=50)
	{
		if (value>150)
		{
			if (value>300)
			{
				if (value>500)
				{
					if(value<800){ 						// When select button is pressed 700
						if(setting==1 | setting ==2 ){	//Button only works in certain settings
							sel++;
							if(sel>1){
								sel=0;
							}
							else{
								lcd_gotoxy(1,4);		//When sel=1 show an * in the value
								lcd_puts(¨*¨);
							}
						}
						
					}
				}
				else{								//When left button is pressed 450
					if (sel){
						if(data[setting]>5){
							*data[setting]=*data[setting]-5;	//If the number is bigger tha 5 decrease the value in jumps of 5
						} 
					}
			}
			else{							//When DOWN is pressed 250
				newset=currentset +1;
				if(newset>4){
					newset = 0;
				}
				if(!sel){					// if select has not been started change the displayed setting
					return newset;
				}
				
		}
		else{
			newset=currentset -1;		//UP is pressed 120
			if(newset<0){
				newset= 3;
			}
			if(!sel){				// if select has not been started change the displayed setting
				return newset;
			}
	}
	else{					//Right is pressed 0
		if(*data[setting]>5){
			*data[setting]=*data[setting]-5;
		} 
	}
	
	return setting;
		
}