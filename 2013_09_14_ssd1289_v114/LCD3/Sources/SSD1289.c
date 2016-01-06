/*
 *SSD1289.c
 *
 *  Author: Guillaume Sahuc
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */
#pragma MESSAGE DISABLE C2705 /*desactive les messages d'erreur C2705 */
#include "board.h"
#include "color16bits.h"
#include "derivative.h"
#include "fonts.h"
#include "tempo.h"
#include "SSD1289.h"
#include <math.h>
#include <stdio.h> /*  pour printf , sprintf ... */ 
#include <stdlib.h> /* pour abs */
#include "main.h"

extern UINT8 buffer_16[6];
extern UINT8 buffer_32[11];


// échange de valeur entre 2 adresses
void swap(INT16 *a, INT16 *b)
{
	INT16 temp = *a;
	*a = *b;
	*b = temp;
}
//--------------------(--HIGHBYTE---,------LOWBYTE-)
void Lcd_Write_Com_2x8( UINT8 addr_H, UINT8  addr_L)	 
{	
	LCD_CS = 0;	
	LCD_RS = 0;
 	LCD_DATA_H = addr_H;	
	LCD_DATA_L = addr_L;		
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_RS = 1;
	LCD_CS = 1;	
}

void Lcd_Write_DATA_2x8(UINT8 data_H,UINT8 data_L)		
{
	LCD_CS = 0;	
    LCD_RS = 1;
	LCD_DATA_H = data_H;	
	LCD_DATA_L = data_L;					
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}

void Lcd_Write_DATA_16(UINT16 data)		
{
	/*UINT8 array[2] = {0};
	memcpy2(&array[0],&data,sizeof(UINT16));*/
	LCD_CS = 0;	
    LCD_RS = 1;
	LCD_DATA_H = data>>8;	
	LCD_DATA_L = data;					
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}

// envoi d'une donnée LSB sur le bus de données ( 8 bits LCD )
void Lcd_Write_DATA_8(UINT8 data)		
{
	LCD_CS = 0;	
    LCD_RS = 1;	
	LCD_DATA_L = data;					
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}

void Lcd_W_com_data_4x8( UINT8 address_H,UINT8 address_L, UINT8 data_H, UINT8 data_L)	
{
   Lcd_Write_Com_2x8(address_H,address_L); // addresse registre
   Lcd_Write_DATA_2x8(data_H,data_L); // Donnée à stocker dans le registre
}

// write command + data
void Lcd_W_com_data_8(UINT8 address_H,UINT8 address_L,UINT8 data)	
{
   Lcd_Write_Com_2x8(address_H,address_L); // addresse registre
   Lcd_Write_DATA_8(data); // Donnée à stocker dans le registre
}

// Lecture d'un registre uniquement le LSB (8bits D7 à D0) 
UINT8 Lcd_Read_data_8() 
{
	UINT8 data;
	LCD_DATA_L_DIR = ENTREE; // Port en entrée 
	LCD_CS = 0;	 
    LCD_RS = 1;
    LCD_RD = 0;
	LCD_RD = 1;
    data = LCD_DATA_L;  // lecture du registre
	LCD_CS = 1;	
	LCD_DATA_L_DIR = SORTIE;
	return data;
}

// Read 8 bits LSB register 
// return 8 bits data from index register
UINT8 Lcd_R_com_data_8( UINT8 address_H,UINT8 address_L)
{
    Lcd_Write_Com_2x8(address_H,address_L); // addresse registre
   return Lcd_Read_data_8();  // read register
}

