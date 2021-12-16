# Water-Tank-Project 🚰

<p align="center">
  <img width="600" height="400" src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/water-tank.jpg">
</p>

### Team members
[Ander Marin](https://github.com/andermarin), [Unai Telletxea](https://github.com/UTAN25), [Dogancan Gurbuz](https://github.com/DogancanG) and [Unax Lasa](https://github.com/unaxlasa)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Here](https://github.com/unaxlasa/Water-Tank-Project/blob/main/README.md) the link to the Readme file.
https://github.com/unaxlasa/Water-Tank-Project

## Project objectives
The objective of this project is to control a water tank using ATMega328p microcontroller and C language . In order to do so, we have to use some sensor to measure the level of the water, check the rain. Also, we are going to use a water-pump, when the level of the water is low, we will pump water into the tank. We will have a butterfly valve at the output pipe, in order to regulate the water flow. We will have a LCD to display and manipulate all the variables of the tank.
## Circuit Diagram and Flowchart
**Circuit Diagram**

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/Schema.png)

**Here the flowcharts of our programm:**
Firstly, the flowchart of the main:

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/FlowChartMain.drawio.png">
</p>

Here the flowchart of the ISR of the main programme:

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/ISR.drawio.png">
</p>

Finally, the flowcharts of two of the most important functions:

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/Menu.drawio.png">
</p>

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/Buttons.drawio.png">
</p>

## Hardware description
- 1x Microcontroller (ATMega328p)
- 1x Ultrasonic sensor (HC-SR04)
- 1x Humidity, temperature and barometric sensor (I2C BME280)
- 1x Micro servo (SG-90)
- 1x LCD

*Connections:*

![your figure](https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/Connections.jpeg)

## Code description and simulations
In order to do this project we had to use several libraries, some of them from previous laboratory excercises. We had to add libraries for the servo motor, ultrasonic sensorand humidity, temperature and barometric sensor. We created our own libraries to use them, based on libraries we found on the internet.

**Libraries from previous labs:**
* avr/io.h: AVR input/output definitions.
* avr/interrupt.h: For AVR-GCC standard interruptors.
* stdlib.h: For conversion functions-
* gpio.h: For configuration and manipulation of I/O.
* math.h: For mathematical operations. 
* stdio.h: For variables and I/O functions.
* util/delay.h: For dalays.
* [lcd.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/lcd.h): For using the LCD.
* [lcd_definitions.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/lcd_definitions.h): For defining the LCD parameters.
* [timer.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/timer.h): For difining timers.
* [conf_board.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/conf_board.h): For configurating the board.
* [i2c.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/i2c.h): For serial comunication.
* [twi.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/twi.h): For serial comunication.


**Added libraries:**
* [hc-sr04.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/hc-sr04.h): For using the ultrasonic sensor.
* [servo.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/servo.h): For controlling the servo motor.
* [bme280.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/bme280.h): For using the humidity sensor.
* [menu.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/menu.h): To control the menu.
* [pump.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/pump.h): To control the pump.
* [valve.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/valve.h): To control the valve.


We use all 3 timers in our project, in the table below you can see why and with which prescaler we use the them,
&nbsp;
|           TIMER          | PRESCALER | REASON |        
|:------------------------:|:------------------------------------:|:---:|
|      `Timer/Counter0`      |   16.384ms  |  In order to create a PWM pulse to control the microservo-motor. |
|      `Timer/Counter1`      |   4.096ms   |  For the LCD. |
|      `Timer/Counter2`      |   16ms  |  In order to count the time of the ultrasonic echo. |



Those are some functions we created for the programme.
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `ValveSet()` | uint8_t openper | None | Moves the servo motor to the porcentage introduced  |
| `DistanceSensorValue()` | uint8_t FULL | int16_t | Update the values of distance. |
| `DistanceValue()` | None | uint16_t | Measures the distance. | 

We created a library for the menu, [menu.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/menu.h)
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `Display()` |   uint8_t setting, uint8_t value, uint16_t data[]   | None | Displays different display settings. |
| `ReadKeys()` | uint8_t setting, uint8_t data[], int value | uint8_t newset | Proccess the press of the button, by changing the data when is posible. |

We created a library to control de pump, [pump.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/pump.h)
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `PumpToggle()` | uint16_t data[] | None | Swiches the state of the pump. |

We created a library to control the valve, [valve.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank-2/WaterTankTrial/valve.h)
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `ValveSet()` | uint8_t openper | None | Moves the valve to the porcentage indicated. |


We created a library for the servo motor, [servo.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/servo.h). 
Those are the functions in it that we used:
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `setupServo()` | vuint8_t porcentage | None |Set ups the pin as output an creates the PWM in order to move the microservo motor. |

This are functions we used for the ultrasonic sensor, here the library [hc-sr04.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/hc-sr04.h).
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `init_ultrasonic_sensor()` | None | None | Initialize the ultrasonic sensor. |
| `get_dist()` | None | float dist | The sensor is always making the measurement, when we activate this function we get the value of it. | 

This are functions we used for the humidity sensor, here the library [bme280.h](https://github.com/unaxlasa/Water-Tank-Project/blob/main/Program/WATERTANKPROJECT_TEAM3/bme280.h).
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `PressureGetValue()`| uint16_t data[],uint8_t FULL | uint16_t | Gets the preassure value. |
| `HumidGetValue()`| uint16_t data[],uint8_t FULL | uint16_t | Gets the humidity value. |

## Simulation of Watertank
Here the schema we did on [simulIDE](https://www.simulide.com/p/home.html):

<p align="center">
  <img src="https://github.com/unaxlasa/Water-Tank-Project/blob/main/img/Eskema.PNG">
</p>

* PUMP:

![PUMP](https://github.com/unaxlasa/Water-Tank-Project/blob/main/gifs/PUMP.gif)

* VALVE SET:

![VALVE SET](https://github.com/unaxlasa/Water-Tank-Project/blob/main/gifs/VALVE%20SET.gif)

* MENU:

![MENU](https://github.com/unaxlasa/Water-Tank-Project/blob/main/gifs/MENU.gif)

## References
1) [FlowchartMaker](https://app.diagrams.net/)
2) [simulIDE](https://www.simulide.com/p/home.html)
3) [Ultrasonic I](https://www.arxterra.com/11-atmega328p-external-interrupts/)
4) [Ultrasonic II](https://www.avrfreaks.net/forum/atmega328p-and-hc-sr04?skey=atmega328p%20sr04%20INT0)
5) [Servo I](https://ee-diary.blogspot.com/2021/07/atmega328p-fast-pwm-mode-programming.html)
6) [Servo II](https://www.laboratoriogluon.com/generar-senal-pwm-para-servo-con-avr-atmega328p/)


