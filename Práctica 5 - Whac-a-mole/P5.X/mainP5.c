///++++++++++++++++++|Headers y Librerias|+++++++++++++++///
#include "device_config-1.h"
#include <stdlib.h>
#include <math.h>

///++++++++++|Directivas|++++++++++///
#define _XTAL_FREQ 1000000

///++++++++++|Tipos de datos|++++++++++///
enum por_direc{output = 0,input = 255};     //Define la direcci�n de los puertos, output=0b00000000, input=0b11111111
enum por_ACDC {digital = 0,analog = 255};   //Define si el puerto ser� digital o an�logo, digital=0b00000000, analog=0b11111111

///++++++++++|Declaraci�n de funciones|++++++++++///
void portsInit(void);
void knightRider(void);
void rndNumGen(void);
 int checkButton();

///++++++++++|MAIN|++++++++++///
void main(void){
    portsInit();                            //Se llama a la funci�n para configurar puertos
    while(1){
        rndNumGen();                        //Se enciende un LED de forma aleatoria
        __delay_ms(500);
        uint8_t buttPress = checkButton();  //Se le asigna el n�mero del bot�n presionado a la variable buttPress
        if (PORTA == buttPress){            //Se verifica si el LED corresponde al bot�n
            PORTA = 0;
            knightRider();                  //Si s� corresponde se llama a knightRider
            __delay_ms(100);
        } else{                             //Si no corresponde
            __delay_ms(200);                //Se espera 0.2 segundos
            buttPress = checkButton();          
            if (PORTA == buttPress){        //Se vuelve a verificar que el bot�n y el LED coincidad
                PORTA = 0;
                knightRider();              //Si s� corresponde se llama a knightRider
                __delay_ms(100);
            }
        }                                   //Si no corresponde se reinicia el ciclo
    }
}

///++++++++++|Funciones|+++++++++++///
//Funci�n para configurar puertos
void portsInit(void){
    //Configuramos los puertos que usamos en �ste programa
    //El puerto A ser� usado para los LEDS
    TRISA = output;                         //Todos los pines son salidas
    ANSELA = digital;                       //Todos los pines son digitales
    PORTA = 0;                              //El valor inicial de todos los LEDS es 0
    //El puerto B ser� usado para los botones
    TRISB = input;                          //Todos los pines son entradas
    ANSELB = digital;                       //Todos los pines son digitales
}
//Funci�n para hacer el efecto de knight rider. Adaptado de: https://github.com/funkyguy4000/AVR-Programs/blob/master/Programs/C%20programs/Knight%20Rider/Knight%20Rider.c
void knightRider(void){
    //Ida
    for(uint8_t i = 0; i<7; i++)	
		{			
			PORTA |= (1<<i); 
			__delay_ms(20);	
			PORTA &= ~(1<<i);	
			__delay_ms(20);	
		}
    //Regreso
    for(uint8_t i = 7; i>0; i--)
		{
			PORTA |= (1<<i);
			__delay_ms(20);
			PORTA &= ~(1<<i);
			__delay_ms(20);
		}
    //Ida
    for(uint8_t i = 0; i<7; i++)	
		{			
			PORTA |= (1<<i); 
			__delay_ms(20);	
			PORTA &= ~(1<<i);	
			__delay_ms(20);	
		}
    //Regreso
    for(uint8_t i = 7; i>0; i--)
		{
			PORTA |= (1<<i);
			__delay_ms(20);
			PORTA &= ~(1<<i);
			__delay_ms(20);
		}
}
//Funci�n para encender un LED de forma aleatoria
void rndNumGen(void){
    int i = (rand()%8);
    i = pow(2,i);
    PORTA = i;
}
//Funci�n que me regresa el n�mero del bot�n que se presiona
int checkButton(){
    int j = ~PORTB;
    return j;
}