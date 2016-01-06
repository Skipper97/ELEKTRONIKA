/**************************************************************************************************
*	  			  BL-TFT320420 tester
* File name		: main.c
* Programmer 	: jaruwit supa
* Web presence  : www.circuitidea.com
* Note			: test lcd BL-TFT320420
* Language		: avrGCC
* Hardware		: atmega32
* Date			: 01/05/2009
***************************************************************************************************/

/* _____STANDARD INCLUDES____________________________________________________ */
#include <avr/io.h>  		// include I/O definitions (port names, pin names, etc)

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "SSD1289.h"
#include "graphic.h"
#include "font.h"

//#include "ft18x34.h"
#include "ft10x20.h"

//#include "color3.h"		//was3

//#include "pic_image.h"

/* _____LOCAL DEFINITIONS____________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */


/* _____PRIVATE FUNCTIONS____________________________________________________ */
int main(void)
{
//	uint16_t color[]={0xf800,0x001f,0xffe0,0x0000,0xffff,0x07ff,0xf81f,0x07e0};    

	uint16_t color[]={ WHITE, BLACK, RED, GREEN,BLUE,YELLOW,MAGENTA,CYAN, GRAY, SILVER, GOLD }; 

	LCD_BL_ON();

	LCD_Reset();

/*
	LCD_Clear(BLACK);

    for(uint8_t n=0;n<11;n++)    //n<8
    {    
    	SetColor(color[n]);
		RectangleFill(0, 25*n, GetMaxX(), 25*(n+1)-1, 0);	//was 40
   	}    	

	SetColor(WHITE);
	Rectangle(0+40, 0+40, GetMaxX()-40, GetMaxY()-40, 10);
	SetColor(BLACK);
	Rectangle(0+50, 0+50, GetMaxX()-50, GetMaxY()-50, 10);
	SetColor(RED);
	Circle(GetMaxX() / 2, GetMaxY() / 2, GetMaxX()/4 + 40);
	SetColor(GREEN);
	CircleFill(GetMaxX() / 2, GetMaxY() / 2, GetMaxX()/4 + 30, 1);

//	SetColor(WHITE);
//	Line(0, 0, GetMaxX(), GetMaxY());
//	Line(0, GetMaxY(), GetMaxX(), 0);

	LcdFont(ft18x34);
	SetFgColor(WHITE);
	PutText(0,10, GetMaxX(), 30, "BL-TFT240320PLUS", ALINE_CENTER);
	SetFgColor(RED);
	PutText(0,GetMaxY()-30, GetMaxX(), GetMaxY(), "www.circuitidea.com", ALINE_CENTER);

	LCD_DrawImage(56, 96,gIcon_color3);		//Was3  PIC_image);	//


	LcdFont(ft18x34);
	SetFgColor(BLACK);
	PutText(2,10, GetMaxX(), 30, "BL-TFT240320PLUS", ALINE_LEFT);

	LcdFont(ft10x20);
	SetFgColor(WHITE);
	PutText(20,100, GetMaxX(), 30, "Micro-Tech", ALINE_LEFT);
*/
	while(1);
	return 0;
}
