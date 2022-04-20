/*
 * uart_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_UART_HAL_UART_HAL_H_
#define INTERFACE_UART_HAL_UART_HAL_H_
#include "Cpu.h"

status_t lpuart_init__hal_api(uint32_t instance, lpuart_state_t * lpuartStatePtr,const lpuart_user_config_t * lpuartUserConfig);
status_t lpuart_send_data__hal_api(uint32_t instance,const uint8_t * txBuff,uint32_t txSize);
status_t lpuart_get_transmit_status__hal_api(uint32_t instance, uint32_t * bytesRemaining);
status_t lpuart_deinit_hal_api(uint32_t instance);
status_t lpuart_drv_senddatapolling_api(uint32_t instance,const uint8_t *txBuff,uint32_t txSize);



#endif /* INTERFACE_UART_HAL_UART_HAL_H_ */
