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
#include "mc9s08aw60.h"
#include "FslTypes.h"
//***********************************************************************
//** Function:      sci_tx_byte
//*********************************************************************** 
void sci_tx(INT8 data)
{
	INT8 dummy;
    SCI1C2_TE = 1;          	// enable Tx
    dummy = SCI1S1;          	// 1st half of TDRE clear procedure
    SCI1D = data;             // 2nd half of TDRE clear procedure
    while(!SCI1S1_TDRE);		// Wait until send buffer empty
    while(!SCI1S1_TC);       	// Wait until byte sent
    SCI1C2_TE = 0;
}

//***********************************************************************
//** Function:      sci_rx_byte
//***********************************************************************
char sci_rx()
{
INT8 rec_char;

    SCI1C2_RE = 1;           	// enable Rx
    while(!SCI1S1_RDRF);        // wait for character
    rec_char = SCI1D;        	// get received character
    SCI1C2_RE = 0;              // disable Rx
    return rec_char;			 			
}

//***********************************************************************
//** Function:      send_msg
//*********************************************************************** 
void sci_send_msg(char msg[]){
byte n=0;	   							// String pointer
  
    do{
        sci_tx(msg[n]);
  	    n++;
    }while(msg[n]);
}

//***********************************************************************
//** Function:      send_midi
//***********************************************************************

void print_midi(INT8 midi){
INT8 dummy;

    SCI2C2_TE = 1;          	// enable Tx
    dummy = SCI2S1;          	// 1st half of TDRE clear procedure
    SCI2D = midi;               // 2nd half of TDRE clear procedure
    while(!SCI2S1_TDRE);		// Wait until send buffer empty
    while(!SCI2S1_TC);       	// Wait until byte sent
    SCI2C2_TE = 0;
}
