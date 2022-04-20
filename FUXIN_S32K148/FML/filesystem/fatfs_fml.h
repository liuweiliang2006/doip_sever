/*
 * fatfs_flash_fml.h
 *
 *  Created on: 2021年5月28日
 *      Author: Administrator
 */

#ifndef FILESYSTEM_FML_FATFS_FLASH_FML_H_
#define FILESYSTEM_FML_FATFS_FLASH_FML_H_

/*
 * fatfs_flash.h
 *
 *  Created on: 2021年5月18日
 *      Author: Administrator
 */

#ifndef FATFS_FLASH_FATFS_FLASH_H_
#define FATFS_FLASH_FATFS_FLASH_H_

#include "flash_driver.h"
#include "diskio.h"
/**
* pfalsh sector total number
*/
#define SECTOR_NUM (240)
/**
* pfalsh every sector size
*/
#define SECTOR_SIZE (512)  //
/**
* Fatfs flash start address
*/
//#define START_ADDR (0x162000)
#define START_ADDR (0x10000000) //FATFS in DFLASH start address
//#define START_ADDR (0x10000000)
//#define START_ADDR (0x80000)


extern flash_ssd_config_t flashSSDConfig;

void fatfs_init_fml_api(void);

DRESULT fatfs_flash_init_fml();

DRESULT fatfs_dflsh_read_fml(uint8_t *pBuffer,uint32_t readAddr,uint16_t NumByteRead);

DRESULT fatfs_dflsh_write_fml(uint8_t *pBuffer,uint32_t WriteAddr ,uint16_t NumByteToWrite);

#endif /* FATFS_FLASH_FATFS_FLASH_H_ */


#endif /* FILESYSTEM_FML_FATFS_FLASH_FML_H_ */
