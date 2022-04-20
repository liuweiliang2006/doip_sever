/*
 * fml_uart.c
 *
 *  Created on: 2021Äê5ÔÂ25ÈÕ
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
#include "Driver_interface.h"
#include "ff.h"
#include "pubsub.h"
#include "pwr_manage_test.h"

#define UPLOADTIMECYCLE (10000)  //10s
QueueHandle_t uartLogQueue = NULL;
QueueHandle_t taskLogQueue = NULL;
SemaphoreHandle_t  configQueue = NULL;
SemaphoreHandle_t  fatfsInitQueue = NULL;
#define logFileMaxCnt (10)
#define fileNameMaxLen (30)
#define singleFileMaxSize (4*1024)
//#define SAVE_FAULT_START_ADD (0x10061000)
#define SAVE_FAULT_START_ADD (0x1001E000)  //MCU fault
#define SAVE_GET_SET_AVAILABLE_ADD (0x1001F000) //CMD get/set
#define LOG_DEBUG_PRINT 0

struct stUploadTime upLoadTime;
struct uartSocReadBuffType uartSocReadBuff = {
        .readBuffFlag = readBufferEnable,
        .readBuff = {0},
        .usefullDataCnt = 0
};

extern void setup_hardware( void );
extern uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free);

struct stFaultType HardFaultMsg;

//void HardFault_Handler(void)
//{
//    register uint32_t paralr,parasp;
//    __asm volatile ("mov %0, lr\n" : "=r" (paralr) );
//    __asm volatile ("mov %0, sp\n" : "=r" (parasp) );
////    __asm volatile ("mov r0,lr" );
////    MOV     r0, lr                  /* get lr */
////    MOV     r1, sp                  /* get stack pointer (current is MSP) */
//    cm_backtrace_fault(paralr, parasp);
//    while(1)
//        ;
//}
char print_msg[32]={" "};

void uart_log_printf_fml(const char *format, ...)
{
    char msg[32] = {0};
    va_list args;

    if (uartLogQueue != NULL) {
        memcpy((uint8_t *)&msg[0], format, 32);
        strncat(msg, "\r\n",2);
        xQueueSendToBack(uartLogQueue, &msg, 0);
    }
}

void uart_log_printf_isr_fml(const char *format, ...)
{
    char msg[32] = {0};
    va_list args;

    if (uartLogQueue != NULL) {
        memcpy((uint8_t *)&msg[0], format, 32);
        strncat(msg, "\r\n",2);
        xQueueSendToBackFromISR(uartLogQueue, &msg, 0);
    }
}
struct stTask_log taskLogG;
void uart_printf_char_fml_api(uint8_t source,const char *function,const char *format)
{

    memset(&taskLogG,0,sizeof(taskLogG));

    taskLogG.logTime.year = 2021;
    taskLogG.logTime.month = 6;
    taskLogG.logTime.day = 31;
    taskLogG.logTime.hour = 14;
    taskLogG.logTime.minutes = 46;
    taskLogG.logTime.seconds = 10;
    taskLogG.logEvent = LOGInfo;
    strcpy(taskLogG.inifo,format);
    strncat(taskLogG.inifo, "\r\n",2);
    strcpy(taskLogG.functionName,function);
    if(source == true)
    {
    	xQueueSendToBack(taskLogQueue, &taskLogG, 0);
    }
    else
    {
    	xQueueSendToBackFromISR(taskLogQueue, &taskLogG, 0);
    }
}
/*void uart_printf_char_fml_api(uint8_t source,char *format)
{
    if(source == true )
    {
    	uart_log_printf_fml(format);
    }
    else
    {
        uart_log_printf_isr_fml(format);
    }
}*/

void uart_printf_data_fml_api(uint8_t source,uint8_t *data,uint8_t len,const char *function,char *format)
{
    uint8_t temp_char[10][2];
    int i;
    memcpy((uint8_t *)&print_msg[len*2], format, 32);
    for(i=0;i<len;i++)
    {
        put_hex_fml( data[i] ,temp_char[i]);
        print_msg[0+i*2]= temp_char[i][0];
        print_msg[1+i*2]= temp_char[i][1];
    }
    uart_printf_char_fml_api(source,function,&print_msg[0]);
}

void uartSocSendData(uint8_t *sendData,uint16_t len) {
    uint32_t bytesRemaining;
        /* Send data via LPUART */

        lpuart_send_data__hal_api(INST_UARTSOC,(uint8_t *) sendData, len);
        /* Wait for transmission to be successful */
        while (lpuart_get_transmit_status__hal_api(INST_UARTSOC, &bytesRemaining)
            != STATUS_SUCCESS)
        {
        }
}

void put_hex_fml( uint8_t hex_data ,uint8_t *p)
{
    uint8_t temp;
    temp = (uint8_t)( ( hex_data & 0xf0 ) >> 4 );
    if(temp<10) temp+=48;
    else temp += 55;
    p[0] = temp;
    temp = (uint8_t)( hex_data & 0x0f );
    if(temp<10) temp+=48;
    else temp += 55;
    p[1] = temp;
}

struct stSHELL shellCmdData;
uint8_t uartshellvalue;
void shell_uart_recCallback(void *driverState, uart_event_t event, void *userData)
{
    /* Unused parameters */
    (void)driverState;
    (void)userData;
    uint64_t current_time = 0 ;
    /* Check the event type */
    if (event == UART_EVENT_RX_FULL)
    {
        if(shellCmdData.rCnt == 0)
        {
            memset(shellCmdData.recbuf,0,CMD_BUFF_LEN);
            shellCmdData.uartWork = shelluartWorking;
        }
        shellCmdData.recTimeCnt = 0;
        shellCmdData.recbuf[shellCmdData.rCnt] = uartshellvalue;
        shellCmdData.rCnt++;
        LPUART_DRV_SetRxBuffer(INST_LPUART1,&uartshellvalue,1U);
    }
    else
    {
        LPUART_DRV_AbortReceivingData(INST_LPUART1);
        LPUART_DRV_ReceiveData(INST_LPUART1,&uartshellvalue,1U);
    }
}