// fonction définition de la zone écran +  position sur l'ecran ( mode vertical ) 
void Lcd_address_set(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2)
{
	UINT8 array[8] = {0};
	memcpy2(&array[0],&x1,sizeof(UINT16));
	memcpy2(&array[2],&y1,sizeof(UINT16));
	memcpy2(&array[4],&x2,sizeof(UINT16));
	memcpy2(&array[6],&y2,sizeof(UINT16));
    Lcd_W_com_data_4x8(0x00,0x44,array[5],array[1]); // end + start  horizontal
	Lcd_W_com_data_4x8(0x00,0x45,array[2] & 0x01,array[3]);	 //vertical start  
	Lcd_W_com_data_4x8(0x00,0x46,array[6] & 0x01,array[7]);	  //vertical end 
	Lcd_W_com_data_4x8(0x00,0x4e,array[0],array[1]);	 //set GDDRAM adress counter 
	Lcd_W_com_data_4x8(0x00,0x4f,array[2] & 0x01,array[3]);	  //set GDDRAM adress counter 
    Lcd_Write_Com_2x8(0x00,0x22);		// transform data into 16 bits bus before write to GRAM 
}	

// fonction de changement de position sur l'ecran
void Lcd_Position_Set(UINT16 x1,UINT16 y1)
{
	UINT8 array[4] = {0};
	memcpy2(&array[0],&x1,sizeof(UINT16));
	memcpy2(&array[2],&y1,sizeof(UINT16));
	Lcd_W_com_data_4x8(0x00,0x4e,array[0],array[1]);	 //set GDDRAM adress counter 
	Lcd_W_com_data_4x8(0x00,0x4f,array[2] & 0x01,array[3]);	  //set GDDRAM adress counter 
    Lcd_Write_Com_2x8(0x00,0x22);		// transform data into 16 bits bus before write to GRAM 
}

// conversion d'une donnée integer en string
// string[6]
void IntToStr(INT16 dd,UINT8* str)
{
	sprintf(str,"%d",dd);
}


// conversion d'une donnée long en string
// string[11]
void LongToStr(INT32 dd,UINT8* str)
{
	sprintf(str,"%ld",dd);
}

//dcolor = data color 
//bgcolor = background color
//fonction d'affichage d'un caractere avec l'utilisation d'un user font 
void Lcd_PutChar(UINT16 x,UINT16 y,UINT8 value,UINT8 dcolor_H,UINT8 dcolor_L,UINT8 bgcolor_H,UINT8 bgcolor_L)	
{  
	UINT8 i,j;
//	const FONT *FontTemp = fonts[UserFont];
	const UINT8 *temp = FontTemp->data;
    Lcd_address_set(x,y,x+(FontTemp->width-1),y+(FontTemp->height-1));     
	temp+=value*FontTemp->height;
	for(j=0;j<FontTemp->height;j++)
	{
		for(i=0;i<FontTemp->width;i++)
		{ 		     
		 	if((*temp&(1<<(7-i)))!=0)
			{
				Lcd_Write_DATA_2x8(dcolor_H,dcolor_L);
			} 
			else
			{
				Lcd_Write_DATA_2x8(bgcolor_H,bgcolor_L);
			}   
		}
		temp++;
	 }
}

// fonction d'affichage sur l'écran : position + donnée à afficher + couleur de la donnée + couleur de fond
void Lcd_print(UINT16 Column,UINT16 Row,UINT8* str,UINT8 dcolor_H,UINT8 dcolor_L,UINT8 bgcolor_H,UINT8 bgcolor_L)	  
{  
	UINT8 MaxLineChar;
//	const FONT *FontTemp = fonts[UserFont];
	/*-----------------*/
	MaxLineChar = (UINT8)(LCD_WIDTH/(FontTemp->width));
	/*-----------------*/
	while(*str!='\0')
	{	
		if((Column>=MaxLineChar*FontTemp->width) || (*str == 0x0D) || (*str == 0x0A))//à chaque depassement de l'écran ou caractère dédié = retour à la ligne
			{
				Row +=  FontTemp->height;
				Column = 0;
			}
		while((*str == 0x0D) || (*str == 0x0A)){str++;} //si plusieur retour à la ligne on les ignores.
		if(*str=='\0'){break;}
		Lcd_PutChar(Column,Row,*str,dcolor_H,dcolor_L,bgcolor_H,bgcolor_L);
		Column+= FontTemp->width;
		str++;
	}	
}


void Init_LCD(void)
{
	LCD_RS = 0;
	LCD_RS = 1;
	LCD_CS = 0;
  /*SSD1289*/
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x21);  //display control
	Lcd_W_com_data_4x8(0x00,0x00,0x00,0x01);  //oscillator start 
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x23);
	Lcd_W_com_data_4x8(0x00,0x03,0xAE,0xAC); 
	Lcd_W_com_data_4x8(0x00,0x0C,0x00,0x07); 
	Lcd_W_com_data_4x8(0x00,0x0D,0x00,0x0F); 
	Lcd_W_com_data_4x8(0x00,0x0E,0x29,0x00); 
	Lcd_W_com_data_4x8(0x00,0x1E,0x00,0xB3);
//	DelayMs(15);        
	Lcd_W_com_data_4x8(0x00,0x01,0x2b,0x3F); 
	Lcd_W_com_data_4x8(0x00,0x02,0x06,0x00); 
	Lcd_W_com_data_4x8(0x00,0x10,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0); // ID=11  AM=0
//	DelayMs(15);        
	Lcd_W_com_data_4x8(0x00,0x05,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x06,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x16,0xEF,0x1C); 
	Lcd_W_com_data_4x8(0x00,0x17,0x00,0x03); 
	Lcd_W_com_data_4x8(0x00,0x07,0x02,0x33);
	Lcd_W_com_data_4x8(0x00,0x0B,0x53,0x12); 
	Lcd_W_com_data_4x8(0x00,0x0F,0x00,0x00);
//	DelayMs(15);         
	Lcd_W_com_data_4x8(0x00,0x41,0x00,0X00); // scroll screen 1
	Lcd_W_com_data_4x8(0x00,0x42,0x00,0x00); // scroll screen 2
	Lcd_W_com_data_4x8(0x00,0x48,0x00,0x00); // first screen start
	Lcd_W_com_data_4x8(0x00,0x49,0x01,0x3F); // first screen end
	Lcd_W_com_data_4x8(0x00,0x44,0xEF,0x00); 
	Lcd_W_com_data_4x8(0x00,0x45,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x46,0x01,0x3F); 
	Lcd_W_com_data_4x8(0x00,0x4A,0x00,0x00); // second screen start
	Lcd_W_com_data_4x8(0x00,0x4B,0x00,0x00); // second screen end
//	DelayMs(15);       
	Lcd_W_com_data_4x8(0x00,0x30,0x07,0x07); 
	Lcd_W_com_data_4x8(0x00,0x31,0x07,0x04); 
	Lcd_W_com_data_4x8(0x00,0x32,0x02,0x04); 
	Lcd_W_com_data_4x8(0x00,0x33,0x02,0x01); 
	Lcd_W_com_data_4x8(0x00,0x34,0x02,0x03);
	Lcd_W_com_data_4x8(0x00,0x35,0x02,0x04);
	Lcd_W_com_data_4x8(0x00,0x36,0x02,0x04);
	Lcd_W_com_data_4x8(0x00,0x37,0x05,0x02);
	Lcd_W_com_data_4x8(0x00,0x3A,0x03,0x02);
	Lcd_W_com_data_4x8(0x00,0x3B,0x05,0x00);
	Lcd_W_com_data_4x8(0x00,0x23,0x00,0x00);
	Lcd_W_com_data_4x8(0x00,0x24,0x00,0x00);
	Lcd_W_com_data_4x8(0x00,0x25,0x80,0x00); //ajout
//	DelayMs(20); 
	Lcd_Write_Com_2x8(0x00,0x22);
	LCD_CS = 1;
}

// activation du mode scroll = rotation axe y de l'écran ( verticale ) 
void Lcd_Scroll_On(void)
{
	Lcd_W_com_data_4x8(0x00,0x07,0x02,0x33); 
}

void Lcd_Scroll_Off(void)
{
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x33); 
}

void Lcd_On(void)
{ 
	// Display ON Setting
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x21);  //display control
	Lcd_W_com_data_4x8(0x00,0x00,0x00,0x01);  //oscillator start 
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x23);
	Lcd_W_com_data_4x8(0x00,0x10,0x00,0x00);
	DelayMs(30); 
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x33);
	Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0); // ID=11  AM=0
	Lcd_W_com_data_4x8(0x00,0x02,0x06,0x00);
	Lcd_Write_Com_2x8(0x00,0x22);
}

void Lcd_Off(void)
{ 
	Lcd_W_com_data_4x8(0x00,0x07,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x00,0x00,0x00); 
	Lcd_W_com_data_4x8(0x00,0x10,0x00,0x01); 
}


void SDD1289_STANDBY_ON (void)
{
	// Display Off
	Lcd_W_com_data_4x8(0x00,0x10,0x00,0x01); 

}
	
void SSD1289_STANDBY_OFF (void)
{
	// Start Oscillation
	Lcd_W_com_data_4x8(0x00,0x10,0x00,0x00); 
}

/*! \configuration de la zone de scrolling.
 *
 *  @param VL1 1er écran  
 *  @param VL2 2eme écran 
 *
 */
void Lcd_ScrollAreaSetup(UINT16 VL1, UINT16 VL2)
{  
	UINT8 array[4] = {0};
	memcpy2(&array[0],&VL1,sizeof(UINT16));
	memcpy2(&array[2],&VL2,sizeof(UINT16));
	Lcd_W_com_data_4x8(0x00,0x41,array[0],array[1]);
	Lcd_W_com_data_4x8(0x00,0x42,array[2],array[3]);
}


// allumage d'un pixel + couleur
void LCD_setPixel(UINT16 x,UINT16 y, UINT8 color_H,UINT8 color_L)
{
	Lcd_address_set(x,y,x,y);//x_start,y_start,x_end,y_end
	Lcd_Write_DATA_2x8(color_H,color_L);
}


//affichage d'une boite pleine
void Lcd_Fill_Box(UINT16 x,UINT16 y,UINT16 longueur,UINT16 largeur, UINT8 color_H,UINT8 color_L)
{
	INT16 i,j;
	Lcd_address_set(x,y,longueur,largeur);//x_start,y_start,x_end,y_end
    for(i=0;i!=largeur+1;i++)
	 {
    	 Lcd_Write_DATA_2x8(color_H,color_L);
	  for (j=0;j!=longueur+1;j++)
	   	{
			LCD_CS = 0;
			LCD_WR = 0;
			LCD_WR = 1;
			LCD_CS = 1;  
	    }
	  Lcd_address_set(x,y+i,239,319);//x_start,y_start,x_end,y_end
	 
	 }
}

// Affichage d'une ligne
void Lcd_Line(INT16 x0,INT16 y0, INT16 x1, INT16 y1, UINT8 color_H,UINT8 color_L)
{  
	  INT16 dy = y1 - y0;
	  INT16 dx = x1 - x0;
	  float m = 0;
	  INT16 b = 0;
	  
	  if ((dy == 0) && (dx == 0))
	  {
		  LCD_setPixel(x0,y0,color_H,color_L);
		  return;
	  }
	  else if (dy == 0){
		  Lcd_Fill_Box(x0,y0,x1,1,color_H,color_L); // horizontal
				  return;
	  }
	  else if (dx == 0)
	  {
		  Lcd_Fill_Box(x0,y0,0,y1,color_H,color_L); // vertical
				  return; 
	  }
	  else// if (dx != 0)
	     {
	       m = ((float)(dy)) / (dx);
	       b = y0 - (int)(m * x0);
	      }
		
	Lcd_address_set(0,0,239,319);//x_start,y_start,x_end,y_end
		
	if ( abs(dx) >= abs(dy) )
	{
		 if (x0 > x1)
		  {
		    swap(&x0, &x1);
		    swap(&y0, &y1);
		  }
		 
		 while (x0 <= x1)
		 {
			 LCD_setPixel(x0, y0,color_H,color_L);
             x0++;
             if (x0 <= x1)
				 {
            	 y0 = (int)(m * x0) + b;
		    	 }
		  }
	}
	else
		{
			if (y0 > y1)
	        	{
					swap(&x0, &x1);
	             	swap(&y0, &y1);
	           	}
	      	while (y0 <= y1)
	        {
	      		 LCD_setPixel(x0, y0,color_H,color_L);
					y0++;
						if (y0 <= y1)
	                    {
	                            if (dx != 0)
	                            {
	                               	 x0 = (INT16)((float)((y0 - b) / m));
	                            }  
	                     }
	         }
	 }
}

// remplissage de l'ecran avec une couleur 
void Lcd_Fill(UINT8 color_H,UINT8 color_L) // <!> in vertical mode <!>
{
	INT16 i,j;
	Lcd_address_set(0,0,239,319);//x_start,y_start,x_end,y_end
	Lcd_Write_DATA_2x8(color_H,color_L);
    for(i=0;i!=320;i++)
	 {
	  for (j=0;j!=240;j++)
	   	{
		 LCD_CS = 0;
         LCD_WR = 0;
         LCD_WR = 1;
         LCD_CS = 1;
	    }
	  }
}

// remplissage écran en mode horizontale
void Lcd_Fill_H(UINT8 color_H,UINT8 color_L)
{
	INT16 i,j;
	Lcd_W_com_data_4x8(0x00,0x11,0x60,0x38); // registre qui permet de modifier l'orientation de l'écran "paysage" ( landscape )
	Lcd_address_set(0,0,239,319);//x_start,y_start,x_end,y_end
	 Lcd_Write_DATA_2x8(color_H,color_L);
	  for (j=0;j!=240;j++)
	 {
		  for(i=0;i!=320;i++)
	   	{
				 LCD_CS = 0;
		         LCD_WR = 0;
		         LCD_WR = 1;
		         LCD_CS = 1;     
	    }

	  }	
	  //retour vers l'orientation portrait
	  Lcd_W_com_data_4x8(0x00,0x11,0x60,0xB0);; // MY=0, MX=0, MV=0, ML=1, BGR=0=RGB if 1=BGR, TEON=0 
}

// affichage d'une boite non pleine ( position de départ + longueur + largeur + couleur ) 
void Lcd_Box(INT16 x, INT16 y, INT16 longueur,INT16 largeur, UINT8 color_H,UINT8 color_L)
{
	/*+----------------------------+
	  |							   |
	  |							   |
	  +----------------------------+*/
	Lcd_Line(x,y,longueur,y,color_H,color_L);
	Lcd_Line(x + longueur,y,x + longueur,largeur,color_H,color_L);
	Lcd_Line(x ,y + largeur,longueur ,y + largeur,color_H,color_L);
	Lcd_Line(x,y,x,largeur,color_H,color_L);
}


// affichage d'un cercle ( radius = rayon )
void LCD_Circle(INT16 Xpos,INT16 Ypos, INT16 Radius,UINT8 color_H,UINT8 color_L)
{ //algo d'Andres
  INT16  D;/* Decision Variable */
  INT16  CurX;/* Current X Value */
  INT16  CurY;/* Current Y Value */

  D = Radius - 1;
  CurX = 0;
  CurY = Radius;
  while (CurY >= CurX)  {
    LCD_setPixel( Xpos + CurX, Ypos + CurY,color_H,color_L);
    LCD_setPixel(Xpos + CurX, Ypos - CurY,color_H,color_L);
    LCD_setPixel(Xpos - CurX, Ypos + CurY,color_H,color_L);
    LCD_setPixel(Xpos - CurX, Ypos - CurY,color_H,color_L);
    LCD_setPixel(Xpos + CurY, Ypos + CurX,color_H,color_L);
    LCD_setPixel(Xpos + CurY, Ypos - CurX,color_H,color_L);
    LCD_setPixel(Xpos - CurY, Ypos + CurX,color_H,color_L);
    LCD_setPixel(Xpos - CurY, Ypos - CurX,color_H,color_L);
    if (D >= 2 * CurX)
    {
      D = D - 2 * CurX - 1;
      CurX++;
    }
    else if (D <= (2*(Radius-CurY)))
    {
      D = D + 2 * CurY - 1;
      CurY--;
    }
    else 
    {
    	 D += 2 * (CurY - CurX - 1);
    	 CurY--;
    	 CurX++;
    }
   
  }
}


