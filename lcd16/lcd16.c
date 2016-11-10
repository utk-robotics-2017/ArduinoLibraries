/******************************************************************************
 
 Implements a stand alone interface to a HD44780 based 2 line by 16 character 
 LCD display.
  
  Ron Kreymborg
  
******************************************************************************/

#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include "lcd.h"
#include "lcd16.h"
#include "compat.h"

static BYTE commandFlag;

void CustChar(unsigned char c, char *data) {
  SendCommand(0x40+((c&0x07)<<3)); //Set CG-RAM address
  for (char i=0; i<8; i++) {
    SendData(*data++);
  }
}

//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the 
// specified position.
//
void SendString(char *pt, int line, int position)
{
    if (line == 1)
        SendCommand(0x80 + position);
    else
        SendCommand(0xc0 + position);
    while (*pt)
        SendData(*pt++);
}

//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the 
// specified position.
//
void SendLong(long number, int line, int position)
{
    char temp[15];

    sprintl(number, temp);
    SendString(temp, line, position);
}
    
//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the 
// specified position.
//
void SendInt(int number, int line, int position)
{
    char temp[15];
    
    itoa(number, temp, 10);
    SendString(temp, line, position);
}

//-----------------------------------------------------------------------------
// Display the null terminated string in the specified line starting at the 
// specified position.
//
void SendFloat(float value, int line, int position)
{
   char temp[15];

   dtostre(value, temp, 4, 3);
   SendString(temp, line, position);
}

//-----------------------------------------------------------------------------
// Convert the number to the equeivelent ascii string.
//
void sprintl(long number, char *pt)
{
    int i, a, flag;
    long divisor = 1000000000L;
      
    if (number < 0L)
        *pt++ = '-';
        
    if (number == 0L)
    {
        *pt++ = '0';
    }
    else
    {
        flag = 0;
        for (i=1; i<11; i++)
        {
            a = (int)(number / divisor);
            if (a > 0)
            {
                flag = 1;
                number = number - (long)a * divisor;
            }
            if (flag)
            {
                *pt++ = '0' + (char)a;
            }
            divisor /= 10L;
        } 
    }
    *pt = '\0';
}

//-----------------------------------------------------------------------------
// Initialise the lcd display. Must be called before any display functions.
//
void InitLCD(void)
{
	outp(0x00, PORT);			    // all low
	outp(0xff, DDR);			    // all output
	Delay(50);                      // wait 50 mSec
	outp(0x03, PORT);
	Delay(5);
	outp(0x03, PORT);
	Delay(5);
	outp(0x03, PORT);
	Delay(5);
	outp(0x02, PORT);
	Delay(5);
	
	SendCommand(0x28);
	SendCommand(0x08);
	SendCommand(0x0c);
	SendCommand(0x01);
	SendCommand(0x06);
}
    
//-----------------------------------------------------------------------------
// Prepare and send a command byte.
//
void SendCommand(BYTE value)
{
    commandFlag = 0;
    Send(value);
}

//-----------------------------------------------------------------------------
// Prepare and send a data byte.
//
static void SendData(BYTE value)
{
    commandFlag = 1;
    Send(value);
}

//-----------------------------------------------------------------------------
// Send the byte to the display. First check if the display is busy.
//
static void Send(BYTE value)
{
    BYTE state;
    
	outp(0xf0, DDR);			    // low 4 bits input
	outp(0x1f, PORT);               // R/W high, pullup on
	do
	{
	    Tick();
        sbi(PORT, E_PIN);           // clock high
        sbi(PORTA, 1);
        Tick();
        state = inp(PIN);
        cbi(PORT, E_PIN);
        cbi(PORTA, 1);
        Tick();
        sbi(PORT, E_PIN);
        sbi(PORTA, 1);
        Tick();
        cbi(PORT, E_PIN);
        cbi(PORTA, 1);
    } while (state & 0x08);

    Tick();
    outp(0x00, PORT);               // R/W low
	outp(0xff, DDR);			    // low 4 bits output again
	SendByte(value>>4);             // send high nibble
	SendByte(value);                // send low nibble
}

//-----------------------------------------------------------------------------
// Actually send the byte. Use the global lag to decide whether a command
// or data byte.
//
static void SendByte(BYTE value)
{
    value &= 0x0f;              // mask off high nibble
    if (commandFlag)                // or in the RS bit
        value |= 1<<RS_PIN;
    Tick();
    outp(value, PORT);          // output low nibble
    Clock();
}

//-----------------------------------------------------------------------------
// Provide a high to low transition on the E (clock) line.
//
static void Clock(void)
{
    sbi(PORT, E_PIN);
    Tick();
    cbi(PORT, E_PIN);
}

//-----------------------------------------------------------------------------
// Provide an approx delay in milliseconds.
//
static void Delay(int milliSeconds)
{
    long n;
    
    n = (long)milliSeconds * 800L;
    while (n)
        n--;
}



