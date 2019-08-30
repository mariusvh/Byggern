#include "avr/io.h"
#include "uart.h"
#include <stdio.h>

#define F_CPU 4000000
#include "util/delay.h"

#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void main() {

  USART_Init(MYUBRR);
  fdevopen(USART_Transmit, USART_Receive);

  while (1) {
    //USART_Transmit('A');
    //SquareWaveTest();
    //printf(USART_Receive());


  }

}
/*
void SquareWaveTest(){

  DDRD = (1 << PD1);
  PORTD = 0;

  while(1){
    PORTD ^= (1 << PD1);
    _delay_ms(1000);
  }
}
*/
