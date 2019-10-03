#include "spi.h"

void SPI_master_init(void){
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<DDB5)|(1<<DDB7);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


void SPI_master_transmit(uint8_t data){
  /* Start transmission */
  SPDR = data;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)))
  ;
}


void SPI_slave_init(void){
  /* Set MISO output, all others input */
  DDRB = (1<<DDB6);
  /* Enable SPI */
  SPCR = (1<<SPE);
}


uint8_t SPI_slave_receive(void){
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
      ;
    /* Return data register */
    return SPDR;
}

// value needs to be 0 or 1
void SPI_set_SS(uint8_t value){
  /*Set slave select to output*/
  DDRB = (1<<DDB4);
  /*Set SS*/
  PORTB = (value << PB4);
}
