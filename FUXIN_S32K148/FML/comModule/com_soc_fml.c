/*
 * fml_spi.c
 *
 *  Created on: 2021Äê5ÔÂ25ÈÕ
 *      Author: Administrator
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "Cpu.h"
#include "com_task.h"
#include <string.h>

#include "pwrmanage_apl.h"

#define COM_SOC_DEBUG 1

static uint16_t check_resend_frame_fml(void);
uint8_t blankFrame[6] = {0xFF,0XA5,0X5A,0,0xFE,0xFE};
uint8_t shakeFrame[6] = {0xFF,0XA5,0X5A,0,0xFE,0xDF};
uint8_t ackFrame[6] = {0xFF,0XA5,0X5A,0,0xFF,0xFF};
status_t slaveTransferStatus;
uint8_t spiReceiveTimeout;
uint8_t spiReceiveTimeoutEn;
uint8_t spiRunStep;
uint8_t startUpdateFlag;
spi_buffer_t slaveBuffer;
uint8_t spiReceiveBuffer[512] ;
uint8_t spiAckHander[3];
static uint8_t frameTure;
uint8_t spiForCanIndex;
uint8_t can2DETimes[10];
extern uint8_t tempTestData[20];
typedef struct {
    uint8_t index;
    uint16_t start_id;
    uint16_t len;
}component_ring_t;
component_ring_t spiFrameInfo[128];
uint8_t readSpiRingbufferData[1024];
uint8_t spiWork;
uint8_t spiTimeoutOdlid[3]={0xaa,0xaa,0xaa};
uint8_t spiTimeoutId[3]={0xaa,0xaa,0xaa};
uint8_t ackTimeoutTimes[3];
uint8_t spiTimeoutFlag;
spi_cp_buffer_t spiStoreSendData[3];
spi_tx_buffer_t spiTimeoutBuffer;
uint8_t shakeHandsOk;
uint8_t spiMsgId=0;
uint8_t spiQueueIndex;
uint8_t didInfor[24];
uint8_t spiFrameId;
uint8_t socAndMcuConnecting;
typedef struct {
    uint8_t data[8];                   /*!< Data bytes of the FlexCAN message*/
    uint8_t msgId[2];                     /*!< Message Buffer ID*/
    uint8_t dataLen;                    /*!< Length of data in bytes */
    uint8_t fuc0;
    uint8_t fuc1;
    uint8_t data_packlen;
} rx_msgbuff_spi_t;
rx_msgbuff_spi_t spiDataForCan[10]={
    {
        .dataLen=8,
    },
};


uint16_t shake_step_receive_soc_process_fml_api(uint32_t value)
{
    if(value == 0x02)
    {
        package_spi_nodata_frame_fml(&slaveBuffer,blankFrame);
    }
    else if(value == 0x01)
    {
        package_spi_nodata_frame_fml(&slaveBuffer,shakeFrame);
    }
    else
    {
        ;
    }
    return SPI_MIN_LEN;
}
uint16_t normal_step_receive_soc_process_fml_api(uint32_t value)
{
    uint16_t len;
    uint16_t txCount = 0;
    uint8_t ulReceivedU8;
    if(value == 0x02)
    {
        if(spiAckHander[0] == 1)
        {
            ackFrame[3] = spiAckHander[2];
            package_spi_nodata_frame_fml(&slaveBuffer,ackFrame);
            spiAckHander[0] = 0;
            len =512;
            frameTure =1;
        }
        else
        {
            if(xQueueReceive( spiRingbufferQueue, &ulReceivedU8, 0 ))
            {
                frameTure =1;
                len = copy_slave_buffer_tx_fml(ulReceivedU8);
            }
        }
        if(frameTure == 0)
        {
            package_spi_nodata_frame_fml(&slaveBuffer,blankFrame);
            len =SPI_MIN_LEN;
        }
        else
        {
            frameTure = 0;
        }
    }
    else if(value == 0x03)
    {
        if(spiAckHander[0] == 1)
        {
            ackFrame[3] = spiAckHander[2];
            package_spi_nodata_frame_fml(&slaveBuffer,ackFrame);
            spiAckHander[0] = 0;
            len =SPI_MIN_LEN;
        }
    }
    else if((value&0xff) == 0x04)
    {
        txCount = check_resend_frame_fml();
        if(txCount != 0)
        {
            len = txCount;
            if(len <= 512)
            {
                len =512;
            }
            else if(len >1024)
            {
                len =1024;
            }
            else
            {
                ;
            }
        }
        else
        {
            if(xQueueReceive( spiRingbufferQueue, &ulReceivedU8, 0 ))
            {
                len = copy_slave_buffer_tx_fml(ulReceivedU8);
            }
            else
            {
                package_spi_nodata_frame_fml(&slaveBuffer,blankFrame);
                len =SPI_MIN_LEN;
            }
        }
    }
    else if((value&0xff) == 0x09)
    {
        package_version_fml(&slaveBuffer);
        len =SPI_MIN_LEN;
    }
    else if((value&0xff) == 0x0A)
    {
        package_did_fml(&slaveBuffer);
        len =SPI_MIN_LEN;
    }
    else
    {
        ;
    }
    return len;
}
void package_spi_nodata_frame_fml(spi_buffer_t * spiBuffer,uint8_t *data)
{
    uint16_t cnt;
    for(cnt = 0U; cnt < 512; cnt++)
    {
        spiBuffer->tx[cnt] = 0;
    }
    for(cnt = 0U; cnt < 6; cnt++)
    {
        spiBuffer->tx[cnt] = data[cnt];
    }
    spiBuffer->tx[6] = spiBuffer->tx[3]^spiBuffer->tx[4]^spiBuffer->tx[5];
}
void spi_intr_soc_fml(uint8_t delay)
{
    uint8_t PDIO;
    PDIO = 17;
    if(delay == 1)
        vTaskDelay(1/portTICK_PERIOD_MS);
    PINS_DRV_ClearPins(LED_GPIO, (1 << PDIO));
    vTaskDelay(1/portTICK_PERIOD_MS);
}

