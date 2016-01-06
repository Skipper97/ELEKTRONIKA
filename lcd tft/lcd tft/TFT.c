/* Implementation of SSD1289 TFT LCD library from TFT.h */

#include "TFT.h"
#include "pins.h"

void TFT_write_command(uint16_t command) {
	LCD_STER &= ~LCD_RS;

	LCD_DATA_H = command >> 8;
	LCD_DATA_L = command;

	LCD_STER &= ~(LCD_WR);
	LCD_STER |= (LCD_WR);
}

void TFT_write_data(uint16_t data) {
	LCD_STER |= LCD_RS;

	LCD_DATA_H = data >> 8;
	LCD_DATA_L = data;

	LCD_STER &= ~(LCD_WR);
	LCD_STER |= (LCD_WR);
}

void TFT_write_command_data(uint16_t command, uint16_t data) {
  TFT_write_command(command);
  TFT_write_data(data);
}



void LCD_Send_SSD1298(uint16_t command, uint16_t data) {
  TFT_write_command(command);
  TFT_write_data(data);
}


/*void TFT_write_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  TFT_write_command_data(0x0044, (x2 << 8) + x1);
  TFT_write_command_data(0x0045, y1);
  TFT_write_command_data(0x0046, y2);
  TFT_write_command_data(0x004e, x1);
  TFT_write_command_data(0x004f, y1);
  TFT_write_command(0x0022);
}*/

void TFT_write_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  TFT_write_command_data(0x0044, (x2 << 8) + x1);
  TFT_write_command_data(0x0045, y1);
  TFT_write_command_data(0x0046, y2);
  TFT_write_command_data(0x004e, x1);
  TFT_write_command_data(0x004f, y1);
  TFT_write_command(0x0022);
}

void TFT_fill(uint16_t color) {
  uint32_t i;
  LCD_STER &= ~(LCD_CS);
  TFT_write_address(0,0,239,319);
  TFT_write_data(color);

  for(i = 0; i <= 0x9600; i++)
  {
		LCD_STER &= ~(LCD_WR);
		LCD_STER |= (LCD_WR);
		LCD_STER &= ~(LCD_WR);
		LCD_STER |= (LCD_WR);
  }

  LCD_STER |= (LCD_CS);
}

void TFT_draw_box(uint16_t x1, uint16_t y1, uint16_t x2,
                  uint16_t y2, uint16_t color) {
  uint16_t dx = x2 - x1 + 2, j;
  LCD_STER &= ~(LCD_CS);
  TFT_write_address(x1, y1, x2, y2);
  TFT_write_data(color);

  y2 = (y2 - y1) + 2;
  while (--y2) {
    j = dx;
    while (--j) {
		LCD_STER &= ~(LCD_WR);
		LCD_STER |= (LCD_WR);
    }
  }

  LCD_STER |= (LCD_CS);
}

void TFT_box_outline(uint16_t x1, uint16_t y1, uint16_t x2,
                     uint16_t y2, uint16_t width, uint16_t color) {
  width-=1;
  TFT_draw_box(x1, y1, x2, y1 + width, color);

  TFT_draw_box(x1, y1+width, x1+width, y2-width, color);
  TFT_draw_box(x2-width, y1+width, x2, y2-width, color);

  TFT_draw_box(x1, y2 - width, x2, y2, color);
}

void TFT_dot(uint16_t x, uint16_t y, uint16_t color) {
	LCD_STER &= ~(LCD_CS);
  TFT_write_address(x, y, x, y);
  TFT_write_data(color);
	LCD_STER |= (LCD_CS);
}

void TFT_init(void) {

	LCD_DATA_L_DIR = 0xFF;
	LCD_DATA_H_DIR = 0xFF;
	LCD_DATA_L = 0xFF;
	LCD_DATA_H = 0xFF;

	LCD_STER_DIR |= (LCD_CS)|(LCD_RD)|(LCD_WR)|(LCD_RS)|(LCD_RESET);
	LCD_STER |= (LCD_CS)|(LCD_RD)|(LCD_WR)|(LCD_RS)|(LCD_RESET);
	_delay_ms(100);

	LCD_STER &= ~(LCD_CS);
	LCD_STER &= ~(LCD_RESET);
	_delay_ms(10);
	LCD_STER |= LCD_RESET;
	_delay_ms(10);
	 LCD_Send_SSD1298( 0x0000, 0x0001 );    _delay_ms( 5 );
		    LCD_Send_SSD1298( 0x0003, 0xA8A4 );    _delay_ms(5);
		    LCD_Send_SSD1298( 0x000C, 0x0000 );    _delay_ms(5);
		    LCD_Send_SSD1298( 0x000D, 0x080C );    _delay_ms(5);
		    LCD_Send_SSD1298(0x000E,0x2B00);    _delay_ms(5);
		    LCD_Send_SSD1298(0x001E,0x00B0);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0001,0x2B3F);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0002,0x0600);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0010,0x0000);    _delay_ms(30);

		    LCD_Send_SSD1298(0x0011,0x6070);    _delay_ms(5); //0x6870    _delay_ms(5); //6870
		    LCD_Send_SSD1298(0x0007,0b0001100100110011);    _delay_ms(5); //!!!!!
		    LCD_Send_SSD1298(0x0005,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0006,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0016,0xEF1C);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0017,0x0003);    _delay_ms(5);
		    LCD_Send_SSD1298(0x000B,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x000F,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0041,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0042,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0048,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0049,0x013F);    _delay_ms(5);
		    LCD_Send_SSD1298(0x004B,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0044,0xEF00);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0045,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0046,0x013F);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0030,0x0707);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0031,0x0204);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0032,0x0204);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0033,0x0502);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0034,0x0507);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0035,0x0204);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0036,0x0204);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0037,0x0502);    _delay_ms(5);
		    LCD_Send_SSD1298(0x003A,0x0302);    _delay_ms(5);
		    LCD_Send_SSD1298(0x003B,0x0302);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0023,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0024,0x0000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x0025,0x8000);    _delay_ms(5);
		    LCD_Send_SSD1298(0x004f,0);
		    LCD_Send_SSD1298(0x004e,0);
		    TFT_write_command(0x0022);
	LCD_STER |= (LCD_CS);
}

void TFT_char(const uint8_t *font, uint8_t ch,
              uint16_t x, uint16_t y,
              uint16_t fg_color, uint16_t bg_color,
              uint16_t width, uint16_t height) {
  uint16_t j, k;
  const uint8_t *bmp_addr = font + ((ch - ' ')*height*(width/8));
  uint8_t bmp_byte = 0, pixel_mask = 0x80;
  uint8_t bit_set = 0;

  LCD_STER &= ~(LCD_CS);
  TFT_write_address(x, y, x + width - 1, y + height - 1);

  k = 0;
  while (height--)
  {
    for (j = width; j; --j)
    {
      if ((k % 8) == 0) {
        bmp_byte = pgm_read_byte(bmp_addr);
        pixel_mask = 0x80;
        ++bmp_addr;
      }

      bit_set = bmp_byte & pixel_mask;

      pixel_mask >>= 1;
      ++k;

      if (bit_set) {
        TFT_write_data(fg_color);
      } else {
        TFT_write_data(bg_color);
      }
    }
  }

  LCD_STER |= (LCD_CS);
}
