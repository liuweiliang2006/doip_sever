#include "Cpu.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "pubsub_demo.h"
#include "string.h"
#include "pubsub.h"
#include "stdlib.h"
#include "Driver_interface.h"
#include "BoardDefines.h"
#define SUCESSINFOPRINT (0)
#define ERRINFOPRINT (0)

#define ONE_TO_MUTI (0) //one push muti sub; muti push one sub

#define MUTI_TO_MUTI (1) //MTUI push muti sub; muti push MUTI sub

#define PUBSUB_TASK_PRIORITY        ( tskIDLE_PRIORITY + 4 )
#define PUBSUBL_STACK_SIZE                 ( ( unsigned short ) 300 )

#define PUBTASK_TIME (2)

#define SUBTASK_TIME (2)

#define PRINT_PRIO (500)

#define GROUPNUM (100)
#define SUBNUM (10)
#define QUEUESIZE (200)
enum PubTaskSignalCount{
    PubTask1SigCnt = 8,
    PubTask2SigCnt = 8,
    PubTask3SigCnt = 8,
    PubTask4SigCnt = 8,
    PubTask5SigCnt = 8,
    PubTask6SigCnt = 8,
    PubTask7SigCnt = 8,
    PubTask8SigCnt = 8,
    PubTask9SigCnt = 16,
    PubTask10SigCnt = 20,

};

uint32_t PubTimes[GROUPNUM] = {0};
uint32_t subRecCnt[SUBNUM+1][GROUPNUM+1] = {0};
EventGroupHandle_t pubEventGroup;

TaskHandle_t PubsubTask_Handle;  //pubsub task instance

#if ONE_TO_MUTI

void pubsub_pub_Task( void *pvParameters );
void pubsub_sub_Task( void *pvParameters );
void pubsub_sub1_Task( void *pvParameters );
void pubsub_sub2_Task( void *pvParameters );
void pubsub_sub3_Task( void *pvParameters );
void pubsub_sub4_Task( void *pvParameters );
void pubsub_sub5_Task( void *pvParameters );
void pubsub_sub6_Task( void *pvParameters );
void pubsub_sub7_Task( void *pvParameters );
void pubsub_sub8_Task( void *pvParameters );
void pubsub_sub9_Task( void *pvParameters );
void pubsub_sub10_Task( void *pvParameters );
void pubsub_sub11_Task( void *pvParameters );
void pubsub_sub12_Task( void *pvParameters );
void pubsub_sub13_Task( void *pvParameters );
void pubsub_sub14_Task( void *pvParameters );
void pubsub_sub15_Task( void *pvParameters );

#endif


#if MUTI_TO_MUTI

void pubsub_pub1_Task( void *pvParameters );
void pubsub_pub2_Task( void *pvParameters );
void pubsub_pub3_Task( void *pvParameters );
void pubsub_pub4_Task( void *pvParameters );
void pubsub_pub5_Task( void *pvParameters );
void pubsub_pub6_Task( void *pvParameters );
void pubsub_pub7_Task( void *pvParameters );
void pubsub_pub8_Task( void *pvParameters );
void pubsub_pub9_Task( void *pvParameters );
void pubsub_pub10_Task( void *pvParameters );

void pubsub_sub1_Task( void *pvParameters );
void pubsub_sub2_Task( void *pvParameters );
void pubsub_sub3_Task( void *pvParameters );
void pubsub_sub4_Task( void *pvParameters );
void pubsub_sub5_Task( void *pvParameters );
void pubsub_sub6_Task( void *pvParameters );
void pubsub_sub7_Task( void *pvParameters );
void pubsub_sub8_Task( void *pvParameters );
void pubsub_sub9_Task( void *pvParameters );
void pubsub_sub10_Task( void *pvParameters );
void pubsub_sub11_Task( void *pvParameters );
void pubsub_sub12_Task( void *pvParameters );
void pubsub_sub13_Task( void *pvParameters );
void pubsub_sub14_Task( void *pvParameters );
void pubsub_sub15_Task( void *pvParameters );

//void query_task(void *pvParameters);



#endif


void pubsub_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();

//    uart_printf_char_fml_api(true,"pubsub_task\r\n");
    ps_init();
    pubEventGroup = xEventGroupCreate();
    if(pubEventGroup == NULL)
    {

    }
    int_sys_enable_irq_hal_api(FTM0_Ovf_Reload_IRQn);
#if MUTI_TO_MUTI
//    taskENTER_CRITICAL();
    xTaskCreate( pubsub_sub1_Task, "pubsub_sub1", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+2 , NULL );
    xTaskCreate( pubsub_sub2_Task, "pubsub_sub2", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+2 , NULL );
    xTaskCreate( pubsub_sub3_Task, "pubsub_sub3", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub4_Task, "pubsub_sub4", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub5_Task, "pubsub_sub5", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub6_Task, "pubsub_sub6", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub7_Task, "pubsub_sub7", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub8_Task, "pubsub_sub8", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub9_Task, "pubsub_sub9", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub10_Task, "pubsub_sub10", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub11_Task, "pubsub_sub11", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub12_Task, "pubsub_sub12", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub13_Task, "pubsub_sub13", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub14_Task, "pubsub_sub14", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub15_Task, "pubsub_sub15", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );

    xTaskCreate( pubsub_pub1_Task, "pubsub_pub1", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub2_Task, "pubsub_pub2", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub3_Task, "pubsub_pub3", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub4_Task, "pubsub_pub4", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub5_Task, "pubsub_pub5", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub6_Task, "pubsub_pub6", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub7_Task, "pubsub_pub7", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub8_Task, "pubsub_pub8", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub9_Task, "pubsub_pub9", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub10_Task, "pubsub_pub10", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );

//    xTaskCreate((TaskFunction_t )query_task,
//                    (const char*    )"query_task",
//                    (uint16_t       )PUBSUBL_STACK_SIZE,
//                    (void*          )NULL,
//                    (UBaseType_t    )PUBSUB_TASK_PRIORITY,
//                    NULL);
#endif


#if ONE_TO_MUTI
//    xTaskCreate( pubsub_pub_Task, "pubsub_pub", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pubsub_sub_Task, "pubsub_sub", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub1_Task, "pubsub_sub1", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub2_Task, "pubsub_sub2", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub3_Task, "pubsub_sub3", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub4_Task, "pubsub_sub4", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub5_Task, "pubsub_sub5", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub6_Task, "pubsub_sub6", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub7_Task, "pubsub_sub7", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub8_Task, "pubsub_sub8", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub9_Task, "pubsub_sub9", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub10_Task, "pubsub_sub10", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub11_Task, "pubsub_sub11", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub12_Task, "pubsub_sub12", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub13_Task, "pubsub_sub13", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub14_Task, "pubsub_sub14", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_sub15_Task, "pubsub_sub15", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
    xTaskCreate( pubsub_pub_Task, "pubsub_pub", PUBSUBL_STACK_SIZE, NULL,PUBSUB_TASK_PRIORITY+1 , NULL );
#endif
    vTaskDelete(PubsubTask_Handle);
//    taskEXIT_CRITICAL();
}






static void send_byte_UART1(const uint8_t *sourceStr)
{
    uint32_t bytesRemaining;
    LPUART_DRV_SendData(INST_LPUART1, (uint8_t *)sourceStr, 1);
    while (LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining)!= STATUS_SUCCESS);
}

