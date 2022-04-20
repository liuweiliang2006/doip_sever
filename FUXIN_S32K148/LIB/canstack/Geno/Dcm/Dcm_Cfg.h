/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dcm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dcm module configuration File
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
*   04.03.02    16/08/2019     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#ifndef _DCM_CFG_H_
#define _DCM_CFG_H_

/*******************************************************************************
*   Include files
*******************************************************************************/
#include "Dcm_Types.h"
#include "CanTp.h"
/*******************************************************************************
*   Macros and Tyedef
*******************************************************************************/

/*******************************************************************************
*   The following macros are non-configurable
*******************************************************************************/

#define  Dcm_ClearDiagnosticFun                                     App_ClearDiagnosticInformation

#define  UseBlockId                                                 (0x01U)
#define  UseDataClientServer                                        (0x02U)
#define  UseDataSenderReceiver                                      (0x03U)
#define  UseEcuSignal                                               (0x04U)
#define  UseFnc                                                     (0x05U)
#define  DCM_NULL                                                   ((void*)0U)
#define  SUB_FUNCTION_NOT_SUPPORTED                                 (0x00U)
#define  SUB_FUNCTION_SUPPORTED                                     (0x01U)
#define  PHYSICAL_REQ_SUPPORTED                                     (0x01U)
#define  FUNCTIONAL_REQ_SUPPORTED                                   (0x02U)
#define  PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED                      (0x03U)
/* For 0x19 */
#define DCM_REPORTNUMBEROFDTCBYSTATUSMASK                           (0x01U)
#define DCM_REPORTDTCBYSTATUSMASK                                   (0x02U)
#define DCM_REPORTDTCSNAPSHOTIDENTIFICATION                         (0x03U)
#define DCM_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER                      (0x04U)
#define DCM_REPORTDTCSNAPSHOTRECORDBYRECORDNUMBER                   (0x05U)
#define DCM_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER                  (0x06U)
#define DCM_REPORTNUMBEROFDTCBYSEVERITYMASKRECORD                   (0x07U)
#define DCM_REPORTDTCBYSEVERITYMASKRECORD                           (0x08U)
#define DCM_REPORTSEVERITYINFORMATIONOFDTC                          (0x09U)
#define DCM_REPORTSUPPORTEDDTC                                      (0x0AU)
#define DCM_REPORTFIRSTTESTFAILEDDTC                                (0x0BU)
#define DCM_REPORTFIRSTCONFIRMEDDTC                                 (0x0CU)
#define DCM_REPORTMOSTRECENTTESTFAILEDDTC                           (0x0DU)
#define DCM_REPORTMOSTRECENTCONFIRMEDDTC                            (0x0EU)
#define DCM_REPORTMIRRORMEMORYDTCBYSTATUSMASK                       (0x0FU)
#define DCM_REPORTMIRRORMEMORYDTCEXTENDEDDATARECORDBYDTCNUMBER      (0x10U)
#define DCM_REPORTNUMBEROFMIRRORMEMORYDTCBYSTATUSMASK               (0x11U)
#define DCM_REPORTNUMBEROFEMISSIONSRELATEDOBDDTCBYSTATUSMASK        (0x12U)
#define DCM_REPORTEMISSIONSRELATEDOBDDTCBYSTATUSMASK                (0x13U)

/* For 0x27 */
#define REQUEST_SEED_L1                                             (0x01U)
#define SEND_KEY_L1                                                 (0x02U)
#define REQUEST_SEED_L2                                             (0x03U)
#define SEND_KEY_L2                                                 (0x04U)
#define REQUEST_SEED_L3                                             (0x11U)
#define SEND_KEY_L3                                                 (0x12U)

#define REQUEST_SEED_INTER_L1                                       (0x01U)
#define SEND_KEY_INTER_L1                                           (0x02U)
#define REQUEST_SEED_INTER_L2                                       (0x03U)
#define SEND_KEY_INTER_L2                                           (0x04U)
#define REQUEST_SEED_INTER_L3                                       (0x11U)
#define SEND_KEY_INTER_L3                                           (0x12U)

