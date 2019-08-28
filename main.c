#include "avr/io.h"

#define F_CPU 4000000
#include "util/delay.h"


int main() {
  DDRA = (1 << PA4);
  PORTA = 0;

  while(1){
    PORTA ^= (1 << PA4);
    _delay_ms(1000);
  }

  return 0;
}
