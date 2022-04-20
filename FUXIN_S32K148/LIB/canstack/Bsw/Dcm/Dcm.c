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
*   Title           : Dcm module Source File 
*   Author          : Hirain
********************************************************************************
*   Description     : Main source file of the AUTOSAR Diagnositc communcation 
*   manager, according to:AUTOSAR_SWS_DiagnosticCommunicationManager.pdf(Release
*   4.0) and ISO14229-1.pdf.
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
*   02.03.01    29/10/2014    rui.guo       N/A          HrAsrDcm141029-01
*   02.03.02    30/10/2014    rui.guo       N/A          HrAsrDcm141030-01
*   02.03.03    11/11/2014    rui.guo       N/A          HrAsrDcm141111-01
*   02.03.04    14/11/2014    rui.guo       N/A          HrAsrDcm141114-01
*   02.03.05    22/07/2016    rui.guo       N/A          HrAsrDcm160722-01
*   02.03.06    29/07/2016    rui.guo       N/A          HrAsrDcm160729-01
*   02.03.07    22/09/2016    rui.guo       N/A          HrAsrDcm160922-01
*   02.03.08    29/09/2016    rui.guo       N/A          HrAsrDcm160929-01
*   02.04.00    01/11/2016    rui.guo       N/A          HrAsrDcm161101-01
*   02.04.01    04/11/2016    rui.guo       N/A          HrAsrDcm161104-01
*   02.04.02    17/11/2016    rui.guo       N/A          HrAsrDcm161117-01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Dcm.h"

/*******************************************************************************
* Global variables(Scope:global)
*******************************************************************************/
#define DCM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) 
                                gUDS_Physical_DiagBuffer[UDS_PHYS_BUFFER_SIZE];
              
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)   
                              gUDS_Functional_DiagBuffer[UDS_FUNC_BUFFER_SIZE];

VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)
                              gUDS_Doip_Functional_DiagBuffer[UDS_DOIP_BUFFER_SIZE];

#if(ISO_15031_5_MultiChannel == STD_ON)
VAR(DcmDslBufferSize, DCM_NOINIT_DATA)  
          gDcmDslAvailableBufferSize[DCM_NUMBER_OF_CHANNEL_BUFFER_OBD_INCLUDE];
#else
VAR(DcmDslBufferSize, DCM_NOINIT_DATA)  
          gDcmDslAvailableBufferSize[DCM_NUMBER_OF_CHANNEL_BUFFER_WITHOUT_OBD];
#endif
 
#if(ISO_15031_5 == STD_ON)
#if(ISO_15031_5_MultiChannel == STD_ON)
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)   
                                gOBD_Physical_DiagBuffer[OBD_PHYS_BUFFER_SIZE];
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)   
                              gOBD_Functional_DiagBuffer[OBD_FUNC_BUFFER_SIZE];
#endif
#endif

VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)  
                                 gNegativeResponseBuffer[NEG_RESP_BUFFER_SIZE];
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)  
                          gNegativeResponseBufferForRRCP[NEG_RESP_BUFFER_SIZE];

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA)   
                             gPeriodicResponseBuffer[PERODIC_RESP_BUFFER_SIZE];
#endif

#if(DCM_SERVICE_86_ENABLED == STD_ON)
VAR(Dcm_MsgItemType, DCM_NOINIT_DATA) 
                                gResponseOnEventBuffer[EVENT_RESP_BUFFER_SIZE];
#endif

VAR(uint16, DCM_NOINIT_DATA)  gResponseLength;   

#if(DCM_SERVICE_27_ENABLED == STD_ON)
VAR(Dcm_SecLevelType, DCM_NOINIT_DATA)  gSecLevelType;
#endif

VAR(Dcm_SesCtrlType, DCM_NOINIT_DATA)  gSesCtrlType;
VAR(Dcm_ProtocolType, DCM_NOINIT_DATA)  gActiveProtocol;
VAR(Dcm_MsgContextType, DCM_NOINIT_DATA) gMsgContextType;
VAR(Dcm_NegativeResponseCodeType, DCM_NOINIT_DATA)  gNegativeResponseCode;
VAR(uint8, DCM_NOINIT_DATA)  gDiagState;
VAR(uint32, DCM_NOINIT_DATA)  gP2ServerTimer;
VAR(uint32, DCM_NOINIT_DATA)  gS3ServerTimer;
VAR(uint8, DCM_NOINIT_DATA)  gP2ServerTimerStartFlag;
VAR(uint8, DCM_NOINIT_DATA)  gS3ServerTimerStartFlag;

#if(DCM_SERVICE_27_ENABLED == STD_ON)
/* Default value,used for Delay time on boot for 0x27 */
VAR(uint8, DCM_NOINIT_DATA) gCurrentSecurityIndex;
VAR(uint8, DCM_NOINIT_DATA) gSecurityDelayFlag[KIND_OF_SECURITY_LEVEL];
VAR(uint8, DCM_NOINIT_DATA) gSecurityAcessAttempNumber[KIND_OF_SECURITY_LEVEL];
VAR(uint32, DCM_NOINIT_DATA)  gSecurityAcessDelayTime[KIND_OF_SECURITY_LEVEL]; 
VAR(uint8, DCM_NOINIT_DATA)  gSecurityAcessSequence[KIND_OF_SECURITY_LEVEL];
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
VAR(uint32, DCM_NOINIT_DATA)  gPeriodicResponseRate[NUMBER_OF_PERIODIC_DID];
VAR(uint32, DCM_NOINIT_DATA)  gPeriodicResponseTimer[NUMBER_OF_PERIODIC_DID]; 
VAR(uint8, DCM_NOINIT_DATA)  PeriodicDidCounter;
#endif

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
VAR(DynamicalDidRelatedInfo, DCM_NOINIT_DATA) gDynamicalDidRelatedInfo[NUMBER_OF_DYN_DID];
VAR(uint8, DCM_NOINIT_DATA)  gDynamicalDidCounter;
#endif

#if(DCM_SERVICE_31_ENABLED == STD_ON)
VAR(uint8, DCM_NOINIT_DATA)  gRountineControlSequence[NUMBER_OF_RID];
VAR(uint8, DCM_NOINIT_DATA)  gRountineControlDidHandle;
#endif

VAR(EcucFunctionNameDef, DCM_NOINIT_DATA)  gFunctionHandler;
VAR(VoidEcucSubFunctionNameDef, DCM_NOINIT_DATA)  gSubFunctionHandler;
 
/*******************************************************************************
* Global variables(Scope:local)
*******************************************************************************/
STATIC VAR(DCM_InitType, DCM_CONFIG_DATA) DCM_InitStatus = DCM_UNINITIALIZED;
STATIC VAR(DcmDsdServiceTable, DCM_PRIVATE_CODE) service;
STATIC VAR(EcucPostSubFunctionNameDef, DCM_PRIVATE_CODE)  
                                                       gSubFunctionPostHandler;
STATIC VAR(uint32, DCM_PRIVATE_CODE)  gMaxNumberOfRCRRP;
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gSubServicePosition;

/* change from global to internal by larry 2013.11.11 */
STATIC VAR(uint8, DCM_NOINIT_DATA)  gCurrentSessionType;
/*
#if(DCM_SERVICE_27_ENABLED == STD_ON)
STATIC VAR(Dcm_SecLevelType, DCM_NOINIT_DATA)   
                                 gSecLevelForCurrentSecurityAccessRequestLevel;
#endif
*/

#if(DCM_SERVICE_22_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gDidPosition;
STATIC VAR(DidlistType, DCM_PRIVATE_CODE)  DidList[MAX_NUM_OF_DID_TO_READ];
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
STATIC VAR(Dcm_MsgType, DCM_PRIVATE_CODE)  gDidResData;
/* change into #if #endif by larry 2013.11.11 */
STATIC VAR(Dcm_MsgLenType, DCM_PRIVATE_CODE)  gDidResDataLen;
#endif
#endif 

#if(DCM_SERVICE_24_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gNumberOfReadDID_24;
#endif

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
STATIC VAR(PeriodicDidlistType, DCM_PRIVATE_CODE)  
                                       PeriodicDidList[NUMBER_OF_PERIODIC_DID];
/* move into function as it only be used once larry 20140116 */
/* STATIC VAR(PeriodicDidlistType, DCM_PRIVATE_CODE)  CurrentPeriodicDid; */
STATIC VAR(uint16, DCM_PRIVATE_CODE)  CurrentPeriodicDidIndx;
STATIC VAR(uint16, DCM_PRIVATE_CODE) 
                                 gPeriodicResponseFlag[NUMBER_OF_PERIODIC_DID];
#endif

#if(DCM_SERVICE_22_ENABLED == STD_ON) 
STATIC VAR(uint16, DCM_PRIVATE_CODE)  DidCounter;
#endif 

#if(DCM_SERVICE_2E_ENABLED == STD_ON) 
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gNumberOfWriteDID;
#endif

#if(DCM_SERVICE_2F_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gNumberOfIOCtrlDID;
#endif

#if(DCM_SERVICE_2C_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_PRIVATE_CODE)  gReadDID_2C_Active_Flag;
#endif


STATIC VAR(uint8, DCM_PRIVATE_CODE)  gDcm_RepeatTransmitFlag;
/* removed by larry according to QAC 2013.11.11 */
/* STATIC VAR(uint8, DCM_PRIVATE_CODE)  gDcm_CurrentServiceSubfuncAvail; */

#define DCM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
* Local Function Prototype
*******************************************************************************/
/* Self-defined */
#define DCM_START_SEC_PRIVATE_CODE
#include "MemMap.h"

