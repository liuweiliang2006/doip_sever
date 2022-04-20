/*
 * uds_apl.c
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "pubsub.h"
#include <printflib.h>

#include "com_task.h"
/**************************************************************/
void uds_store_task_apl( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    read_udsData_fml_api();
    read_dtcData_fml_api();
    dig2EServiceActive = 1;
    ps_subscriber_t *su = ps_new_subscriber(10, STRLIST("systemPowerMode"));
    ps_msg_t *msg = NULL;
    uint8_t powerModeData[1];
     while(1)
     {
        vTaskDelayUntil(&xNextWakeTime, (10/portTICK_RATE_MS));
//        count = ps_waiting(su);
        msg = ps_get(su,0);
        if (msg != NULL)
        {
            if(IS_INT(msg))
            {
            	powerModeData[0] = (uint8_t)msg->int_val;
//            	uart_printf_data_fml_api(&powerModeData[0],1,",systemPowerMode",UARTTASKPRINT);
            }
            ps_unref_msg(msg);
        }
        check_did_dtc_status_fml_api(powerModeData[0]);
     }
}


