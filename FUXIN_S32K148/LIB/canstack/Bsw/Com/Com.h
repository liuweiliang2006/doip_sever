/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       Com.h
********************************************************************************
*   Project/Product: COM programme
*   Title:           Com.h
*   Author:          bo.liu        2010-2011
*                    donger.yang   2012-
********************************************************************************
*   Description:     Defination of Interface for Application Layer
* 
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date    Initials      CR#     Descriptions
*   -------   ----------  ----------    ------  -------------------
*   01.00.00  10/08/2010  bo.liu        N/A     Original
*   01.00.01  04/07/2011  bo.liu        N/A     HrAsrCom110407-01
*   01.00.02  05/08/2011  bo.liu        N/A     HrAsrCom110508-01
*   01.00.03  05/20/2011  bo.liu        N/A     HrAsrCom110520-01
*   01.01.00  03/05/2012  donger.yang   N/A     HrAsrCom120305-01
*   02.00.00  05/03/2012  donger.yang   N/A     HrAsrCom120503-01
*   02.01.00  07/01/2012  donger.yang   N/A     HrAsrCom120701-01
*   02.01.01  07/12/2012  donger.yang   N/A     HrAsrCom120712-01
*   02.01.02  07/22/2012  donger.yang   N/A     HrAsrCom120722-01
*   02.01.03  08/01/2012  donger.yang   N/A     HrAsrCom120801-01
*   02.01.04  08/10/2012  donger.yang   N/A     HrAsrCom120810-01
*   02.01.05  08/14/2012  donger.yang   N/A     HrAsrCom120814-01
*   02.01.06  08/17/2012  donger.yang   N/A     HrAsrCom120817-01
*   02.01.07  08/22/2012  donger.yang   N/A     HrAsrCom120822-01
*   02.01.08  08/25/2012  donger.yang   N/A     HrAsrCom120825-01
*   02.01.09  09/04/2012  donger.yang   N/A     HrAsrCom120904-01
*   02.02.00  09/11/2012  donger.yang   N/A     HrAsrCom120911-01
*   02.02.01  10/10/2012  donger.yang   N/A     HrAsrCom121010-01
*   02.02.02  10/17/2012  donger.yang   N/A     HrAsrCom121017-01
*   02.02.03  10/19/2012  donger.yang   N/A     HrAsrCom121019-01
*   02.02.04  10/22/2012  donger.yang   N/A     HrAsrCom121022-01
*   03.00.00  11/08/2012  donger.yang   N/A     HrAsrCom121108-01
*   03.00.01  01/06/2013  donger.yang   N/A     HrAsrCom130106-01
*   03.00.02  03/25/2013  donger.yang   N/A     HrAsrCom130325-01
*   03.00.03  05/03/2013  donger.yang   N/A     HrAsrCom130503-01
*   03.00.04  06/08/2013  donger.yang   N/A     HrAsrCom130608-01 
*   03.00.05  07/30/2013  donger.yang   N/A     HrAsrCom130730-01
*   03.00.06  08/26/2013  donger.yang   N/A     HrAsrCom130826-01    
*   03.01.00  08/30/2013  donger.yang   N/A     HrAsrCom130830-01     
*   03.01.01  01/15/2014  donger.yang   N/A     HrAsrCom140115-01   
*   03.01.02  02/12/2014  donger.yang   N/A     HrAsrCom140212-01   
*   03.01.03  02/24/2014  donger.yang   N/A     HrAsrCom140224-01
*   03.01.04  30/10/2014  rui.guo       N/A     HrAsrCom141030-01
********************************************************************************
*END_FILE_HDR*/

#ifndef _COM_H_
#define _COM_H_
/*******************************************************************************
*   Includes
*******************************************************************************/
 #include "ComStack_Types.h"
 #include "Com_Types.h"
 #include "Com_Cfg.h"

/*******************************************************************************
*   Function Declaration 
*******************************************************************************/
#define COM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

#define COM_VENDOR_ID             (uint16)(0xFFFFu)  /*Supplier ID */
#define COM_MODULE_ID             (uint16)(0x0023u)  /*CanTp Moudle ID */
#define COM_INSTANCE_ID           ((uint8)0)