/* Dcm_SecLevelType */
#define DCM_SEC_LEV_LOCK                                            (0x1U)
#define DCM_SEC_LEV_L1                                              (0x2U)
#define DCM_SEC_LEV_L2                                              (0x4U)
#define DCM_SEC_LEV_L3                                              (0x8U)

#define DCM_SEC_LEV_INTER_L1                                        (0x2U)
#define DCM_SEC_LEV_INTER_L2                                        (0x4U)
#define DCM_SEC_LEV_INTER_L3                                        (0x8U)
/* For 0x28 */
#define ENABLE_RX_AND_TX                                            (0x00U)
#define ENBALE_RX_AND_DISABLE_TX                                    (0x01U)
#define DISABLE_RX_AND_ENBALE_TX                                    (0x02U)
#define DISABLE_RX_AND_TX                                           (0x03U)
#define NORMAL_MSG                                                  (0x01U)
#define NM_MSG                                                      (0x02U)
#define BOTH_NORMAL_AND_NM_MSG                                      (0x03U)
/* For 0x2C */
#define DEFINEBYIDENTIFIER                                          (0x01U)
#define DEFINEBYMEMORYADDRESS                                       (0x02U)
#define CLEARDYNAMICALLYDEFINEDDATAIDENTIFIER                       (0x03U)
/* For 0x2F */
#define RETURN_CONTROL_TO_ECU                                       (0x00U)
#define RESET_TO_DEFAULT                                            (0x01U)
#define FREEZE_CURRENT_STATE                                        (0x02U)
#define SHORT_TERM_ADJUSTMENT                                       (0x03U)
/* For 0x31 */
#define START_ROUTINE                                               (0x01U)
#define STOP_ROUTINE                                                (0x02U)
#define REQUEST_ROUTINE_RESULT                                      (0x03U)
/* For 0x3E */
#define ZERO_SUB_FUNCTION                                           (0x00U)
/* For 0x85 */
#define DTC_RECORD_ON                                               (0x01U)
#define DTC_RECORD_OFF                                              (0x02U)
#define DcmTransmit(DcmTxPduId,PduInfoPtr)                          CanTp_Transmit(0,PduInfoPtr)
#define Dcm_DefaultSessionPost(result)                              App_DefaultPost(result)

/*******************************************************************************
*   The following macros are configurable
*******************************************************************************/
#define DCM_DSP_DATA_USE_PORT                                       UseFnc
#define DCM_DEV_ERROR_DETECT                                        STD_OFF
#define DCM_OEM_INDICATION                                          STD_OFF
#define DCM_SUPPLIER_INDICATION                                     STD_OFF
#define DCM_RESPONSE_ALL_REQ                                        STD_OFF
#define DCM_VERSION_INFO_API                                        STD_OFF
/* For 15031-5 */
#define ISO_15031_5                                                 STD_OFF
#define ISO_15031_5_MultiChannel                                    STD_OFF
/* Related to Dcm calling cycle */
#define DCM_TASK_TIME                                               (10UL)
/* Related to 0x78 negative response */
#define DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN                        STD_ON
#define DCM_NUM_MAX_RESPPEND                                        (0xFFFFFFFFUL)
/* Related to customized service */
#define DCM_COSTOMIZED_SERVCIE_SUPPORTED                            STD_OFF
/* Related to Obd service */
/* Related to Uds service */
#define DCM_NUM_OF_SERVICE                                          (11U)
#define DCM_NUM_OF_SUB_SERVICE                                      (NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION +\
											                          NUM_OF_19_SUB_FUNCTION + NUM_OF_27_SUB_FUNCTION +\
											                          NUM_OF_28_SUB_FUNCTION + NUM_OF_2C_SUB_FUNCTION +\
											                          NUM_OF_31_SUB_FUNCTION + NUM_OF_3E_SUB_FUNCTION +\
											                          NUM_OF_85_SUB_FUNCTION + NUM_OF_86_SUB_FUNCTION + 1U)
