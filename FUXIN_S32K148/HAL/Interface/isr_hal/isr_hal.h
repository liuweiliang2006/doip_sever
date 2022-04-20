/*
 * isr_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_ISR_HAL_ISR_HAL_H_
#define INTERFACE_ISR_HAL_ISR_HAL_H_
#include "Cpu.h"

void int_sys_install_handler_hal_api(IRQn_Type irqNumber,const isr_t newHandler,isr_t* const oldHandler);
void int_sys_set_priority_hal_api(IRQn_Type irqNumber, uint8_t priority);
void int_sys_enable_irq_hal_api(IRQn_Type irqNumber);

#define  ENABLE_IRQ_GLOBAL INT_SYS_EnableIRQGlobal()
#define  DISENABLE_IRQ_GLOBAL INT_SYS_DisableIRQGlobal()

#endif /* INTERFACE_ISR_HAL_ISR_HAL_H_ */
