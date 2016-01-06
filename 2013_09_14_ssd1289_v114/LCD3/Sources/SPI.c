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
#include "SPI.h"
#include "board.h"

/************************************************/
void SPI_Init(void)
{
  SPI_SS = 1;
  SPI1BR = 0x05;   		
  SPI1C2 = 0x00;     
  SPI1C1 = SPI1C1_SPE_MASK | SPI1C1_MSTR_MASK;
}

/************************************************/
void SPI_Send_byte(UINT8 u8Data)
{
	(void)SPI1S;
	SPI1D=u8Data;
	while(!SPI1S_SPTEF){};
}

/************************************************/
UINT8 SPI_Receive_byte(void)
{
	(void)SPI1D;
	SPI1D=0xFF;
	while(!SPI1S_SPRF){};	
	return(SPI1D);
}

/************************************************/
void SPI_High_rate(void) // for SDCARD 
{
  SPI1C1 = 0x00;
  SPI1BR = 0x10; //  0x10; 		
  SPI1C1 = SPI1C1_SPE_MASK | SPI1C1_MSTR_MASK;
}


void SPI_Low_rate(void) // for Touch Screen
{
  SPI1C1 = 0x00;
  SPI1BR = 0x40;  		
  SPI1C1 = SPI1C1_SPE_MASK | SPI1C1_MSTR_MASK;
}
