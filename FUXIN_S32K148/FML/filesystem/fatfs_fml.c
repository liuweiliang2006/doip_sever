/**@file  fatfs_flash.c
* @brief  fatfs library use DFLASH
* @details   flash init,flash write,flash read,flash erase
* @author      willianm
* @date        2021-5-18
* @version     V1.0
* @copyright    Copyright (c) 2020 enovate
**********************************************************************************
* @attention
* Hareware:s32k148
* SDK version£º3.0.0
* @par modify data:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021/5/18   <td>1.0      <td>william   <td>create
* </table>
*
**********************************************************************************
*/

#include "fatfs_fml.h"
#include "diskio.h"
#include "stdint.h"
#include "Driver_interface.h"
//#include "Flash1.h"

#define FLAH_SECTOR_SIZE (4096)

uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free)
{
    FATFS *fs1;
    uint8_t res;
    DWORD fre_clust=0, fre_sect=0, tot_sect=0;

    res = f_getfree((const TCHAR*)drv, &fre_clust, &fs1);
    if(res==0)
    {
        tot_sect=(fs1->n_fatent-2)*fs1->csize;    //Get the total number of sectors
        fre_sect=fre_clust*fs1->csize;            //Get the number of free sectors
#if FF_MAX_SS!=512                                  //If the sector size is not 512 bytes, it is converted to 512 bytes
        tot_sect*=fs1->ssize/512;
        fre_sect*=fs1->ssize/512;
#endif
        *total=tot_sect>>1;    //unit is KB
        *free=fre_sect>>1;    //unit is KB
     }
    return res;
}

void fatfs_init_fml_api(void)
{
    FATFS fatfs;
    FRESULT res;
    BYTE work[FF_MAX_SS];
    FATFS *fs;
//    FIL saveFaultFs;
    DIR dir;
    static FILINFO fno;
    unsigned long total,free;

//    res = f_mkfs("0:",1,FF_MAX_SS,work,sizeof(work));
    res = f_mount(&fatfs,"0:" , 1);
    if (res != FR_OK)
    {
        res = f_mkfs("0:",1,0,work,sizeof(work));
        res = f_mount(&fatfs,"0:" , 0);
        res = f_mount(&fatfs,"0:" , 1);
        exf_getfree("0",&total,&free);
        res = f_opendir(&dir, "/");
        res = f_mkdir("config");
        res = f_opendir(&dir, "/");
        res = f_mkdir("log");
        res = f_opendir(&dir, "/");
        res = f_mkdir("fault");
    }
}



/**@brief S32K1R48 DFLASH init
* @param[in]  none
* @return  Init result
* - RES_OK      Init Success
* - RES_ERROR   Init error
*/

DRESULT fatfs_flash_init_fml()
{
    return RES_OK;
}

/**@brief S32K1R48 DFLASH read
* @param[in]  *pBuffer store data point
* @param[in]  readAddr  read Dflash address
* @param[in]  NumByteRead  read data number;max number is 4096(one sector)
* @return  read result
* - RES_OK      read Success
* - RES_ERROR   read error
*/
DRESULT fatfs_dflsh_read_fml(uint8_t *pBuffer,uint32_t readAddr,uint16_t NumByteRead)
{
    uint16_t i = 0;
    for(i = 0; i < NumByteRead; i++)
    {
        pBuffer[i] = (*(__IO uint8_t*)(START_ADDR+readAddr+i));
    }
    return RES_OK;
}


/**@brief S32K1R48 DFLASH write
* @param[in]  *pBuffer store data point
* @param[in]  WriteAddr  write Dflash address
* @param[in]  NumByteRead  write data number;max number is 4096(one sector)
* @return  read result
* - RES_OK      read Success
* - RES_ERROR   read errorFLASH_DRV_EraseBlock();
*/


uint8_t flashSectorBuff[FLAH_SECTOR_SIZE];
DRESULT fatfs_dflsh_write_fml(uint8_t *pBuffer,uint32_t WriteAddr ,uint16_t NumByteToWrite)
{
    uint16_t i = 0;
    status_t ret;
    uint32_t secPos; //write flash position
    uint32_t secOff; //flash sector offerset address
    uint32_t secSpace; //flash sector available space

    secPos = WriteAddr / FLAH_SECTOR_SIZE; //write which sector
    secOff = WriteAddr % FLAH_SECTOR_SIZE; //the sector offset address
    secSpace = FLAH_SECTOR_SIZE - secOff; //the sector available space

    if (NumByteToWrite < secSpace)
        secSpace = NumByteToWrite; //need write data size <4096
    while(1)
    {
        for (i = 0; i< FLAH_SECTOR_SIZE; i++) //read the whole sector
        {
            flashSectorBuff[i] = (*(__IO uint8_t*)(START_ADDR+secPos*FLAH_SECTOR_SIZE+i));
        }

        /*add new message to sector buff,and repare write.*/
        for (i = 0; i < secSpace; i++)
        {
            flashSectorBuff[secOff + i] = pBuffer[i];
        }

        /* Erase the DFlash sector */
        ret = flash_erase_sector_hal_api(START_ADDR+secPos*FLAH_SECTOR_SIZE, FLAH_SECTOR_SIZE);
        /* Verify the erase operation at margin level value of 1, user read */
        ret = flash_verify_section_hal_api( START_ADDR+secPos*FLAH_SECTOR_SIZE, FLAH_SECTOR_SIZE/FTFx_DPHRASE_SIZE,1u);
        /*write flashSectorBuff to FLASH sector*/
        ret = flash_program_hal_api(START_ADDR+secPos*FLAH_SECTOR_SIZE, FLAH_SECTOR_SIZE, flashSectorBuff);
        return RES_OK;
    }
}
//DRESULT Fatfs_Dflsh_write(uint8_t *pBuffer,uint32_t WriteAddr)
//{
//    uint16_t i = 0;
//    status_t ret;
//    /* Erase the DFlash sector */
//    ret = FLASH_DRV_EraseSector(&flashSSDConfig, START_ADDR+WriteAddr, SECTOR_SIZE);
//    if (ret != STATUS_SUCCESS)
//    {
//        return RES_ERROR;
//    }
//    /* Verify the erase operation at margin level value of 1, user read */
//    ret = FLASH_DRV_VerifySection(&flashSSDConfig, START_ADDR+WriteAddr, SECTOR_SIZE/FTFx_DPHRASE_SIZE,1u);
//    if (ret != STATUS_SUCCESS)
//    {
//        return RES_ERROR;
//    }
//    ret = FLASH_DRV_Program(&flashSSDConfig, START_ADDR+WriteAddr, SECTOR_SIZE, pBuffer);
//    if (ret != STATUS_SUCCESS)
//    {
//        return RES_ERROR;
//    }
//    return RES_OK;
//}

