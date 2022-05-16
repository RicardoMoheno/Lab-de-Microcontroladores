#include "LCD_disp_Driver.h"
#include "device_config.h"
#include <math.h>

#define _XTAL_FREQ 1000000

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

void set_LCD_dir(char d){
    if(d == 'L'){
        LCD_cmd(EMS_DEC_S);
        LCDdir = 'L';
    } else if (d == 'R'){
        LCD_cmd(EMS_INC_S);
        LCDdir = 'R';
    }
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

void set_cursor_pos(char row,char col){
    unsigned char Pos = 0;
    switch (row){
        case 0: {
            Pos = 0x80|col;
            LCD_cmd(Pos);
        } break;
        case 1: {
            Pos = 0xC0|col;
            LCD_cmd(Pos);
        } break;
        default: Nop(); break;
    }
}

void move_cursor_n_times(int n, char dir){
    if (dir == 'R'){
        for (int i = 0; i <n ;i++){
        LCD_cmd(CURSOR_MOVE_RIGHT);
        }
    } else if (dir == 'L'){
        for (int i = 0; i <n ;i++){
        LCD_cmd(CURSOR_MOVE_LEFT);
        }
    }   
}

void write_string_LCD(const char *s){
    while(*s)
        send_to_LCD(*s++);
}

void write_int_LCD(int x){
    unsigned char UnitDigit  = 0;
    unsigned char TenthDigit = 0; 
    unsigned char HundrethDigit = 0;
    HundrethDigit = x/100;
    TenthDigit = (x - HundrethDigit*100)/10;
    UnitDigit = x - TenthDigit*10 - HundrethDigit*100;
    if(LCDdir == 'R'){
        send_to_LCD(HundrethDigit+'0');
        send_to_LCD(TenthDigit+'0'); 
        send_to_LCD(UnitDigit+'0'); 
    } else if(LCDdir == 'L'){
        send_to_LCD(UnitDigit+'0'); 
        send_to_LCD(TenthDigit+'0');
        send_to_LCD(HundrethDigit+'0');
    }
}
