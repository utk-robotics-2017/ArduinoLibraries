#include "PositionControlledMotor.h"
#include "Arduino.h"

PositionControlledMotor::PositionControlledMotor(Motor& motor, I2CEncoder& encoder, PID& pid, double* input, double* output, double* setpoint)
{
    this->motor = &motor;
    this->i2cEncoder = &encoder;
    this->pid = &pid;

    this->input = input;
    this->output = output;
    this->setpoint = setpoint;
}

void PositionControlledMotor::setValue(int value)
{
    pid->SetMode(MANUAL);
    motor->drive(value);
}

void PositionControlledMotor::setPosition(double position)
{
    *setpoint = position;
    pid->SetMode(AUTOMATIC);
}

double PositionControlledMotor::getPosition()
{
    return i2cEncoder->getPosition();
}

void PositionControlledMotor::stop()
{
    setValue(0);
}

void PositionControlledMotor::runPID()
{
    *input = getPosition();
    char updated = pid->Compute();
    if (updated)
    {
        motor->drive((int)*output);
    }
}