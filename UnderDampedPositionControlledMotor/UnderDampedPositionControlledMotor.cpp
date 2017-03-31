#include "UnderDampedPositionControlledMotor.h"
#include "Arduino.h"

UnderDampedPositionControlledMotor::UnderDampedPositionControlledMotor(Motor& motor, I2CEncoder& encoder, UnderDampedPID& pid, double* input, double* output, double* setpoint)
{
    this->motor = &motor;
    this->i2cEncoder = &encoder;
    this->pid = &pid;

    this->input = input;
    this->output = output;
    this->setpoint = setpoint;
}

void UnderDampedPositionControlledMotor::setValue(int value)
{
    pid->SetMode(MANUAL);
    motor->drive(value);
}

void UnderDampedPositionControlledMotor::setPosition(double position)
{
    *setpoint = position;
    pid->SetMode(AUTOMATIC);
}

double UnderDampedPositionControlledMotor::getPosition()
{
    return i2cEncoder->getPosition();
}

double UnderDampedPositionControlledMotor::getVelocity()
{
    return i2cEncoder->getVelocity();
}

void UnderDampedPositionControlledMotor::setAllowedDirection(int value)
{
    pid->SetAllowedDirection(value);
}

void UnderDampedPositionControlledMotor::stop()
{
    setValue(0);
}

void UnderDampedPositionControlledMotor::runPID()
{
    *input = getPosition();
    char updated = pid->Compute();
    if (updated)
    {
        motor->drive((int)*output);
    }
}
