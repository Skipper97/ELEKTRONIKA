/**************************************************************************************************
*	  			  SSD1289 color Graphical LCD Display Driver
* File name		: SSD1289.h
* Programmer 	: jaruwit supa
* Web           : www.circuitidea.com
* Note			: SSD1289 16 bit interface.for 8 bit use 74lv573 to latch HI byte
* Language		: avrGCC
* Hardware		: atmega16
* Date			: 01/05/2009
************************************************************************************************/

#ifndef __SSD1289X_H__
#define __SSD1289X_H__

/* _____CONFIG DEFINES_____________________________________________________ */
//#define LCD_8_BIT_MODE		// 8 bit bus data using latch. *** Need jumpper for 8 bit *** 
//#define LCD_BL_HARDWARE	  	// using back light internal jumper
//#define LCD_RESET_HARDWARE  // using hardware control reset pin to reset
//#define LCD_WRITE_ONLY	  	// write only mode no read back
#define LCD_V2			  	// hardware v2 
#define Horizontal		  	// Horizontal or vertical
//#define Reverse			  // reverse direction

/* _____HARDWARE DEFINES_____________________________________________________ */
#define LCD_LO_DDR  DDRA
#define LCD_LO_PORT PORTA
#define LCD_LO_PIN  PINA

/*
#ifdef LCD_8_BIT_MODE
	#define LCD_HI_DDR  LCD_LO_DDR
	#define LCD_HI_PORT LCD_LO_PORT
	#define LCD_HI_PIN  LCD_LO_PIN
#else
*/
	#define LCD_HI_DDR  DDRC
	#define LCD_HI_PORT PORTC
	#define LCD_HI_PIN  PINC
//#endif
/*
#ifndef LCD_V2
    #define LCD_CS_DDR  DDRC
    #define LCD_CS_PORT PORTC
    #define LCD_CS_PIN  PINC
    #define LCD_CS_BIT  5
    
    #define LCD_RS_DDR  DDRC
    #define LCD_RS_PORT PORTC
    #define LCD_RS_PIN  PINC
    #define LCD_RS_BIT  4
    
    #define LCD_WR_DDR  DDRC
    #define LCD_WR_PORT PORTC
    #define LCD_WR_PIN  PINC
    #define LCD_WR_BIT  3
#else
*/
    #define LCD_CS_DDR  DDRB
    #define LCD_CS_PORT PORTB
    #define LCD_CS_PIN  PINB
    #define LCD_CS_BIT  4
    
    #define LCD_RS_DDR  DDRB
    #define LCD_RS_PORT PORTB
    #define LCD_RS_PIN  PINB
    #define LCD_RS_BIT  5
    
    #define LCD_WR_DDR  DDRB
    #define LCD_WR_PORT PORTB
    #define LCD_WR_PIN  PINB
    #define LCD_WR_BIT  6
//#endif
    
//#ifdef LCD_WRITE_ONLY
	#define LCD_RD_DDR  DDRB
    #define LCD_RD_PORT PORTB
    #define LCD_RD_PIN  PINB
    #define LCD_RD_BIT  7
//#endif

#ifndef LCD_RESET_HARDWARE
    #define LCD_RST_DDR  DDRG
    #define LCD_RST_PORT PORTG
    #define LCD_RST_PIN  PING
    #define LCD_RST_BIT  4
#endif
    
#ifndef LCD_BL_HARDWARE
	#define LCD_BL_DDR  DDRG
	#define LCD_BL_PORT PORTG
	#define LCD_BL_PIN  PING
	#define LCD_BL_BIT  3
#endif

/*
#ifdef LCD_8_BIT_MODE
	#ifndef LCD_V2
    	#define LCD_LATCH_DDR  DDRC
    	#define LCD_LATCH_PORT PORTC
    	#define LCD_LATCH_PIN  PINC
    	#define LCD_LATCH_BIT  1
	#else

    	#define LCD_LATCH_DDR  DDRB
    	#define LCD_LATCH_PORT PORTB
    	#define LCD_LATCH_PIN  PINB
    	#define LCD_LATCH_BIT  0
        #endif
#endif
*/

