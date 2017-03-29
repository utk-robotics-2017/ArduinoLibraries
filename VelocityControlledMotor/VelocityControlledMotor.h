#ifndef VELOCITYCONTROLLEDMOTOR_h
#define VELOCITYCONTROLLEDMOTOR_h

#include "Motor.h"
#include "I2CEncoder.h"
#include "Encoder.h"
#include "PID.h"

class VelocityControlledMotor
{
public:
	VelocityControlledMotor(Motor, I2CEncoder, PID, double* input, double* setpoint, double* output);
    VelocityControlledMotor(Motor, Encoder, PID, double* input, double* setpoint, double* output);

	void setValue(int);
	void setVelocity(double);
	void stop();

    void runPID();

	double getVelocity();
	double getPosition();
private:
    bool i2c;

	Motor* motor;
	Encoder* encoder;
	I2CEncoder* i2cEncoder;
    
    PID* pid;
    double* input;
    double* setpoint;
    double* output;
};

#endif
