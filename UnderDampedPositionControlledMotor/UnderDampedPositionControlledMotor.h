#ifndef UNDERDAMPEDPOSITIONCONTROLLEDMOTOR_H
#define UNDERDAMPEDPOSITIONCONTROLLEDMOTOR_H

#include "Motor.h"
#include "I2CEncoder.h"
#include "UnderDampedPID.h"

class UnderDampedPositionControlledMotor
{
public:
  UnderDampedPositionControlledMotor(Motor&, I2CEncoder&, UnderDampedPID&, double* input, double* output, double* setpoint);

  void setValue(int);
  void setPosition(double);
  double getPosition();
  double getVelocity();

  void setAllowedDirection(int);
  
  void stop();
  
  void runPID();

private:
  Motor* motor;
  I2CEncoder* i2cEncoder;
  UnderDampedPID* pid;

  double* input;
  double* setpoint;
  double* output;
};

#endif //UNDERDAMPEDPOSITIONCONTROLLEDMOTOR_H