#define LCD_SET_CS()  LCD_CS_PORT  |=  (1<<LCD_CS_BIT)
#define LCD_CLR_CS()  LCD_CS_PORT  &= ~(1<<LCD_CS_BIT)
#define LCD_DIR_CS(x) LCD_CS_DDR   |=  (1<<LCD_CS_BIT)

#define LCD_SET_RS()  LCD_RS_PORT  |=  (1<<LCD_RS_BIT)
#define LCD_CLR_RS()  LCD_RS_PORT  &= ~(1<<LCD_RS_BIT)
#define LCD_DIR_RS(x) LCD_RS_DDR   |=  (1<<LCD_RS_BIT)

#define LCD_SET_WR()  LCD_WR_PORT  |=  (1<<LCD_WR_BIT)
#define LCD_CLR_WR()  LCD_WR_PORT  &= ~(1<<LCD_WR_BIT)
#define LCD_DIR_WR(x) LCD_WR_DDR   |=  (1<<LCD_WR_BIT)

#define LCD_SET_RD()  LCD_RD_PORT  |=  (1<<LCD_RD_BIT)
#define LCD_CLR_RD()  LCD_RD_PORT  &= ~(1<<LCD_RD_BIT)
#define LCD_DIR_RD(x) LCD_RD_DDR   |=  (1<<LCD_RD_BIT)

#ifndef LCD_RESET_HARDWARE
	#define LCD_SET_RST()  LCD_RST_PORT |= (1<<LCD_RST_BIT)
	#define LCD_CLR_RST()  LCD_RST_PORT &= ~(1<<LCD_RST_BIT)
	#define LCD_DIR_RST(x) LCD_RST_DDR  |= (1<<LCD_RST_BIT)
#else
	#define LCD_SET_RST()
	#define LCD_CLR_RST()
	#define LCD_DIR_RST(x)
#endif

#define LCD_SET_LATCH()  LCD_LATCH_PORT |=  (1<<LCD_LATCH_BIT)
#define LCD_CLR_LATCH()  LCD_LATCH_PORT &= ~(1<<LCD_LATCH_BIT)
#define LCD_DIR_LATCH(x) LCD_LATCH_DDR  |=  (1<<LCD_LATCH_BIT)

#ifndef LCD_BL_HARDWARE
	#define LCD_BL_OFF()	LCD_BL_DDR  |=  (1<<LCD_BL_BIT); \
							LCD_BL_PORT &= ~(1<<LCD_BL_BIT)
	#define LCD_BL_ON()		LCD_BL_DDR  |=  (1<<LCD_BL_BIT); \
							LCD_BL_PORT |=  (1<<LCD_BL_BIT)
#else
	#define LCD_BL_OFF()
	#define LCD_BL_ON()
#endif


/*
#ifdef LCD_8_BIT_MODE
	#define LCD_INPUT()		LCD_LO_DDR = 0x00
	#define LCD_OUTPUT()	LCD_LO_DDR = 0xFF //; DDRA = 0xFF; PORTA = 0xFF

	#define LCD_MODE()		LCD_LO_DDR = 0xFF;\
							LCD_SET_LATCH(); \
							LCD_DIR_LATCH(1);

	#define LCD_SET_DBH(x)	LCD_HI_PORT = x; \
							LCD_SET_LATCH(); \
							LCD_CLR_LATCH();
//							asm volatile ("nop");


	#define LCD_SET_DBL(x)	LCD_LO_PORT = x

	// read back not support in 8 bit bus
	#define LCD_GET_DBH()	LCD_HI_PIN
	#define LCD_GET_DBL()	LCD_LO_PIN
#else
*/
	#define LCD_INPUT()		LCD_LO_DDR = 0x00; \
							LCD_HI_DDR = 0x00
	#define LCD_OUTPUT()	LCD_LO_DDR = 0xFF; \
							LCD_HI_DDR = 0xFF
	#define LCD_MODE()

	#define LCD_SET_DBH(x)	LCD_HI_PORT = x
	#define LCD_SET_DBL(x)	LCD_LO_PORT = x

	#define LCD_GET_DBH()	LCD_HI_PIN
	#define LCD_GET_DBL()	LCD_LO_PIN