static void send_string_UART1(const uint8_t *recstring,int32_t length)
{
    uint32_t bytesRemaining;
    uint32_t i;
    for(i = 0; i < length; i++)
    {
        send_byte_UART1((recstring+i));
    }
}

static void bubbleSort(uint8_t *arr, int n)
{
    for (uint8_t i = 0; i<n - 1; i++)
        for (uint8_t j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                uint8_t temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }
        }
}

void uart_printf_inter(uint8_t *data,uint8_t len,char *format)
{
    uint8_t temp_char[10][2];
    int i;
    char print_msg[32]={" "};
    memcpy((uint8_t *)&print_msg[len*2], format, 32);
    for(i=0;i<len;i++)
    {
        put_hex( data[i] ,temp_char[i]);
        print_msg[0+i*2]= temp_char[i][0];
        print_msg[1+i*2]= temp_char[i][1];
    }
    send_string_UART1(print_msg,strlen(print_msg));
}


#if MUTI_TO_MUTI

void pubsub_pub1_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = 0;
    arrend = PubTask1SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK1,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK1) == SUBTASK1)
        {
            PUB_INT_FL("topic1", (senddata+1), FL_NONRECURSIVE);
            PUB_INT_FL("topic2", (senddata+2), FL_NONRECURSIVE);
            PUB_INT_FL("topic3", (senddata+3), FL_NONRECURSIVE);
            PUB_INT_FL("topic4", (senddata+4), FL_NONRECURSIVE);
            PUB_INT_FL("topic5", (senddata+5), FL_NONRECURSIVE);
            PUB_INT_FL("topic6", (senddata+6), FL_NONRECURSIVE);
            PUB_INT_FL("topic7", (senddata+7), FL_NONRECURSIVE);
            PUB_INT_FL("topic8", (senddata+8), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}


void pubsub_pub2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK2,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK2) == SUBTASK2)
        {
            PUB_INT_FL("topic9", (senddata+9), FL_NONRECURSIVE);
            PUB_INT_FL("topic10", (senddata+10), FL_NONRECURSIVE);
            PUB_INT_FL("topic11", (senddata+11), FL_NONRECURSIVE);
            PUB_INT_FL("topic12", (senddata+12), FL_NONRECURSIVE);
            PUB_INT_FL("topic13", (senddata+13), FL_NONRECURSIVE);
            PUB_INT_FL("topic14", (senddata+14), FL_NONRECURSIVE);
            PUB_INT_FL("topic15", (senddata+15), FL_NONRECURSIVE);
            PUB_INT_FL("topic16", (senddata+16), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub3_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK3,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK3) == SUBTASK3)
        {
            PUB_INT_FL("topic17", (senddata+17), FL_NONRECURSIVE);
            PUB_INT_FL("topic18", (senddata+18), FL_NONRECURSIVE);
            PUB_INT_FL("topic19", (senddata+19), FL_NONRECURSIVE);
            PUB_INT_FL("topic20", (senddata+20), FL_NONRECURSIVE);
            PUB_INT_FL("topic21", (senddata+21), FL_NONRECURSIVE);
            PUB_INT_FL("topic22", (senddata+22), FL_NONRECURSIVE);
            PUB_INT_FL("topic23", (senddata+23), FL_NONRECURSIVE);
            PUB_INT_FL("topic24", (senddata+24), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub4_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK4,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK4) == SUBTASK4)
        {
            PUB_INT_FL("topic25", (senddata+25), FL_NONRECURSIVE);
            PUB_INT_FL("topic26", (senddata+26), FL_NONRECURSIVE);
            PUB_INT_FL("topic27", (senddata+27), FL_NONRECURSIVE);
            PUB_INT_FL("topic28", (senddata+28), FL_NONRECURSIVE);
            PUB_INT_FL("topic29", (senddata+29), FL_NONRECURSIVE);
            PUB_INT_FL("topic30", (senddata+30), FL_NONRECURSIVE);
            PUB_INT_FL("topic31", (senddata+31), FL_NONRECURSIVE);
            PUB_INT_FL("topic32", (senddata+32), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub5_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK5,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK5) == SUBTASK5)
        {
            PUB_INT_FL("topic33", (senddata+33), FL_NONRECURSIVE);
            PUB_INT_FL("topic34", (senddata+34), FL_NONRECURSIVE);
            PUB_INT_FL("topic35", (senddata+35), FL_NONRECURSIVE);
            PUB_INT_FL("topic36", (senddata+36), FL_NONRECURSIVE);
            PUB_INT_FL("topic37", (senddata+37), FL_NONRECURSIVE);
            PUB_INT_FL("topic38", (senddata+38), FL_NONRECURSIVE);
            PUB_INT_FL("topic39", (senddata+39), FL_NONRECURSIVE);
            PUB_INT_FL("topic40", (senddata+40), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub6_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK6,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK6) == SUBTASK6)
        {
            PUB_INT_FL("topic41", (senddata+41), FL_NONRECURSIVE);
            PUB_INT_FL("topic42", (senddata+42), FL_NONRECURSIVE);
            PUB_INT_FL("topic43", (senddata+43), FL_NONRECURSIVE);
            PUB_INT_FL("topic44", (senddata+44), FL_NONRECURSIVE);
            PUB_INT_FL("topic45", (senddata+45), FL_NONRECURSIVE);
            PUB_INT_FL("topic46", (senddata+46), FL_NONRECURSIVE);
            PUB_INT_FL("topic47", (senddata+47), FL_NONRECURSIVE);
            PUB_INT_FL("topic48", (senddata+48), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub7_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK7,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK7) == SUBTASK7)
        {
            PUB_INT_FL("topic49", (senddata+49), FL_NONRECURSIVE);
            PUB_INT_FL("topic50", (senddata+50), FL_NONRECURSIVE);
            PUB_INT_FL("topic51", (senddata+51), FL_NONRECURSIVE);
            PUB_INT_FL("topic52", (senddata+52), FL_NONRECURSIVE);
            PUB_INT_FL("topic53", (senddata+53), FL_NONRECURSIVE);
            PUB_INT_FL("topic54", (senddata+54), FL_NONRECURSIVE);
            PUB_INT_FL("topic55", (senddata+55), FL_NONRECURSIVE);
            PUB_INT_FL("topic56", (senddata+56), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub8_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt+PubTask8SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK8,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK8) == SUBTASK8)
        {
            PUB_INT_FL("topic57", (senddata+57), FL_NONRECURSIVE);
            PUB_INT_FL("topic58", (senddata+58), FL_NONRECURSIVE);
            PUB_INT_FL("topic59", (senddata+59), FL_NONRECURSIVE);
            PUB_INT_FL("topic60", (senddata+60), FL_NONRECURSIVE);
            PUB_INT_FL("topic61", (senddata+61), FL_NONRECURSIVE);
            PUB_INT_FL("topic62", (senddata+62), FL_NONRECURSIVE);
            PUB_INT_FL("topic63", (senddata+63), FL_NONRECURSIVE);
            PUB_INT_FL("topic64", (senddata+64), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub9_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt
            +PubTask8SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt+PubTask8SigCnt
            +PubTask9SigCnt;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK9,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK9) == SUBTASK9)
        {
            PUB_INT_FL("topic65", (senddata+65), FL_NONRECURSIVE);
            PUB_INT_FL("topic66", (senddata+66), FL_NONRECURSIVE);
            PUB_INT_FL("topic67", (senddata+67), FL_NONRECURSIVE);
            PUB_INT_FL("topic68", (senddata+68), FL_NONRECURSIVE);
            PUB_INT_FL("topic69", (senddata+69), FL_NONRECURSIVE);
            PUB_INT_FL("topic70", (senddata+70), FL_NONRECURSIVE);
            PUB_INT_FL("topic71", (senddata+71), FL_NONRECURSIVE);
            PUB_INT_FL("topic72", (senddata+72), FL_NONRECURSIVE);
            PUB_INT_FL("topic73", (senddata+73), FL_NONRECURSIVE);
            PUB_INT_FL("topic74", (senddata+74), FL_NONRECURSIVE);
            PUB_INT_FL("topic75", (senddata+75), FL_NONRECURSIVE);
            PUB_INT_FL("topic76", (senddata+76), FL_NONRECURSIVE);
            PUB_INT_FL("topic77", (senddata+77), FL_NONRECURSIVE);
            PUB_INT_FL("topic78", (senddata+78), FL_NONRECURSIVE);
            PUB_INT_FL("topic79", (senddata+79), FL_NONRECURSIVE);
            PUB_INT_FL("topic80", (senddata+80), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_pub10_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    EventBits_t uxBits=0;
    uint8_t senddata =0,arrstart = 0,arrend = 0;
    xNextWakeTime = xTaskGetTickCount();
    arrstart = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt
            +PubTask8SigCnt+PubTask9SigCnt;
    arrend = PubTask1SigCnt+PubTask2SigCnt+PubTask3SigCnt+PubTask4SigCnt+PubTask5SigCnt+PubTask6SigCnt+PubTask7SigCnt+PubTask8SigCnt
            +PubTask9SigCnt+PubTask10SigCnt;

    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK10,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK10) == SUBTASK10)
        {
            PUB_INT_FL("topic81", (senddata+81), FL_NONRECURSIVE);
            PUB_INT_FL("topic82", (senddata+82), FL_NONRECURSIVE);
            PUB_INT_FL("topic83", (senddata+83), FL_NONRECURSIVE);
            PUB_INT_FL("topic84", (senddata+84), FL_NONRECURSIVE);
            PUB_INT_FL("topic85", (senddata+85), FL_NONRECURSIVE);
            PUB_INT_FL("topic86", (senddata+86), FL_NONRECURSIVE);
            PUB_INT_FL("topic87", (senddata+87), FL_NONRECURSIVE);
            PUB_INT_FL("topic88", (senddata+88), FL_NONRECURSIVE);
            PUB_INT_FL("topic89", (senddata+89), FL_NONRECURSIVE);
            PUB_INT_FL("topic90", (senddata+90), FL_NONRECURSIVE);
            PUB_INT_FL("topic91", (senddata+91), FL_NONRECURSIVE);
            PUB_INT_FL("topic92", (senddata+92), FL_NONRECURSIVE);
            PUB_INT_FL("topic93", (senddata+93), FL_NONRECURSIVE);
            PUB_INT_FL("topic94", (senddata+94), FL_NONRECURSIVE);
            PUB_INT_FL("topic95", (senddata+95), FL_NONRECURSIVE);
            PUB_INT_FL("topic96", (senddata+96), FL_NONRECURSIVE);
            PUB_INT_FL("topic97", (senddata+97), FL_NONRECURSIVE);
            PUB_INT_FL("topic98", (senddata+98), FL_NONRECURSIVE);
            PUB_INT_FL("topic99", (senddata+99), FL_NONRECURSIVE);
            PUB_INT_FL("topic100", (senddata+100), FL_NONRECURSIVE);
            for(uint8_t i = arrstart; i < arrend; i++)
            {
                PubTimes[i] = PubTimes[i]+1;
            }
        }
    }
}

