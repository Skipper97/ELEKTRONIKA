/****************************************************************************
* File:         font.c
* Author:       jaruwit supa
* Compiler:     AVRGCC
* Description:  font library
* Notes:        Base on FontEditor written by H. Reddmann
*
******************************************************************************/
/* _____STANDARD INCLUDES____________________________________________________ */
#include <avr/io.h>
#include <avr/pgmspace.h>

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "graphic.h"
#include "font.h"

/* _____LOCAL DEFINE_________________________________________________________ */
#define FONT_HEADER_SIZE            7     // header size of fonts

/* _____LOCAL VARIABLES______________________________________________________ */
uint8_t 	*FontPointer; 		//Font	Pointer
uint8_t 	rot = 0;			//Rot 0=0°, 1=90°
uint16_t 	FgColor = BLACK;	//Text fg color, 5-6-5 RGB
uint16_t 	BkColor = WHITE;	//Text bk color, 5-6-5 RGB
uint8_t 	FontFixed = 0;		//Text type 0=Proportional , 1=Fixed	
uint8_t		NonTransparence = 0;// Transparent 0=No, 1=Yes

uint8_t		FontWidth;			// max width of font
uint8_t		FontHeight;			// max height of font
uint8_t 	FontXScale = 1;		//X size of font
uint8_t 	FontYScale = 1;		//Y size of font
uint8_t 	FontSpace = 1;		//space between char

unsigned int cursorX = 0;		// x position
unsigned int cursorY = 0;		// y position

/* _____PRIVATE FUNCTIONS____________________________________________________ */

/* _____PUBLIC FUNCTIONS_____________________________________________________ */
void LcdFont(uint8_t *pointer)
{
	FontPointer = pointer;
	FontWidth 	= pgm_read_byte_near(&FontPointer[2]);
	FontHeight	= pgm_read_byte_near(&FontPointer[3]);
}

// draw char
void PutChar(unsigned char c)
{
	uint16_t 	fontSize		=	pgm_read_word_near(&FontPointer[0]);
//	uint8_t 	fontHeigh		=	pgm_read_byte_near(&FontPointer[3]);
	uint8_t 	firstchar 		=	pgm_read_byte_near(&FontPointer[5]);
	uint8_t 	lastchar 		=	pgm_read_byte_near(&FontPointer[6]);
	uint8_t 	charwidth	 	= 	pgm_read_byte_near(&FontPointer[7+c-firstchar]);
	uint8_t 	byte 			= 	0;
	uint8_t 	bitoffset 		= 	0;
	uint8_t 	maske 			= 	0;
	uint16_t 	bcounter 		= 	0;
	uint16_t 	bitsbischar 	= 	0;
	uint16_t 	bytesbischar	= 	0;
	uint16_t 	xPos,yPos;
	uint16_t 	color = GetColor();	// backup color

	if (c == '\n')
	{
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		cursorX = 0;
		return;
	}

	// charactor out of range.
    if( (c < firstchar) || (c > lastchar) || (fontSize == 0)) 
        return;

	// charactor is not in list.
    if (charwidth == 0)
		return;

	// sara thai font. line remain at last position
	if(FontFixed)
		charwidth = FontWidth;
	else
	{
		if (((c >= 0xd4) && (c <= 0xda)) || 
		    ((c >= 0xe7) && (c <= 0xec)) ||
			(c == 0xd1))
		{
			cursorX = cursorX - charwidth * FontXScale;
		}
	}

	// fixed width for digit
    if ( (c >= '0') && (c <= '9'))
		charwidth = pgm_read_byte_near(&FontPointer[7+'0'-firstchar]);

	// line adjust
	if (cursorX + charwidth * FontXScale > GetMaxX())
	{
		cursorY = cursorY + (unsigned int)FontHeight * FontYScale; 
		cursorX = 0;
	}

	for(uint8_t Ccounter = 0; Ccounter < c-firstchar; Ccounter++)
		bitsbischar += (pgm_read_byte_near(&FontPointer[Ccounter+7]));


	bitsbischar *= FontHeight;
	bitsbischar += ((lastchar-firstchar)+7)*8;
	bytesbischar = bitsbischar/8;
	bitoffset = bitsbischar % 8;
	maske = bitoffset % 8;

	for(uint8_t xc = 0; xc < charwidth; xc++) // Eigentlcihe Ausgaberoutine
	{
		for(uint8_t yc = 0; yc < FontHeight; yc++)
		{
			if(maske > 7)
			{
				maske = 0;
				bcounter+=1;
			};
			byte = pgm_read_byte_near(&FontPointer[bytesbischar + bcounter]+1);

			xPos = (uint16_t)xc*FontXScale + cursorX;
#ifdef Horizontal
#ifdef Reverse
			yPos = (((uint16_t)FontHeight-yc)*FontYScale + cursorY);
#else
			yPos = (((uint16_t)yc)*FontYScale + cursorY);
#endif           
            
#else
#ifdef Reverse
			yPos = (((uint16_t)FontHeight-yc)*FontYScale + cursorY);
#else
//			yPos = GetMaxY() - (((uint16_t)yc)*ScaleY + cursorY);
//			yPos = (((uint16_t)FontHeight-yc)*ScaleY + cursorY);
			yPos = (((uint16_t)yc)*FontYScale + cursorY);
//			yPos = ((yc)*FontYScale + cursorY);

#endif
#endif

			for(uint8_t sx = 0; sx < FontXScale; sx++)
			{
				for(uint8_t sy = 0; sy < FontYScale; sy++)
				{
					if(bit_is_set(byte,maske))
					{
						SetColor(GetFgColor());
						if(rot)
							LCD_PutPixel(yPos +sy,xPos+sx);
						else
							LCD_PutPixel(xPos+sx,yPos+sy);
					}
					else
					{
						if(NonTransparence)
						{
							SetColor(GetBkColor());
							if(rot)
								LCD_PutPixel(yPos +sy,xPos+sx);
							else
								LCD_PutPixel(xPos+sx,yPos+sy);
						}
					}
				}
			}
			maske++;
		}
	}
	SetColor(color);

	// adjust cursor to next position
	cursorX += charwidth * FontXScale + FontSpace;

}

