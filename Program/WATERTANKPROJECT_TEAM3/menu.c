/*
 * menu.c
 *
 * Created: 15/12/2021 11:02:10
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include <math.h>			// Math library. For calculations like round
#include <stdio.h>			// Include std. library file



/*Fuction definition.............................................................................................................*/

void Display(uint8_t setting, uint16_t data[], uint8_t FULL){
	
	char lcd_string[2] = " ";						// Creates a string
	lcd_gotoxy(0,1);
	
	switch (setting)						// Defines the display of each setting
	{
		case 0:										// Depth
		data[0] = DistanceSensorValue(FULL);		// Update the water level
		lcd_gotoxy(0,0);							// We go to the 0,0
		lcd_puts("Depth:");							// We write the text, in this case is Depth
		if(data[0]>=FULL){							// If the depth is the same as the full tank we write a message of FULL
				lcd_gotoxy(0,1);					// We move to the 0,1 position and we write the message
				lcd_puts("FULL");
		}else{
		lcd_gotoxy(0,1);						// If the value is not the same as the full tank, we write the depth in the 0,1 position
		itoa(data[setting],lcd_string,10);			// We transform the value from the data matrix into a string
		lcd_puts(lcd_string);				// We write the string
		lcd_gotoxy(3,1);		// As the value in real simulation is always going to be less or same as 400 is going to the 3 digits so we clean the 4th
		lcd_puts(" ");						// We write an space in the 3,1 position
		if(data[setting]<=999){					// We need to do some corrections, depending of the digits
			lcd_gotoxy(3,1);				// If the value is 3 digits we clean the 4th with a space
			lcd_puts(" ");
		}
		if(data[setting]<=99){
			lcd_gotoxy(2,1);				// If the value is 2 digits we clean the 3th with a space too
			lcd_puts(" ");
		}
		if(data[setting]<=9){
			lcd_gotoxy(1,1);				// If the value is 1 digit we clean the 2nd with a space too
			lcd_puts(" ");
		}
		lcd_gotoxy(5,1);
		lcd_puts("cm");						// We put the unit
		}
		break;
		
		case 1:							// Valve open ratio
		itoa(data[setting],lcd_string,10);			// The open percentage is stored in the data matrix, so we need to convert it into a string
		lcd_puts(lcd_string);					// Write the string
		if(data[setting]<=95){					// As the value increases from 5 to 5, if the value is higher than 95 we clean the 3th digit
			lcd_gotoxy(2,1);				// We put an space in the 2,1 position
			lcd_puts(" ");
		}
		if(data[setting]==5){					// If its 5 so its 1 digit, so we clean
			lcd_gotoxy(1,1);				// We put an space at 1,1 position
			lcd_puts(" ");
		}
		lcd_gotoxy(0,0);					// We write Valve in the 0,0 position
		lcd_puts("Valve:");
		lcd_gotoxy(5,1);					// We write the unit in the 5,1 position
		lcd_puts("%");
		break;
		
		case 2:						// Pump state
		itoa(data[setting],lcd_string,10);			// The pump state is stored in the data matrix, so we need to convert it into a string
		if(data[setting]==1){					// If it is 1, the pump is On, so we write On in the display
			lcd_puts("On ");

		}
		else{							// If it is 0, the pump is Off, so we write Off in the display
			lcd_puts("Off");
		}
		lcd_gotoxy(0,0);					// We go to the 0,0 position
		lcd_puts("Pump:");					// And we write Pump in that position
		break;
		
		case 3:							// Atmosphere Pressure
		data[3] = PressureGetValue(data, FULL);			// Update the pressure at the bottom of the tank
		itoa(data[setting],lcd_string,10);			// We convert it into a string
		lcd_puts(lcd_string);					// We write this string
		if(data[setting]<=999){					// If the value is 3 digits we clean the 4th one
			lcd_gotoxy(3,1);				// By putting a space at 3,1 position
			lcd_puts(" ");
		}
		if(data[setting]<=99){					// If the value is 2 digits we clean the 3th one
			lcd_gotoxy(2,1);				// By putting a space at 2,1 position
			lcd_puts(" ");
		}
		if(data[setting]<=9){					// If the value is 1 digit we clean the 2nd one
			lcd_gotoxy(1,1);				// By putting a space at 1,1 position
			lcd_puts(" ");
		}
		lcd_gotoxy(0,0);					// We got to the 0,0 position
		lcd_puts("Atmos Pressure:");				// We write the text
		lcd_gotoxy(5,1);					// We write the unit in the 5,1 position
		lcd_puts("KPa");
		break;
		
		case 4:							// Humidity
		data[4] = HumidGetValue(data, FULL);			// Update the humidity calling to the function
		lcd_gotoxy(0,0);					// We go to 0,0
		lcd_puts("Humid:");					// We write Humidity in that position
		if(data[setting]>=100){					// If the value is higher than 100% is going to RAIN
			lcd_gotoxy(0,1);				// We write a message in the 0,1 position
			lcd_puts("RAIN");
			lcd_gotoxy(5,1);				// We clean the unit
			lcd_puts(" ");
		}else{							// If not we write that value
		itoa(data[setting],lcd_string,10);			// We convert the value into a string
		lcd_gotoxy(3,1);					// As the value is always gong to be less than 3 digits we clean that digit
		lcd_puts(" ");						// We use a space
		lcd_gotoxy(0,1);
		lcd_puts(lcd_string);					// We write the string in the 0,1 position
		if(data[setting]<=99){					// If the humidity is less than 99%
		lcd_gotoxy(2,1);					// We clean the 2,1 position with a space
		lcd_puts(" ");
		}
		if(data[setting]<=9){					// If the humidity is less than 9%
		lcd_gotoxy(1,1);					// We clean the 1,1 position with a space
		lcd_puts(" ");
		}
		lcd_gotoxy(5,1);					// We got to the position 5,1
		lcd_puts("%");						// We write the unit
		}
		break;
		
		case 5:						// Pressure tank
		data[3] = PressureGetValue(data, FULL);			// Update the pressure of the atmosphere
		data[0] = DistanceSensorValue(FULL);			// Update the distance
		uint16_t relative = data[3]+(data[0]*9.8/100000);	// By using Bernoulli we calculate the pressure of the bottom of the tank
		itoa(relative,lcd_string,10);				// We convert it into a string
		lcd_puts(lcd_string);					// We write it in the 0,1 position
		if(data[setting]<=999){					// Like previously done we clean the digits depending on the values
			lcd_gotoxy(3,1);
			lcd_puts(" ");
		}
		if(data[setting]<=99){
			lcd_gotoxy(2,1);
			lcd_puts(" ");
		}
		if(data[setting]<=9){
			lcd_gotoxy(1,1);
			lcd_puts(" ");
		}
		lcd_gotoxy(0,0);
		lcd_puts("Tank Pressure:");							// We write the text in the 0,0 position
		lcd_gotoxy(5,1);									// We go to the 5,1 position
		lcd_puts("KPa");									// We write the unit
		
	}
}
/*Fuction definition.............................................................................................................*/