void pubsub_sub1_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK1][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK1][1] % PRINT_PRIO) ==0) &&
                (subRecCnt[SUBTASK1][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK1][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK1][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK1][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB1:");
                    itoa(subRecCnt[SUBTASK1][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK1 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK2][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK2][1] % (PRINT_PRIO+10)) ==0) &&
                (subRecCnt[SUBTASK2][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK2][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK2][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK2][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB2:");
                    itoa(subRecCnt[SUBTASK2][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK2 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub3_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK3][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK3][1] % (PRINT_PRIO+20)) ==0) &&
                (subRecCnt[SUBTASK3][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK3][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK3][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK3][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB3:");
                    itoa(subRecCnt[SUBTASK3][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK3 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub4_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK4][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK4][1] % (PRINT_PRIO+30)) ==0) &&
                (subRecCnt[SUBTASK4][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK4][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK4][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK4][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB4:");
                    itoa(subRecCnt[SUBTASK4][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK4 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub5_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK5][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK5][1] % (PRINT_PRIO+40)) ==0) &&
                (subRecCnt[SUBTASK5][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK5][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK5][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK5][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB5:");
                    itoa(subRecCnt[SUBTASK5][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK5 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub6_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK6][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK6][1] % (PRINT_PRIO+50)) ==0) &&
                (subRecCnt[SUBTASK6][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK6][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK6][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK6][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB6:");
                    itoa(subRecCnt[SUBTASK6][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK6 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub7_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK7][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK7][1] % (PRINT_PRIO+60)) ==0) &&
                (subRecCnt[SUBTASK7][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK7][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK7][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK7][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB7:");
                    itoa(subRecCnt[SUBTASK7][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK7 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub8_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK8][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK8][1] % (PRINT_PRIO+70)) ==0) &&
                (subRecCnt[SUBTASK8][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK8][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK8][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK8][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB8:");
                    itoa(subRecCnt[SUBTASK8][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK8 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

void pubsub_sub9_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count = 0;
    static uint32_t currentTimes = 0 ,lastTimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST(
            "topic1","topic2","topic3","topic4","topic5","topic6","topic7","topic8",
            "topic9","topic10","topic11","topic12","topic13","topic14","topic15","topic16",
            "topic17","topic18","topic19","topic20","topic21","topic22","topic23","topic24",
            "topic25","topic26","topic27","topic28","topic29","topic30","topic31","topic32",
            "topic33","topic34","topic35","topic36","topic37","topic38","topic39","topic40",
            "topic41","topic42","topic43","topic44","topic45","topic46","topic47","topic48",
            "topic49","topic50","topic51","topic52","topic53","topic54","topic55","topic56",
            "topic57","topic58","topic59","topic60","topic61","topic62","topic63","topic64",
            "topic65","topic66","topic67","topic68","topic69","topic70","topic71","topic72",
            "topic73","topic74","topic75","topic76","topic77","topic78","topic79","topic80",
            "topic81","topic82","topic83","topic84","topic85","topic86","topic87","topic88",
            "topic89","topic90","topic91","topic92","topic93","topic94","topic95","topic96",
            "topic97","topic98","topic99","topic100"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        count = ps_waiting(su);
        for(uint8_t i = 0; i < count ; i++)
        {
            msg = ps_get(su,-1);
            if (msg != NULL)
            {
                if(IS_INT(msg))
                {
                    subRecCnt[SUBTASK9][(uint8_t)msg->int_val]++;
                }
                ps_unref_msg(msg);
            }
        }

        if(((subRecCnt[SUBTASK9][1] % (PRINT_PRIO+80)) ==0) &&
                (subRecCnt[SUBTASK9][1] != 0))
        {
            currentTimes = subRecCnt[SUBTASK9][1];
            if(lastTimes != currentTimes)
            {
                lastTimes = currentTimes;
                uint8_t result = 0;
                uint8_t i;
                for( i = 0; i < GROUPNUM ; i++)
                {
                    if(subRecCnt[SUBTASK9][i+1] == PubTimes[i])
                        continue ;
                    else
                    {
                        result=subRecCnt[SUBTASK9][i+1];
                        break;
                    }
                }
                char sigTimes[50];
                uart_printf_char_fml_api(true,"\r\n");
                if (result == 0)
                {
                    uart_printf_char_fml_api(true,"SUB9:");
                    itoa(subRecCnt[SUBTASK9][1],sigTimes,10);
                    uart_printf_char_fml_api(true,sigTimes);
                }
                else
                {
                    uart_printf_data_fml_api(&result,1,",SUBTASK9 error",1);
                    uart_printf_data_fml_api(&PubTimes[i],1,",PUB DATA",1);
                }
            }
        }
    }
}

#if 0
void pubsub_pub1_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t timecount1 = 0, timecount2 = 0, timecount3 = 0, timecount4 = 0, timecount5 = 0;
    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    EventBits_t uxBits=0;
    xNextWakeTime = xTaskGetTickCount();


    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));
    timecount1 = xTaskGetTickCount();
//    PUB_INT_FL("topic1", (senddata+1), FL_NONRECURSIVE);
//    PUB_INT_FL("topic2", (senddata+2), FL_NONRECURSIVE);
//    PUB_INT_FL("topic3", (senddata+3), FL_NONRECURSIVE);
//    PUB_INT_FL("topic4", (senddata+4), FL_NONRECURSIVE);
//    PUB_INT_FL("topic5", (senddata+5), FL_NONRECURSIVE);
//    PUB_INT_FL("topic6", (senddata+6), FL_NONRECURSIVE);
//    PUB_INT_FL("topic7", (senddata+7), FL_NONRECURSIVE);
//    PUB_INT_FL("topic8", (senddata+8), FL_NONRECURSIVE);
    timecount2 = xTaskGetTickCount();
    while(1)
    {
        timecount3 = xTaskGetTickCount();
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        uxBits = xEventGroupWaitBits(pubEventGroup,SUBTASK1,pdTRUE, pdTRUE,portMAX_DELAY);
        if((uxBits & SUBTASK1) == SUBTASK1)
        {
            PUB_INT_FL("topic1", (senddata+1), FL_NONRECURSIVE);
            PUB_INT_FL("topic2", (senddata+2), FL_NONRECURSIVE);
            PUB_INT_FL("topic3", (senddata+3), FL_NONRECURSIVE);
            PUB_INT_FL("topic4", (senddata+4), FL_NONRECURSIVE);
            PUB_INT_FL("topic5", (senddata+5), FL_NONRECURSIVE);
            PUB_INT_FL("topic6", (senddata+6), FL_NONRECURSIVE);
            PUB_INT_FL("topic7", (senddata+7), FL_NONRECURSIVE);
            PUB_INT_FL("topic8", (senddata+8), FL_NONRECURSIVE);
        }

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {
            timecount4 = xTaskGetTickCount();

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    uart_printf_char_fml_api(true,"OK");
                    runtimes++;
                    if(runtimes >= 20)
                    {
                        runtimes = 0;
                        PINS_DRV_TogglePins(LED_GPIO,1 << 23);
                    }
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB1 task rec ok\r\n",strlen("PUB1 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }

                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic1", (senddata+1), FL_NONRECURSIVE);
                PUB_INT_FL("topic2", (senddata+2), FL_NONRECURSIVE);
                PUB_INT_FL("topic3", (senddata+3), FL_NONRECURSIVE);
                PUB_INT_FL("topic4", (senddata+4), FL_NONRECURSIVE);
                PUB_INT_FL("topic5", (senddata+5), FL_NONRECURSIVE);
                PUB_INT_FL("topic6", (senddata+6), FL_NONRECURSIVE);
                PUB_INT_FL("topic7", (senddata+7), FL_NONRECURSIVE);
                PUB_INT_FL("topic8", (senddata+8), FL_NONRECURSIVE);

            }
        }
        timecount5 = xTaskGetTickCount();
    }
}

void pubsub_pub2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic9", (senddata+9), FL_NONRECURSIVE);
    PUB_INT_FL("topic10", (senddata+10), FL_NONRECURSIVE);
    PUB_INT_FL("topic11", (senddata+11), FL_NONRECURSIVE);
    PUB_INT_FL("topic12", (senddata+12), FL_NONRECURSIVE);
    PUB_INT_FL("topic13", (senddata+13), FL_NONRECURSIVE);
    PUB_INT_FL("topic14", (senddata+14), FL_NONRECURSIVE);
    PUB_INT_FL("topic15", (senddata+15), FL_NONRECURSIVE);
    PUB_INT_FL("topic16", (senddata+16), FL_NONRECURSIVE);

    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
    }
}
void pubsub_pub3_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic17", (senddata+17), FL_NONRECURSIVE);
    PUB_INT_FL("topic18", (senddata+18), FL_NONRECURSIVE);
    PUB_INT_FL("topic19", (senddata+19), FL_NONRECURSIVE);
    PUB_INT_FL("topic20", (senddata+20), FL_NONRECURSIVE);
    PUB_INT_FL("topic21", (senddata+21), FL_NONRECURSIVE);
    PUB_INT_FL("topic22", (senddata+22), FL_NONRECURSIVE);
    PUB_INT_FL("topic23", (senddata+23), FL_NONRECURSIVE);
    PUB_INT_FL("topic24", (senddata+24), FL_NONRECURSIVE);

    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {}
    }
}

void pubsub_pub4_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic25", (senddata+25), FL_NONRECURSIVE);
    PUB_INT_FL("topic26", (senddata+26), FL_NONRECURSIVE);
    PUB_INT_FL("topic27", (senddata+27), FL_NONRECURSIVE);
    PUB_INT_FL("topic28", (senddata+28), FL_NONRECURSIVE);
    PUB_INT_FL("topic29", (senddata+29), FL_NONRECURSIVE);
    PUB_INT_FL("topic30", (senddata+30), FL_NONRECURSIVE);
    PUB_INT_FL("topic31", (senddata+31), FL_NONRECURSIVE);
    PUB_INT_FL("topic32", (senddata+32), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB2 task rec ok\r\n",strlen("PUB2 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 1000000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic25", (senddata+25), FL_NONRECURSIVE);
                PUB_INT_FL("topic26", (senddata+26), FL_NONRECURSIVE);
                PUB_INT_FL("topic27", (senddata+27), FL_NONRECURSIVE);
                PUB_INT_FL("topic28", (senddata+28), FL_NONRECURSIVE);
                PUB_INT_FL("topic29", (senddata+29), FL_NONRECURSIVE);
                PUB_INT_FL("topic30", (senddata+30), FL_NONRECURSIVE);
                PUB_INT_FL("topic31", (senddata+31), FL_NONRECURSIVE);
                PUB_INT_FL("topic32", (senddata+32), FL_NONRECURSIVE);
            }
        }
    }
}

