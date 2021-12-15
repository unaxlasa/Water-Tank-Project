# Water-Tank-Project 🚰

<p align="center">
  <img width="600" height="400" src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/water-tank.jpg">
</p>

### Team members
[Ander Marin](https://github.com/andermarin), [Unai Telletxea](https://github.com/UTAN25), [Dogancan Gurbuz](https://github.com/DogancanG) and [Unax Lasa](https://github.com/unaxlasa)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Here](https://github.com/unaxlasa/Water-Tank-Project/blob/main/README.md) the link to the Readme file.

## Project objectives
The objective of this project is to control a water tank using ATMega328p microcontroller and C language . In order to do so, we have to use some sensor to measure the level of the water, check the rain. Also, we are going to use a water-pump, when the level of the water is low, we will pump water into the tank. We will have a butterfly valve at the output pipe, in order to regulate the water flow; if its raining the valve woul be half open (45º), if the tank is full the valve will be full open (90º). We will have a LCD to display and manipulate all the variables of the tank.
## Circuit Diagram and Flowchart
**Circuit Diagram**

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Schema.png)

**Here the flowchart of our programm:**

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/Flowchart.drawio.png">
</p>

## Hardware description
- 1x Microcontroller (ATMega328p)
- 1x Ultrasonic sensor (HC-SR04)
- 1x Humidity, temperature and barometric sensor (I2C BME280)
- 1x Micro servo (SG-90)
- 1x LCD

*Connections:*

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Connections.jpeg)

## Code description and simulations
In order to do this project we had to use several libraries, some of them from previous laboratory excercises. We had to add libraries for the servo motor, ultrasonic sensorand humidity, temperature and barometric sensor. We created our own library `servo.h` which you can find it [here](WaterTank/WaterTank/src/ServoC.h).

**Libraries from previous labs:**
* avr/io.h: AVR input/output definitions.
* avr/interrupt.h: For AVR-GCC standard interruptors.
* stdlib.h: For conversion functions-
* gpio.h: For configuration and manipulation of I/O.
* math.h: For mathematical operations. 
* stdio.h: For variables and I/O functions.
* util/delay.h: For dalays.
* [lcd.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/lcd.h): For using the LCD.
* [lcd_definitions.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/lcd_definitions.h): For defining the LCD parameters.
* [timer.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/timer.h): For difining timers.
* [conf_board.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/conf_board.h): For configurating the board.


**Added libraries:**
* [hc-sr04.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/hc-sr04.h): For using the ultrasonic sensor.
* [servo.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/servo.h): For controlling the servo motor.
* [bme280.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/bme280.h): For using the humidity sensor.


We use all 3 timers in our project, in the table below you can see why and with which prescaler we use the them,
&nbsp;
|           TIMER          | PRESCALER | REASON |        
|:------------------------:|:------------------------------------:|:---:|
|      `Timer/Counter1`      |    ms    |                         |
|      `Timer/Counter1`      |    ms    |                         |




Those are some functions we created for the programme.
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
|      `Display()`      |   uint8_t setting,uint8_t value    | None | Displays different display settings. |
|      `PressureGetValue()`      |   uint8_t waterlevel  | uint8_t  | Returns the pressure value at the bottom of the tank.  |
| `PumpSet()` | uint8_t state |  None |  Update the values of distance and pressure. |
| `ValveSet()` | uint8_t openper | None | Moves the servo motor to the porcentage introduced  |
| `ReadKeys()` | uint8_t setting, uint8_t *data[4], int value | uint8_t newset | Proccess the press of the button, by changing the data when is posible. |
| `DistanceSensorValue()` | uint8_t full | int8_t | Update the values of distance and pressure. |

We created a library for the servo motor, [servo.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/servo.h). 
Those are the functions in it that we used:
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `setupServoTimer()` | volatile uint8_t *reg_name, uint8_t pin_num | None |Set ups the pin as output an creates the PWM |
| `moveServoTimer()` | uint8_t porcentage | None | Moves the servo, changing the porcentage to values for the servo |

We found some libraries on the internet, in order to control the sensors:

This are functions we used for the ultrasonic sensor, here the library [hc-sr04.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/hc-sr04.h).
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `init_ultrasonic_sensor()` | None | None | Initialize the ultrasonic sensor. |
| `get_dist()` | None | float dist | The sensor is always making the measurement, when we activate this function we get the value of it. | 

This are functions we used for the humidity sensor, here the library [bme280.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/bme280.h).
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| | | | |

## Simulation of Watertank
Here the schema we did on [simulIDE](https://www.simulide.com/p/home.html):

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/Eskema.PNG">
</p>

* If it is rainy:


* If the tank empty:


* If the tank full:


## References
1) [FlowchartMaker](https://app.diagrams.net/)
2) [simulIDE](https://www.simulide.com/p/home.html)
3) 
4) 
5) 
6) 
7) [ASCII](https://www.asciitable.com/)



