#include<LPC21xx.h>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"RTC.h"
#include"KPM.h"
#include"delay.h"
#include"defines.h"
#include<string.h>
#include<stdlib.h>
#define SW 3


typedef struct
{
        s32 hour;
        s32 minute;
        char str[100];
        s32 dis;
}Message;

Message messagelist[]={{7,45,"Good Morning! Classes Start Soon",1},
{13,45,"C Programming Session in Classroom number 2",1},
{10,15,"C module theory exam in 4th floor lab 1",1},
{10,15,"C module lab exam in 4th floor lab2 and middle lab at 10:30 AM",1},
{12,45,"Lunch Break from 1PM 1- 2PM",1},
{9,45,"ARM Workshop on external interrupts in LAB1 at 10AM",1},
{9,45,"ARM Kit issue time from 10AM - 10:30AM in middle lab",1},
{15,15,"Only 15 mins break time for next ARM session",1},
{17,00,"Revise today's Class programs at home!",1},
{17,45,"End of Day - See You Tomorrow!",1}};
extern s32 hour,min,sec,date,month,year,day;

u32 row,dow;
void Admin_Mode(void);
s32 readnum()
{
        s32 num=0;
        char key=0;
        while(1)
        {
                key=KeyScan();
                while(!ColScan());
				delay_ms(100);
                if(key>='0' && key<='9')
                {
                        CharLCD(key);
                        num=num*10+(key-'0');
                }
                else if(key=='C')
                        break;
        }
        return num;
}

void ScrollLCD_CountDown(char *msg)
{
    char buffer[150] = "                ";
    u8 temp[17];
    s32 count,m,i=0;
    u32 pos=0,j,k;
	strcat(buffer, msg);
    strcat(buffer, "                ");
    for(count=2;count>=0;count--)
    {
	 for(m=59;m>=0;m--)
     {
	    for(k =0;k < 1; k++)   // scroll 1 times during 1 second
        {
            CmdLCD(GOTO_LINE1_POS0);
		    for(j = 0; j < 16; j++)
                temp[j] = buffer[pos + j];
            temp[16] = '\0';
            StrLCD(temp);
			StrLCD(temp);
            CmdLCD(GOTO_LINE2_POS0);
            U32LCD(i/10);
			U32LCD(i%10);
			StrLCD(":");
			U32LCD(count/10);
			U32LCD(count%10);
			StrLCD(":");
			U32LCD(m/10);
			U32LCD(m%10);
            StrLCD("   ");
            delay_ms(100);   // 10 × 100ms = 1 second
            pos++;
            if(pos > strlen(buffer) - 16)
                pos = 0;
		    if(READBIT(IOPIN0,SW)==0)
			{
			           Admin_Mode();
                       while(READBIT(IOPIN0,SW)==0);
					   return;
			}
		  }
        }
    }
	 CmdLCD(0x01);
}

void RTC_Edit(void)
{
    s32 h,m,s;
    row=0;
    CmdLCD(0x01);
    GetRTCTimeInfo(&h,&m,&s);
        while(1)
        {
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.H 2.M 3.S");
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("4.EX");
        row=KeyScan();
        while(!ColScan());
		delay_ms(100);
        switch(row)
        {
                case '1':CmdLCD(0x01);
                         StrLCD("enter the hour");
						 CmdLCD(GOTO_LINE2_POS0);
                         h=readnum();
                         if(h<0 && h>23)
				 {
				 CmdLCD(0x01);
				 CmdLCD(0x80);
				 StrLCD("Invalid");
				 delay_s(1);
                         break;
				 }
                         CmdLCD(0x01);
                         CmdLCD(0x80);
                         SetRTCTimeInfo(h,m,s);
                         CmdLCD(0x01);
                         DisplayRTCTime(h,m,s);
                         delay_ms(500);
                         break;
                case '2':CmdLCD(0x01);
                         StrLCD("enter the min");
						 CmdLCD(GOTO_LINE2_POS0);
                         m=readnum();
                         if(m<0 && m>59)
                         {
                                                         CmdLCD(0x01);
                                                         CmdLCD(0x80);
                                                         StrLCD("Invalid");
                                                         delay_s(1);
                                                         break;
                                                 }
                                                 CmdLCD(0x01);
             CmdLCD(0x80);
             SetRTCTimeInfo(h,m,s);
             CmdLCD(0x01);
             DisplayRTCTime(h,m,s);
             delay_ms(500);
             break;
case '3':CmdLCD(0x01);
                         StrLCD("enter the sec");
						 	 CmdLCD(GOTO_LINE2_POS0);
                         s=readnum();
                         if(s<0 && s>59)
                         {
				 CmdLCD(0x01);
				 CmdLCD(0x80);
				 StrLCD("Invalid");
                         delay_s(1);
				 break;
                         }
             CmdLCD(0x01);
             CmdLCD(0x80);
             SetRTCTimeInfo(h,m,s);
             CmdLCD(0x01);
             DisplayRTCTime(h,m,s);
             delay_ms(500);
             break;
                case '4':CmdLCD(0x01);
                                                 return;

        }

        }
}
void Event_Edit(void)
{
    u32 eventno,info;
    row=0;
    while(1)
        {
           CmdLCD(0x01);
           CmdLCD(GOTO_LINE1_POS0);
           StrLCD("1.EVENT 2.EX");
           row=KeyScan();
		   delay_ms(100);
           while(!ColScan());
           if(row=='1')
           {
                  CmdLCD(0x01);
                 StrLCD("EVENT NO(1-10)");
				 CmdLCD(GOTO_LINE2_POS0);
                 eventno=readnum();
                  if(eventno>10 || eventno<1)
                        break;
						 
				  CmdLCD(0x01);
                  CmdLCD(GOTO_LINE1_POS0);
                  StrLCD("1.ACT 2.DEACT");
				  CmdLCD(GOTO_LINE2_POS0);
				  StrLCD("3.EX");
                  info=KeyScan();
				  while(ColScan());
				  CmdLCD(0x01);
                  if(info=='1')
                  {	  
							  messagelist[eventno-1].dis = 1;
							 ScrollLCD_CountDown(messagelist[eventno-1].str);
                                   break;						

						
				  }
                  else if(info=='2')
                  {
						   messagelist[eventno-1].dis = 0;   // deactivate
                           CmdLCD(0x01);
                           StrLCD("DEACTIVATED");
                           delay_ms(1000);
                           break;
                  }
			}
            else if(row=='2')
                             break;
        }
		CmdLCD(0x01);
}
void Admin_Mode(void)
{
    while(1)
        {
                CmdLCD(0x01);
                CmdLCD(GOTO_LINE1_POS0);
        StrLCD("1.RTC Ed 2.EVENT");
                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("3.exit");
        row=KeyScan();
		delay_ms(100);
        if(row=='1')
        {
                RTC_Edit();
                break;
        }
        else if(row=='2')
        {
                Event_Edit();
                break;
        }
        else if(row=='3')
        {
                CmdLCD(0x01);
                return;
        }
        }

}

