/*
 * =====================================================================================
 *
 *       Filename:  Magnetometer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/17 20:45:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H
#include <Arduino.h>
#include <Wire.h>

class Magnetometer
{
    public:
        Magnetometer();
        void config();
        void zero();
        int readX();
        int readY();
        int readZ();
    private:
        int address;
};

#endif
