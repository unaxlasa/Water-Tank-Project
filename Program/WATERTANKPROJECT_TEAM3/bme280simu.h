/*
 * bme280simu.h
 *
 * Created: 15/12/2021 11:15:18
 *  Author: Ander Marin, Unai Telletxea, Dogancan Gurbuz and Unax Lasa
 */ 


#ifndef BME280SIMU_H_
#define BME280SIMU_H_

/* Function declaration ----------------------------------------------*/
/**********************************************************************
 * Function: Get the value of the Pressure
 * Purpose:  Read the pressure at the bottom of the tank. Taking into account the water level
 * Returns:  The pressure at the bottom of the tank
 **********************************************************************/
uint16_t PressureGetValue(uint16_t data[],uint8_t FULL);

/* Function declarations ----------------------------------------------*/
/**********************************************************************
 * Function: Get the value of the Humidity
 * Purpose:  Read the humidity, to see if it rains
 * Returns:  Humidity
 **********************************************************************/
uint16_t HumidGetValue(uint16_t data[],uint8_t FULL);


#endif /* BME280SIMU_H_ */