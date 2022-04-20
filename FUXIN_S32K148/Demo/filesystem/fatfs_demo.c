/*
 * fatfs_demo.c
 *
 *  Created on: 2021Äê5ÔÂ19ÈÕ
 *      Author: Administrator
 */

#include "Cpu.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "string.h"
/*fatfs*/
#include "fatfs_demo.h"
#include "ff.h"

#include "Flash1.h"
#include "log_fml.h"
#include "pubsub.h"
extern flash_ssd_config_t flashSSDConfig;


#define FATFS_TASK_PRIORITY        ( tskIDLE_PRIORITY + 4 )
#define TASK_STACK_SIZE                 ( ( unsigned short ) 1000 )
#define FATFS_TIME (1000)

TaskHandle_t fatfsTask_Handle;

void fatfs_test1_Task( void *pvParameters );
void fatfs_test2_Task( void *pvParameters );

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

//
//int fatfs_test(void)
//{
//    uint8_t flashdata[8] = {1,2,3,4,5,6,7,8};
//    uint32_t testflashaddress = 0x10000000;
//    uint8_t flashreadbuffer[10] = {0};
//    status_t ret;
//    char buf[128];
//    FATFS fatfs;
//    FRESULT res;
//    FIL f;
//    unsigned int flen;
//    BYTE work[FF_MAX_SS];
//    for(uint8_t i = 0; i < 10; i++)
//    {
//        flashreadbuffer[i] = (*(__IO uint8_t*)(testflashaddress+i));
//    }
//
//    res = f_open(&f, "test.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
//    if (res != FR_OK)
//    {
//        while(1);
//    }
//
//    if(flashreadbuffer[0] != 0x01)
//    {
//        f_lseek(&f, 0);
//        res = f_write(&f, "hello test12345", sizeof("hello test12345"), &flen);
//        send_string_UART1("write",strlen("write"));
//        if (res != FR_OK)
//        {
//            while(1);
//        }
//        else
//        {
//            ret = FLASH_DRV_EraseSector(&flashSSDConfig, testflashaddress, 4096);
//            ret = FLASH_DRV_VerifySection(&flashSSDConfig, testflashaddress, 4096/FTFx_DPHRASE_SIZE,1u);
//            ret = FLASH_DRV_Program(&flashSSDConfig, testflashaddress, 8, flashdata);
//        }
//    }
//    memset(buf,0,128);
//    UINT rd;
//    f_lseek(&f, 0);
//    res = f_read(&f, buf, sizeof("hello test12345"), &rd);
//    if(res != FR_OK)
//    {
//        while(1);
//    }
//    if(strcmp(buf,"hello test12345"))
//    {
//        while(1);
//    }
//    res = f_close(&f);
//    if(res != FR_OK)
//    {
//        while(1);
//    }
////    res = f_mount(&fatfs,"0:" , 0);
//}
extern SemaphoreHandle_t  fatfsInitQueue;
void fatfsTest_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    BaseType_t xResult;
    struct stTask_log taskLog2;
    memset(&taskLog2,0,sizeof(taskLog2));

    taskLog2.logTime.year = 2021;
    taskLog2.logTime.month = 6;
    taskLog2.logTime.day = 31;
    taskLog2.logTime.hour = 14;
    taskLog2.logTime.minutes = 46;
    taskLog2.logTime.seconds = 10;
    taskLog2.logEvent = LOGInfo;
    strcpy(taskLog2.inifo,"info log\r\n");
    strcpy(taskLog2.functionName,__FUNCTION__);
//    fatfs_test();
//    xTaskCreate( fatfs_test1_Task, "fatfs_test1", TASK_STACK_SIZE, NULL,FATFS_TASK_PRIORITY , NULL );
//    xTaskCreate( fatfs_test2_Task, "fatfs_test2", TASK_STACK_SIZE, NULL,FATFS_TASK_PRIORITY , NULL );

    while(1)
    {
        vTaskDelayUntil(&xNextWakeTime, (FATFS_TIME/portTICK_RATE_MS));
//        PUB_PTR_FL("logRecordTopic",&taskLog2,FL_STICKY);
//        uart_printf_char_fml_api(true,"log");
        xResult = xSemaphoreTake(fatfsInitQueue, (TickType_t)0);
        if(xResult == pdTRUE)
        {
            fatfs_init_fml_api();
//            uart_printf_char_fml_api(true,"fatfs init done");
//            vTaskDelete(fatfsTask_Handle);
//            break;
        }
    }
//    vTaskDelete(fatfsTask_Handle);

}

