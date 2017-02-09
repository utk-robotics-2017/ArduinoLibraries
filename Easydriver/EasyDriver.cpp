/*
 EasyDiver.cpp - Arduino Library for EasyDriver 3.0 stepper driver board from Sparkfun.com  
 
 Based on:
 Stepper.cpp - - Stepper library for Wiring/Arduino - Version 0.4
 Original library     (0.1) by Tom Igoe.
 Two-wire modifications   (0.2) by Sebastian Gassner
 Combination version   (0.3) by Tom Igoe and David Mellis
 Bug fix for four-wire   (0.4) by Tom Igoe, bug fix from Noah Shibley  

  I wanted This library to be a simple drop-in replacement for the standard stepper lib.
     just change some defines and go!!

                                               Maken "at" maken.org      8/28/09
                                             
	Added stepAng() -Ben Johnson
*/


#include "Arduino.h"
#include "EasyDriver.h"

/*
* EasyDriver constructor.
* Sets Direction and Step Pins.
*/
EasyStepper::EasyStepper(int number_of_steps, int dir_pin, int step_pin, long inital_speed)
{
 this->step_number = 0;      // which step the motor is on
 this->direction = 0;      // motor direction
 this->last_step_time = 0;    // time stamp in ms of the last step taken
 this->number_of_steps = number_of_steps;    // total number of steps for this motor
 this->initial_speed = initial_speed;

 // Arduino pins for the motor control connection:
 this->dir_pin = dir_pin;
 this->step_pin = step_pin;

 // setup the pins on the microcontroller:
 pinMode(this->dir_pin, OUTPUT);
 pinMode(this->step_pin, OUTPUT);
 
 // set initial speed
 setSpeed(initial_speed);
}


/*
 Sets the speed in revs per minute
 Set between 0 and 100 probably
*/
void EasyStepper::setSpeed(long whatSpeed)
{
 this->step_delay = 60L * 1000L / this->number_of_steps / whatSpeed;
}

/*
 Moves the motor steps_to_move steps.  If the number is negative, 
  the motor moves in the reverse direction.
*/
void EasyStepper::step(int steps_to_move)
{  
 int steps_left = abs(steps_to_move);  // how many steps to take
 
 // determine direction based on whether steps_to_mode is + or -:
 if (steps_to_move > 0) {this->direction = 1;}
 if (steps_to_move < 0) {this->direction = 0;}
   
   
 // decrement the number of steps, moving one step each time:
 while(steps_left > 0) {
 // move only if the appropriate delay has passed:
 if (millis() - this->last_step_time >= this->step_delay) {
     // get the timeStamp of when you stepped:
     this->last_step_time = millis();
     // increment or decrement the step number,
     // depending on direction:
     if (this->direction == 1) {
       this->step_number++;
       if (this->step_number == this->number_of_steps) {
         this->step_number = 0;
       }
     } 
     else { 
       if (this->step_number == 0) {
         this->step_number = this->number_of_steps;
       }
       this->step_number--;
     }
     // decrement the steps left:
     steps_left--;
     // step the motor to step number 0, 1, 2, or 3:
     stepMotor(this->direction);
   }
 }
}

/*
* Moves the motor forward or backwards.
*/
void EasyStepper::stepMotor(int thisDir)
{
     digitalWrite(dir_pin, thisDir);
       delayMicroseconds(100);
       digitalWrite(step_pin, LOW);
     delayMicroseconds(100);
       digitalWrite(step_pin, HIGH);
       delayMicroseconds(100);
}

/*
* Steps based on angle in degrees (0-360)
* FIGURE OUT STEPS
*/
void EasyStepper::stepAng(long angle) {
	long s = number_of_steps;
	step(int(s*(angle/360.0))); // ugly, but works
}

/*
 version() returns the version of the library:
*/
int EasyStepper::version(void)
{
 return .01;
}