#define UDS_SERVICE_WITHOUT_SUB_FUNCTION                            (0U)
#define UDS_SERVICE_WITH_SUB_FUNCTION                               (1U)
#define DCM_DSDSIDTABID                                             (1U)
#define DCM_SUBSERVICESTART                                         (0U)

#define DCM_SERVICE_10_ENABLED                                      STD_ON
#define NUM_OF_10_SUB_FUNCTION                                      (3U)
#define KIND_OF_SESSION                                             (3U)
#define DEFAULT_AND_EXTENDED_SEESION_HANDLE                         (DCM_SESSION_DEFAULT  | DCM_SESSION_EXTENDED_DIAGNOSTIC)
#define EXTENDED_SEESION_HANDLE                                     DCM_SESSION_EXTENDED_DIAGNOSTIC
#define RESPONSE_WITH_P2TIMER                                       STD_ON

#define DCM_SERVICE_11_ENABLED                                      STD_ON
#define NUM_OF_11_SUB_FUNCTION                                      (3U)

#define DCM_SERVICE_14_ENABLED                                      STD_ON

#define DCM_SERVICE_19_ENABLED                                      STD_ON
#define NUM_OF_19_SUB_FUNCTION                                      (7U)
#define reportNumberOfDTCByStatusMask                               STD_ON
#define reportDTCByStatusMask                                       STD_ON
#define reportDTCSnapshotIdentification                             STD_OFF
#define reportDTCSnapshotRecordByDTCNumber                          STD_ON
#define reportDTCSnapshotRecordByRecordNumber                       STD_OFF
#define reportDTCExtendedDataRecordByDTCNumber                      STD_ON
#define reportNumberOfDTCBySeverityMaskRecord                       STD_OFF
#define reportDTCBySeverityMaskRecord                               STD_OFF
#define reportSeverityInformationOfDTC                              STD_OFF
#define reportSupportedDTC                                          STD_ON
#define reportFirstTestFailedDTC                                    STD_OFF
#define reportFirstConfirmedDTC                                     STD_OFF
#define reportMostRecentTestFailedDTC                               STD_OFF
#define reportMostRecentConfirmedDTC                                STD_OFF
#define reportMirrorMemoryDTCByStatusMask                           STD_OFF
#define reportMirrorMemoryDTCExtendedDataRecordByDTCNumber          STD_OFF
#define reportNumberOfMirrorMemoryDTCByStatusMask                   STD_OFF
#define reportNumberOfEmissionsRelatedOBDDTCByStatusMask            STD_ON
#define reportEmissionsRelatedOBDDTCByStatusMask                    STD_ON

#define DCM_SERVICE_22_ENABLED                                      STD_ON
#define DCM_SERVICE_22_COMBINED_DID                                 STD_ON
#define MAX_NUM_OF_DID_TO_READ                                      (5U)
#define NUMBER_OF_READ_DID                                          (16U)

#define DCM_SERVICE_23_ENABLED                                      STD_OFF

#define DCM_SERVICE_24_ENABLED                                      STD_OFF

#define DCM_SERVICE_27_ENABLED                                      STD_ON
#define NUM_OF_27_SUB_FUNCTION                                      (6U)
#define KIND_OF_SECURITY_LEVEL                                      (3U)
#define DISABLE_SECURITY_ACCESS_ATTEMPT_NUMBER_RESET                STD_OFF
#define SECURITY_SAVE_ATTEMPT_NUMBER_API                            STD_OFF

#define DCM_SERVICE_28_ENABLED                                      STD_ON
#define NUM_OF_28_SUB_FUNCTION                                      (4U)

#define DCM_SERVICE_2A_ENABLED                                      STD_OFF

#define DCM_SERVICE_2C_ENABLED                                      STD_OFF
#define NUM_OF_2C_SUB_FUNCTION                                      (0U)

#define DCM_SERVICE_2E_ENABLED                                      STD_ON
#define NUMBER_OF_WRITE_DID                                         (4U)

#define DCM_SERVICE_2F_ENABLED                                      STD_OFF

#define DCM_SERVICE_31_ENABLED                                      STD_ON
#define NUM_OF_31_SUB_FUNCTION                                      (3U)
#define NUMBER_OF_RID                                               (2U)

