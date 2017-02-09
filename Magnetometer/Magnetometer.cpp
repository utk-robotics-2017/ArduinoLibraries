/*
 * =====================================================================================
 *
 *       Filename:  Magnetometer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/01/17 20:51:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Magnetometer.h"

Magnetometer::Magnetometer()
{
    address = 0x0E;
}

void Magnetometer::config()
{
    Wire.beginTransmission(address);
    Wire.write(0x11); // ctrl register 2
    Wire.write(0x80); // enable auto resets
    Wire.endTransmission();

    delay(15);

    Wire.beginTransmission(address);
    Wire.write(0x10); // ctrl register 1
    Wire.write(1); // active mode
    Wire.endTransmission();
}

void Magnetometer::zero()
{
    int x = readX();
    int y = readY();
    int z = readZ();

    Wire.beginTransmission(address);
    Wire.write(0x09);
    Wire.write(x>>8);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x0A);
    Wire.write(x & 0xFF);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x0B);
    Wire.write(y>>8);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x0C);
    Wire.write(y & 0xFF);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x0D);
    Wire.write(z>>8);
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x0E);
    Wire.write(z & 0xFF);
    Wire.endTransmission();
}

int Magnetometer::readX()
{
    int xl, xh;  //define the MSB and LSB

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x01);              // x MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        xh = Wire.read(); // read the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x02);              // x LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        xl = Wire.read(); // read the byte
    }

    int xout = (xl|(xh << 8)); //concatenate the MSB and LSB
    return xout;
}

int Magnetometer::readY()
{
    int yl, yh;  //define the MSB and LSB

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x03);              // y MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        yh = Wire.read(); // read the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x04);              // y LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        yl = Wire.read(); // read the byte
    }

    int yout = (yl|(yh << 8)); //concatenate the MSB and LSB
    return yout;
}

int Magnetometer::readZ()
{
    int zl, zh;  //define the MSB and LSB

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x05);              // z MSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        zh = Wire.read(); // read the byte
    }

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.beginTransmission(address); // transmit to device 0x0E
    Wire.write(0x06);              // z LSB reg
    Wire.endTransmission();       // stop transmitting

    delayMicroseconds(2); //needs at least 1.3us free time between start and stop

    Wire.requestFrom(address, 1); // request 1 byte
    while(Wire.available())    // slave may write less than requested
    {
        zl = Wire.read(); // read the byte
    }

    int zout = (zl|(zh << 8)); //concatenate the MSB and LSB
    return zout;
}
