#include "LCD_disp_Driver.h"
#include "device_config.h"
#define _XTAL_FREQ 8000000

void LCD_init(){
    LCDdataDir = 0x00;
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_E  = 0;
    LATC = 0;               
    LCD_E_Dir = 0;          
    LCD_RS_Dir = 0;        
    LCD_RW_Dir = 0;        
    LCD_cmd(setLCD_8bits_2Lines_smallFont);
    __delay_ms(250);  
    LCD_cmd(DISPLAY_ON_C_ON_B_OFF);
    __delay_ms(250);  
    LCD_cmd(Clear_DISP);          
    __delay_ms(250); 
}
void LCD_cmd(char cx) {
    LCD_RS = 0;             // select IR register
    LCD_RW = 0;             // set WRITE mode
    LCD_E  = 1;             // set to clock data
    Nop();
    LCDdataWrite = cx;      // send out command
    Nop();
    LCD_E = 0;              // complete external write cycle
}
void send_to_LCD(char xy){
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_E  = 1;
    LCDdataWrite = xy;
    Nop();
    Nop();
    LCD_E  = 0;
    __delay_ms(250);
}
void write_string_LCD (const char *s){
    while(*s)
        send_to_LCD(*s++);
}