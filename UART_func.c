#include<lpc21xx.h>
#include"delay.h"

#include"lcd.h"
#include"lcd_defines.h"

//system clock and peripheral clock Macros
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL (int) ((PCLK/32768)-1) //RTC Requires 32.768 kHz clock for 1sec increment
#define PREFRAC_VAL (PCLK-(PREINT_VAL+1)*32768)

//RTC control registers (CCR) bit definitions 
#define RTC_ENABLE (1<<0) // Bit=0 -clock enable rtc counter ,bit=1 -clock disable rtc counter
#define RTC_RESET (1<<1)  //BIT-0 -Normal operatiom , Bit=1 -reset rtc counter

#define RTC_CLKSRC (1<<4) // Bit 4 -clock source select,bit=0 -use external PCLK as Rtc clock source, bit=1 -use external 32.768 kHz oscillator

#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6
#define _LPC2148

u8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

s32 hour,min,sec,date,month,year,day;


void RTC_Init(void)	 //fun'c disables the RTC ,sets the prescalar values, and then enable RTC
{
   	//disable and reset the RTC
	CCR=RTC_RESET;
	#ifndef _LPC2148
	   PREINT=PREINT_VAL;
	   PREFRAC=PREFRAC_VAL;

	   //enable Rtc
	   CCR=RTC_ENABLE;
	#else
	   //enable RTc with external clock source 
	   CCR=RTC_ENABLE |	RTC_CLKSRC;
	#endif
}

void GetRTCTimeInfo(s32 *hour , s32 *minute ,s32 *second)
{
    *hour=HOUR;

	*minute=MIN;

	*second=SEC;
}
/*

Display the RTC time on LCD

hour value (0-23)

minute value (0-59)

second value (0-59) seperated by ':'

*/

void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

	CmdLCD(GOTO_LINE1_POS0);

	CharLCD(hour/10+48);

	CharLCD(hour%10+48);

	CharLCD(':');

	CharLCD(minute/10+48);

	CharLCD(minute%10+48);

	CharLCD(':');

	CharLCD(second/10+48);		

	CharLCD(second%10+48);
	

}


/*

Get the current RTC date
day Pointer to store the current date (1-31)

month Pointer to store the current month (1-12)

year Pointer to store the current year (four digits)

*/

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{

	*date = DOM;

	*month = MONTH;

	*year = YEAR;

}


/*

Display the RTC date on LCD

Day of month (1-31)

Month (1-12)

Year (four digits) and seperated by '/'

*/

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

	CmdLCD(GOTO_LINE2_POS0);

	CharLCD(date/10+48);

	CharLCD(date%10+48);

	CharLCD('/');

	CharLCD(month/10+48);
	CharLCD(month%10+48);

	CharLCD('/');

	U32LCD(year);

}


/*

Set the RTC time

Hour to set (0-23)

Minute to set (0-59)

Second to set (0-59)

*/

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;

}


/*

Set the RTC date

day of month to set (1-31)
month to set (1-12)

year to set (four digits)

*/

void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

	DOM = date;

	MONTH = month;

	YEAR = year;

}


/*

Get the current day of the week

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)

*/

void GetRTCDay(s32 *dow)

{

	*dow = DOW; 

}


/*
Display the current day of the week on LCD

dow (Day of Week) (0=Sunday, ..., 6=Saturday)

*/

void DisplayRTCDay(u32 dow)

{

	CmdLCD(GOTO_LINE1_POS0+10);

	StrLCD(week[dow]);

  

}


/*

Set the day of the week in RTC

Day of Week to set (0=Sunday, ..., 6=Saturday)

*/

void SetRTCDay(u32 dow)

{

	DOW = dow;

}
