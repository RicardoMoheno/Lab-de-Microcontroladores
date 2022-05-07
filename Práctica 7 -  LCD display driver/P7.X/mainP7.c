//+++++++++++++++++++++++++| Librerías y headers |++++++++++++++++++++++++++++++
#include "device_config.h"
#include "4x4_kbd_Driver.h"
#include "LCD_disp_Driver.h"
#include <stdint.h>
#include <math.h>

//+++++++++++++++++++++++++| Directivas |+++++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 8000000
#define Error 13

//+++++++++++++++++++++++++| Declaración de Funciones |+++++++++++++++++++++++++
int  get_Num(char);
char get_Func(char);
void disp_Res(signed int);
void disp_Error(int);

//+++++++++++++++++++++++++| Variables |++++++++++++++++++++++++++++++++++++++++
signed int num1,num2;
char oper;

//+++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++
void main(void) {
    OSCCON = 0x74;
    LCD_init();
    kbd_init();
    while(1){
        key = get_Key();        
        send_to_LCD(key);
        num1 = get_Num(key);
        if (num1 != Error){
            key = get_Key();
            send_to_LCD(key);
            oper = get_Func(key);
            if (oper != 'e'){
                key = get_Key();
                send_to_LCD(key);
                num2 = get_Num(key);
                if (num2 != Error){
                    key = get_Key();
                    send_to_LCD(key);
                    if (key == '='){
                        LCD_cmd(LCD_LINE1);
                        switch (oper){
                            case '+': disp_Res(num1+num2); LCD_cmd(Return_Home); break;
                            case '-': disp_Res(num1-num2); LCD_cmd(Return_Home); break;
                            case '*': disp_Res(num1*num2); LCD_cmd(Return_Home); break;
                            case '/': disp_Res(num1/num2); LCD_cmd(Return_Home); break;
                        }
                    } else if (key == 'C'){
                        LCD_cmd(Clear_DISP);
                    } else disp_Error(0);
                }
            }
        }
    }
} 

//+++++++++++++++++++++++++| Funciones |++++++++++++++++++++++++++++++++++++++++
int get_Num(char ch){
    int num = 0;
    switch(ch){
    case '0': num = 0; break;
    case '1': num = 1; break;
    case '2': num = 2; break;
    case '3': num = 3; break;
    case '4': num = 4; break;
    case '5': num = 5; break;
    case '6': num = 6; break;
    case '7': num = 7; break;
    case '8': num = 8; break;
    case '9': num = 9; break;
    case 'C':
        LCD_cmd(Clear_DISP);
        num = Error;
        break;
    default:
        disp_Error(0);
        num = Error;
        break;       //it means wrong input
    }
    return num;
}

char get_Func(char chf){
    if(chf=='C'){
        LCD_cmd(Clear_DISP);
        return 'e';
    }
    if( chf!='+' && chf!='-' && chf!='*' && chf!='/' ){
        disp_Error(1);
        return 'e';
    }
    return chf;
}

void disp_Res(signed int numb){
    unsigned char UnitDigit  = 0;
    unsigned char TenthDigit = 0; 
    if(numb < 0){
        write_string_LCD("--");
        numb = -1*numb;  
    }
    TenthDigit = (numb/10);                   
    if( TenthDigit != 0)              
        send_to_LCD(TenthDigit+'0'); 
    UnitDigit = numb - TenthDigit*10;
    send_to_LCD(UnitDigit+'0');    
}

void disp_Error(int numb){
    LCD_cmd(Clear_DISP);
    switch(numb){
    case 0:  write_string_LCD("-Wrong Input");    break;
    case 1:  write_string_LCD("-Wrong Function"); break;
    default: write_string_LCD("-Wrong Input");    break;
    }
}