void fatfs_test1_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    FATFS fatfs;
    FRESULT res;
    char buf[128];
    uint8_t i,writebuf[255] = {0};
    uint8_t flashdata[8] = {1,2,3,4,5,6,7,8};
    uint32_t testflashaddress = 0x10000000;
    uint8_t flashreadbuffer[10] = {0};
    FIL f;
    FATFS * fs;
    status_t ret;
    DWORD fre_clust,fre_sect,tot_sect;
    unsigned int flen,filesize = 0;
    xNextWakeTime = xTaskGetTickCount();
    while(1)
    {
        for( i =0 ; i < 255; i++)
        {
            writebuf[i] = i+1;
        }
        res = f_getfree("0:", &fre_clust, &fs);
        /* Get total sectors and free sectors */
        tot_sect = (fs->n_fatent - 2) * fs->csize;
        fre_sect = fre_clust * fs->csize;

        vTaskDelayUntil(&xNextWakeTime, (FATFS_TIME/portTICK_RATE_MS));

        res = f_open(&f, "test1.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
        if (res != FR_OK)
        {
            send_string_UART1("open1",sizeof("open1"));
            while(1);
        }
//        if(flashreadbuffer[0] != 0x01)
        {
            f_lseek(&f, 0);
            res = f_write(&f, &writebuf, sizeof(writebuf), &flen);
            memset(writebuf,0,sizeof(writebuf));
            if (res != FR_OK)
            {
                send_string_UART1("write1",sizeof("write1"));
                while(1);
            }
//            else
//            {
//                ret = FLASH_DRV_EraseSector(&flashSSDConfig, testflashaddress, 4096);
//                ret = FLASH_DRV_VerifySection(&flashSSDConfig, testflashaddress, 4096/FTFx_DPHRASE_SIZE,1u);
//                ret = FLASH_DRV_Program(&flashSSDConfig, testflashaddress, 8, flashdata);
//            }
        }
        memset(buf,0,128);
        UINT rd;
        f_lseek(&f, 0);
        res = f_read(&f, writebuf, sizeof(writebuf), &rd);
        if(res != FR_OK)
        {
            send_string_UART1("read1",sizeof("read1"));
            while(1);
        }
        else
        {
            for( i =0 ; i < 255; i++)
            {
                if(writebuf[i] != i+1)
                    break;
            }
        }
        if ( i < 255)
        {
            send_string_UART1("error1",sizeof("error1"));
        }
        filesize = f_size(&f);
        res = f_close(&f);
        if(res != FR_OK)
        {
            send_string_UART1("close1",sizeof("close1"));
            while(1);
        }
        send_string_UART1("test1",sizeof("test1"));
        res = f_getfree("0:", &fre_clust, &fs);
        /* Get total sectors and free sectors */
        tot_sect = (fs->n_fatent - 2) * fs->csize;
        fre_sect = fre_clust * fs->csize;
//        fatfs_test();
    }
}

void fatfs_test2_Task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    FATFS fatfs;
    FRESULT res;
    char buf[128];
    uint8_t i,writebuf[256] = {0};
    uint8_t flashdata[8] = {1,2,3,4,5,6,7,8};
    uint32_t testflashaddress = 0x10000000;
    uint8_t flashreadbuffer[10] = {0};
    FIL f;
    FATFS * fs;
    status_t ret;
    DWORD fre_clust,fre_sect,tot_sect;
    unsigned int flen,filesize = 0;
    xNextWakeTime = xTaskGetTickCount();
    while(1)
    {
        for( i =0 ; i < 255; i++)
        {
            writebuf[i] = 255-i;
        }

        vTaskDelayUntil(&xNextWakeTime, (FATFS_TIME/portTICK_RATE_MS));

        res = f_open(&f, "test2.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
        if (res != FR_OK)
        {
            send_string_UART1("open2",sizeof("open2"));
            while(1);
        }
//        if(flashreadbuffer[0] != 0x01)
        {
            f_lseek(&f, 0);
            res = f_write(&f, &writebuf, sizeof(writebuf), &flen);
//            send_string_UART1("write",strlen("write"));
            memset(writebuf,0,sizeof(writebuf));
            if (res != FR_OK)
            {
                send_string_UART1("write2",sizeof("write2"));
                while(1);
            }
//            else
//            {
//                ret = FLASH_DRV_EraseSector(&flashSSDConfig, testflashaddress, 4096);
//                ret = FLASH_DRV_VerifySection(&flashSSDConfig, testflashaddress, 4096/FTFx_DPHRASE_SIZE,1u);
//                ret = FLASH_DRV_Program(&flashSSDConfig, testflashaddress, 8, flashdata);
//            }
        }
        UINT rd;
        f_lseek(&f, 0);
        res = f_read(&f, writebuf, sizeof(writebuf), &rd);
        if(res != FR_OK)
        {
            send_string_UART1("read2",sizeof("read2"));
            while(1);
        }
        else
        {
            for( i =0 ; i < 255; i++)
            {
                if(writebuf[i] != 255-i)
                    break;
            }
        }
        if ( i < 255)
        {
            send_string_UART1("error2",sizeof("error2"));
        }
        filesize = f_size(&f);
        res = f_close(&f);
        if(res != FR_OK)
        {
            send_string_UART1("close2",sizeof("close2"));
            while(1);
        }
        send_string_UART1("test2",sizeof("test2"));
    }
}
