/*
 * console.c
 *
 *      Author: Sahuc Guillaume
 *      v1 = first release / basic print, clear function, cursor
 *      v2 = add ConsolePrintf + ConsoleGotoX + ConsoleGoToY + ConsoleSwapColor
 */
#include "SSD1289.h"
#include "fonts.h"
#include "main.h"
#include "console.h"
#include <stdio.h>

#define TAB  (FontTemp->width*4)


CONSOLE consoleError = {  0,"Error",0,0,COLOR_2x8BITS_RED,COLOR_2x8BITS_CYAN,0};
CONSOLE console = {  1,"standard",0,0,COLOR_2x8BITS_SNOW,COLOR_2x8BITS_BLACK,1};



void ConsolePrint(CONSOLE* console,const UINT8* str)	  
{  
	UINT8 MaxCharByLine,MaxLine;
	/*-----------------*/
	MaxCharByLine = (UINT8)(LCD_WIDTH/(FontTemp->width));
	MaxLine = (UINT8)(LCD_LENGTH/(FontTemp->height));
	/*-----------------*/
	while(*str!='\0')
	{	
		if((console->x>=MaxCharByLine*FontTemp->width) || (*str == 0x0D) || (*str == 0x0A))//à chaque depassement de l'écran ou caractère dédié = retour à la ligne
		{
			console->y +=  FontTemp->height;
			console->x = 0;
		}
		while((*str == 0x0D) || (*str == 0x0A)){str++;} //si plusieur retour à la ligne on les ignores.
		if(*str=='\0'){break;}
		if(console->y>=MaxLine*FontTemp->height)
		{
			 ConsoleClear(console);
		}
		Lcd_PutChar(console->x,console->y,*str,console->dcolor_H,console->dcolor_L,console->bgcolor_H,console->bgcolor_L);
		console->x+= FontTemp->width;
		str++;
	}
}

void ConsolePrintf(CONSOLE* console,const UINT8* format,...)
{
	  static UINT8 strbuf[260+1]; //260+1 for support Long File Name //MAX_LFN_CHARACTERS+1
	  va_list args;
	  va_start(args,format);
	  vsprintf(strbuf,format,args);
	  ConsolePrint(console,strbuf);
}

void ConsoleClear(CONSOLE* console)
{
	Lcd_Fill(console->bgcolor_H,console->bgcolor_L);
	console->x =0;
	console->y=0;
}

void ConsoleGoTo(CONSOLE* console,UINT16 _x, UINT16 _y)
{
	console->x = _x;
	console->y = _y;
}

void ConsoleGoToX(CONSOLE* console,UINT16 _x)
{
	console->x = _x;
}

void ConsoleGoToY(CONSOLE* console,UINT16 _y)
{
	console->y = _y;
}

void ConsoleSwapColor(CONSOLE* console)
{
	UINT8 H_buffer,L_buffer;
	H_buffer = console->bgcolor_H;
	L_buffer = console->bgcolor_L;
	console->bgcolor_H = console->dcolor_H;
	console->bgcolor_L = console->dcolor_L;
	console->dcolor_H = H_buffer;
	console->dcolor_L = L_buffer;
}

void ConsoleCursor(CONSOLE* console)
{
	/*todo */
}
