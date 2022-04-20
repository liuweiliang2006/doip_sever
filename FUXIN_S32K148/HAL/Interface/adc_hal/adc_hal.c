/*
 * adc_hal.c
 *
 *  Created on: 2021��6��2��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"

status_t adc_init_hal_api(const adc_instance_t * const instance,
        const adc_config_t * const config)
{
    return ADC_Init(instance,config);
}

status_t adc_start_group_conversion_hal_api(const adc_instance_t * const instance,
        const uint32_t groupIdx)
{
    return ADC_StartGroupConversion(instance,groupIdx);
}

