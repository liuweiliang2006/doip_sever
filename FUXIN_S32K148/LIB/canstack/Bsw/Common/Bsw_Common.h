/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Bsw_Common.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : Bsw Common File
*   Author          : Hirain
********************************************************************************
*   Description     : Bsw_Common header file.
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*
********************************************************************************
* END_FILE_HDR*/

#ifndef BSW_COMMON_H
#define BSW_COMMON_H
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Std_Types.h"

#define BSW_START_SEC_CONST_8
#include "MemMap.h"

extern CONST(uint8, BSW_CONST) Bsw_CanFDDlcMap[16];

#define BSW_STOP_SEC_CONST_8
#include "MemMap.h"

#define BSW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
*   Declare
*******************************************************************************/
extern FUNC(void, BSW_CODE) Bsw_MemCpy
(
    CONSTP2VAR(uint8, AUTOMATIC, BSW_APPL_DATA) dest,
    CONSTP2CONST(uint8, AUTOMATIC, BSW_APPL_DATA) src,
    const uint32 size
);
extern FUNC(void, BSW_CODE) Bsw_MemSet
(
    CONSTP2VAR(uint8, AUTOMATIC, BSW_APPL_DATA) dest,
    const uint8 src,
    const uint32 size
);
#define BSW_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSW_COMMON_H */

