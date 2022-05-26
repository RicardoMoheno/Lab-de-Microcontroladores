////++++++++++++++++++++++++| LIBRARIES / HEADERS |+++++++++++++++++++++++++++++
#include "device_config.h"

//++++++++++++++++++++++++++| DIRECTIVES |++++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 8000000
#define BUTTON PORTBbits.RB0

//++++++++++++++++++++++++++| DATA TYPES |++++++++++++++++++++++++++++++++++++++
enum por_dir {output = 0x00, input = 0xFF};
enum por_ACDC {digital = 0x00, analog = 0xFF}; 

//++++++++++++++++++++++++++| ISRs |++++++++++++++++++++++++++++++++++++++++++++
void high_isr (void);

//++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++++++
void setup(void);
void delay1S(void);
void char_to_seg(char);

void state1(void);
void state2(void);
void state3(void);
void state4(void);
void state5(void);

//++++++++++++++++++++++++++| VARIABLE DECLARATIONS |+++++++++++++++++++++++++++
char count = 0;

//++++++++++++++++++++++++++| MAIN |++++++++++++++++++++++++++++++++++++++++++++
void main(void){
    setup();
    while(1){
        state1();
        state2();
        while (count != 0){
            state3();
            count--;
            char_to_seg(count);
        }
        state4();
        state5();
    }
}

//++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++++++
void setup(){
    // Oscillator Init
    OSCCON = 0b01100100;    // Set internal oscillator to 8 MHz and stable
    
    // Interrupt Init
    RCONbits.IPEN = 1;      // Enable interrupt priority
    INTCONbits.GIEH = 1;    // Enable high priority
    INTCONbits.GIEL = 1;    // Enable low priority
    
    INTCON2bits.INTEDG0 = 0;// INT0 interrupts on falling edge
    INTCONbits.INT0IE = 1;  // Enable INT0 (always high priority)
    INTCONbits.INT0IF = 0;  // Turns off INT0 interrupt flag
    
    // Ports Init
    ANSELD = digital;       // Port D set as digital for LEDs
    TRISD = output;         // Port D set as output for LEDs
    PORTD = 0;
    ANSELA = digital;       // Port A set as digital for count display
    TRISA = output;         // Port A set as output for count display
    PORTA = 0;
    ANSELB = digital;       // Port B set as digital for button
    TRISBbits.TRISB2 = 1;   // Pin 2 of Port B set as input for button
    TRISBbits.TRISB1 = 0;   // Pin 1 of Port B set as output generate interrupt signal
    TRISBbits.TRISB0 = 1;   // Pin 0 of Port B set as input for INT0 external interrupt
}

void state1(){
    LATD = 0x14;
    delay1S();
    delay1S();
    delay1S();
}

void state2(){
    LATD = 0x12;
    delay1S();
}

void state3(){
    LATD = 0x99;
    delay1S();
}

void state4(){
    LATD = 0x41;
    delay1S();
    delay1S();
    delay1S();
}

void state5(){
    LATD = 0x21;
    delay1S();
}

void delay1S(){
    TMR0L = 0xEE;
    TMR0H = 0x85;
    T0CON = 0b10000101;     // Enable Timer0 as a 16 bit timer with a 64 prescaler and using the internal clock
    while (INTCONbits.TMR0IF == 0); // Wait for the flag to turn on
    INTCONbits.TMR0IF = 0;  // Turn off TMR0 overflow flag
    T0CON = 0;
}

void __interrupt (high_priority) high_isr (void){
    __delay_ms(30);     // Debouncing delay
    if (BUTTON == 0){
        count++;
        if (count > 8){
            count = 8;
        }
        char_to_seg(count);
    }
    INTCONbits.INT0IF = 0;
}

void char_to_seg(char num){
    switch(num){
        case 0:  PORTA = ~(0b00111111); break;
        case 1:  PORTA = ~(0b00000110); break;
        case 2:  PORTA = ~(0b01011011); break;
        case 3:  PORTA = ~(0b01001111); break;
        case 4:  PORTA = ~(0b01100110); break;
        case 5:  PORTA = ~(0b01101101); break;
        case 6:  PORTA = ~(0b01111101); break;
        case 7:  PORTA = ~(0b00000111); break;
        case 8:  PORTA = ~(0b01111111); break;
        case 9:  PORTA = ~(0b01100111); break;
        case 10: PORTA = ~(0b01110111); break;
        case 11: PORTA = ~(0b01111100); break;
        case 12: PORTA = ~(0b01011000); break;
        case 13: PORTA = ~(0b01011110); break;
        case 14: PORTA = ~(0b01111001); break;
        default: PORTA = ~(0b01110001); break;
    }
}
