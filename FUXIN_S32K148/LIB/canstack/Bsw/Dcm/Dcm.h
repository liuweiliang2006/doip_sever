/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm.c
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Header File 
*   Author          : Hirain
********************************************************************************
*   Description     : Main header file of the AUTOSAR Diagnositc communcation 
*   manager, according to:AUTOSAR_SWS_DiagnosticCommunicationManager.pdf(Release
*   4.0) and ISO14229-1.pdf                      
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
*   02.03.01    30/10/2014    rui.guo       N/A          HrAsrDcm141030-01
*   02.03.02    22/09/2016    rui.guo       N/A          HrAsrDcm160922-01
*   02.04.01    04/11/2016    rui.guo       N/A          HrAsrDcm161104-01
********************************************************************************
* END_FILE_HDR*/

#ifndef _DCM_H_
#define _DCM_H_

#define ISO_14229_2006 STD_ON  
/*******************************************************************************
* Include files
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

#if(ISO_15031_5 == STD_ON)
#include "OBD.h"
#endif

/*******************************************************************************
* Local Macro and Tyedef
*******************************************************************************/
/*PowerOn security access delay*/
#define  DCM_POWERONSECURITYACCESSDELAY                             STD_ON
/*SecurityAcessAttempNumber provided by app*/
#define  DCM_SECACCESSNUMPROVIDEDBYAPP                              STD_OFF
/*PowerOn security access delay only when last delay not finish*/
#define  DCM_POWERONDELAYLASTDELAYNOTFINISH                         STD_OFF
/*Request seed continuous asuse SecurityAcessAttempNumber--*/
#define  DCM_REQUESTSEEDCONTINOUS                                   STD_ON

/*strict seed -Key sequence */
#define  DCM_STRICTSEEDKEYSEQUENCE                                  STD_ON

#define DCM_VENDOR_ID                       (uint16)(0xFFFFu)  /* Supplier ID */
#define DCM_MODULE_ID                       (uint16)(0x0023u)  /* Dcm Moudle ID */
#define DCM_INSTANCE_ID                     ((uint8)0)
/* CanTp Component release Version  */
#define DCM_SW_MAJOR_VERSION                (uint8)(0x01u)
#define DCM_SW_MINOR_VERSION                (uint8)(0x01u)
#define DCM_SW_PATCH_VERSION                (uint8)(0x00u)
/* Autosar release version */
#define DCM_AR_MAJOR_VERSION                (uint8)(0x01u)
#define DCM_AR_MINOR_VERSION                (uint8)(0x00u)
#define DCM_AR_PATCH_VERSION                (uint8)(0x00u)

/* PduIdType */
#define UDS_PHYSICAL_ON_CAN_RX      (0u)
#define UDS_FUNCTIONAL_ON_CAN_RX    (1u) 
#define UDS_FUNCTIONAL_ON_DOIP_RX    (2u)
#define UDS_ON_CAN_TX               (0u)

/* Diagnostic State Machine */
#define DIAG_IDLE                   (0x01u) 
#define DIAG_UDS_INDICATION         (0x02u)
#define DIAG_UDS_PROCESSING         (0x04u)
#define DIAG_UDS_RCRP               (0x08u)
#define DIAG_UDS_RCRP_DONE          (0x10u)
#define DIAG_UDS_PERIODIC_TX        (0x20u)

/* For 0x22 */
typedef struct
{
    uint16  Did;
    uint16  DidPosition; 
}DidlistType;
 
/* For 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
typedef struct
{
    uint8   Did;
    uint16  DidPosition; 
}PeriodicDidlistType;
#endif 

/* For 0x2C */
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
/* 0x00: byDid, 0x01:ByAddress */
typedef struct
{
    uint8 ByDidOrAddress; 
    uint8 DidOrAddressCounter;
}DynamicalDidDefinedSequence;

typedef struct
{
    uint16   SourceDid;
    uint16   SourceDidPosition;
    uint16   PositionInSourceDataRecord;
    uint16   MemorySize;
}DefinedByDid;

typedef struct
{
    uint32   MemoryAddress;
    uint8    AddressSegment;
    uint32   MemorySize;
  
}DefinedByAddress;

typedef struct
{
    uint16 DynamicalDid;
    /* Posicon in gDcmDsdSubService_2C */
    uint8  DynamicalDidPosion;
    uint8  DefinedTime;
    DynamicalDidDefinedSequence  Sequence[DCM_SERVICE_2C_NUMBER_OF_ARRAY];
    /* size should be configurable */
    DefinedByDid  ByDid[DCM_SERVICE_2C_NUMBER_OF_ARRAY];  
    uint8  SourceDidCounter;
    /* size should be configurable */        
    DefinedByAddress  ByAddress[DCM_SERVICE_2C_NUMBER_OF_ARRAY]; 
    uint8  AddessCounter;
    uint32  TotalDataSize;
}DynamicalDidRelatedInfo;
#endif

/******************************************************************************* 
*  Global variables(Scope:global)
*******************************************************************************/ 
#define DCM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
        
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gUDS_Physical_DiagBuffer[UDS_PHYS_BUFFER_SIZE]; 
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gUDS_Functional_DiagBuffer[UDS_FUNC_BUFFER_SIZE]; 
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gUDS_Doip_Functional_DiagBuffer[UDS_DOIP_BUFFER_SIZE];

#if(ISO_15031_5_MultiChannel == STD_ON)
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gOBD_Physical_DiagBuffer[OBD_PHYS_BUFFER_SIZE];
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gOBD_Functional_DiagBuffer[OBD_FUNC_BUFFER_SIZE];
extern VAR(DcmDslBufferSize, DCM_NOINIT_DATA) gDcmDslAvailableBufferSize[DCM_NUMBER_OF_CHANNEL_BUFFER_OBD_INCLUDE];
#else
extern VAR(DcmDslBufferSize, DCM_NOINIT_DATA) gDcmDslAvailableBufferSize[DCM_NUMBER_OF_CHANNEL_BUFFER_WITHOUT_OBD];
#endif 

extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gNegativeResponseBuffer[NEG_RESP_BUFFER_SIZE];
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gNegativeResponseBufferForRRCP[NEG_RESP_BUFFER_SIZE];

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gPeriodicResponseBuffer[PERODIC_RESP_BUFFER_SIZE];
#endif

#if(DCM_SERVICE_86_ENABLED == STD_ON)
extern VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) gResponseOnEventBuffer[EVENT_RESP_BUFFER_SIZE];
#endif

extern VAR(uint16, DCM_NOINIT_DATA)  gResponseLength;   

#if(DCM_SERVICE_27_ENABLED == STD_ON)
extern Dcm_SecLevelType  gSecLevelType;
#endif

extern VAR(Dcm_SesCtrlType, DCM_NOINIT_DATA)  gSesCtrlType;
extern VAR(Dcm_ProtocolType, DCM_NOINIT_DATA)  gActiveProtocol;
extern VAR(Dcm_MsgContextType, DCM_NOINIT_DATA)  gMsgContextType;
extern VAR(VoidEcucSubFunctionNameDef, DCM_NOINIT_DATA) gSubFunctionHandler;
extern VAR(EcucFunctionNameDef, DCM_NOINIT_DATA) gFunctionHandler; 
extern VAR(Dcm_NegativeResponseCodeType, DCM_NOINIT_DATA) gNegativeResponseCode;
extern VAR(uint8, DCM_NOINIT_DATA)  gDiagState;
extern VAR(uint32, DCM_NOINIT_DATA) gP2ServerTimer;
extern VAR(uint32, DCM_NOINIT_DATA) gS3ServerTimer;
extern VAR(uint8, DCM_NOINIT_DATA)  gP2ServerTimerStartFlag;
extern VAR(uint8, DCM_NOINIT_DATA)  gS3ServerTimerStartFlag;

#if(DCM_SERVICE_27_ENABLED == STD_ON)
extern VAR(uint8, DCM_NOINIT_DATA) gSecurityAcessAttempNumber[KIND_OF_SECURITY_LEVEL];   
extern VAR(uint32, DCM_NOINIT_DATA) gSecurityAcessDelayTime[KIND_OF_SECURITY_LEVEL];      
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
extern VAR(uint32, DCM_NOINIT_DATA) gPeriodicResponseRate[NUMBER_OF_PERIODIC_DID];
extern VAR(uint32, DCM_NOINIT_DATA) gPeriodicResponseTimer[NUMBER_OF_PERIODIC_DID];
extern VAR(uint8, DCM_NOINIT_DATA)  PeriodicDidCounter; 
#endif

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
extern VAR(DynamicalDidRelatedInfo, DCM_NOINIT_DATA) gDynamicalDidRelatedInfo[NUMBER_OF_DYN_DID];
extern VAR(uint8, DCM_NOINIT_DATA)  gDynamicalDidCounter;
#endif

