
/* 16 bitowa magistrala danych lcd */
#define LCD_DATA_L PORTB
#define LCD_DATA_H PORTC
#define LCD_DATA_L_DIR DDRB
#define LCD_DATA_H_DIR DDRC


/* piny sterujace lcd TFT */
#define LCD_STER_DIR DDRA
#define LCD_STER PORTA
#define LCD_CS (1<<PA7)
#define LCD_RD (1<<PA6)
#define LCD_WR (1<<PA5)
#define LCD_RS (1<<PA4)
#define LCD_RESET (1<<PA3)

/* Piny dotyku do, dzia³ania koniecznie potrzebne: CLK, IN, OUT, PENIRQ */
//
//#define TOUCH_CLK 0
//#define TOUCH_CLK_PORT PORTB
//#define TOUCH_CLK_DDR DDRB
//#define TOUCH_CLK_PIN PINB
//
//#define TOUCH_IN 1
//#define TOUCH_IN_PORT PORTB
//#define TOUCH_IN_DDR DDRB
//#define TOUCH_IN_PIN PINB
//
//#define TOUCH_OUT 2
//#define TOUCH_OUT_f
//
//#define TOUCH_BUSY 4
//#define TOUCH_BUSY_PORT PORTA
//#define TOUCH_BUSY_DDR DDRA
//#define TOUCH_BUSY_PIN PINA