status_t spi_slave_transfer_fml(uint16_t len)
{
     slaveTransferStatus = lpspi_slave_transfer_hal_api(1, slaveBuffer.tx,slaveBuffer.rx, len);
     return slaveTransferStatus;
}

void start_spi_Transfer_fml_api(uint16_t len)
{
    uint32_t txcount=0;
    uint8_t retry = 0;
    while(1)
    {
        if(len >= SPI_MAX_LEN)
        {
            len = SPI_MAX_LEN;
        }
        slaveTransferStatus = spi_slave_transfer_fml(len) ;
        if(STATUS_SUCCESS == slaveTransferStatus)
        {
            spiWork = 1;
            spiReceiveTimeoutEn = 1;
            spiReceiveTimeout = 0;
            spi_intr_soc_fml(0);
            retry = 0;
            break;

        }
        else
        {
            vTaskDelay(1/portTICK_PERIOD_MS);
            retry ++;
            if(retry >100)
            {
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"spi busy");
                retry = 0;
                break;
            }
        }
    }
    while(retry < 15)
    {
        slaveTransferStatus = lpspi_slave_get_transfer_status_hal_api(1,&txcount);
        if(slaveTransferStatus == STATUS_SUCCESS )
        {
            retry =0;

            break;
        }
        else
        {
            vTaskDelay(1/portTICK_PERIOD_MS);
            if(retry == 14)
            {
                ;
            }
            retry ++;

        }
    }
    retry =0;
}

static uint16_t check_resend_frame_fml(void)
{
    int i;
    uint16_t return_value;
    return_value = 0;
    if(spiTimeoutBuffer.full == 1)
    {
        spiTimeoutBuffer.full = 0;
        //PINS_DRV_TogglePins(LED_GPIO, (1 << 23));
        return_value = spiTimeoutBuffer.len;
        memcpy((uint8_t *)&slaveBuffer.tx[0], spiTimeoutBuffer.data, 1024);
        for(i=0;i<3;i++)
        {
            if(spiStoreSendData[i].full == 0)
            {
                spiStoreSendData[i].full = 1;
                spiStoreSendData[i].spiId = slaveBuffer.tx[3];
                spiStoreSendData[i].frame_len = return_value;
                memcpy((uint8_t *)&spiStoreSendData[i].dataCopy, slaveBuffer.tx, return_value);

                break;
            }
        }
    }
    return return_value;
}

void spi_timeout_process_fml_api(void)
{
    int i;
    unsigned long ulReceivedValue=0;
    if(spiReceiveTimeoutEn == 1)
    {
        spiReceiveTimeout++;
        if(spiReceiveTimeout >100)
        {
            clear_send_data_timeout_fml();
            for(i=0;i<3;i++)
            {
                if(spiStoreSendData[i].full == 1)
                {
                    if(slaveBuffer.tx[3] == spiStoreSendData[i].spiId)
                    {
                        break;
                    }
                }
            }
            uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"spi timeout");
            if(xQueuePeek(spiQueue,&ulReceivedValue,0))
            {
                xQueueReceive(spiQueue,&ulReceivedValue,0);
            }
        }
    }
    for(i=0;i<3;i++)
    {
        if(spiStoreSendData[i].full == 1)
        {
            spiTimeoutId[i] = spiStoreSendData[i].spiId;
        }
        else
        {
            spiTimeoutId[i] = 0xaa;
        }
    }
    for(i=0;i<3;i++)
    {
        if(spiTimeoutOdlid[i] != spiTimeoutId[i])
        {
            spiTimeoutOdlid[i] = spiTimeoutId[i];
            ackTimeoutTimes[i] = 0;

        }
        else
        {
            if(spiTimeoutOdlid[i] != 0xaa)
            {
                spiTimeoutFlag =  1;
                ackTimeoutTimes[i] += 1;
            }
        }
    }
    if(spiTimeoutFlag == 1)
    {
        spiTimeoutFlag = 0;
        if(ackTimeoutTimes[0]>100)
        {
            uart_printf_data_fml_api(UARTTASKPRINT,&spiTimeoutId[0],1,__FUNCTION__,",ack_id");
            uart_printf_data_fml_api(UARTTASKPRINT,ackTimeoutTimes,3,__FUNCTION__,",ack_time");
            pins_toggle_pins_hal_api(LED_GPIO,1 << LED2);
            ackTimeoutTimes[0] =0;
            for(i=0;i<3;i++)
             {
                 if(spiStoreSendData[i].full == 1)
                 {
                     if(spiStoreSendData[i].spiId == spiTimeoutId[0])
                     {
                         spiStoreSendData[i].full = 0;
                         spiStoreSendData[i].spiId = 0;
                         if(spiStoreSendData[i].frame_len>1024)
                         {
                             spiStoreSendData[i].frame_len = 1024;
                         }
                         memcpy((uint8_t *)spiTimeoutBuffer.data, spiStoreSendData[i].dataCopy, spiStoreSendData[i].frame_len);
                         spiTimeoutBuffer.full = 1;
                         spiTimeoutBuffer.len = spiStoreSendData[i].frame_len;
                         break;
                     }
                 }
             }
        }
        if(ackTimeoutTimes[1]>100)
        {
            uart_printf_data_fml_api(UARTTASKPRINT,&spiTimeoutId[1],1,__FUNCTION__,",ack_id1");
            uart_printf_data_fml_api(UARTTASKPRINT,ackTimeoutTimes,3,__FUNCTION__,",ack_time1");
            pins_toggle_pins_hal_api(LED_GPIO,1 << LED2);
            ackTimeoutTimes[1] =0;
            for(i=0;i<3;i++)
            {
                if(spiStoreSendData[i].full == 1)
                {
                    if(spiStoreSendData[i].spiId == spiTimeoutId[1])
                    {
                        spiStoreSendData[i].full = 0;
                        spiStoreSendData[i].spiId = 0;
                        if(spiStoreSendData[i].frame_len>1024)
                        {
                            spiStoreSendData[i].frame_len = 1024;
                        }
                        memcpy((uint8_t *)spiTimeoutBuffer.data, spiStoreSendData[i].dataCopy, spiStoreSendData[i].frame_len);
                        spiTimeoutBuffer.full = 1;
                        spiTimeoutBuffer.len = spiStoreSendData[i].frame_len;
                        break;
                    }
                }
            }
        }
        if(ackTimeoutTimes[2]>100)
        {
//            uart_printf_data_fml_api(UARTTASKPRINT,&spiTimeoutId[2],1,__FUNCTION__,",ack_id2");
//            uart_printf_data_fml_api(UARTTASKPRINT,ackTimeoutTimes,3,__FUNCTION__,",ack_time2");
            pins_toggle_pins_hal_api(LED_GPIO,1 << LED2);
            ackTimeoutTimes[2] =0;
            for(i=0;i<3;i++)
            {
                if(spiStoreSendData[i].full == 1)
                {
                     if(spiStoreSendData[i].spiId == spiTimeoutId[2])
                     {
                         spiStoreSendData[i].full = 0;
                         spiStoreSendData[i].spiId = 0;
                         if(spiStoreSendData[i].frame_len>1024)
                         {
                             spiStoreSendData[i].frame_len = 1024;
                         }
                         memcpy((uint8_t *)spiTimeoutBuffer.data, spiStoreSendData[i].dataCopy, spiStoreSendData[i].frame_len);
                         spiTimeoutBuffer.full = 1;
                         spiTimeoutBuffer.len = spiStoreSendData[i].frame_len;
                         break;
                     }
                }
            }
        }
    }    
}

