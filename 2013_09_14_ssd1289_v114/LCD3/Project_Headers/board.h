/*
 * board.h
 *
 *      Author: Guillaume Sahuc
 */

#ifndef BOARD_H_
#define BOARD_H_

#define SW1 PTCD_PTCD2
#define SW2 PTCD_PTCD6
#define SW3 PTDD_PTDD3
#define SW4 PTDD_PTDD2
#define LED PTFD_PTFD1
#define ENTREE 0x00 //00 = entrée / FF = sortie
#define SORTIE 0xFF
#define ON 1
#define OFF 0

/* lcd definition */
#define LCD_CS PTED_PTED3
#define LCD_RD PTED_PTED2
#define LCD_WR PTED_PTED1
#define LCD_RS PTED_PTED0
#define LCD_BACKLIGHT PTCD_PTCD0
#define LCD_DATA_L PTAD
#define LCD_DATA_H PTBD
#define LCD_DATA_L_DIR PTADD // for direction
#define LCD_DATA_H_DIR PTBDD // for direction

#define SDCARD_CS PTED_PTED4
#define TOUCH_CS PTGD_PTGD4
#define TOUCH_BUSY PTCD_PTCD1


#endif /* BOARD_H_ */
