/*
 * tools.c
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
#include "tools.h"
#include "derivative.h"


float Temperature(float Vtemp){
	float temp;
	float m;
	if (Vtemp > Vtemp25){
		m = COLD;
	temp = 25 - ((Vtemp - Vtemp25) / m );
	return temp;
	}
	else{ 
		m = HOT;
	temp = 25 - ((Vtemp - Vtemp25) / m );
	return temp;
	}
}

void Led_Flash(void){    
	 PTFD = ~PTFD;	 /* ~ = inverse */
	 DelayMs(250);
}

INT8 ADC(INT8 channel){
	INT8 value;
	ADC1SC1 = channel;
	while(!ADC1SC1_COCO);
	value = ADC1RL;
	return value;
}
