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
#include "FslTypes.h"


//***********************************************************************
//** Function:      delay_10us
//** 
//** Description:  ~~10uS loop counter delay
//**  
//** Parameters:    Fbus = 20Mhz  <!> ONLY FOR FBUS = 20MHZ <!>
//***********************************************************************  
void delay_10us(){
  UINT8 n;
  for (n=17;n!=0;n--) {
    asm("nop");
  }
}


//***********************************************************************
//** Function:      delay_100us
//** 
//** Description:  ~~100uS loop counter delay
//**
//** Parameters:    Fbus = 20 Mhz
//***********************************************************************  
void delay_100us(){
  UINT8 n;
  for (n=181;n!=0;n--) {
    asm("nop");
  }
}


//----------------------------------------------------------------------------
// delay_1ms : Delay one milliseconds
// =========
//
// Parameters
//      none
//
// Notes
//      Uses delay_100us routine
// 
void delay_1ms(void){
	UINT8  i;
	  for (i = 0 ; i < 10; i++) {
		  delay_100us();                   //delay 1 millisecond
	    }
}

//----------------------------------------------------------------------------
// DelayMs 
//---------------------------------------------------------------------------

void DelayMs(UINT16 count) 
{
	UINT16  i;

    if (count == 0) {
        return;
    }
    for (i = count ; i!= 0 ; i--) {
        delay_1ms();                   //delay 1 millisecond
    }
    return;
}

//***********************************************************************
//** Function:      delay_1ms
//** 
//** Description:   250ms loop counter delay
 
void delay_250ms(){
  UINT8 n;
  for (n=250;n!=0;n--) {
    delay_1ms();
  }
}



