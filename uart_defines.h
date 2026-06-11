
#define LCD_DATA 8 // P0.8 TO P0.15
#define RS 6
#define RW 5
#define EN 7

//LCD COMMANDS
#define CLEAR_LCD   0x01
#define RET_CUR_HOME 0x02
#define MODE_4BIT_1LINE 0x20
#define MODE_4BIT_2LINE 0x28
#define MODE_8BIT_1LINE 0x30
#define MODE_8BIT_2LINE 0x38
#define DISP_OFF 0x08
#define DISP_ON_CUR_OFF 0x0C
#define DISP_ON_CUR_ON 0x0E		                                                                                                                                                                
#define DISP_ON_CUR_BLINK 0x0F
#define GOTO_LINE1_POS0 0x80  
#define GOTO_LINE2_POS0 0xC0  
#define GOTO_CGRAM 0x40  
#define SHIFT_CUR_RIGHT 0x06  
#define SHIFT_DISP_RIGHT 0x1C
#define SHIFT_DISP_LEFT 0x18

    
