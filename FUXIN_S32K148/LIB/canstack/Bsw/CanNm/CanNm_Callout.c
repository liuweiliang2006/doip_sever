/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Callout.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanNm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanNm module configuration File
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
*   04.03.02    12/09/2017     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/


/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanNm_Callout.h"
#include "Bsw_Common.h"

#define CANNM_USER_DATA_LENGTH                 ((uint8)6u)

#define CANNM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, CANNM_CODE) CanNm_SetUserDataCall
(
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) dataBuffPtr,
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
    Bsw_MemCpy(&dataBuffPtr[(CANNM_PDU_LENGTH - CANNM_USER_DATA_LENGTH)], nmUserDataPtr, 
               CANNM_USER_DATA_LENGTH);
}


FUNC(void, CANNM_CODE) CanNm_GetUserDataCall
(
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) dataBuffPtr,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
    Bsw_MemCpy(nmUserDataPtr, &dataBuffPtr[(CANNM_PDU_LENGTH - CANNM_USER_DATA_LENGTH)], 
               CANNM_USER_DATA_LENGTH);
}


#define CANNM_STOP_SEC_CODE
#include "MemMap.h"
