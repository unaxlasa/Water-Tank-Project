# Water-Tank-Project 🚰

### Team members
[Ander Marin](https://github.com/andermarin), [Unai Telletxea](https://github.com/UTAN25), [Dogancan Gurbuz](https://github.com/DogancanG) and [Unax Lasa](https://github.com/unaxlasa)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
### Readme.md

[Here](https://github.com/unaxlasa/Water-Tank-Project/blob/main/README.md) the link to the Readme file.

### Project objectives
The objective of this project is to control a water tank using ATMega328p microcontroller and C language . In order to do so, we have to use some sensor to measure the level of the water while it is empty or filling the tank during the day, the sensors checked it is rainy or not. If the tank full the system close the pump till the water level decreased. It is the same situation about valve, if the tank empty the valve is closed till the water level increased. If it is rain the valve stay half open.

## Circuit Diagram and Flowchart
**Circuit Diagram**

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Schema.png)

**Here the flowchart of our programm:**

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Flowchart.drawio.png)

## Hardware description
- 1x Microcontroller (ATMega328p)
- 1x Ultrasonic sensor (HC-SR04)
- 1x Humidity, temperature and barometric sensor (I2C BME280)
- 1x Micro servo (SG-90)
- 1x LCD

## Code description and simulations
In order to do this project we had to use several libraries, some of them from previous laboratory excercises. We had to create libraries for the servo motor, ultrasonic sensorand humidity, temperature and barometric sensor.

**Libraries from previous labs:**
* [i2c.c](WaterTank/WaterTank/src/i2c.c):
* [i2c.h](WaterTank/WaterTank/src/i2c.h):
* [lcd.c](WaterTank/WaterTank/src/lcd.c):
* [lcd.h](WaterTank/WaterTank/src/lcd.h):
* [lcd_definitions.h](WaterTank/WaterTank/src/lcd_definitions.h):
* [timer.h](WaterTank/WaterTank/src/timer.h):

**Own libraries:**
* [hc-sr04.c](WaterTank/WaterTank/src/hc-sr04.c):
* [hc-sr04.h](WaterTank/WaterTank/src/hc-sr04.h):
* [ServoC.cpp](WaterTank/WaterTank/src/ServoC.cpp):
* [ServoC.h](WaterTank/WaterTank/src/ServoC.h):
* [bme280.c](WaterTank/WaterTank/src/bme280.c):
* [bme280.h](WaterTank/WaterTank/src/bme280.h):
* [conf_board.h](WaterTank/WaterTank/src/conf_board.h):

&nbsp;

We use all 3 timers in our project, in the table below you can see why and with which prescaler we use the them,
|           TIMER          | PRESCALER | REASON |
|:------------------------:|:---------:|:---------------------------------------------------------------------------------------------------------------------------------------------------|
|      `Timer/Counter0`      |    4ms    | For scanning the keypad at every overflow,  and configure the sytem according the pressed key.                                                     |
|      `Timer/Counter1`      |     1s    | For creating counters (5s and 3s) which is used in the application,  for example it starts counting to 5 after the user start typing the password. |
|      `Timer/Counter2`      |    16ms   | To create PWM signals for buzzer and the door bell.                                                                                                |

&nbsp;

## Software


## Simulation of Watertank
* If it is rainy:


* If the tank empty:


* If the tank full:


## References
1) [What is flowchart?](https://www.breezetree.com/articles/what-is-a-flow-chart)
2) [FlowchartMaker](https://app.diagrams.net/)
3) ...
4) ...
5) ...
6) ...
7) [ASCII](https://www.asciitable.com/)



