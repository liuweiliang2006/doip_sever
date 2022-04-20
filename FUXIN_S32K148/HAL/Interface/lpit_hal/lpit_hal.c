/*
 * lpit_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"

void lpit_init_hal_api(uint32_t instance)
{
    LPIT_DRV_Init(instance, &lpit1_InitConfig);
}
status_t lpit_init_channe_hal_api(uint32_t instance, uint32_t channel)
{
    status_t status;
    switch(channel)
    {
        case 0:
            status = LPIT_DRV_InitChannel(instance, channel, &lpit1_ChnConfig0);
            break;
        case 1:
            status = LPIT_DRV_InitChannel(instance, channel, &lpit1_ChnConfig1);
            break;
        case 2:
            status = LPIT_DRV_InitChannel(instance, channel, &lpit1_ChnConfig2);
            break;
        default:
            break;
    }
    return status;
}
void lpit_start_timer_channels_hal_api(uint32_t instance,uint32_t Channel)
{
    uint32_t mask;
    mask = 1 << Channel;
    LPIT_DRV_StartTimerChannels(instance,mask);
}
void lpit_stop_timer_channels_hal_api(uint32_t instance,uint32_t Channel)
{
    uint32_t mask;
    mask = 1 << Channel;
    LPIT_DRV_StopTimerChannels(instance,mask);
}
void lpit_clear_interrupt_flag_hal_api(uint32_t instance,uint32_t Channel)
{
    uint32_t mask;
    mask = 1 << Channel;
    LPIT_DRV_ClearInterruptFlagTimerChannels(instance,mask);
}

