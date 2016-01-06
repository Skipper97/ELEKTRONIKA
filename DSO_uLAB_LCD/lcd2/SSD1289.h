#ifndef SSD1289_H_
#define SSD1289_H_

#include "FslTypes.h"
#include <string.h>

typedef struct _Point
{
	UINT16 x;
	UINT16 y;
}LCD_Position;



#define LCD_LENGTH 320  //longueur 
#define LCD_WIDTH 240   //largeur
#define MAX_LINE 26 // 320 / 12


void Lcd_Write_DATA_8(UINT8 data);
void Lcd_Write_DATA_2x8(UINT8 data_H,UINT8 data_L);
void Lcd_W_com_data_4x8( UINT8 address_H,UINT8 address_L, UINT8 data_H, UINT8 data_L);
void Lcd_address_set(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2);
void Lcd_PutChar(UINT16 x,UINT16 y,UINT8 value,UINT8 dcolor_H,UINT8 dcolor_L,UINT8 bgcolor_H,UINT8 bgcolor_L);
void Lcd_print(UINT16 Column,UINT16 Row,UINT8 *str,UINT8 dcolor_H,UINT8 dcolor_L,UINT8 bgcolor_H,UINT8 bgcolor_L);

void Init_LCD(void);
void Lcd_test(void);
void Lcd_test2(void);
void Lcd_test3(void);
void Lcd_test4(void);
void Lcd_test5(void);

void IntToStr(INT16 dd,UINT8 *str);
void LongToStr(INT32 dd,UINT8 *str);
void SDD1289_STANDBY_ON(void);
void SDD1289_STANDBY_OFF(void);
void Lcd_ScrollAreaSetup(UINT16 VL1, UINT16 VL2);


void LCD_setPixel(UINT16 x,UINT16 y, UINT8 color_H,UINT8 color_L);
void Lcd_Line(INT16 x0, INT16 y0,  INT16 x2,  INT16 y2, UINT8 color_H, UINT8 color_L);
void Lcd_Fill(UINT8 color_H,UINT8 color_L);
void Lcd_Fill_H(UINT8 color_H,UINT8 color_L);
void Lcd_Box( INT16 x, INT16 y, INT16 longueur, INT16 largeur, UINT8 color_H,UINT8 color_L);
void Lcd_Fill_Box(UINT16 x,UINT16 y,UINT16 longueur,UINT16 largeur, UINT8 color_H,UINT8 color_L);
void LCD_Circle(INT16 Xpos, INT16 Ypos, INT16 Radius, UINT8 color_H,UINT8 color_L);
void LCD_Fill_Circle(INT16 Xpos, INT16 Ypos, INT16 Radius, UINT8 color_H,UINT8 color_L);
void Lcd_Position_Set(UINT16 x1,UINT16 y1);


#endif /* SSD1289_H_ */
