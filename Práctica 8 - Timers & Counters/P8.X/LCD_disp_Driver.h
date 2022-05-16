//++++++++++++++++++++++++++++| Directivas |++++++++++++++++++++++++++++++++++++
                     /* Puerto del bus de datos */
#define LCDdataWrite LATD
#define LCDdataRead  PORTD
#define LCDdataDir TRISD
                     /* Puerto de control */
#define LCD_RS       LATCbits.LATC2
#define LCD_RS_Dir   TRISCbits.TRISC2
#define LCD_RW       LATCbits.LATC1
#define LCD_RW_Dir   TRISCbits.TRISC1
#define LCD_E        LATCbits.LATC0
#define LCD_E_Dir    TRISCbits.TRISC0
                     /* Instrucciones */
// Function set
/* RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *	0 	0 	0 	0 	1 	DL 	N 	F 	? 	?
 *	(DL) data length				DL=1: 8 bits, 	DL=0: 4 bits
 *	(N)  number of display lines  	N=1:  2 lines, 	 N=0: 1 line
 *	(F)	 character font  			F=1:  5x10 dots, F=0: 5x8 dots
 */
#define setLCD_8bits_2Lines_smallFont  0b00111000
#define setLCD_8bits_2Lines_bigFont    0b00111100
// Display ON/OFF
/* RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	0 	0 	0 	0 	1 	D 	C 	B
 *	Sets entire Display on/off				(D).
 *	Cursor on/off 							(C).
 *	Blinking of cursor position character 	(B).
 */
#define  DISPLAY_ALL_ON				0b00001111
#define  DISPLAY_ON_C_OFF_B_OFF		0b00001100
#define  DISPLAY_ON_C_ON_B_OFF      0b00001110
#define  DISPLAY_ON_C_OFF_B_ON      0b00001101
// Entry mode set
/* Sets cursor move direction and specifies display shift.
 * These operations are performed during data write and read.
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	0 	0 	0 	0 	0 	1  I/D 	S
 *  I/D=1	: Increment
 *  I/D=0	: Decrement
 *  S=1	: Accompanies display shift
 */
#define	 EMS_INC_S			0b00000110
#define  EMS_DEC_S          0b00000100
// Cursor or display shift
/* Moves cursor and shifts display without changing DDRAM contents.
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
   	0 	0 	0 	0 	0 	1  S/C R/L 	? 	?
	S/C=1: Display shift			S/C=0: Cursor move
	R/L=1: Shift to the right		R/L=0: Shift to the left
 */
#define	DISP_MOVE_RIGHT		0b00011100
#define	DISP_MOVE_LEFT		0b00011000
#define	CURSOR_MOVE_RIGHT	0b00010100
#define	CURSOR_MOVE_LEFT	0b00010000
// Set	DDRAM
/* RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	1  ADD ADD ADD ADD ADD ADD ADD
 */
#define LCD_LINE0 0x80
#define LCD_LINE1 0xC0
// Instrucciones básicas
#define Return_Home 0b00000010
#define Clear_DISP  0b00000001

//++++++++++++++++++++++++++++| Declaración de funciones |++++++++++++++++++++++
void LCD_init (void);
void LCD_cmd (char);
void set_LCD_dir (char);
void send_to_LCD (char);
void set_cursor_pos(char,char);
void move_cursor_n_times(int,char);
void write_string_LCD (const char*);
void write_int_LCD (int x);

//+++++++++++++++++++++++++++++| Variables globales |+++++++++++++++++++++++++++
char LCDdir;
