#include<LPC21xx.h>
#include"ADC_defines.h"
#include"types.h"
#include"delay.h"
#include"defines.h"

#define ADC_FUNC 0x01 

void InitADC(void)
{
   	 PINSEL1 |= (ADC_FUNC<<24);  //configure P0.28 as ADC input

  ADCR=PDN_BIT|CLKDIV|CHANNEL_SEL;	
}

/* void READ_ADC(u32 chno, f32 *eAR, u32 *AdcDval)
{
     //clear channel bits
	 ADCR&=~(255<<0);
	 //select chno and start now
	 ADCR|=chno|START_CONV;
	 //wait for conv
	 delay_us(3);
	 //wait for done bit 
	 while(!READBIT(ADCR,DONE_BIT));
	 //stop conv
	 ADCR&=~(START_CONV);
	 //extract the digital value from data reg
	 *AdcDval=((ADDR>>RESULT)&1023);
	 //equivalent analog reading
	 *eAR=((*AdcDval*3.3)/1023);
}  */
f32 Read_ADC(u8 chNo)
{
  u16 adcVal=0;
	f32 eAR;
	WRITEBYTE(ADCR,0,chNo);
	SETBIT(ADCR,ADC_START_BIT);
	delay_us(3);
	while(!READBIT(ADDR,DONE_BIT));
	CLRBIT(ADCR,ADC_START_BIT);
	adcVal=(ADDR>>6)&0x3FF;
	eAR=((adcVal*3.3)/1023);
	return eAR;
}  



