/*
 * interrupt.c
 *
 *      Author: Guillaume Sahuc
 
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
#include "interrupt.h"
#include "board.h"
#include "derivative.h"
#include "ads7843.h"
#include <stdio.h>
#include <termio.h>
#include <hidef.h>
#include "spi.h"
#include "init.h"

/**********************************************************************************
 * INTERRUPTION 
 **********************************************************************************/

#pragma TRAP_PROC
__interrupt void intTpm1Ch0(void){
	 /* Write your interrupt code here ... */
	printf("intTpm1Ch0");
}

#pragma TRAP_PROC
__interrupt void intTpm1Ch2(void){
	 /* Write your interrupt code here ... */
	//printf("intTpm1Ch2");
	TPM1C2SC_CH2F = 0; 
	TPM1C2SC = 0x68; 
}
#pragma TRAP_PROC
__interrupt void isrVicg(void)
{
  /* Write your interrupt code here ... */
	//printf("isrVicg");
}
#pragma TRAP_PROC
__interrupt void intTpm1ovf(void)
{
  /* Write your interrupt code here ... */
	//printf("intTpm1ovf");
	  TPM1SC_TOF = 0;    // Stops Timer 
	  TPM1SC =  0x48;   // Restarts Timer
	
}
//touch panel on IRQ
#pragma TRAP_PROC
__interrupt void int_IRQ(void)
{
  /* Write your interrupt code here ... */
	//LED = ~LED; //debug
	SDCARD_CS = 1;
	SPI_Low_rate();
	TOUCH_CS = 0; // activation ADS7843
	TouchPanelRead();
	TOUCH_CS = 1;
	SPI_High_rate();
	IRQSC_IRQACK = 1;
}
/* end of isrVicg */
extern void _Startup(void);

//il faut commenter les vecteurs dans le fichier *.PRM
void (* const _vect[])() @0xFFCC = { /* Interrupt vector table */
         UNASSIGNED_ISR,               /* Int.no. 25 Vrti (at FFCC)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 24 Viic1 (at FFCE)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 23 Vadc1 (at FFD0)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 22 Vkeyboard1 (at FFD2)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 21 Vsci2tx (at FFD4)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 20 Vsci2rx (at FFD6)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 19 Vsci2err (at FFD8)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 18 Vsci1tx (at FFDA)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 17 Vsci1rx (at FFDC)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 16 Vsci1err (at FFDE)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 15 Vspi1 (at FFE0)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 14 Vtpm2ovf (at FFE2)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 13 Vtpm2ch1 (at FFE4)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 12 Vtpm2ch0 (at FFE6)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 11 Vtpm1ovf (at FFE8)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 10 Vtpm1ch5 (at FFEA)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  9 Vtpm1ch4 (at FFEC)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  8 Vtpm1ch3 (at FFEE)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  7 Vtpm1ch2 (at FFF0)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  6 Vtpm1ch1 (at FFF2)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  5 Vtpm1ch0 (at FFF4)              Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  4 Vicg (at FFF6)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  3 Vlvd (at FFF8)                  Unassigned */
         int_IRQ,   	               /* Int.no.  2 Virq (at FFFA)                  used for touchpanel */
         UNASSIGNED_ISR,               /* Int.no.  1 Vswi (at FFFC)                  Unassigned */
         _Startup                      /* Int.no.  0 Vreset (at FFFE)                Reset vector */
};