uint8_t ReadKeys( uint8_t setting, int value, uint16_t data[]){
	
	uint8_t newset = setting;									// We set a new variable called newsetting with will take the setting value

	if(value>80 && value<120){									// Up
		if(newset<1||newset>50){								// If the setting is zero and we push the up button, we return to setting 5
			newset= 5;
		}
		else{													// If not we decrease the value by one
			newset = newset -1;									//UP is pressed 120. Change the display setting.
		}
		lcd_gotoxy(0,0);										// We go to 0,0
		lcd_puts("                                                                                                       "); //Resets screen
	}
	
	if(value>200 && value< 300){								// DOWN
		if(newset>5){											// If newset is 5 and we push the button the value will increase by one, and enter
			newset = 0;											// The newset will be 0
		}
		else{													// If not we increase the value by one
			newset= setting + 1;
		}
		lcd_gotoxy(0,0);										// We go to 0,0 position
		lcd_puts("												                                                        "); //Resets screen
	}
	
	if(value>390 && value<430){									// LEFT, When left button is pressed 410.
		if (setting==1 && data[setting] != 0 ){					// If we are in the setting 1 and the value is not zero
			data[setting]=data[setting]-5;						// Decrease the value in jumps of 5
			ValveSet(data[setting]);							// Set the value
		}
		if(setting==2){											// If we are in the setting 2, pump state, we toggle the pump
			PumpToggle(data);
		}
	}
	
	if(value < 80){												// Right
		if(data[setting] != 100 && setting==1){					// If we are in setting 2, the valve state, and the value is not 100
			data[setting]=data[setting]+5;						// If it is possible to edit increase the value
			ValveSet(data[setting]);							// We set the valve
		}
		if(setting==2){											// If we are in the pump set
			PumpToggle(data);									// We set the pump
		}
	}
	return newset;												// We return the new setting
	
}
