//Directivas
/*
 * Usando el Puerto B para trabajar haciendo uso de las resitencias pull-up
 * que inlcuye el PIC18. En caso de usar otro puerto cambiar las siguientes
 * directivas.
 */
#define kbdWrite    LATB
#define kbdRead     PORTB
#define kbdANSEL    ANSELB
#define kbdTRIS     TRISB

// Declaracion de funciones
void kbd_init(void);
char kbd_scanner (void);
char get_Key(void);

// Declaración de variables y constantes
const char kbdMatrix[4][4] = {{'1','2','3','+'},
                              {'4','5','6','-'},
                              {'7','8','9','*'},
                              {'=','0','C','/'}};
char key;