void spi_slave_callback(void *driverState, spi_event_t event, void *userData)
{
    unsigned long ulValueToSend = 99UL;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    int i;
    ulValueToSend =99;
    pins_set_pins_hal_api(LED_GPIO, (1 << 17));//jialin
    if(spiRunStep == Shake_hands)
    {
        spiWork = 0;
        spiReceiveTimeout = 0;
        spiReceiveTimeoutEn = 0;
        for(i=0;i<16;i++)
        {
            spiReceiveBuffer[i] = slaveBuffer.rx[i];
        }
        if((spiReceiveBuffer[3]==0x0)&&(spiReceiveBuffer[4]==0xFE)&&(spiReceiveBuffer[5]==0xFD)&&(spiReceiveBuffer[6]==0x03))
        {
            uart_printf_char_fml_api(UARTISRPRINT,__FUNCTION__,"hand re");
            ulValueToSend = 0x01;
            xQueueSendToBackFromISR(spiQueue, &ulValueToSend, &xHigherPriorityTaskWoken);
        }
        if((spiReceiveBuffer[4]==0xFE)&&(spiReceiveBuffer[5]==0xFE))
        {
            spiRunStep = spi_com_normal;
            shakeHandsOk = true;
            uart_printf_char_fml_api(UARTISRPRINT,__FUNCTION__,"Shake_hands ok");
        }
    }
    if(spiRunStep == spi_com_normal)
    {
        spiWork = 0;
        spiReceiveTimeout = 0;
        spiReceiveTimeoutEn = 0;
        for(i=0;i<10;i++)
        {
            spiReceiveBuffer[i] = slaveBuffer.rx[i];
        }
        if((spiReceiveBuffer[4]==0xFF)&&(spiReceiveBuffer[5]==0xFF))
        {
            for(i=0;i<3;i++)
            {
                if(spiStoreSendData[i].full == 1)
                {
                    if(spiStoreSendData[i].spiId == spiReceiveBuffer[3])
                    {
                        spiStoreSendData[i].full = 0;
                        spiStoreSendData[i].spiId = 0;
                        break;
                    }
                }
            }
        }
        else if((spiReceiveBuffer[4]==0xFE)&&(spiReceiveBuffer[5]==0xFE))
        {
            ;
        }
        else if((spiReceiveBuffer[4]==0)&&(spiReceiveBuffer[5]==0))
        {
            ;
        }
        else if((spiReceiveBuffer[3]==0x0)&&(spiReceiveBuffer[4]==0xFE)&&(spiReceiveBuffer[5]==0xFD)&&(spiReceiveBuffer[6]==0x03))
        {
            uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"hand re");
            ulValueToSend = 0x01;
            spiRunStep = Shake_hands;
            xQueueSendToBackFromISR(spiQueue, &ulValueToSend, &xHigherPriorityTaskWoken);
        }
        else
        {
            spiAckHander[0]=1;
            spiAckHander[1]=3;
            spiAckHander[2]=spiReceiveBuffer[3];
            ulValueToSend = SPICALLBACK;
            xQueueSendToBackFromISR(spiCallbackQueue, &ulValueToSend, &xHigherPriorityTaskWoken);
            ulValueToSend = 0x03;
            if(xQueueSendToBackFromISR( spiQueue, &ulValueToSend, &xHigherPriorityTaskWoken ))
            {
                ;
            }
            else
            {
#if UARTlog
                uint8_t temp_char[2];
                char print_msg[32]={"  spiQueue full"};
                unsigned long ulReceivedValue=0;
                xQueuePeekFromISR(spiQueue,&ulReceivedValue);
                //uart_log_printf_isr_fml("uartrx: 0x%x", uart_recv[index][4]);
                 put_hex_fml( (uint8_t)ulReceivedValue ,temp_char);
                 print_msg[0]= temp_char[0];
                 print_msg[1]= temp_char[1];
                 uart_printf_char_fml_api(UARTTASKPRINT,&print_msg[0]);
#endif
            }
        }
    }

}
/*-----------------------------------------------------------*/
uint16_t copy_slave_buffer_tx_fml(uint8_t data)
{
    uint16_t len;
    int i;
    uint16_t rbAddress;
    len = spiFrameInfo[data].len;
    rbAddress = rb_get_head(&wholePackageSpirbTx);;
    if(rbAddress  != spiFrameInfo[data].start_id)
    {
        tempTestData[0]=rbAddress>>8;
        tempTestData[1]=rbAddress>>0;
        tempTestData[2]=spiFrameInfo[data].start_id>>8;
        tempTestData[3]=spiFrameInfo[data].start_id>>0;
        tempTestData[3] = data;
        uart_printf_data_fml_api(UARTTASKPRINT,tempTestData,5,__FUNCTION__,",add err");
    }
    len = whole_package_spiring_read_fml(&readSpiRingbufferData[0],spiFrameInfo[data].len);
    if(len >1024)
    {
        len = 1024;
    }
    if(len == spiFrameInfo[data].len)
    {
        memcpy((uint8_t *)&slaveBuffer.tx[0], readSpiRingbufferData, len);
    }
    else
    {
        uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"ring len err");
    }
    for(i=0;i<3;i++)
    {
        if(spiStoreSendData[i].full == 0)
        {
            spiStoreSendData[i].full = 1;
            spiStoreSendData[i].spiId = slaveBuffer.tx[3];
            spiStoreSendData[i].frame_len = len;
            memcpy((uint8_t *)&spiStoreSendData[i].dataCopy, slaveBuffer.tx, len);
            break;
        }
    }
    if(len<512)
    {
        memset((uint8_t *)&slaveBuffer.tx[len], 0, 512-len);
        len = 512;
    }
    len =ALIGN_4(len);
    return len;
}