void pubsub_pub5_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));


    PUB_INT_FL("topic33", (senddata+33), FL_NONRECURSIVE);
    PUB_INT_FL("topic34", (senddata+34), FL_NONRECURSIVE);
    PUB_INT_FL("topic35", (senddata+35), FL_NONRECURSIVE);
    PUB_INT_FL("topic36", (senddata+36), FL_NONRECURSIVE);
    PUB_INT_FL("topic37", (senddata+37), FL_NONRECURSIVE);
    PUB_INT_FL("topic38", (senddata+38), FL_NONRECURSIVE);
    PUB_INT_FL("topic39", (senddata+39), FL_NONRECURSIVE);
    PUB_INT_FL("topic40", (senddata+40), FL_NONRECURSIVE);
//    PUB_INT_FL("topic41", (senddata+41), FL_NONRECURSIVE);
//    PUB_INT_FL("topic42", (senddata+42), FL_NONRECURSIVE);
//    PUB_INT_FL("topic43", (senddata+43), FL_NONRECURSIVE);
//    PUB_INT_FL("topic44", (senddata+44), FL_NONRECURSIVE);
//    PUB_INT_FL("topic45", (senddata+45), FL_NONRECURSIVE);
//    PUB_INT_FL("topic46", (senddata+46), FL_NONRECURSIVE);
//    PUB_INT_FL("topic47", (senddata+47), FL_NONRECURSIVE);
//    PUB_INT_FL("topic48", (senddata+48), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB3 task rec ok\r\n",strlen("PUB3 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);

                PUB_INT_FL("topic33", (senddata+33), FL_NONRECURSIVE);
                PUB_INT_FL("topic34", (senddata+34), FL_NONRECURSIVE);
                PUB_INT_FL("topic35", (senddata+35), FL_NONRECURSIVE);
                PUB_INT_FL("topic36", (senddata+36), FL_NONRECURSIVE);
                PUB_INT_FL("topic37", (senddata+37), FL_NONRECURSIVE);
                PUB_INT_FL("topic38", (senddata+38), FL_NONRECURSIVE);
                PUB_INT_FL("topic39", (senddata+39), FL_NONRECURSIVE);
                PUB_INT_FL("topic40", (senddata+40), FL_NONRECURSIVE);
