//#include <LPC21xx.H>  /* LPC21xx definitions         */
#include "uart_defines.h"

char buff[200]="hello",dummy;
unsigned char i=0,ch,r_flag;


void UART0_isr(void) __irq
{
  if((U0IIR & 0x04)) //check if receive interrupt
 {
		ch = U0RBR;	/* Read to Clear Receive Interrupt */
		if(i<200)
			buff[i++] = ch; 
  }
  else
  {
      dummy=U0IIR; //Read to Clear transmit interrupt
  }
   VICVectAddr = 0; /* dummy write */
}


void Init_UART0 (void) /* Initialize Serial Interface       */ 
{  
  PINSEL0=0x00000005; /* Enable RxD0 and TxD0              */
  U0LCR=0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U0DLL=DIVISOR;      /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
  U0DLM=DIVISOR>>8;
  U0LCR=0x03;         /* DLAB = 0  */
  #if UART_INT_ENABLE > 0
  VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
  VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
  #endif						
}


void UART0_Tx_char(char ch)  /* Write character to Serial Port    */  
{ 
  while (!(U0LSR & 0x20));
  U0THR = ch;                
}


char UART0_Rx_char(void)    /* Read character from Serial Port   */
{                     
  while (!(U0LSR & 0x01));
  return (U0RBR);
}




void UART0_Tx_str(char *s)

{

   while(*s)

       UART0_Tx_char(*s++);

}


void UART0_Tx_int(unsigned int n)

{

  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};

  int i=0;

  if(n==0)

  {

    UART0_Tx_char('0');

		return;

  }

  else

  {

     while(n>0)

	 {

	   a[i++]=(n%10)+48;

	   n=n/10;

	 }

	 --i;

	 for(;i>=0;i--)

	 {

	   UART0_Tx_char(a[i]);

	 }

   }

}


void UART0_Tx_float(float f)

{

  int x;

  float temp;

  x=f;

  UART0_Tx_int(x);

  UART0_Tx_char('.');

  temp=(f-x)*100;

  x=temp;

  UART0_Tx_int(x);

}
 

