/*
 * pins_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_PINS_HAL_PINS_HAL_H_
#define INTERFACE_PINS_HAL_PINS_HAL_H_
#include "Cpu.h"

status_t pins_init__hal_api(void);
void pins_set_pins_direction_hal_api(GPIO_Type * const base,pins_channel_type_t pins);
void pins_set_pins_hal_api(GPIO_Type * const base,pins_channel_type_t pins);
void pins_toggle_pins_hal_api(GPIO_Type * const base,pins_channel_type_t pins);
void pins_clear_pins_hal_api(GPIO_Type * const base,pins_channel_type_t pins);
uint32_t pins_read_pins_hal_api(const GPIO_Type * const base);
status_t pins_set_canrx_wake_api(void);
status_t pins_set_canrx_halt_api(void);


#endif /* INTERFACE_PINS_HAL_PINS_HAL_H_ */
