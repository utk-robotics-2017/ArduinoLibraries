#ifndef NAVX_H
#define NAVX_H

class NavX
{
public:
  static float getYaw();
  static float getPitch();
  static float getRoll();

  static char getStatus();

private:
  static char* read(char register_, char num_bytes);
  static int m_address;
};

#endif // NAVX_H
