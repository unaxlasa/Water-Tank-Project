/**
 * ServoC.cpp - A barebones servo library for Tower Pro SG-90 Servo Motor.
 *
 * A servomotor is a rotary actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration.
 * It consists of a suitable motor coupled to a sensor for position feedback. It also requires a relatively sophisticated controller, often a dedicated module designed specifically for use with servomotors.
 * Servomotors are not a specific class of motor although the term servomotor is often used to refer to a motor suitable for use in a closed-loop control system..(Ref : https://en.wikipedia.org/wiki/Servomotor)
 * 
 * For more information about Servo Motor and SG-90 , do check out this link (https://components101.com/servo-motor-basics-pinout-datasheet).
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */

#define min_angle 0  // Minimum Servo angle
#define max_angle 180  // Maximum servo angle
#define min_pulse_width 540   // 540 uS : PulseWidth for on-pulse to write 0 degree angle on servo
#define max_pulse_width 2450   //2450 uS : PulseWidth for on-pulse to write 180 degree angle on servo

#include "ServoC.h"
#include "Arduino.h"

void ServoC::attach(int servo_pin)
{
	this->servopin = servo_pin;
	pinMode(this->servopin, OUTPUT);
}

void ServoC::write(int angle)
{
	angle=constrain(angle,min_angle,max_angle);  // Constraining the angle to avoid motor cluttering due to unusual pulses at higher angles
  	delay_time=map(angle,min_angle,max_angle,min_pulse_width,max_pulse_width);  // Boundaries to be calibrated by trial and error
  	digitalWrite(this->servopin,HIGH);
  	delayUs(delay_time);
  	digitalWrite(this->servopin,LOW);
  	delayUs((20000-delay_time));  // Because servo sg90 requires a total pulse of 20mS with proper duty cycle
}

void ServoC::delayUs(unsigned long uS)
{
	unsigned long time_now = micros();
    	while(micros() < time_now + uS);
}

