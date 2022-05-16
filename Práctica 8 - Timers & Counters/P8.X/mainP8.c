////++++++++++++++++++++++++++++| LIBRARIES / HEADERS |+++++++++++++++++++++++++
#include "device_config.h"
#include "LCD_disp_Driver.h"

//++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++
void measure (void);

//++++++++++++++++++++++++++++++| VARIABLE DECLARATIONS |+++++++++++++++++++++++
int count;

//++++++++++++++++++++++++++++++| MAIN |++++++++++++++++++++++++++++++++++++++++
void main (void){
    OSCCON = 0x34;         //Set internal oscillator to 1 MHz and stable
    TRISAbits.TRISA4 = 1;  //Set pin 4 of PORTA as input for the function generator signal
    LCD_init();            //Initialize PORTC & PORTD to control the LCD Display
    write_string_LCD("Frequency:");
    set_cursor_pos(1,0);
    write_string_LCD("000 Hz");
    set_LCD_dir('L');
    while(1){
        set_cursor_pos(1,2);
        measure();
        write_int_LCD(count);
    }
}
//++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++

void measure(){
    // Configuration so that TIMER1 counts up to 1 second
    TMR1L = 0xEE;
    TMR1H = 0x85;
    T1GCONbits.TMR1GE = 0;
    PIR1bits.TMR1IF = 0;
    // Initialize TIMER1 with a 1:8 prescaler using the instruction clock (FOSC/4) as clock source
    T1CON = 0b00110001;    
    while(PIR1bits.TMR1IF == 0){
    // Initialize TIMER0 as an 8 bit counter that increases every time the T0CKI pin transitions from
    // high to low   
        T0CON = 0b11111000;
    }
    count = TMR0L;
    TMR0L = 0;
    T1CON = 0;
    T0CON = 0;
    PIR1bits.TMR1IF = 0;
}
