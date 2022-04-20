/*
 * pwr_manage_test.c
 *
 *  Created on: 2021年7月22日
 *      Author: Administrator
 */

/*
 * fml_uart.c
 *
 *  Created on: 2021年5月25日
 *      Author: Administrator
 */
 #include "Cpu.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "com_task.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "pubsub.h"
#include "pwr_manage_test.h"
#include "pwrmanage_apl.h"

typedef enum
{
    serial_ignOff = 1,
    serial_ignACC =2,
    serial_ignOn = 3,
    serial_ignReady = 4,
    serial_AntithelfArm = 5,
    serial_AntithelfDisarm =6,
    serial_AntithelfPream = 7,
    serial_AntithelfWarning = 8,
    serial_FLOpen = 9,
    serial_FLClose = 10,
    serial_SOCFiveMinute = 11,
    serial_SocDoubleClick = 12,
    serial_SocHearBeatEn = 13,
    serial_SocHearBeatDis = 14,
    serial_SocACKNotAllow = 15,
    serial_SocACKAllow = 16,
    serial_DBC = 17
};
QueueHandle_t pwrManageQueue = NULL;

void pwrmanage_test_task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint32_t value = 0;

    ps_msg_t *SPISendMsg = NULL;
    ps_subscriber_t *SPISendSub;

//    SPISendSub = ps_new_subscriber(10, STRLIST("SpiSendRequst"));  //

    pwrManageQueue = xQueueCreate(10,32);
    while(1)
    {
       vTaskDelayUntil(&xNextWakeTime, (40/portTICK_RATE_MS));
       if (xQueueReceive(pwrManageQueue, &value, 0))
       {
           if(value == serial_ignOff)
           {
//               ps_flush(igsSwSub);
               PUB_INT_FL("systemPowerMode", (ignOff), FL_STICKY);
           }
           else if ( value == serial_ignACC)
           {
//               ps_flush(igsSwSub);
               PUB_INT_FL("systemPowerMode", (ignACC), FL_STICKY);
           }
           else if ( value == serial_ignOn)
           {
//               ps_flush(igsSwSub);
               PUB_INT_FL("systemPowerMode", (ignON), FL_STICKY);
           }
           else if ( value == serial_ignReady)
           {
               PUB_INT_FL("systemPowerMode", (ignReady), FL_STICKY);
           }
           else if ( value == serial_AntithelfArm)
           {
               PUB_INT_FL("antiThelfStatus", (Arm), FL_STICKY);
           }
           else if ( value == serial_AntithelfDisarm)
           {
               PUB_INT_FL("antiThelfStatus", (Disarm), FL_STICKY);
           }
           else if ( value == serial_AntithelfPream)
           {
               PUB_INT_FL("systemPowerMode", (Prearm), FL_STICKY);
           }
           else if ( value == serial_AntithelfWarning)
           {
               PUB_INT_FL("systemPowerMode", (Warning), FL_STICKY);
           }
           else if ( value == serial_FLOpen)
           {
               PUB_INT_FL("FLDoorStatus", (DoorOpen), FL_STICKY);
           }
           else if ( value == serial_FLClose)
           {
               PUB_INT_FL("FLDoorStatus", (DoorClose), FL_STICKY);
           }
//           else if ( value == serial_SOCFiveMinute)
//           {
//               PUB_INT_FL("systemPowerMode", (ignACC), FL_STICKY);
//           }
           else if ( value == serial_SocDoubleClick)
           {
               PUB_INT_FL("DoubleClick", (DoubleClickEnable), FL_STICKY);
           }
           else if ( value == serial_SocHearBeatEn)
           {
               socHeartBeatFlag = 1;
           }
           else if ( value == serial_SocHearBeatDis)
           {
               socHeartBeatFlag = 0;
           }
           else if ( value == serial_SocACKNotAllow)
           {
               PUB_INT_FL("SpiRec", (OneHourDisable), FL_STICKY);
           }
           else if ( value == serial_SocACKAllow)
           {
               PUB_INT_FL("SpiRec", (OneHourEnable), FL_STICKY);
           }
           else if ( value == serial_DBC)
           {
               PUB_INT_FL("DbcWakeUp", (DbcSigEnable), FL_STICKY);
           }
       }

       SPISendMsg = ps_get(socSpiSendSub,0);
       if (SPISendMsg != NULL)
       {
           value = (uint8_t)SPISendMsg->int_val;
           if (value == 1) // 5min timeout or 1 hour timeout
           {
               Printf("timeout request\r\n");
           }
           ps_unref_msg(SPISendMsg);
       }
#if PWR_MANAGE_DEBUG
//       myprintf("pwrmanage\r\n");
#endif

    }
}
