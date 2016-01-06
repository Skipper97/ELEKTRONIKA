/*
 * star.h
 *
 *  Created on: Mar 23, 2013
 *      Author: Sahuc Guillaume
 */

#ifndef STAR_H_
#define STAR_H_

#define NUMSTARS 100 // nombre d'étoiles

typedef struct star{
	UINT8 x; // abscisse de l'étoile
	UINT16 y; // son ordonnée 
	INT8 speed; // sa vitesse 
	UINT8 last_x; 
	UINT16 last_y;
} star;

static star tabstars[NUMSTARS]; // tableau d'étoiles

void initStars(void);
void viewStar(void);

#endif /* STAR_H_ */