//                PUB_INT_FL("topic41", (senddata+41), FL_NONRECURSIVE);
//                PUB_INT_FL("topic42", (senddata+42), FL_NONRECURSIVE);
//                PUB_INT_FL("topic43", (senddata+43), FL_NONRECURSIVE);
//                PUB_INT_FL("topic44", (senddata+44), FL_NONRECURSIVE);
//                PUB_INT_FL("topic45", (senddata+45), FL_NONRECURSIVE);
//                PUB_INT_FL("topic46", (senddata+46), FL_NONRECURSIVE);
//                PUB_INT_FL("topic47", (senddata+47), FL_NONRECURSIVE);
//                PUB_INT_FL("topic48", (senddata+48), FL_NONRECURSIVE);
            }
        }
    }
}

void pubsub_pub6_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));


//    PUB_INT_FL("topic33", (senddata+33), FL_NONRECURSIVE);
//    PUB_INT_FL("topic34", (senddata+34), FL_NONRECURSIVE);
//    PUB_INT_FL("topic35", (senddata+35), FL_NONRECURSIVE);
//    PUB_INT_FL("topic36", (senddata+36), FL_NONRECURSIVE);
//    PUB_INT_FL("topic37", (senddata+37), FL_NONRECURSIVE);
//    PUB_INT_FL("topic38", (senddata+38), FL_NONRECURSIVE);
//    PUB_INT_FL("topic39", (senddata+39), FL_NONRECURSIVE);
//    PUB_INT_FL("topic40", (senddata+40), FL_NONRECURSIVE);
    PUB_INT_FL("topic41", (senddata+41), FL_NONRECURSIVE);
    PUB_INT_FL("topic42", (senddata+42), FL_NONRECURSIVE);
    PUB_INT_FL("topic43", (senddata+43), FL_NONRECURSIVE);
    PUB_INT_FL("topic44", (senddata+44), FL_NONRECURSIVE);
    PUB_INT_FL("topic45", (senddata+45), FL_NONRECURSIVE);
    PUB_INT_FL("topic46", (senddata+46), FL_NONRECURSIVE);
    PUB_INT_FL("topic47", (senddata+47), FL_NONRECURSIVE);
    PUB_INT_FL("topic48", (senddata+48), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB3 task rec ok\r\n",strlen("PUB3 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);

//                PUB_INT_FL("topic33", (senddata+33), FL_NONRECURSIVE);
//                PUB_INT_FL("topic34", (senddata+34), FL_NONRECURSIVE);
//                PUB_INT_FL("topic35", (senddata+35), FL_NONRECURSIVE);
//                PUB_INT_FL("topic36", (senddata+36), FL_NONRECURSIVE);
//                PUB_INT_FL("topic37", (senddata+37), FL_NONRECURSIVE);
//                PUB_INT_FL("topic38", (senddata+38), FL_NONRECURSIVE);
//                PUB_INT_FL("topic39", (senddata+39), FL_NONRECURSIVE);
//                PUB_INT_FL("topic40", (senddata+40), FL_NONRECURSIVE);
                PUB_INT_FL("topic41", (senddata+41), FL_NONRECURSIVE);
                PUB_INT_FL("topic42", (senddata+42), FL_NONRECURSIVE);
                PUB_INT_FL("topic43", (senddata+43), FL_NONRECURSIVE);
                PUB_INT_FL("topic44", (senddata+44), FL_NONRECURSIVE);
                PUB_INT_FL("topic45", (senddata+45), FL_NONRECURSIVE);
                PUB_INT_FL("topic46", (senddata+46), FL_NONRECURSIVE);
                PUB_INT_FL("topic47", (senddata+47), FL_NONRECURSIVE);
                PUB_INT_FL("topic48", (senddata+48), FL_NONRECURSIVE);
            }
        }
    }
}



void pubsub_pub7_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t sendresult = 0;

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic49", (senddata+49), FL_NONRECURSIVE);
    PUB_INT_FL("topic50", (senddata+50), FL_NONRECURSIVE);
    PUB_INT_FL("topic51", (senddata+51), FL_NONRECURSIVE);
    PUB_INT_FL("topic52", (senddata+52), FL_NONRECURSIVE);
    PUB_INT_FL("topic53", (senddata+53), FL_NONRECURSIVE);
    PUB_INT_FL("topic54", (senddata+54), FL_NONRECURSIVE);
    PUB_INT_FL("topic55", (senddata+55), FL_NONRECURSIVE);
    PUB_INT_FL("topic56", (senddata+56), FL_NONRECURSIVE);
