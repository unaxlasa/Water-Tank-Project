# Water-Tank-Project 🚰

### Team members
[Ander Marin](https://github.com/andermarin), [Unai Telletxea](https://github.com/UTAN25), [Dogancan Gurbuz](https://github.com/DogancanG) and [Unax Lasa](https://github.com/unaxlasa)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Readme.md

[Here](https://github.com/unaxlasa/Water-Tank-Project/blob/main/README.md) the link to the Readme file.

### Project objectives
The objective of this project is to control a water tank using ATMega328p microcontroller and C language . In order to do so, we have to use some sensor to measure the level of the water, the rain and the pump of the scape pump.
![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Schema.png)
## Circuit Diagram and Flowchart
**Circuit Diagram**

**Here the flowchart of our programm:**

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Flowchart.drawio.png)

## Hardware description

- 1x Microcontroller (ATMega328p)
- 1x Ultrasonic sensor (HC-SR04)
- 1x Humidity, temperature and barometric sensor (I2C BME280)
- 1x Micro servo (SG-90)
- 1x LCD
- 1x 4x4 Matrix keypad

## Code description and simulations

#### Libraries from previous labs:

* [i2c.c](WaterTank/WaterTank/src/i2c.c)
* [i2c.h](WaterTank/WaterTank/src/i2c.h)
* [lcd.c](WaterTank/WaterTank/src/lcd.c)
* [lcd.h](WaterTank/WaterTank/src/lcd.h)
* [lcd_definitions.h](WaterTank/WaterTank/src/lcd_definitions.h)
* [timer.h](WaterTank/WaterTank/src/timer.h) 

#### Own libraries:
* [hc-sr04.c](WaterTank/WaterTank/src/hc-sr04.c)
* [hc-sr04.h](WaterTank/WaterTank/src/hc-sr04.h)
* [ServoC.cpp](WaterTank/WaterTank/src/ServoC.cpp)
* [ServoC.h](WaterTank/WaterTank/src/ServoC.h)
* [bme280.c](WaterTank/WaterTank/src/bme280.c)
* [bme280.h](WaterTank/WaterTank/src/bme280.h)
* [conf_board.h](WaterTank/WaterTank/src/conf_board.h)

## Software


## Simulation of Watertank
* -1) If it is rainy:


* -2) If the tank empty:


* -3) If the tank full:


## References
1) [What is flowchart?](https://www.breezetree.com/articles/what-is-a-flow-chart)
2) ...
3) ...
4) ...
5) ...
6) ...
7) [ASCII](https://www.asciitable.com/)



