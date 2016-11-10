/******************************************************************************

    Test program for the lcd16.c module. Displays a floating point number
    on line one along with a fixed string. Displays a long integer (32-bits)
    and an integer (16-bits) on the second line. Increments the numbers by one
    forever.
  
  Ron Kreymborg
  
******************************************************************************/

#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <math.h>
#include "compat.h"
#include "lcd.h"

#define outp(a,b) b=a

#define BYTE            unsigned char
#define WORD            unsigned int

int main(void);

int main(void)
{    
    float fnum;
    long lnum;
    int inum;
    
   // PORTB
    outp(0xff, PORTB);              // all high
    outp(0xff, DDRB);               // all output
    // PORTA
    outp(0x00, PORTA);              // all low
    outp(0xff, DDRA);               // all output

    InitLCD();
    fnum = 0.0;
    lnum = 0L;
    inum = 0;

    CustChar(0,"\x98\x94\x92\x91\x92\x94\x98\x80");
    CustChar(1,"\x83\x85\x89\x91\x89\x85\x83\x80");
    CustChar(2,"\x90\x90\x90\x90\x90\x90\x90\x90");
    CustChar(3,"\x94\x94\x94\x94\x94\x94\x94\x94");
    CustChar(4,"\x95\x95\x95\x95\x95\x95\x95\x95");
    CustChar(5,"\x80\x9f\x80\x9f\x80\x9f\x80\x9F");
    CustChar(6,"\x95\x8a\x95\x8a\x95\x8a\x95\x8a");
    CustChar(7,"\x90\x88\x84\x82\x81\x80\x90\x88");
    SendString(">> 2\xeb\x31\x36 chars <<", 1, 0);     // plain string
    SendString("userdef:\x08\x01\x02\x03\x04\x05\x06\x07", 2, 0);     // plain string
        
    while (1)
    {

    }    
    
    return 0;
}


