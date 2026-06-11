#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define ADCLK 3750000
#define CLK_DIV (((PCLK/ADCLK)-1)<<8)


#define CH0 0x01
#define CH1 0x02
#define CH2 0x04
#define CH3 0x08

#define PDN_BIT (1<<21)
#define CLKDIV  (CLK_DIV<<8)
#define START_CONV (1<<24)
#define CHANNEL_SEL CH1

#define RESULT 6
#define DONE_BIT 31

#define AIN0 0x00400000
#define AIN1 0x01000000
#define AIN2 0x04000000
#define AIN3 0x10000000
#define ADC_START_BIT 24