void read_spi_ringbuffer_fml_api(void)
{
    uint16_t value=0;
    uint8_t crc=0;
    if(readRingbufferEn == 1)
    {
        value = spi_ring_read_fml(&spiTxPackage[7]);
        if((value+8) > get_write_space_fml(&wholePackageSpirbTx))
        {
            uint8_t ulReceivedU8;
            while((value+8) > get_write_space_fml(&wholePackageSpirbTx))
            {
                xQueueReceive( spiRingbufferQueue, &ulReceivedU8, 0 );
                whole_package_spiring_read_fml(&readSpiRingbufferData[0],spiFrameInfo[ulReceivedU8].len);
            }
        }
        if(((value+8) <= get_write_space_fml(&wholePackageSpirbTx))&&(value !=0))
        {
            spiFrameInfo[spiQueueIndex].len = value+8;
            spiFrameInfo[spiQueueIndex].index = spiQueueIndex;
            spiFrameInfo[spiQueueIndex].start_id= rb_start_tail(&wholePackageSpirbTx);
            spiTxPackage[0] = 0xFF;
            spiTxPackage[1] = 0xA5;
            spiTxPackage[2] = 0x5A;
            spiTxPackage[3] = spiMsgId;
            spiTxPackage[4] = (uint8_t)((value+1)>>8);
            spiTxPackage[5] = (uint8_t)((value+1));
            spiTxPackage[6] = spiTxPackage[4]^spiTxPackage[5]^(spiTxPackage[3]);
            crc = calculation_crc_fml((uint8_t *)&spiTxPackage[7], value);
            *(uint8_t *)&spiTxPackage[sizeof(com_packet_header_t)+value] = crc;
            *(uint8_t *)&spiTxPackage[sizeof(com_packet_header_t)+value+1] = 0;
            spiMsgId ++;
            if(spiMsgId >=0x80)
            {
                spiMsgId = 0;
            }
            whole_package_spiring_write_fml(spiTxPackage,value+8);
            /*uint16_t rbAddress;
            rbAddress =  rb_get_head(&wholePackageSpirbTx);
            tempTestData[0]=rbAddress>>8;
            tempTestData[1]=rbAddress>>0;
            tempTestData[2]=spiFrameInfo[spiQueueIndex].start_id>>8;
            tempTestData[3]=spiFrameInfo[spiQueueIndex].start_id>>0;
            tempTestData[4]= spiQueueIndex;
            uart_printf_data_fml_api(tempTestData,5,",add idd");*/
            if(xQueueSendToBack(spiRingbufferQueue, &spiFrameInfo[spiQueueIndex].index, 0))
            {
                ;
            }
            else
            {
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"xQ_spi_tx full");
            }
            spiQueueIndex ++;
            if(spiQueueIndex >=128)
            {
                spiQueueIndex = 0;
            }
        }
        else
        {
            if(value !=0)
            uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"big ring full");
        }
    }
}
void spi_data_to_soc_fml_api(void)
{
    unsigned long ulValueToSend = 0;
    unsigned long ulReceivedValue=0;
    uint8_t ulReceivedU8;
    if(spiRunStep == spi_com_normal)
    {
        if((spiWork == 0)&&(!xQueuePeek(spiQueue,&ulReceivedValue,0)))
        {
            if(xQueuePeek( spiRingbufferQueue, &ulReceivedU8, 0 ))
            {
                ulValueToSend = 0x04;
                if(xQueueSendToBack(spiQueue, &ulValueToSend, 0))
                {

                }
            }
            else
            {
                if(shakeHandsOk == true)
                {
                    shakeHandsOk = 0;
                    ulValueToSend = 0x0A;
                    if(xQueueSendToBack(spiQueue, &ulValueToSend, 0))
                    {
                        ;
                    }
                }
            }    
        }
    }
}