#define DCM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/******************************************************************************* 
*  Macro function 
*******************************************************************************/        
#define Set_SecLevel(x)  (gSecLevelType = (x))
#define Set_SesCtrl(x)  (gSesCtrlType = (x))
#define Set_ActiveProtocol(x)  (gActiveProtocol = (x))
#define Clr_ActiveProtocol()  (gActiveProtocol = (0u))
#define Set_PduId(x)  (gMsgContextType.dcmRxPduId = (x))
#define Reset_PduId()  (gMsgContextType.dcmRxPduId = DCM_INVALID_HANDLE_OR_ID)
#define Set_P2_Server_Timer(x)  (gP2ServerTimer = ((x)/DCM_TASK_TIME))
#define Dec_P2_Server_Timer()  (gP2ServerTimer--)
#define Clr_P2_Server_Timer()  (gP2ServerTimer = (uint32)0u)
#define Set_S3_Server_Timer(x)  (gS3ServerTimer = ((x)/DCM_TASK_TIME))
#define Dec_S3_Server_Timer()  (gS3ServerTimer--)
#define Clr_S3_Server_Timer()  (gS3ServerTimer = (uint32)0u)
#define Set_DiagState(x)  (gDiagState |= (x))
/* changed by larry  2013.11.12 QAC */
/*#define Clr_DiagState(x)  (gDiagState &= (~(x)))*/
#define Clr_DiagState(x)  (gDiagState &= (((x) ^ 0xFFu)))
#define Reset_DiagState()  (gDiagState = DIAG_IDLE)
#define GetSuppressPosResponseBit()  (gMsgContextType.msgAddInfo.suppressPosResponse)
#define ClrSuppressPosResponseBit()  (gMsgContextType.msgAddInfo.suppressPosResponse = 0u)
#define SetNegativeResponseCode(x)  (gNegativeResponseCode = (x))
#define ClrNegativeResponseCode()  (gNegativeResponseCode = 0u)
#define Dec_Max_Number_Of_RCRRP()  (gMaxNumberOfRCRRP--)
#define Reset_Max_Number_Of_RCRRP()  (gMaxNumberOfRCRRP = DCM_NUM_MAX_RESPPEND)
#define Make16Bit(HiByte,LoByte)  ((uint16)((((uint16)(HiByte)) << 8u)|((uint16)(LoByte))))
#define Make32Bit(HiByte,MiByte,LoByte)  ((uint32)((((uint32)(HiByte)) << 16)|((uint32)(MiByte) << 8)|((uint32)(LoByte))))

/*******************************************************************************
* extern Function
*******************************************************************************/
/* Defined in AUTOSAR */
#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void,DCM_PUBLIC_CODE) Dcm_Init
(
    CONSTP2CONST(Dcm_ConfigType,AUTOMATIC,DCM_APPL_DATA) ConfigPtr
);
extern FUNC(void,DCM_PUBLIC_CODE) Dsd_InteralInit
(
    void
);
#if (DCM_VERSION_INFO_API == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) Dcm_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType,AUTOMATIC,DCM_APPL_DATA) versionInfo
);
#endif
extern FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetSecurityLevel
(
    CONSTP2VAR(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) SecLevel
);
extern FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetSesCtrlType
(
    CONSTP2VAR(Dcm_SesCtrlType,AUTOMATIC,DCM_APPL_DATA) SesCtrlType
);
extern FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetActiveProtocol
(
    CONSTP2VAR(Dcm_ProtocolType,AUTOMATIC,DCM_APPL_DATA) ActiveProtocol
);
extern FUNC(void,DCM_PUBLIC_CODE) Dcm_MainFunction
(
    void
);

#if(DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DslInternal_RCRResponsePending
(
    const uint8 ForceRCR_RP
);
#endif

extern FUNC(void,DCM_PUBLIC_CODE) DsdInternal_ProcessingDone
(
    CONSTP2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext
);
extern FUNC(void,DCM_PUBLIC_CODE) DsdInternal_ProcessingDoneNoResponse
(
    void
);

#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DsdInternal_DidProcessingDone
(
    void
);
#endif

extern void DsdInternal_SetNegResponse
(
    CONSTP2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext,
    const uint8 ErrorCode
);
/* UDS diagnostic service */
#if(DCM_SERVICE_10_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_DiagnosticSessionControl
(
    void
);
#endif

extern uint8 Dsd_GetSessionMapId
(
    const Dcm_SesCtrlType DcmSessionType
);

#if(DCM_SERVICE_11_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_EcuReset
(
    void
);
#endif

#if(DCM_SERVICE_14_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ClearDiagnosticInformation
(
    void
);
#endif

#if(DCM_SERVICE_19_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadDTCInformation
(
    void
);
#endif

#if(DCM_SERVICE_22_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadDataByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_23_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadMemoryByAddress
(
    void
);
#endif

#if(DCM_SERVICE_24_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadScalingDataByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_27_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_SecurityAccess
(
    void
);
extern void  DsdInternal_SecurityAccessKeyCompared
(
    const uint8 level, 
    const DcmDspSecurityAccessKey keyIsValid
);
#endif

#if(DCM_SERVICE_28_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_CommunicationControl
(
    void
);
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadDataByPeriodicIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_DynamicallyDefinedDataIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_2E_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_WriteDataByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_2F_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_InputOutputControlByIdentifier
(
    void
);
#endif

#if(DCM_SERVICE_31_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE)  DspInternal_Uds_RoutineControl
(
    void
);
extern FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RoutineStarted
(
    void
);
extern FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RoutineStopped
(
    void
);
extern FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RequestRoutineResults
(
    void
);
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_WriteMemoryByAddress
(
    void
);

#endif

#if(DCM_SERVICE_3E_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_TesterPresent
(
    void
);
#endif

#if(DCM_SERVICE_85_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ControlDTCSetting
(
    void
);
#endif

#if(DCM_SERVICE_86_ENABLED == STD_ON)
extern FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ResponseOnEvent
(
    void
);
#endif


#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif
