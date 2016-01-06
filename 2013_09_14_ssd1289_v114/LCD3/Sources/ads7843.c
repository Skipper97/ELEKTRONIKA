/*
 * ads7843.c
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
 *      
 */
#pragma MESSAGE DISABLE C1420
#pragma MESSAGE DISABLE C1801
#include "ads7843.h"
#include "derivative.h"
#include "SSD1289.h"
#include "board.h"
#include "tools.h"
#include "color16bits.h"



// calibration du touch panel 
void CalibrateADS7843(INT16 *a,INT16 *b){

	INT16 x = *a;
	INT16 y = *b;
	if (x > 3759)//3750
	 x = 3759;
	 else if (x < 400)
	   x = 400;

	 if (y > 3850)
	   y = 3850;
	 else if (y < 450)
	   y = 450;

	  x = (x - 399) / 14;//13.3
	  y = 320 - ((y - 449) / 10) ;
	  if (x > 240)
		  x = 240;
	 *a = x ;
	 *b = y ;
}

void CalibrateXPT2046(INT16 *a,INT16 *b){

	INT16 x = *a;
	INT16 y = *b;
	if (x > 3900)
	 x = 3900;
	 else if (x < 200)
	   x = 200;

	 if (y > 3850)
	   y = 3850;
	 else if (y < 150)
	   y = 150;

	  x = (x - 200) / 16.2; //16.25
	  y = 320 - ((y - 150) / 11.5) ; //11.5625
	  if (x > 240)
		  x = 240;
	 *a = x ;
	 *b = y ;
}

INT16 READ_Y_TouchPanel(void)
{
	UINT8 MSB_Y,LSB_Y; // 8 bits data from ADS7843
	INT16 TP_Y;
	TP_Y = SPI1D; // lecture factice
	/*------------------------------------
	 * RECEIVE Y TOUCH PANEL ( portrait mode = vertical otherwise it's X in landscape mode = horizontal )
	------------------------------------*/
	while(!SPI1S_SPTEF){} //data send ready ? 
	SPI1D = 0x90;//Y REQUEST 
	while(!SPI1S_SPRF){} //data read ready ? 
	TP_Y = SPI1D; // lecture factice
	while(!SPI1S_SPTEF){} //data send ready ? 
	SPI1D = 0x00; // ecriture factice
	while(!SPI1S_SPRF){} //data read ready ?
	MSB_Y = SPI1D & 0x7F; // lecture Y MSB  
	while(!SPI1S_SPTEF){} //data send ready ? 
	SPI1D = 0xD0;// X REQUEST  
	while(!SPI1S_SPRF){}
	LSB_Y = SPI1D; // lecture Y LSB 
	TP_Y = ((MSB_Y <<8) | (LSB_Y))>>3; // 12 bits data from ADS7843
	return TP_Y;
}

INT16 READ_X_TouchPanel(void)
{
	INT16 TP_X;
	UINT8 MSB_X,LSB_X; // 8 bits data from ADS7843
	/*------------------------------------
	 * RECEIVE X TOUCH PANEL ( portrait mode = vertical otherwise it's Y in landscape mode = horizontal  )
	------------------------------------*/
	while(!SPI1S_SPTEF){} //data send ready ? 
	SPI1D = 0x00;// ecriture factice
	while(!SPI1S_SPRF){} //data read ready ?   
	MSB_X = SPI1D & 0x7F; // lecture factice 
	while(!SPI1S_SPTEF){} //data send ready ? 
	SPI1D = 0x00; // ecriture factice
	while(!SPI1S_SPRF){} //data read ready ?
	LSB_X = SPI1D; // lecture X MSB
	TP_X = ((MSB_X<<8) | (LSB_X))>>3; // 12 bits data from ADS7843
	return TP_X;
}

void Debug_TouchPanelRead(void){
	UINT8 ss[6]; // pour debug
	INT16 TP_X,TP_Y;	//touch panel X & Y  12 bits from MSB + LSB  
//	while(TOUCH_BUSY){}  //pas nécessaire
	TP_Y =	READ_Y_TouchPanel();			
	TP_X =	READ_X_TouchPanel();	
	//debug RAW
	
	IntToStr(TP_X,ss);
	Lcd_print(10,270,"X:",COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	Lcd_print(25,270,ss,COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	//sprintf(ss,"%d",TP_Y);
	IntToStr(TP_Y,ss);
	Lcd_print(80,270,"Y:",COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	Lcd_print(95,270,ss,COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
			
    CalibrateXPT2046(&TP_X,&TP_Y);
			
	//debug Calibration
    IntToStr(TP_X,ss);
	Lcd_print(10,305,"X:",COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	Lcd_print(25,305,ss,COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	IntToStr(TP_Y,ss);
	Lcd_print(80,305,"Y:",COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	Lcd_print(95,305,ss,COLOR_2x8BITS_RED,COLOR_2x8BITS_WHITE);
	LCD_Fill_Circle(TP_X,TP_Y,5,COLOR_2x8BITS_WHITE);

}

INT16 LastX,LastY;

void TouchPanelRead(void){
	INT16 TP_X,TP_Y;	//touch panel X & Y  12 bits from MSB + LSB  
	INT16 Xarray[6];
	INT16 Yarray[6];
	UINT8 x,y = 0;
	while(y!=15)
	{
		y++; // ignore first touchpanel read
	
		for(x=0;x!=5;x++)
			{
				Yarray[x] =	READ_Y_TouchPanel();			
				Xarray[x] =	READ_X_TouchPanel();
			}
	}
    qsort(Xarray,sizeof(Xarray)/ sizeof *Xarray,sizeof(INT16), compare);
    qsort(Yarray,sizeof(Yarray)/ sizeof *Yarray,sizeof(INT16), compare);
    // median 
    TP_Y = (Yarray[2]+Yarray[3])*0.5; 
    TP_X = (Xarray[2]+Xarray[3])*0.5; 
    CalibrateXPT2046(&TP_X,&TP_Y);
	LCD_Fill_Circle(TP_X,TP_Y,5,COLOR_2x8BITS_WHITE);
}
