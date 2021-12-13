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
In order to do this project we had to use several libraries, some of them from previous laboratory excercises. We had to add libraries for the servo motor, ultrasonic sensorand humidity, temperature and barometric sensor. We created our own library `servo.h` which you can find it [here](WaterTank/WaterTank/src/ServoC.h).

**Libraries from previous labs:**
* avr/io.h: AVR input/output definitions.
* [lcd.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/lcd.h): For using the LCD.
* [lcd_definitions.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/lcd_definitions.h): For defining the LCD parameters.
* [timer.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/timer.h): For difining timers.

**Added libraries:**
* [hc-sr04.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/hc-sr04.h): For using the ultrasonic sensor.
* [servo.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/servo.h): For controlling the servo motor.
* [bme280.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/bme280.h): For using the humidity sensor.


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

We created a library for the servo motor, [servo.h](https://github.com/unaxlasa/Water-Tank-Project/tree/main/WaterTank/WaterTankTrial/servo.h). Those are the functions in it:
&nbsp;
| FUNCTION NAME | PARAMETERS | RETURN | APPLICATION |         
|:-----------:|:------------------------------------:|:---:|:--:|
| `setupServoTimer()` | volatile uint8_t *reg_name, uint8_t pin_num | None |Set ups the pin as output an creates the PWM |
| `moveServoTimer()` | uint8_t porcentage | None | Moves the servo, changing the porcentage to values for the servo |

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



