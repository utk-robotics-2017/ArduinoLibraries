#define BYTE            unsigned char
#define WORD            unsigned int

#define PORT            PORTD   // allows easy port change
#define DDR             DDRD
#define PIN             PIND

#define E_PIN           6
#define RS_PIN          5
#define RW_PIN          4


static void SendData(BYTE value);
static void Send(BYTE value);
static void SendByte(BYTE value);
static void Clock(void);
static void Delay(int milliSeconds);
static inline void Tick(void);


//-----------------------------------------------------------------------------
// Provide a small delay to ensure a minimum clock frequency.
//
static inline void Tick(void)
{
    asm("nop\n\tnop"::);
}
