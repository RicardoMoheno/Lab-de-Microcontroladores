////+++++++++++++++++++++++++++++++++++++| LIBRARIES / HEADERS |+++++++++++++++++++++++++++++++++++++
#include "device_config.h"
#include <stdint.h>
#include <math.h>

//+++++++++++++++++++++++++++++++++++++| DIRECTIVES |+++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 8000000
#define SWEEP_STEP 5

//+++++++++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++++++++++++++++
   void portsInit   (void);
uint8_t char_to_seg (uint8_t);
   void send_to_disp(uint32_t);
   void key_scanner (void);

//+++++++++++++++++++++++++++++++++++++| VARIABLE DECLARATIONS |++++++++++++++++++++++++++++++++++++
uint32_t kbdMatrix[4][4] = {{1 ,2 ,3 ,10},  //This matrix represents the position of the buttons
                            {4 ,5 ,6 ,11},  //of our key pad
                            {7 ,8 ,9 ,12},
                            {15,0 ,14,13}}; 

uint32_t new_num,curr_num = 0x10101010;     //This two variables save the value of the pressed buttons

//+++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++
void main(void){ 
    portsInit();                            //Configure the ports of the PIC18
    while(1){                               //This will be done all the time
        while ((~PORTB & 0x0F) != 0){       //When the lower nibble is different form 0 (when a key is pressed)...
            key_scanner();                  //Call the key_scanner function to get the new number to be registered
            curr_num = curr_num << 8;       //The current number gets shifted to the next position to the left
            curr_num = curr_num + new_num;  //Add the new number to the current number
            __delay_ms(500);                //A delay to get only one number
        }
        send_to_disp(curr_num);             //Display the current number in the 7 segment display
    }
}

//+++++++++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++++
void portsInit(void){ 
    OSCCON = 0b01110100;    // Set the internal oscillator to 8MHz and stable
    //PORTB Config for the KeyPad
    ANSELB = 0X00;          // Set port B as Digital for keypad driving
    TRISB = 0x0F;           // For port B, set pins 4 to 7 as outputs (rows) and 0 to 3 as inputs (cols)
    WPUB = 0x0F;            // For port B, set the pull-up resistors for pins 0 to 3
    INTCON2bits.RBPU = 0;   // For port B turn on pull-up resistors
    
    //PORTA Config to choose the display's cathode
    ANSELA = 0x00;          // Set port A as Digital for 7 segment cathode selection (only 4 pins used)  
    TRISA  = 0x00;          // For Port A, set pins as outputs for cathode selection
    
    //PORTD Config to turn on the display's LEDs
    ANSELD = 0x00;          // Set port D as Digital for 7 segment anodes
    TRISD  = 0x00;          // for Port D, set all pins as outputs for 7 segment anodes
    }

//This function send a number to the display. It first brakes the 32 bit number into four 8 bit numbers and sends each
//one to each of the 4 cathodes of the display
void send_to_disp(uint32_t disp_word){
    for (char i = 0; i < 4; i++){
        int internal_sweep = (int) pow(2, i);
        int sweep = 0x0F & ~internal_sweep;
        LATA = (char) sweep;
        uint8_t num_disp = 0x000000FF & (disp_word >> i*8);
        LATD = char_to_seg(num_disp);
        __delay_ms(SWEEP_STEP);
    } 
}

//This function translates an unsigned 8 bit integer into the configuration that turns on 
//the different LED's of the 7 segment display
uint8_t char_to_seg(uint8_t num){
    uint8_t segments;
    switch(num){            //PGEDCBAF
        case 0:  segments = 0b00111111; break;
        case 1:  segments = 0b00000110; break;
        case 2:  segments = 0b01011011; break;
        case 3:  segments = 0b01001111; break;
        case 4:  segments = 0b01100110; break;
        case 5:  segments = 0b01101101; break;
        case 6:  segments = 0b01111101; break;
        case 7:  segments = 0b00000111; break;
        case 8:  segments = 0b01111111; break;
        case 9:  segments = 0b01100111; break;
        case 10: segments = 0b01110111; break;
        case 11: segments = 0b01111100; break;
        case 12: segments = 0b01011000; break;
        case 13: segments = 0b01011110; break;
        case 14: segments = 0b01111001; break;
        case 15: segments = 0b01110001; break;
        default: segments = 0b00000000; break;
    }
    return segments;
}

//This function, when called, scans the key pad and, depending on the button pressed,
//saves the value of the button pressed in the variable new_num from the key board matrix
void key_scanner(){
    LATB = 0xE0; 
    switch (PORTB){
        case 0xEE: new_num = kbdMatrix[0][0]; break; //0x01
        case 0xED: new_num = kbdMatrix[0][1]; break; //0x02
        case 0xEB: new_num = kbdMatrix[0][2]; break; //0x03
        case 0xE7: new_num = kbdMatrix[0][3]; break; //0x0A
    }
    LATB = 0xD0; 
    switch (PORTB){
        case 0xDE: new_num = kbdMatrix[1][0]; break; //0x04
        case 0xDD: new_num = kbdMatrix[1][1]; break; //0x05
        case 0xDB: new_num = kbdMatrix[1][2]; break; //0x06
        case 0xD7: new_num = kbdMatrix[1][3]; break; //0x0B
    }
    LATB = 0xB0; 
    switch (PORTB){
        case 0xBE: new_num = kbdMatrix[2][0]; break; //0x07
        case 0xBD: new_num = kbdMatrix[2][1]; break; //0x08
        case 0xBB: new_num = kbdMatrix[2][2]; break; //0x09
        case 0xB7: new_num = kbdMatrix[2][3]; break; //0x0C
    }
    LATB = 0x70; 
    switch (PORTB){
        case 0x7E: new_num = kbdMatrix[3][0]; break; //0x0F
        case 0x7D: new_num = kbdMatrix[3][1]; break; //0x00
        case 0x7B: new_num = kbdMatrix[3][2]; break; //0x0E
        case 0x77: new_num = kbdMatrix[3][3]; break; //0x0D
    }
    LATB = 0x00; //Reset the port in order to work correctly
}