//    PUB_INT_FL("topic57", (senddata+57), FL_NONRECURSIVE);
//    PUB_INT_FL("topic58", (senddata+58), FL_NONRECURSIVE);
//    PUB_INT_FL("topic59", (senddata+59), FL_NONRECURSIVE);
//    PUB_INT_FL("topic60", (senddata+60), FL_NONRECURSIVE);
//    PUB_INT_FL("topic61", (senddata+61), FL_NONRECURSIVE);
//    PUB_INT_FL("topic62", (senddata+62), FL_NONRECURSIVE);
//    PUB_INT_FL("topic63", (senddata+63), FL_NONRECURSIVE);
//    PUB_INT_FL("topic64", (senddata+64), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    uart_printf_data_all(,,"OK");
//                    uart_printf_inter("OK", 1, " ");
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB4 task rec ok\r\n",strlen("PUB4 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic49", (senddata+49), FL_NONRECURSIVE);
                PUB_INT_FL("topic50", (senddata+50), FL_NONRECURSIVE);
                PUB_INT_FL("topic51", (senddata+51), FL_NONRECURSIVE);
                PUB_INT_FL("topic52", (senddata+52), FL_NONRECURSIVE);
                PUB_INT_FL("topic53", (senddata+53), FL_NONRECURSIVE);
                PUB_INT_FL("topic54", (senddata+54), FL_NONRECURSIVE);
                PUB_INT_FL("topic55", (senddata+55), FL_NONRECURSIVE);
                PUB_INT_FL("topic56", (senddata+56), FL_NONRECURSIVE);
//                PUB_INT_FL("topic57", (senddata+57), FL_NONRECURSIVE);
//                PUB_INT_FL("topic58", (senddata+58), FL_NONRECURSIVE);
//                PUB_INT_FL("topic59", (senddata+59), FL_NONRECURSIVE);
//                PUB_INT_FL("topic60", (senddata+60), FL_NONRECURSIVE);
//                PUB_INT_FL("topic61", (senddata+61), FL_NONRECURSIVE);
//                PUB_INT_FL("topic62", (senddata+62), FL_NONRECURSIVE);
//                PUB_INT_FL("topic63", (senddata+63), FL_NONRECURSIVE);
//                PUB_INT_FL("topic64", (senddata+64), FL_NONRECURSIVE);
            }
        }
    }
}


void pubsub_pub8_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t sendresult = 0;

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic57", (senddata+57), FL_NONRECURSIVE);
    PUB_INT_FL("topic58", (senddata+58), FL_NONRECURSIVE);
    PUB_INT_FL("topic59", (senddata+59), FL_NONRECURSIVE);
    PUB_INT_FL("topic60", (senddata+60), FL_NONRECURSIVE);
    PUB_INT_FL("topic61", (senddata+61), FL_NONRECURSIVE);
    PUB_INT_FL("topic62", (senddata+62), FL_NONRECURSIVE);
    PUB_INT_FL("topic63", (senddata+63), FL_NONRECURSIVE);
    PUB_INT_FL("topic64", (senddata+64), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    uart_printf_data_all(,,"OK");
//                    uart_printf_inter("OK", 1, " ");
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB4 task rec ok\r\n",strlen("PUB4 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic57", (senddata+57), FL_NONRECURSIVE);
                PUB_INT_FL("topic58", (senddata+58), FL_NONRECURSIVE);
                PUB_INT_FL("topic59", (senddata+59), FL_NONRECURSIVE);
                PUB_INT_FL("topic60", (senddata+60), FL_NONRECURSIVE);
                PUB_INT_FL("topic61", (senddata+61), FL_NONRECURSIVE);
                PUB_INT_FL("topic62", (senddata+62), FL_NONRECURSIVE);
                PUB_INT_FL("topic63", (senddata+63), FL_NONRECURSIVE);
                PUB_INT_FL("topic64", (senddata+64), FL_NONRECURSIVE);
            }
        }
    }
}


void pubsub_pub9_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t sendresult = 0;

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic65", (senddata+65), FL_NONRECURSIVE);
    PUB_INT_FL("topic66", (senddata+66), FL_NONRECURSIVE);
    PUB_INT_FL("topic67", (senddata+67), FL_NONRECURSIVE);
    PUB_INT_FL("topic68", (senddata+68), FL_NONRECURSIVE);
    PUB_INT_FL("topic69", (senddata+69), FL_NONRECURSIVE);
    PUB_INT_FL("topic70", (senddata+70), FL_NONRECURSIVE);
    PUB_INT_FL("topic71", (senddata+71), FL_NONRECURSIVE);
    PUB_INT_FL("topic72", (senddata+72), FL_NONRECURSIVE);
    PUB_INT_FL("topic73", (senddata+73), FL_NONRECURSIVE);
    PUB_INT_FL("topic74", (senddata+74), FL_NONRECURSIVE);
    PUB_INT_FL("topic75", (senddata+75), FL_NONRECURSIVE);
    PUB_INT_FL("topic76", (senddata+76), FL_NONRECURSIVE);
    PUB_INT_FL("topic77", (senddata+77), FL_NONRECURSIVE);
    PUB_INT_FL("topic78", (senddata+78), FL_NONRECURSIVE);
    PUB_INT_FL("topic79", (senddata+79), FL_NONRECURSIVE);
    PUB_INT_FL("topic80", (senddata+80), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    uart_printf_data_all(,,"OK");
//                    uart_printf_inter("OK", 1, " ");
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB4 task rec ok\r\n",strlen("PUB4 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic65", (senddata+65), FL_NONRECURSIVE);
                PUB_INT_FL("topic66", (senddata+66), FL_NONRECURSIVE);
                PUB_INT_FL("topic67", (senddata+67), FL_NONRECURSIVE);
                PUB_INT_FL("topic68", (senddata+68), FL_NONRECURSIVE);
                PUB_INT_FL("topic69", (senddata+69), FL_NONRECURSIVE);
                PUB_INT_FL("topic70", (senddata+70), FL_NONRECURSIVE);
                PUB_INT_FL("topic71", (senddata+71), FL_NONRECURSIVE);
                PUB_INT_FL("topic72", (senddata+72), FL_NONRECURSIVE);
                PUB_INT_FL("topic73", (senddata+73), FL_NONRECURSIVE);
                PUB_INT_FL("topic74", (senddata+74), FL_NONRECURSIVE);
                PUB_INT_FL("topic75", (senddata+75), FL_NONRECURSIVE);
                PUB_INT_FL("topic76", (senddata+76), FL_NONRECURSIVE);
                PUB_INT_FL("topic77", (senddata+77), FL_NONRECURSIVE);
                PUB_INT_FL("topic78", (senddata+78), FL_NONRECURSIVE);
                PUB_INT_FL("topic79", (senddata+79), FL_NONRECURSIVE);
                PUB_INT_FL("topic80", (senddata+80), FL_NONRECURSIVE);
            }
        }
    }
}