//#endif

/* _____PUBLIC DEFINE_____________________________________________________ */
#ifdef Horizontal
	// Horizontal and vertical screen size
	#define SCREEN_HOR_SIZE   240UL
	#define SCREEN_VER_SIZE   320UL

#else
	// Horizontal and vertical screen size
	#define SCREEN_HOR_SIZE    320UL
	#define SCREEN_VER_SIZE    240UL
#endif

// color
#define BLACK                       RGB(0x00, 0x00, 0x00)
#define WHITE                       RGB(0xFF, 0xFF, 0xFF)
#define RED                         RGB(0xFF, 0x00, 0x00)
#define GREEN                       RGB(0x00, 0xFF, 0x00)
#define BLUE                        RGB(0x00, 0x00, 0xFF)
#define YELLOW                      RGB(0xFF, 0xFF, 0x00)
#define MAGENTA                     RGB(0xFF, 0x00, 0xFF)
#define CYAN                        RGB(0x00, 0xFF, 0xFF)
#define GRAY                        RGB(0x80, 0x80, 0x40)
#define SILVER                      RGB(0xA0, 0xA0, 0x80)
#define GOLD                        RGB(0xA0, 0xA0, 0x40)

/* _____PUBLIC VARIABLE_____________________________________________________ */
extern unsigned int _color;

/* _____PUBLIC FUNCTIONS_____________________________________________________ */
extern void LCD_Reset(void);
extern void LCD_SetCursor(unsigned int x, unsigned int y);
extern void LCD_SetArea(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
extern void LCD_PutPixel(unsigned int x, unsigned int y);
extern void LCD_Rect(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom, unsigned int color);
extern void LCD_Clear(unsigned int color);
extern void LCD_DrawSymbol(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char t, const unsigned char *pImage);
extern void LCD_DrawImage(unsigned int x, unsigned int y, const unsigned char *pImage);

// low level
void LCD_WrCmd(unsigned char cmd);
void LCD_WrDat(unsigned int val);

/* _____DEFINE MACRO_________________________________________________________ */
// fast write is macro define. prevent call routine
#define LCD_OPEN_WRITE()		LCD_CLR_CS();\
								LCD_SET_RS();

#define LCD_FAST_WRITE(val)		LCD_SET_DBH((val)>>8); \
								LCD_SET_DBL(val); \
								LCD_CLR_WR(); \
								LCD_SET_WR();

#define LCD_FAST_WRITE_CS(val)	LCD_CLR_CS();\
								LCD_SET_DBH((val)>>8); \
								LCD_SET_DBL(val); \
								LCD_CLR_WR(); \
								LCD_SET_WR(); \
								LCD_SET_CS()

#define LCD_FAST_WRITE2(H,L)	LCD_SET_DBH(H); \
								LCD_SET_DBL(L); \
								LCD_CLR_WR(); \
								LCD_SET_WR();

#define LCD_FAST_WRITE2_CS(H,L)	LCD_CLR_CS();\
								LCD_SET_DBH(H); \
								LCD_SET_DBL(L); \
								LCD_CLR_WR(); \
								LCD_SET_WR(); \
								LCD_SET_CS()

#define LCD_CLOSE() 			LCD_SET_CS()



#define GetMaxX() 		((unsigned int)SCREEN_HOR_SIZE-1)
#define GetMaxY() 		((unsigned int)SCREEN_VER_SIZE-1)

#define RGB(red, green, blue)	((unsigned int)( (( red >> 3 ) << 11 ) | \
								(( green >> 2 ) << 5  ) | \
								( blue  >> 3 )))

#define SetColor(color) _color = color
#define GetColor()      _color

#endif