STATIC FUNC(uint8,DCM_PRIVATE_CODE)  FindUdsSid(const uint8 RequestSid);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_UdsSidDispatcher(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_RepeatTransmitCheck(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_Periodic_Transmit(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_DidDispatcher(void);

/* chenged by larry  2013.11.11 QAC */
#if(DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN != STD_ON)
STATIC FUNC(void,DCM_PRIVATE_CODE)  
                        DslInternal_RCRResponsePending(const uint8 ForceRCR_RP);
#endif

STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_10_11_85(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_AccessAttemptNumberDec(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_UdsRepeatServiceCall(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_UdsPostServiceProcessing(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DslInternal_Timer_CallbackTask(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_Uds_Common(void);
STATIC FUNC(void,DCM_PUBLIC_CODE)  Dcm_ResetToDefaultSession(void);
STATIC FUNC(void,DCM_PRIVATE_CODE)  
                            DsdInternal_SessionTransferPostProcessing(void);
/* add by larry. 2013.11.11 QAC no declaration */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType,DCM_PUBLIC_CODE) 
                            Dcm_GetSecurityLevelMap(CONSTP2CONST(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) ReqSecLevel);
#endif


#define DCM_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"
 
/*******************************************************************************
* Global Function Implementation
*******************************************************************************/

#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_Init
*                
* Description:   Initial Dcm module's global variable 
*                             
* Inputs:        ConfigPtr: Pointer pointing to the configure parameter of Dcm
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) Dcm_Init
(
    CONSTP2CONST(Dcm_ConfigType,AUTOMATIC,DCM_CONFIG_DATA) ConfigPtr
)
{
    uint16 i;
    (void) ConfigPtr;
    
    #if(ISO_15031_5 == STD_ON)
    {
        Init_SupportedPID();
    } 
    #endif

    Dsd_InteralInit();
    Set_SesCtrl(DCM_DEFAULT_SESSION);
    gCurrentSessionType = DCM_SESSION_DEFAULT;
    Clr_S3_Server_Timer();
    
    /* removed by larry according to QAC 2013.11.11 */
    /*gDcm_CurrentServiceSubfuncAvail = UDS_SERVICE_WITHOUT_SUB_FUNCTION;*/
    
    #if(ISO_15031_5_MultiChannel == STD_ON)
    gDcmDslAvailableBufferSize[DCM_INDEX_0] = (uint32)UDS_PHYS_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[DCM_INDEX_1] = (uint32)UDS_FUNC_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[DCM_INDEX_2] = (uint32)OBD_PHYS_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[3] = (uint32)OBD_FUNC_BUFFER_SIZE;
    #else
    gDcmDslAvailableBufferSize[DCM_INDEX_0] = (uint32)UDS_PHYS_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[DCM_INDEX_1] = (uint32)UDS_FUNC_BUFFER_SIZE;
    gDcmDslAvailableBufferSize[DCM_INDEX_2] = (uint32)UDS_DOIP_BUFFER_SIZE;
    #endif
    
    for(i = 0u; i < UDS_PHYS_BUFFER_SIZE; i++)
    {
        gUDS_Physical_DiagBuffer[i] = 0u;
    }

    for(i = 0u; i < UDS_FUNC_BUFFER_SIZE; i++)
    {
        gUDS_Functional_DiagBuffer[i] = 0u;
    }

    for(i = 0u; i < UDS_DOIP_BUFFER_SIZE; i++)
    {
    	gUDS_Doip_Functional_DiagBuffer[i] = 0u;
    }
    service = gServiceTable_1[DCM_INDEX_0];
    
    #if(DCM_SERVICE_22_ENABLED == STD_ON)
    for(i = 0u; i < MAX_NUM_OF_DID_TO_READ; i++)
    {
        DidList[i].Did = DCM_SERVICE_22_NO_DID_TO_STORE;
        DidList[i].DidPosition = DCM_SERVICE_22_NO_DIDPOSITION_TO_STORE;  
    }
    gDidPosition = 0u; 
    DidCounter = 0u;

    
    /* change into #if #endif by larry 2013.11.11 */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    gDidResDataLen = 0u;
    #endif
    #endif  

    #if(DCM_SERVICE_24_ENABLED == STD_ON)
    gNumberOfReadDID_24 = NUMBER_OF_READ_DID_24;
    #endif
    
    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    for(i = 0u;i < KIND_OF_SECURITY_LEVEL;i++)
    {
        gSecurityAcessSequence[i] = 0u;
        /*gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;*/
        /*gSecurityAcessAttempNumberExceeded[i] = 0;*/
#if(DCM_POWERONSECURITYACCESSDELAY == STD_ON)
        gSecurityDelayFlag[i] = DCM_FLAG_ACTIVE;
        gSecurityAcessDelayTime[i] = gDcmDspSecurityRow[i].DcmDspSecurityDelayTimeOnBoot/DCM_TASK_TIME;

    #if(DCM_SECACCESSNUMPROVIDEDBYAPP == STD_ON)
        if(gSecurityAcessAttempNumber[i] > gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay)
        {
            gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
        }
    #else
        gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
    #endif
#else
    #if(DCM_SECACCESSNUMPROVIDEDBYAPP == STD_ON)
        #if(DCM_POWERONDELAYLASTDELAYNOTFINISH == STD_ON)
        if(gSecurityAcessAttempNumber[i] == 0)
        {
            gSecurityAcessAttempNumber[i] = 1;
            gSecurityDelayFlag[i] = DCM_FLAG_ACTIVE;
        }
        else
        {
            gSecurityDelayFlag[i] = DCM_FLAG_DISACTIVE;
            if(gSecurityAcessAttempNumber[i] > gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay)
            {
                gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
            }
        }
        #else    
        if(gSecurityAcessAttempNumber[i] != gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay)
        {
            gSecurityAcessAttempNumber[i] = 1;
            gSecurityDelayFlag[i] = DCM_FLAG_ACTIVE;
        }
        else
        {
            gSecurityDelayFlag[i] = DCM_FLAG_DISACTIVE;
        }
        #endif
    #else
        gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
        gSecurityDelayFlag[i] = DCM_FLAG_DISACTIVE;
    #endif
        gSecurityAcessDelayTime[i] = gDcmDspSecurityRow[i].DcmDspSecurityDelayTime/DCM_TASK_TIME;
#endif
    }
    gSecLevelType = DCM_SEC_LEV_LOCK;
    gCurrentSecurityIndex = 0;
    /*gSecLevelForCurrentSecurityAccessRequestLevel = 0u;*/

    #endif
    
    #if(DCM_SERVICE_2A_ENABLED == STD_ON)
    for(i = 0u; i < PERODIC_RESP_BUFFER_SIZE;i++)
    {
        gPeriodicResponseBuffer[i] = 0u;
    }
    
    for(i = 0u; i < NUMBER_OF_PERIODIC_DID; i++)
    {
        gPeriodicResponseRate[i] = (uint32)0u;
        gPeriodicResponseTimer[i] = (uint32)0u;
        gPeriodicResponseFlag[i] = DCM_FLAG_DISACTIVE;
    }
    
    PeriodicDidCounter = 0u;
    #endif

    #if(DCM_SERVICE_2C_ENABLED == STD_ON)
    for(i = 0u; i < NUMBER_OF_DYN_DID; i++)
    {
        gDynamicalDidRelatedInfo[i].DynamicalDid = DCM_ALL_BITS_ON_16;
        gDynamicalDidRelatedInfo[i].DynamicalDidPosion = 0u;
        gDynamicalDidRelatedInfo[i].SourceDidCounter = 0u;
        gDynamicalDidRelatedInfo[i].AddessCounter = 0u;
        gDynamicalDidRelatedInfo[i].TotalDataSize = (uint32)0u;
        gDynamicalDidRelatedInfo[i].DefinedTime = 0u;
    }
    gDynamicalDidCounter = 0u;
    gReadDID_2C_Active_Flag = STD_OFF;
    #endif
    
    #if(DCM_SERVICE_2E_ENABLED == STD_ON) 
    gNumberOfWriteDID = NUMBER_OF_WRITE_DID;
    #endif

    #if(DCM_SERVICE_2F_ENABLED == STD_ON)
    gNumberOfIOCtrlDID = NUMBER_OF_CONTROL_DID;
    #endif

    #if(DCM_SERVICE_31_ENABLED == STD_ON)
    #if(NUMBER_OF_RID > 0u) 
    gRountineControlDidHandle = DCM_INVALID_HANDLE_OR_ID; 
    for(i = 0u; i < NUMBER_OF_RID; i++)
    {
        gRountineControlSequence[i] = 0u;
    }
    #endif
    #endif 
    
    #if(DCM_SERVICE_86_ENABLED == STD_ON)
    for(i = 0u;i < EVENT_RESP_BUFFER_SIZE;i++)
    {
        gResponseOnEventBuffer[i] = 0u;
    }
    #endif

    gResponseLength = 0u;   
    gNegativeResponseCode = DCM_E_POSITIVERESPONSE;
    gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
    gSubFunctionPostHandler = DCM_NULL;
    gMaxNumberOfRCRRP = DCM_NUM_MAX_RESPPEND;
    gSubServicePosition = 0u;
    gDcm_RepeatTransmitFlag = DCM_FLAG_DISACTIVE;
  
    DCM_InitStatus = DCM_INITIALIZED;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_GetVersionInfo
*                
* Description:   Get Dcm's version 
*                             
* Inputs:        versionInfo: Pointer pointing to the version info of Dcm
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (DCM_VERSION_INFO_API == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) Dcm_GetVersionInfo
(
    CONSTP2VAR(Std_VersionInfoType,AUTOMATIC,DCM_APPL_DATA) versionInfo
)
{
    versionInfo->vendorID = DCM_VENDOR_ID;
    versionInfo->moduleID = DCM_MODULE_ID;
    versionInfo->instanceID = DCM_INSTANCE_ID;
    versionInfo->sw_major_version = DCM_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = DCM_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = DCM_SW_PATCH_VERSION;
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_GetSecurityLevel
*                
* Description:   Get Dcm's Security Level
*                             
* Inputs:        SecLevel: Active Security Level value
*                
* Outputs:       result: Always be OK
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_27_ENABLED == STD_ON)
FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetSecurityLevel
(
    CONSTP2VAR(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) SecLevel
)
{   
    Std_ReturnType Result = E_OK;
    uint8 i = 0;   
    Dcm_SecLevelType temp;
        
    if(SecLevel == DCM_NULL)
    {
        Result = E_NOT_OK;
    }
    else
    {
        temp = gSecLevelType;
        for(i = 0;i < KIND_OF_SECURITY_LEVEL;i++)
        {
            if(1 == (temp >> i))
            {
                *SecLevel = i;
            }
        }
    }
    return Result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_GetSecurityLevelMap
*                
* Description:   Map Request_seed_Lx and Send_key_lx to the same result
*                             
* Inputs:        ReqSecLevel: Request security sub Function data
*                
* Outputs:       result: The according Security Level
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetSecurityLevelMap
(
    CONSTP2CONST(Dcm_SecLevelType,AUTOMATIC,DCM_APPL_DATA) ReqSecLevel
)
{
    const uint8 SecLevel = *ReqSecLevel;
    uint8 SecLevel_Int;   
    Std_ReturnType result;
    
    switch(SecLevel)
    {                  
#if defined(REQUEST_SEED_INTER_L1) && defined(SEND_KEY_INTER_L1)  
        case  REQUEST_SEED_INTER_L1:                                 
        case  SEND_KEY_INTER_L1:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L1;
            gCurrentSecurityIndex = 0;
        }
        break; 
#endif         
#if defined(REQUEST_SEED_INTER_L2) && defined(SEND_KEY_INTER_L2)                                            
        case  REQUEST_SEED_INTER_L2:                                
        case  SEND_KEY_INTER_L2:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L2;
            gCurrentSecurityIndex = 1;
        }
        break; 
#endif
#if defined(REQUEST_SEED_INTER_L3) && defined(SEND_KEY_INTER_L3)  

        case  REQUEST_SEED_INTER_L3:                                  
        case  SEND_KEY_INTER_L3:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L3;
            gCurrentSecurityIndex = 2;
        }
        break; 
#endif
#if defined(REQUEST_SEED_INTER_L4) && defined(SEND_KEY_INTER_L4)  
        case  REQUEST_SEED_INTER_L4:                               
        case  SEND_KEY_INTER_L4:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L4;
            gCurrentSecurityIndex = 3;
        }
        break;        
#endif
#if defined(REQUEST_SEED_INTER_L5) && defined(SEND_KEY_INTER_L5)  

        case  REQUEST_SEED_INTER_L5:                                
        case  SEND_KEY_INTER_L5:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L5;
            gCurrentSecurityIndex = 4;
        }
        break;          
#endif
#if defined(REQUEST_SEED_INTER_L6) && defined(SEND_KEY_INTER_L6)  

        case  REQUEST_SEED_INTER_L6:                               
        case  SEND_KEY_INTER_L6:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L6;
            gCurrentSecurityIndex = 5;
        }
        break;          
#endif
#if defined(REQUEST_SEED_INTER_L7) && defined(SEND_KEY_INTER_L7)  

        case  REQUEST_SEED_INTER_L7:                                 
        case  SEND_KEY_INTER_L7:
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L7;
            gCurrentSecurityIndex = 6;
        }
        break;         
#endif                                      
            
        default: 
        {
            SecLevel_Int = DCM_SEC_LEV_INTER_L1; 
            gCurrentSecurityIndex = 0;
        }
        break;

    }

    return SecLevel_Int;
}

#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_GetSesCtrlType
*                
* Description:   Get current session type
*                             
* Inputs:        SesCtrlType: Active session type
*                
* Outputs:       result: Always be OK
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetSesCtrlType            
(
    CONSTP2VAR(Dcm_SesCtrlType,AUTOMATIC,DCM_APPL_DATA) SesCtrlType
)
{
    Std_ReturnType Result = E_OK;
        
    if(SesCtrlType == DCM_NULL)
    {
        Result = E_NOT_OK;
    }
    else
    {
        *SesCtrlType = gCurrentSessionType;
    }
    return Result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_GetActiveProtocol
*                
* Description:   Get current active protocol
*                             
* Inputs:        SesCtrlType: Active portocol type
*                
* Outputs:       result: The active protocol
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType,DCM_PUBLIC_CODE) Dcm_GetActiveProtocol
(
    CONSTP2VAR(Dcm_ProtocolType,AUTOMATIC,DCM_APPL_DATA) ActiveProtocol
)
{
    Std_ReturnType Result = E_OK;
        
    if(ActiveProtocol == DCM_NULL)
    {
        Result = E_NOT_OK;
    }
    else
    {
        *ActiveProtocol = 0x00u;   /* stand for UDS protocol */
    }
    return Result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_ResetToDefaultSession
*                
* Description:   Turn current session mode into default mode
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PUBLIC_CODE) Dcm_ResetToDefaultSession 
(
    void
)
{
    #if(DCM_SERVICE_2A_ENABLED == STD_ON)
    uint16 i;
    {
        /* Clear all periodicDid info in PeriodicDidList */ 
        for(i = 0u;i < NUMBER_OF_PERIODIC_DID;i++)
        {
            PeriodicDidList[i].Did = 0u;
            PeriodicDidList[i].DidPosition = 0u;
            gPeriodicResponseFlag[i] = 0u;
            gPeriodicResponseRate[i] = (uint32)0u;
            gPeriodicResponseTimer[i] = (uint32)0u;
        }
        PeriodicDidCounter = 0u;
    }
    #endif
    Set_SesCtrl(DCM_SESSION_DEFAULT);
    gCurrentSessionType = DCM_SESSION_DEFAULT;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_MainFunction
*                
* Description:   The main processing Function
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/   
FUNC(void,DCM_PUBLIC_CODE) Dcm_MainFunction
(
    void
)
{   
    /* add judgement of DCM_InitStatus by larry 2013.11.11 */
    if(DCM_InitStatus == DCM_INITIALIZED)
    {
        DsdInternal_UdsPostServiceProcessing();
        DsdInternal_UdsRepeatServiceCall();
        DslInternal_Timer_CallbackTask(); 

        #if(ISO_15031_5 == STD_ON)
        DsdInternal_ObdSidDispatcher();
        #endif
        DsdInternal_RepeatTransmitCheck();
        DsdInternal_UdsSidDispatcher();
         
        #if(DCM_SERVICE_2A_ENABLED == STD_ON)
        DsdInternal_Periodic_Transmit();  
        #endif
    }
    else
    {
        /* No Init yet, do nothing */
    }
}

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"


#define DCM_START_SEC_PRIVATE_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DslInternal_Timer_CallbackTask
*                
* Description:   The timer processing function
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE) DslInternal_Timer_CallbackTask(void) 
{
    uint8 SessionId;
    
    #if((DCM_SERVICE_2A_ENABLED == STD_ON) || (DCM_SERVICE_27_ENABLED == STD_ON))
    uint8 i;
    #endif
    
    /* for 0x27, access delay time */
    #if (DCM_SERVICE_27_ENABLED == STD_ON)                           
    for(i = 0u;i < KIND_OF_SECURITY_LEVEL;i++)
    {
        if(gSecurityDelayFlag[i] == DCM_FLAG_ACTIVE) 
        {
            if (gSecurityAcessDelayTime[i] != 0) 
            {
                gSecurityAcessDelayTime[i]--;

                if(gSecurityAcessDelayTime[i] == 0)
                {
                    gSecurityDelayFlag[i] = DCM_FLAG_DISACTIVE;
                    gSecurityAcessDelayTime[i] = gDcmDspSecurityRow[i].DcmDspSecurityDelayTime/DCM_TASK_TIME;
                    gSecurityAcessSequence[i] = 0u;

                    if(gSecurityAcessAttempNumber[i] == 0)
                    {
                        gSecurityAcessAttempNumber[i] = 1u;
                    }
                }
            } 
        }
    }
#endif    
    /* S3 Timer */
    if (gS3ServerTimerStartFlag == DCM_FLAG_ACTIVE) 
    {
        if (gS3ServerTimer != (uint32)DCM_TIME_EXPIRED) 
        {
            Dec_S3_Server_Timer();
            if (gS3ServerTimer == (uint32)DCM_TIME_EXPIRED) 
            {
                Dcm_ResetToDefaultSession();
                gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
                Dcm_DefaultSessionPost(E_OK);
                DsdInternal_SessionTransferPostProcessing();
                
                #if(DCM_SERVICE_27_ENABLED == STD_ON)
                for (i = 0u; i < KIND_OF_SECURITY_LEVEL; i++) 
                {
                    gSecurityAcessSequence[i] = 0u;
                }
                gSecLevelType = DCM_SEC_LEV_LOCK;
                #endif
                
            } 
            else 
            {
            }
        } 
        else 
        {
        }
    } 
    else 
    {
    }
     /* P2 and P2* timer  */
    if (gP2ServerTimerStartFlag == DCM_FLAG_ACTIVE)
    {
        Dec_P2_Server_Timer();
        if (gMaxNumberOfRCRRP != (uint32)0u)
        {
            /*Dec_P2_Server_Timer();*/
            /* If P2 timeout,send first 0x78 negative response and change P2 to P2Ext */
            DslInternal_RCRResponsePending(UNFORCERCR_RP);
            /* If P2Ext timeout,send following 0x78 negative response */
            SessionId = Dsd_GetSessionMapId(gSesCtrlType);
            if ((gP2ServerTimer > (gDcmDspSessionRow[SessionId].DcmDspSessionP2ServerMax/ DCM_TASK_TIME)) 
            &&  (gP2ServerTimer < (((gDcmDspSessionRow[SessionId].DcmDspSessionP2StarServerMax/DCM_TASK_TIME)) >> DCM_DIVIDE_TOW)))
            {
                DslInternal_RCRResponsePending(FORCERCR_RP);
            }
            else
            {
            }
        } 
        else if(gP2ServerTimer == 0)
        {
            DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_GENERALREJECT);
            DsdInternal_ProcessingDone(&gMsgContextType);
            /*Set_DiagState(DIAG_UDS_RCRP_DONE);*/
            gP2ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        }
        else
        {

        }
    } 
    else 
    {
    }
    /* For 0x2A */
    #if(DCM_SERVICE_2A_ENABLED == STD_ON)
    if((gDiagState & DIAG_IDLE) == DIAG_IDLE)
    {
        for(i = 0u; i < PeriodicDidCounter; i++)
        {
            if(gPeriodicResponseTimer[PeriodicDidList[i].DidPosition] > (uint32)0u)
            {
                gPeriodicResponseTimer[PeriodicDidList[i].DidPosition]--;
            }
            else
            {
            }
        }
    }
    else
    {
    }
    #endif
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DslInternal_RCRResponsePending
*                
* Description:   used for 0x78 negative response
*                             
* Inputs:        ForceRCR_RP: Parameter to decide the 0x78 send method
*                
* Outputs:       None
* 
* Limitations:   None  
********************************************************************************
END_FUNCTION_HDR*/
/* changed by larry according to QAC 2013.11.11 */
#if(DCM_DSL_DIAG_RESP_FORCE_RESP_PEND_EN == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DslInternal_RCRResponsePending
#else
STATIC FUNC(void,DCM_PRIVATE_CODE)  
                             DslInternal_RCRResponsePending
#endif
(
    const uint8 ForceRCR_RP
)
{
    PduInfoType temp;
    uint8 SessionId;
    
    if((gP2ServerTimer <= (uint32)1u)  ||  (ForceRCR_RP == FORCERCR_RP))  
    {
        Set_DiagState(DIAG_UDS_RCRP);
       
        gNegativeResponseBufferForRRCP[DCM_INDEX_0] = DCM_NEGATIVE_RES_SERVICE_ID;
        gNegativeResponseBufferForRRCP[DCM_INDEX_1] = gUDS_Physical_DiagBuffer[DCM_SID_POSITION];
        gNegativeResponseBufferForRRCP[DCM_INDEX_2] = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;
        
        temp.SduDataPtr = gNegativeResponseBufferForRRCP;
        temp.SduLength = (uint16)NEG_RESP_BUFFER_SIZE;

        /* Transmite 0x78 negative response(NR) */
        (void)DcmTransmit(gMsgContextType.dcmRxPduId,&temp);
        
        /* Decrease the allowed maximum number of 0x78 NR */
        Dec_Max_Number_Of_RCRRP();

        SessionId = Dsd_GetSessionMapId(gSesCtrlType);
        Set_P2_Server_Timer(gDcmDspSessionRow[SessionId].DcmDspSessionP2StarServerMax);
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_DiagnosticSessionControl
*                
* Description:   Implementation of Uds servie 0x10
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_10_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_DiagnosticSessionControl
(
    void
)
{
    DsdInternal_10_11_85();
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_EcuReset
*                
* Description:   Implementation of Uds servie 0x11
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_11_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_EcuReset
(
    void
) 
{   
    DsdInternal_10_11_85();
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ClearDiagnosticInformation
*                
* Description:   Implementation of Uds servie 0x14
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_14_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ClearDiagnosticInformation
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_14_REQ_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        gSubFunctionHandler = &Dcm_ClearDiagnosticFun;
        if(gSubFunctionHandler != DCM_NULL)
        {
            (*gSubFunctionHandler)(&gMsgContextType);
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ReadDTCInformation
*                
* Description:   Implementation of Uds servie 0x19 
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_19_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadDTCInformation
(
    void
)
{
    /*ClrSuppressPosResponseBit();*/

    switch(gMsgContextType.reqData[DCM_INDEX_1])
    {
        #if(reportNumberOfDTCByStatusMask == STD_ON)
        case DCM_REPORTNUMBEROFDTCBYSTATUSMASK:
        #endif
        
        #if(reportDTCByStatusMask == STD_ON)
        case DCM_REPORTDTCBYSTATUSMASK:
        #endif
        
        #if(reportDTCSnapshotRecordByRecordNumber == STD_ON)
        case DCM_REPORTDTCSNAPSHOTRECORDBYRECORDNUMBER:
        #endif
        
        #if(reportMirrorMemoryDTCByStatusMask == STD_ON)
        case DCM_REPORTMIRRORMEMORYDTCBYSTATUSMASK:
        #endif
        
        #if(reportNumberOfMirrorMemoryDTCByStatusMask == STD_ON)
        case DCM_REPORTNUMBEROFMIRRORMEMORYDTCBYSTATUSMASK:
        #endif
        
        #if(reportNumberOfEmissionsRelatedOBDDTCByStatusMask == STD_ON)
        case DCM_REPORTNUMBEROFEMISSIONSRELATEDOBDDTCBYSTATUSMASK:
        #endif
        #if(reportEmissionsRelatedOBDDTCByStatusMask == STD_ON)
        case DCM_REPORTEMISSIONSRELATEDOBDDTCBYSTATUSMASK:
        #endif
        
        #if((reportNumberOfDTCByStatusMask == STD_ON) \
           || (reportDTCByStatusMask == STD_ON) \
           || (reportDTCSnapshotRecordByRecordNumber == STD_ON) \
           || (reportMirrorMemoryDTCByStatusMask == STD_ON) \
           || (reportNumberOfMirrorMemoryDTCByStatusMask == STD_ON) \
           || (reportNumberOfEmissionsRelatedOBDDTCByStatusMask == STD_ON) \
           || (reportEmissionsRelatedOBDDTCByStatusMask == STD_ON))
        if(gMsgContextType.reqDataLen != (uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        }
        break;
        #endif
        
        
        #if(reportDTCSnapshotRecordByDTCNumber == STD_ON) 
        case DCM_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER:
        #endif
        
        #if(reportDTCExtendedDataRecordByDTCNumber == STD_ON) 
        case DCM_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER:
        #endif
        #if(reportMirrorMemoryDTCExtendedDataRecordByDTCNumber == STD_ON) 
        case DCM_REPORTMIRRORMEMORYDTCEXTENDEDDATARECORDBYDTCNUMBER:
        #endif
        
        #if((reportDTCSnapshotRecordByDTCNumber == STD_ON) \
           || (reportDTCExtendedDataRecordByDTCNumber == STD_ON) \
           || (reportMirrorMemoryDTCExtendedDataRecordByDTCNumber == STD_ON))
        if(gMsgContextType.reqDataLen != (uint32)DCM_REQUIRE_DATA_LENGTH_6_BYTE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        }
        break;
        #endif 
        
        #if(reportDTCSnapshotIdentification == STD_ON) 
        case DCM_REPORTDTCSNAPSHOTIDENTIFICATION:
        #endif
        
        #if(reportSupportedDTC == STD_ON)
        case DCM_REPORTSUPPORTEDDTC:
        #endif
        
        #if(reportFirstTestFailedDTC == STD_ON)
        case DCM_REPORTFIRSTTESTFAILEDDTC:
        #endif
        
        #if(reportFirstConfirmedDTC == STD_ON)
        case DCM_REPORTFIRSTCONFIRMEDDTC:
        #endif
        
        #if(reportMostRecentTestFailedDTC == STD_ON)
        case DCM_REPORTMOSTRECENTTESTFAILEDDTC:
        #endif
        
        #if(reportMostRecentConfirmedDTC == STD_ON)
        case DCM_REPORTMOSTRECENTCONFIRMEDDTC:
        #endif
        
        #if((reportDTCSnapshotIdentification == STD_ON) \
           || (reportSupportedDTC == STD_ON) \
           || (reportFirstTestFailedDTC == STD_ON) \
           || (reportFirstConfirmedDTC == STD_ON) \
           || (reportMostRecentTestFailedDTC == STD_ON) \
           || (reportMostRecentConfirmedDTC == STD_ON))
        if(gMsgContextType.reqDataLen != (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        }
        break;
        #endif
        
        #if(reportNumberOfDTCBySeverityMaskRecord == STD_ON)
        case DCM_REPORTNUMBEROFDTCBYSEVERITYMASKRECORD:
        #endif
        
        #if(reportDTCBySeverityMaskRecord == STD_ON)
        case DCM_REPORTDTCBYSEVERITYMASKRECORD:
        #endif
        
        #if((reportNumberOfDTCBySeverityMaskRecord == STD_ON) \
           || (reportDTCBySeverityMaskRecord == STD_ON))
        if(gMsgContextType.reqDataLen != DCM_REQUIRE_DATA_LENGTH_4_BYTE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        }
        break;
        #endif
        
        #if(reportSeverityInformationOfDTC == STD_ON)
        case DCM_REPORTSEVERITYINFORMATIONOFDTC:
        if(gMsgContextType.reqDataLen != DCM_REQUIRE_DATA_LENGTH_5_BYTE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        else
        {
        }
        break;
        #endif
        
        default:
        break;
    }
    if(gNegativeResponseCode == DCM_E_POSITIVERESPONSE)
    {
        DsdInternal_Uds_Common();
    }
    else
    {
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ReadDataByIdentifier
*                
* Description:   Implementation of Uds servie 0x22
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_22_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE)DspInternal_Uds_ReadDataByIdentifier
(
    void
)
{
    /* the correct request length should be even number and bigger than 0 */
    gMsgContextType.reqDataLen -= (uint32)1u; 
     
    /* Check message format */
	if(gMsgContextType.reqDataLen < 2)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else if((gMsgContextType.reqDataLen&0x01uL) != (uint32)0u)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else if((gMsgContextType.reqDataLen >> DCM_DIVIDE_TOW) > (uint32)MAX_NUM_OF_DID_TO_READ)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        DsdInternal_DidDispatcher();
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ReadMemoryByAddress
*                
* Description:   Implementation of Uds servie 0x23
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_23_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadMemoryByAddress
(
    void
)
{
    uint8  securitylevel;
    uint8  sessiontype;
    uint8  addressFormat;
    uint8  sizeFormat;
    uint8  i;
    uint32 startAddress = (uint32)0u;
    uint32 memorySize = (uint32)0u;

    addressFormat = (gMsgContextType.reqData[DCM_INDEX_1] & DCM_SERVICE_23_GET_MEMORY_AND_ADDRESS_BYTE_LOW_NIBBLE);
    sizeFormat = (gMsgContextType.reqData[DCM_INDEX_1] >> DCM_SERVICE_23_GET_MEMORY_AND_ADDRESS_BYTE_HIGH_NIBBLE);

    /*min length check, at least 4*/
    if(gMsgContextType.reqDataLen < 4)
   	{
   	    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);  
   	}
    /* Check addressAndLengthFormatIdentifier */
    else if((addressFormat != gMemoryAddressFormat) || (sizeFormat != gMemorySizeFormat))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    
    /* Check message format */ 
    else if(gMsgContextType.reqDataLen != 
        (DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH + gMemoryAddressFormat + gMemorySizeFormat))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        /* Calculate start address */
        for(i = 0u; i < gMemoryAddressFormat; i++)
        {
            startAddress |= (uint32)(gMsgContextType.reqData[DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH + i])  
                    << (DCM_AMPLIFY_8_TIMES *(gMemoryAddressFormat -1u -i));      
        }
        
        /* Calculate size  */
        for(i = 0u; i < gMemorySizeFormat;i++)
        {
            memorySize |= (uint32)(gMsgContextType.reqData[DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH + gMemoryAddressFormat+i])
                       << (DCM_AMPLIFY_8_TIMES*(gMemorySizeFormat-1-i)); 
        }
        /* Check the scope of the address in requested message */
        for(i = 0u; i < NUMBER_OF_READ_ADDRESS_SEG; i++)
        {
            if((startAddress >= gDcmDspReadMemoryRangeInfo_23[i].DcmDspReadMemoryRangeLow)
            && ((startAddress + memorySize)<= 1u + gDcmDspReadMemoryRangeInfo_23[i].DcmDspReadMemoryRangeHigh))
            {
                sessiontype = gDcmDspReadMemoryRangeInfo_23[i].DcmDspReadMemoryRangeSessionRef;
                securitylevel = gDcmDspReadMemoryRangeInfo_23[i].DcmDspReadMemoryRangeSecurityLevelRef;
                break;
            }
        }
        /* is parametre supported ?*/
        if(i == NUMBER_OF_READ_ADDRESS_SEG)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
        /* Check session condition */
        else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
		        /* Check security access conditon */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
        else if((securitylevel & gSecLevelType ) == DCM_SECURITY_LEVEL_NOT_CORRECT)                
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
        }
#endif
        /* Check adressing mode */
        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
        && ((gDcmDspReadMemoryRangeInfo_23[i].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
        {
            /* Service is not supported under functional request,but do
                         not send 0x11 negative response */
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }
        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
        && (((gDcmDspReadMemoryRangeInfo_23[i].AddressingMode) & PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
        {
            /* Service is not supported under physical request, send 
                         negative response */ 
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }

        else
        {
            App_ReadAddress(&gMsgContextType,startAddress,memorySize);
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ReadScalingDataByIdentifier
*                
* Description:   Implementation of Uds servie 0x24
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_24_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadScalingDataByIdentifier
(
    void
)
{
    uint8  i;
    uint8  error = DCM_HAVE_NO_ERRORS;
    uint16 tempdid;
    uint8  didposition = 0u;
    uint8  securitylevel;
    uint8  sessiontype;
    
    /* Check message format */
    if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_24_REQ_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        error = DCM_HAVE_ERRORS;
    }
    else
    {
        tempdid = Make16Bit(gMsgContextType.reqData[DCM_INDEX_1],gMsgContextType.reqData[DCM_INDEX_2]);
        for(i = 0u; i < gNumberOfReadDID_24; i++)
        {
            if(tempdid == gDcmDsdSubService_24[i].DcmDspDidIdentifier)
            {
                securitylevel
                = gDcmDsdSubService_24[didposition].DcmDspDidReadSecurityLevelRef;
                sessiontype = gDcmDsdSubService_24[didposition].DcmDspDidReadSessionRef;
                
                /* Check if the requested DID supported */
                if(gDcmDsdSubService_24[didposition].DcmDspDidUsed != 1u)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                    error = DCM_HAVE_ERRORS;
                }
                
                /* Check Session condition */
                else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                    error = DCM_HAVE_ERRORS; 
                }
                
                /* Check adressing mode */
                else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                && ((gDcmDsdSubService_24[didposition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                {
                    /* Service is not supported under functional request,but do
                                 not send 0x31 negative response */
                     
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                    error = DCM_HAVE_ERRORS; 
                }
                else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                    && ((gDcmDsdSubService_24[didposition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == 0u))
                {
                    /* Service is not supported under physical request,
                                 send negative response */ 
                     
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                    error = DCM_HAVE_ERRORS;  
                }
                
                /* Check security acess condition */
                #if(DCM_SERVICE_27_ENABLED == STD_ON)
                else if(securitylevel != 0u)
                {
                    if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                        error = DCM_HAVE_ERRORS; 
                    }
                    else
                    {
                    }
                }
                #endif
                else
                {
                }
                didposition = i;
                i = gNumberOfReadDID_24;
            }
            else
            { 
                if(i == (gNumberOfReadDID_24 - 1u))
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE); 
                    error = DCM_HAVE_ERRORS;
                }
                else
                {
                }
            }
        }
    }
    
    if(error == DCM_HAVE_NO_ERRORS)
    {
        /* If no error happend,give positive response */
        gSubFunctionHandler = gDcmDsdSubService_24[didposition].DcmDspDataGetScalingInfoFnc;
        if(gSubFunctionHandler != DCM_NULL)
        {
            (*gSubFunctionHandler)(&gMsgContextType);
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
    }
    else
    {
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_SecurityAccess
*                
* Description:   Implementation of Uds servie 0x27
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/* there is only one kind of security access level at a time */
#if(DCM_SERVICE_27_ENABLED == STD_ON)

FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_SecurityAccess
(
    void
)
{
    uint8 i;
    uint8 level;

    /*ClrSuppressPosResponseBit();*/

    level = Dcm_GetSecurityLevelMap(&gMsgContextType.reqData[DCM_INDEX_1]);
#if 0
    /* Check whether the delay time on-boot has elapsed */
    if(gSecurityDelayFlag != DCM_FLAG_DISACTIVE)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
    }
    
    /* If attempt number is over the limit, check whether the delay time has elapsed */
    else 
#endif

    /*   Get Seed   */
    if((gMsgContextType.reqData[DCM_INDEX_1]&1u) != DCM_SERVICE_27_SEND_KEEY) 
    {

        /* Check message format */
        if (gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH)  
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
			gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
        }
		/* Check the delay flag */
		else if(gSecurityDelayFlag[gCurrentSecurityIndex] == DCM_FLAG_ACTIVE)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
			gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
        }
        
        /* Check the requested security leve has already been cracked, if so, send zero seeds */
        else if (gSecLevelType == level)
        {               
            gMsgContextType.resData[DCM_INDEX_1] = gMsgContextType.reqData[DCM_INDEX_1];
            for (i = 0u; i < gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecuritySeedSize; i++)
            {
                gMsgContextType.resData[DCM_SERVICE_AND_SUB_SERVICE_RESPONSE_LENGTH + i] = 0x00u;
            }

            /* Record latest request's level */
            /*gCurrentSecurityIndex = gSecLevelForCurrentSecurityAccessRequestLevel;*/
            /*if the requested level is already unlocked,Send NCR 0x24 when Key is received*/
            /*gSecurityAcessSequence[gCurrentSecurityIndex] = HAVE_GOTTON_SEED;*/
            gMsgContextType.resDataLen = 
                (gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecuritySeedSize + (uint32)DCM_SERVICE_AND_SUB_SERVICE_RESPONSE_LENGTH);    
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
        #if(DCM_REQUESTSEEDCONTINOUS == STD_ON)
        else if(gSecurityAcessSequence[gCurrentSecurityIndex] == HAVE_GOTTON_SEED)
        {
            if(gSecurityAcessAttempNumber[gCurrentSecurityIndex] != 0u)
            {
                gSecurityAcessAttempNumber[gCurrentSecurityIndex]--;
                if(gSecurityAcessAttempNumber[gCurrentSecurityIndex] == 0u)
                {
                    /*gSecurityAcessAttempNumberExceeded[gCurrentSecurityIndex - 1] = 1u;*/
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
                    /*gSecurityAcessAttempNumber[gCurrentSecurityIndex] = 1u;*/ /*gDcmDspSecurityRow[gCurrentSecurityIndex - 1u].DcmDspSecurityNumAttDelay;*/
                    gSecurityDelayFlag[gCurrentSecurityIndex] = DCM_FLAG_ACTIVE;
					gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
                }
                else
                {
                    /*DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INVALIDKEY);*/
                    gMsgContextType.resDataLen = 
                        (gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecuritySeedSize + (uint32)DCM_SERVICE_AND_SUB_SERVICE_RESPONSE_LENGTH); 
                    gSubFunctionHandler = gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;
                    if(gSubFunctionHandler != DCM_NULL)
                    {
                        (*gSubFunctionHandler)(&gMsgContextType);
                    }
                    else
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
						gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
                    }
                }
            }
            else
            {
                /*gSecurityAcessAttempNumberExceeded[gCurrentSecurityIndex - 1] = 1u;*/
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUIREDTIMEDELAYNOTEXPIRED);
                /*gSecurityAcessAttempNumber[gCurrentSecurityIndex] = 1u;*/ /*gDcmDspSecurityRow[gCurrentSecurityIndex - 1u].DcmDspSecurityNumAttDelay;*/
                gSecurityDelayFlag[gCurrentSecurityIndex] = DCM_FLAG_ACTIVE;
				gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
            }
        }
        #endif
        /* If not, call related appliction callback function to get the seeds */
        else 
        {
            /*gCurrentSecurityIndex = gSecLevelForCurrentSecurityAccessRequestLevel;*/
            gSecurityAcessSequence[gCurrentSecurityIndex] = HAVE_GOTTON_SEED;
            gMsgContextType.resDataLen = 
                (gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecuritySeedSize + (uint32)DCM_SERVICE_AND_SUB_SERVICE_RESPONSE_LENGTH); 
            gSubFunctionHandler = gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;
            if(gSubFunctionHandler != DCM_NULL)
            {
                (*gSubFunctionHandler)(&gMsgContextType);
            }
            else
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
				gSecurityAcessSequence[gCurrentSecurityIndex] = 0;
            }
        }
    }

    /*   Send Key  */
    else
    {

        /**/
        /* Check message format */
        if (gMsgContextType.reqDataLen != 
            (gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecurityKeySize + (uint32)DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH))
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        }
        /**/        
        else
        {   
            /* Check whether the client has already gotten the seeds */
            if((gSecurityAcessSequence[gCurrentSecurityIndex]&HAVE_GOTTON_SEED) != HAVE_GOTTON_SEED)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR);
            }
            /* Check whether the send-key request's level is equal to latest get-seed request */
            #if 0
            else if(gCurrentSecurityIndex != gSecLevelForCurrentSecurityAccessRequestLevel)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR);
            }
            #endif
            else
            {
                /* Call related application callback funtion to compare the key */
                gSubFunctionHandler = gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;
                if(gSubFunctionHandler != DCM_NULL)
                {
                    (*gSubFunctionHandler)(&gMsgContextType);
                }
                else
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                }
            }
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_CommunicationControl
*                
* Description:   Implementation of Uds servie 0x28
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_28_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_CommunicationControl
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_28_REQ_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    
    /* Check communication type */
    else if(((gMsgContextType.reqData[DCM_INDEX_2]&BOTH_NORMAL_AND_NM_MSG) == 0u)
           || (gMsgContextType.reqData[DCM_INDEX_2] > DCM_REQUIRE_DATA_LENGTH_3_BYTE))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    else
    {
        DsdInternal_Uds_Common();
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ReadDataByPeriodicIdentifier
*                
* Description:   Implementation of Uds servie 0x2A
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if((DCM_SERVICE_2A_ENABLED == STD_ON) && (DCM_SERVICE_22_ENABLED == STD_ON))
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ReadDataByPeriodicIdentifier
(
    void
)
{
    uint32 i;
    uint32 j;
    uint8  securitylevel;
    uint8  sessiontype;
    PeriodicDidlistType temp_periodicdidlist[NUMBER_OF_PERIODIC_DID];
    uint8  counter = 0u;
    uint8  temp;
    uint8  error = DCM_HAVE_NO_ERRORS;
    uint8  SupportedDIDNum = 0u;
    /* removed temp */
    /* const static PeriodicDidlistType CurrentPeriodicDid;*/

    /* init temp_periodicdidlist[0] as flag */
    temp_periodicdidlist[DCM_INDEX_0].Did = DCM_ALL_BITS_ON_8;

    /* is number request DIDs   < = MAXNUMDIDs */
    /* Check transfer mode */
    if(gMsgContextType.reqDataLen > (NUMBER_OF_PERIODIC_DID + DCM_REQUIRE_DATA_LENGTH_2_BYTE))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT); 
        error = DCM_HAVE_ERRORS;
    }
    else
    {
        if(gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_STOP_SENDING)
        {
            if(gMsgContextType.reqDataLen < (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                /* let error on, so below code could not be processed */
                error = DCM_HAVE_ERRORS;
            }
            /* if reqdata only has two bytes, it means clear all */
            else if(gMsgContextType.reqDataLen == (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
            {
                /* Clear all periodicDid info in PeriodicDidList */ 
                for(i = (uint32)0u; i < (uint32)NUMBER_OF_PERIODIC_DID; i++)
                {
                    PeriodicDidList[i].Did = DCM_SERVICE_2A_NO_PERIODIC_DID_TO_STORE;
                    PeriodicDidList[i].DidPosition = DCM_SERVICE_2A_NO_PERIODIC_DIDPOSITION_TO_STORE;
                    gPeriodicResponseFlag[i] = DCM_FLAG_DISACTIVE;
                    gPeriodicResponseRate[i] = (uint32)0u;
                    gPeriodicResponseTimer[i] = (uint32)0u;
                }
                PeriodicDidCounter = 0u;
                gMsgContextType.resDataLen = (uint32)1u;
                /* let error on, so below code could not be processed */
                error = DCM_HAVE_ERRORS;
                DsdInternal_ProcessingDone(&gMsgContextType);
            }
            /* clear specify one */
            else 
            {
                /* do nothing, so below code could be processed */
            }
        }
        else if((gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_FAST_RATE)
               || (gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_MEDIUM_RATE)
               || (gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_SLOW_RATE))
        {
            if(gMsgContextType.reqDataLen < (uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                error = DCM_HAVE_ERRORS;
            }
            else
            {
                /* do nothing, so below code could be processed */
            }
        }
        else
        {
            /* out of parameters */          
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE); 
            error = DCM_HAVE_ERRORS;
        }

        if(error == DCM_HAVE_NO_ERRORS)
        {
            if(gMsgContextType.reqDataLen > (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
            {
                 /* Check whether a particular periodicDataIdentifier multiple times within a single request message */
                for(i = (uint32)0u; i < (gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE); i++)
                {
                    for(j = (i + (uint32)1u); j <= (gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE); j++)
                    {
                        if(gMsgContextType.reqData[i + (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE] 
                            == gMsgContextType.reqData[j + (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE])
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                            error = DCM_HAVE_ERRORS;
                            i = gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE;
                            j = gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE;
                        }
                        else
                        {
                            /* do nothing, so below code could be processed */
                        }
                    }
                }
            }
            else
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT); 
                error = DCM_HAVE_ERRORS;
            }
        }
        
        if(error == DCM_HAVE_NO_ERRORS)
        {
            /* Find the supported DID */
            for(i = (uint32)0u; i < (gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE); i++)
            {
                for(j = (uint32)0u; j < (uint32)NUMBER_OF_PERIODIC_DID; j++)
                {
                    if(gMsgContextType.reqData[(uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE + i] == gDcmDsdSubService_2A[j].DcmDspDidIdentifier)
                    {
                        /* Check session type */
                        SupportedDIDNum++;
                        sessiontype = gDcmDsdSubService_2A[j].DcmDspDidReadSessionRef;
                        securitylevel = gDcmDsdSubService_2A[j].DcmDspDidReadSecurityLevelRef;
                        
                        /*if parameter supported in session */
                        if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                            error = DCM_HAVE_ERRORS;
                            j = (uint32)NUMBER_OF_PERIODIC_DID;
                            i = gMsgContextType.reqDataLen;
                        }
                        
                        /*if parameter security access allow */
                        #if(DCM_SERVICE_27_ENABLED == STD_ON)
                        else if(((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
                                ||((service.ServiceTable.DcmDsdSidTabSecurityLevelRef & gSecLevelType) == 0u))
                        {                
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                            error = DCM_HAVE_ERRORS;
                            j = (uint32)NUMBER_OF_PERIODIC_DID;
                            i = gMsgContextType.reqDataLen;
                        }
                        #endif
                       
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                        && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            /* do nothing, so below code could be processed */
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
                        && ((service.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                            error = DCM_HAVE_ERRORS;
                            j = (uint32)NUMBER_OF_PERIODIC_DID;
                            i = gMsgContextType.reqDataLen;
                        }
                       
                        /* Check DID adressing mode */
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                        && ((gDcmDsdSubService_2A[j].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            /* do nothing, so below code could be processed */
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
                        && ((gDcmDsdSubService_2A[j].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                            error = DCM_HAVE_ERRORS;
                            j = (uint32)NUMBER_OF_PERIODIC_DID;
                            i = gMsgContextType.reqDataLen;
                        }
                        else
                        { 
                            temp_periodicdidlist[counter].Did = gMsgContextType.reqData[(uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE + i];
                            temp_periodicdidlist[counter].DidPosition = (uint16)j;                  
                            counter++; 
                            j = (uint32)NUMBER_OF_PERIODIC_DID;
                        }
                    }
                    else
                    {
                        /* do nothing, go on searching */
                    }
                }
            }

            if(gNegativeResponseCode != DCM_E_POSITIVERESPONSE)
            {
                /* do nothing */
            }
            else if(SupportedDIDNum == 0u)
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                error = DCM_HAVE_ERRORS;
            }
            /* check other state of the supported DID  */ 
            else if(counter == 0u)
            {
                /* all DIDs' AddressingMode not OK ,under UDS_FUNCTIONAL addressing */
                DsdInternal_ProcessingDoneNoResponse();
                error = DCM_HAVE_ERRORS;
            } 
            /* removed by larry 20140410
            else if(temp_periodicdidlist[DCM_INDEX_0].Did != (uint8)DCM_ALL_BITS_ON_8)
            {
                error = DCM_HAVE_ERRORS;
            }*/
            else
            {
                if(gMsgContextType.reqData[DCM_INDEX_1] < DCM_INDEX_4)
                {
                    /* Update periodic DID ,If one periodicDid is already in PeriodicDidList,use new transmission rate */
                    for(i = (uint32)0u; i < counter; i++)
                    {
                        if(gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_SLOW_RATE)
                        {
                            gPeriodicResponseRate[temp_periodicdidlist[i].DidPosition] = (SEND_AT_SLOW_RATE/DCM_TASK_TIME);
                        }
                        else if(gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_MEDIUM_RATE)
                        {
                            gPeriodicResponseRate[temp_periodicdidlist[i].DidPosition] = (SEND_AT_MEDIUM_RATE/DCM_TASK_TIME);
                        }
                        else if(gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2A_SEND_AT_FAST_RATE)  
                        {
                            gPeriodicResponseRate[temp_periodicdidlist[i].DidPosition] = (SEND_AT_FAST_RATE/DCM_TASK_TIME);
                        }
                        else
                        {
                            /* do nothing */
                        }
                        
                        if(gPeriodicResponseFlag[temp_periodicdidlist[i].DidPosition] == DCM_FLAG_ACTIVE)
                        {
                            /* change rate frome next periodic ,so delet */
                        }
                        else
                        {
                            gPeriodicResponseFlag[temp_periodicdidlist[i].DidPosition] = DCM_FLAG_ACTIVE;
                            
                            /*Send as soon as possible*/
                            gPeriodicResponseTimer[temp_periodicdidlist[i].DidPosition] = (uint32)0u;
                        }
                    }
                    
                    /*Updata PeriodicDidList */
                    PeriodicDidCounter = 0u;
                    for(j = (uint32)0u; j < (uint32)NUMBER_OF_PERIODIC_DID; j++)
                    {
                        if(gPeriodicResponseFlag[j] == DCM_FLAG_ACTIVE)
                        {
                            PeriodicDidList[PeriodicDidCounter].Did = gDcmDsdSubService_2A[j].DcmDspDidIdentifier;
                            PeriodicDidList[PeriodicDidCounter].DidPosition = (uint16)j;
                            PeriodicDidCounter++;
                        }
                    }
                    
                    /* restart from the first  PeriodicDidList*/
                    CurrentPeriodicDidIndx  = 0u;
                }
                else
                { 
                    /* dele DID from  Periodic Tx table (PeriodicDidList)*/
                    temp = PeriodicDidCounter;
                    
                    /* Clear periodicDid info in PeriodicDidList */ 
                    for(i = (uint32)0u; i < counter; i++)
                    {
                        for(j = (uint32)0u; j < temp; j++)
                        {
                            if((temp_periodicdidlist[i].Did == PeriodicDidList[j].Did) 
                            && (gPeriodicResponseFlag[temp_periodicdidlist[i].DidPosition] == DCM_FLAG_ACTIVE))
                            {
                                gPeriodicResponseFlag[temp_periodicdidlist[i].DidPosition] = DCM_FLAG_DISACTIVE;
                                gPeriodicResponseRate[temp_periodicdidlist[i].DidPosition] = (uint32)0u;
                                gPeriodicResponseTimer[temp_periodicdidlist[i].DidPosition] = (uint32)0u;
                                j = (uint32)temp;
                            }
                            else
                            {
                                if(j == (uint32)(temp-1u))
                                {
                                    /* 
                                     * If periodicDid to clear is not in PeriodicDidList, 
                                     * give negative response 
                                     */
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                                    error = DCM_HAVE_ERRORS; 
                                }
                                else
                                {
                                }
                            }
                        }
                    }
                    if(error == DCM_HAVE_NO_ERRORS)
                    {
                        /* Update PeriodicDidList */
                        PeriodicDidCounter = 0u;
                        for(j = (uint32)0u; j < (uint32)NUMBER_OF_PERIODIC_DID; j++)
                        {
                            if(gPeriodicResponseFlag[j] == DCM_FLAG_ACTIVE)
                            {
                                PeriodicDidList[PeriodicDidCounter].Did = gDcmDsdSubService_2A[j].DcmDspDidIdentifier; 
                                PeriodicDidList[PeriodicDidCounter].DidPosition = (uint16)j;
                                PeriodicDidCounter++;
                            }
                        }
                        for(j = (uint32)0u; j < (uint32)PeriodicDidCounter; j++)
                        {
                            /* removed temp */
                            /* if(CurrentPeriodicDid.DidPosition == PeriodicDidList[j].DidPosition) */
                            if(DCM_UINT8_0 == PeriodicDidList[j].DidPosition) 
                            {
                                /*
                                 * remember the current did'index in new list,
                                 * if the current did is not dele 
                                 */
                                CurrentPeriodicDidIndx = (uint16)j;
                                j = (uint32)PeriodicDidCounter;
                            }
                            else
                            {   
                                /*Tx DID from the first*/
                                CurrentPeriodicDidIndx  = 0u;
                            }
                        }
                    }
                }
            }
        }
    }
    
    /* No error happend,postive response */
    if(error == DCM_HAVE_NO_ERRORS) 
    {
        gMsgContextType.resDataLen = (uint32)1u;
        DsdInternal_ProcessingDone(&gMsgContextType);
    }
    else
    {
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_DynamicallyDefinedDataIdentifier
*                
* Description:   Implementation of Uds servie 0x2C
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/

/* Asumption: the addresssAndLength format is the same as 0x23 and 0x3d */
#if((DCM_SERVICE_2C_ENABLED == STD_ON) && (DCM_SERVICE_22_ENABLED == STD_ON) && (DCM_SERVICE_23_ENABLED == STD_ON))
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_DynamicallyDefinedDataIdentifier
(
    void
)
{
    uint8  i;
    uint8  j;
    uint8  error = STD_ON;
    uint16 tempdid;
    uint16 dynamicaldid;
    uint8  dynamicaldidposition = 0u;
    uint8  securitylevel;
    uint8  sessiontype = 0u;
    DynamicalDidRelatedInfo  dynamicaldidrealatedinfo = 
    {
        0u,
        0u,
        0u,
        { 
            0u 
        },
        { 
            0u
        },
        0u,
        { 
            0u 
        },
        0u,
        (uint32)0u
    };
    uint32 sum = (uint32)0u;
    uint8  sourcedidcounter;
    uint8  addressFormat;
    uint32 startAddress = (uint32)0u;
    uint8  sizeFormat;
    uint32 memorySize = (uint32)0u; 
    uint8  addresssegment = 0u;
    uint8  addressandmemorylength;
    uint8  addresscounter;
    
    /* Check message format */
    if(gMsgContextType.reqDataLen < (uint32)DCM_SERVICE_2C_LEAST_REQ_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        tempdid = Make16Bit(gMsgContextType.reqData[DCM_INDEX_2],gMsgContextType.reqData[DCM_INDEX_3]);
        for(i = 0u; i < NUMBER_OF_DYN_DID; i++)
        {
            if(tempdid == gDcmDsdSubService_2C[i].DcmDspDidIdentifier)
            {
                /* Check the security access condition of dynamical did */
                securitylevel = gDcmDsdSubService_2C[dynamicaldidposition].DcmDspDidReadSecurityLevelRef;
                sessiontype = gDcmDsdSubService_2C[dynamicaldidposition].DcmDspDidReadSessionRef;
                if(securitylevel != 0u)
                {
                    #if(DCM_SERVICE_27_ENABLED == STD_ON)
                    if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                        error = STD_ON; 
                    }
                    else
                    #endif
                    {
                        error = STD_OFF;
                        dynamicaldidposition = i;
                        i = NUMBER_OF_DYN_DID;
                    }
                }
                else
                {
                    error = STD_OFF;
                    dynamicaldidposition = i;
                    i = NUMBER_OF_DYN_DID;
                }
            }
            else
            {
                #if(NUMBER_OF_DYN_DID > 1u)
                if(i == (NUMBER_OF_DYN_DID - 1u))
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                    error = STD_ON;
                }
                else
                {
                    /* do nothing */
                }
                #else
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                error = STD_ON;
                #endif
            }
        }
        if(error == STD_ON)
        { 
            /* do nothing */
        }
        
        /* Check session condition */
        else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }
        
        /* Check adressing mode */
        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) \
        && ((gDcmDsdSubService_2C[dynamicaldidposition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
        {
            /* Service is not supported under functional request,but do not send 0x11 negative response */
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }
        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) && ((gDcmDsdSubService_2C[dynamicaldidposition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
        {
            /* Service is not supported under physical request, send negative response */ 
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }
        else
        {       
            dynamicaldid = tempdid;
            if(gMsgContextType.reqData[DCM_INDEX_1] == 0x01u) 
            {
                dynamicaldidrealatedinfo.SourceDidCounter = 0u;
                /* removed by larry according to QAC 20140116 */
                /* dynamicaldidrealatedinfo.TotalDataSize = 0u; */
                
                /* Check message format. correct length should be multiple of 4 */
                if((gMsgContextType.reqDataLen % (uint32)DCM_SERVICE_2C_JUDGE_THE_LENGTH_IS_MULTIPLE_OF_4) != (uint32)0u)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                }
                else
                {
                    for(i = 0u; i < (gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE); i +=  DCM_REQUIRE_DATA_LENGTH_4_BYTE)
                    {
                        tempdid = Make16Bit(gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_4_BYTE + i],gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_5_BYTE + i]);
                        for(j = 0u; j < NUMBER_OF_READ_DID; j++)                                          
                        {
                            if(tempdid != gDcmDsdSubService_22[j].DcmDspDidIdentifier)
                            {
                                /* Check whether all the source is supported */
                                if(j == (NUMBER_OF_READ_DID-1u))
                                {
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                                    error = STD_ON;
                                }
                                else
                                {
                                }
                            }
                            else
                            {
                                /* Check whether the PositionInSourceDataRecord is valid */
                                if((gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_6_BYTE+i] < 1u)
                                  || (gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_6_BYTE+i] > gDcmDsdSubService_22[j].DcmDspDataSize))
                                {
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                                    error = STD_ON;
                                }
                                else
                                {
                                    /* Check security access condition of the source did */
                                    securitylevel = gDcmDsdSubService_22[j].DcmDspDidReadSecurityLevelRef;
                                    if(securitylevel != 0u)
                                    {
                                        #if(DCM_SERVICE_27_ENABLED == STD_ON)

                                        if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
                                        {
                                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                                            error = 1u;
                                        }
                                        else
                                        {
                                            /* Record related info of the supported source did and check the next source did */
                                            dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].SourceDid = tempdid;
                                            dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].SourceDidPosition = j;
                                            dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].PositionInSourceDataRecord 
                                            = gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_6_BYTE + i];
                                            dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].MemorySize 
                                            = gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_7_BYTE + i];
                                            dynamicaldidrealatedinfo.SourceDidCounter++; 

                                            /* Redudce cycle times */
                                            j = NUMBER_OF_READ_DID;
                                        }
                                        #endif
                                    }
                                    else
                                    {
                                        /* Record related info of the supported source did and check the next source did */
                                        dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].SourceDid = tempdid;
                                        dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].SourceDidPosition = j;
                                        dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].PositionInSourceDataRecord = gMsgContextType.reqData[DCM_INDEX_6 + i];
                                        dynamicaldidrealatedinfo.ByDid[dynamicaldidrealatedinfo.SourceDidCounter].MemorySize = gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_7_BYTE + i];
                                        dynamicaldidrealatedinfo.SourceDidCounter++;

                                        /* Redudce cycle times */
                                        j = NUMBER_OF_READ_DID;
                                    }
                                    
                                }
                            }
                        }
                    }
                    if(error == STD_OFF)
                    {
                        /* Check whether the amount of data to be packed into the dynamic data identifier exceeds the maximum allowed by server */
                        dynamicaldidrealatedinfo.TotalDataSize = gDynamicalDidRelatedInfo[dynamicaldidposition].TotalDataSize;
                        for(i = 0u; i < dynamicaldidrealatedinfo.SourceDidCounter; i++)
                        {
                            sum +=  dynamicaldidrealatedinfo.ByDid[i].MemorySize;
                        }
                        dynamicaldidrealatedinfo.TotalDataSize += sum;
                        if(dynamicaldidrealatedinfo.TotalDataSize > gDcmDsdSubService_2C[dynamicaldidposition].DcmDspDataSize)
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        }
                        else
                        {
                            /* No error happended,move all the source Did info in to global variable gDynamicalDidRelatedInfo[8] */
                            if(gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDid != dynamicaldid)
                            {
                                gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDid = dynamicaldid;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDidPosion = dynamicaldidposition;
                                gDynamicalDidCounter++;
                            }
                            sourcedidcounter = gDynamicalDidRelatedInfo[dynamicaldidposition].SourceDidCounter;
                            for(i = 0u;i < dynamicaldidrealatedinfo.SourceDidCounter;i++)
                            {
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByDid[i + sourcedidcounter].SourceDid = dynamicaldidrealatedinfo.ByDid[i].SourceDid;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByDid[i + sourcedidcounter].SourceDidPosition = dynamicaldidrealatedinfo.ByDid[i].SourceDidPosition;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByDid[i + sourcedidcounter].PositionInSourceDataRecord = dynamicaldidrealatedinfo.ByDid[i].PositionInSourceDataRecord;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByDid[i + sourcedidcounter].MemorySize = dynamicaldidrealatedinfo.ByDid[i].MemorySize;
                            }
                            gDynamicalDidRelatedInfo[dynamicaldidposition].SourceDidCounter += dynamicaldidrealatedinfo.SourceDidCounter; 
                            gDynamicalDidRelatedInfo[dynamicaldidposition].TotalDataSize = dynamicaldidrealatedinfo.TotalDataSize;
                            i = gDynamicalDidRelatedInfo[dynamicaldidposition].DefinedTime;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].Sequence[i].ByDidOrAddress = 0u;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].Sequence[i].DidOrAddressCounter = dynamicaldidrealatedinfo.SourceDidCounter;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].DefinedTime++;
                            gMsgContextType.resDataLen = (uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE;
                            DsdInternal_ProcessingDone(&gMsgContextType);
                        }
                    }
                    else
                    {
                    }
                }
            }
            else if(gMsgContextType.reqData[DCM_INDEX_1] == DCM_SERVICE_2C_DEFINE_BY_MEMORY_ADDRESS)
            {
                dynamicaldidrealatedinfo.AddessCounter = 0u;
                
                /* removed by larry according to QAC 20140116 */
                /* dynamicaldidrealatedinfo.TotalDataSize = 0u; */
                
                addressFormat = gMsgContextType.reqData[DCM_INDEX_4] & DCM_SERVICE_23_GET_MEMORY_AND_ADDRESS_BYTE_LOW_NIBBLE;
                sizeFormat = gMsgContextType.reqData[DCM_INDEX_4] >> DCM_REQUIRE_DATA_LENGTH_4_BYTE; 
                addressandmemorylength = addressFormat + sizeFormat;
                
                /* Check addressAndLengthFormatIdentifier */
                if((addressFormat != gMemoryAddressFormat) || (sizeFormat != gMemorySizeFormat))
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                }

                /* Check message format */
                else if(((gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_5_BYTE) % addressandmemorylength) != (uint32)0u)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                }
                else
                {   
                    for(i = 0u; i < (gMsgContextType.reqDataLen - (uint32)DCM_REQUIRE_DATA_LENGTH_5_BYTE);i += addressandmemorylength)
                    {
                        /* Calculate start address */
                        for(j = 0u; j < gMemoryAddressFormat; j++)
                        {
                            startAddress |= (uint32)(gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_5_BYTE + j + i]) << (DCM_AMPLIFY_8_TIMES*(gMemoryAddressFormat - 1u - j));      
                        }
                        
                        /* Calculate size */
                        for(j = 0u; j < gMemorySizeFormat; j++)
                        {
                            memorySize |= (uint32)(gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_5_BYTE + gMemoryAddressFormat + j + i]) << (DCM_AMPLIFY_8_TIMES*(gMemorySizeFormat - 1 - j)); 
                        }
                        
                        /* Check address */
                        for(j = 0u; j < NUMBER_OF_READ_ADDRESS_SEG; j++)
                        {
                            if((startAddress >= gDcmDspReadMemoryRangeInfo_23[j].DcmDspReadMemoryRangeLow) && ((startAddress + memorySize)  <= gDcmDspReadMemoryRangeInfo_23[j].DcmDspReadMemoryRangeHigh))
                            {
                                addresssegment = j;
                                j = NUMBER_OF_READ_ADDRESS_SEG;
                            }
                            else
                            {
                                #if(NUMBER_OF_READ_ADDRESS_SEG > 1u)
                                if(j == (NUMBER_OF_READ_ADDRESS_SEG - 1u))
                                {
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                                    error = 1u;
                                }
                                else
                                {
                                    /* do nothing */
                                }
                                #else
                                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                                error = 1u;
                                #endif
                            }
                        }
                        if(error == STD_OFF)
                        {
                            /* Check security access conditon */
                            securitylevel = gDcmDspReadMemoryRangeInfo_23[addresssegment].DcmDspReadMemoryRangeSecurityLevelRef;
                            if(securitylevel != 0u)
                            {
                                #if(DCM_SERVICE_27_ENABLED == STD_ON)
                                if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT) 
                                {
                                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                                    error = STD_ON; 
                                }
                                else
                                {
                                    /* Record related info of the supported source did and check the next source did */
                                    dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].MemoryAddress = startAddress;
                                    dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].AddressSegment = addresssegment;
                                    dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].MemorySize = memorySize;
                                    dynamicaldidrealatedinfo.AddessCounter++;
                                    
                                    /* Clear the print of last cycle */
                                    startAddress = (uint32)0u;

                                     /* Clear the print of last cycle */
                                    memorySize = (uint32)0u; 
                                }
                                #endif
                            }
                            else
                            {
                                /* Record related info of the supported source did and check the next source did */
                                dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].MemoryAddress = startAddress;
                                dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].AddressSegment = addresssegment;
                                dynamicaldidrealatedinfo.ByAddress[dynamicaldidrealatedinfo.AddessCounter].MemorySize = memorySize;
                                dynamicaldidrealatedinfo.AddessCounter++;
                                
                                /* Clear the print of last cycle */
                                startAddress = (uint32)0u;

                                /* Clear the print of last cycle */
                                memorySize = (uint32)0u;  
                            }
                        }
                        else
                        {
                        }
                    }
                    if(error == STD_OFF)
                    {
                        /* 
                         * Check whether the amount of data to be packed into the dynamic data 
                         * identifier exceeds the maximum allowed by server 
                         */
                        dynamicaldidrealatedinfo.TotalDataSize = gDynamicalDidRelatedInfo[dynamicaldidposition].TotalDataSize;
                        for(i = 0u; i < dynamicaldidrealatedinfo.AddessCounter; i++)
                        {
                            sum += dynamicaldidrealatedinfo.ByAddress[i].MemorySize;
                        }
                        dynamicaldidrealatedinfo.TotalDataSize += sum;
                        if(dynamicaldidrealatedinfo.TotalDataSize > gDcmDsdSubService_2C[dynamicaldidposition].DcmDspDataSize)
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        }
                        else
                        {
                            /* 
                             * No error happended,move all the source did info in to global 
                             * variable gDynamicalDidRelatedInfo[8] 
                             */
                            if(gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDid != dynamicaldid)
                            {
                                gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDid = dynamicaldid;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDidPosion = dynamicaldidposition;
                                gDynamicalDidCounter++;
                            }
                            addresscounter = gDynamicalDidRelatedInfo[dynamicaldidposition].AddessCounter;
                            for(i = 0u; i < dynamicaldidrealatedinfo.AddessCounter; i++)
                            {
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByAddress[i + addresscounter].MemoryAddress 
                                = dynamicaldidrealatedinfo.ByAddress[i].MemoryAddress;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByAddress[i + addresscounter].AddressSegment 
                                = dynamicaldidrealatedinfo.ByAddress[i].AddressSegment;
                                gDynamicalDidRelatedInfo[dynamicaldidposition].ByAddress[i + addresscounter].MemorySize 
                                = dynamicaldidrealatedinfo.ByAddress[i].MemorySize;
                            }
                            gDynamicalDidRelatedInfo[dynamicaldidposition].AddessCounter += dynamicaldidrealatedinfo.AddessCounter; 
                            gDynamicalDidRelatedInfo[dynamicaldidposition].TotalDataSize = dynamicaldidrealatedinfo.TotalDataSize;
                            i = gDynamicalDidRelatedInfo[dynamicaldidposition].DefinedTime;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].Sequence[i].ByDidOrAddress = 1u;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].Sequence[i].DidOrAddressCounter = dynamicaldidrealatedinfo.AddessCounter;
                            gDynamicalDidRelatedInfo[dynamicaldidposition].DefinedTime++;
                            
                            /* Positive response */ 
                            gMsgContextType.resDataLen = (uint32)DCM_RESPONSE_DATA_LENGTH_4_BYTE;
                            DsdInternal_ProcessingDone(&gMsgContextType);
                        }
                    }
                    else
                    {
                    }
                }
            }
            else
            {
                if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_2C_SUB_SERVICE_03_REQ_LENGTH)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                }
                else
                {
                    /* Clear dynamical Did info */
                    gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDid = 0u;
                    gDynamicalDidRelatedInfo[dynamicaldidposition].DynamicalDidPosion = 0u;
                    gDynamicalDidRelatedInfo[dynamicaldidposition].DefinedTime = 0u;
                    gDynamicalDidRelatedInfo[dynamicaldidposition].SourceDidCounter = 0u;
                    gDynamicalDidRelatedInfo[dynamicaldidposition].AddessCounter = 0u;
                    gDynamicalDidRelatedInfo[dynamicaldidposition].TotalDataSize = (uint32)0u;
                    gDynamicalDidCounter--;
                    
                    /* No error happended,positive response */
                    gMsgContextType.resDataLen = (uint32)DCM_RESPONSE_DATA_LENGTH_4_BYTE;
                    DsdInternal_ProcessingDone(&gMsgContextType);
                }
            }
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_WriteDataByIdentifier
*                
* Description:   Implementation of Uds servie 0x2E
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_WriteDataByIdentifier
(
    void
)
{
    uint8  i;
    uint8  error = 1u;
    uint16 tempdid;
  
    uint8  didposition = 0u;
    uint8  securitylevel;
    uint8  sessiontype;
  
    tempdid = Make16Bit(gMsgContextType.reqData[DCM_INDEX_1],gMsgContextType.reqData[DCM_INDEX_2]);
    for(i = 0u; i < gNumberOfWriteDID; i++)
    {
        if(tempdid == gDcmDsdSubService_2E[i].DcmDspDidIdentifier)
        {
            error = 0u;
            didposition = i;
            break;/*i = gNumberOfWriteDID;*/
        }
        else
        {
        }
    }
    sessiontype = gDcmDsdSubService_2E[didposition].DcmDspDidWriteSessionRef;
	securitylevel = gDcmDsdSubService_2E[didposition].DcmDspDidWriteSecurityLevelRef;

    /*min length check, minimum length is 4 byte(SI+DID+DREC)*/
	if(gMsgContextType.reqDataLen < 4)
	{
	    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
	}
    /* Check whether the requested DID is defined in gDcmDsdSubService_2E */
    else if(error == 1u)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    
    /* Check if the requested DID supported */
    else if(gDcmDsdSubService_2E[didposition].DcmDspDidUsed != 1u)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
	    /* Check session condition */
    else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    
    /* Check message format */
    else if(gMsgContextType.reqDataLen != (uint32)(DCM_UINT8_3 + gDcmDsdSubService_2E[didposition].DcmDspDataSize))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
	/* Check whether the security condition is met */
    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    else if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)               
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
    }
    #endif 
    
    /* Check adressing mode */
    else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
    && ((gDcmDsdSubService_2E[didposition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
    && ((gDcmDsdSubService_2E[didposition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
    {
        /* Service is not supported under physical request, send negative response */ 
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    else
    {
        /* No error happened,give positive response */
        /* changed by larry 2013.11.12 QAC */
        /* gMsgContextType.resData += 1u; */
        gMsgContextType.resData = (&gMsgContextType.resData[1u]);
        gSubFunctionHandler = gDcmDsdSubService_2E[didposition].DcmDspDataWriteFnc;
        if(gSubFunctionHandler != DCM_NULL)
        {
            (*gSubFunctionHandler)(&gMsgContextType);
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
        
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_InputOutputControlByIdentifier
*                
* Description:   Implementation of Uds servie 0x2F
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_InputOutputControlByIdentifier
(
    void
)
{
    uint8  i;
    uint8  error = DCM_HAVE_ERRORS;
    uint16 tempdid;
   
    uint8  didposition = 0u;
    uint8  securitylevel;
    uint8  sessiontype = 0u;
  
    tempdid = Make16Bit(gMsgContextType.reqData[DCM_INDEX_1],gMsgContextType.reqData[DCM_INDEX_2]);
    for(i = 0u; i < gNumberOfIOCtrlDID; i++)
    {
        if(tempdid == gDcmDsdSubService_2F[i].DcmDspDidIdentifier)
        {
            error = DCM_HAVE_NO_ERRORS;
            didposition = i;
            sessiontype = gDcmDsdSubService_2F[didposition].DcmDspDidControlSessionRef;
		    securitylevel = gDcmDsdSubService_2F[didposition].DcmDspDidControlSecurityLevelRef;
            break;/*i = gNumberOfIOCtrlDID;*/
        }
    }
    /*min length check, at least 4*/
    if(gMsgContextType.reqDataLen < 4)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    /* Check whether the requested DID is defined in gDcmDsdSubService_2F */
    else if(error != DCM_HAVE_NO_ERRORS)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
      /* Check session condition */
    else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
	/* Check security condition */
    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    else if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)             
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
    }
    #endif   
    /* Check adressing mode */
    else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
    && ((gDcmDsdSubService_2F[didposition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
    && ((gDcmDsdSubService_2F[didposition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
    {
        /* Service is not supported under physical request, send negative response */ 
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    else
    {  
            switch(gMsgContextType.reqData[DCM_INDEX_3])
            {
                case RETURN_CONTROL_TO_ECU:
                {
                    /* Check message format */
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_SERVICE_2F_RETURN_CONTROL_TO_ECU_REQ_LENGTH
                                                       + gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlOptionRecordSize))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /* No error happened,give positive response */
                        gSubFunctionHandler = gDcmDsdSubService_2F[didposition].DcmDspDataReturnControlToEcuFnc;
                        if(gSubFunctionHandler == DCM_NULL)
                        {                                           
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);                     
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);
                        }
                    }
                }
                break;
                
                case RESET_TO_DEFAULT:
                {
                    /* Check message format */
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_SERVICE_2F_RESET_TO_DEFAULT_REQ_LENGTH
                                                       + gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlOptionRecordSize))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /* Call related appliction callbacek function */
                        gSubFunctionHandler = gDcmDsdSubService_2F[didposition].DcmDspDataResetToDefaultFnc;
                        
                        if(gSubFunctionHandler == DCM_NULL)
                        {                                        
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);
                        }
                    }
                }
                break;
                
                case FREEZE_CURRENT_STATE:
                {
                    /* Check message format */ 
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_SERVICE_2F_FREEZE_CURRENT_STATE_REQ_LENGTH
                                                       + gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlOptionRecordSize))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /* Call related appliction callbacek function */
                        gSubFunctionHandler = gDcmDsdSubService_2F[didposition].DcmDspDataFreezeCurrentStateFnc;
                        
                        if(gSubFunctionHandler == DCM_NULL)
                        {                                            
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);
                        }
                    }
                }
                break;
                
                case SHORT_TERM_ADJUSTMENT:
                {
                    /* Check message format */
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE + gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlEnableMaskRecordSize))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /* Call related appliction callbacek function */
                        gSubFunctionHandler = gDcmDsdSubService_2F[didposition].DcmDspDataShortTermAdjustmentFnc;
                        
                        if(gSubFunctionHandler == DCM_NULL)
                        {                                         
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);            
                        }
                    }
                }
                break;
                
                default:
                {
                    /* Check message format*/
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_REQUIRE_DATA_LENGTH_3_BYTE + gDcmDsdSubService_2F[didposition].RecordSizes.DcmDspDidControlOptionRecordSize))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        gSubFunctionHandler = gDcmDsdSubService_2F[didposition].OtherFnc;
                       
                        if(gSubFunctionHandler == DCM_NULL)
                        {
                                                                        
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);
                        }
                    }
                }
                break;
            }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_RoutineControl
