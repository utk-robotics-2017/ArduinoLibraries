#include "Arduino.h"
#include "Motor.h"

Motor::Motor(char inA, char inB, char pwm, char reverse, MotorControllerType type)
{
  this->inA     = inA;
  this->inB     = inB;
  this->pwm     = pwm;
  this->reverse = reverse;
  this->type    = type;
}

void Motor::drive(int speed)
{
  if (reverse)
  {
    speed *= -1;
  }

  switch (type) {
  case MonsterMoto:
    digitalWrite(inA, speed > 0);
    digitalWrite(inB, speed < 0);
    analogWrite(pwm, abs(speed));
    break;

  case RoverFive:
    analogWrite(pwm, abs(speed));
    digitalWrite(inA, speed > 0);
    break;
  }
}

void Motor::stop()
{
  switch (type) {
  case MonsterMoto:
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
    analogWrite(pwm, 0);
    break;

  case RoverFive:
    analogWrite(pwm, 0);
    digitalWrite(inA, LOW);
    break;
  }
}
