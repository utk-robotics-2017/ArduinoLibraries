#ifndef MOTOR_h
#define MOTOR_h

#include <Arduino.h>
#include <Servo.h>

enum MotorControllerType {
	MonsterMoto,
	RoverFive,
    Vex,
    Mosfet
};

class Motor
{
public:
	Motor(char, char, char, char, MotorControllerType);
	void init();
    void drive(int);
	void stop();

private:
	char inA, inB, pwm, reverse;
	MotorControllerType type;

    // For Vex Motor Controller
    Servo servo;
};


#endif
