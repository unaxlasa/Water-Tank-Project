/***********************************************************************
 * 

 * 
 **********************************************************************/

#define F_CPU 16000000


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "bme280.h"			//add Library to control the BME
#include "hc-sr04.h"
#include "bme280.c"		
#include "hc-sr04.c"
#include <math.h>


uint8_t full = 10; //The size of the tank in hight [m]
//Data will store: Depth, Valve open %,
uint8_t data[4]= {60,80,60,0};	//Array storing the sensors measured values
uint8_t setting = 0;	//Defines what the LCD while display

bme280_init();
init_ultrasonic_sensor();
lcd_init(LCD_DISP_ON);


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: LCD Display
 * Purpose:  Shows the data the user wants.
 * Returns:  none
 **********************************************************************/
 void Display(uint8_t setting,uint8_t value){
 
 char lcd_string[2] = " ";
 
 lcd_gotoxy(0,0);
 lcd_puts("                                       "); //Resets screen

 itoa(value,lcd_string,10);
 
 switch (setting)					//Defines the display of each setting
 {
 case 0:		//Depth
 lcd_gotoxy(0,0);
 lcd_puts("Depth:");
 lcd_gotoxy(1,5);
 lcd_puts("cm");
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

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Get the value of the Pressure
 * Purpose:  Read the pressure at the bottom of the tank. Taking into account the water level
 * Returns:  The pressure at the bottom of the tank
 **********************************************************************/

uint8_t PressureGetValue(uint8_t waterlevel){
	float distance = bme280_readPressure(); //Presure in Pa
	return round((waterlevel-distance)*9800/1000); //Formula to get the pressure at the bottom of the tank (supposing 10m) [KPa]
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Read biutton state
 * Purpose:  Proccess the press of the button, by changing the data when is posible.
 * Returns:  The setting value the user wants to see.
 **********************************************************************/

uint8_t ReadKeys( uint8_t setting, uint8_t *data[4]){
	uint8_t newset;
	uint8_t value = ADC;
	uint8_t sel;
	if (value>=50)
	{
		if (value>150)
		{
			if (value>300)
			{
				if (value>500)
				{
					if(value<800){ 						// When Select button is pressed 70
						if(setting==1 | setting ==2 ){	//Button only works in certain settings
							sel++;
							if(sel>1){					//Safe the state of the button 1 == Active; 0 == INNACTIVE
								sel=0;
							}
							else{
								lcd_gotoxy(1,4);		//When sel=1 show an * in the value
								lcd_puts('---');
							}
						}
						
					}
				}
				else{								//When left button is pressed 450.
					if (sel){
						if(data[setting]>3){
							*data[setting]=*data[setting]-5;	//If it is possible to effit the number is bigger than 5 decrease the value in jumps of 5
						}
					}
				}
			}
			else{							//When DOWN is pressed 250. Change the display setting.
				newset= setting +1;
				if(newset>4){
					newset = 0;
				}
				if(!sel){					// if select has not been started change the displayed setting
					return newset;
				}
			}
			
		}
		else{
			newset= setting -1;		//UP is pressed 120. Change the display setting.
			if(newset<0){
				newset= 3;
			}
			if(!sel){				// if select has not been started change the displayed setting
				return newset;
			}
		}
	}
	else{										//Right is pressed 0
		if(*data[setting]<98){
			*data[setting]=*data[setting]+5;	//If it is possible to edit increase the value
		}
	}
	
	return setting;
	
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/


int8_t DistanceSensorValue(uint8_t full){
	return round(full - get_dist()/100);
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/

void PumpSet(uint8_t speed){ //Set the speed in a % form
	
}

void ValveSet(uint8_t openper){ //Set the opening range of valve % form

}


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/
int main(void)
{
	
	Display(setting,data[setting]);			//Update the display
	
	data[0] = DistanceSensorValue(full);		//Update the water level
	data[3] = PressureGetValue(data[0]);		//Update the pressure at the bottom of the tank
	
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
	setting= ReadKeys(setting,*data);	//analize the meaning of the pressed button
	ValveSet(data[1]);					//Update Valve status
	PumpSet(data[2]);					//Update pump status
}

