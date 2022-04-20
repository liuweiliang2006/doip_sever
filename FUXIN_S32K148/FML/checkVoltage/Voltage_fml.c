/*
 * fml_adc.c
 *
 *  Created on: 2021Äê5ÔÂ20ÈÕ
 *      Author: Administrator
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "Cpu.h"
#include "com_task.h"

#include <stdint.h>
#include <stdbool.h>

#define ADC_INSTANCE    0UL
#define ADC_CHN         28U
#define ADC_VREFH       5.0f
#define ADC_VREFL       0.0f
uint8_t selectedGroupIndex;
uint16_t resultStartOffset;
uint8_t numChans;
uint16_t adcMax;
volatile bool groupConvDone = false;
volatile uint32_t resultLastOffset = 0;
char adcmsg[128] ={ 0, };
static void float_to_str (const float *srcValue, char *destStr, uint8_t maxLen)
{
    uint8_t i, lessThanOne = 0;
    float tempVal = (*srcValue);
    uint8_t currentVal;

    if (tempVal < 0)
    {
      tempVal *= -1;
      *destStr = '-';
      destStr++;
    }
    for (i = 0; i < maxLen; i++)
    {
        currentVal = (uint8_t) (tempVal);
        *destStr = currentVal + 48;
        destStr++;
        tempVal -= currentVal;
        if ((tempVal < 1) && (lessThanOne == 0))
        {
            *destStr = '.';
            destStr++;
            lessThanOne = 1;
        }
        tempVal *= 10;
    }
    *destStr = 0;
}
void adc_pal1_callback(const adc_callback_info_t * const callbackInfo, void * userData)
{
    (void) userData;
    groupConvDone = true;
    resultLastOffset = callbackInfo->resultBufferTail;
}

void adc_init_fml_api(void)
{
    status_t status;
    /* Get ADC max value from the resolution configured in extension field */
    adc_resolution_t resolution = ((extension_adc_s32k1xx_t *)(adc_pal1_InitConfig0.extension))->resolution;
    if (resolution == ADC_RESOLUTION_8BIT)
        adcMax = (uint16_t) (1 << 8);
    else if (resolution == ADC_RESOLUTION_10BIT)
        adcMax = (uint16_t) (1 << 10);
    else
        adcMax = (uint16_t) (1 << 12);

    /* Initialize the ADC PAL
     *  -   See ADC PAL component for the configuration details
     */
    for(int i = 0; i< 4; i++)
    {
        /* We add 16 because the value of ADC_INPUTCHAN_EXT28 is 44  */
        DEV_ASSERT(adc_pal1_ChansArray00[i] == (ADC_CHN + 16U)) ;
    }
    DEV_ASSERT(adc_pal1_instance.instIdx == ADC_INSTANCE);
    status = adc_init_hal_api(&adc_pal1_instance, &adc_pal1_InitConfig0);
    DEV_ASSERT(status == STATUS_SUCCESS);
    /* Start the selected SW triggered group of conversions */
    selectedGroupIndex = 0u;
    status = adc_start_group_conversion_hal_api(&adc_pal1_instance, selectedGroupIndex);
    DEV_ASSERT(status == STATUS_SUCCESS);
     numChans = adc_pal1_InitConfig0.groupConfigArray[selectedGroupIndex].numChannels;
    resultStartOffset = 0u;
}

void read_voltage_fml(void)
{
    status_t status;
    uint32_t sum, avg;
    float avgVolts;
    sum = 0;
    if(groupConvDone == true)
    {
        for(uint8_t idx = resultStartOffset; idx <= resultLastOffset; idx++)
        {
            sum += adc_pal1_Results00[idx]; /* Results are directly available in resultBuffer associated with the group at initialization */
        }
        DEV_ASSERT((resultLastOffset - resultStartOffset + 1) == numChans);
        avg = sum / numChans;

        /* Convert avg to volts */
        avgVolts = ((float) avg / adcMax) * (ADC_VREFH - ADC_VREFL);
        /* Convert avg to string */
        float_to_str(&avgVolts, adcmsg, 5);
        //uart_printf_char_fml_api(UARTTASKPRINT,adcmsg);
        groupConvDone = false;
        /* Restart the SW triggered group of conversions */
        status = adc_start_group_conversion_hal_api(&adc_pal1_instance, selectedGroupIndex); /* Restart can be avoided if SW triggered group is configured to run in continuous mode */
        DEV_ASSERT(status == STATUS_SUCCESS);
    }
}



