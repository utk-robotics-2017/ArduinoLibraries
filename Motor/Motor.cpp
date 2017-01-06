#include "Motor.h"

Motor::Motor(char inA, char inB, char pwm, char reverse, MotorControllerType type)
{
  this->inA     = inA;
  this->inB     = inB;
  this->pwm     = pwm;
  this->reverse = reverse;
  this->type    = type;
}

void Motor::init()
{
    if(type == Vex)
    {
        Serial.println(servo.attach(pwm));
    }
    else
    {
        if(inA > -1)
        {
            pinMode(inA, OUTPUT);
        }
        if(inB > -1)
        {
            pinMode(inB, OUTPUT);
        }
        if(pwm > -1)
        {
            pinMode(pwm, OUTPUT);
        }
    }
    stop();
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

  // Use the Servo instead...
  case Vex:
    Serial.println(speed);
    Serial.println(servo.attached());
    speed = speed * 500 / 1024 + 1500;
    servo.write(speed);
    break;

  case Mosfet:
    digitalWrite(inA, HIGH);
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

  case Vex:
    servo.write(1500);
    break;

  case Mosfet:
    digitalWrite(inA, LOW);
    break;
  }
}
