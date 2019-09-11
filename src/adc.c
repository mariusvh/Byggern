#include "adc.h"

#define F_CPU 4000000
#include "util/delay.h"

void ADC_init(void) {
  MCUCR |= (1 << SRE);
  SFIOR |= (1 << XMM2);
}

uint8_t ADC_read(uint8_t channel){
  volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
  //uint16_t ext_adc_size = 0x400; //

  *ext_adc = 0x04 | channel; // choose channel in ADC
  _delay_us(60);
  return *ext_adc;
}

uint8_t ADC_read2(uint8_t channel){
  volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
  ext_adc[0] = channel;
  _delay_us(40);
  return ext_adc[0];
}


// value needs to be 0 or 1
void ADC_setCS(uint8_t value){
  DDRC = 0x0F;
  PORTC = 0;
  PORTC = (value << PC2);

}

// value needs to be 1-4
void ADC_setChannel(uint8_t channel){
  DDRA = 1;
  PORTA = 0;
  PORTA = (1 << PA2);
  switch (channel) {
    case 1 :
      break;
    case 2 :
      PORTA = (1 << PA0);
      break;
    case 3:
      PORTA = (1 << PA1);
      break;
    case 4:
      PORTA = (1 << PA0) | (1 << PA1);
      break;
  }
}


// value needs to be 0 or 1
void ADC_setWR(uint8_t value){
  DDRD |= 0x40;
  if (value) {
    PORTD |= (1 << PD6);
  }
  else {
    PORTD &= (0xBF);
  }

}


// value needs to be 0 or 1
void ADC_setRD(uint8_t value){
  DDRD |= 0x80;
  if (value) {
    PORTD |= (1 << PD7);
  }
  else {
    PORTD &= (0x7F);
  }
}

/*void ADC_config(int channel){
  ADC_setRD(1);
  ADC_setCS(0);
  ADC_setWR(0);
  _delay_ms(T_WI);
  ADC_setChannel(channel);
  _delay_ms(T_DS);
  ADC_setWR(1);
  _delay_ms(T_DH);
  ADC_setCS(1);
  _delay_ms(T_C-T_DH);
}

uint8_t ADC_read(uint8_t channel) {
  ADC_setRD(1);
  ADC_setCS(0);
  ADC_setWR(0);
  _delay_ms(T_WI);
  ADC_setChannel(channel);
  _delay_ms(T_DS);
  ADC_setWR(1);
  _delay_ms(T_DH);
  ADC_setCS(1);
  _delay_ms(T_C-T_DH);

  ADC_setCS(0);
  ADC_setRD(0);
  _delay_ms(T_RI);

}
*/
