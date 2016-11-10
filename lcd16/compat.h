/* This file gives backwards compability for newer avr-ggc and libavr */

#define inp(x) x
#define outp(x,y) y=x
#define sbi(y,x) y|=_BV(x)
#define cbi(y,x) y&=~_BV(x)