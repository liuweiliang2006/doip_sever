/*
 * task_info.c
 *
 *  Created on: 2021Äê9ÔÂ29ÈÕ
 *      Author: Administrator
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "com_task.h"
#include "pwrmanage_apl.h"
#include "printflib.h"

#include "task_info.h"

#if TASK_INFO

void taskinfo_task_apl( void *pvParameters )
{
    uint32_t ArraySize=0,x,TotalRunTime;
    TaskStatus_t *StatusArray;
    TaskHandle_t TaskHandle;
    TaskStatus_t TaskStatus;
    while(1)
    {
        TaskHandle=xTaskGetHandle("MQTT_test");
        vTaskGetInfo((TaskHandle_t  )TaskHandle,
                         (TaskStatus_t* )&TaskStatus,
                         (BaseType_t    )pdTRUE,
                         (eTaskState    )eInvalid);
        Printf("taskname:              %s\r\n",TaskStatus.pcTaskName);
        Printf("taskid  :              %d\r\n",(int)TaskStatus.xTaskNumber);
        Printf("tasksts :              %d\r\n",TaskStatus.eCurrentState);
        Printf("taskstackbase :        %#x\r\n",(int)TaskStatus.pxStackBase);
        Printf("stackspace:            %d\r\n",TaskStatus.usStackHighWaterMark);
        Printf("_____________________\r\n");
//        ArraySize = uxTaskGetNumberOfTasks();
//        StatusArray=pvPortMalloc(ArraySize*sizeof(TaskStatus_t));
//        uxTaskGetSystemState((TaskStatus_t*)StatusArray,(UBaseType_t)ArraySize,(uint32_t*)&TotalRunTime);
//        for(x=0;x<ArraySize;x++)
//        {
//            Printf("%s\t\t%d\t\t\t%d\t\t\t\r\n",StatusArray[x].pcTaskName,(int)StatusArray[x].uxCurrentPriority,(int)StatusArray[x].xTaskNumber);
//        }
//        vPortFree(StatusArray);
        vTaskDelay(5000);
    }
}

#endif