uint8_t uartsocvalue;
void uart_soc_recCallback(void *driverState, uart_event_t event, void *userData)
{
//    static uint8_t rCnt = 0;
    /* Unused parameters */
    (void)driverState;
    (void)userData;

    if (event == UART_EVENT_RX_FULL)
    {
        uartsoc_ring_write_fml(&uartsocvalue,1);
        LPUART_DRV_SetRxBuffer(INST_UARTSOC,&uartsocvalue,1U);
    }
    else
    {
        LPUART_DRV_AbortReceivingData(INST_UARTSOC);
        LPUART_DRV_ReceiveData(INST_UARTSOC,&uartsocvalue,1U);
    }
}
/*uart1 init,this used for PC and MCU communication*/
void shell_uart_config_init(void)
{
//    lpuart_init__hal_api(INST_LPUART1);
    lpuart_init__hal_api(INST_LPUART1,&lpuart1_State, &lpuart1_InitConfig0);
    lpuart_drv_install_rx_callback_hal_api(INST_LPUART1, shell_uart_recCallback, NULL);
    lpuart_drv_receive_data_hal_api(INST_LPUART1,&uartshellvalue,1U);
    int_sys_set_priority_hal_api(LPUART1_RxTx_IRQn, 0x02);
    int_sys_enable_irq_hal_api(LPUART1_RxTx_IRQn);

    /*init shellCmdData struct, then prepare work*/
    shellCmdData.uartWork = shelluartNotWork;
    shellCmdData.shellCmd = shellCmdEnable;
    shellCmdData.rCnt = 0;
    shellCmdData.recTimeCnt = 0;
}

/*uart0 init,this used for SOC and MCU communication*/
void uart_soc_config_init(void)
{
    status_t ret;
//    lpuart_init__hal_api(INST_UARTSOC);
    ret =lpuart_init__hal_api(INST_UARTSOC,&UARTSOC_State, &UARTSOC_InitConfig0);
    lpuart_drv_install_rx_callback_hal_api(INST_UARTSOC, uart_soc_recCallback, NULL);
    ret =lpuart_drv_receive_data_hal_api(INST_UARTSOC,&uartsocvalue,1U);
    int_sys_set_priority_hal_api(LPUART0_RxTx_IRQn, 0x02);
    int_sys_enable_irq_hal_api(LPUART0_RxTx_IRQn);
}

static void analysis_cmd(struct stAnalysisCmd *dest,char *src)
{
    uint8_t i = 0,j=0;
    char *str = src,*str1;
    for(i = 0; i<strlen(src);i++)
    {
        if(i<3)
        {
            dest->cmd[i] = src[i];
        }
//        else if ((src[i] != ' ')&&(str1[i] != 0x0D) &&(str1[i+1] != 0x0A))
        else if (strstr(&dest->cmd,"set") != NULL)
        {
            if ((src[i] != ' '))
                dest->idDef[j++] = src[i];
            else
            {
                dest->idDef[j] = ' ';
                break;
            }
        }
        else if (strstr(&dest->cmd,"get") != NULL)
        {
            if ((src[i] != ' ')&&(src[i] != 0x0D) &&(src[i+1] != 0x0A))
                dest->idDef[j++] = src[i];
            else
                break;
        }
        else
        {
            break;
        }
    }

    while(str = strchr(str,' '))
    {
        str ++;
        str1 = str;
        break; /*note:if without this line ,will filter all space */
    }

    for(i = 0; i < strlen(str1); i++)
    {
//        if ((str1[i] != ' ')&&(str1[i] != 0x0D) &&(str1[i+1] != 0x0A))
//        if ((str1[i] != ' ')&&(str1[i] != '\0'))
        if (str1[i] != '\0')
        {
            dest->data[i] = str1[i];
        }
        else
        {
            break;
        }
    }
}

void readFrameFromRing(struct uartSocReadBuffType *readBuf)
{
    uint8_t readValue;
//    uint8_t readBuf[256] = {0};
    uint8_t readCnt = 0,datalength = 0;
    uint16_t ringLength = 0;
    ringLength = uartsoc_ring_can_read_fml();
    if (ringLength >= 7)  //one frame at least has 7 byte data
    {
        readBuf->readBuffFlag = readBufferDisable;
        for(uint16_t i = 0; i < 256; i++ )
        {
            uartsoc_ring_read_fml(&readValue);
            if (readCnt == head1Pos)
            {
                readBuf->readBuff[readCnt] = readValue;
                readCnt = (UART_SOC_HEAD1 != readBuf->readBuff[readCnt])? 0 :readCnt+1;
            }
            else if (readCnt == head2Pos)
            {
                readBuf->readBuff[readCnt] = readValue;
                readCnt = (UART_SOC_HEAD2 != readBuf->readBuff[readCnt])? 0 :readCnt+1;
            }
            else if (readCnt == lengthPos)
            {
                i = 0;
                readBuf->readBuff[readCnt] = readValue;
                datalength = readValue;
                readCnt = readCnt+1;
            }
            else if (readCnt == cmdPos)
            {
                readBuf->readBuff[readCnt] = readValue;
                readCnt = readCnt+1;
            }
            else if (readCnt == frameNumPos)
            {
                readBuf->readBuff[readCnt] = readValue;
                readCnt = readCnt+1;
            }
            else if (readCnt > frameNumPos)
            {
                readBuf->readBuff[readCnt] = readValue;
                readCnt++;
                if (readCnt == datalength+6)
                {
                    readBuf->usefullDataCnt = readCnt;
                    break;
                }
            }
        }
    }
}

