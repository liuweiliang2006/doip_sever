/*
 * uds.c
 *
 *  Created on: 2020Äê11ÔÂ19ÈÕ
 *      Author: Administrator
 */
#include "ComStack_Types_Cfg.h"
#include "ComStack_Types.h"
#include "CanIf_Type.h"
#include "Can_Pl.h"
#include "Can.h"
#include "CanIf.h"
#include "interrupt_manager.h"

#include "Dcm.h"
#include "CanTp.h"
#include "OsekNm.h"
#include "Com.h"
#include <stddef.h>
#include <string.h>
#include <status.h>
#include "FreeRTOS.h"
#include "com_task.h"

extern  uint32 SupportedDTC[NUM_OF_DTC];
extern uint8 DTCStatus[NUM_OF_DTC];
uint8 DTCStatusBak[NUM_OF_DTC];
uint8_t dig2EServiceActive;
extern uint8 DATA_0xF18A[7];
extern uint8 DATA_0xF187[10];
extern uint8 DATA_0xF18B[4];
extern uint8 DATA_0xF18C[8];
extern uint8 DATA_0xF190[17];
extern uint8 DATA_0xF198[16];
extern uint8 DATA_0xF19D[4];
extern uint8 DATA_0xF192[16];
extern uint8 DATA_0xF193[4];
extern uint8 DATA_0xF194[16];
extern uint8 DATA_0xF195[4];
extern uint8 DATA_0x2001[4];
#define DATA_0xF190INDEX 4
#define DATA_0xF198INDEX 9
#define DATA_0xF19DINDEX 10
#define DATA_0x2001INDEX 11

status_t write_to_EEfalsh_fml(uint8_t *ptr,uint16_t len,uint8_t index)
{
    uint32_t address;
    uint32_t size;
    status_t ret;
    address = flashSSDConfig.EERAMBase+0x10+0x200*index;
    size = len;

    ret = flash_eeprom_write_hal_api(address, size, ptr);
    DEV_ASSERT(STATUS_SUCCESS == ret);
    return STATUS_SUCCESS;
}

uint8_t dtcMempry[400];
void write_DTCdata_to_EEflash_fml(void)
{
    uint16_t i;
    for(i=0;i<NUM_OF_DTC;i++)
    {
        dtcMempry[0+4*i] = SupportedDTC[i]>>16;
        dtcMempry[1+4*i] = SupportedDTC[i]>>8;
        dtcMempry[2+4*i] = SupportedDTC[i];
        dtcMempry[3+4*i] = DTCStatus[i];
    }
    write_to_EEfalsh_fml((uint8_t *)&dtcMempry,400,1);
}
void read_DTCdata_from_dflash_fml(void)
{
    uint16_t i;
    for(i=0;i<400;i++)
    {
        dtcMempry[i] = *((uint32_t *)(DFLASH_START_ADDRESS+4096*2+i));
    }

    for(i=0;i<NUM_OF_DTC;i++)
    {
        SupportedDTC[i] |= dtcMempry[0+4*i]<<16;
        SupportedDTC[i] |= dtcMempry[1+4*i]<<8;
        SupportedDTC[i] |= dtcMempry[2+4*i]<<0;
        DTCStatus[i]     = dtcMempry[3+4*i];
    }

}
uint8_t didMempry[12][20];
/*
 * DATA_0xF18A 0
 * DATA_0xF187 1
 * DATA_0xF18B 2
 * DATA_0xF18C 3
 * DATA_0xF190 4
 * DATA_0xF192 5
 * DATA_0xF193 6
 * DATA_0xF194 7
 * DATA_0xF195 8
 * DATA_0xF198 9
 * DATA_0xF19D 10
 * DATA_0x2001 11
 * */

void write_DIDdata_to_EEflash_fml(void)
{
    uint8_t i;
    for(i=0;i<7;i++)
    {
        didMempry[0][i] = DATA_0xF18A[i];
    }
    for(i=0;i<10;i++)
    {
        didMempry[1][i] = DATA_0xF187[i];
    }
    for(i=0;i<4;i++)
    {
        didMempry[2][i] = DATA_0xF18B[i];
    }
    for(i=0;i<8;i++)
    {
        didMempry[3][i] = DATA_0xF18C[i];
    }
    for(i=0;i<17;i++)
    {
        didMempry[4][i] = DATA_0xF190[i];
    }
    for(i=0;i<16;i++)
    {
        didMempry[5][i] = DATA_0xF192[i];
    }
    for(i=0;i<4;i++)
    {
        didMempry[6][i] = DATA_0xF193[i];
    }
    for(i=0;i<16;i++)
    {
        didMempry[7][i] = DATA_0xF194[i];
    }
    for(i=0;i<4;i++)
    {
        didMempry[8][i] = DATA_0xF195[i];
    }
    for(i=0;i<16;i++)
    {
        didMempry[9][i] = DATA_0xF198[i];
    }
    for(i=0;i<4;i++)
    {
        didMempry[10][i] = DATA_0xF19D[i];
    }
    for(i=0;i<4;i++)
    {
        didMempry[11][i] = DATA_0x2001[i];
    }
    write_to_EEfalsh_fml((uint8_t *)&didMempry,240,0);
}
uint8_t mcu_spi_package_did2001(uint8_t * Buffer)
{
    uint8_t i;
    Buffer[0] = 0x73;
    Buffer[1] = 0x51;
    Buffer[2] = sizeof(DATA_0x2001)+1;
    Buffer[3] = 0;
    for(i=0;i<4;i++)
    {
        Buffer[4+i] = DATA_0x2001[i];
    }
    return sizeof(DATA_0x2001)+4;
}
uint8_t mcu_spi_package_didF187(uint8_t * Buffer)
{
    uint8_t i;
    Buffer[0] = 0x73;
    Buffer[1] = 0x51;
    Buffer[2] = sizeof(DATA_0xF187)+1;
    Buffer[3] = 1;
    for(i=0;i<sizeof(DATA_0xF187);i++)
    {
        Buffer[4+i] = DATA_0xF187[i];
    }
    return sizeof(DATA_0xF187)+4;
}
uint8_t mcu_spi_package_didF18A(uint8_t * Buffer)
{
    uint8_t i;
    Buffer[0] = 0x73;
    Buffer[1] = 0x51;
    Buffer[2] = sizeof(DATA_0xF18A)+1;
    Buffer[3] = 2;
    for(i=0;i<sizeof(DATA_0xF18A);i++)
    {
        Buffer[4+i] = DATA_0xF18A[i];
    }
    return sizeof(DATA_0xF18A)+4;
}
uint8_t mcu_spi_package_didF190(uint8_t * Buffer)
{
    uint8_t i;
    Buffer[0] = 0x73;
    Buffer[1] = 0x51;
    Buffer[2] = sizeof(DATA_0xF190)+1;
    Buffer[3] = 3;
    for(i=0;i<sizeof(DATA_0xF190);i++)
    {
        Buffer[4+i] = DATA_0xF190[i];
    }
    return sizeof(DATA_0xF190)+4;
}
void read_udsData_fml_api(void)
{
    uint32_t i;
    uint8_t temp[2];
    uint32_t address;
    address = flashSSDConfig.EERAMBase+0x10;
    temp[0] = *((uint32_t *)(address));
    if(temp[0] != 0xFF)
    {
        for(i=0;i<17;i++)
        {
            DATA_0xF190[i] = *((uint32_t *)(address+i+20*DATA_0xF190INDEX));
        }
        uart_printf_data_fml_api(UARTTASKPRINT,DATA_0xF190,10,__FUNCTION__,",90");
        for(i=0;i<16;i++)
        {
            DATA_0xF198[i] = *((uint32_t *)(address+i+20*DATA_0xF198INDEX));
        }
        uart_printf_data_fml_api(UARTTASKPRINT,DATA_0xF198,10,__FUNCTION__,",98");

        for(i=0;i<4;i++)
        {
            DATA_0xF19D[i] = *((uint32_t *)(address+i+20*DATA_0xF19DINDEX));
        }

        uart_printf_data_fml_api(UARTTASKPRINT,DATA_0xF19D,4,__FUNCTION__,",9D");
        for(i=0;i<4;i++)
        {
            DATA_0x2001[i] = *((uint32_t *)(address+i+20*DATA_0x2001INDEX));
        }
        uart_printf_data_fml_api(UARTTASKPRINT,DATA_0x2001,4,__FUNCTION__,",2001");
    }
}
void read_dtcData_fml_api(void)
{
    uint16_t i;
    uint8_t temp;
    uint32_t address;
    address = flashSSDConfig.EERAMBase+0x10+0x200;
    temp = *((uint32_t *)(address));
    if(temp != 0xFF)
    {
        for(i=0;i<400;i++)
        {
            dtcMempry[i] = *((uint32_t *)(address+i));
        }
        for(i=0;i<NUM_OF_DTC;i++)
        {
            DTCStatus[i] = dtcMempry[3+4*i];
        }
        for(i=0;i<NUM_OF_DTC;i++)
        {
            DTCStatusBak[i]= DTCStatus[i];
        }
        uart_printf_data_fml_api(UARTTASKPRINT,DTCStatus,10,__FUNCTION__,",dst");

    }

}
uint8_t DTCStatusChange;
void check_did_dtc_status_fml_api(uint8_t status)
{
    int j;
    for(j=0;j<NUM_OF_DTC;j++)
    {
        if(DTCStatusBak[j] != DTCStatus[j])
        {
            DTCStatusChange = 1;
            DTCStatusBak[j]= DTCStatus[j];
        }
    }
     if(DTCStatusChange == 1)
     {
        DTCStatusChange =0;
        DISENABLE_IRQ_GLOBAL;
        write_DTCdata_to_EEflash_fml();
        ENABLE_IRQ_GLOBAL;
     }
     if((status == 0x02)||(status == 0x03))
     {
         if(dig2EServiceActive == true)
         {
             dig2EServiceActive = false;
             write_DIDdata_to_EEflash_fml();
         }
     }
}



