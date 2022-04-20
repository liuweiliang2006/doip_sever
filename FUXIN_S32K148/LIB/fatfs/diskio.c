/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include <fatfs_fml.h>
#include "ff.h"            /* Obtains integer types */
#include "diskio.h"        /* Declarations of disk functions */
#include "Cpu.h"
/* Definitions of physical drive number for each drive */
//#define DEV_RAM        0    /* Example: Map Ramdisk to physical drive 0 */
//#define DEV_MMC        1    /* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB        2    /* Example: Map USB MSD to physical drive 2 */
#define DFLASH 0  /*DFLASH start address:0x1007 1000  size:60k(0xF000)*/

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv        /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;
    int result;

    switch (pdrv) {
    case DFLASH :
        return RES_OK;
    default:
        return STA_NOINIT;
    }
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv                /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;
    int result;

    switch (pdrv) {
    case DFLASH :
        fatfs_flash_init_fml();
        return RES_OK;
    default:
        return STA_NOINIT;
    }
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,        /* Physical drive nmuber to identify the drive */
    BYTE *buff,        /* Data buffer to store read data */
    DWORD sector,    /* Start sector in LBA */
    UINT count        /* Number of sectors to read */
)
{
    DRESULT res;
    int result;

    switch (pdrv) {
    case DFLASH :
        for( ; count > 0; count--)
        {
            res =fatfs_dflsh_read_fml(buff,sector*SECTOR_SIZE,SECTOR_SIZE);
            if(res != RES_OK)
            {
                res = RES_PARERR;
                break;
            }
        }
        break;
    default:
        res = RES_PARERR;
    }

    return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,            /* Physical drive nmuber to identify the drive */
    const BYTE *buff,    /* Data to be written */
    DWORD sector,        /* Start sector in LBA */
    UINT count            /* Number of sectors to write */
)
{
    DRESULT res;
    int result;

//    char *test = "test1.txt";
//    result = sizeof(*buff);

    switch (pdrv) {
    case DFLASH :
        for(; count > 0; count--)
        {
            INT_SYS_DisableIRQ(PORTC_IRQn);
            INT_SYS_DisableIRQ(DMA2_IRQn);
            INT_SYS_DisableIRQ(LPSPI1_IRQn);
            INT_SYS_DisableIRQ(LPUART1_RxTx_IRQn);
            INT_SYS_DisableIRQ(FTM0_Ovf_Reload_IRQn);
            INT_SYS_DisableIRQGlobal();
            MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
            MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);
            res = fatfs_dflsh_write_fml(buff,sector*SECTOR_SIZE ,SECTOR_SIZE);
//            MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x0u);
//            MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x0u);
            MSCM->OCMDR[0u] &= ~(3<<4);
            MSCM->OCMDR[1u] &= ~(3<<4);
            INT_SYS_EnableIRQ(PORTC_IRQn);
            INT_SYS_EnableIRQ(DMA2_IRQn);
            INT_SYS_EnableIRQ(LPSPI1_IRQn);
            INT_SYS_EnableIRQ(LPUART1_RxTx_IRQn);
            INT_SYS_EnableIRQ(FTM0_Ovf_Reload_IRQn);
            INT_SYS_EnableIRQGlobal();
            if(res != RES_OK)
            {
                res = RES_PARERR;
                break;
            }
        }

        break;
    default:
        res = RES_PARERR;
    }

    return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,        /* Physical drive nmuber (0..) */
    BYTE cmd,        /* Control code */
    void *buff        /* Buffer to send/receive control data */
)
{
    DRESULT res;
    int result;

    if (pdrv == DFLASH)
    {
        switch (cmd) {
        case CTRL_SYNC:
            res = RES_OK;
            break;
        case GET_SECTOR_SIZE:
            *(WORD*)buff = SECTOR_SIZE;
//            *(WORD*)buff = 512;
            res = RES_OK;
            break;
        case GET_BLOCK_SIZE:
//            *(WORD*)buff = 2;
            *(WORD*)buff = 8;
            res = RES_OK;
            break;
        case GET_SECTOR_COUNT:
            *(DWORD*)buff = SECTOR_NUM;
//            *(DWORD*)buff = 240 ;
            res = RES_OK;
            break;
        default:
            res = RES_PARERR;
        }
    }
    else
    {
        res = RES_ERROR;
    }

    return res;
}

//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime (void)
{
    uint32_t time=0;
    rtc_timedate_t Time;
    RTC_DRV_GetCurrentTimeDate(RTCTIMER1, &Time);
    time=(Time.year)<<25;//year
    time|=(Time.month)<<21;   //month
    time|=(Time.day)<<16;    //data
    time|=(Time.hour)<<11;      //hour
    time|=(Time.minutes)<<5;        //minu
    time|=(Time.seconds/2);         //sec
    return time;
}