// affichage d'un cercle plein
void LCD_Fill_Circle(INT16 Xpos, INT16 Ypos, INT16 Radius,UINT8 color_H,UINT8 color_L)
{
	while(Radius >= 0){
		LCD_Circle(Xpos,Ypos,Radius,color_H,color_L);
		Radius--;
	}
}

void Lcd_test(void)
{	
	UINT16 i=0;
	Lcd_Fill(COLOR_2x8BITS_RED); 
	Lcd_Fill_H(COLOR_2x8BITS_GREEN); 
	Lcd_Fill(COLOR_2x8BITS_BLUE); 
	Lcd_Fill_H(COLOR_2x8BITS_YELLOW);
	Lcd_Fill(COLOR_2x8BITS_TURQUOISE);
	Lcd_Fill_H(COLOR_2x8BITS_OLIVE);
	Lcd_Fill(COLOR_2x8BITS_LIGHTGREEN);
	Lcd_Fill_H(COLOR_2x8BITS_SILVER);
	Lcd_Fill(COLOR_2x8BITS_TOMATO);
	Lcd_Fill_H(COLOR_2x8BITS_BLACK);
	Lcd_Fill(COLOR_2x8BITS_DARKVIOLET);
 	Lcd_Fill(COLOR_2x8BITS_BLACK);
  	Lcd_print(82,5,"HELLO WORLD",COLOR_2x8BITS_WHITE,COLOR_2x8BITS_BLACK);
  	Lcd_Line(120,0,120,319,COLOR_2x8BITS_RED);
  	Lcd_Line(0,160,239,160,COLOR_2x8BITS_RED);
  	Lcd_Line(0,0,239,319,COLOR_2x8BITS_RED);
  	Lcd_Line(0,319,239,0,COLOR_2x8BITS_RED);
  	Lcd_Box(60,80,120,160,COLOR_2x8BITS_RED);
  	LCD_Circle(120,160,60,COLOR_2x8BITS_RED);
  	LCD_Circle(120,160,119,COLOR_2x8BITS_RED);
  	LCD_Fill_Circle(60,40,10,COLOR_2x8BITS_RED);
  	LCD_Fill_Circle(100,40,10,COLOR_2x8BITS_GREEN);
  	LCD_Fill_Circle(140,40,10,COLOR_2x8BITS_BLUE);
  	LCD_Fill_Circle(180,40,10,COLOR_2x8BITS_WHITE);
  	
  	for(i=0;i!=321;i++){
  	  Lcd_ScrollAreaSetup(i,0x0000);
  	 	DelayMs(25);
  	}		
}

void Lcd_test2(void)
{
	UINT16 i,j;
	UINT8 color_H,color_L;
	while(color_H!=0xFF){
	for(j=10;j<LCD_LENGTH;j=j+40)
	{
		for(i=10;i<LCD_WIDTH;i=i+40)
		{
			Lcd_Fill_Box(i,j,20,20,color_H,color_L);
		}
	}
	color_H +=1;
	color_L +=5;
	}
}


void Lcd_test3(void)
{
	UINT8 color_H=0,color_L=0;

		while(color_H!=0xFF)
			{
				Lcd_Fill(color_H,color_L);
				color_H +=1;
				color_L += 5 ;
			}
	
}

void Lcd_test4(void)
{
	//RED += 1;
	//GREEN += 2; 
	BLUE += 1;
Lcd_Fill(COLOR2,COLOR1);
IntToStr( _COLOR16BITS.Word,buffer_16);
Lcd_print(0,0,buffer_16,COLOR_2x8BITS_WHITE,COLOR_2x8BITS_BLACK);
}

void Lcd_test5(void)
{
	RED += 1;
  	GREEN += 2; 
  	BLUE += 1;
  	Lcd_print(40,0,"----HELLO WORLD----",COLOR_2x8BITS_WHITE,COLOR_2x8BITS_BLACK);
  	Lcd_print(40,20,"LOADING...",COLOR2,COLOR1,COLOR_2x8BITS_BLACK);
  	delay_1ms();
}
