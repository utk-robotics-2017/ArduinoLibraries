#include "Wire.h"
#include "Arduino.h"

#include "NavX.h"

#include "IMURegisters.h"

NavX::NavX()
{
  m_address = 0x32;
}

float NavX::getYaw()
{
  char* data = read(NAVX_REG_YAW_L, 2);
  return IMURegisters::decodeProtocolSignedHundredthsFloat(data);
}

float NavX::getPitch()
{
  char* data = read(NAVX_REG_PITCH_L, 2);

  return IMURegisters::decodeProtocolSignedHundredthsFloat(data);
}

float NavX::getRoll()
{
  char* data = read(NAVX_REG_ROLL_L, 2);
  return IMURegisters::decodeProtocolSignedHundredthsFloat(data);
}

char NavX::getStatus()
{
  return 0;
}

char* NavX::read(char register_, char num_bytes)
{
  Wire.beginTransmission(m_address);
  Wire.write(register_);
  Wire.write(num_bytes);
  Wire.endTransmission();

  Wire.beginTransmission(m_address);
  Wire.requestFrom(m_address, num_bytes);
  char data[num_bytes];
  int i = 0;
  while(Wire.available())
  {
    data[i++] = Wire.read();
  }
  Wire.endTransmission();
  return data;
}
