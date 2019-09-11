#ifndef ADC_H
#define ADC_H
#include <avr/io.h>

#define T_C 40
#define T_DS 0.1
#define T_DH 0.05
#define T_WI 0.4
#define T_RI 0.4

void ADC_init(void);
uint8_t ADC_read(uint8_t channel);

uint8_t ADC_read2(uint8_t channel);
void ADC_setCS(uint8_t value);
void ADC_setChannel(uint8_t channel);
void ADC_setWR(uint8_t value);
void ADC_setRD(uint8_t value);


#endif
