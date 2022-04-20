/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Bsw_Common.c
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : BSW COMMON File
*   Author          : Hirain
********************************************************************************
*   Description     : for some functions may be used by all modules
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    24/08/2016    ning.chen     N/A          Original
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Bsw_Common.h"

#define BSW_START_SEC_CONST_8
#include "MemMap.h"
/* CANFD DLC Map */
CONST(uint8, BSW_CONST) Bsw_CanFDDlcMap[16] =
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    12,
    16,
    20,
    24,
    32,
    48,
    64
};
#define BSW_STOP_SEC_CONST_8
#include "MemMap.h"


#define BSW_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
*   Functions
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Bsw_MemCpy
*
* Description:   This service copy data from src to dest
*
* Inputs:        dest, src, size
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC (void, BSW_CODE) Bsw_MemCpy
(
    CONSTP2VAR (uint8, AUTOMATIC, BSW_APPL_DATA) dest,
    CONSTP2CONST (uint8, AUTOMATIC, BSW_APPL_DATA) src,
    const uint32 size
)
{
    uint32 i;

    for (i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Bsw_MemSet
*
* Description:   This service set fix data to  dest
*
* Inputs:        dest, src, size
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC (void, BSW_CODE) Bsw_MemSet
(
    CONSTP2VAR (uint8, AUTOMATIC, BSW_APPL_DATA) dest,
    const uint8 src,
    const uint32 size
)
{
    uint32 i;

    for (i = 0; i < size; i++)
    {
        dest[i] = src;
    }
}

#define BSW_STOP_SEC_CODE
#include "MemMap.h"






