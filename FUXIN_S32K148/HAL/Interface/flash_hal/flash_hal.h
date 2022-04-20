/*
 * flash_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_FLASH_HAL_FLASH_HAL_H_
#define INTERFACE_FLASH_HAL_FLASH_HAL_H_
#include "Cpu.h"
#define PFLASH_START_ADDRESS flashSSDConfig.PFlashBase
#define DFLASH_START_ADDRESS flashSSDConfig.DFlashBase
extern flash_ssd_config_t flashSSDConfig;
status_t flash_init_hal_api(void);
status_t flash_verify_section_hal_api(uint32_t dest,uint16_t number,uint8_t marginLevel);
status_t flash_erase_sector_hal_api(uint32_t dest, uint32_t size);
status_t flash_program_hal_api( uint32_t dest,uint32_t size,const uint8_t * pData);
status_t flash_program_check_hal_api(uint32_t dest,uint32_t size, const uint8_t * pExpectedData,uint32_t * pFailAddr,uint8_t marginLevel);
status_t flash_eeprom_write_hal_api( uint32_t dest,uint32_t size,const uint8_t * pData);
void ccif_handler_hal_api(void);

#endif /* INTERFACE_FLASH_HAL_FLASH_HAL_H_ */