void rx_soc_data_process_fml_api(void)
{
    int i;
    unsigned long ulValueToSend = 0UL;
    unsigned long ulReceivedValue = 0;
    if(spiRunStep == spi_com_normal)
    {
        for(i=0;i<512;i++)
        {
            spiReceiveBuffer[i] = slaveBuffer.rx[i];
        }
        if((spiReceiveBuffer[4]==0xFF)&&(spiReceiveBuffer[5]==0xFF))
        {
            ;
        }
        else if((spiReceiveBuffer[4]==0xFE)&&(spiReceiveBuffer[5]==0xFE))
        {
            ;
        }
        else if((spiReceiveBuffer[4]==0)&&(spiReceiveBuffer[5]==0))
        {
            ;
        }
        else
        {
            //uart_printf_data_fml_api(&spiReceiveBuffer[7],2,",re");
            if((spiReceiveBuffer[7] == 0x54)&&(spiReceiveBuffer[8] == 0x10)&&(spiReceiveBuffer[10] == 0x1))
            {
                startUpdateFlag = 1;//51 11 01 00
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"start ota");
                update_start_fml(ulValueToSend);
                return;
            }
            if((spiReceiveBuffer[7] == 0x75)&&(spiReceiveBuffer[8] == 0x17))
            {
                ulValueToSend = 0x09;
                xQueueSendToBack( spiQueue, &ulValueToSend, 0 );
            }
            if(check_re_soc_data_crc_fml(spiReceiveBuffer))
            {
                process_soc_can_data_fml(spiReceiveBuffer);
            }
            else
            {
                uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"crc err");
            }
        }
    }
    else
    {
        ;
    }
}

uint8_t package_did_fml(spi_buffer_t * spiBuffer)
{
    uint8_t len = 0;
    uint8_t i = 0;
    uint8_t ptr = 0;
    uint8_t ID;
    ID = spiFrameId;
    if(ID == 0)
    {
        ID = 1;
        spiFrameId=1;
    }
    spiFrameId ++;
    spiBuffer->tx[0] = 0xFF;
    spiBuffer->tx[1] = 0xA5;
    spiBuffer->tx[2] = 0x5A;
    spiBuffer->tx[3] = ID;
    spiBuffer->tx[4] = 0x0;
    spiBuffer->tx[5] = 55;
    spiBuffer->tx[6] = 0x0^55^(spiBuffer->tx[3]);
    len = mcu_spi_package_did2001(didInfor);
    ptr = 7;
    for(i=0;i<len;i++)
    {
        spiBuffer->tx[ptr+i] = didInfor[i];
    }
    ptr += len;
    len = mcu_spi_package_didF187(didInfor);
    for(i=0;i<len;i++)
    {
        spiBuffer->tx[ptr+i] = didInfor[i];
    }
    ptr += len;
    len = mcu_spi_package_didF18A(didInfor);
    for(i=0;i<len;i++)
    {
        spiBuffer->tx[ptr+i] = didInfor[i];
    }
    ptr += len;
    len = mcu_spi_package_didF190(didInfor);
    for(i=0;i<len;i++)
    {
        spiBuffer->tx[ptr+i] = didInfor[i];
    }
    ptr += len;
    spiBuffer->tx[ptr] = calculation_crc_fml((uint8_t *)&spiBuffer->tx[7], ptr-7);
    uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"send did");
    return 1;
}

void package_version_fml(spi_buffer_t * spiBuffer)
{
    uint16_t cnt;
    uint8_t ID;
    ID = spiFrameId;
    if(ID == 0)
    {
        ID = 1;
        spiFrameId=1;
    }
      for(cnt = 0U; cnt < 32; cnt++)
      {
          spiBuffer->tx[cnt] = 0;
          spiBuffer->rx[cnt] = 0U;
      }
      spiBuffer->tx[0] = 0xFF;
      spiBuffer->tx[1] = 0xA5;
      spiBuffer->tx[2] = 0x5A;
      spiBuffer->tx[3] = ID;
      spiBuffer->tx[4] = 0x0;
      spiBuffer->tx[5] = 23;
      spiBuffer->tx[6] = ID^0x0^23;
      spiBuffer->tx[7] = 0x73;
      spiBuffer->tx[8] = 0x56;
      spiBuffer->tx[9] = 19;
      spiBuffer->tx[10] = 0;
      for(cnt = 0U; cnt < 18; cnt++)
      {
          spiBuffer->tx[11+cnt] = mcuVersion[cnt];
      }
      spiBuffer->tx[29] = calculation_crc_fml((uint8_t *)&spiBuffer->tx[7], 22);
      uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"version");
}

