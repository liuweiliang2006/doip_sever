/*
 * lpit_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_LPIT_HAL_LPIT_HAL_H_
#define INTERFACE_LPIT_HAL_LPIT_HAL_H_
#include "Cpu.h"

void lpit_init_hal_api(uint32_t instance);
status_t lpit_init_channe_hal_api(uint32_t instance, uint32_t channel);
void lpit_start_timer_channels_hal_api(uint32_t instance,uint32_t Channel);
void lpit_stop_timer_channels_hal_api(uint32_t instance,uint32_t Channel);
void lpit_clear_interrupt_flag_hal_api(uint32_t instance,uint32_t Channel);


#endif /* INTERFACE_LPIT_HAL_LPIT_HAL_H_ */
