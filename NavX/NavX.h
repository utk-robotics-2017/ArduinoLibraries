#ifndef NAVX_H
#define NAVX_H

class NavX
{
public:
  NavX();
  float getYaw();
  float getPitch();
  float getRoll();

  char getStatus();

private:
  char* read(char register_, char num_bytes);
  int m_address;
};

#endif // NAVX_H