#define DCM_SERVICE_3D_ENABLED                                      STD_OFF

#define DCM_SERVICE_3E_ENABLED                                      STD_ON
#define NUM_OF_3E_SUB_FUNCTION                                      (1U)

#define DCM_SERVICE_85_ENABLED                                      STD_ON
#define NUM_OF_85_SUB_FUNCTION                                      (2U)

#define DCM_SERVICE_86_ENABLED                                      STD_OFF
#define NUM_OF_86_SUB_FUNCTION                                      (0U)

/* Related to diagnostic buffer */
#define DCM_PAGEDBUFFER_ENABLED                                     STD_OFF
#define UDS_FUNC_BUFFER_SIZE                                        (8U)
#define UDS_DOIP_BUFFER_SIZE                                        (512U)
#define UDS_PHYS_BUFFER_SIZE                                        (512U)
#define NEG_RESP_BUFFER_SIZE                                        (3U)
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#define PERODIC_RESP_BUFFER_SIZE                                    (8U)
#endif
/* Additional applicaiton callback */
#define DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL                          STD_OFF

typedef uint32 DcmDslBufferSize;
typedef void   (*EcucFunctionNameDef)(void);
/* removed by larry 2013.11.12 QAC no used for this typedef */
/*
typedef uint8  (*EcucSubFunctionNameDef)(Dcm_MsgContextType*);
*/
typedef void   (*VoidEcucSubFunctionNameDef)(Dcm_MsgContextType* pMsgContext);
typedef void   (*EcucPostSubFunctionNameDef)(Std_ReturnType Result);

/* For Uds service table */
typedef struct
{
    EcucFunctionNameDef DcmDsdSidTabFnc;
    uint8               DcmDsdSidTabSubfuncAvail;
    uint8               DcmDsdSidTabSecurityLevelRef; 
    uint8               DcmDsdSidTabSessionLevelRef;
}DcmDsdService;
typedef struct
{
    uint8         DcmDsdSidTabId;
    DcmDsdService ServiceTable;
    uint8         FirstSubService; /* self-defined */
    uint8         LastSubService;  /* self-defined */
    uint8         AddressingMode;
}DcmDsdServiceTable;

/* For Uds sub-service table */
typedef struct
{
    VoidEcucSubFunctionNameDef  DcmDsdSubFunction;/* self-defined */
    EcucPostSubFunctionNameDef  DcmDsdSubFunctionPost;/* self-defined */
    uint8                       DcmDsdSubServiceId;
    uint8                       DcmDsdSubServiceIdSupported;/* self-defined */
    uint8                       DcmDsdSubServiceSecurityLevelRef;
    uint8                       DcmDsdSubServiceSessionLevelRef;
    uint8                       AddressingMode;/* self-defined */
}DcmDsdSubService;

/* For security access */
typedef struct
{
    /* uint32 DcmDspSecurityADRSize;*/
    uint32 DcmDspSecurityDelayTime;    
    uint32 DcmDspSecurityDelayTimeOnBoot;
    uint32 DcmDspSecurityKeySize;
    uint8  DcmDspSecurityNumAttDelay;
    uint32 DcmDspSecuritySeedSize;
}DcmDspSecurityRow;
typedef enum
{
    KEY_IS_NOT_VALID = 0x00U,
    KEY_IS_VALID = 0x01U
}DcmDspSecurityAccessKey;
/* For session control */
typedef enum
{
    DCM_NO_BOOT,
    DCM_OEM_BOOT,
    DCM_SYS_BOOT
}DcmDspSessionForBoot;
typedef struct 
{
    DcmDspSessionForBoot DcmDspSession;
    uint8                DcmDspSessionLevel;
    uint32               DcmDspSessionP2ServerMax;
    uint32               DcmDspSessionP2StarServerMax;
}DcmDspSessionRow;

/* For 0x22 */
typedef struct
{
    uint32                 DcmDspDidIdentifier;    
    boolean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
    #if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataReadFnc;
    #endif
    #if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
    VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;
    #endif
    uint8                  DcmDspDidReadSecurityLevelRef;
    uint8                  DcmDspDidReadSessionRef;
    uint8                  AddressingMode;
}Dcm_22_ServiceInfoType;

