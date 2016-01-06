/* Pin definitions for this project */

#ifndef __PINS_h
#define __PINS_h


/* 16 bitowa magistrala danych lcd */
#define LCD_DATA_L PORTC
#define LCD_DATA_H PORTA
#define LCD_DATA_L_DIR DDRC
#define LCD_DATA_H_DIR DDRA


/* piny sterujace lcd TFT */
#define LCD_STER_DIR DDRD
#define LCD_STER PORTD
#define LCD_CS (1<<PD7)
#define LCD_RD (1<<PD6)
#define LCD_WR (1<<PD5)
#define LCD_RS (1<<PD4)
#define LCD_RESET (1<<PD3)

/* Piny dotyku do, dzia³ania koniecznie potrzebne: CLK, IN, OUT, PENIRQ */

#define TOUCH_CLK 0
#define TOUCH_CLK_PORT PORTB
#define TOUCH_CLK_DDR DDRB
#define TOUCH_CLK_PIN PINB

#define TOUCH_IN 1
#define TOUCH_IN_PORT PORTB
#define TOUCH_IN_DDR DDRB
#define TOUCH_IN_PIN PINB

#define TOUCH_OUT 2
#define TOUCH_OUT_PORT PORTB
#define TOUCH_OUT_DDR DDRB
#define TOUCH_OUT_PIN PINB

#define TOUCH_PENIRQ 3
#define TOUCH_PENIRQ_PORT PORTB
#define TOUCH_PENIRQ_DDR DDRB
#define TOUCH_PENIRQ_PIN PINB


#define TOUCH_BUSY 4
#define TOUCH_BUSY_PORT PORTC
#define TOUCH_BUSY_DDR DDRC
#define TOUCH_BUSY_PIN PINC







#endif