void process_soc_can_data_fml(uint8_t *pdata)
{
    int i;
    uint16_t packLen =0;
    uint16_t can_msgID;
    uint8_t start_base = 0;
    com_packet_header_t *header = (com_packet_header_t *)pdata;
    packLen = ((header->lenH)<<8) | header->lenL;
    spiForCanIndex = 0;
    uint8_t socData[4];

    while(1)
    {
        spiDataForCan[spiForCanIndex].fuc0 = pdata[sizeof(com_packet_header_t)+start_base] ;
        spiDataForCan[spiForCanIndex].fuc1 = pdata[sizeof(com_packet_header_t)+start_base + 1] ;
        spiDataForCan[spiForCanIndex].data_packlen = pdata[sizeof(com_packet_header_t)+start_base + 2];
        if(spiDataForCan[spiForCanIndex].fuc0 == 0x75 && spiDataForCan[spiForCanIndex].fuc1 == 0x01)
        {

        }
        else
        {
#if COM_SOC_DEBUG  //define in this file head position
            Printf("SPI:0x%x,0x%x\r\n",spiDataForCan[spiForCanIndex].fuc0,spiDataForCan[spiForCanIndex].fuc1);
#endif
            //templen = spiDataForCan[spiForCanIndex].data_packlen;
            socData[0] = pdata[sizeof(com_packet_header_t)+start_base+3];
            socData[1] = pdata[sizeof(com_packet_header_t)+start_base+4];
#if COM_SOC_DEBUG //define in this file head position
            Printf("SPIData:0x%x,0x%x\r\n",socData[0],socData[1]);
#endif
        }
        if(spiDataForCan[spiForCanIndex].fuc0 == 0x75 && spiDataForCan[spiForCanIndex].fuc1 == 0x01)
        {
            spiDataForCan[spiForCanIndex].msgId[1]= pdata[sizeof(com_packet_header_t)+start_base+3];
            spiDataForCan[spiForCanIndex].msgId[0]= pdata[sizeof(com_packet_header_t)+start_base+4];
            spiDataForCan[spiForCanIndex].dataLen = pdata[sizeof(com_packet_header_t)+start_base+5];
            for(i=0;i<spiDataForCan[spiForCanIndex].dataLen;i++)
            {
                spiDataForCan[spiForCanIndex].data[i] = pdata[sizeof(com_packet_header_t)+start_base+6+i];
            }
            socAndMcuConnecting += 1;
#if COM_SOC_DEBUG //define in this file head position
//            Printf("heartbeat\r\n");
#endif
        }
        else if(spiDataForCan[spiForCanIndex].fuc0 == 0x75 && spiDataForCan[spiForCanIndex].fuc1 == 0x1A)
        {
        	socData[0] = pdata[sizeof(com_packet_header_t)+start_base+3];
        	socData[1] = pdata[sizeof(com_packet_header_t)+start_base+4];
        	OneHourModeAck(socData[0]);
        }
        else if(spiDataForCan[spiForCanIndex].fuc0 == 0x75 && spiDataForCan[spiForCanIndex].fuc1 == 0x1E)
        {
        	socData[0] = pdata[sizeof(com_packet_header_t)+start_base+3];
        	socData[1] = pdata[sizeof(com_packet_header_t)+start_base+4];
        	fiveMinutesModeAck(socData[0]);
        }
        else if(spiDataForCan[spiForCanIndex].fuc0 == 0x75 && spiDataForCan[spiForCanIndex].fuc1 == 0x14)
        {
            socData[0] = pdata[sizeof(com_packet_header_t)+start_base+3];
            socData[1] = pdata[sizeof(com_packet_header_t)+start_base+4];
            DoubleClick(socData[0]);
        }
        else
        {
            if(spiDataForCan[spiForCanIndex].dataLen < 8)
            {
                for(i=0;i<spiDataForCan[spiForCanIndex].dataLen;i++)
                {
                    spiDataForCan[spiForCanIndex].data[i] = pdata[sizeof(com_packet_header_t)+start_base+3+i];
                }
            }
        }
        start_base = spiDataForCan[spiForCanIndex].data_packlen+3;
        packLen -= start_base;
        if(packLen < 2)
        {
            break;
        }
        else
        {
            spiForCanIndex++;
            if(spiForCanIndex > 10)
            {
                spiForCanIndex = 0;
            }
        }
    }
    for(i=0;i< (1+spiForCanIndex);i++)
    {
        if(spiDataForCan[i].fuc0 == 0x75 && spiDataForCan[i].fuc1 == 0x01)
        {
            can_msgID = ((spiDataForCan[i].msgId[1])<<8) | spiDataForCan[i].msgId[0];
            if(can_msgID == 0x2e2)
            {
                if(rightLedRead != (spiDataForCan[i].data[1] & 0x0c)>> 2)
                {
                    rightLedRead =  (spiDataForCan[i].data[1] & 0x0c)>> 2;
                    can2DETimes[0] = 3;
                }
                if(flooLlight != (spiDataForCan[i].data[1] & 0x30)>> 4)
                {
                    flooLlight = (spiDataForCan[i].data[1] & 0x30)>> 4;
                    can2DETimes[1] = 3;
                }
                if(heaLlight != (spiDataForCan[i].data[2] & 0x03))
                {
                    heaLlight =  (spiDataForCan[i].data[2] & 0x03);
                    can2DETimes[2] = 3;
                }
                if(followme != (spiDataForCan[i].data[2] & 0xc0)>> 6)
                {
                    followme = (spiDataForCan[i].data[2] & 0xc0)>> 6;
                    can2DETimes[3] = 3;
                }
                if(leftLedRead != (spiDataForCan[i].data[1] & 0x03))
                {
                    leftLedRead = spiDataForCan[i].data[1] & 0x03;
                    can2DETimes[4] = 3;
                }
            }
            push_can_data_fml(can_msgID,spiDataForCan[i].data);
        }
    }
    spiForCanIndex = 0;
}

