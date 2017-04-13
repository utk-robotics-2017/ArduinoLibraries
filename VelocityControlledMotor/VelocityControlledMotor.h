#ifndef VELOCITYCONTROLLEDMOTOR_h
#define VELOCITYCONTROLLEDMOTOR_h

#include "Motor.h"
#include "I2CEncoder.h"
#include "Encoder.h"
#include "vPID.h"

class VelocityControlledMotor
{
public:
	VelocityControlledMotor(Motor, I2CEncoder, vPID, double* input, double* output, double* setpoint);
    VelocityControlledMotor(Motor, Encoder, vPID, double* input, double* output, double* setpoint);

	void setValue(int);
	void setVelocity(double);
	void stop();

    void runVPID();

	double getVelocity();
	double getPosition();
private:
    bool i2c;

	Motor* motor;
	Encoder* encoder;
	I2CEncoder* i2cEncoder;

    vPID* vpid;
    double* input;
    double* output;
    double* setpoint;
};

#endif
