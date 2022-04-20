/*
 * fml_freertostask.c
 *
 *  Created on: 2021年5月25日
 *      Author: Administrator
 */
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "com_task.h"
#include "CanNm.h"
#include "Com.h"
#include "pwrmanage_apl.h"

#define TEST_DEBUG 1

extern int32_t spi_ring_write_fml(uint8_t *data,uint16_t len);
extern uint8_t socAndMcuConnecting;
uint8_t socAndMcuConnectingFlag = 1;
uint8_t socAndMcuConnectingOld;
uint8_t tempTestData[20];
uint32_t canFrames;
uint8_t NmSleepMode;
uint8_t accLowTimes=0;
uint8_t accHighTimes=0;
extern uint8_t socResetFlag;
/*************************************************/
extern uint32_t canRingCount;
void mcu_check_acc_status_fml(void)
{
    uint32_t pinoutput;
    pinoutput = pins_read_pins_hal_api(PTC);
    if((pinoutput & 0x00080000) == 0)
    {
        accLowTimes ++;
        accHighTimes =0;
        if(accLowTimes >= 5)
        {
            accLowTimes = 0;
            uart_printf_data_fml_api(UARTTASKPRINT,tempTestData,1,__FUNCTION__,",ACC OFF");
            CanNm_NetworkRelease(0);
        }
    }
    else
    {
        accLowTimes =0;
        if(NmSleepMode == 1)
        {
            accHighTimes ++;
            if(accHighTimes >=5)
            {
                accHighTimes = 0;
                CanNm_NetworkRequest(0);
            }
        }
    }
}
ps_msg_t *socTest;
uint8_t SpiRecData;
void OneHourModeAck(uint8_t data)
{
    SpiRecData = data;
    ps_flush(socSpiRecSub);
    PUB_INT_FL("SpiRec", (SpiRecData), FL_STICKY);
}
void fiveMinutesModeAck(uint8_t data)
{
    SpiRecData = data;//3,4
    ps_flush(socSpiRecSub);
    PUB_INT_FL("SpiRec", (SpiRecData), FL_STICKY);
}
void DoubleClick(uint8_t data)
{
    SpiRecData = data;//3,4
    ps_flush(doubleClickSub);
    ps_flush(socFiveTimeOutSub);
    if(SpiRecData == 0x01)
    {
        PUB_INT_FL("DoubleClick", (SpiRecData), FL_STICKY);
    }
    else if(SpiRecData == 0x00)
    {
        PUB_INT_FL("SocFiveTimeOut", (SpiRecData), FL_STICKY);
    }
}
void get_soc_data()
{
    //751A yix小时模式反馈
    SpiRecData = OneHourEnable;
    ps_flush(socSpiRecSub);
    PUB_INT_FL("SpiRec", (SpiRecData), FL_STICKY);

    /*** 5 m**/
    //751E APP下发到MCU 5分钟时间反馈
    SpiRecData = 3;//3,4
    ps_flush(socSpiRecSub);
    PUB_INT_FL("SpiRec", (SpiRecData), FL_STICKY);

    //双击屏幕
    SpiRecData = DoubleClickEnable;
    ps_flush(doubleClickSub);
    PUB_INT_FL("DoubleClick", (SpiRecData), FL_STICKY);
}
void check_soc_connect(void)
{
//    Printf("heart %d\r\n",socAndMcuConnectingFlag);
	if(socAndMcuConnectingOld != socAndMcuConnecting)
	{
		socAndMcuConnectingOld = socAndMcuConnecting;
		socAndMcuConnectingFlag = 1;
	}
	else
	{
		socAndMcuConnectingFlag = 0;
	}
}
uint8_t getSocHeartBeatSts()
{
//    Printf("get heart %d\r\n",socAndMcuConnectingFlag);
	return socAndMcuConnectingFlag;
}
HuModeStsType mcuMode;
uint8_t send_MCU_mode_fml_api(void)
{
    if(mcuMode != getPowerManageSts())
    {
        PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
        Printf("send MCU pwr mode\r\n");
        mcuMode = getPowerManageSts();
        tempTestData[0] = 0x73;
        tempTestData[1] = 0x50;
        tempTestData[2] = 3;
        tempTestData[3] = 0x0;
        tempTestData[4] = mcuMode;
        tempTestData[5] = socResetFlag;
        spi_ring_write_fml(tempTestData,6 );
    }
}

uint8_t send_MCU_sleep_mode_fml_api(void)
{
//    if(mcuMode != getPowerManageSts())
    {
        PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
        Printf("send MCU pwr mode\r\n");
        mcuMode = getPowerManageSts();
        tempTestData[0] = 0x73;
        tempTestData[1] = 0x50;
        tempTestData[2] = 3;
        tempTestData[3] = 0x0;
        tempTestData[4] = mcuMode;
        tempTestData[5] = socResetFlag;
        spi_ring_write_fml(tempTestData,6 );
    }
}