uint8_t calculation_crc_fml(const uint8_t *input, uint16_t len)
{
    uint8_t wcrcin = 0xFF;
    uint16_t i = 0;
    wcrcin = input[0];
    for(i =1;i<len;i++)
    {
        wcrcin ^= input[i];
    }
    return wcrcin;
}

uint8_t check_re_soc_data_crc_fml(uint8_t *p)
{
    uint16_t packLen =0;
    uint8_t crc;
    packLen = ((p[4])<<8) | p[5];
    if(packLen > 512)
    {
        packLen = 512;
        uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"len long1");
    }
    crc = calculation_crc_fml((uint8_t *)&p[7], packLen-1);
    if(crc == p[packLen+7-1])
    {
         return 1;
    }
    else
    {
         return 0;
    }
}

void clear_send_data_timeout_fml(void)
{
    spiReceiveTimeout = 0;
    spiReceiveTimeoutEn = 0;
    spiWork = 0;
    (void)LPSPI_DRV_SlaveAbortTransfer(1);
}

void soc_isr_hander_fml( void )
{
    uint32_t pinoutput;
    unsigned long ulValueToSend = 100UL;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    pinoutput = PINS_DRV_ReadPins(PTC);
    if((pinoutput & 0x00040000) == 0)
    {
        ulValueToSend = 0X02;
        if(xQueueSendToBackFromISR( spiQueue, &ulValueToSend, &xHigherPriorityTaskWoken ))
        {

        }
        else
        {
            ;
        }
    }
    PINS_DRV_ClearPortIntFlagCmd(BTN_PORT);
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

void porte_interrupt_fml( void )
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    CanWakeupSource =1;
    PINS_DRV_ClearPortIntFlagCmd(PORTE);
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}


extern uint8_t MonitorHeartFlag;
extern uint8_t socAndMcuConnectingFlag;
void spi_transfer_task_fml( void *pvParameters )
{
    unsigned long ulReceivedValue;
    uint16_t len;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    TickType_t xNextWakeTime;

    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();
    while(1)
    {
        xQueueReceive(spiQueue,&ulReceivedValue,portMAX_DELAY);
        if(spiRunStep == Shake_hands)
        {
            len = shake_step_receive_soc_process_fml_api(ulReceivedValue);
        }
        else if(spiRunStep == spi_com_normal)
        {
            len = normal_step_receive_soc_process_fml_api(ulReceivedValue);
        }
        else
        {
            len =512;
        }
        if(xQueueReceive( spiCallbackQueue, &ulReceivedValue, 0 ))
        {
            MonitorHeartFlag =1;
            socAndMcuConnectingFlag = 1;
            if(SPICALLBACK == ulReceivedValue)
            {
                rx_soc_data_process_fml_api();
            }
        }
        start_spi_Transfer_fml_api(len);
    }
}

