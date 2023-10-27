#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


static esp_adc_cal_characteristics_t adc1_chars;


void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    
    while (1) 
    {
        int adc_value = adc1_get_raw(ADC1_CHANNEL_0);
        uint32_t mV = adc_value*3.3/4096;
        printf("ADC Value: %d ADC volt: %ld", adc_value, mV);
        printf("\n");
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}