unsigned int CalcTextWidth(char *Text)
{
	unsigned int strSize = 0;
	unsigned char firstchar =	pgm_read_byte_near(&FontPointer[5]);
	unsigned char lastchar 	=	pgm_read_byte_near(&FontPointer[6]);
	unsigned char charwidth;
	unsigned char c;

	while(*Text)
	{
		c = *Text;

		if(FontFixed)
			strSize += FontWidth * FontXScale;
		else
		{
		    if( (c < firstchar) || (c > lastchar)) 
				charwidth = FontWidth;
			else
			{
				if (((c >= 0xd4) && (c <= 0xda)) || 
			    	((c >= 0xe7) && (c <= 0xec)) ||
					(c == 0xd1))
					charwidth = 0;
				else
					charwidth = pgm_read_byte_near(&FontPointer[7+c-firstchar]);
			}
			strSize += charwidth * FontXScale;
		}
		strSize += FontSpace;
		Text++;
	}
	return strSize ;
}

unsigned int CalcTextHeight(char *Text)
{
	return FontHeight * FontYScale;
}

// draw string
void Puts(char *Text)
{	
	char c;
	while((c = *Text++))
	{
		PutChar(c);
	}
}

void PutsP(char *Text)
{
	char c;
	while((c = pgm_read_byte(Text++)))
	{
		PutChar(c);
	}
}

void PutLong(uint32_t src, uint8_t digit, uint8_t decimal, uint8_t Parameter)
{
	char text[10+1];
	uint8_t i;

	text[digit] = 0;
	for(i = digit; i >0; i--)
	{
		text[i-1] =(src % 10) + 48;
		src = src/10;
	}
	if (Parameter & (STYLE_NO_ZERO | STYLE_NO_SPACE))
	{
		while(text[i] == '0')
		{
		
			if (Parameter & (STYLE_NO_ZERO))
				PutChar(' ');
			i++;
			if (i > digit - decimal -1 -1) // include lead 0.xx
				break;
		}
	}
	while(text[i])
	{
		if (i == digit - decimal) // include lead 0.xx
			PutChar('.');
		PutChar(text[i]);
		i++;
	}
}

void PutInt(uint16_t src, uint8_t digit, uint8_t decimal, uint8_t Parameter)
{
	unsigned long n = src;
	PutLong(n, digit, decimal, Parameter);
}

void PutByte(uint8_t src, uint8_t digit, uint8_t decimal, uint8_t Parameter)
{
	unsigned long n = src;
	PutLong(n, digit, decimal, Parameter);
}

void PutText(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, char *str, uint8_t style)
{
	uint16_t sizeofstring;

	sizeofstring = CalcTextWidth(str);
	top = top + (bottom - top - FontHeight)/2;
	
	switch (style & ALINE_MARK)
	{
		case ALINE_LEFT:
			break;

		case ALINE_CENTER:
				left = left + (right - left - sizeofstring) / 2;
			break;

		case ALINE_RIGHT:
			if (right > sizeofstring)
				left = right - sizeofstring;
			break;
	}

	SetCursorX(left);
	SetCursorY(top);
	Puts(str);
}

void PutTextP(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, const char *str, uint8_t style)
{
	char strP[100+1];
	strncpy_P(strP, str, strnlen_P(str,100));
	strP[100] = 0;	// terminate string
	PutText(left, top, right, bottom, strP, style);
}

void TextBox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, char *str, uint8_t style)
{
	unsigned int r;
	unsigned int colorSave = GetColor();
    

	if (style & BORDER_RECT)
	{
		r = (style & BORDER_BEVEL) >> 4;	// get bevel radius
		if (r)	// bevel
		{
			if (style & BORDER_FILL)
			{
				SetColor(BkColor);
				RectangleFill(x1+1, y1+1, x2-1, y2-1, r);
				SetColor(colorSave);
			}
			Rectangle(x1, y1, x2, y2, r);
		}
		else	// rect
		{
			if (style & BORDER_FILL)
			{
				SetColor(BkColor);
				RectangleFill(x1+1, y1+1, x2-1, y2-1, 0);
				SetColor(colorSave);
			}
			Rectangle(x1, y1, x2, y2, 0);
		}
	}
	else if (style & BORDER_FILL)
	{
		SetColor(BkColor);
		RectangleFill(x1, y1, x2, y2, 0);
		SetColor(colorSave);
	}

	if ((style & BORDER_RECT) || (style & BORDER_FILL))
	    PutText(x1+1, y1+1, x2-1, y2-1, str, style & ALINE_MARK);
    else
	    PutText(x1, y1, x2, y2, str, style & ALINE_MARK);
}

void TextBoxP(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, char *str, uint8_t style)
{
	char strP[100+1];
	strncpy_P(strP, str, strnlen_P(str,100));
	strP[100] = 0;	// terminate string
	TextBox(x1, y1, x2, y2, strP, style);
}
