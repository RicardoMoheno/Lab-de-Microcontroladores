#include "4x4_kbd_Driver.h"
#include "device_config.h"
#define _XTAL_FREQ 8000000

void kbd_init (void){
    kbdANSEL = 0x00;  // Se configura el puerto del teclado como digital
    kbdTRIS = 0x0F;   // Se usan los pines 0 a 3 como entradas (columnas) 
                      // y 4 a 7 como salidas (filas)
    /* En caso de NO usar el puerto B para el teclado, se pueden comentar las 
     * siguientes líneas y conectar resitencias de pull-up en los pines de
     * entrada del puerto quese use.
     */
    WPUB = 0x0F;            // Para el Puerto B usar las resistencias de 
                            // pull-up en los pines 0 a 3
    INTCON2bits.RBPU = 0;   // Encender las resistencias de pull-up         
}

char kbd_scanner(void){
    kbdWrite = 0xE0;
    switch (kbdRead){
        case 0xEE: return kbdMatrix[0][0]; break;
        case 0xED: return kbdMatrix[0][1]; break;
        case 0xEB: return kbdMatrix[0][2]; break;
        case 0xE7: return kbdMatrix[0][3]; break;
    }
    kbdWrite = 0xD0;
    switch (kbdRead){
        case 0xDE: return kbdMatrix[1][0]; break;
        case 0xDD: return kbdMatrix[1][1]; break;
        case 0xDB: return kbdMatrix[1][2]; break;
        case 0xD7: return kbdMatrix[1][3]; break;
    }
    kbdWrite = 0xB0;
    switch (kbdRead){
        case 0xBE: return kbdMatrix[2][0]; break;
        case 0xBD: return kbdMatrix[2][1]; break;
        case 0xBB: return kbdMatrix[2][2]; break;
        case 0xB7: return kbdMatrix[2][3]; break;
    }
    kbdWrite = 0x70;
    switch (kbdRead){
        case 0x7E: return kbdMatrix[3][0]; break;
        case 0x7D: return kbdMatrix[3][1]; break;
        case 0x7B: return kbdMatrix[3][2]; break;
        case 0x77: return kbdMatrix[3][3]; break;
    }
    kbdWrite = 0x00;
    return 'x';
}

char get_Key(){
    key = 'x';
    while (key == 'x'){
        key = kbd_scanner();
        __delay_ms(100);
    }
    return key;
}
