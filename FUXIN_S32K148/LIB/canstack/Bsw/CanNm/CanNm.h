/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Network Management module head File
*   Author          : Hirain
********************************************************************************
*   Description     : CAN Network Management module head File
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

#ifndef _CANNM_H_
#define _CANNM_H_


/*******************************************************************************
*   Includes
*******************************************************************************/

#include "CanNm_Lcfg.h"
#include "CanNm_PBcfg.h"

/**********************************************************************************************************************
* Functions
*********************************************************************************************************************/


/*Development error code*/
#define CANNM_E_NO_INIT                                 ((uint8)0x01u)
#define CANNM_E_INVALID_CHANNEL                         ((uint8)0x02u)
#define CANNM_E_INVALID_PDUID                           ((uint8)0x03u)
#define CANNM_E_NET_START_IND                           ((uint8)0x04u)
#define CANNM_E_INIT_FAILED                             ((uint8)0x05u)
#define CANNM_E_NETWORK_TIMEOUT                         ((uint8)0x11u)
#define CANNM_E_PARAM_POINTER                           ((uint8)0x12u)

#define CANNM_INIT_APIID                                ((uint8)0x00U)
#define CANNM_PASSIVESTARTUP_APIID                      ((uint8)0x01U)
#define CANNM_NETWORKREQUEST_APIID                      ((uint8)0x02U)
#define CANNM_NETWORKRELEAE_APIID                       ((uint8)0x03U)
#define CANNM_SETUSERDATA_APIID                         ((uint8)0x04U)
#define CANNM_GETUSERDATA_APIID                         ((uint8)0x05U)
#define CANNM_GETNODEID_APIID                           ((uint8)0x06U)
#define CANNM_GETLOCALNODEID_APIID                      ((uint8)0x07U)
#define CANNM_RPTMSGREQ_APIID                           ((uint8)0x08U)
#define CANNM_GETPDUDATA_APIID                          ((uint8)0x0AU)
#define CANNM_GETSTATE_APIID                            ((uint8)0x0BU)
#define CANNM_DISABLECOMM_APIID                         ((uint8)0x0CU)
#define CANNM_ENABLECOMM_APIID                          ((uint8)0x0DU)
#define CANNM_MAINFUNC_APIID                            ((uint8)0x13U)
#define CANNM_TRANSMIT_APIID                            ((uint8)0x14U)
#define CANNM_TXCFM_APIID                               ((uint8)0x40U)
#define CANNM_RXIND_APIID                               ((uint8)0x42U)
#define CANNM_REQBUSSYNCH_APIID                         ((uint8)0xC0U)
#define CANNM_CHECKRMTSLEEPIND_APIID                    ((uint8)0xD0U)
#define CANNM_GETVERSIONINFO_APIID                      ((uint8)0xF1U)

#define CANNM_START_SEC_CODE
#include "MemMap.h"
/*[SWS_CanNm_00208]*/
extern FUNC(void, CANNM_CODE) CanNm_Init
( 
    P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_DATA) cannmConfigPtr 
);
/*[SWS_CanNm_00211]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_PassiveStartUp
(
    NetworkHandleType nmChannelHandle
);
/*[SWS_CanNm_00257]*//*[SWS_CanNm_00260]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00213]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRequest
(
    NetworkHandleType nmChannelHandle
);
/*[SWS_CanNm_00214]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRelease
(
    NetworkHandleType nmChannelHandle
);
#endif
/*[SWS_CanNm_00262]*//*[SWS_CanNm_00264]*/
#if(CANNM_COM_CONTROL_ENABLED == STD_ON)
/*[SWS_CanNm_00215]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication
(
    NetworkHandleType nmChannelHandle
);
/*[SWS_CanNm_00216]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication
(
    NetworkHandleType nmChannelHandle
);
#endif
/*[SWS_CanNm_00266]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00158]*/
#if(CANNM_USER_DATA_ENABLED == STD_ON)
/*[SWS_CanNm_00327]*/
#if(CANNM_COM_USER_DATA_SUPPORT == STD_OFF)
/*[SWS_CanNm_00217]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetUserData
(
    NetworkHandleType nmChannelHandle, 
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
);
#endif
#endif
#endif
/*[SWS_CanNm_00268]*/
/*[SWS_CanNm_00158]*/
#if(CANNM_USER_DATA_ENABLED == STD_ON)
/*[SWS_CanNm_00218]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetUserData
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
);
#endif
/*[SWS_CanNm_00330]*/
#if(CANNM_COM_USER_DATA_SUPPORT == STD_ON)
/*[SWS_CanNm_00331]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_Transmit
(
    PduIdType CanNmTxPduId,
    P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduInfoPtr
);
#endif
/*[SWS_CanNm_00270]*//*[SWS_CanNm_00272]*/
#if(CANNM_NODE_ID_ENABLED == STD_ON)
/*[SWS_CanNm_00219]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNodeIdentifier
(
    NetworkHandleType nmChannelHandle,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
);
/*[SWS_CanNm_00220]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetLocalNodeIdentifier 
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
);
#endif
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00274]*/
/*[SWS_CanNm_00135]*/
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
/*[SWS_CanNm_00221]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_RepeatMessageRequest 
(
    NetworkHandleType nmChannelHandle
);
#endif
#endif
/*[SWS_CanNm_00276]*/
#if((CANNM_NODE_DETECTION_ENABLED == STD_ON)||(CANNM_USER_DATA_ENABLED == STD_ON)||(CANNM_NODE_ID_ENABLED == STD_ON))
/*[SWS_CanNm_00222]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetPduData
(
    NetworkHandleType nmChannelHandle,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmPduDataPtr
);
#endif
/*[SWS_CanNm_00223]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetState
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(Nm_StateType, AUTOMATIC, CANNM_APPL_DATA) nmStatePtr,
    P2VAR(Nm_ModeType, AUTOMATIC, CANNM_APPL_DATA) nmModePtr
);
#if(CANNM_VERSION_INFO_API == STD_ON)
/*[SWS_CanNm_00224]*/
extern FUNC(void, CANNM_CODE) CanNm_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CANNM_APPL_DATA) versioninfo
);
#endif
/*[SWS_CanNm_00280]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)

/*[SWS_CanNm_00226]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynchronization
(
    NetworkHandleType nmChannelHandle
);
#endif
/*[SWS_CanNm_00282]*/
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
/*[SWS_CanNm_00227]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_CheckRemoteSleepIndication
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(boolean, AUTOMATIC, CANNM_APPL_DATA) nmRemoteSleepIndPtr
);
#endif
#endif
/*[SWS_CanNm_00340]*/
#if(CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
/*[SWS_CanNm_00338]*/
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetSleepReadyBit
( 
    NetworkHandleType nmChannelHandle, 
    boolean nmSleepReadyBit 
);
#endif
/*[SWS_CanNm_00234]*/
extern FUNC(void, CANNM_CODE) CanNm_MainFunction
(
    void
);
#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

#endif/*_CANNM_H_*/

