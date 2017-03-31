#ifndef POSITIONCONTROLLEDMOTOR_H
#define POSITIONCONTROLLEDMOTOR_H

#include "Motor.h"
#include "I2CEncoder.h"
#include "PID.h"

class PositionControlledMotor
{
public:
  PositionControlledMotor(Motor&, I2CEncoder&, PID&, double* input, double* output, double* setpoint);

  void setValue(int);
  void setPosition(double);
  double getPosition();
  
  void stop();
  
  void runPID();

private:
  Motor* motor;
  I2CEncoder* i2cEncoder;
  PID* pid;

  double* input;
  double* setpoint;
  double* output;
};

#endif //POSITIONCONTROLLEDMOTOR_H
