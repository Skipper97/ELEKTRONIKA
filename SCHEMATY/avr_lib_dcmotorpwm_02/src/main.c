#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dcmotorpwm/dcmotorpwm.h"

int main(void) {

	//init
	dcmotorpwm_init();

	sei();

	for(;;) {
		dcmotorpwm_goslow('B', dcmotorpwm_getspeed(), 100, 90);
		_delay_ms(2000); _delay_ms(2000); _delay_ms(2000); _delay_ms(2000); _delay_ms(2000);

		dcmotorpwm_gostopslow(80);
		_delay_ms(2000); _delay_ms(2000); _delay_ms(2000); _delay_ms(2000); _delay_ms(2000);
	}
}
