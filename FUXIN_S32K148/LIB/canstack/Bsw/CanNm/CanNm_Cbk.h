/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Cbk.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Network Management module call back head File
*   Author          : Hirain
********************************************************************************
*   Description     : CAN Network Management module call back head File
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
*   01.00.00    02/09/2016    liya.zhu      N/A          Original
********************************************************************************
* END_FILE_HDR*/

#ifndef _CANNM_CBK_H_
#define _CANNM_CBK_H_


/*******************************************************************************
*   Includes
*******************************************************************************/
#include "CanNm_Types.h"
/**********************************************************************************************************************
* Functions
*********************************************************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"
/*[SWS_CanNm_00284]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
/*[SWS_CanNm_00228]*/
extern FUNC(void, CANNM_CODE) CanNm_TxConfirmation
(
    PduIdType TxPudId
);
#endif

/*[SWS_CanNm_00231]*/
extern FUNC(void, CANNM_CODE) CanNm_RxIndication 
(
    PduIdType RxPudId,
    const uint16 RxId,
    P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA)PduInfoPtr 
);
#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

#endif/*_CANNM_CBK_H_*/

