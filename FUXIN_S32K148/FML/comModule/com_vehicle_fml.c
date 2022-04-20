/*
 * can_function.c
 *
 *  Created on: 2020Äê12ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include "ComStack_Types_Cfg.h"
#include "ComStack_Types.h"
#include "CanIf_Type.h"
#include "Can_Pl.h"
#include "Can.h"
#include "CanIf.h"
#include "interrupt_manager.h"
#include "flexcan_driver.h"

#include "Dcm.h"
#include "CanTp.h"
#include "OsekNm.h"
#include "Com.h"
#include <stddef.h>
#include <string.h>
#include "FreeRTOS.h"
#include "com_task.h"
#include "Cpu.h"
#include "pubsub.h"
#include "pwrmanage_apl.h"

#define VEHICLE_DEBUG 0
#define COM_VEHICLE_FML 1

uint8 canBusoffStatus = 0;
uint8 appstart = 1;
uint8 networkFlag = 0;
uint8_t accStatus = 1;
uint16_t nmTimeoutCnt = 0;
uint8_t nmActive;
uint8_t canRingbufferRxData[256];
uint32_t canRingCount;


typedef struct {
    uint8_t data[8];                   /*!< Data bytes of the FlexCAN message*/
    uint8_t msgId[2];                     /*!< Message Buffer ID*/
    uint8_t dataLen;                    /*!< Length of data in bytes */
} flexcan_msgbuff_spi_t;
flexcan_msgbuff_spi_t msgRxCanBuffer[30]={
    {
        .dataLen=8,
    },
};
uint8_t spiCanBuffer[1024+48]={1};
uint8_t spiTxPackage[1024+48];
uint16_t canPakageLen;
uint8_t canReBuffer[20];
uint8_t busoffTimes;
uint8_t busoffFast;
uint8_t busoffFlag;
uint8_t canRingLock;
extern unsigned char canMessageReFlag;
int32_t spi_ring_write_fml(uint8_t *data,uint16_t len);

void check_canbus_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if (canBusoffStatus == 1) {
        can_controller_init_fml_api(0);
        set_can_controller_mode_fml_api(CANFML_CS_STARTED);
        canBusoffStatus = 0;
    }
}

void CanIf_GetCanBuffer
(
    uint16 CanId,
    uint8 CanDlc,
    uint8 *CanSduPtr
)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    int i;uint8_t len;
    canReBuffer[0]=(uint8_t)(CanId>>8);
    canReBuffer[1]=(uint8_t)(CanId);
    canReBuffer[2]=(uint8_t)(CanDlc);
    for(i=0;i<CanDlc;i++)
    {
        canReBuffer[3+i] = CanSduPtr[i];
    }
    len = 3+CanDlc;
    can_ring_write_fml(canReBuffer,len);
    canFrames ++;
}

void set_busoff_times_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    busoffFlag = 1;
}
void process_busoff_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if(busoffFlag == 1)
    {
        canMessageReFlag = 0;
        if(busoffFast <5)
        {
            busoffTimes ++;
            if(busoffTimes >=10)
            {
                busoffFast ++;
                busoffTimes = 0;
                busoffFlag  = 0;
                can_controller_init_fml_api(0);
                set_can_controller_mode_fml_api(CANFML_CS_STARTED);
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"can fast bus off");

            }
        }
        else
        {
            busoffTimes ++;
            if(busoffTimes >=100)
            {
                busoffFast = 0;
                busoffTimes = 0;
                busoffFlag  = 0;
                can_controller_init_fml_api(0);
                set_can_controller_mode_fml_api(CANFML_CS_STARTED);
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"can slow bus off");
            }
        }
    }
    else
    {
        if(canMessageReFlag == 1)
        {
            busoffFast = 0;
        }
    }
}
static void check_NM_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if (nmActive == 1)
    {
        if(nmTimeoutCnt++ >=100)
        {
            nmTimeoutCnt = 0;
            nmActive = 0;
        }
    }
}

