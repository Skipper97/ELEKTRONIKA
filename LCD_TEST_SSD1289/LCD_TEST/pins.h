/* Pin definitions for this project */

#ifndef __PINS_h
#define __PINS_h


/* 16 bitowa magistrala danych lcd */
#define LCD_DATA_L PORTC
#define LCD_DATA_H PORTA
#define LCD_DATA_L_DIR DDRC // for direction
#define LCD_DATA_H_DIR DDRA // for direction


/* lcd definition */
#define LCD_STER_DIR DDRD
#define LCD_STER PORTD
#define LCD_CS (1<<PD7)
#define LCD_RD (1<<PD6)
#define LCD_WR (1<<PD5)
#define LCD_RS (1<<PD4)
#define LCD_RESET (1<<PD3)

/*
#define TFT_WR       1
#define TFT_RD       2
#define TFT_CS       3
#define TFT_RST      4
*/
// PORT C

#define TOUCH_CLK    0
#define TOUCH_CLK_PORT  PORTB
#define TOUCH_CLK_DDR   DDRB
#define TOUCH_CLK_PIN   PINB

#define TOUCH_IN     1
#define TOUCH_IN_PORT  PORTB
#define TOUCH_IN_DDR   DDRB
#define TOUCH_IN_PIN   PINB

#define TOUCH_BUSY   2
#define TOUCH_BUSY_PORT  PORTB
#define TOUCH_BUSY_DDR   DDRB
#define TOUCH_BUSY_PIN   PINB

#define TOUCH_OUT    3
#define TOUCH_OUT_PORT  PORTB
#define TOUCH_OUT_DDR   DDRB
#define TOUCH_OUT_PIN   PINB

#define TOUCH_PENIRQ 4
#define TOUCH_PENIRQ_PORT  PORTB
#define TOUCH_PENIRQ_DDR   DDRB
#define TOUCH_PENIRQ_PIN   PINB

#define TEMP       PB5
#define TEMP_PORT  PORTB
#define TEMP_DDR   DDRB
#define TEMP_PIN   PINB


#endif
