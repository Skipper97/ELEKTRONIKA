/**************************************************************************************************
* File name		: graphic.c
* Programmer 	: jaruwit supa
* Web presence  : www.thaibestlink.com
* Note			: lcd graphic support
* Language		: avrGCC
* Hardware		: atmega16
* Date			: 01/05/2009
************************************************************************************************/

/* _____STANDARD INCLUDES____________________________________________________ */
#include <avr/io.h>
#include <stdlib.h>

/* _____PROJECT INCLUDES_____________________________________________________ */
#include "graphic.h"

/* _____LOCAL DEFINE_________________________________________________________ */

/* _____LOCAL VARIABLES______________________________________________________ */

/* _____LOCAL FUNCTIONS______________________________________________________ */

/* _____PUBLIC FUNCTIONS_____________________________________________________ */

/*********************************************************************
* Function     : void Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
* Description  : Draw a line on a graphic LCD using Bresenham's
* PreCondition : SetColor()
* Input        : x1,y1 - starting coordinates
*              : x2,y2 - ending coordinates
* Output       : none
* Note         : none
********************************************************************/
void Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	signed int  x, y, addx, addy, dx, dy;
	signed long P;
	int i;
/*
	if (x1>x2)
	{
		dx = x1; x1 = x2; x2 = dx;
		dy = y1; y1 = y2; y2 = dy;
	}

	// vertical line
	if ((x1 == x2) || (y1 == y2))
	{
		FillRectangle(x1, y1, x2, y2);
		return;
	}
*/
	dx = abs((signed int)(x2 - x1));
	dy = abs((signed int)(y2 - y1));
	x = x1;
	y = y1;

	addx = addy = 1;
	if(x1 > x2)
		addx = -1;
	if(y1 > y2)
		addy = -1;

	if (dx >= dy)
	{
		P = 2L*dy - dx;
		for (i=0; i<=dx; ++i)
		{
	  		DrawPixel(x, y);
			if(P < 0)
	  		{
	    		P += 2*dy;
	    		x += addx;
	  		}
			else
			{
	    		P += 2*dy - 2*dx;
	    		x += addx;
	    		y += addy;
	  		}
		}
	}
	else
	{
		P = 2L*dx - dy;
		for(i=0; i<=dy; ++i)
		{
	  		DrawPixel(x, y);
	  		if(P < 0)
	  		{
	    		P += 2*dx;
	    		y += addy;
	  		}
	  		else
	  		{
	    		P += 2*dx - 2*dy;
	    		x += addx;
	    		y += addy;
	  		}
		}
	}
}

/*********************************************************************
* Function    : void Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int rad)
* Description : Draws a beveled figure on the screen. 
* PreCondition: None
* Input       : x1, y1 - coordinate position of the upper left center
*		      : x2, y2 - coordinate position of the lower right center
*             : rad - defines the redius of the circle,
* Output      : None
* Note        : None
********************************************************************/
void Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius)
{
	signed int a, b, P;
	signed int bx, ay;

	// adjust size
	x1 = x1 + radius;
	x2 = x2 - radius;
	y1 = y1 + radius;
	y2 = y2 - radius;

	DrawRect(x1       , y1-radius, x2       , y1-radius);	// top
	DrawRect(x1       , y2+radius, x2       , y2+radius);	// bottom
	DrawRect(x1-radius, y1       , x1-radius, y2       );	// left
	DrawRect(x2+radius, y1       , x2+radius, y2       );	// right

	if (radius == 0)
		return;

	// draw broder
	a = 0;       // increment by 1
	b = radius;  // decrement by 1 using P
	P = 1 - radius;
	bx = b;
	ay = a;

	do
	{
		if (a && (a != b))
		{
			DrawPixel(x1-b, y1-a);
			DrawPixel(x1-b, y2+a);
			DrawPixel(x2+b, y1-a);
			DrawPixel(x2+b, y2+a);
		}
		DrawPixel(x1-a, y1-b);
		DrawPixel(x2+a, y1-b);
		DrawPixel(x1-a, y2+b);
		DrawPixel(x2+a, y2+b);

		if(P < 0)
			P+= 3 + 2*a++;
		else
			P+= 5 + 2*(a++ - b--);
	} while(a <= b);
}

void RectangleFill(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int radius)
{
	signed int a, b, P;
	signed int bx, ay;

	if (radius == 0)
	{
	    DrawRect(x1, y1, x2, y2);
		return;
	}
	// adjust size
	x1 = x1 + radius;
	x2 = x2 - radius;
	y1 = y1 + radius;
	y2 = y2 - radius;

	a = 0;       // increment by 1
	b = radius;  // decrement by 1 using P
	P = 1 - radius;
	bx = b;
	ay = a;
	
	DrawRect(x1, y1-radius, x2, y2+radius);
	do
	{
		if (bx != b)
		{
			DrawRect(x1-bx, y1-ay, x1-bx, y2+ay); // left in
			DrawRect(x2+bx, y1-ay, x2+bx, y2+ay); // right in
			bx = b;
		}
  		ay = a;
		if (a != b)
		{ 
			DrawRect(x1-a, y1-b, x1, y2+b); // left out
			DrawRect(x2  , y1-b, x2+a, y2+b); // rigth out
  		}
		if(P < 0)
			P+= 3 + 2*a++;
		else
			P+= 5 + 2*(a++ - b--);
	} while(a <= b);

	if (bx != b)
	{
		DrawRect(x1-bx, y1-ay, x1-bx, y2+ay); // left in
		DrawRect(x2+bx, y1-ay, x2+bx, y2+ay); // right in
	}
}
/*********************************************************************
* Function    : void Circle(unsigned int x, unsigned int y, unsigned int radius, unsigned char fill)
* Description : Draw a circle on the screen. 
* PreCondition: None
* Input       : x,y - the center of the circle
*             : rad - defines the redius of the circle,
*             : fill - fill yes or no
* Output      : None
* Note        : None
********************************************************************/
void CircleFill(unsigned int x, unsigned int y, unsigned int radius, unsigned char fill)
{
   signed int a, b, P;
   a = 0;
   b = radius;
   P = 1 - radius;

   do
   {
      if(fill)
      {
         DrawRect(x-a, y+b, x+a, y+b);
         DrawRect(x-a, y-b, x+a, y-b);
         DrawRect(x-b, y+a, x+b, y+a);
         DrawRect(x-b, y-a, x+b, y-a);
      }
      else
      {
         DrawPixel(a+x, b+y);
         DrawPixel(b+x, a+y);
         DrawPixel(x-a, b+y);
         DrawPixel(x-b, a+y);
         DrawPixel(b+x, y-a);
         DrawPixel(a+x, y-b);
         DrawPixel(x-a, y-b);
         DrawPixel(x-b, y-a);
      }

      if(P < 0)
         P+= 3 + 2*a++;
      else
         P+= 5 + 2*(a++ - b--);
    } while(a <= b);
}