void canstack_init_fml_api(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_Init();       /* Init FlexCAN0 */
    CanIf_Init();
    set_can_controller_mode_fml_api(CANFML_CS_STARTED);
#ifndef OSEK_NM
    CanNm_Init();
#else
    CanNm_Init_osek();
#endif
    CanTp_Init(&CanTp_Cfg);
    Dcm_Init(NULL_PTR);
    Com_Init();
    Com_RxStart();
    Com_TxStart();
    CanNm_NetworkRequest(0);
    int_sys_enable_irq_hal_api(CAN0_0_15_MB_VECTOR);
    int_sys_enable_irq_hal_api(CAN0_16_31_MB_VECTOR);
    int_sys_enable_irq_hal_api(CAN0_BUSOFF_VECTOR);
    int_sys_set_priority_hal_api(CAN0_ORed_0_15_MB_IRQn, 0x01);
    int_sys_set_priority_hal_api(CAN0_ORed_16_31_MB_IRQn, 0x01);
}

void canstack_wakeup_init_fml_api(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_Init();       /* Init FlexCAN0 */
    set_can_controller_mode_fml_api(CANFML_CS_STARTED);
#ifndef OSEK_NM
    //CanNm_Init();
#else
    CanNm_Init_osek();
#endif
    CanTp_Init(&CanTp_Cfg);
    Dcm_Init(NULL_PTR);
    Com_Init();
    Com_RxStart();
    Com_TxStart();
//    CanNm_NetworkRequest(0);
    int_sys_enable_irq_hal_api(CAN0_0_15_MB_VECTOR);
    int_sys_enable_irq_hal_api(CAN0_16_31_MB_VECTOR);
    int_sys_enable_irq_hal_api(CAN0_BUSOFF_VECTOR);
    int_sys_set_priority_hal_api(CAN0_ORed_0_15_MB_IRQn, 0x01);
    int_sys_set_priority_hal_api(CAN0_ORed_16_31_MB_IRQn, 0x01);
}

void can_run_function_fml_api(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if(busoffFlag == 0)
    {

    }
    Com_MainFunctionTx();
    Com_MainFunctionRx();
    CanTp_MainFunction();
    Dcm_MainFunction();
    //CanNm_MainFunction();
   // process_busoff_fml();
}

void sleep_can_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    can_controller_init_fml_api(0);
    set_can_controller_mode_fml_api(CANFML_CS_SLEEP);
}
void wakeup_can_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    can_controller_init_fml_api(0);
    set_can_controller_mode_fml_api(CANFML_CS_STARTED);
}

void debug_nm_fuction_fml(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    /*------------------------OSEK NM---------------------------*/

    if((accStatus != 0)||(networkFlag == 1))
    {
        CanNm_GotoMode(0,GOTO_AWAKE);
        Com_RxStart();
        Com_TxStart();

        if(networkFlag == 1)
        {
            networkFlag=0;
        }
    }
    else
    {
        CanNm_GotoMode(0,GOTO_BUSSLEEP);
    }
}


static uint16_t fill_can_buffer_fml(flexcan_msgbuff_spi_t *rxmsgsub,uint32_t count)
 {
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint16_t countptr=0;
    uint16_t i,j;
    uint32_t seconds,micsecond;
    countptr=0;
    for(j=0;j<count;j++)
    {
        seconds = get_rtc_seconds_fml();
        micsecond = get_rtc_micseconds_fml();
        spiCanBuffer[countptr]   = 0x73;
        spiCanBuffer[countptr+1] = 0x4f;
        spiCanBuffer[countptr+2] = 9+rxmsgsub[j].dataLen;
        spiCanBuffer[countptr+3] = (uint8_t)(seconds>>24);
        spiCanBuffer[countptr+4] = (uint8_t)(seconds>>16);
        spiCanBuffer[countptr+5] = (uint8_t)(seconds>>8);
        spiCanBuffer[countptr+6] = (uint8_t)seconds;
        spiCanBuffer[countptr+7] = (uint8_t)(micsecond>>8);
        spiCanBuffer[countptr+8] = (uint8_t)micsecond;
        spiCanBuffer[countptr+9] = rxmsgsub[j].msgId[1];
        spiCanBuffer[countptr+10] = rxmsgsub[j].msgId[0];
        spiCanBuffer[countptr+11]= rxmsgsub[j].dataLen;
        for(i = 0;i < rxmsgsub[j].dataLen;i++)
        {
            spiCanBuffer[countptr+12+i] = rxmsgsub[j].data[i];
        }
        countptr += (12+rxmsgsub[j].dataLen);
    }
    return countptr;
}
uint8_t systemPowerMode;
uint8_t antiThelfStatus = antiTheftDefaut;
uint8_t FLDoorStatus;

