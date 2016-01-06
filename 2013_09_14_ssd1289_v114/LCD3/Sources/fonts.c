

#include "Fonts.h"
#include "font_mini_4x6.h"
#include "font_standard.h"

UINT8 UserFont = FONT_STANDARD;
const FONT standart_font = { 0, "user_font",  12,  6,  ufont_1 };
const FONT font_mini = {  1, "font_mini",  6,  4,  fontdata_mini_4x6 };

//tableau pointant sur les fonts disponible
const FONT *fonts[] = {
 &standart_font,
 &font_mini
};

const FONT *FontTemp;

