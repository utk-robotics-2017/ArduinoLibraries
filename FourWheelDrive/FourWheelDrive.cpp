
#include "FourWheelDrive.h"

FourWheelDrive::FourWheelDrive(Motor* lfm, Motor* rfm, Motor* lbm, Motor* rbm)
{
	this->lfm = lfm;
	this->rfm = rfm;
	this->lbm = lbm;
	this->rbm = rbm;
	this->pid = 0;
}

FourWheelDrive::FourWheelDrive(VelocityControlledMotor* lf, VelocityControlledMotor* rf, VelocityControlledMotor* lb, VelocityControlledMotor* rb)
{
	this->lf = lf;
	this->rf = rf;
	this->lb = lb;
	this->rb = rb;
	this->pid = 1;
}

void FourWheelDrive::drive(int lf_value, int rf_value, int lb_value, int rb_value)
{
	if(pid){
		lf->setValue(lf_value);
		rf->setValue(rf_value);
		lb->setValue(lb_value);
		rb->setValue(rb_value);
	} else {
		lfm->drive(lf_value);
		rfm->drive(rf_value);
		lbm->drive(lb_value);
		rbm->drive(rb_value);
	}
}

void FourWheelDrive::stop()
{
	if(pid){
		lf->stop();
		rf->stop();
		lb->stop();
		rb->stop();
	} else {
		lfm->stop();
		rfm->stop();
		lbm->stop();
		rbm->stop();
	}
}

void FourWheelDrive::drivePID(double lf_value, double rf_value, double lb_value, double rb_value)
{
	if(pid){
		lf->setVelocity(lf_value);
		rf->setVelocity(rf_value);
		lb->setVelocity(lb_value);
		rb->setVelocity(rb_value);
	}
}

double FourWheelDrive::getLeftPosition()
{
	if(pid)
	{
		return lb->getPosition();
	}
	return 0.0;
}

double FourWheelDrive::getRightPosition()
{
	if(pid)
	{
		return rb->getPosition();
	}
	return 0.0;
}


double FourWheelDrive::getLeftVelocity()
{
    if(pid)
    {
        return (lf->getVelocity() + lb->getVelocity()) / 2.0;
    }
    return 0.0;
}

double FourWheelDrive::getRightVelocity()
{
    if(pid)
    {
        return (rf->getVelocity() + rb->getVelocity()) / 2.0;
    }
    return 0.0;
}

double FourWheelDrive::getLeftFrontVelocity()
{
    if(pid)
    {
        return lf->getVelocity();
    }
    return 0.0;
}

double FourWheelDrive::getLeftBackVelocity()
{
    if(pid)
    {
        return lb->getVelocity();
    }
    return 0.0;
}

double FourWheelDrive::getRightFrontVelocity()
{
    if(pid)
    {
        return rf->getVelocity();
    }
    return 0.0;
}

double FourWheelDrive::getRightBackVelocity()
{
    if(pid)
    {
        return rb->getVelocity();
    }
    return 0.0;
}

