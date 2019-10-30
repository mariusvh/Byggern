#include "ir.h"
#include "adc.h"
uint8_t total_bins = 4;
uint16_t bins[4];
uint8_t bin_index = 0;
uint16_t sum = 0;

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
    
    return average;
}

uint16_t IR_count_scores(){
    /*10bits -> 1024 -> 5V, thus 2V (2.6V w/offset) -> 400 */
    uint16_t IR_threshold = 400;
    uint8_t score = 0;
    if (IR_digital_filter() <= IR_threshold)
    {
        score = score + 1;
    }
    return score;    
}