/* For 0x23 */
typedef struct
{
    uint32 DcmDspReadMemoryRangeHigh;
    uint32 DcmDspReadMemoryRangeLow;
    uint8  DcmDspReadMemoryRangeSecurityLevelRef;
    uint8  DcmDspReadMemoryRangeSessionRef;
    uint8  AddressingMode;
}DcmDspReadMemoryRangeInfo;

typedef uint8 Dcm_MemoryAddressFormatType;
typedef uint8 Dcm_MemorySizeFormatType;

/* For 0x24 */
typedef struct
{
    uint32                 DcmDspDidIdentifier;    
    boolean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
    #if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataGetScalingInfoFnc;
    #endif
    #if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
    VoidEcucSubFunctionNameDef DcmDspDataReadEcuSignal;
    #endif
    uint8                  DcmDspDidReadSecurityLevelRef;
    uint8                  DcmDspDidReadSessionRef;
    uint8                  AddressingMode;
}Dcm_24_ServiceInfoType;

/* For 0x2A */
typedef struct
{
    uint8                  DcmDspDidIdentifier;    
    boolean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
    #if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataReadFnc;
    #endif
    uint8                  DcmDspDidReadSecurityLevelRef;
    uint8                  DcmDspDidReadSessionRef;
    uint8                  AddressingMode;
}Dcm_2A_ServiceInfoType;

/* For 0x2C */
typedef struct
{
    uint32                 DcmDspDidIdentifier; 
    uint16                 DcmDspDataSize;
    uint8                  DcmDspDidReadSecurityLevelRef;/* security level must be the same as in 0x22 */
    uint8                  DcmDspDidReadSessionRef;/* session type must be the same as in 0x22 */
    uint8                  AddressingMode;
}Dcm_2C_ServiceInfoType;
/* For 0x2E */
typedef struct
{
    uint32                 DcmDspDidIdentifier;  
    boolean                DcmDspDidUsed;
    uint16                 DcmDspDataSize;
    #if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef DcmDspDataWriteFnc;  
    #endif
    #if(DCM_DSP_DATA_USE_PORT == UseEcuSignal)
    VoidEcucSubFunctionNameDef DcmDspDataEcuSignal;
    #endif
    uint8                  DcmDspDidWriteSecurityLevelRef;
    uint8                  DcmDspDidWriteSessionRef;
    uint8                  AddressingMode;
}Dcm_2E_ServiceInfoType;

/* For 0x2F */
typedef struct
{
    uint32 DcmDspDidControlOptionRecordSize;   /* This define the size of controlOptionRecord without the InputOutputControlParameter */   
    uint32 DcmDspDidControlEnableMaskRecordSize;/* This is only useful when use InputOutputControlParameter */ 
    uint32 DcmDspDidControlStatusRecordSize;    
}DcmDspDidControlRecordSizes;
typedef struct
{
    uint32                       DcmDspDidIdentifier;  
    uint8                        DcmDspDidControlSecurityLevelRef;
    uint8                        DcmDspDidControlSessionRef;
    uint8                        AddressingMode;
    DcmDspDidControlRecordSizes  RecordSizes;
    #if(DCM_DSP_DATA_USE_PORT == UseFnc)
    VoidEcucSubFunctionNameDef   DcmDspDataReturnControlToEcuFnc; 
    VoidEcucSubFunctionNameDef   DcmDspDataResetToDefaultFnc;    
    VoidEcucSubFunctionNameDef   DcmDspDataFreezeCurrentStateFnc; 
    VoidEcucSubFunctionNameDef   DcmDspDataShortTermAdjustmentFnc;
    #endif
    VoidEcucSubFunctionNameDef       OtherFnc;/* self-defined */
}Dcm_2F_ServiceInfoType;

