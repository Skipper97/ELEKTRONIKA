/*
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
#pragma MESSAGE DISABLE C1801 /*desactive les messages d'erreur */
#pragma MESSAGE DISABLE C2705 /*desactive les messages d'erreur */
#pragma MESSAGE DISABLE C1420 /*desactive les messages d'erreur */

#include "board.h" // definitions des IO de la carte 
#include "init.h" // initialisation des IO / timers / etc ...
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <stdio.h> /*  pour printf , sprintf ... */ 
#include <stdlib.h> /* pour malloc realloc qsort*/
#include <ctype.h> /* pour isalpha() ... */
#include <math.h> /* cos sin etc... */
#include <string.h> /* strlen  etc... */
#include "tempo.h"
#include "tools.h"
#include "ads7843.h"
#include "interrupt.h"
#include "FslTypes.h"
#include "SPI.h"
#include "SD.h"
#include "main.h"
//#include "star.h"
#include "fonts.h"
#include "console.h"
#include "text.h"
#include "Fat.h"
#include "FileList.h"


//FILE *fp;
t_bmp _Bmp;
Color_RGB _Color;
const UINT8* Touch1 = "PRESS SW1 TO CONTINUE...";
const UINT8* Touch2 = "PRESS SW2 TO CONTINUE...";
const UINT8* Touch3 = "PRESS SW3 TO CONTINUE...";
const UINT8* Touch4 = "PRESS SW4 TO CONTINUE...";


void main(void) {
	 Init_MC08(); // configuration de la puce
     FontTemp = fonts[UserFont]; // init userfont
	 Init_LCD();
     EnableInterrupts;//autorisation des interruptions.
 	 u8sd_status = SD_Init();  /* Configures SPI module and File System to handle a SD card */
     SDcheck();           /* Send messages of card detection and file status */
     FAT_LS2(); // listing des fichiers à la racine 
     ClearFileList(&FList); //free space
 	ConsoleGoToY(&console,300);
 	ConsolePrint(&console,Touch1);
 	while(SW1){ } // attente appuie sur bouton 1
  	 // SD_WriteFile("");// first call no writting //1er appel non pris en compte pour l'ecriture
  	 //SD_WriteFile("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 
     // SD_ReadFile("FILE.TXT",COLOR_2x8BITS_SNOW,COLOR_2x8BITS_BLACK);
 	/* SD_Read24BitsBmpFile(0,0,"IMG.BMP", &_Bmp);
 	 Lcd_Fill(COLOR_2x8BITS_BLACK);
     SD_Read16BitsBmpFile(0,0,"IMG2.BMP", &_Bmp);*/
    ConsoleClear(&console);
    TestFileList();
 	while(1){ 
	   	  __RESET_WATCHDOG();
	   	    while(!SW1)
	   	    {
	   	    	ConsolePrint(&console,"bouton1\n");
	   	    }
	   	    while(!SW2)
	   	    {
	   	    	ConsolePrint(&console,"bouton2");
	   	    }
	   	    while(!SW3)
	   	    {
	   	    	ConsolePrint(&console,"_____*bouton3*_____\n");
	   	    }
		   	while(!SW4)
		   	{
		   	    ConsoleClear(&console);
		   	}
      	}  /* please make sure that you never leave main */
}
