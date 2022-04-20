/*
 * update.c
 *
 *  Created on: 2020Äê12ÔÂ1ÈÕ
 *      Author: Administrator
 */
#include "Flash1.h"
#include "com_task.h"
#include "utils.h"
#include "Cpu.h"
#include "BoardDefines.h"

#define A_PROGRAM_ADDRESS 0xD000
#define A_PROGRAM_FLAG 0xAA
#define B_PROGRAM_ADDRESS 0x40000
#define B_PROGRAM_FLAG 0xBB
#define FEATURE_OF_WRITE_BLOCK_SIZE 64
#define RUN_STATUS_LEN 4
extern uint8_t tempTestData[20];
uint8_t pfalshBuffer[128]={0xFF};
uint8_t dflashBuffer[256]={0xff};
uint32_t updateStartAddress;
uint8_t mcuVersion[20] = {"EAEXAR1CN21041503S"};



status_t flash_app_set_fml(void)
{
    status_t ret;
    /* Install interrupt for Flash Command Complete event */
    int_sys_install_handler_hal_api(FTFC_IRQn, ccif_handler_hal_api, (isr_t*) 0);
    int_sys_enable_irq_hal_api(FTFC_IRQn);
    int_sys_set_priority_hal_api( FTFC_IRQn, 0x02 );

    ret = flash_init_hal_api();
    /* Enable global interrupt */
    ENABLE_IRQ_GLOBAL;
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    return STATUS_SUCCESS;
}
#if 0
status_t write_to_Dfalsh_fmlx(uint8_t *ptr,uint16_t len,uint8_t index)
{
    status_t ret;        /* Store the driver APIs return code */
    uint32_t address;
    uint32_t size;
    uint32_t failAddr;
    uint8_t i;

    address = DFLASH_START_ADDRESS+4096*index;
    size = FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
    flash_erase_sector_hal_api(address, size);
    /* Verify the erase operation at margin level value of 1, user read */
    flash_verify_section_hal_api(address, size,1u);

    /* Write some data to the erased DFlash sector */
    address = DFLASH_START_ADDRESS+4096*index;
    size = FEATURE_OF_WRITE_BLOCK_SIZE*8;
    ret = flash_program_hal_api(address, size, ptr);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    /* Verify the program operation at margin level value of 1, user margin */
    ret = flash_program_check_hal_api(address, size, ptr, &failAddr, 1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    return STATUS_SUCCESS;
}
#endif

uint8_t read_Dflsh_ABversion_fml(void)
{
    uint32_t i;
    for(i=0;i<256;i++)
    {
        dflashBuffer[i] = *((uint32_t *)(DFLASH_START_ADDRESS+i));
    }
    if(dflashBuffer[0]==B_PROGRAM_FLAG)
    {
        updateStartAddress = A_PROGRAM_ADDRESS;

        return 'B';
    }
    else
    {
        updateStartAddress = B_PROGRAM_ADDRESS;

        return 'A';
    }
}

uint8_t read_pflsh_fml(uint16_t index,uint32_t base_address)
{
    uint32_t i;
    DISENABLE_IRQ_GLOBAL;
    for(i=0;i<64;i++)
    {
        pfalshBuffer[i] = *((uint32_t *)(PFLASH_START_ADDRESS+base_address+i+192*index));
    }
    ENABLE_IRQ_GLOBAL;
    uart_printf_data_fml_api(UARTTASKPRINT,pfalshBuffer,10,__FUNCTION__,",pd");
    //uart_printf_data_fml_api(pfalshBuffer+10,10,",pd2");
    return 1;
}



status_t Erase_Pfalsh_fml(uint32_t addr)
{
    status_t ret;        /* Store the driver APIs return code */
    uint32_t size;

    size = FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    ret = flash_erase_sector_hal_api(addr, size);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }

    /* Verify the erase operation at margin level value of 1, user read */
    ret = flash_verify_section_hal_api(addr, size, 1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    return STATUS_SUCCESS;
}
void erase_updata_pflash_fml(uint32_t address)
{
    uint32_t i;
    //num =(B_PROGRAM_ADDRESS - A_PROGRAM_ADDRESS)/FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    for(i=0;i<32;i++)
    {
        DISENABLE_IRQ_GLOBAL;
        Erase_Pfalsh_fml(address);
        ENABLE_IRQ_GLOBAL;
        address+=FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
        //feed_wdg();
    }
}
status_t erase_dfalsh_fml(uint32_t address)
{
    status_t ret;        /* Store the driver APIs return code */
    uint32_t size;
    //address = DFLASH_START_ADDRESS;
    size = FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
    ret = flash_erase_sector_hal_api(address, size);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    /* Verify the erase operation at margin level value of 1, user read */
    ret = flash_verify_section_hal_api(address, size,1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    return STATUS_SUCCESS;
}
status_t write_version_fml(uint8_t *ptr,uint8_t len,uint32_t address)
{
    status_t ret;        /* Store the driver APIs return code */
    uint32_t size;
    int i;
    uint32_t failAddr;
    size = FEATURE_FLS_DF_BLOCK_SECTOR_SIZE;
    DISENABLE_IRQ_GLOBAL;
    for(i=0;i<len;i++)
    {
        dflashBuffer[i]=ptr[i];
    }
    erase_dfalsh_fml(DFLASH_START_ADDRESS);

    ret = flash_program_hal_api(address, size, dflashBuffer);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    /* Verify the program operation at margin level value of 1, user margin */
    ret = flash_program_check_hal_api(address, size, dflashBuffer, &failAddr, 1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    ENABLE_IRQ_GLOBAL;
    return STATUS_SUCCESS;
}

status_t Write_Pfalsh_fml(uint32_t addr,uint8_t *ptrbuffer)
{

    status_t ret;        /* Store the driver APIs return code */
    uint32_t size;
    uint32_t failAddr;
    /* Write some data to the erased DFlash sector */
    size = FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;

    ret = flash_program_hal_api(addr, size/64, ptrbuffer);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    /* Verify the program operation at margin level value of 1, user margin */
    ret = flash_program_check_hal_api(addr, size/64, ptrbuffer, &failAddr, 1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }
    return STATUS_SUCCESS;
}

typedef void(*JumpToPtr)(void);
uint32_t *pNewbootEntry = 0x4;
JumpToPtr    pJumpTo;
void jump_app_fml(void)
{
    pJumpTo = *pNewbootEntry;
    pJumpTo();
}
void mcu_update_jump_fml( void )
{
    int i;
    for(i=0;i<8;i++)
    {
        dflashBuffer[i] = *((uint32_t *)(DFLASH_START_ADDRESS+i));
    }
    dflashBuffer[2] = 0x55;
    write_version_fml(dflashBuffer,8,DFLASH_START_ADDRESS);
    DISENABLE_IRQ_GLOBAL;
    vTaskSuspendAll();
    taskENTER_CRITICAL();
    //vTaskEndScheduler();
    LPSPI_DRV_SlaveAbortTransfer(SPISLAVE);
    LPSPI_DRV_SlaveDeinit(SPISLAVE);
    lpit_stop_timer_channels_hal_api(INST_LPIT1, LPIT_CHANNEL);
    lpit_stop_timer_channels_hal_api(INST_LPIT1, 1);
    lpit_stop_timer_channels_hal_api(INST_LPIT1, 2);
    jump_app_fml();
    pins_toggle_pins_hal_api(LED_GPIO, (1 << LED1));
}

void update_start_fml(unsigned long uValue)
{
    int i;
    uint8_t tempotadata[4];
    for(i=0;i<4;i++)
    {
        tempotadata[i] = *((uint32_t *)(DFLASH_START_ADDRESS+i));
    }
    if(tempotadata[0] == 0xaa)
    {
        //erase_updata_pflash_fml(0x30000);
        tempotadata[2] = 0x55;
        tempotadata[3] = 0xAA;
    }
    else if(tempotadata[0] == 0xbb)
    {
        //erase_updata_pflash_fml(0x10000);
        tempotadata[2] = 0x55;
        tempotadata[3] = 0xBB;
    }
    else
    {
        //erase_updata_pflash_fml(0x30000);
        tempotadata[2] = 0x55;
        tempotadata[3] = 0xAA;
    }
    write_version_fml(tempotadata,4,DFLASH_START_ADDRESS);
    for(i=0;i<16;i++)
    {
        dflashBuffer[i] = *((uint32_t *)(DFLASH_START_ADDRESS+i));
    }
    uart_printf_data_fml_api(UARTTASKPRINT,&dflashBuffer[0],4,__FUNCTION__,",falsh clear");
    vTaskDelay(20/portTICK_PERIOD_MS);
    mcu_update_jump_fml();
}




