#ifndef FOURWHEELDRIVE_h
#define FOURWHEELDRIVE_h

#include "Motor.h"
#include "VelocityControlledMotor.h"

class FourWheelDrive {
public:
	FourWheelDrive(Motor*, Motor*, Motor*, Motor*);
	FourWheelDrive(VelocityControlledMotor*, VelocityControlledMotor*, VelocityControlledMotor*, VelocityControlledMotor*);

	void drive(int, int, int, int);
	void stop();
	void drivePID(double, double, double, double);
	double getLeftPosition();
	double getRightPosition();
    double getLeftVelocity();
    double getRightVelocity();
    double getLeftFrontVelocity();
    double getLeftBackVelocity();
    double getRightFrontVelocity();
    double getRightBackVelocity();
private:
	char pid;
	Motor *lfm, *rfm, *lbm, *rbm;
	VelocityControlledMotor *lf, *rf, *lb, *rb;

};
#endif
