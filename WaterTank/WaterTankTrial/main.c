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
#include <math.h>


uint8_t full = 10; //The size of the tank in hight [m]
//Data will store: Depth, Valve open %, Pump state, Pressure
uint8_t data[4]= {60,80,60,0};	//Array storing the sensors measured values
uint8_t setting = 1;	//Defines what the LCD while display


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: LCD Display
 * Purpose:  Shows the data the user wants.
 * Returns:  none
 **********************************************************************/
 void Display(uint8_t setting,uint8_t value){
	 
	 lcd_init(LCD_DISP_ON);
 
	 char lcd_string[2] = " ";
 
	 lcd_gotoxy(0,0);
	 lcd_puts("                                                                                                       "); //Resets screen

	 itoa(value,lcd_string,10);
	 lcd_gotoxy(0,1);
 
	 switch (setting)					//Defines the display of each setting
	 {
		 case 0:		//Depth
			lcd_puts(lcd_string);
			 lcd_gotoxy(0,0);
			 lcd_puts("Depth:");
			 lcd_gotoxy(5,1);
			 lcd_puts("cm");
			 break;
		 case 1:		//Valve open ratio
			 lcd_puts(lcd_string);
			 lcd_gotoxy(0,0);
			 lcd_puts("Valve:");
			 lcd_gotoxy(5,1);
			 lcd_puts("%");
			 break;
		 case 2:		//Pump state
			 if(value==1){
				 lcd_puts("On");
			 }
			 else{
				 lcd_puts("Off");
			 }
			 lcd_gotoxy(0,0);
			 lcd_puts("Pump:");
			 lcd_gotoxy(5,1);
			 lcd_puts("%");
			 break;
		 case 3:		//Pressure
			 lcd_puts(lcd_string);
			 lcd_gotoxy(0,0);
			 lcd_puts("Pressure:");
			 lcd_gotoxy(5,1);
			 lcd_puts("Pa");
			 break;
	 }

	 
 
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
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/

int PumpSet(uint8_t state){ //Set the pump
	GPIO_config_output(&DDRD, PUMP_PIN);
	GPIO_toggle(state,PUMP_PIN);
	if(state==1){
		GPIO_write_high(&PORTD, PUMP_PIN);
		}else{
		GPIO_write_low(&PORTD, PUMP_PIN);
	}
	return state;
}

void ValveSet(uint8_t openper){ //Set the opening range of valve % form
	setupServoTimer(&DDRB, SERVO_PIN);
	moveServoTimer(openper);
}

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Read biutton state
 * Purpose:  Proccess the press of the button, by changing the data when is posible.
 * Returns:  The setting value the user wants to see.
 **********************************************************************/

uint8_t ReadKeys( uint8_t setting, uint8_t *data[4]){

	uint8_t newset = setting;
	uint8_t value = 0;
	uint8_t sel;
	value = ADC;
	if (value>=50)
	{
		if (value>150)
		{
			if (value>300)
			{
				if (value<500)
				{							//When left button is pressed 450.
					if (setting=1 |data[setting]>3 ){
						*data[setting]=*data[setting]-5;	//If it is possible to effit the number is bigger than 5 decrease the value in jumps of 5
					}
					if(setting==2){
						PumpSet(data[2]);
					}
				}
			}
			else{							//When DOWN is pressed 250. Change the display setting.
				newset= setting +1;
				if(newset>3){
					newset = 0;
				}
			}
			
		}
		else{
			newset= setting -1;		//UP is pressed 120. Change the display setting.
			if(newset<0){
				newset= 3;
			}
		}
	}
	else{										//Right is pressed 0
		if(*data[setting]<98| setting==1){
			*data[setting]=*data[setting]+5;	//If it is possible to edit increase the value
		}
		if(setting==2){
			PumpSet(data[2]);
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
	return round(full - get_dist()/100);
}




/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update the values of distance and pressure.
 * Returns:  none
 **********************************************************************/
int main(void)
{
	//bme280_init();
	//init_ultrasonic_sensor();
	// Configure ADC to convert PC0[A0] analog value
	
	// Set ADC reference to AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	// Set input channel to ADC0
	ADMUX &= ~(1<<MUX3|1<<MUX2|1<<MUX1|1<<MUX0);
	// Enable ADC module
	ADCSRA |= (1<<ADEN);
	// Enable conversion complete interrupt
	ADCSRA |= (1<<ADIE);
	// Set clock prescaler to 128
	ADCSRA |= (1<<ADPS0 | 1<<ADPS1| 1<<ADPS2);
	// Configure 16-bit Timer/Counter1 to start ADC conversion
	// Set prescaler to 262 ms and enable overflow interrupt
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();
	// Enables interrupts by setting the global interrupt mask
	sei();
	
	while(1){
		Display(setting,data[setting]);			//Update the display
		
		//data[0] = DistanceSensorValue(full);		//Update the water level
		//data[3] = PressureGetValue(data[0]);		//Update the pressure at the bottom of the tank
		
		/*if(DistanceSensorValue >= full - 0,2){				//When tank is at the edge of overflow
			while(DistanceSensorValue >= full - 0,5){		//open valve to maintain it at 0,5m from overflow
				ValveSet(100);
			}
			ValveSet(data[1]);		//Return the valve to the preselected value
		}*/
		setting=ReadKeys(setting,*data);

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


ISR(TIMER1_OVF_vect)
{
	// Start ADC conversion
	ADCSRA |= (1<<ADSC);

}