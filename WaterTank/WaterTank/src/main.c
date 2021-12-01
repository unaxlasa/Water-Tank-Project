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

#define uint8_t full = 10; //The size of the tank in hight [m]


uint8_t data[4]=;	//Array storing the sensors meassured values
uint8_t setting = 0;	//Defines what the LCD whil display

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/
int main(void)
{
	setting = ButtonGetUpDown(setting);
	
	Display(setting,data[setting]);
	
	setting[0] = DistanceSensorValue();
	setting[3] = PressureGetValue();
	
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
ISR() //When the keypad is touched start the interrupt
{

}

void Display(setting,value){
	
	char lcd_string[2] = "  ";
	
	lcd_gotoxy(0,0);
	lcd_puts("                                       "); //Resets screen
	
	itoa(value,lcd_string,10);
	
	switch (setting)
	{
	case 0:		//Depth
		lcd_gotoxy(0,0);
		lcd_puts("Depth:");
		break;
	case 1:		//Valve open ratio
		lcd_gotoxy(0,0);
		lcd_puts("Valve:");
		break;
	case 2:		//Pump speed
		lcd_gotoxy(0,0);
		lcd_puts("Pump:");
		break;
	case 3:		//Pressure
		lcd_gotoxy(0,0);
		lcd_puts("Pressure:");
		break;
	}
	lcd_gotoxy(1,0);
	lcd_puts(lcd_string);
	
}

int8_t ButtonGetUpDown(currentset){	//Set the setting mode of the display hen button is pressed 
	int8_t newset
	value = ADC;                  // Copy ADC result to 16-bit variable
	if(value>240){
		newset= currentset + 1;
		
	if(value>1000){
		newset=currentset -1;
		
	if(newset<0){return 3;}
	if(newset>4){return 0;}
	return newset;
}

int8_t DistanceSensorValue(){
	
}

int8_t PressureGetValue(distance){
	
	
	return (full-distance)*9,8; //Formula to get the pressure at the bottom of the tank (supposing 10m) [KPa]
}

void PumpSet(speedper){ //Set the speed in a % form
	
}

void ValveSet(openper){ //Set the opening range of valve % form
	
}

int8_t ReadKeypad(){
	 if (value>=50)
	 {
		 if (value>150)
		 {
			 if (value>300)
			 {
				 if (value>500)
				 {
					 if (value>800)
					 {
						 return ;
					 }
					 else{ return ;}
				 }
				 else{return ; }
			 }
			 else{return ;}
		 }
		 else{return ; }
	 }
	 else{ return ; }
}