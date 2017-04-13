#include "VelocityControlledMotor.h"

VelocityControlledMotor::VelocityControlledMotor(Motor motor, I2CEncoder encoder, vPID vpid, double* input, double* output, double* setpoint)
{
	this->i2c = 1;
	this->motor = &motor;
	this->i2cEncoder = &encoder;
	this->vpid = &vpid;

	this->input = input;
	this->output = output;
	this->setpoint = setpoint;
}

VelocityControlledMotor::VelocityControlledMotor(Motor motor, Encoder encoder, vPID vpid, double* input, double* output, double* setpoint)
{
    this->i2c = 0;
    this->motor = &motor;
    this->encoder = &encoder;
    this->vpid = &vpid;

    this->input = input;
    this->output = output;
    this->setpoint = setpoint;
}

void VelocityControlledMotor::setValue(int value)
{
	vpid->SetMode(MANUAL);
	motor->drive(value);
}

void VelocityControlledMotor::setVelocity(double velocity)
{
	*setpoint = velocity;
	vpid->SetMode(AUTOMATIC);
}

void VelocityControlledMotor::stop()
{
	vpid->SetMode(MANUAL);
	setValue(0);
}

void VelocityControlledMotor::runVPID()
{
	*input = getVelocity();
	char updated = vpid->Compute();
	if(updated) {
		motor->drive(*output);
	}
}

double VelocityControlledMotor::getVelocity()
{
	if(i2c)
    {
        return i2cEncoder->getVelocity();
    }
    else
    {
        //TODO: set up way to get velocity from encoder
        return 0;
    }
}

double VelocityControlledMotor::getPosition()
{
	if(i2c)
    {
        return i2cEncoder->getPosition();
    }
    else
    {
        return encoder->read();
    }
}
