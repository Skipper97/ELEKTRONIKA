#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "pins.h"
#include "TFT.h"
#include "fonts.h"
#include "uart.h"
#include "shift.h"
#include "touch.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

void TFT_pattern1(void) {
  uint16_t i;
  LCD_STER &= ~(LCD_CS);
  TFT_write_address(0, 0, 239, 319);

  for(i = 0; i <= 0x9600; i++)
  {
    TFT_write_data(0xff00);
    TFT_write_data(0x00ff);
  }

  LCD_STER |= (LCD_CS);
  LCD_STER |= (LCD_RS);
}

void TFT_pattern2(void) {
  uint16_t i;
  LCD_STER &= ~(LCD_CS);
  TFT_write_address(0, 0, 239, 319);

  for(i = 0; i <= 0x9600; i++)
  {
    TFT_write_data(0x00ff);
    TFT_write_data(0xff00);
  }

  LCD_STER |= (LCD_CS);
  LCD_STER |= (LCD_RS);
}

uint16_t read_temp(void) {
  uint16_t temp = 1;



  return temp;
}

int main(void) {
/*
  configure_as_output(SHIFT_DATA);
  configure_as_output(SHIFT_LATCH);
  configure_as_output(SHIFT_CLOCK);

  configure_as_output(TOUCH_IN);
  configure_as_output(TOUCH_CLK);

  configure_as_output(TFT_RS);
  configure_as_output(TFT_WR);
  configure_as_output(TFT_CS);
  configure_as_output(TFT_RD);
  configure_as_output(TFT_RST); */


  TFT_init();

  touch_init();

  TFT_fill(0xFFFF);


  TFT_char(FONT_16x16, 'D', 5, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'z', 22, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'i', 39, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'a', 56, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'l', 73, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'a', 90, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, ' ', 107, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'L', 124, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'C', 141, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'D', 158, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, ';', 175, 5, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'o', 192, 5, 0, 0xFFFF, 16, 16);


  TFT_char(FONT_16x16, 'O', 5, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 's', 22, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'k', 39, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'u', 56, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'r', 73, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'w', 90, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'e', 107, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 's', 124, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'y', 141, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'n', 158, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, ':', 175, 30, 0, 0xFFFF, 16, 16);
  TFT_char(FONT_16x16, 'D', 192, 30, 0, 0xFFFF, 16, 16);
  uint16_t x, y, box_x1=0xFFFF, box_x2, box_y1, box_y2,
    prev_bx1, prev_bx2, prev_by1, prev_by2;
  while(1) {
    if (touch_available()) {
      touch_read(&x, &y);

      if (x != 0xFFFF && y != 0xFFFF) {
        prev_bx1 = box_x1;
        prev_bx2 = box_x2;
        prev_by1 = box_y1;
        prev_by2 = box_y2;

        box_x1 = (x >= 1)? (x-1) : 0;
        box_x2 = (x <= 238)? (x+1) : 239;

        box_y1 = (y >= 1)? (y-1) : 0;
        box_y2 = (y <= 318)? (y+1) : 319;

        TFT_draw_box(box_x1, box_y1, box_x2, box_y2, 61);

        if (x > 2 && x < 92 && y > 2 && y < 24) {
          TFT_fill(0xFFFF);

          TFT_box_outline(2,2,92,24,2,0);

          TFT_char(FONT_16x16, 'C', 5, 5, 0, 0xFFFF, 16, 16);
          TFT_char(FONT_16x16, 'l', 22, 5, 0, 0xFFFF, 16, 16);
          TFT_char(FONT_16x16, 'e', 39, 5, 0, 0xFFFF, 16, 16);
          TFT_char(FONT_16x16, 'a', 56, 5, 0, 0xFFFF, 16, 16);
          TFT_char(FONT_16x16, 'r', 73, 5, 0, 0xFFFF, 16, 16);
        }
      }
    }
  }

  return 0;
}
