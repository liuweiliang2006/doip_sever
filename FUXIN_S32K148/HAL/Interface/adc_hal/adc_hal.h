/*
 * adc_hal.h
 *
 *  Created on: 2021��6��2��
 *      Author: Administrator
 */

#ifndef INTERFACE_ADC_HAL_ADC_HAL_H_
#define INTERFACE_ADC_HAL_ADC_HAL_H_
#include "Cpu.h"

status_t adc_init_hal_api(const adc_instance_t * const instance,const adc_config_t * const config);

status_t adc_start_group_conversion_hal_api(const adc_instance_t * const instance,const uint32_t groupIdx);


#endif /* INTERFACE_ADC_HAL_ADC_HAL_H_ */