uint8_t MonitorHeartFlag = 0;
void mcu_test_task( void *pvParameters )
 {
     TickType_t xNextWakeTime;
     xNextWakeTime = xTaskGetTickCount();
     uint8_t taskTimes=0;
//     static uint8_t runtimes = 0;
     uint8_t value;
//     socSpiSendSub = ps_new_subscriber(10, STRLIST("SpiSendRequst"));
     while(1)
     {
        vTaskDelayUntil(&xNextWakeTime, (100/portTICK_RATE_MS));

        //Printf("mcu mode %d",getPowerManageSts());
        /***********************soc test****************************/
        socTest = ps_get(socSpiSendSub,0);
        if (socTest != NULL)
        {
            value = (uint8_t)socTest->int_val;
            if (value == oneHourTimeOutVal)
            {
                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                tempTestData[0] = 0x73;
                tempTestData[1] = 0x57;
                tempTestData[2] = 2;
                tempTestData[3] = 0x0;
                tempTestData[4] = 0x0;
#if TEST_DEBUG
                Printf("OneHour timeout request\r\n");
//                uart_printf_data_fml_api(UARTTASKPRINT,1,1,__FUNCTION__,",OneHour");
#endif
                spi_ring_write_fml(tempTestData,5 );
            }
            else if (value == fiveMinutesTimeOutVal)
            {
                PINS_DRV_TogglePins(LED_GPIO,1 << LED1);
                tempTestData[0] = 0x73;
                tempTestData[1] = 0x5A;
                tempTestData[2] = 2;
                tempTestData[3] = 0x0;
                tempTestData[4] = 0x0;
#if TEST_DEBUG
                Printf("Five timeout request\r\n");
//                uart_printf_data_fml_api(UARTTASKPRINT,1,1,__FUNCTION__,",FiveTime");
#endif
                spi_ring_write_fml(tempTestData,5 );
            }
            ps_unref_msg(socTest);
        }
        /*************************************/
//        PINS_DRV_TogglePins(LED_GPIO,1 << LED2);
//        if(NmSleepMode == 1)
//        {
//            mcu_halt_set_fml_api();
//            NmSleepMode = 0;
//            mcu_wakeup_set_fml_api();
//        }
//        mcu_check_acc_status_fml();
//        taskTimes ++;
//        if(taskTimes >=50)
//        {
//            taskTimes =0;
//            tempTestData[0]=canFrames>>24;
//            tempTestData[1]=canFrames>>16;
//            tempTestData[2]=canFrames>>8;
//            tempTestData[3]=canFrames;
//            tempTestData[4]=canRingCount>>24;
//            tempTestData[5]=canRingCount>>16;
//            tempTestData[6]=canRingCount>>8;
//            tempTestData[7]=canRingCount;
//            //uart_printf_data_fml_api(tempTestData,8,",total",UARTTASKPRINT);
///*
//            struct stTask_log taskLog2;
//            memset(&taskLog2,0,sizeof(taskLog2));
//
//            taskLog2.logTime.year = 2021;
//            taskLog2.logTime.month = 6;
//            taskLog2.logTime.day = 31;
//            taskLog2.logTime.hour = 14;
//            taskLog2.logTime.minutes = 46;
//            taskLog2.logTime.seconds = 10;
//            taskLog2.logEvent = LOGInfo;
//            strcpy(taskLog2.inifo,"info log\r\n");
//            strcpy(taskLog2.functionName,__FUNCTION__);
//            xQueueSendToBack(taskLogQueue, &taskLog2, 0);*/
//            //strcpy(functionNameLog,__FUNCTION__);
//
//            uart_printf_char_fml_api(1,__FUNCTION__,"test log");
//
//        }
        if(spiRunStep == spi_com_normal)
        {
//            runtimes++;
//            if (runtimes >= 3)
//            {
//                runtimes = 0;
//                check_soc_connect();
//                MonitorHeartFlag = 1;
//            }
            /*
            tempTestData[0] = 0x73;
            tempTestData[1] = 0x50;
            tempTestData[2] = 0x3;
            tempTestData[3] = 0x0;
            tempTestData[4] = 0x00;
            tempTestData[5] = 0x00;
            tempTestData[6] = 0x73;
            tempTestData[7] = 0x58;
            tempTestData[8] = 0x02;
            tempTestData[9] = 0x00;
            tempTestData[10] = 0x01;
            spi_ring_write_fml(tempTestData,11 );*/
            readRingbufferEn = 1;
            send_MCU_mode_fml_api();
        }
     }
 }








