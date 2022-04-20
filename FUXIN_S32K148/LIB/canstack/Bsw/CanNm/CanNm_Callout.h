/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Callout.h
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
#ifndef _CANNM_CALLOUT_H_
#define _CANNM_CALLOUT_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanNm_Lcfg.h"

#define CANNM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, CANNM_CODE) CanNm_SetUserDataCall
(
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) dataBuffPtr,
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
);


extern FUNC(void, CANNM_CODE) CanNm_GetUserDataCall
(
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) dataBuffPtr,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
);


#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

#endif

