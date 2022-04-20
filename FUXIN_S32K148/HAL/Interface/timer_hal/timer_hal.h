/*
 * timer_hal.h
 *
 *  Created on: 2021��6��3��
 *      Author: Administrator
 */

#ifndef INTERFACE_TIMER_HAL_TIMER_HAL_H_
#define INTERFACE_TIMER_HAL_TIMER_HAL_H_

#include "Cpu.h"

status_t timer_init_hal_api(uint32_t instance,const ftm_user_config_t * info,ftm_state_t * state);
status_t timer_dinit_hal_api(uint32_t instance);
status_t timer_init_counter_hal_api(uint32_t instance,const ftm_timer_param_t * timer);
status_t timer_counter_start_hal_api(uint32_t instance);
status_t timer_counter_stop_hal_api(uint32_t instance);
uint32_t timer_counter_read_hal_api(uint32_t instance);

#endif /* INTERFACE_TIMER_HAL_TIMER_HAL_H_ */
