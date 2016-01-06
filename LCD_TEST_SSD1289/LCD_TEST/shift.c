#include "shift.h"
#include <util/delay.h>
/*
void shift_out(uint16_t data) {
  uint16_t mask = 1 << 15, not_bit;

  while (mask) {
    not_bit = !(data & mask);
    if (not_bit) {
      PORTD &= ~(_BV(SHIFT_DATA));
    } else {
      PORTD |= _BV(SHIFT_DATA);
    }

    PORTD |= _BV(SHIFT_CLOCK);
    PORTD &= ~(_BV(SHIFT_CLOCK));

    if (not_bit != !(data & (mask >> 1))) {
      PORTD ^= _BV(SHIFT_DATA);
    }
    mask >>= 2;

    PORTD |= _BV(SHIFT_CLOCK);
    PORTD &= ~(_BV(SHIFT_CLOCK));
  }

  PORTD |= _BV(SHIFT_LATCH);
  PORTD &= ~(_BV(SHIFT_LATCH));
}
*/