/* CanTp Component release Version  */
#define COM_SW_MAJOR_VERSION      (uint8)(0x01u)
#define COM_SW_MINOR_VERSION      (uint8)(0x00u)
#define COM_SW_PATCH_VERSION      (uint8)(0x00u)
/* Autosar release version */
#define COM_AR_MAJOR_VERSION      (uint8)(0x04u)
#define COM_AR_MINOR_VERSION      (uint8)(0x00u)
#define COM_AR_PATCH_VERSION      (uint8)(0x00u)

#if(COM_VERSION_INFO_API == STD_ON)
extern FUNC(void,COM_PUBLIC_CODE) Com_GetVersionInfo
(
    P2VAR(Std_VersionInfoType,AUTOMATIC,COM_APPL_DATA) VersionInfo
);
#endif
extern FUNC(void, COM_PUBLIC_CODE) Com_Init
(
    void
);

extern FUNC(void, COM_PUBLIC_CODE) Com_IpduGroupControl
(
    Com_IpduGroupVector IpduGroupVector, 
    boolean Initialize
);


#if (COM_TXIPDUNUM >= 1u)

extern FUNC(void, COM_PUBLIC_CODE) Com_MainFunctionTx
( 
    void 
);

extern FUNC(void, COM_PUBLIC_CODE) Com_TxStart
( 
    void 
);

extern FUNC(void, COM_PUBLIC_CODE) Com_TxStop
( 
    void 
);

extern FUNC(void, COM_PUBLIC_CODE) Com_TriggerIPDUSend
(
    PduIdType PduId
);

#ifndef COM_ENABLE_NONSENDTYPEONLY
extern FUNC(void, COM_PUBLIC_CODE) Com_SetSendRequest
(
    Com_SignalIdType ComTxSignalId
);
#endif

extern FUNC(void, COM_PUBLIC_CODE) Com_StartTxIpdu
(
    PduIdType ComTxPduId
);

extern FUNC(void, COM_PUBLIC_CODE) Com_StopTxIpdu
(
    PduIdType ComTxPduId
);

extern FUNC(uint8, COM_PUBLIC_CODE) Com_GetTxIpduStatus
(
    PduIdType ComTxPduId
);

extern FUNC(uint8, COM_PUBLIC_CODE) Com_SendSignal
(
    Com_SignalIdType ComTxSignalId,
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SignalDataPtr
);

/*#if (COM_TXIPDUNUM >= 1u)*/
#endif

#if (COM_RXIPDUNUM >= 1u)

extern FUNC(void, COM_PUBLIC_CODE) Com_MainFunctionRx
(
    void
);

extern FUNC(void, COM_PUBLIC_CODE)  Com_RxStart
(
    void
);

extern FUNC(void, COM_PUBLIC_CODE) Com_RxStop
( 
    void 
);

extern FUNC(void, COM_PUBLIC_CODE) Com_StartRxIpdu
(
    PduIdType ComRxPduId
);

extern FUNC(void, COM_PUBLIC_CODE) Com_StopRxIpdu
(
    PduIdType ComRxPduId
);

extern FUNC(uint8, COM_PUBLIC_CODE) Com_GetRxIpduStatus
(
    PduIdType ComRxPduId
);

extern FUNC(uint16, COM_PUBLIC_CODE) Com_GetRxIpduLength
(
    PduIdType ComRxPduId
);

extern FUNC(uint8, COM_PUBLIC_CODE) Com_ReceiveSignal
(
    Com_SignalIdType ComRxSignalId, 
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SignalDataPtr
);

/*#if (COM_RXIPDUNUM >= 1u)*/
#endif


#ifdef COM_ENABLE_ROUTESIGNAL

#if(COM_GWSIGNUM >= 1u)

extern FUNC(void, COM_PUBLIC_CODE)  Com_MainFunctionRouteSignals
(
    void
);
/*
#if(COM_GWSIGNUM >= 1u)
*/
#endif
/*#ifdef COM_ENABLE_ROUTESIGNAL*/
#endif

#define COM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif




