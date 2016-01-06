#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "dcmotorpwm/dcmotorpwm.h"

int main(void) {

	//init
	dcmotorpwm_init();

	uint8_t motor = 0;
	for(;;) {
		if(motor == 0)
			dcmotorpwm_gobackward(0);
		else
			dcmotorpwm_goforward(0);
		motor++;
		motor%=2;

		_delay_ms(2000);
	}
}
