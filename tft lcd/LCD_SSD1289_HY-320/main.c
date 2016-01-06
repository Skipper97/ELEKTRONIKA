/*
 * main.c
 *
 *  Created on: 23-01-2014
 *  Author: Marcin "Mesho" Popko
 *  Strona www: atmegan.blogspot.com
 *
 *  Program testowy dla wyswietlacza 3,2' HY-320 ze sterownikiem SSD1289
 *  Na bazie bibliotek ze strony:
 *  https://github.com/gpittarelli/avr-ssd1289/blob/master/TFT.c
 *
 *  Wersja robocza, wci¹¿ jest wiele do zrobienia...
 */



#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "pins.h"
#include "TFT.h"
#include "fonts.h"
#include "touch.h"
#include "color16bits.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

void TFT_pattern1(void) {
	uint16_t i;
	LCD_STER &= ~(LCD_CS);
	TFT_write_address(0, 0, 239, 319);

	for (i = 0; i <= 0x9600; i++) {
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

	for (i = 0; i <= 0x9600; i++) {
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


void TFT_puts(char * str, uint16_t wysokosc) {
	uint8_t szerokosc = 5;

	register uint8_t znak;
	while ((znak = *(str++))) {
		TFT_char(FONT_16x16, znak, szerokosc, wysokosc, 0, COLOR_16BITS_YELLOW,
				16, 16);
		szerokosc = szerokosc + 16;
	}

}

void TFT_putin(int val, uint16_t wysokosc) {
	char bufor[17];
	TFT_puts(itoa(val, bufor, 10), wysokosc);

}



//##########################################################
//Funkcje testowe (nie dzia³aj¹, lub dzia³aj¹ nieprawid³owo)
void TFT_string(char * str, uint16_t wysokosc, uint16_t szerokosc) {
	register uint8_t znak;
	while ((znak = *(str++))) {
		TFT_char(FONT_16x16, znak, szerokosc, wysokosc, 0, COLOR_16BITS_YELLOW,
				16, 16);
	}

}


void button(uint16_t x, uint16_t y, char *s) {
	register uint8_t znak;
	uint8_t liczby, znaki;
	while ((liczby = *(s++))) znaki++;
	znaki*=16;

	TFT_box_outline(x, y, x + znaki, y + 19, 2, 0);
	// TFT_box_outline(100,2,170,24,2,0);
	x = x+2;
	y = y+2;
	while ((znak = *(s++))) {
		TFT_char(FONT_16x16, znak, x, y, 0, COLOR_16BITS_YELLOW, 16, 16);
		x+= 16;
	}
	/*TFT_char(FONT_16x16, 'K', x + 2, y + 2, COLOR_16BITS_YELLOW, COLOR_16BITS_BLACK, 16, 16);

	TFT_char(FONT_16x16, 'l', x + 18, y + 2, 0, COLOR_16BITS_YELLOW, 16, 16);
	TFT_char(FONT_16x16, 'i', x + 34, y + 2, 0, COLOR_16BITS_YELLOW, 16, 16);
	TFT_char(FONT_16x16, 'k', x + 50, y + 2, 0, COLOR_16BITS_YELLOW, 16, 16);*/
}

//Funkcje testowe (nie dzia³aj¹, lub dzia³aj¹ nieprawid³owo)
//##########################################################


int main(void) {

	TFT_init(); //inicjalizacja wyswietlacza

	touch_init(); //inicjalizacja dotyku

	TFT_fill(0xFFFF); //wypelnienie calego LCD kolorem bia³ym

	TFT_puts("SSD1289", 300); //fukcja testowa napisu

	TFT_box_outline(2, 2, 92, 24, 2, 0); //funkcja rysuj¹ca ramkê

	TFT_box_outline(100, 2, 170, 24, 2, 0);
	TFT_char(FONT_16x16, 'K', 102, 5, 0, 0xFFFF, 16, 16); //podstawowa funkcja wyswietlajaca litery
	TFT_char(FONT_16x16, 'l', 118, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 'i', 134, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 'k', 150, 5, 0, 0xFFFF, 16, 16);

	TFT_char(FONT_16x16, 'C', 5, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 'z', 22, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 'y', 39, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 's', 56, 5, 0, 0xFFFF, 16, 16);
	TFT_char(FONT_16x16, 'c', 73, 5, 0, 0xFFFF, 16, 16);

	uint16_t x, y, box_x1 = 0xFFFF, box_x2, box_y1, box_y2, prev_bx1, prev_bx2,
			prev_by1, prev_by2;
	while (1) {
		if (touch_available()) {
			touch_read(&x, &y);
			if (x > 100)
				TFT_putin(x, 30);
			TFT_putin(y, 50);

			if (x != 0xFFFF && y != 0xFFFF) {

				//#####################################
				//uproszczona procedura rysowania dotykiem
				prev_bx1 = box_x1;
				prev_bx2 = box_x2;
				prev_by1 = box_y1;
				prev_by2 = box_y2;

				box_x1 = (x >= 1) ? (x - 1) : 0;
				box_x2 = (x <= 238) ? (x + 1) : 239;

				box_y1 = (y >= 1) ? (y - 1) : 0;
				box_y2 = (y <= 318) ? (y + 1) : 319;

				TFT_draw_box(box_x1, box_y1, box_x2, box_y2,
						COLOR_16BITS_BLACK);
				//#####################################

				if (x > 2 && x < 92 && y > 2 && y < 24) {
					TFT_fill(0xFFFF);

					TFT_putin(x, 30);
					TFT_putin(y, 50);

					TFT_box_outline(2, 2, 92, 24, 2, 0);

					TFT_char(FONT_16x16, 'C', 5, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'z', 22, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'y', 39, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 's', 56, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'c', 73, 5, 0, 0xFFFF, 16, 16);
					TFT_puts("SSD1289", 300);

					TFT_box_outline(100, 2, 200, 24, 2, 0);
					TFT_char(FONT_16x16, 'K', 102, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'l', 118, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'i', 134, 5, 0, 0xFFFF, 16, 16);
					TFT_char(FONT_16x16, 'k', 150, 5, 0, 0xFFFF, 16, 16);
				}
				if (x > 100 && x < 200 && y > 2 && y < 24) {
					TFT_puts("POSZLO!", 180); //jakas akcja po przycisnieciu pola z przyciskiem "KLIK"
				}

			}
		}
	}

	return 0;
}
