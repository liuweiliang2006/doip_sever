/*
 * isr_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"

void int_sys_install_handler_hal_api(IRQn_Type irqNumber,
                            const isr_t newHandler,
                            isr_t* const oldHandler)
{
    INT_SYS_InstallHandler(irqNumber,newHandler,oldHandler);
}
void int_sys_set_priority_hal_api(IRQn_Type irqNumber, uint8_t priority)
{
    INT_SYS_SetPriority(irqNumber,priority);
}
void int_sys_enable_irq_hal_api(IRQn_Type irqNumber)
{
    INT_SYS_EnableIRQ(irqNumber);
}

