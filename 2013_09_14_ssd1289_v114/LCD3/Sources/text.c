/*
 * text.c
 *
 *      Author: Guillaume Sahuc
 *      v1 = Insert / Length / Clear / View.
 *      v2 = use console
 */
#include "FslTypes.h"
#include "libdefs.h" // it's a local lib 
#include <stdlib.h> /* pour malloc realloc qsort*/
#include "color16bits.h"
#include "sd.h"
#include "text.h"
#include "SSD1289.h"
#include "board.h"
#include "tempo.h"
#include "fonts.h"
#include "main.h"
#include "console.h"

UINT16 line;
//inspiration ====> chgi.developpez.com/sortlist/


const UINT8* text1  = "...............1.............";
const UINT8* text2  = "...............2.............";	
const UINT8* text3  = "...............3.............";
const UINT8* text4  = "...............4.............";
const UINT8* text5  = "...............5.............";
const UINT8* text6  = "...............6.............";
const UINT8* text7  = "...............7.............";
const UINT8* text8  = "...............8.............";
const UINT8* text9  = "...............9.............";
const UINT8* text10 = "...............10.............";

void Insert(ScrollText** List,const UINT8* Text)
{
	ScrollText* NewText = malloc(sizeof(ScrollText));
	if (!NewText) { SD_SysHalt(); }
	NewText->text = Text;
	NewText->next = *List;
	*List = NewText;
}

UINT16 Lenght(ScrollText* List)
{
	UINT16 n = 0;
	while(List)
	{
		n++;
		List = List->next;
	}
	return n;
}

void Clear(ScrollText** List)
{
	ScrollText* tmp;
	while(*List)
	{
		tmp = (*List)->next;
		free(*List);
		*List = tmp;
	}
}

void View(ScrollText* List)
{
	while(List)
	{
		ConsolePrint(&console,List->text);
		List = List->next;	
	}
	Clear(&List);
}


void TestScroll(void)
{
    UINT16 count;
	ScrollText *TextListBuffer = NULL; // Initialisation
	Insert(&TextListBuffer,text1);
	Insert(&TextListBuffer,text2);
	Insert(&TextListBuffer,text3);
	Insert(&TextListBuffer,text4);
	Insert(&TextListBuffer,text5);
	Insert(&TextListBuffer,text6);
	Insert(&TextListBuffer,text7);
	Insert(&TextListBuffer,text8);
	Insert(&TextListBuffer,text9);
	Insert(&TextListBuffer,text10);
	View(TextListBuffer);
	count = Lenght(TextListBuffer); // verification de la taille de la liste 
	ConsolePrintf(&console,"%d",count);
}


void Scroll_Up(void) /*scroll hardware simple de l'affichage*/
{
 if (line <= LCD_LENGTH)
 	{
		Lcd_ScrollAreaSetup(line,0x0000);
		line++;
		DelayMs(1);
 	}
 	else
 	{
		line = 1;
 	}
}
void Scroll_Down(void)
{
	if (line >= 1)
	{
		line--;
		Lcd_ScrollAreaSetup((line),0x0000);
		DelayMs(1);
	}
	else
	{
		line = LCD_LENGTH; 
	}
}

void Scroll_Line_Up(void)
{
//	const FONT *FontTemp = fonts[UserFont];
   if ((line*FontTemp->height) <= LCD_LENGTH)
   {
		Lcd_ScrollAreaSetup(line*FontTemp->height,0x0000);
		line++;
		DelayMs(80);
   }
 else
 {
 	line = 1;
 }
}


void Scroll_Line_Down(void)
{
	//const FONT *FontTemp = fonts[UserFont];
if ((line*FontTemp->height) >= FontTemp->height)
	{
		line--;
		Lcd_ScrollAreaSetup((line*FontTemp->height),0x0000);
		DelayMs(80);
	}
	else
	{
		line = LCD_LENGTH / FontTemp->height; 
	}
}
