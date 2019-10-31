#include "ir.h"
#include "adc.h"
#include <stdio.h>
uint8_t total_bins = 4;
uint16_t bins[4];
volatile uint8_t bin_index = 0;
volatile uint16_t sum = 0;
volatile uint8_t score = 0;
volatile uint8_t flag = 1;

void IR_init(){

    ADC_init();
    /*Initialize bins*/
    for (uint8_t current_value = 0; current_value < total_bins; current_value++)
    {
        bins[current_value] = 0;
    }
    /*Initialize first read*/
    bins[bin_index] = ADC_read();
    sum = bins[bin_index];
    printf("SUM: %x\n\r", sum);
}

uint16_t IR_digital_filter(){
    /*Removing the previous read of bin*/
    sum = sum - bins[bin_index];

    /*Reading updated value of bin */
    bins[bin_index] = ADC_read();

    /*Adding updated bin to sum*/
    sum = sum + bins[bin_index];

    bin_index = bin_index + 1;
    
    /*reset bin_index if it exceeds 4*/
    if(bin_index >= total_bins){
        bin_index = 0;
    }

    uint16_t average = sum/total_bins;

    printf("Average: %x\n\r", average);
    
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