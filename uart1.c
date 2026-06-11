#include <string.h>
#include "delay.h"
#include "lcd.h"
#include "uart0.h"
#include "types.h"
#include<stdlib.h>


extern u8 buff[200];

extern  u8 i;


void esp01_connectAP()

{

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("AT");

	delay_ms(1000);

	UART0_Tx_str("AT\r\n");

	i=0;memset(buff,'\0',200);

//	while(i<4);

	delay_ms(500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);
												 
	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"OK"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);		

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

	

	

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("ATE0");

	delay_ms(1000);

	UART0_Tx_str("ATE0\r\n");

	i=0;memset(buff,'\0',200);

	while(i<4);

	delay_ms(500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"OK"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);		

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

	

	

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("AT+CIPMUX");

	delay_ms(1000);

	UART0_Tx_str("AT+CIPMUX=0\r\n");

	i=0;memset(buff,'\0',200);

	while(i<4);

	delay_ms(500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"OK"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);		

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

	

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("AT+CWQAP");

	delay_ms(1000);

	UART0_Tx_str("AT+CWQAP\r\n");

	i=0;memset(buff,'\0',200);

	while(i<4);

	delay_ms(1500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"OK"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);		

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

	

	

	

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("AT+CWJAP");

	delay_ms(1000);

	//need to change the wifi network name and password

	UART0_Tx_str("AT+CWJAP=\"Ramani\",\"divya2505\"\r\n");

	i=0;memset(buff,'\0',200);

	while(i<4);

	delay_ms(2500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"WIFI CONNECTED"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);		

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

	

}


void esp01_sendToThingspeak(char val,int n)

{

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD("AT+CIPSTART");

	delay_ms(1000);

	UART0_Tx_str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	i=0;memset(buff,'\0',200);

	//while(i<5);

	delay_ms(2500);

	buff[i] = '\0';

	CmdLCD(0x01);

	CmdLCD(0x80);

	StrLCD(buff);

	delay_ms(2000);

	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))

	{

		CmdLCD(0xC0);

		StrLCD("OK");

		delay_ms(1000);

		

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("AT+CIPSEND");

		delay_ms(1000);

		UART0_Tx_str("AT+CIPSEND=49\r\n");

		i=0;memset(buff,'\0',200);

		//while(buff[i] != '>');

		delay_ms(500);

		//need to change the thingspeak write API key accordind to your channel

		if(n==1)

		{

		UART0_Tx_str("GET /update?api_key=RZELB4TI91RDMXHV&field1=");

		}

		else

		{

		UART0_Tx_str("GET /update?api_key=RZELB4TI91RDMXHV&field2=");

		}

		UART0_Tx_int(val);

		UART0_Tx_str("\r\n");

        UART0_Tx_str("\r\n");

	  delay_ms(5000);

		delay_ms(5000);

		buff[i] = '\0';

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD(buff);

		delay_ms(2000);

		if(strstr(buff,"SEND OK"))

		{

			CmdLCD(0x01);

			StrLCD("DATA UPDATED");

			delay_ms(1000);			

		}

		/*

		else if(!strstr(buff,"CLOSED"))

		{

			CmdLCD(0x01);

			CmdLCD(0x80);

			StrLCD("AT+CIPCLOSE");

			delay_ms(1000);

			UART0_Tx_str("AT+CIPCLOSE\r\n");

			i=0;memset(buff,'\0',200);

			while(i<5);

			delay_ms(2500);

			buff[i] = '\0';

			CmdLCD(0x01);

			CmdLCD(0x80);

			StrLCD(buff);

			delay_ms(2000);

			if(strstr(buff,"OK"))

			{

				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("OK");

				delay_ms(2000);				

			}

			else

			{

				CmdLCD(0x01);

				CmdLCD(0x80);

				StrLCD("ERROR");

				delay_ms(2000);		

			}

		

		}*/

		else

		{

			CmdLCD(0x01);

			StrLCD("DATA NOT UPDATED");

			delay_ms(1000);	

		}

		CmdLCD(0x01);

	}

	else

	{

		CmdLCD(0xC0);

		StrLCD("ERROR");

		delay_ms(1000);		

		return;

	}

}