*                
* Description:   Implementation of Uds servie 0x31
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_31_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE)DspInternal_Uds_RoutineControl
(
    void
)
{
    uint8  i;
    uint16 routineId; 
    uint8  postion = 0u;
    /* add flag by larry 2013.11.13 QAC*/
    uint8  Available_ID = STD_OFF;
    uint8  securitylevel = INVALID_SECURITY_LEVEL;
    uint8  sessiontype = INVALID_SESSION_TYPE;
    uint8  error = DCM_HAVE_ERRORS;

    /*ClrSuppressPosResponseBit();*/

    routineId = Make16Bit(gMsgContextType.reqData[DCM_INDEX_2],gMsgContextType.reqData[DCM_INDEX_3]);
    
    /* Check whether the requested RID is supported */
    for(i = 0u; i < NUMBER_OF_RID; i++)
    {
        if(routineId == DcmDspRoutineIdentifierTable_31[i].DcmDspRoutineIdentifier)
        {
            postion = i;
            Available_ID = STD_ON;
            sessiontype = DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.DcmDspRoutineSessionRef;
            securitylevel = DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.DcmDspRoutineSecurityLevelRef; 
            /* changed to break. larry 2013.11.12 QAC */
            /* i = NUMBER_OF_RID; */
            break;
        }
        else
        {
        }
    }
	/*min length check, at least 4(SI+SubFunction+RID Parameter)*/
    if(gMsgContextType.reqDataLen < 4)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    /* No supported RID found */ 
    else if(Available_ID == STD_OFF) 
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE); 
    }    
    /* parameter execuation state check */
    /* is parameter supported in session */
    else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    
    /* is parameter security access allowed ?*/
    else if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
    }

    /* security ok */
    else
    {
        error = DCM_HAVE_NO_ERRORS;
    }
    
    /* no NRC registered */
    if(error == DCM_HAVE_NO_ERRORS)
    {   
        error = DCM_HAVE_ERRORS;
      
        /* RID supported SubFun */
        if(gMsgContextType.reqData[DCM_INDEX_1] == START_ROUTINE)
        {
            /*  Is RID supports sub-function  */
            if(DcmDspRoutineIdentifierTable_31[postion].DcmDspStartRoutineFnc == DCM_NULL)
            { 
                /*  sub not cfg to support  */
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
            }
            else
            {
                /*  if req lenght valid  */
                /*  If routine control signal is fixed,check message format  */
                if(DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineFixedLength == 1u)
                {
                    if(gMsgContextType.reqDataLen != ((uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE + DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.DcmDspStartRoutineIn.DcmDspRoutineSignalLength))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {  
                       /*  lenght valid  */
                        error = DCM_HAVE_NO_ERRORS;
                    }
                }
                else
                {
                    /*  lenght valid  */
                    error = DCM_HAVE_NO_ERRORS;
                }
                if(error == DCM_HAVE_NO_ERRORS)
                { 
                    /* error = DCM_HAVE_ERRORS; */
                    /* romoved by larry according to QAC 2013.11.11*/
                    
                    /*  0x31's Sub fun is found  in DsdInternal_UdsSidDispatcher  */
                    if(gSubServicePosition != INVALID_SUB_SERVICE_POSITION)
                    {    
                        /* Sub-Function Exection state check */
                        /* is  Sub-Function supported in session  */
                        /* all condication have checked and no error*/
                        /* Check service id adressing mode  */
                        if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                        && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                        && ((service.AddressingMode & 0x01u) == 0u))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        } 
                                   
                        /* Check sub-function adressing mode */
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                        && ((gDcmDsdSubService[gSubServicePosition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                        && ((gDcmDsdSubService[gSubServicePosition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        }
                           
                        /* Check RID adressing mode */                                                                    
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                        && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                        && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        }
                        else            
                        {
                            gRountineControlDidHandle = postion;

                            /* reset  sequence */
                            gRountineControlSequence[postion] = 0u;
                            gSubFunctionHandler = DcmDspRoutineIdentifierTable_31[postion].DcmDspStartRoutineFnc;
                            (*gSubFunctionHandler)(&gMsgContextType); 
                        }
                    }
                    else
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                    }
                }
                else
                {
                }
            }
        }
        else if(gMsgContextType.reqData[DCM_INDEX_1] == STOP_ROUTINE)
        { 
             /*  If RID supports sub-function  */
            if(DcmDspRoutineIdentifierTable_31[postion].DcmDspStopRoutineFnc == DCM_NULL)
            { 
                /*sub = 02,sub not cfg to support */
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
            }
            else
            { 
                /*is req lenght valid?*/
                /* If routine control signal is fixed,check message format */
                if(DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineFixedLength == 1u)
                {
                    if(gMsgContextType.reqDataLen != 
                        ((uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE + DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.DcmDspRoutineStopIn.DcmDspRoutineSignalLength))
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /*  lenght valid  */
                        error = DCM_HAVE_NO_ERRORS; 
                    }
                }
                else
                {
                    /*  lenght valid  */
                    error = DCM_HAVE_NO_ERRORS; 
                }
                if(error == DCM_HAVE_NO_ERRORS)
                {      
                    /*  0x31's Sub fun is found  in DsdInternal_UdsSidDispatcher  */
                    if(gSubServicePosition != INVALID_SUB_SERVICE_POSITION)
                    {  
                        /* Sub-Function Exection state check */
                        /* is  Sub-Function supported in session  */
                        /* all condication have checked and no error*/
                        /* Check service id adressing mode  */
                        if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                        && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                            && ((service.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);    
                        }            
                        /* Check sub-function adressing mode */
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                            && ((gDcmDsdSubService[gSubServicePosition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                            && ((gDcmDsdSubService[gSubServicePosition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        }   
                        /* Check RID adressing mode */                                                                    
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                            && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType 
                            == UDS_PHYSICAL_ON_CAN_RX) && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        } 
                        else if(((gRountineControlSequence[postion]&HAVE_STARTED_ROUNTINE) == 0u) && ((gRountineControlSequence[postion]&HAVE_REQ_ROUNTINE_RESULT) == 0u)) 
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR);
                        } 
                        else
                        {
                            gRountineControlDidHandle = postion;
                            gSubFunctionHandler = DcmDspRoutineIdentifierTable_31[postion].DcmDspStopRoutineFnc;

                            if(gSubFunctionHandler == DCM_NULL)
                            {
                                                                            
                                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                            }
                            else
                            {
                                (*gSubFunctionHandler)(&gMsgContextType);
                            }

                            if((gRountineControlSequence[postion] & HAVE_STOPPED_ROUNTINE) != 0u)
                            {
                                /* changed by larry 2013.11.12 QAC */
                                /* gRountineControlSequence[postion] &= (uint8)(~((uint8)HAVE_STARTED_ROUNTINE));  */
                                gRountineControlSequence[postion] &= (uint8)(((uint8)HAVE_STARTED_ROUNTINE) ^ DCM_ALL_BITS_ON_8);
                                if(gRountineControlSequence[postion] == (uint8)(HAVE_REQ_ROUNTINE_RESULT|HAVE_STOPPED_ROUNTINE))
                                {
                                    gRountineControlSequence[postion] = 0u;
                                }
                            }
                        }
                    }
                    else
                    {       
                        /* Not cfg in gDcmDsdSubService Table */
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                    }
                }
                else
                {
                }
            }
        }
        else if(gMsgContextType.reqData[DCM_INDEX_1] == REQUEST_ROUTINE_RESULT)  
        { 
            /*  If RID supports sub-function  */
            if(DcmDspRoutineIdentifierTable_31[postion].DcmDspRequestResultsRoutineFnc == DCM_NULL)
            { 
                /*  sub = 03,sub not cfg to support  */
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
            }
            else
            { 
                /*  if req lenght valid  */
                /*  If routine control signal is fixed,check message format */
                if(DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineFixedLength == 1u)
                {             
                    if(gMsgContextType.reqDataLen != (uint32)DCM_REQUIRE_DATA_LENGTH_4_BYTE)
                    {
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                    }
                    else
                    {
                        /*  lenght valid  */
                        error = DCM_HAVE_NO_ERRORS;
                    }
                }
                else
                {
                    /*  lenght valid  */
                    error = DCM_HAVE_NO_ERRORS;
                }
                if(error == DCM_HAVE_NO_ERRORS)
                { 
                    /*  0x31's Sub fun is found  in DsdInternal_UdsSidDispatcher  */
                    if(gSubServicePosition != DCM_ALL_BITS_ON_8)
                    {  
                        /*  all condication have checked and no error  */
                        /*  Check service id adressing mode  */
                        if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                            && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType 
                        == UDS_PHYSICAL_ON_CAN_RX) && ((service.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            /* AddressingMode is not supportted */
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);    
                        } 
                                 
                        /* Check sub-function adressing mode */
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                            && ((gDcmDsdSubService[gSubServicePosition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType 
                        == UDS_PHYSICAL_ON_CAN_RX) && ((gDcmDsdSubService[gSubServicePosition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        }
                         
                        /* Check RID adressing mode */                                    
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                            && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                        {
                            DsdInternal_ProcessingDoneNoResponse();
                        }
                        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                            && ((DcmDspRoutineIdentifierTable_31[postion].DcmDspRoutineInfoRef.RoutineAuthorization.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT); 
                        }
                        else if(((gRountineControlSequence[postion]&HAVE_STARTED_ROUNTINE) == 0u) && 
                        ((gRountineControlSequence[postion]&HAVE_STOPPED_ROUNTINE) == 0u)) 
                        {
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTSEQUENCEERROR);
                        }
                        else
                        {
                            gRountineControlDidHandle = postion;
                            gSubFunctionHandler = DcmDspRoutineIdentifierTable_31[postion].DcmDspRequestResultsRoutineFnc;
                            if(gSubFunctionHandler == DCM_NULL)
                            {
                                                                            
                                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                            }
                            else
                            {
                                (*gSubFunctionHandler)(&gMsgContextType);
                            }
 
                            /* (HAVE_REQ_ROUNTINE_RESULT|HAVE_STOPPED_ROUNTINE|HAVE_STARTED_ROUNTINE)) */
                            if((gRountineControlSequence[postion] & HAVE_REQ_ROUNTINE_RESULT) != 0u)
                            {
                                gRountineControlSequence[postion] &= (uint8)(((uint8)HAVE_STARTED_ROUNTINE) ^ DCM_ALL_BITS_ON_8);
                                if(gRountineControlSequence[postion] == (uint8)(HAVE_REQ_ROUNTINE_RESULT|HAVE_STOPPED_ROUNTINE))
                                {
                                    gRountineControlSequence[postion] = 0u;
                                }
                            }
                        }
                    }
                    else
                    {  
                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                    }
                }
                else
                {
                }
            }
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
        }
    }
    else
    {
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_WriteMemoryByAddress
*                
* Description:   Implementation of Uds servie 0x3D
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_WriteMemoryByAddress
(
    void
)
{
    uint8  securitylevel;
    uint8  sessiontype;
    uint8  addressFormat;
    uint8  sizeFormat;
    uint8  i;
    uint32 startAddress = (uint32)0u;
    uint32 memorySize = (uint32)0u;

    addressFormat = gMsgContextType.reqData[DCM_INDEX_1] & DCM_SERVICE_3D_GET_MEMORY_AND_ADDRESS_BYTE_LOW_NIBBLE;
    sizeFormat = gMsgContextType.reqData[DCM_INDEX_1] >> DCM_SERVICE_3D_GET_MEMORY_AND_ADDRESS_BYTE_HIGH_NIBBLE;

    /*min length check, at least 5*/
	if(gMsgContextType.reqDataLen < 5)
	{
	  DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
	}
    /* Check addressAndLengthFormatIdentifier */
    else if((addressFormat != gMemoryAddressFormat) || (sizeFormat != gMemorySizeFormat))
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    /* Check message format */
    else
    {
        /* Calculate start address */
        for(i = 0u;i<gMemoryAddressFormat;i++)
        {
            startAddress |= (uint32)(gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_2_BYTE+i]) << (DCM_AMPLIFY_8_TIMES*(gMemoryAddressFormat-1-i));        
        }
        /* Calculate size  */
        for(i = 0u;i<gMemorySizeFormat;i++)
        {
            memorySize |= (uint32)(gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_2_BYTE+gMemoryAddressFormat+i]) << (DCM_AMPLIFY_8_TIMES*(gMemorySizeFormat-1-i)); 
        }
        /* Check the scope of the address in requested message */
        for(i = 0u; i < NUMBER_OF_WRITE_ADDRESS_SEG; i++)
        {
            if((startAddress >= gDcmDspWriteMemoryRangeInfo_3D[i].DcmDspWriteMemoryRangeLow)&&\
                ((startAddress + memorySize) <= 1u + gDcmDspWriteMemoryRangeInfo_3D[i].DcmDspWriteMemoryRangeHigh))
            {
                sessiontype=gDcmDspWriteMemoryRangeInfo_3D[i].DcmDspWriteMemoryRangeSessionRef;
                securitylevel=gDcmDspWriteMemoryRangeInfo_3D[i].DcmDspWriteMemoryRangeSecurityLevelRef;
                break;
            }
        }

        if(i == NUMBER_OF_WRITE_ADDRESS_SEG)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
        /* is request length valid ? */ 
        else if(gMsgContextType.reqDataLen != ((uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE + gMemoryAddressFormat+gMemorySizeFormat+memorySize))
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        } 
        else if(0 == memorySize)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }  
        /*is parameter supported in session ?*/
        else if((sessiontype & gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }

        /* Check security access conditon */
        /*is parameter security access allowed ?*/
        else if((securitylevel & gSecLevelType )== DCM_SECURITY_LEVEL_NOT_CORRECT)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
        }

        /* is service security access allowed? */
        else if((service.ServiceTable.DcmDsdSidTabSecurityLevelRef & gSecLevelType) == 0u)
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
        } 
        else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                  && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
        {
            /* AddressingMode is not supportted */
            DsdInternal_ProcessingDoneNoResponse();
        } 
        else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
        && ((service.AddressingMode & PHYSICAL_REQ_SUPPORTED)==DCM_REQUEST_ADDRESS_NOT_CORRECT))
        {
            /* AddressingMode is not supportted */
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }                     
        /* Check par adressing mode */
        else if((gMsgContextType.msgAddInfo.reqType==UDS_FUNCTIONAL_ON_CAN_RX) 
        && ((gDcmDspWriteMemoryRangeInfo_3D[i].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
        {
            DsdInternal_ProcessingDoneNoResponse();
        }
        else if((gMsgContextType.msgAddInfo.reqType==UDS_PHYSICAL_ON_CAN_RX) 
        && ((gDcmDspWriteMemoryRangeInfo_3D[i].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
        }
        else
        {
            gMsgContextType.resDataLen=DCM_REQUIRE_DATA_LENGTH_2_BYTE+addressFormat+sizeFormat;
            App_WriteAddress(&gMsgContextType,startAddress,memorySize,&gMsgContextType.reqData[DCM_REQUIRE_DATA_LENGTH_2_BYTE+addressFormat+sizeFormat]);
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_TesterPresent
*                
* Description:   Implementation of Uds servie 0x3E
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_3E_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_TesterPresent
(
    void
)
{
    /* Check message format */
    if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_3E_REQUIRE_DATA_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        gMsgContextType.resDataLen = (uint32)DCM_SERVICE_3E_RESPONSE_DATA_LENGTH;
        DsdInternal_ProcessingDone(&gMsgContextType); 
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ControlDTCSetting
*                
* Description:   Implementation of Uds servie 0x85
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_85_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ControlDTCSetting
(
    void
)
{
    DsdInternal_10_11_85();
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DspInternal_Uds_ResponseOnEvent
*                
* Description:   Implementation of Uds servie 0x86
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_86_ENABLED == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DspInternal_Uds_ResponseOnEvent
(
    void
)
{
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_SetNegResponse
*                
* Description:   Set negative response
*                             
* Inputs:        pMsgContext:Pointer pointed to the buffer having NR
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) DsdInternal_SetNegResponse
(
    CONSTP2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext,
    const uint8 ErrorCode 
)
{
    
    if(gNegativeResponseCode == DCM_E_POSITIVERESPONSE)
    {
        SetNegativeResponseCode(ErrorCode);
    }
    else
    {
    }
    gNegativeResponseBuffer[DCM_INDEX_0] = DCM_NEGATIVE_RES_SERVICE_ID;
    gNegativeResponseBuffer[DCM_INDEX_1] = gUDS_Physical_DiagBuffer[DCM_SID_POSITION];
    gNegativeResponseBuffer[DCM_INDEX_2] = gNegativeResponseCode;

    /* Make global pointer point to gNegativeResponseBuffer */
    pMsgContext->resData = gNegativeResponseBuffer;
    pMsgContext->resDataLen = (uint32)NEG_RESP_BUFFER_SIZE;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_ProcessingDone
*                
* Description:   Preocessing the response result of each Uds service.Transmit 
*                negative or positive respose(if not suppressed)
*                             
* Inputs:        pMsgContext: Pointer pointed to the buffer having response
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) DsdInternal_ProcessingDone
(
    CONSTP2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext
)
{
    PduInfoType temp;
    Std_ReturnType result = E_OK;

    if((gDiagState&DIAG_UDS_RCRP_DONE) != DIAG_UDS_RCRP_DONE)
    {
        /* Suppress positive response or fobidden 0x11 and 0x12 NRC under the 
           condition of functionally-addressing */
        if(((GetSuppressPosResponseBit() == 1u)&& (gNegativeResponseCode == DCM_E_POSITIVERESPONSE)) 
          || (gMsgContextType.resDataLen == (uint32)0u))
        {
            
            /* Start S3 Timer */
            if(gSesCtrlType != DCM_SESSION_DEFAULT)
            {
                gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
                Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
            }
            else
            {
            }
            Dsd_InteralInit();
        }
        else
        {
            /* Check whether the response length is over the related buffer's 
             * buffersize.
             * Response is always put in physical buffer 
             */
            if(gMsgContextType.resDataLen > (uint32)UDS_PHYS_BUFFER_SIZE) 
            {
                DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_RESPONSETOOLONG);
            }
            else
            {
                /* Under the situation of functionally-addressing,not send 0x31 NR */
                if((gMsgContextType.msgAddInfo.reqType == 1u)
                && (gNegativeResponseCode == DCM_E_REQUESTOUTOFRANGE)  ) /*larry 2013.10.30*/
                /* && (gDcm_CurrentServiceSubfuncAvail == UDS_SERVICE_WITHOUT_SUB_FUNCTION)) */
                {
                    /* Start S3 Timer */
                    if(gSesCtrlType != DCM_SESSION_DEFAULT)
                    {
                        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
                        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
                    }
                    else
                    {
                    
                    }
                    Dsd_InteralInit();
                }
                else
                {
                }
            }
            if((gNegativeResponseCode != DCM_E_POSITIVERESPONSE) 
            && (gNegativeResponseCode != DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING))             
            {
                #if(DCM_SERVICE_22_COMBINED_DID == STD_OFF)
                #else
                pMsgContext->resData = gNegativeResponseBuffer;
                pMsgContext->resDataLen = NEG_RESP_BUFFER_SIZE;
                #endif 
            }
            #if(DCM_SERVICE_2A_ENABLED == STD_ON)  
            else if((gDiagState & DIAG_UDS_PERIODIC_TX) == DIAG_UDS_PERIODIC_TX)
            {
                pMsgContext->resData = gPeriodicResponseBuffer;
            }
            #endif
            else
            {
                pMsgContext->resData = gUDS_Physical_DiagBuffer;
                pMsgContext->resData[DCM_INDEX_0] = pMsgContext->reqData[DCM_INDEX_0] + DCM_SID_OFF_SET;
            }
            
            /* Positive response or negative response */
            temp.SduDataPtr = pMsgContext->resData;
            temp.SduLength  = (uint16)pMsgContext->resDataLen;
            gResponseLength = (uint16)pMsgContext->resDataLen;
            if(pMsgContext->dcmRxPduId != DCM_INVALID_HANDLE_OR_ID)
            {
                result = DcmTransmit(gMsgContextType.dcmRxPduId,&temp);
            }
            
            /* FF has been correctly transmitted */
            if(result == E_OK)  
            {
                gDcm_RepeatTransmitFlag = DCM_FLAG_DISACTIVE;
   
                /* Stop P2 Timer */ 
                gP2ServerTimerStartFlag = DCM_FLAG_DISACTIVE; 
                Clr_P2_Server_Timer();
                ClrSuppressPosResponseBit();
                gFunctionHandler = DCM_NULL;
                gSubFunctionHandler = DCM_NULL;
                gSubFunctionPostHandler = DCM_NULL;
            }
            else
            {
                gDcm_RepeatTransmitFlag = DCM_FLAG_ACTIVE;
                gFunctionHandler = DCM_NULL;
                gSubFunctionHandler = DCM_NULL;
            }
            #if(DCM_SERVICE_22_COMBINED_DID == STD_OFF)
            ClrNegativeResponseCode();
            #endif
        }
        Reset_Max_Number_Of_RCRRP();
    }
    else
    {
        Clr_ActiveProtocol();
        Reset_PduId();
        Clr_DiagState(DIAG_UDS_RCRP_DONE);
        gFunctionHandler = DCM_NULL;
        gSubFunctionHandler = DCM_NULL;
        gSubFunctionPostHandler = DCM_NULL;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_ProcessingDoneNoResponse
*                
* Description:   The processing of request has been finished, but do not send
*                any response including positive or negative for other reason 
*                but not be set of SuppressPosResponseBit.
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) DsdInternal_ProcessingDoneNoResponse
(
    void
)
{
    gMsgContextType.resDataLen = (uint32)0u;
    DsdInternal_ProcessingDone(&gMsgContextType);
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_DidProcessingDone
*                
* Description:   This function will be call by 0x22 service's callbackfunction
*                once one of the did processing is finished when 
*                DCM_SERVICE_22_COMBINED_DID is enabled.
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
FUNC(void,DCM_PUBLIC_CODE) DsdInternal_DidProcessingDone
(
    void
)
{
    if(gDidPosition != DCM_SERVICE_22_INVALID_DID_POSITION)
    {
        #if(DCM_SERVICE_2C_ENABLED == STD_ON) 
        if(gReadDID_2C_Active_Flag == STD_ON)
        {
            /* do nothing */
        }
        else
        #endif
        {
            gDidResData[DCM_INDEX_0] = (uint8)(DidList[gDidPosition].Did >> DCM_SERVICE_22_RIGHT_ROLLING_8_BIT);
            gDidResData[DCM_INDEX_1] = (uint8)(DidList[gDidPosition].Did);
            gDidResData += (gDcmDsdSubService_22[DidList[gDidPosition].DidPosition].DcmDspDataSize 
                           + DCM_RESPONSE_DATA_LENGTH_2_BYTE);
            gDidResDataLen += (gDcmDsdSubService_22[DidList[gDidPosition].DidPosition].DcmDspDataSize 
                              + DCM_RESPONSE_DATA_LENGTH_2_BYTE);
            gMsgContextType.resData = gDidResData;
            gMsgContextType.resDataLen = gDidResDataLen;
			if(gMsgContextType.resDataLen > UDS_PHYS_BUFFER_SIZE)
			{
			  DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_RESPONSETOOLONG);
			}
            gDidPosition++;
            
            if(gDidPosition < DidCounter)
            {
                gSubFunctionHandler = gDcmDsdSubService_22[DidList[gDidPosition].DidPosition].DcmDspDataReadFnc;
            }
            else
            {
                gMsgContextType.resData = gUDS_Physical_DiagBuffer; 
                gMsgContextType.resDataLen = gDidResDataLen;
                gDidPosition = 0u;
                DidCounter = 0u;
                gDidResData = 0u;
                gDidResDataLen = 0u;
                DsdInternal_ProcessingDone(&gMsgContextType);
            }
        }
    }
    else
    {
        DsdInternal_ProcessingDone(&gMsgContextType);
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: FindSid
*                
* Description:   The timer processing function
*                             
* Inputs:        RequestSid:service Id in requested message
*                
* Outputs:       result: The service Id's positon in gCurrentSidMap
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(uint8,DCM_PRIVATE_CODE) FindUdsSid
(
    const uint8 RequestSid
)
{
    uint8 result = DCM_INVALID_HANDLE_OR_ID;
    uint8 offset = 0u;
    if(((RequestSid & THE_OFFSET_DATA) == 0u) 
      && (RequestSid  <= THE_LARGEST_SERVICE_ID))
    {
        if((RequestSid & SUPPRESS_POS_RSP_BYTE) != 0u)
        {
            offset = THE_OFFSET_DATA;
        }
        else
        {
            /* do nothing */
        }
        result = gCurrentSidMap[RequestSid - offset];
    }
    else
    {
        /* do nothing */
    }
    return result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_Dispatcher
*                
* Description:   Uds service dispatcher.
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_UdsSidDispatcher
(
    void
)
{
    uint8 i;
    uint8 sid;
    /* removed by larry. 2013.11.11 QAC same with global VAR */
    /*DcmDsdServiceTable service = { 0,{ DCM_NULL, 0, 0, 0 }, 0, 0, 0};*/
    uint8 securitylevel;
    uint8 sessiontype;
    uint8 error = DCM_HAVE_ERRORS;
    #if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
    Std_ReturnType result;
    #endif
    
    if((gDiagState&DIAG_UDS_INDICATION) == DIAG_UDS_INDICATION)
    {
        Clr_DiagState(DIAG_UDS_INDICATION);
        gSubServicePosition = 0u;

        #if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
        result = App_DiagnosticActive();
        if(result != E_OK) 
        {
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
        else
        {
        #endif

            Set_DiagState(DIAG_UDS_PROCESSING);
            sid = FindUdsSid(gMsgContextType.reqData[DCM_INDEX_0]);

           /*service = gServiceTable_1[sid];*/
            
            /* If it is functional request, check whether it is supported */
            if(sid < DCM_NUM_OF_SERVICE)
            {
                service = gServiceTable_1[sid];
			    sessiontype = service.ServiceTable.DcmDsdSidTabSessionLevelRef;
                securitylevel = service.ServiceTable.DcmDsdSidTabSecurityLevelRef;
                /* Check adressing mode */                                      
                if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                {
                    DsdInternal_ProcessingDoneNoResponse();
                    /* Service is not supported under functional request,but do not
                       send 0x11 negative response */
                }
                else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) && ((service.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                {
                    /* Service is not supported under physical request, send negative response */ 
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTED); 
                }                        
                /* Check service session condition */
                else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
                { 
                   if(gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                   {
                     //DsdInternal_ProcessingDoneNoResponse(); 
					 #if (ISO_14229_2006==STD_ON) 
					 DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION);
					 #else
					 DsdInternal_ProcessingDoneNoResponse();
					 #endif
                   }
				   else
				   {
				     DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION);
				   }
                }
                else
                {
                    /* Check service security access conditon */
                    //if((securitylevel != 0u) && ((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT))
                    //{
                    //    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                    //}
                   // else
                    {
                      /* Check minimum request length */
                      if(gMsgContextType.reqDataLen < (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
                      {
                          DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
                      }
                      else
                      {
  
                              /* If the requested service has sub-function */
                              if((service.ServiceTable.DcmDsdSidTabSubfuncAvail == 1u))
                              {
                                  /* Set suprresPostResponseBit if needed */
                                  gMsgContextType.msgAddInfo.suppressPosResponse = (gMsgContextType.reqData[DCM_INDEX_1] & SETSUPPRESSPOSRESPONSEBITMASK) >> RIGHT_ROLLING_SUPPRESS_POS_RSP_BIT;
                                  /* changed by larry 2013.11.11 QAC */
                                  /* gMsgContextType.reqData[1] &= ~SETSUPPRESSPOSRESPONSEBITMASK;*/
                                  gMsgContextType.reqData[DCM_INDEX_1] &= (SETSUPPRESSPOSRESPONSEBITMASK ^ DCM_ALL_BITS_ON_8);
                                  /* Check if the sub-function is defined in the gDcmDsdSubService */
                                  for(i = service.FirstSubService; i < (service.LastSubService+1u); i++)
                                  {
                                      if((gMsgContextType.reqData[DCM_INDEX_1] == gDcmDsdSubService[i].DcmDsdSubServiceId))
                                      {
                                          error = DCM_HAVE_NO_ERRORS;
                                          gSubServicePosition = i;
                                          break;/*i = service.LastSubService + 1;*/ 
                                      }
                                      else
                                      {
                                      }
                                  }
                                  if(error == DCM_HAVE_ERRORS)
                                  {
                                      /* Under the situation of functionally-addressing,not send 0x12 NR */
                                      if(gMsgContextType.msgAddInfo.reqType == 0u)
                                      {
                                          DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                                      }
                                      else
                                      {
                                          DsdInternal_ProcessingDoneNoResponse();
                                      }
                                  }
                                  else
                                  {
                                      sessiontype = gDcmDsdSubService[gSubServicePosition].DcmDsdSubServiceSessionLevelRef;
                                      securitylevel = gDcmDsdSubService[gSubServicePosition].DcmDsdSubServiceSecurityLevelRef;
                                      
                                      /* Check if the sub-function supported */
                                      if(gDcmDsdSubService[gSubServicePosition].DcmDsdSubServiceIdSupported != SUB_FUNCTION_SUPPORTED)
                                      {
                                          /* Under the situation of functionally-addressing,not send 0x12 NR */
                                          if(gMsgContextType.msgAddInfo.reqType == 0u) 
                                          {
                                              DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED);
                                          }
                                          else
                                          {
                                              DsdInternal_ProcessingDoneNoResponse();
                                          }
                                      }
                                      
                                      /* Check sub-function adressing mode */
                                      else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) && ((gDcmDsdSubService[gSubServicePosition].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                                      {
                                          DsdInternal_ProcessingDoneNoResponse();
                                          /* sub-function is not supported under functional request,but do not send 0x12 negative response */
                                      }
                                      else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) && ((gDcmDsdSubService[gSubServicePosition].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                                      {
                                          /* sub-function is not supported under physical request, send negative response */ 
                                          DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTED); 
                                      }
                                      
                                      /* Check sub-function session conditon */
                                      else if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT) 
                                      {
                                          if(gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
                                          {
                                          #if (ISO_14229_2006==STD_ON) 
					                        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION);
					                      #else
					                        DsdInternal_ProcessingDoneNoResponse();
					                      #endif
                                            //DsdInternal_ProcessingDoneNoResponse();
                                          }
                        				  else
                        				  {
                                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION);
                        				  }
                                      }
                                      
                                      /* Check sub-function security conditon */
                                      else if((securitylevel != 0u) && ((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT))
                                      {
                                          DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                                      }
                                      else
                                      {
                                          /* Call corresponding service function */                                                    
                                          
                                          /* removed by larry according to QAC 2013.11.11 */
                                          /*gDcm_CurrentServiceSubfuncAvail = UDS_SERVICE_WITH_SUB_FUNCTION;*/
                                          gFunctionHandler = service.ServiceTable.DcmDsdSidTabFnc;
                                          (*gFunctionHandler)(); 
                                      }
                                  }
                              }
                              else
                              {
                                  /* Call corresponding service function */
                                  
                                  /* removed by larry according to QAC 2013.11.11 */
                                  /*gDcm_CurrentServiceSubfuncAvail = UDS_SERVICE_WITHOUT_SUB_FUNCTION;*/
                                  gFunctionHandler = service.ServiceTable.DcmDsdSidTabFnc;
                                  (*gFunctionHandler)();
                              }
                          
                      }
                     }
                }
            }
            else
            {
                #if(DCM_COSTOMIZED_SERVCIE_SUPPORTED == STD_ON)
                gSubFunctionHandler = App_CustomizedServcie;
                if(gSubFunctionHandler == DCM_NULL)
                {
                                                                
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                }
                else
                {
                    (*gSubFunctionHandler)(&gMsgContextType);
                }
                #else
                if(gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SERVICENOTSUPPORTED);
                }
                else
                {
                    /* Under the situation of functionally-addressing,not send 0x11 NR */
                    DsdInternal_ProcessingDoneNoResponse();
                }
                #endif
            }
        #if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
        }
        #endif
        /*Send Neg Resp (NO 0x78)*/
        if((gNegativeResponseCode != DCM_E_POSITIVERESPONSE) 
          &&(gNegativeResponseCode != DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING))
        {
            DsdInternal_ProcessingDone(&gMsgContextType);
        }
        else
        {
            
        }
    }
    else
    {
        
    }
}

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#define DCM_START_SEC_PRIVATE_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_RepeatTransmitCheck
*                
* Description:   Uds service repeat transmit
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_RepeatTransmitCheck
(
    void
)
{
    PduInfoType temp;
    Std_ReturnType result;
    
    if(gDcm_RepeatTransmitFlag == DCM_FLAG_ACTIVE)
    {
        temp.SduDataPtr = gMsgContextType.resData;
        temp.SduLength = (uint16)gMsgContextType.resDataLen;
        gResponseLength = (uint16)gMsgContextType.resDataLen;
    	result = DcmTransmit(gMsgContextType.dcmRxPduId,&temp);
        
        if(result == E_OK)
        {
            gDcm_RepeatTransmitFlag = DCM_FLAG_DISACTIVE;

            /* Stop P2 Timer */
            gP2ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
            Clr_P2_Server_Timer();
            ClrSuppressPosResponseBit();
            gFunctionHandler = DCM_NULL;
            gSubFunctionHandler = DCM_NULL;
            /*gSubFunctionPostHandler = DCM_NULL;*/
        }
        else
        {
            gDcm_RepeatTransmitFlag = DCM_FLAG_ACTIVE;
            gFunctionHandler = DCM_NULL;
            gSubFunctionHandler = DCM_NULL;
        }
    }
    else
    {
    }
}

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_Periodic_Transmit
*                
* Description:   Uds service 2A periodic transmit
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_Periodic_Transmit
(
    void
)
{   
    uint8 i;
    
    if((gDiagState & DIAG_IDLE) == DIAG_IDLE)
    {
        for(i = 0u; i < PeriodicDidCounter; i++)
        {
            if(gPeriodicResponseTimer[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition] == (uint32)0u)
            { 
                Set_DiagState(DIAG_UDS_PERIODIC_TX);
                
                /* Type1,use the same CAN id as normal request message, 
                change to types2 may be better */   
                gMsgContextType.dcmRxPduId = UDS_FUNCTIONAL_ON_CAN_RX; 
                
                /* removed by larry according to QAC 2013.11.11 */
                /*gDcm_CurrentServiceSubfuncAvail == UDS_SERVICE_WITHOUT_SUB_FUNCTION;*/
                gMsgContextType.resData = gPeriodicResponseBuffer;
                gMsgContextType.resData[DCM_INDEX_0] = DCM_SERVICE_2A_POSITIVE_RESPONSE;
                gMsgContextType.resData[DCM_INDEX_1] = gDcmDsdSubService_2A[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition].DcmDspDidIdentifier;
                gMsgContextType.resDataLen = (((uint32)DCM_UINT8_2 + (uint32)gDcmDsdSubService_2A[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition].DcmDspDataSize));
                #if(DCM_SERVICE_22_ENABLED == STD_ON)
                gDidPosition = DCM_ALL_BITS_ON_8;
                #endif
                gSubFunctionHandler = gDcmDsdSubService_2A[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition].DcmDspDataReadFnc;
                if(gSubFunctionHandler == DCM_NULL)
                {
                                                                
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                }
                else
                {
                    (*gSubFunctionHandler)(&gMsgContextType);
                }
                gPeriodicResponseTimer[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition] = gPeriodicResponseRate[PeriodicDidList[CurrentPeriodicDidIndx].DidPosition];
                i = PeriodicDidCounter;
                CurrentPeriodicDidIndx++;
                if(CurrentPeriodicDidIndx == PeriodicDidCounter)
                {
                    CurrentPeriodicDidIndx = 0u;
                }
                else
                {    
                }
                break;
            } 
            else
            {
                if((CurrentPeriodicDidIndx + 1u) == PeriodicDidCounter)
                {
                    CurrentPeriodicDidIndx = 0u;
                }
                else
                {
                    CurrentPeriodicDidIndx++;
                }
            }
        }
    }
    else
    {
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_DidDispatcher
*                
* Description:   Implementation of Uds service 0x22
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_22_ENABLED == STD_ON)
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_DidDispatcher
(
    void
)
{
    uint16 tempdid;
    uint8* tempreqdata;
    uint32 i;
    uint16 j;
    /* add #if (DCM_SERVICE_2C_ENABLED == STD_ON) by larry 2013.11.11 */
    #if (DCM_SERVICE_2C_ENABLED == STD_ON)
    uint16 k;
    uint16 temp_22_Did_Index;
    uint8* temp_ptr_rsp_data;
    uint8* temp_ptr_rsp_data_org;
    uint8 temp_2C_error_status = STD_OFF;
    #endif
    uint8  securitylevel;
    uint8  sessiontype;
    uint8  SupportedDIDNum = 0u;
    
    /* changed by larry 2013.11.12 QAC */
    /* tempreqdata = gMsgContextType.reqData + 1u; */
    tempreqdata = (&gMsgContextType.reqData[1u]);
    gDidPosition = 0u;
    DidCounter = 0u;
    
    /* Check whether the request DIDs are supported and record total number of DID */
    /* search for all supported DID and record them */
    for(i = (uint32)0u; i < gMsgContextType.reqDataLen; i += (uint32)DCM_REQUIRE_DATA_LENGTH_2_BYTE)
    {
        /* changed by larry 2013.11.12 QAC */
        /* tempdid = Make16Bit(*tempreqdata,*(tempreqdata + 1u)); */
        tempdid = Make16Bit((*tempreqdata), tempreqdata[1u]);
        for(j = 0u; j < NUMBER_OF_READ_DID; j++)
        {
            if(tempdid == gDcmDsdSubService_22[j].DcmDspDidIdentifier)
            {
                /* Check session type */
                SupportedDIDNum++;
                sessiontype = gDcmDsdSubService_22[j].DcmDspDidReadSessionRef;
                securitylevel = gDcmDsdSubService_22[j].DcmDspDidReadSecurityLevelRef;
                

				/* parameter supported is in session or not*/
                if((sessiontype&gSesCtrlType) == DCM_SESSION_TYPE_NOT_CORRECT)
                {
                    j = NUMBER_OF_READ_DID;
					SupportedDIDNum--;
                }                
                /* parameter security is allow access or not*/
                else if((securitylevel & gSecLevelType) == DCM_SECURITY_LEVEL_NOT_CORRECT)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                    j = NUMBER_OF_READ_DID;
                    i = gMsgContextType.reqDataLen;
                }
                
                /* check if other condication are fullfilled */
                /* check if service security access is allowed */
                else if((service.ServiceTable.DcmDsdSidTabSecurityLevelRef & gSecLevelType) == 0u)
                {
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_SECURITYACCESSDENIED);
                    j = NUMBER_OF_READ_DID;
                    i = gMsgContextType.reqDataLen;
                }

                else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                    && ((service.AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                {
                    /* AddressingMode is not supportted */
                }
                else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                    && ((service.AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                {           
                    /* AddressingMode is not supportted */
                    DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
                    j = NUMBER_OF_READ_DID;
                    i = gMsgContextType.reqDataLen;
                }
                          
                /* Check DID adressing mode */
                else if((gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX) 
                       && ((gDcmDsdSubService_22[j].AddressingMode - gMsgContextType.msgAddInfo.reqType) < 1u))
                {
       
                }
                else if((gMsgContextType.msgAddInfo.reqType == UDS_PHYSICAL_ON_CAN_RX) 
                    && ((gDcmDsdSubService_22[j].AddressingMode&PHYSICAL_REQ_SUPPORTED) == DCM_REQUEST_ADDRESS_NOT_CORRECT))
                {

                }
                else
                {
                    DidList[DidCounter].Did = tempdid;
                    DidList[DidCounter].DidPosition = j;
                    DidCounter++;
                    j = NUMBER_OF_READ_DID; 
                }           
            }
            else 
            {
            }
        }
        /* changed by larry 2013.11.12 QAC */
        /* tempreqdata += DCM_SERVICE_22_DID_DATA_LENGTH; */
        tempreqdata = (&tempreqdata[DCM_SERVICE_22_DID_DATA_LENGTH]);
        #if (DCM_SERVICE_2C_ENABLED == STD_ON)
        for(j = 0u; j < NUMBER_OF_DYN_DID; j++)
        {
            if(tempdid == gDcmDsdSubService_2C[j].DcmDspDidIdentifier)
            {
                if((gDynamicalDidRelatedInfo[j].DynamicalDid == 0u)
                    ||(gDynamicalDidRelatedInfo[j].DynamicalDid != tempdid))
                {
                    gDynamicalDidRelatedInfo[j].DynamicalDid = DCM_ALL_BITS_ON_16;
                    DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_REQUESTOUTOFRANGE);
                    DsdInternal_ProcessingDone(&gMsgContextType);
                    temp_2C_error_status = STD_ON;
                }
                else
                {
                    temp_ptr_rsp_data_org = gMsgContextType.resData;
                    gMsgContextType.resData = (&gMsgContextType.resData[DCM_INDEX_1]); 

                    temp_ptr_rsp_data = gMsgContextType.resData;

                    for(i = 0u; i < gDynamicalDidRelatedInfo[j].SourceDidCounter; i++)
                    {
                        temp_22_Did_Index = gDynamicalDidRelatedInfo[j].ByDid[i].SourceDidPosition;
                        gSubFunctionHandler = gDcmDsdSubService_22[temp_22_Did_Index].DcmDspDataReadFnc;
                        gReadDID_2C_Active_Flag = STD_ON;
                        if(gSubFunctionHandler == DCM_NULL)
                        {                                                                        
                            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
                            temp_2C_error_status = STD_ON;
                        }
                        else
                        {
                            (*gSubFunctionHandler)(&gMsgContextType);
                        }

                        gMsgContextType.resData = temp_ptr_rsp_data;
                        
                        for(k = 0u; k < gDynamicalDidRelatedInfo[j].ByDid[i].MemorySize; k++)
                        {
                            gMsgContextType.resData[DCM_INDEX_2 + k] = gMsgContextType.resData[DCM_INDEX_2 + k + gDynamicalDidRelatedInfo[j].ByDid[i].PositionInSourceDataRecord - DCM_INDEX_1];
                            temp_ptr_rsp_data++;
                        }
                        gMsgContextType.resData += gDynamicalDidRelatedInfo[j].ByDid[i].MemorySize;
                    }
                    *temp_ptr_rsp_data_org = 0x22u;
                }
                break;
            }
            else 
            {
            }
        }
        gReadDID_2C_Active_Flag = STD_OFF;
        #endif
    }
    #if(DCM_SERVICE_2C_ENABLED == STD_ON)  
    if((gNegativeResponseCode != DCM_E_POSITIVERESPONSE)
        || (temp_2C_error_status == STD_ON))
    #else
    if(gNegativeResponseCode != DCM_E_POSITIVERESPONSE)
    #endif
    {
    }
    else if(SupportedDIDNum == 0u)
    {
       if(gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
       {
       	  DsdInternal_ProcessingDoneNoResponse();
       }
	   else
	   {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
	   }
    }
    
    /* check other state of the supported DID  */ 
    else if(DidCounter == 0u)
    {
       if(gMsgContextType.msgAddInfo.reqType == UDS_FUNCTIONAL_ON_CAN_RX)
       {
          DsdInternal_ProcessingDoneNoResponse();
       }
	   else
	   {
	   	  DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
	   }
    }
    else
    {
        /* Call realated did processing function */
        /* changed by larry 2013.11.12 QAC */
        /* (gMsgContextType.resData) += 1u; */
        gMsgContextType.resData = (&gMsgContextType.resData[1u]);         
        gMsgContextType.resDataLen = (uint32)1u;

        #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
        gDidResData = gMsgContextType.resData;
        /* change into #if #endif by larry 2013.11.11 */
        gDidResDataLen = gMsgContextType.resDataLen;
        #endif

        gSubFunctionHandler = gDcmDsdSubService_22[DidList[gDidPosition].DidPosition].DcmDspDataReadFnc;
        if(gSubFunctionHandler == DCM_NULL)
        {
                                                        
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
        }
        else
        {
            (*gSubFunctionHandler)(&gMsgContextType);
        }
    }

}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_10_11_28_85
*                
* Description:   If no error happened, give positive response if needed, and
*                call related application callback function
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_10_11_85
(
    void
)
{
    if(gMsgContextType.reqDataLen != (uint32)DCM_SERVICE_10_11_85_REQUIRE_DATA_LENGTH)
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
        DsdInternal_Uds_Common();
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_AccessAttemptNumberDec
*                
* Description:   Decrease allowed security access attempt number
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(DCM_SERVICE_27_ENABLED == STD_ON)
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_AccessAttemptNumberDec
(
    void
)
{
    if(gSecurityAcessAttempNumber[gCurrentSecurityIndex] != 0u)
    {
        gSecurityAcessAttempNumber[gCurrentSecurityIndex]--;
        if(gSecurityAcessAttempNumber[gCurrentSecurityIndex] == 0u)
        {
            /*gSecurityAcessAttempNumberExceeded[gCurrentSecurityIndex - 1] = 1u;*/
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_EXCEEDNUMBEROFATTEMPTS);
            /*gSecurityAcessAttempNumber[gCurrentSecurityIndex] = 1u;*/ /*gDcmDspSecurityRow[gCurrentSecurityIndex - 1u].DcmDspSecurityNumAttDelay;*/
            gSecurityDelayFlag[gCurrentSecurityIndex] = DCM_FLAG_ACTIVE;
        }
        else
        {
            DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_INVALIDKEY);
        }
    }   
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_UdsRepeatServiceCall
*                
* Description:   Repeat ServiceCall
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE) DsdInternal_UdsRepeatServiceCall(void)
{
    if((gDiagState&DIAG_UDS_PROCESSING) == DIAG_UDS_PROCESSING) 
    {
        if(gSubFunctionHandler != DCM_NULL)
        {
            (*gSubFunctionHandler)(&gMsgContextType);
        }
        else
        {
        }
    }
    else
    {
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_UdsPostServiceProcessing
*                
* Description:   Postprocessing of request."Post" means positive response has
*                been sent and confirmed.If negative response has been sent,this
*                function will not be called.
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_UdsPostServiceProcessing
(
    void
)
{
    if((gDiagState&DIAG_UDS_PROCESSING) != DIAG_UDS_PROCESSING)
    {
        if(gSubFunctionPostHandler != DCM_NULL)
        {
            (*gSubFunctionPostHandler)(E_OK);
            gSubFunctionPostHandler = DCM_NULL;
        }
        else
        {
        } 
    }
    else
    {
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_SessionTransferPostProcessing
*                
* Description:   Reset security access and rountine control releated  variables 
*               
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_SessionTransferPostProcessing
(
    void
)
{
    uint8 i;

    #if(DCM_SERVICE_31_ENABLED == STD_ON)
    for(i = 0u; i < NUMBER_OF_RID; i++)
    {
        gRountineControlSequence[i] = 0u;
    }
    gRountineControlDidHandle = DCM_INVALID_HANDLE_OR_ID;
    #endif

    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    for(i = 0u; i < KIND_OF_SECURITY_LEVEL; i++)
    {
        gSecurityAcessSequence[i] = 0u;
    }
    gSecLevelType = DCM_SEC_LEV_LOCK;  
    #endif
#if 0
    if(gSecurityDelayFlag == DCM_FLAG_DISACTIVE)
    {
        #if(DCM_SERVICE_27_ENABLED == STD_ON)
        for(i = 0u; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            if(gSecurityAcessDelayTime[i]
            == (gDcmDspSecurityRow[i].DcmDspSecurityDelayTime/DCM_TASK_TIME))
            {
                gSecurityAcessAttempNumber[i] = gDcmDspSecurityRow[i].DcmDspSecurityNumAttDelay;
            }
        }
        #endif
    }
#endif
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_Uds_Common
*                
* Description:   Abstraction of Common code of Uds Service function
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PRIVATE_CODE)  DsdInternal_Uds_Common
(
    void
)
{
    /* Check and call sub-function main hander */
    gSubFunctionHandler = gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunction;
    if(gSubFunctionHandler != DCM_NULL)
    {
        (*gSubFunctionHandler)(&gMsgContextType);
    }
    else
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_REQUESTOUTOFRANGE);
    }
    
    /* If the there is no error found in main handler,check and call 
       sub-function post hanler */
    if((gNegativeResponseCode == DCM_E_POSITIVERESPONSE) || (gNegativeResponseCode == DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING))
    {        
        if(gUDS_Physical_DiagBuffer[DCM_INDEX_0] == DCM_SERVICE_10_POSITIVE_RESPONSE_DATA) 
        {
            gCurrentSessionType = gUDS_Physical_DiagBuffer[DCM_INDEX_1];
        }
                                                          
        if(gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunctionPost != DCM_NULL)
        {
            gSubFunctionPostHandler = gDcmDsdSubService[gSubServicePosition].DcmDsdSubFunctionPost; 
        }
        else
        {
        }
    }
    else
    {
    }
}

#define DCM_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

#if(DCM_SERVICE_27_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_SecurityAccessKeyCompared
*                
* Description:   Post pocessing after application has finished key-checking
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_SecurityAccessKeyCompared
(
    const uint8 level, 
    const DcmDspSecurityAccessKey keyIsValid
)
{
    uint8 i;

    if (keyIsValid == KEY_IS_NOT_VALID)
    {   
        /*If key is not valid,decrease allowed attmept number */
        DsdInternal_AccessAttemptNumberDec();
    }
    
    /* If the key is valid,unlock realated security level and reset related variable */
    else
    {   
    #if(DCM_STRICTSEEDKEYSEQUENCE != STD_ON)
        gSecurityAcessSequence[gCurrentSecurityIndex] = 0u;
    #endif
        gSecurityAcessAttempNumber[gCurrentSecurityIndex] = gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecurityNumAttDelay;
        gSecurityAcessDelayTime[gCurrentSecurityIndex] = gDcmDspSecurityRow[gCurrentSecurityIndex].DcmDspSecurityDelayTime/DCM_TASK_TIME;
        Set_SecLevel(level);
    }
#if(DCM_STRICTSEEDKEYSEQUENCE == STD_ON)
    gSecurityAcessSequence[gCurrentSecurityIndex] = 0u;
#endif
}
#endif

#if(DCM_SERVICE_31_ENABLED == STD_ON) 
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_RoutineStarted
*                
* Description:   Set rountine started sequence flag
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RoutineStarted
(
    void
)
{
    gRountineControlSequence[gRountineControlDidHandle]  |= HAVE_STARTED_ROUNTINE;
    gRountineControlDidHandle = DCM_INVALID_HANDLE_OR_ID;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_RoutineStopped
*                
* Description:   Set rountine stopped sequence flag
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RoutineStopped
(
    void
)
{
    gRountineControlSequence[gRountineControlDidHandle] |= HAVE_STOPPED_ROUNTINE;
    /* Reset */
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DsdInternal_RequestRoutineResults
*                
* Description:   Set RequestRoutineResults sequence flag
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE)  DsdInternal_RequestRoutineResults
(
    void
)
{
    gRountineControlSequence[gRountineControlDidHandle] |= HAVE_REQ_ROUNTINE_RESULT;
    /* Reset */
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dsd_InteralInit
*                
* Description:   Init common global paramters
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/

FUNC(void,DCM_PUBLIC_CODE) Dsd_InteralInit(void)
{
    gP2ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
    Clr_P2_Server_Timer();
    ClrSuppressPosResponseBit();
    ClrNegativeResponseCode();
    Clr_ActiveProtocol();
    Reset_DiagState();
    Reset_PduId();
    gFunctionHandler = DCM_NULL;
    gSubFunctionHandler = DCM_NULL;
    gMsgContextType.resDataLen = (uint32)0u;
    Reset_Max_Number_Of_RCRRP() ;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dsd_GetSessionMapId
*                
* Description:   Map self define session to the real session level
*                             
* Inputs:        None
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(uint8,DCM_PUBLIC_CODE) Dsd_GetSessionMapId
(
    const Dcm_SesCtrlType DcmSessionType
) 
{
    uint8 SessionId;
    switch(DcmSessionType)   
    {
        case  DCM_SESSION_DEFAULT:
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_0;
        }
        break;
        
        case  DCM_SESSION_PROGRAMMING:                     
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_1;
        }
        break;
        
        case  DCM_SESSION_EXTENDED_DIAGNOSTIC:             
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_2;
        }
        break; 
        
        case  DCM_SESSION_USERDEFINED1:                    
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_3;
        }
        break;

        case  DCM_SESSION_USERDEFINED2:                    
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_4;
        }
        break;

        case  DCM_SESSION_USERDEFINED3:                    
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_5;
        }
        break;  
        case  DCM_SESSION_USERDEFINED4:                    
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_6;
        }
        break;

        case  DCM_SESSION_USERDEFINED5:                    
        {
            SessionId = DCM_SERVICE_10_SESSION_TYPE_7;
        }
        break;

        default:  
        {
            SessionId = 0u; 
        }
        break;            
    }

    if(SessionId >= KIND_OF_SESSION)
    {
        SessionId = 0; 
    }
    return SessionId;
}

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