uint8_t read_can_Ringbuffer_fml_api(void)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint16_t canlen;
    int i,j;
    uint8_t rxcanIndex = 0;
    canlen = can_ring_read_fml(canRingbufferRxData);
    if(canlen == 0)
    {
        return 0;
    }
    canRingCount ++;
    for(i =0;i<(canlen/11);i++)
    {
        if(i>29)
        {
            break;
        }
        if((canRingbufferRxData[0+i*11] == 0x03)&&(canRingbufferRxData[1+i*11] == 0x10))
        {
            if(systemPowerMode != (canRingbufferRxData[3+i*11]&0x03))
            {
#if COM_VEHICLE_FML
                Printf("powermode\r\n");
#endif
                systemPowerMode = canRingbufferRxData[3+i*11]&0x03;
                ps_flush(igsSwSub);
                PUB_INT_FL("systemPowerMode", (systemPowerMode), FL_STICKY);
            }
            if(antiThelfStatus != ((canRingbufferRxData[3+i*11]>>2)&0x03))
            {
#if COM_VEHICLE_FML
                Printf("antiThelfStatus\r\n");
#endif
                antiThelfStatus = (canRingbufferRxData[3+i*11]>>2)&0x03;
                ps_flush(antiThelSub);
                PUB_INT_FL("antiThelfStatus", (antiThelfStatus), FL_STICKY);
            }//FLDoorStatus
            if(FLDoorStatus != ((canRingbufferRxData[6+i*11])&0x03))
            {
#if COM_VEHICLE_FML
                Printf("FLDoorStatus\r\n");
#endif
            	FLDoorStatus = (canRingbufferRxData[6+i*11])&0x03;
            	ps_flush(FLDoorsSub);
                PUB_INT_FL("FLDoorStatus", (FLDoorStatus), FL_STICKY);
            }
        }
        msgRxCanBuffer[i].msgId[0]=canRingbufferRxData[0+i*11];
        msgRxCanBuffer[i].msgId[1]=canRingbufferRxData[1+i*11];
        msgRxCanBuffer[i].dataLen =canRingbufferRxData[2+i*11];
        for(j=0;j<8;j++)
        {
            msgRxCanBuffer[i].data[j] = canRingbufferRxData[3+j];
        }
    }
    rxcanIndex = (canlen/11);
    if(rxcanIndex >29)
    {
        rxcanIndex = 29;
    }
    canPakageLen = fill_can_buffer_fml(msgRxCanBuffer,rxcanIndex);
    spi_ring_write_fml(spiCanBuffer,canPakageLen );
    canPakageLen = 0;
    readRingbufferEn = 1;
}

void push_can_data_fml(uint16_t id,uint8_t *ptr)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    switch(id)
    {
        case 0x2A2:
            memcpy(TxIpduNew_Message_21._c, ptr, 8);
            break;
        case 0x2DD:
            memcpy(TxIpduNew_Message_22._c, ptr, 8);
            break;
        case 0x2DE:
            memcpy(TxIpduNew_Message_23._c, ptr, 8);
            break;
        case 0x2DF:
            memcpy(TxIpduNew_Message_24._c, ptr, 8);
            break;
        case 0x2E1:
            memcpy(TxIpduNew_Message_25._c, ptr, 8);
            break;
        case 0x2E2:
            memcpy(TxIpduNew_Message_26._c, ptr, 8);
            break;
        case 0x2FE:
            memcpy(TxIpduNew_Message_27._c, ptr, 8);

            break;
        case 0x2FF:
            memcpy(TxIpduNew_Message_28._c, ptr, 8);
            break;
        case 0x3A2:
            memcpy(TxIpduNew_Message_29._c, ptr, 8);
            break;
        case 0x3A3:
            memcpy(TxIpduNew_Message_30._c, ptr, 8);
            break;
        case 0x3A4:
            memcpy(TxIpduNew_Message_31._c, ptr, 8);
            break;
        case 0x3A5:
            memcpy(TxIpduNew_Message_32._c, ptr, 8);
            break;
        case 0x3A7:
            memcpy(TxIpduNew_Message_33._c, ptr, 8);
            break;
        case 0x556:
            memcpy(TxIpduNew_Message_34._c, ptr, 8);
            break;
        case 0x5D0:
            memcpy(TxIpduPLG_General_Status._c, ptr, 8);
            break;
    default:
        break;
    }
}

uint8_t set_can_controller_mode_fml_api(canControllerModeTypeFml mode)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    return CanIf_SetControllerMode(0,mode);
}
void can_controller_init_fml_api(uint8_t channel)
{
#if VEHICLE_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_InitController(channel, 0);
}