/* For 0x31 */   
typedef struct
{
    uint8  DcmDspRoutineSecurityLevelRef;
    uint8  DcmDspRoutineSessionRef;
    uint8  AddressingMode;
}DcmDspRoutineAuthorization;
typedef struct
{
    uint32 DcmDspRoutineSignalLength;
    /* uint32 DcmDspRoutineSignalPos; */ /* Reserved */  
}DcmDspRoutineSignal;
typedef struct
{
    DcmDspRoutineAuthorization  RoutineAuthorization;
    DcmDspRoutineSignal         DcmDspRoutineRequestResOut;/*not used */
    DcmDspRoutineSignal         DcmDspRoutineStopIn;
    DcmDspRoutineSignal         DcmDspRoutineStopOut;  /*not used */
    DcmDspRoutineSignal         DcmDspStartRoutineIn;
    DcmDspRoutineSignal         DcmDspStartRoutineOut; /*not used */
}DcmDspRoutineInfo;
typedef struct
{
    uint16                      DcmDspRoutineIdentifier;
    boolean                     DcmDspRoutineUsed;     /*not used */
    boolean                     DcmDspRoutineUsePort;/*not used */
    boolean                     DcmDspRoutineFixedLength;
    VoidEcucSubFunctionNameDef  DcmDspStartRoutineFnc;
    VoidEcucSubFunctionNameDef  DcmDspStopRoutineFnc;
    VoidEcucSubFunctionNameDef  DcmDspRequestResultsRoutineFnc;
    DcmDspRoutineInfo           DcmDspRoutineInfoRef;
}DcmDspRoutine;

/* For 0x3D */
typedef struct
{
    uint32 DcmDspWriteMemoryRangeHigh;
    uint32 DcmDspWriteMemoryRangeLow;
    uint8  DcmDspWriteMemoryRangeSecurityLevelRef;
    uint8  DcmDspWriteMemoryRangeSessionRef;
    uint8  AddressingMode;
}DcmDspWriteMemoryRangeInfo;

/* removed by larry QAC reserved for future */
/* For 0x86 */
/*
typedef struct
{
    void(*DcmDspDidRoeActivateFnc)();
    uint32 DcmDspDidRoeEventId;
    boolean DcmDspRoeInitOnDSC;
    uint32  DcmDspRoeInterMessageTime;
    uint16  DcmDspRoeMaxEventLength;
    uint8   DcmDspRoeMaxNumberOfRetry;
    uint16  DcmDspRoeMaxQueueLength;
    boolean DcmDspRoeQueueEnabled;
}DcmDspRoe;
*/
/**************************************************************************************************
*   Pre-compile parameter
**************************************************************************************************/
#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, DCM_CONFIG_CONST) gSidMap_1[DCM_MAX_NUMBER_OF_SID_MAP];
extern CONSTP2CONST(CurrentSidMapType, DCM_CONFIG_CONST, DCM_CONFIG_CONST) gCurrentSidMap;
extern CONST(DcmDsdServiceTable, DCM_CONFIG_CONST)   gServiceTable_1[DCM_NUM_OF_SERVICE];
/* For 0x10,0x11,0x19,0x27,0x28,0x2C,0x31,0x3E,0x85 0x86 */
extern CONST(DcmDsdSubService, DCM_CONFIG_CONST) gDcmDsdSubService[DCM_NUM_OF_SUB_SERVICE];

/**************************************************************************************************
*   Link-compile parameter
**************************************************************************************************/
/* changed by larry 2013.11.11 QAC defination and declaration are not same */
extern CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_CONFIG_CONST) gDcmDspNonDefaultSessionS3Server;
extern CONST(DcmDspSessionRow, DCM_CONFIG_CONST) gDcmDspSessionRow[KIND_OF_SESSION];

#if(DCM_SERVICE_27_ENABLED == STD_ON)
extern CONST(DcmDspSecurityRow, DCM_CONFIG_CONST) gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL];
#endif 

