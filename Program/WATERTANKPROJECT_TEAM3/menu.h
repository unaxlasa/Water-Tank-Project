/*
 * menu.h
 *
 * Created: 15/12/2021 11:03:08
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 


#ifndef MENU_H_
#define MENU_H_

/* Function declaration ----------------------------------------------*/
/**********************************************************************
 * Function: LCD Display
 * Purpose:  Shows the data the user wants.
 * Returns:  none
 **********************************************************************/

void Display(uint8_t setting, uint16_t data[], uint8_t FULL);

/* Function declarations ----------------------------------------------*/
/**********************************************************************
 * Function: Read button state
 * Purpose:  Proccess the press of the button, by changing the data when is posible.
 * Returns:  The setting value the user wants to see.
 **********************************************************************/
uint8_t ReadKeys( uint8_t setting, int value, uint16_t data []);


#endif /* MENU_H_ */