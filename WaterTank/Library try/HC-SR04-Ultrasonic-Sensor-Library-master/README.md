# HC-SR04 Ultrasonic sensor library

This is a easy header-only C library for the HC-SR04 Ultrasonic sensor.

## Sensor details

|                     |                                  |
| ------------------- | :------------------------------: |
| Operating voltage   |          5 V (+/- 10 %)          |
| Current             |      ~ 2 mA per measurement      |
| Signal level        |               TTL                |
| max. distance       |            ~ 3000 mm             |
| min. distance       |             ~ 20 mm              |
| Ultrasonic capsules |    2 (transmitter, receiver)     |
| Precision           |              ~ 3 mm              |
| Pin                 | 1: Vcc 2: Trigger 3: Echo 4: GND |

## How the measurement works

The distance measurement get started with a falling edge on the trigger Pin (2). The previous high-signal must be at least 10 microseconds long. When the ultrasonic sensor detected the trigger signal, it sends after about 250 microseconds a 40 kHz burst-signal for a time period of 250 microseconds. After that, the Echo pin (3) get on high-level. Until the ultrasonic echo received, the echo pin (3) change from high to low. Next measurement can be triggered after 20 milliseconds.

## Calculating distance from echo

At 20 °C, the speed of sound is roughly 343 m/s. The distance of a sound signal can be calculated with the following equastion:

> Distance = Speed \* Time

But that is not the full result to calculate the measured distance from the sensor. The distance between the sensor and the object is actually only half the distance because the signal waves traveled from the sensor to the object and back from the object to the sensor. With the following equation, the distance can be calculated:

> Distance \[mm\] = Speed of sound \[mm/us\] \* Time \[us\] / 2

## Temperature dependence of the speed of sound

The speed of sound actually depends significant on temperature and to a far lesser degree on the humidity of the air. The speed of sound increases with nearly 0.6 m/s per degree Celcius [1]. For most cases at 20 °C the assumption of 343 m/s is a quite well choice. For more accurate measurement, the following equation can be used:

> v = 331.3 + (0.606 \* T)
>
> \[v\] Speed of sound in m/s \
> \[T\] Air temperature in °C

For accurate measurements the HC-SR04 can be used together with the DHT11 temperature and humidity sensor.

## Important notes

This code contain hardware depended code for Atmega microcontrollers. This library uses the 16-bit **TIMER1** for calculating delays. If you need the **TIMER1** somewhere else in your project, this part of the code have to be changed. This library configurate the Trigger pin on **PORTB2** you can change this to a other pin at the define section in _hc_sr04.c_.

```c
...
#define HCSR_TRIGGER PORTB2
#define HCSR_TRIGGER_PORT PORTB
#define HCSR_TRIGGER_DDR DDRB
...
```

# Example

A short example of how to use this library, getting measured distance.

```c
#include <avr/io.h>
#include <util/delay.h>
#include "hcr-sr04.h"

int main() {

    init_ultrasonic_sensor();

    float distance = null;

    while(1) {
        distance = get_dist();
        delay_ms(100);
    }

    return 0;
}
```

[1]: https://en.wikipedia.org/wiki/Speed_of_sound