#if(DCM_SERVICE_22_ENABLED == STD_ON)
extern CONST(Dcm_22_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_22[NUMBER_OF_READ_DID];    /* For 0x22 */
#endif

#if((DCM_SERVICE_23_ENABLED == STD_ON)|| (DCM_SERVICE_2C_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
extern CONST(Dcm_MemoryAddressFormatType, DCM_CONFIG_CONST) gMemoryAddressFormat;
extern CONST(Dcm_MemorySizeFormatType, DCM_CONFIG_CONST) gMemorySizeFormat;
#endif

#if(DCM_SERVICE_23_ENABLED == STD_ON)
extern CONST(DcmDspReadMemoryRangeInfo, DCM_CONFIG_CONST) gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG];
#endif

#if(DCM_SERVICE_24_ENABLED == STD_ON)
extern CONST(Dcm_24_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_24[NUMBER_OF_READ_DID_24]; /* For 0x24 */
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
extern CONST(Dcm_2A_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID];/* For 0x2A */
#endif 

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
extern CONST(Dcm_2C_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2C[NUMBER_OF_DYN_DID];     /* For 0x2C */
#endif

#if(DCM_SERVICE_2E_ENABLED == STD_ON)
extern CONST(Dcm_2E_ServiceInfoType, DCM_CONFIG_CONST)  gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID];   /* For 0x2E */
#endif

#if(DCM_SERVICE_2F_ENABLED == STD_ON)
extern CONST(Dcm_2F_ServiceInfoType, DCM_CONFIG_CONST)  gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID]; /* For 0x2F */
#endif

#if(DCM_SERVICE_31_ENABLED == STD_ON)
extern CONST(DcmDspRoutine, DCM_CONFIG_CONST)  DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID];       /* For 0x31 */
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
extern CONST(DcmDspWriteMemoryRangeInfo, DCM_CONFIG_CONST)  gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG];
#endif

#define DCM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**************************************************************************************************
*   Application Callback Function Prototye
**************************************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
extern FUNC(Std_ReturnType,DCM_CODE) App_DiagnosticActive(void);
#endif

#if(DCM_COSTOMIZED_SERVCIE_SUPPORTED == STD_ON)
extern FUNC(void,DCM_CODE) App_CustomizedServcie(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
#endif

#define NUM_OF_DTC   (92U)
extern VAR(uint8, DCM_VARIABLE) DTCStatus[NUM_OF_DTC];

/* 10 */
extern FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 11 */
extern FUNC(void,DCM_CODE) App_Hard_Reset_ResetPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_Hard_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_KeyOffOnReset_ResetPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_KeyOffOnReset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Soft_Reset_ResetPost(Std_ReturnType Result);
extern FUNC(void,DCM_CODE) App_Soft_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 14 */
extern FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 19 */
extern FUNC(void,DCM_CODE) App_Fault_Memory_Read_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_Read_identified_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_Read_snapshot(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_Read_DTC_Extended_Data_Records_By_DTC_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_Read_supported_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_ReadOBDDTCOUNT(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Fault_Memory_ReadOBDDTCINFO(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 22 */
extern FUNC(void,DCM_CODE) App_Read0x2001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF101(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF100(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF112(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF150(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF18B(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF192(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF193(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF194(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF195(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Read0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 27 */
extern VAR(uint8, DCM_VARIABLE)   gSecurityAcessSequence[KIND_OF_SECURITY_LEVEL];
extern FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Request_Seed_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Send_Key_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Request_Seed_L3(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Send_Key_L3(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 28 */
extern FUNC(void,DCM_CODE) App_EnableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_EnableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_DisableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_DisableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 2E */
extern FUNC(void,DCM_CODE) App_Write0x2001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Write0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_Write0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 31 */
extern VAR(uint8, DCM_VARIABLE)  gRountineControlSequence[NUMBER_OF_RID];
extern VAR(uint8, DCM_VARIABLE)  gRountineControlDidHandle;
extern FUNC(void,DCM_CODE) App_StartRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_StopRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_RequestRoutineResults0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_StartRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_StopRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_RequestRoutineResults0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
/* 85 */
extern VAR(uint8, DCM_VARIABLE) gDTCSwitch;
extern FUNC(void,DCM_CODE) App_ON_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);
extern FUNC(void,DCM_CODE) App_OFF_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext);

#endif
