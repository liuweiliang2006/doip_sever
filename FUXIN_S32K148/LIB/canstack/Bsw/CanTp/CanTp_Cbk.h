/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanTp_Cbk.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CanTp Callback module Source File
*   Author          : qyMa
*                     rui.guo
********************************************************************************
*   Description     : Callback header file of the AUTOSAR CAN Transport Protocol.
*                     The header file contains the declaration of the API used 
*                     by CANIF module.
********************************************************************************
*   Limitations     : 
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    2010/05/24    qyMa          N/A          Original
*   02.00.00    2014/03/11    rui.guo       N/A          N/A   
********************************************************************************
* END_FILE_HDR*/


#ifndef _CANTP_CBK_H_
#define _CANTP_CBK_H_


/*******************************************************************************
* Prototypes of export functions
*******************************************************************************/
#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h"
#include "ComStack_Types.h"

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_RxIndication
(
    PduIdType RxPduId, 
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA)PduInfoPtr
);

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_TxConfirmation
(
    PduIdType CanTpTxPduId
);
#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"


#endif
/* ifndef _CANTP_CBK_H_ */

/*******************************************************************************
 *  END OF FILE: CanTp_Cbk.
 ******************************************************************************/ 

