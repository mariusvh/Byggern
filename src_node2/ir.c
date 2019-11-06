#include "ir.h"
#include "adc.h"
#include <stdio.h>
uint8_t total_samples = 4;
uint16_t bin[4];
volatile uint8_t sample_index = 0;
volatile uint16_t sum = 0;
volatile uint8_t score = 0;
volatile uint8_t flag = 1;

void IR_init(){

    ADC_init();
    /*Initialize samples*/
    for (uint8_t current_value = 0; current_value < total_samples; current_value++)
    {
        bin[current_value] = 0;
    }
    /*Initialize first read*/
    bin[sample_index] = ADC_read();
    sum = bin[sample_index];
    //printf("SUM: %x\n\r", sum);
}

uint16_t IR_digital_filter(){
    /*Removing the previous read of sample*/
    sum = sum - bin[sample_index];

    /*Reading updated value of sample */
    bin[sample_index] = ADC_read();

    /*Adding updated sample to sum*/
    sum = sum + bin[sample_index];

    sample_index = sample_index + 1;
    
    /*reset sample_index if it exceeds 4*/
    if(sample_index >= total_samples){
        sample_index = 0;
    }

    uint16_t average = sum/total_samples;

    //printf("Average: %x\n\r", average);
    
    return average;
}

uint16_t IR_count_scores(){
    /*score threshold at 100*/
    uint16_t score_threshold = 100;
    uint16_t no_score_threshold = 254;
    if (IR_digital_filter() <= score_threshold && flag == 0)
    {   
        score = score + 1;
        flag = 1;
    }
    if (IR_digital_filter() >= no_score_threshold && flag == 1)
    {
        flag = 0;
    }
    
    return score;    
}

uint8_t IR_game_over(){
    uint8_t score_limit = 20;
    if (IR_count_scores() >= score_limit)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}