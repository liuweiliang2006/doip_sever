/*
 * spi_communication_apl.c
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "com_task.h"

void spi_prv_send_task_apl( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t taksTime = 0;
    uint8_t taksRingTime = 0;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (5/portTICK_RATE_MS));
        taksTime ++;
        if(taksTime >=2)
        {
            taksTime = 0;
            spi_data_to_soc_fml_api();
            spi_timeout_process_fml_api();
        }
        taksRingTime ++;
        if(taksRingTime >= 3)
        {
            taksRingTime = 0;
            read_spi_ringbuffer_fml_api();
        }
    }
}

void can_run_task_apl( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t cantaskTimes=0;
    canstack_init_fml_api();
    //adc_init();
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (5/portTICK_RATE_MS));

        if(cantaskTimes %2 == 0)
        {
            can_run_function_fml_api();
        }
        else
        {
            read_can_Ringbuffer_fml_api();
        }
        //read_voltage_fml();
        cantaskTimes ++;
    }
}

