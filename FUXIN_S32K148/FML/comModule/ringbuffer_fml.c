/*
 * fml_ringbuffer.c
 *
 *  Created on: 2021年5月25日
 *      Author: Administrator
 */
/*
 * ringbuffer.c
 *
 *  Created on: 2021年2月18日
 *      Author: Administrator
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* SDK includes. */
#include "interrupt_manager.h"
#include "clock_manager.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "Cpu.h"

#include "BoardDefines.h"
#include "com_task.h"
#include "utils.h"

#include "ringbuffer.h"
#include "string.h"
#include <stdio.h>


uint8_t readRingbufferEn;
rb_t spiRbTx;
rb_t wholePackageSpirbTx;
rb_t canRingbuffer;
#define Spi_TX_FRAME_MAX_SIZE 4096*2
uint8_t Spi_RingBuff[Spi_TX_FRAME_MAX_SIZE];
uint8_t SpiRingBuffwhole[4096*10];
uint8_t Can_RingBuff[1024];

#define UART_SOC_MAX_SIZE 4096
uint8_t uartSocBuff[UART_SOC_MAX_SIZE];
rb_t uartsocRingbuffer;

int32_t get_write_space_fml(rb_t *rb)
{
    return  rbCanWrite(rb);
}

void ringbuffer_creat_fml(void)
{
    rbCreate(&spiRbTx,Spi_RingBuff,Spi_TX_FRAME_MAX_SIZE);
}

int32_t spi_ring_write_fml(uint8_t *data,uint16_t len)
{
    int32_t status;
    status =rbWrite(&spiRbTx, data, len);
    if(status == -1)
    {
        uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"no can write");
    }
    return status;
}

uint16_t spi_ring_read_fml(uint8_t *p)
{
    uint16_t len;

    len = rbCanRead(&spiRbTx);
    if(len == 0)
    {
        return 0;
    }
    else
    {
        ;
    }
    len = rbRead(&spiRbTx,p,1000);
    return (uint16_t)len;
}

uint16_t spi_hand_ring_read_fml(uint8_t *p,uint16_t count)
{
    uint16_t len;
    len = rbRead(&spiRbTx,p,count);
    return (uint16_t)len;
}

void can_ringbuffer_creat_fml(void)
{
    rbCreate(&canRingbuffer,Can_RingBuff,1023);
}
void can_ring_write_fml(uint8_t *data,uint16_t len)
{
    int32_t status;
    status = rbWrite(&canRingbuffer, data, len);
    if(status == -1)
    {
        uart_printf_char_fml_api(UARTISRPRINT,__FUNCTION__,"not can write");
    }
}
uint16_t can_ring_read_fml(uint8_t *p)
{
    uint16_t len;
    len = rbCanRead(&canRingbuffer);
    if(len == 0)
    {
        return 0;
    }
    else
    {
        ;
    }
    len = rbRead(&canRingbuffer,p,253);
    return (uint16_t)len;
}

void whole_package_spiring_creat_fml(void)
{
    rbCreate(&wholePackageSpirbTx,SpiRingBuffwhole,4096*10);
}
int32_t whole_package_spiring_write_fml(uint8_t *data,uint16_t len)
{
    int32_t status;
    status = rbWrite(&wholePackageSpirbTx, data, len);
    if(status == -1)
    {
       uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"no big write");
    }
    return status;
}
uint16_t whole_package_spiring_read_fml(uint8_t *p,uint16_t lens)
{
    uint16_t len;
    len = rbCanRead(&wholePackageSpirbTx);
    if(len == 0)
    {
        return 0;
    }
    else
    {
        ;
    }
    len = rbRead(&wholePackageSpirbTx,p,lens);
    return (uint16_t)len;
}

/**********************soc to uart ringbuffer start********************************/
/****************************add by william****************************************/
void uartsoc_ringbuffer_creat_fml(void)
{
    rbCreate(&uartsocRingbuffer,uartSocBuff,UART_SOC_MAX_SIZE);
}

void uartsoc_ring_write_fml(uint8_t *data,uint16_t len)
{
    int32_t status;
    status = rbWrite(&uartsocRingbuffer, data, len);
    if(status == -1)
    {
        uart_printf_char_fml_api(UARTISRPRINT,__FUNCTION__,"not can write");
    }
}
uint16_t uartsoc_ring_read_fml(uint8_t *p)
{
    uint16_t len;
    len = rbCanRead(&uartsocRingbuffer);
    if(len == 0)
    {
        return 0;
    }
    else
    {
        ;
    }
    len = rbRead(&uartsocRingbuffer,p,1);
    return (uint16_t)len;
}

uint16_t uartsoc_ring_can_read_fml(void)
{
    uint16_t len;
    len = rbCanRead(&uartsocRingbuffer);
    return (uint16_t)len;
}
/**********************soc to uart ringbuffer end********************************/
