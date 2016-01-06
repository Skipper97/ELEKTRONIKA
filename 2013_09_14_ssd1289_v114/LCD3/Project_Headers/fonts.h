/*
 * fonts.h
 *
 *  Created on: Sep 14, 2013
 *      Author: Satellite23
 */

#ifndef FONTS_H_
#define FONTS_H_

#include "FslTypes.h"

#define FONT_STANDARD 0
#define FONT_MINI 1


typedef struct font {
	const UINT8 index;
	const UINT8 *Name;
	UINT8 height, width;
    const void *data;
}FONT;


extern UINT8 UserFont;
extern const FONT standart_font; 
extern const FONT font_mini;
extern const FONT *fonts[];
extern const FONT *FontTemp;

#endif /* FONTS_H_ */