void pubsub_pub10_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;

    uint8_t senddata =0, i=0;
    volatile uint8_t msgCount=0;
    uint8_t value[15]={0};
    ps_msg_t *msg = NULL;
    static uint32_t runtimes = 0;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t sendresult = 0;

    ps_subscriber_t *su = ps_new_subscriber(SUBNUM, STRLIST("re_topic_group1_from_subtask1","re_topic_group1_from_subtask2",
            "re_topic_group1_from_subtask3","re_topic_group1_from_subtask4",
            "re_topic_group1_from_subtask5","re_topic_group1_from_subtask6",
            "re_topic_group1_from_subtask7","re_topic_group1_from_subtask8",
            "re_topic_group1_from_subtask9","re_topic_group1_from_subtask10",
            "re_topic_group1_from_subtask11","re_topic_group1_from_subtask12",
            "re_topic_group1_from_subtask13","re_topic_group1_from_subtask14",
            "re_topic_group1_from_subtask15"));

    PUB_INT_FL("topic81", (senddata+81), FL_NONRECURSIVE);
    PUB_INT_FL("topic82", (senddata+82), FL_NONRECURSIVE);
    PUB_INT_FL("topic83", (senddata+83), FL_NONRECURSIVE);
    PUB_INT_FL("topic84", (senddata+84), FL_NONRECURSIVE);
    PUB_INT_FL("topic85", (senddata+85), FL_NONRECURSIVE);
    PUB_INT_FL("topic86", (senddata+86), FL_NONRECURSIVE);
    PUB_INT_FL("topic87", (senddata+87), FL_NONRECURSIVE);
    PUB_INT_FL("topic88", (senddata+88), FL_NONRECURSIVE);
    PUB_INT_FL("topic89", (senddata+89), FL_NONRECURSIVE);
    PUB_INT_FL("topic90", (senddata+90), FL_NONRECURSIVE);
    PUB_INT_FL("topic91", (senddata+91), FL_NONRECURSIVE);
    PUB_INT_FL("topic92", (senddata+92), FL_NONRECURSIVE);
    PUB_INT_FL("topic93", (senddata+93), FL_NONRECURSIVE);
    PUB_INT_FL("topic94", (senddata+94), FL_NONRECURSIVE);
    PUB_INT_FL("topic95", (senddata+95), FL_NONRECURSIVE);
    PUB_INT_FL("topic96", (senddata+96), FL_NONRECURSIVE);
    PUB_INT_FL("topic97", (senddata+97), FL_NONRECURSIVE);
    PUB_INT_FL("topic98", (senddata+98), FL_NONRECURSIVE);
    PUB_INT_FL("topic99", (senddata+99), FL_NONRECURSIVE);
    PUB_INT_FL("topic100", (senddata+100), FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));

        msgCount = ps_waiting(su);

        if (msgCount == SUBNUM)
        {

//            if(reMsgCount != 0)
            {
                for(uint8_t i =0 ; i< SUBNUM ; i++)
                {
                    msg = ps_get(su,-1);
                    if (msg != NULL)
                    {
                        if(IS_INT(msg))
                        {
                            value[i] =  (uint8_t)msg->int_val;
                        }
                        ps_unref_msg(msg);
                    }
                }
                bubbleSort(value,SUBNUM);
                for( i = 0; i < SUBNUM; i++)
                {
                    if (value[i] != RECERROR)
                        continue;
                    else
                        break;
                }
                if (i >= SUBNUM)
                {
//                    uart_printf_data_all(,,"OK");
//                    uart_printf_inter("OK", 1, " ");
//                    vTaskSuspendAll();
#if SUCESSINFOPRINT
                    send_string_UART1("PUB4 task rec ok\r\n",strlen("PUB4 task rec ok\r\n"));
#endif
//                    xTaskResumeAll();
                }
                else
                {
//                    vTaskSuspendAll();
#if ERRINFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < SUBNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
//                    uart_printf_data_all(&msg->int_val,1,",main.evt");
                    while(1)
                    {
                        runtimes = 0;
                        while(1)
                        {
                            runtimes++;
                            if(runtimes >= 500000)
                            {
                                runtimes = 0;
                                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                            }
                        }
                    }
                }
                msgCount=0;
                memset(value,0,SUBNUM);
                PUB_INT_FL("topic81", (senddata+81), FL_NONRECURSIVE);
                PUB_INT_FL("topic82", (senddata+82), FL_NONRECURSIVE);
                PUB_INT_FL("topic83", (senddata+83), FL_NONRECURSIVE);
                PUB_INT_FL("topic84", (senddata+84), FL_NONRECURSIVE);
                PUB_INT_FL("topic85", (senddata+85), FL_NONRECURSIVE);
                PUB_INT_FL("topic86", (senddata+86), FL_NONRECURSIVE);
                PUB_INT_FL("topic87", (senddata+87), FL_NONRECURSIVE);
                PUB_INT_FL("topic88", (senddata+88), FL_NONRECURSIVE);
                PUB_INT_FL("topic89", (senddata+89), FL_NONRECURSIVE);
                PUB_INT_FL("topic90", (senddata+90), FL_NONRECURSIVE);
                PUB_INT_FL("topic91", (senddata+91), FL_NONRECURSIVE);
                PUB_INT_FL("topic92", (senddata+92), FL_NONRECURSIVE);
                PUB_INT_FL("topic93", (senddata+93), FL_NONRECURSIVE);
                PUB_INT_FL("topic94", (senddata+94), FL_NONRECURSIVE);
                PUB_INT_FL("topic95", (senddata+95), FL_NONRECURSIVE);
                PUB_INT_FL("topic96", (senddata+96), FL_NONRECURSIVE);
                PUB_INT_FL("topic97", (senddata+97), FL_NONRECURSIVE);
                PUB_INT_FL("topic98", (senddata+98), FL_NONRECURSIVE);
                PUB_INT_FL("topic99", (senddata+99), FL_NONRECURSIVE);
                PUB_INT_FL("topic100", (senddata+100), FL_NONRECURSIVE);
            }
        }
    }
}


void pubsub_sub1_Task( void *pvParameters )
{
    uint32_t timecount = 0;
    char timestring[32];
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    uint8_t timecount1 = 0, timecount2 = 0, timecount3 = 0, timecount4 = 0, timecount5 = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        timecount3 = xTaskGetTickCount();
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB1\r\n",strlen("SUB1\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            timecount4 = xTaskGetTickCount();
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
//                    vTaskSuspendAll();
#if INFOPRINT
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }

            }
//            ps_flush(su);
            memset(value,0,GROUPNUM);
            msg_count = 0;

//            timecount = FTM_DRV_CounterRead(INST_FLEXTIMER_MC1);
//            itoa(timecount,timestring,10);
//            vTaskSuspendAll();
//            send_string_UART1("SUB1:",strlen("SUB1:"));
//            send_string_UART1(timestring,strlen(timestring));
//            xTaskResumeAll();

            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask1", (SUBTASK1), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask1", (RECERROR), FL_NONRECURSIVE);

        }
        timecount5 = xTaskGetTickCount();
        msg_count = 0;
    }
}

void pubsub_sub2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB2\r\n",strlen("SUB2\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }

            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask2", (SUBTASK2), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask2", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub3_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        queuespace = ps_get_space(su);
