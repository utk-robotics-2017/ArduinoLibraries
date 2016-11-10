/******************************************************************************


  
  Ron Kreymborg
  
******************************************************************************/

extern void InitLCD(void);
extern void CustChar(unsigned char c, char *data);
extern void SendCommand(unsigned char value);
extern void SendString(char *pt, int line, int position);
extern void SendFloat(float value, int line, int position);
extern void SendLong(long number, int line, int position);
extern void SendInt(int number, int line, int position);
extern void sprintl(long number, char *pt);