static FRESULT setConfigFile(struct stAnalysisCmd *setData)
{
    FRESULT result = FR_OK;
    FIL configFs;
    FRESULT resSetFlash;
    char readBuf[70] = {0};
    UINT readCnt = 0;
    char writeBuf[70] = {0};
    UINT writeCnt = 0;
    char *getresult;
    uint8_t addFlag = 1;
    char *readFileALL ;

    strcat(writeBuf,setData->idDef);
    strcat(writeBuf,setData->data);

    resSetFlash = f_open(&configFs, "config/configInfo.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    if (resSetFlash == FR_OK)
    {
        resSetFlash = f_lseek(&configFs, 0);
        while(!f_eof(&configFs))
        {
            getresult = f_gets(readBuf,70, &configFs);
            if (getresult != NULL)
            {
                getresult = strstr(readBuf,setData->idDef);
                if (getresult != NULL)  // the file have current field,need re-write this field.do not need add at the end fo file
                {
                    uint32_t eraseDataAddrTail = 0;
                    volatile uint32_t FileSize = 0;
                    FileSize = f_size(&configFs);
                    readFileALL = (char *) pvPortMalloc(f_size(&configFs)+strlen(writeBuf)+10);
                    eraseDataAddrTail = f_tell(&configFs);
                    f_lseek(&configFs,0);
                    if(f_read( &configFs,readFileALL,f_size(&configFs),&readCnt) == FR_OK) //read file all data
                    {
                        resSetFlash = f_close(&configFs);
                        if (resSetFlash != FR_OK)
                        {
                            //reseve interface
                        }
                        f_unlink("config/configInfo.txt");
                        /*readFileALL include: SSIDPN00264\r\nVMSPN3B1925402C\r\nsetECUSND1234567
                         * now need to modify field VMSPN pra
                         * we need get VMSPN's position:when we use cmd "f_gets(readBuf,70, &configFs)" get this line ,
                         * we found this line is need instead by us,the file point position is 30
                         * we need to write field SSIDPN00264\r\n,so in readFileALL expect "VMSPN3B1925402C\r\n" is we need*/
                        resSetFlash = f_open(&configFs, "config/configInfo.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
                        if (resSetFlash != FR_OK)
                        {
                            //reseve interface
                        }
                        resSetFlash = f_write(&configFs, &writeBuf, strlen(writeBuf), &writeCnt);
                        if (resSetFlash == FR_OK)
                        {
                            Printf("set secess\r\n");
                            //reseve interface
                        }
                        resSetFlash = f_write(&configFs, readFileALL,eraseDataAddrTail-strlen(readBuf), &writeCnt);
                        if (resSetFlash != FR_OK)
                        {
                            //reseve interface
                        }
                        resSetFlash = f_write(&configFs,(readFileALL+eraseDataAddrTail) ,readCnt-eraseDataAddrTail, &writeCnt);
                        if (resSetFlash != FR_OK)
                        {
                            //reseve interface
                        }
                    }
                    vPortFree(readFileALL);
                    addFlag =0;
                    break;
                }
                memset(readBuf,0,sizeof(readBuf));
            }
            else
            {
                result = !FR_OK;
                break;
            }
        }

        if(addFlag == 1) //the file haven't idDef field,needs add at the end of file.
        {
            resSetFlash = f_lseek(&configFs, 0);
            resSetFlash = f_lseek(&configFs, f_size(&configFs));
            if (resSetFlash == FR_OK)
            {
                resSetFlash = f_write(&configFs, &writeBuf, strlen(writeBuf), &writeCnt);
                {
                    if ((resSetFlash != FR_OK) || (writeCnt < strlen(writeBuf)))
                    {
                        /*write error*/
                        result = !FR_OK;
                    }
                    else
                    {
                        Printf("set secess\r\n");
                    }
                }
            }
            else
            {
                result = !FR_OK;
            }
        }
    }
    else
    {
        result = !FR_OK;
    }
    resSetFlash = f_close(&configFs);
    if( resSetFlash != FR_OK)
    {
        result = !FR_OK;
    }
    return result;
}

static void getTime(char *time)
{
//    uint32_t time=0;
    rtc_timedate_t Time;
    char temp[5] = {0};

    strcat(time,"[");

    RTC_DRV_GetCurrentTimeDate(RTCTIMER1, &Time);
    sprintf(temp,"%4d",Time.year);
    strcat(time,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.month);
    strcat(time,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.day);
    strcat(time,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.hour);
    strcat(time,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.minutes);
    strcat(time,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.seconds);
    strcat(time,temp);
    memset(temp,0,5);

    strcat(time,"]");
}
//cmbacktrace use this function,
/****************************
 * start:0x1001E000
 * 0x1001E000-0x1001E001:16bit,Stores space already used
 * 0x1001E002:8bit , store fault code
 * 0x1001E008:store falut message
 * */
#define SAVE_FAULT_SIZE (4000)
uint8_t faultLog[4096] = {0};
FRESULT saveFaultFile(struct stFaultType *faultMsg)
{
    char time[20]= {0};
    uint16_t length = 0;
    uint8_t writeCnt = 0 , ret = 0;
    uint16_t i =0;
    uint64_t usedadd = 0;

    getTime(time);
    strcat(faultMsg->faultReason,time);
    strcat(faultMsg->faultReason,"\r\n");

    if (*(__IO uint16_t*)(SAVE_FAULT_START_ADD) != 0xffff)
    {
        usedadd = *(__IO uint16_t*)(SAVE_FAULT_START_ADD);
    }

    memset(faultLog,0,4096);
    for (i = 0; i < usedadd*8; i++)
    {
        faultLog[i] = *(__IO uint8_t*)(SAVE_FAULT_START_ADD+8+i);
    }

    length = strlen(faultMsg->faultReason);
    if(length % 8 == 0)
    {
        writeCnt = length % 8;
    }
    else
    {
        writeCnt = length/8+1;
    }
    ret = flash_erase_sector_hal_api(SAVE_FAULT_START_ADD, 4096);
    /* Verify the erase operation at margin level value of 1, user read */
    ret = flash_verify_section_hal_api( SAVE_FAULT_START_ADD, 4096/FTFx_DPHRASE_SIZE,1u);
    /*write flashSectorBuff to FLASH sector*/
    for(i = 0; i < writeCnt; i++)
    {
        ret = flash_program_hal_api(SAVE_FAULT_START_ADD+8+i*8, 8, &faultMsg->faultReason[i*8]);
    }
    if (usedadd != 0)
    {
        if(usedadd*8 +writeCnt*8 > SAVE_FAULT_SIZE)
        {
            usedadd = (SAVE_FAULT_SIZE -writeCnt*8)/8; //the flag need 8 BYTEr space
        }
        for(i = 0; i < usedadd ; i++)
        {
            ret = flash_program_hal_api(SAVE_FAULT_START_ADD+8+writeCnt*8+i*8, 8, &faultLog[i*8]);
        }
    }
    usedadd+=writeCnt;
    usedadd =(usedadd | (faultMsg->faultCode << 16));
    ret = flash_program_hal_api(SAVE_FAULT_START_ADD, 8, &usedadd);
}

/*after read hardfault reason,need modify hardfault value is 0,
 * waitting next hardfault ,
 * write fault reason
 * if next has not any hardfault
 * this value is 0,means hardfault casue not reset*/
static void updataFalutFlag(void)
{
    uint8_t ret = 0;
    uint16_t i =0;

    for (i = 0; i < 4096; i++)
    {
        faultLog[i] = *(__IO uint8_t*)(SAVE_FAULT_START_ADD+i);
    }
    ret = flash_erase_sector_hal_api(SAVE_FAULT_START_ADD, 4096);
    ret = flash_verify_section_hal_api( SAVE_FAULT_START_ADD, 4096/FTFx_DPHRASE_SIZE,1u);
    faultLog[2] = 0x00;
    ret = flash_program_hal_api(SAVE_FAULT_START_ADD, 4096,faultLog);
}

static uint16_t getresetstatus()
{
    uint16_t reset_source = 0;
    int i;
    for(i=0;i<13;i++)
    {
        if(POWER_SYS_GetResetSrcStatusCmd(RCM,(rcm_source_names_t)(i+1)))
        {
            reset_source |= (1<<i);
        }
    }
    return reset_source;
}

static void getFaultLog(void)
{
    uint64_t usedadd = 0;
    uint16_t i=0;
    if (*(__IO uint16_t*)(SAVE_FAULT_START_ADD) != 0xffff)
    {
        usedadd = *(__IO uint16_t*)(SAVE_FAULT_START_ADD);
    }
    if( (usedadd!= 0) && (usedadd != 0xffff))
    {
        for (i = 0; i < usedadd*8; i++)
        {
            Printf("%c",*(__IO uint8_t*)(SAVE_FAULT_START_ADD+8+i));
        }
        Printf("\r\n");
    }
    else
    {
        Printf("No fault log info!\r\n");
    }
}

static FRESULT getConfigFile(struct stAnalysisCmd *setData,uint8_t *findData,uint8_t *cnt)
{
    FRESULT result = FR_OK;
    FIL readConfigFs;
    FRESULT resGetFlash;
    char readBuf[70] = {0};
    char *getresult;

    resGetFlash = f_open(&readConfigFs, "config/configInfo.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    if (resGetFlash == FR_OK)
    {
        while(!f_eof(&readConfigFs))
        {
            getresult = f_gets(readBuf,70, &readConfigFs);
            if (getresult != NULL)
            {
                getresult = strstr(readBuf,setData->idDef);
                if (getresult != NULL)
                {
                    if (findData != NULL)
                    {
                        uint8_t i=0;
                        for(i = 0; (readBuf[strlen(setData->idDef)+i] != 0x0D) && (readBuf[strlen(setData->idDef)+i+1] != 0x0A); i++)
                        {
                            findData[i] = readBuf[strlen(setData->idDef)+i];
                        }
                        *cnt = i;
                    }
                    Printf("%s %s\r\n",&(setData->idDef),&readBuf[strlen(setData->idDef)]);
                    break;
                }
            }
            else
            {
                result = !FR_OK;
                break;
            }
        }
    }
    else
    {
        result = !FR_OK;
    }
    resGetFlash = f_close(&readConfigFs);
    if( resGetFlash != FR_OK)
    {
        result = !FR_OK;
    }
    return result;
}

static void fileNameSortBuff(char sortFileName[][30],uint8_t fileCount)
{
    char temp[30] = {0};
    int i, j;

    for (i = 0; i < fileCount; ++i)
    {
        for (j = i + 1; j < fileCount; ++j)
        {
            if( strcmp((const char *)sortFileName[i], (const char *)sortFileName[j]) > 0)
            {
                strncpy(temp,(char *)sortFileName[i],fileNameMaxLen);
                strncpy((char *)sortFileName[i],(char *)sortFileName[j],fileNameMaxLen);
                strncpy((char *)sortFileName[j],temp,fileNameMaxLen);
            }
        }
    }
}

static void creatFileName(char *name)
{
    rtc_timedate_t Time;
    char temp[5] = {0};

    RTC_DRV_GetCurrentTimeDate(RTCTIMER1, &Time);
    sprintf(temp,"%4d",Time.year);
    strcat(name,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.month);
    strcat(name,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.day);
    strcat(name,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.hour);
    strcat(name,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.minutes);
    strcat(name,temp);
    memset(temp,0,5);

    sprintf(temp,"%02d",Time.seconds);
    strcat(name,temp);
    memset(temp,0,5);

    strcat(name,".txt");
}

static void creatNewFile(char *fileName)
{
    char name[20] = {0};
    FIL creatFs;
    FRESULT result;

    creatFileName(name);
    strcat(fileName,"/log/");
    strcat(fileName,name);
    result = f_open(&creatFs, fileName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    if (result == FR_OK)
    {
    }
    result = f_close(&creatFs);
}

static void mergeFileName(char *fileName , char *existFileName)
{
    strcat(fileName,"/log/");
    strcat(fileName,existFileName);
}

static void saveLogFile(struct stTask_log * saveLogData)
{
    FRESULT result = FR_OK;
    FIL saveLogFs;
    static FILINFO fno;
    uint16_t saveLogMsgLen = 0;
    DIR dir;
    UINT writeCnt = 0;
    char writebuf[80] = {0};
    char allFileName[logFileMaxCnt][fileNameMaxLen] = {0}, pathName[30] = {0};
    unsigned long total =0,free =0;
    uint8_t i = 0,fileCnt = 0;
    saveLogMsgLen = sizeof(struct stTask_log) + 2; //include '\0'
    memcpy(writebuf,saveLogData,saveLogMsgLen);

    result = f_opendir(&dir,"/log");
    if (result == FR_OK)
    {
        for( i = 0; i < logFileMaxCnt+10; i++)   //found all exist file
        {
            result = f_readdir(&dir, &fno);
            if(result == FR_OK)
            {
                if (fno.fname[0] != 0)   //file name is available
                {
                    fileCnt = i+1;
                    strcpy( allFileName[i],fno.fname);
                    f_stat(allFileName[i], &fno);
                }
                else
                {
                    break;
                }
            }
        }
    }
//    Printf("---------------------------\r\n");
    if(fileCnt > 1)
    {
#if LOG_DEBUG_PRINT
        for( i = 0; i < fileCnt; i++)
        {
            Printf("before: %s \r\n",allFileName[i]);
        }
#endif
        fileNameSortBuff(allFileName,fileCnt);
#if LOG_DEBUG_PRINT
//        for( i = 0; i < fileCnt; i++)
//        {
//            Printf("after: %s \r\n",allFileName[i]);
//        }
#endif
    }

//    exf_getfree("0",&total,&free);
//    Printf("free:%d\r\n",free);

    if ( fileCnt == 0)
    {
        memset(pathName,0,sizeof(pathName));
        creatNewFile(pathName);
        result = f_open(&saveLogFs, pathName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
        if (result == FR_OK)
        {
            result =  f_write(&saveLogFs, writebuf, sizeof(writebuf), &writeCnt);
        }
        result = f_close(&saveLogFs);
    }
    else if ((fileCnt > 0) && (fileCnt < logFileMaxCnt))
    {
        memset(pathName,0,sizeof(pathName));
        mergeFileName(pathName,allFileName[fileCnt - 1]);
        result = f_stat(pathName, &fno);
        if ((fno.fsize < singleFileMaxSize) && ( singleFileMaxSize - fno.fsize > saveLogMsgLen))
        {
            result = f_open(&saveLogFs, pathName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if (result == FR_OK)
            {
                result = f_lseek(&saveLogFs, 0);
                result = f_lseek(&saveLogFs, f_size(&saveLogFs));
                result =  f_write(&saveLogFs, writebuf, sizeof(writebuf), &writeCnt);
            }
            result = f_close(&saveLogFs);
        }
        else
        {
            memset(pathName,0,sizeof(pathName));
            creatNewFile(pathName);
            result = f_open(&saveLogFs, pathName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if (result == FR_OK)
            {
                result =  f_write(&saveLogFs, writebuf, sizeof(writebuf), &writeCnt);
            }
            result = f_close(&saveLogFs);
        }
    }
    else if (fileCnt >= logFileMaxCnt)
    {
        memset(pathName,0,sizeof(pathName));
        mergeFileName(pathName,allFileName[fileCnt - 1]);
        result = f_stat(pathName, &fno);
        if ((fno.fsize < singleFileMaxSize) && ( singleFileMaxSize - fno.fsize > saveLogMsgLen))
        {
            result = f_open(&saveLogFs, pathName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if (result == FR_OK)
            {
                result = f_lseek(&saveLogFs, 0);
                result = f_lseek(&saveLogFs, f_size(&saveLogFs));
                result =  f_write(&saveLogFs, writebuf, sizeof(writebuf), &writeCnt);
            }
            result = f_close(&saveLogFs);
        }
        else
        {
            memset(pathName,0,sizeof(pathName));
            mergeFileName(pathName,allFileName[0]);
            exf_getfree("0",&total,&free);
#if LOG_DEBUG_PRINT
            Printf("del:%s\r\n",pathName);
            Printf("ex unlink:%d\r\n",free);
#endif
            result =f_unlink(pathName);
#if LOG_DEBUG_PRINT
            exf_getfree("0",&total,&free);
            Printf("freed:%d\r\n",free);
#endif
            memset(pathName,0,sizeof(pathName));
            creatNewFile(pathName);
            result = f_open(&saveLogFs, pathName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if (result == FR_OK)
            {
                result =  f_write(&saveLogFs, writebuf, sizeof(writebuf), &writeCnt);
            }
            result = f_close(&saveLogFs);
        }
    }
}


static void uploadConfig(void)
{
    FRESULT result = FR_OK;
    FIL readConfigFs;
    FRESULT resGetFlash;
    char readBuf[70] = {0};
    char *getresult;

    resGetFlash = f_open(&readConfigFs, "config/configInfo.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
    if (resGetFlash == FR_OK)
    {
        while(!f_eof(&readConfigFs))
        {
            getresult = f_gets(readBuf,70, &readConfigFs);
            if (getresult != NULL)
            {
                Printf("%s\r\n",readBuf);
            }
        }
    }
    else
    {
        result = !FR_OK;
    }
    resGetFlash = f_close(&readConfigFs);
    if( resGetFlash != FR_OK)
    {
        result = !FR_OK;
    }
}
/**********************************************************************/
static void responseACK(uint8_t *findData , uint8_t findCnt,uint8_t *uartSocData)
{
    uint8_t resDataBuf[270] ={0};
    uint16_t frameLength = 0;
    uint8_t checkSum = 0;
    resDataBuf[head1Pos] = UART_SOC_HEAD1 ;
    resDataBuf[head2Pos] = UART_SOC_HEAD2 ;
    resDataBuf[cmdPos] = uartSocData[cmdPos];
    resDataBuf[frameNumPos] = uartSocData[frameNumPos];
    resDataBuf[paraPos] = uartSocData[paraPos];
    if (findData != NULL)
    {
        for (uint8_t i=0; i < findCnt; i++)
        {
            resDataBuf[dataPos+i] = findData[i];
        }
        resDataBuf[lengthPos] = findCnt + 1;
        frameLength = ONE_FRAME_SHORTEST_LEN + findCnt;
    }
    else
    {
        resDataBuf[lengthPos] = 1 ;
        frameLength = ONE_FRAME_SHORTEST_LEN;
    }
    for(uint8_t i = 0; i < frameLength-1; i++)
    {
        checkSum ^= resDataBuf[i];
    }
    resDataBuf[frameLength-1] = checkSum;
    uartSocSendData(resDataBuf,frameLength);
}

static void uartSocSetCmdFunc(uint8_t *data, uint8_t dataLen)
{
    FRESULT res_flash;
    struct stAnalysisCmd cmdData;
    memset(&cmdData,0,sizeof(cmdData));
    switch(data[paraPos])
    {
        case uartSocParaVMSPN:
        {
            strcat(cmdData.idDef,"VMSPN "); break;
        }
        case uartSocParaSSID:
        {
            strcat(cmdData.idDef,"SSID "); break;
        }
        case uartSocParaECUMD:
        {
            strcat(cmdData.idDef,"ECUMD "); break;
        }
        case uartSocParaECUSND:
        {
            strcat(cmdData.idDef,"ECUSND "); break;
        }
        case uartSocParaVIN:
        {
            strcat(cmdData.idDef,"VIN "); break;
        }
        case uartSocParaSSECUHWN:
        {
            strcat(cmdData.idDef,"SSECUHWN "); break;
        }
        case uartSocParaSSECUHWVN:
        {
            strcat(cmdData.idDef,"SSECUHWVN "); break;
        }
        case uartSocParaSSECUSWN:
        {
            strcat(cmdData.idDef,"SSECUSWN "); break;
        }
        case uartSocParaSSECUSWVN:
        {
            strcat(cmdData.idDef,"SSECUSWVN "); break;
        }
        case uartSocParaRSCOTSN:
        {
            strcat(cmdData.idDef,"RSCOTSN "); break;
        }
        case uartSocParaEDID:
        {
            strcat(cmdData.idDef,"EDID "); break;
        }
        default:break;
    }

    memcpy(cmdData.data,&data[dataPos],data[lengthPos]-1);
    strcat(cmdData.data,"\r\n");

    taskENTER_CRITICAL();
    res_flash = setConfigFile(&cmdData);
    taskEXIT_CRITICAL();
    if (res_flash == FR_OK)
    {
        responseACK(NULL, 0, data);
    }

}

static void uartSocGetCmdFunc(uint8_t *data)
{
    FRESULT res_flash;
    uint8_t getDataBuf[256]={0},dataCnt = 0;

    struct stAnalysisCmd cmdData ;
    memset(&cmdData,0,sizeof(cmdData));
    switch(data[paraPos])
    {
        case uartSocParaVMSPN:
        {
            strcat(cmdData.idDef,"VMSPN "); break;
        }
        case uartSocParaSSID:
        {
            strcat(cmdData.idDef,"SSID "); break;
        }
        case uartSocParaECUMD:
        {
            strcat(cmdData.idDef,"ECUMD "); break;
        }
        case uartSocParaECUSND:
        {
            strcat(cmdData.idDef,"ECUSND "); break;
        }
        case uartSocParaVIN:
        {
            strcat(cmdData.idDef,"VIN "); break;
        }
        case uartSocParaSSECUHWN:
        {
            strcat(cmdData.idDef,"SSECUHWN "); break;
        }
        case uartSocParaSSECUHWVN:
        {
            strcat(cmdData.idDef,"SSECUHWVN "); break;
        }
        case uartSocParaSSECUSWN:
        {
            strcat(cmdData.idDef,"SSECUSWN "); break;
        }
        case uartSocParaSSECUSWVN:
        {
            strcat(cmdData.idDef,"SSECUSWVN "); break;
        }
        case uartSocParaRSCOTSN:
        {
            strcat(cmdData.idDef,"RSCOTSN "); break;
        }
        case uartSocParaEDID:
        {
            strcat(cmdData.idDef,"EDID "); break;
        }
        default:break;
    }

    taskENTER_CRITICAL();
    res_flash = getConfigFile(&cmdData,&getDataBuf,&dataCnt);
    taskEXIT_CRITICAL();
    if (res_flash == FR_OK)
    {
        responseACK(getDataBuf , dataCnt, data);
    }
}

uint8_t shellFlagSector[4096] = {0};
static void uartSocShellAvailableUpdataFunc(uint8_t *data)
{
    uint8_t ret = 0;
    for (uint16_t i = 0; i< 4096; i++) //read the whole sector
    {
        shellFlagSector[i] = (*(__IO uint8_t*)(SAVE_GET_SET_AVAILABLE_ADD+i));
    }
    ret = flash_erase_sector_hal_api(SAVE_GET_SET_AVAILABLE_ADD, 4096);
    ret = flash_verify_section_hal_api( SAVE_GET_SET_AVAILABLE_ADD, 4096/FTFx_DPHRASE_SIZE,1u);
    if (data[dataPos] == 0)
    {
        shellFlagSector[0] = 0;
    }
    else if (data[dataPos] == 0x01)
    {
        shellFlagSector[0] = 1;
    }
    ret = flash_program_hal_api(SAVE_GET_SET_AVAILABLE_ADD, 4096, shellFlagSector);
    responseACK(NULL,0,data);
}

static void uartSocUploadFunc(void)
{
    uint8_t resDataBuf[20] ={0}, checkSum = 0;
    uint16_t RstSts = 0;

    static uint8_t hardFaultVal = 0;
    static uint8_t faultFlag = 0;
    RstSts = getresetstatus();
    resDataBuf[head1Pos] = UART_SOC_HEAD1 ;
    resDataBuf[head2Pos] = UART_SOC_HEAD2 ;
    resDataBuf[lengthPos] = 4;
    resDataBuf[cmdPos] = uartSocUploadCmd;
    resDataBuf[frameNumPos] = 0x0D;
    resDataBuf[dataPos] = (RstSts>>8) & 0xff; //high 8 bit
    resDataBuf[dataPos+1] = RstSts & 0xff;  //low 8 bit
    if (faultFlag == 0)
    {
        faultFlag =1;
        hardFaultVal = *(__IO uint8_t*)(SAVE_FAULT_START_ADD+2);
        updataFalutFlag();
    }
    resDataBuf[dataPos+2] = hardFaultVal;
    for(uint8_t i = 0; i < 9; i++)
    {
        checkSum ^= resDataBuf[i];
    }
    resDataBuf[9] = checkSum;
    uartSocSendData(resDataBuf,10);
}

void fault_test_by_div0(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
}

#define HSRUN (0u) /* High speed run      */
#define RUN   (1u) /* Run                 */
#define VLPR  (2u) /* Very low power run  */
#define STOP1 (3u) /* Stop option 1       */
#define STOP2 (4u) /* Stop option 2       */
#define VLPS  (5u) /* Very low power stop */
#if PWR_TEST
void power_test_cmd_anay( void )
{
    uint32_t sendvalue = 0;
    if (strstr((char *)shellCmdData.recbuf,"ignOff")!=NULL)
    {
        sendvalue = 1;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"ignACC")!=NULL)
    {
        sendvalue = 2;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"ignOn")!=NULL)
    {
        sendvalue = 3;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"ignReady")!=NULL)
    {
        sendvalue = 4;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"AntithelfArm")!=NULL)
    {
        sendvalue = 5;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"AntithelfDisarm")!=NULL)
    {
        sendvalue = 6;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"AntithelfPream")!=NULL)
    {
        sendvalue = 7;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"AntithelfWarning")!=NULL)
    {
        sendvalue = 8;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"FLOpen")!=NULL)
    {
        sendvalue = 9;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"FLClose")!=NULL)
    {
        sendvalue = 10;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SOCFiveMinute")!=NULL)
    {
        sendvalue = 11;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SocDoubleClick")!=NULL)
    {
        sendvalue = 12;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SocHearBeatEn")!=NULL)
    {
        sendvalue = 13;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SocHearBeatDis")!=NULL)
    {
        sendvalue = 14;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SocACKNotAllow")!=NULL)
    {
        sendvalue = 15;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"SocACKAllow")!=NULL)
    {
        sendvalue = 16;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
    else if (strstr((char *)shellCmdData.recbuf,"DBC")!=NULL)
    {
        sendvalue = 17;
        xQueueSendToBack(pwrManageQueue, &sendvalue, 0);
    }
}
#endif

void uart_log_task_fml( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();
    uint8_t msg[32];
    uint8_t len = 0;
    uint32_t bytesRemaining;
    uint32_t uartTimeOut=0;
    FRESULT res_flash;
    BaseType_t xResult;
    struct stAnalysisCmd analyCmdData ;
//    struct stTask_log taskLog;
//    memset(&taskLog,0,sizeof(taskLog));
    status_t retV = STATUS_SUCCESS;
//    ps_subscriber_t *taskLogSub = ps_new_subscriber(sizeof(taskLog)*10+10,STRLIST("logRecordTopic") );  // taskLogSub can receive most 10 data type is TaskLog
//    ps_msg_t *taskLogMsg = NULL;
//    uint8_t taskLogMsgCnt = 0;
    struct stTask_log taskLog;
    rtc_timedate_t getdatatime;
    upLoadTime.upUploadEn = 1;
    while(1)
    {
//        fault_test_by_div0();
        vTaskDelayUntil(&xNextWakeTime, (10/portTICK_RATE_MS));
//        Printf("filename:%s\r\n", __FILE__);
//        Printf("funname:%s\r\n", __func__);
        if (xQueueReceive(uartLogQueue, &msg[0], 0))
        {
            len = strlen(msg);
            lpuart_send_data__hal_api(INST_LPUART1, (uint8_t *)msg, len);
            while (lpuart_get_transmit_status__hal_api(INST_LPUART1, &bytesRemaining)!= STATUS_SUCCESS)
            {
                uartTimeOut ++;
                if(uartTimeOut >= 0x8ffff)
                {
                    uartTimeOut = 0;
                    break;
                }
            }
        }
        /***********************shell config(set/get) start****************************************/
        xResult = xSemaphoreTake(configQueue, (TickType_t)0);
        if (xResult == pdTRUE)
        {
            if (strstr((char *)shellCmdData.recbuf,"\r\n")!=NULL)
            {
                if ((strstr((char *)shellCmdData.recbuf,"get")!=NULL) || (strstr((char *)shellCmdData.recbuf,"set")!=NULL))
                {
                    memset(&analyCmdData,0,sizeof(analyCmdData));
                    analysis_cmd(&analyCmdData,(char *)shellCmdData.recbuf);
                    if ( !strcmp(analyCmdData.cmd,"set"))
                    {
                        taskENTER_CRITICAL();
                        res_flash = setConfigFile(&analyCmdData);
                        if (res_flash == FR_OK)
                        {
                            /*if set is not sucess*/
                        }
                        taskEXIT_CRITICAL();
                    }
                    else if ( !strcmp(analyCmdData.cmd,"get"))
                    {
                        taskENTER_CRITICAL();
                        if( !strcmp(analyCmdData.idDef,"FAULT"))
                        {
                            getFaultLog();
                        }
                        else
                        {
                            res_flash = getConfigFile(&analyCmdData,NULL,NULL);
                            if (res_flash == FR_OK)
                            {
                                /*if get is not sucess*/
                            }
                        }
                        taskEXIT_CRITICAL();
                    }
                }
            }
            else
            {
                Printf("fomate wrong\r\n");
            }

            if (strstr((char *)shellCmdData.recbuf,"VLPS")!=NULL)
            {
                Printf("vlps\r\n");
//                mcu_halt_set_fml_api();
                rtc_get_timestamp_hal_api(&getdatatime);
                getdatatime.minutes =getdatatime.minutes + 2;
//                getdatatime.hour = getdatatime.hour+4; //SOSC
//                getdatatime.day = getdatatime.day+1; //FIRC
                set_alarm_Time_hal_api(&getdatatime);
                Printf("%d-%d-%d:%d-%d-%d\r\n",getdatatime.year,getdatatime.month,getdatatime.day,getdatatime.hour,getdatatime.minutes,getdatatime.seconds);
                mcu_halt_set_fml_api();
                mcu_wakeup_set_fml_api();
                if (retV == STATUS_SUCCESS)
                {
                    if (POWER_SYS_GetCurrentMode() == POWER_MANAGER_RUN)
                    {
                        Printf("Current mode is RUN.\r\n");
                    }
                    else
                    {
                        Printf("Current mode is VLPR.\r\n");
                    }
                }
                else
                {
                    Printf("Switch VLPS mode unsuccessfully\r\n");
                }
            }
            if (strstr((char *)shellCmdData.recbuf,"time")!=NULL)
            {
                rtc_timedate_t setTime ;
                setTime.year = 2021;
                setTime.month = shellCmdData.recbuf[4];
                setTime.day = shellCmdData.recbuf[5];
                setTime.hour = shellCmdData.recbuf[6];
                setTime.minutes = shellCmdData.recbuf[7];
                setTime.seconds = shellCmdData.recbuf[8];
                rtc_updata_time_api(&setTime);
            }
            if (strstr((char *)shellCmdData.recbuf,"date")!=NULL)
            {
                rtc_timedate_t getdatatime ;
                rtc_get_timestamp_hal_api(&getdatatime);
                Printf("%d-%d-%d:%d-%d-%d\r\n",getdatatime.year,getdatatime.month,getdatatime.day,getdatatime.hour,getdatatime.minutes,getdatatime.seconds);
            }
#if PWR_TEST
            else
            {
                power_test_cmd_anay();
            }
#endif
        }
        /***********************shell config(set/get) end****************************************/

        /***********************log record start****************************************/
        if (xQueueReceive(taskLogQueue, &taskLog, 0))
        {
            Printf("%d-%d-%d:%d-%d-%d ",taskLog.logTime.year,taskLog.logTime.month,taskLog.logTime.day,
                    taskLog.logTime.hour,taskLog.logTime.minutes,taskLog.logTime.seconds
                    );
            Printf("%s ",taskLog.functionName);
            Printf(":%d %s",taskLog.logEvent,taskLog.inifo);
        }
#if 0
        taskLogMsg = ps_get(taskLogSub,0);
        if ( taskLogMsg != NULL )
        {
            memcpy(&taskLog,(struct stTask_log *)taskLogMsg->ptr_val, sizeof(taskLog));
            taskENTER_CRITICAL();
            saveLogFile(&taskLog);
            taskEXIT_CRITICAL();
            memset(&taskLog,0,sizeof(taskLog));
            ps_unref_msg(taskLogMsg);
            taskLogMsgCnt = ps_waiting( taskLogSub );
            for(uint8_t i = 0; i < taskLogMsgCnt ; i++)
            {
                taskLogMsg = ps_get(taskLogSub,0);
                memcpy(&taskLog,(struct stTask_log *)taskLogMsg->ptr_val, sizeof(taskLog));
                taskENTER_CRITICAL();
                saveLogFile(&taskLog);
                taskEXIT_CRITICAL();
                memset(&taskLog,0,sizeof(taskLog));
                ps_unref_msg(taskLogMsg);
            }
        }
#endif
        /***********************log record end *****************************************/

        /*******************************config field upload****************************************/
        upLoadTime.upUploadEn = (*(__IO uint8_t*)(SAVE_GET_SET_AVAILABLE_ADD));
        if (upLoadTime.upUploadEn)
        {
            if (upLoadTime.timeUploadCnt >= UPLOADTIMECYCLE)
            {
                taskENTER_CRITICAL();
                uploadConfig();
                taskEXIT_CRITICAL();
                uartSocUploadFunc();
                upLoadTime.timeUploadCnt = 0;
            }
        }
        /***********************************upload end*********************************************/

        if (uartSocReadBuff.readBuffFlag == readBufferEnable)
        {
            readFrameFromRing(&uartSocReadBuff);
            if (uartSocReadBuff.readBuffFlag == readBufferDisable)
            {
                uint8_t checksum = 0;
                //checksum
                for (uint8_t i = 0; i < uartSocReadBuff.usefullDataCnt-1; i++)
                {
                    checksum ^= uartSocReadBuff.readBuff[i];
//                    Printf("%02x ",uartSocReadBuff.readBuff[i]);
                }
//                Printf("%x ",uartSocReadBuff.readBuff[uartSocReadBuff.usefullDataCnt-1]);

                if (checksum == uartSocReadBuff.readBuff[uartSocReadBuff.usefullDataCnt-1]) // is equal
                {
                    if (uartSocReadBuff.readBuff[cmdPos] == uartSocSetCmd)  //set cmd
                    {
                        uartSocSetCmdFunc(uartSocReadBuff.readBuff,uartSocReadBuff.usefullDataCnt);
                    }
                    else if (uartSocReadBuff.readBuff[cmdPos] == uartSocgetCmd) //get cmd
                    {
                        uartSocGetCmdFunc(uartSocReadBuff.readBuff);
                    }
                    else if (uartSocReadBuff.readBuff[cmdPos] == uartSocSetGetEnableCmd) //set/get cmd
                    {
                        uartSocShellAvailableUpdataFunc(uartSocReadBuff.readBuff);
                    }
                }
                uartSocReadBuff.readBuffFlag = readBufferEnable;
            }
        }
    }
}


