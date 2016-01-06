/*
 * ads7843.h
 *
 *      Author: Guillaume Sahuc
 */

#ifndef ADS7843_H_
#define ADS7843_H_


#include "FslTypes.h"


enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

/* Prototypes */
void Debug_TouchPanelRead(void);
void TouchPanelRead(void);
INT16 READ_X_TouchPanel(void);
INT16 READ_Y_TouchPanel(void);
void CalibrateXPT2046(INT16 *a,INT16 *b);
void CalibrateADS7843(INT16 *a,INT16 *b);

#endif /* ADS7843_H_ */
