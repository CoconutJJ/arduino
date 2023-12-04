#include <avr/io.h>

void set_pin_out(int i) {

  if (0 <= i && i <= 4) {
    DDRB |= (1 << i);
  }
  
  
}

