/*
 * flash_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"
flash_ssd_config_t flashSSDConfig;
status_t flash_init_hal_api(void)
{
    status_t status;
    FLASH_DRV_Init(&Flash1_InitConfig0 , &flashSSDConfig);
    if (flashSSDConfig.EEESize == 0u)
    {
        /* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
         * DEFlashPartition will be failed if the IFR region isn't blank.
         * Refer to the device document for valid EEPROM Data Size Code
         * and FlexNVM Partition Code. For example on S32K148:
         * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
         * - DEPartitionCode = 0x04u: EEPROM backup size = 64 Kbytes */
        status = FLASH_DRV_DEFlashPartition(&flashSSDConfig, 0x02u, 0x04u, 0x0u, false, true);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Re-initialize the driver to update the new EEPROM configuration */
        status = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Make FlexRAM available for EEPROM */
        status = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
    return status;
}
status_t flash_erase_sector_hal_api(uint32_t dest, uint32_t size)
{
    return FLASH_DRV_EraseSector(&flashSSDConfig, dest, size);
}
status_t flash_verify_section_hal_api(uint32_t dest,uint16_t number,uint8_t marginLevel)
{
    return FLASH_DRV_VerifySection(&flashSSDConfig, dest, number,marginLevel);
}
status_t flash_program_hal_api( uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData)
{
    return FLASH_DRV_Program(&flashSSDConfig, dest, size, pData);
}
status_t flash_program_check_hal_api(uint32_t dest,
                                uint32_t size,
                                const uint8_t * pExpectedData,
                                uint32_t * pFailAddr,
                                uint8_t marginLevel)
{
    return FLASH_DRV_ProgramCheck(&flashSSDConfig, dest, size, pExpectedData, pFailAddr, 1u);
}
void ccif_handler_hal_api(void)
{
    /* Disable Flash Command Complete interrupt */
    FTFx_FCNFG &= (~FTFx_FCNFG_CCIE_MASK);
    return;
}

status_t flash_eeprom_write_hal_api( uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData)
{
    return FLASH_DRV_EEEWrite(&flashSSDConfig, dest, size, pData);
}