//        send_string_UART1("SUB3\r\n",strlen("SUB3\r\n"));
        msg_count = ps_waiting(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask3", (SUBTASK3), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask3", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub4_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB4\r\n",strlen("SUB4\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask4", (SUBTASK4), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask4", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub5_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB5\r\n",strlen("SUB5\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask5", (SUBTASK5), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask5", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub6_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB6\r\n",strlen("SUB6\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask6", (SUBTASK6), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask6", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub7_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB7\r\n",strlen("SUB7\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask7", (SUBTASK7), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask7", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub8_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        queuespace = ps_get_space(su);
//        send_string_UART1("SUB8\r\n",strlen("SUB8\r\n"));
        msg_count = ps_waiting(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask8", (SUBTASK8), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask8", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub9_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB9\r\n",strlen("SUB9\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask9", (SUBTASK9), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask9", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub10_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                          "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB10\r\n",strlen("SUB10\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask10", (SUBTASK10), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask10", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub11_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB11\r\n",strlen("SUB11\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask11", (SUBTASK11), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask11", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub12_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB12\r\n",strlen("SUB12\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask12", (SUBTASK12), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask12", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub13_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB13\r\n",strlen("SUB13\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask13", (SUBTASK13), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask13", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub14_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB14\r\n",strlen("SUB14\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            msg_count = 0;
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask14", (SUBTASK14), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask14", (RECERROR), FL_NONRECURSIVE);

        }
    }
}

void pubsub_sub15_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg_count = 0,head = 0x5A,tail = 0xA5;
    uint8_t value[GROUPNUM] = {0};
    uint8_t i,queuespace = 0;
    static uint32_t runtimes = 0;
    ps_subscriber_t *su = ps_new_subscriber(QUEUESIZE, STRLIST("topic1","topic2","topic3","topic4",
                                                         "topic5","topic6","topic7","topic8",
                                                         "topic9","topic10","topic11","topic12",
                                                         "topic13","topic14","topic15","topic16",
                                                         "topic17","topic18","topic19","topic20",
                                                         "topic21","topic22","topic23","topic24",
                                                         "topic25","topic26","topic27","topic28",
                                                         "topic29","topic30","topic31","topic32",
                                                         "topic33","topic34","topic35","topic36",
                                                         "topic37","topic38","topic39","topic40",
                                                         "topic41","topic42","topic43","topic44",
                                                         "topic45","topic46","topic47","topic48",
                                                         "topic49","topic50","topic51","topic52",
                                                         "topic53","topic54","topic55","topic56",
                                                         "topic57","topic58","topic59","topic60",
                                                         "topic61","topic62","topic63","topic64",
                                                         "topic65","topic66","topic67","topic68",
                                                         "topic69","topic70","topic71","topic72",
                                                         "topic73","topic74","topic75","topic76",
                                                         "topic77","topic78","topic79","topic80",
                                                         "topic81","topic82","topic83","topic84",
                                                         "topic85","topic86","topic87","topic88",
                                                         "topic89","topic90","topic91","topic92",
                                                         "topic93","topic94","topic95","topic96",
                                                         "topic97","topic98","topic99","topic100"
                                                         ));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
//        send_string_UART1("SUB15\r\n",strlen("SUB15\r\n"));
        msg_count = ps_waiting(su);
        queuespace = ps_get_space(su);
        if (msg_count >= GROUPNUM)
        {
            for(uint8_t i =0 ; i< msg_count ; i++)
            {
                msg = ps_get(su,-1);
                if (msg != NULL)
                {
                    if(IS_INT(msg))
                    {
                        value[i] = (uint8_t)msg->int_val ;
                    }
                    ps_unref_msg(msg);
                }
            }

            bubbleSort(value,GROUPNUM);
            msg_count = 0;
            for( i = 0; i < GROUPNUM; i++ )
            {
                if(value[i] == (i+1))
                    continue;
                else
                {
#if ERRINFOPRINT
//                    vTaskSuspendAll();
                    send_string_UART1("error\r\n",strlen("error\r\n"));

                    for(i = 0; i < GROUPNUM; i++)
                    {
                        uart_printf_inter(&value[i], 1, " ");
                    }
#endif
//                    xTaskResumeAll();
                    runtimes = 0;
                    while(1)
                    {
                        runtimes++;
                        if(runtimes >= 500000)
                        {
                            runtimes = 0;
                            PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
                        }
                    }
                }
            }
//            ps_flush(su);
//            while(1)
//                ;
            memset(value,0,GROUPNUM);
            if(i == GROUPNUM)
                PUB_INT_FL("re_topic_group1_from_subtask15", (SUBTASK15), FL_NONRECURSIVE);
            else
                PUB_INT_FL("re_topic_group1_from_subtask15", (RECERROR), FL_NONRECURSIVE);

        }
    }
}
#endif
#endif



#if ONE_TO_MUTI



void pubsub_pub_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    TickType_t last;
    xNextWakeTime = xTaskGetTickCount();
    volatile uint8_t count=0;
    uint8_t head=0x5A,tail=0xA5;

//    ps_subscriber_t *sub = ps_new_subscriber(10, STRLIST("thread.ready"));
    ps_subscriber_t *su1 = ps_new_subscriber(20, STRLIST("Muti_SUB"));

    ps_msg_t *msg = NULL;
//    uart_printf_char_fml_api(true,"pubsub_pub_Task");
    uint8_t value[15];
    static uint8_t senddata =1;


    PUB_INT_FL("SINGLE_PUB", senddata, FL_NONRECURSIVE);
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        count = ps_waiting(su1);
        if(count == 15)
        {
            for(uint8_t i=0; i<count; i++)
            {
                msg = ps_get(su1, -1);
                if (msg != NULL)
                {
                    if (IS_INT(msg))
                    {
                        value[i] =msg->int_val;
                    }
                }
                ps_unref_msg(msg);
            }
            vTaskSuspendAll();
            send_byte_UART1(&head);
            send_byte_UART1(&head);
            for(uint8_t i=0; i<count; i++)
            {
                send_byte_UART1(&value[i]);
            }
            send_byte_UART1(&tail);
            send_byte_UART1(&tail);
            memset(value,0,15);
            count = 0;
            xTaskResumeAll();
            PUB_INT_FL("SINGLE_PUB", senddata, FL_NONRECURSIVE);
            last = xTaskGetTickCount();
        }
    }

}

void pubsub_sub_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t count=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("main.evt", "main.stopping"));
    ps_subscriber_t *s1 = ps_new_subscriber(10, STRLIST("foo.bar"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (1000/portTICK_RATE_MS));
        uart_printf_char_fml_api(true,"pubsub_sub_Task");
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                uart_printf_char_fml_api(true,"main.evt rec int");
                uart_printf_data_all(&msg->int_val,1,",main.evt");
            }
            if(IS_BOOL(msg))
            {
                uart_printf_char_fml_api(true,"main.evt rec bool");
                uart_printf_data_all(&msg->bool_val,1,",main.evt");
            }
        }
        ps_unref_msg(msg);
    }
}

void pubsub_sub1_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+1), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+2), FL_NONRECURSIVE);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub3_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+3), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub4_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+4), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub5_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+5), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub6_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+6), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub7_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+7), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub8_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+8), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub9_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+9), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error  free subcriber
}

void pubsub_sub10_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+10), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub11_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+11), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub12_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+12), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub13_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+13), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub14_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+14), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}

void pubsub_sub15_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    uint8_t value=0;
    xNextWakeTime = xTaskGetTickCount();
    ps_subscriber_t *s = ps_new_subscriber(10, STRLIST("SINGLE_PUB"));
    ps_msg_t *msg = NULL;
    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (SUBTASK_TIME/portTICK_RATE_MS));
        msg = ps_get(s, -1);
        if (msg != NULL)
        {
            if (IS_INT(msg))
            {
                value = msg->int_val;
            }
        }
        ps_unref_msg(msg);
        PUB_INT_FL("Muti_SUB", (value+15), FL_STICKY);
    }
    ps_free_subscriber(s);  //run error free subcriber
}
#endif


