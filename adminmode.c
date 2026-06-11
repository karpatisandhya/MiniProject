#include<LPC21xx.h>																		                       
#include<string.h>
#include"delay.h"
#include"defines.h"
#include"lcd.h"
#include"LCD_defines.h"
#include"ADC.h"
#include"RTC.h"
#include"types.h"
#include"KPM.h"
#include"ADC_defines.h"
#include"adminmode.h"
#define TOTAL_MESSAGES  10
#define SW 3

extern s32 hour,min,sec,date,month,year,day;


void ScrollLCD_CountDown(char *);

typedef struct
{
        s32 hour;
        s32 minute;
        char str[100];
        s32 dis;
}Message;

extern Message messagelist[TOTAL_MESSAGES];

extern s32 hour,sec,min;


int main()
{
        u32 i;
        f32 aR1;
        IODIR0 &= ~(1<<SW);
  InitLCD();
        RTC_Init();
        InitADC();
        InitKPM();
        // Initial Time
    SetRTCTimeInfo(7,44,44);
    // Initial Date
    SetRTCDateInfo(11,6,2026);
	SetRTCDay(4);
        while(1)
        {
                                                                                                                                                                                            GetRTCTimeInfo(&hour,&min,&sec);
                 DisplayRTCTime(hour,min,sec);
				 GetRTCDay(&day);
				 DisplayRTCDay(day);
				 GetRTCDateInfo(&date,&month,&year);
				 year=year%100;
				 DisplayRTCDate(date,month,year);
				 //CmdLCD(0xC0);
				 StrLCD("temp:");
                 aR1=Read_ADC(1);
                 U32LCD(aR1*100);
				 CharLCD(223);
				 StrLCD("C");
                 for(i=0;i<10;i++)
                 {
                         if(messagelist[i].dis == 1)
						 {
                                 if(messagelist[i].hour==hour && messagelist[i].minute==min && sec==0)
                                 {
										 CmdLCD(0x01);
                                         ScrollLCD_CountDown(messagelist[i].str);
                                 }
                         }
                 }
                 if(READBIT(IOPIN0,SW)==0)
                {
                        delay_ms(200);
                        if(READBIT(IOPIN0,SW)==0)
                        {
                                Admin_Mode();
                                while(READBIT(IOPIN0,SW)==0);
                  }
          }
        }
}

		


