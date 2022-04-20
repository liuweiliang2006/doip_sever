/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : OsekNm_Cbk.h
********************************************************************************
*   Project/Product : OsekNm module
*   Title           : OsekNm module Header File
*   Author          : Hirain
********************************************************************************
*   Description     : Callback header file of OsekNm
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*   Reference to Core C File
********************************************************************************
* END_FILE_HDR*/

#ifndef _OSEKNM_CBK_H_
#define _OSEKNM_CBK_H_

/*******************************************************************************
* Include files
********************************************************************************/
#include "OsekNm_Types.h"
#include "CanNm_Types.h"
/*******************************************************************************
* Global Function Prototype
********************************************************************************/
#define OSEKNM_START_SEC_PUBLIC_CODE
#include "MemMap.h"/* PRQA S 5087 */

#if(NM_ACK_CHECK == STD_ON)
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_AckErr
(
    const nmIndexType CanControllerId
);
#endif
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_BusOff
(
    const nmIndexType CanControllerId
);
#ifndef OSEK_NM

#else
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_RxIndication
(
    const PduIdType canNmPduId,
    const Can_IdType canNmRxId,
    CONSTP2CONST(PduInfoType, AUTOMATIC, OSEKNM_APPL_DATA) pCanNmRxPduPtr
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_TxConfirmation
(
    const PduIdType canNmTxPduId
);
#endif

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_WakeUp
(
    const nmIndexType CanControllerId
);
#define OSEKNM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"/* PRQA S 5087 */
#endif
