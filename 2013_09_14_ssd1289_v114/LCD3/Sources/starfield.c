/*
 * starfield.c
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "color16bits.h"
#include "FslTypes.h"
#include "star.h"
#include "SSD1289.h"

void initStars(void)
{
	int i;
	for (i=0; i<NUMSTARS; i++)
	{
		tabstars[i].x = rand() % 240;
		tabstars[i].y = rand() % 320;
		tabstars[i].speed = (rand() % 4)+1;
		tabstars[i].last_x = 0;
		tabstars[i].last_y = 0;
	}
}

void viewStar(void)
{
	UINT8 i,j;// si > 255 à mettre en uint16
	j = 0;
	while(j<250)
	{
		for (i=0; i<NUMSTARS; i++)
		{
			// on déplace l'étoile
			tabstars[i].x += tabstars[i].speed; // on ajoute la vitesse à l'abscisse
			// on teste si l'étoile sort de la ligne. si c'est le cas, on la remet en début de ligne
			if (tabstars[i].x > 239)
				tabstars[i].x = 0;
			// effacement et affichage
			LCD_setPixel(tabstars[i].last_x,tabstars[i].last_y,COLOR_2x8BITS_BLACK);// efface l'ancienne position
			LCD_setPixel(tabstars[i].x,tabstars[i].y,COLOR_2x8BITS_WHITE);// affiche la nouvelle
			//sauvegarde de la position
			tabstars[i].last_x = tabstars[i].x;
			tabstars[i].last_y = tabstars[i].y;
		}
		j++;
	}
}
