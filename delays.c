#include<LPC21xx.h>
#include"uart.h"
int main()
{
    InitUart();
	while(1)
	{
	    Uart_TX('A');
	}
}
