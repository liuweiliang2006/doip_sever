/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Cbk.h
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Header File 
*   Author          : Hirain
********************************************************************************
*   Description     : Callback header file of the AUTOSAR DCM module,according 
*   to: AUTOSAR_SWS_DiagnosticCommunicationManager.pdf (Release 4.0) and 
*   ISO14229-1.pdf.
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
*   01.00.00    12/03/2010    xyliu         N/A          Original
*   01.02.01    22/12/2011    xyliu         N/A          HrAsrDcm111222-01
*   01.02.02    12/09/2012    dongeryang    N/A          HrAsrDcm120912-01
*   02.00.01    27/07/2013    jinbiao.li    N/A          HrAsrDcm130727-01
*   02.00.02    14/08/2013    jinbiao.li    N/A          HrAsrDcm130814-01
*   02.00.03    19/08/2013    jinbiao.li    N/A          HrAsrDcm130819-01
*   02.00.04    27/08/2013    jinbiao.li    N/A          HrAsrDcm130827-01
*   02.01.00    03/09/2013    jinbiao.li    N/A          HrAsrDcm130903-01
*   02.02.00    20/02/2014    wenrui.li     N/A          HrAsrDcm140220-01
*   02.03.00    11/04/2014    wenrui.li     N/A          HrAsrDcm140411-01
********************************************************************************
* END_FILE_HDR*/

#ifndef _DCM_CBK_H_
#define _DCM_CBK_H_

/*******************************************************************************
* Include files
********************************************************************************/
#include "ComStack_Types.h"
/*******************************************************************************
* Global Function Prototype
********************************************************************************/
#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_StartOfReception
(
    const PduIdType     DcmRxPduId,
    const PduLengthType TpSduLength,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) Length
);

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyRxData
(
    const PduIdType  DcmRxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPointer,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  RxBufferSizePtr
);

extern FUNC(void,DCM_PUBLIC_CODE) Dcm_RxIndication
(
    const PduIdType       DcmRxPduId,
    const NotifResultType Result
);

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyTxData
(
    const PduIdType  DcmTxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPtr,
    CONSTP2CONST(RetryInfoType,AUTOMATIC,DCM_APPL_DATA)  RetryInfoPtr,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  TxDataCntPtr
);

extern FUNC(void,DCM_PUBLIC_CODE) Dcm_TxConfirmation
(
    const PduIdType       DcmTxPduId,
    const NotifResultType Result
);

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif
