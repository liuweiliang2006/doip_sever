/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm.c
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Network Management module Source File
*   Author          : Hirain
********************************************************************************
*   Description     : Implementation of CAN Network Management 
*                     provided functionality
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

/*******************************************************************************
*   Includes
*******************************************************************************/                     
#include "CanNm.h"
#include "CanNm_Cbk.h"
#include "CanNm_Callout.h"
/*[SWS_CanNm_00307]*/
#include "Nm_Cbk.h"
#include "Bsw_Common.h"
//#include "Det.h"
#include "SchM.h"
/*Version Check*/
#if(STD_ON == CANNM_PRIVATE_VERSION_CHECK)
/* check Version with other import module */
/* check Version with cfg file */
#if ((CANNM_AR_RELEASE_MAJOR_VERSION != CANNM_AR_RELEASE_MAJOR_VERSION_CFG) || \
   (CANNM_AR_RELEASE_MINOR_VERSION != CANNM_AR_RELEASE_MINOR_VERSION_CFG))
#error "AutoSar Version Numbers of CanNm and its cfg file are different"
#endif

#if ((CANNM_SW_MAJOR_VERSION != CANNM_SW_MAJOR_VERSION_CFG) || \
   (CANNM_SW_MINOR_VERSION != CANNM_SW_MINOR_VERSION_CFG))
#error "SW Version Numbers of CanNm and its cfg file are different"
#endif
#endif

extern uint8 nmActive;
extern uint16 nmTimeoutCnt;

/*dependency check*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_ON)
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
#error: "if CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_BUS_LOAD_REDUCTION_ENABLED = STD_OFF" 
#endif
#if(CANNM_BUS_SYNCHRONIZATION_ENABLED== STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_BUS_SYNCHRONIZATION_ENABLED = STD_OFF"
#endif
#if(CANNM_COM_USER_DATA_SUPPORT == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_COM_USER_DATA_SUPPORT = STD_OFF"
#endif
#if(CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_COORDINATOR_SYNC_SUPPORT = STD_OFF"
#endif
#if(CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_IMMEDIATE_RESTART_ENABLED = STD_OFF"
#endif
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_IMMEDIATE_TXCONF_ENABLED = STD_OFF"
#endif
#if(CANNM_NODE_ID_ENABLED == STD_OFF)
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON or CANNM_NODE_ID_ENABLED == STD_OFF\
        then CANNM_NODE_DETECTION_ENABLED = STD_OFF"
#endif
#endif
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
#error: "If CANNM_PASSIVE_MODE_ENABLED == STD_ON then CANNM_REMOTE_SLEEP_IND_ENABLED = STD_OFF"
#endif
#endif

#if(STD_ON == CANNM_DEV_ERROR_DETECT)
#define CANNM_DET_ERROR_DETECT(cond, ApiId, errcode)  \
        DET_ERROR_DETECT((cond), CANNM_MODULE_ID, CANNM_INSTANCE_ID,(ApiId),(errcode))
    
#define CANNM_DET_ERROR_DETECT_RET(cond, ApiId, errcode, ret) \
        DET_ERROR_DETECT_RET((cond), CANNM_MODULE_ID,CANNM_INSTANCE_ID,(ApiId),(errcode), (ret))
    
#define CANNM_DET_REPORT_ERROR(ApiId, errcode)  \
        DET_REPORT_ERROR(CANNM_MODULE_ID, CANNM_INSTANCE_ID, (ApiId), (errcode))
    
#else
#define  CANNM_DET_ERROR_DETECT(cond, ApiId, errcode)
#define  CANNM_DET_ERROR_DETECT_RET(cond, ApiId, errcode, ret)
#define  CANNM_DET_REPORT_ERROR(ApiId, errcode)
#endif
typedef void (* CanNm_TimerExpiresType)
(
    const NetworkHandleType nmChannelHandle
);
typedef enum
{
    CANNM_NETWORK_MODE_ENTER             =0u,      
    CANNM_RPT_MSG_REQ                    =1u,
    CANNM_RPT_MSG_BIT_RX                 =2u
} CanNm_RptMsgStEnterType;


#define CANNM_START_SEC_VAR_INIT_8
#include "MemMap.h"
STATIC VAR(Std_InitStateType, CANNM_VAR_POWER_ON_INIT) CanNm_InitState = STD_UNINITIALIZED;
#define CANNM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"

#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
#if(CANNM_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_POSTBUILD)
STATIC P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_VAR_NOINIT) CanNm_PBConfig;
#endif
#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define CANNM_USER_DATA_DEFAULT_VALUE        ((uint8)0xFFu)

/*[SWS_CanNm_00206]*/
#define CANNM_START_NMTO_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].NmTOTimer.TimerCnt) = CANNM_TIMEOUT_TIME(nmChannelHandle))
#define CANNM_STOP_NMTO_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].NmTOTimer.TimerCnt) = 0)
#define CANNM_NMTO_TIMER(nmChannelHandle)  \
        (&(CanNm_Timer[nmChannelHandle].NmTOTimer))
        
#define CANNM_START_RPT_MSG_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].RptMsgTimer.TimerCnt) = CANNM_RPT_MSG_TIME(nmChannelHandle)+1)
#define CANNM_STOP_RPT_MSG_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].RptMsgTimer.TimerCnt) = 0)
#define CANNM_RPT_MSG_TIMER(nmChannelHandle)  \
        (&(CanNm_Timer[nmChannelHandle].RptMsgTimer))       

#define CANNM_START_WBS_TIMER(nmChannelHandle)   \
        (*(CanNm_Timer[nmChannelHandle].WbsTimer.TimerCnt) = CANNM_WBS_TIME(nmChannelHandle))
#define CANNM_STOP_WBS_TIMER(nmChannelHandle)   \
        (*(CanNm_Timer[nmChannelHandle].WbsTimer.TimerCnt) = 0)
#define CANNM_WBS_TIMER(nmChannelHandle)   \
        (&(CanNm_Timer[nmChannelHandle].WbsTimer))
        
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#define CANNM_START_MSG_CYCLE_OFFSET(nmChannelHandle)   \
        (*(CanNm_Timer[nmChannelHandle].MsgCycOffsetTimer.TimerCnt) = CANNM_MSG_CYCLE_OFFSET(nmChannelHandle))
#define CANNM_STOP_MSG_CYCLE_OFFSET(nmChannelHandle)   \
        (*(CanNm_Timer[nmChannelHandle].MsgCycOffsetTimer.TimerCnt) = 0)
#define CANNM_MSG_CYCLE_OFFSET_TIMER(nmChannelHandle)   \
        (&(CanNm_Timer[nmChannelHandle].MsgCycOffsetTimer))
        
/*[SWS_CanNm_00073]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF) 
#define CANNM_START_TXTO_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].TxTOTimer.TimerCnt) = CANNM_MSG_TIMEOUT_TIME(nmChannelHandle))
#define CANNM_STOP_TXTO_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].TxTOTimer.TimerCnt) = 0)
#define CANNM_TXTO_TIMER(nmChannelHandle)  \
        (&(CanNm_Timer[nmChannelHandle].TxTOTimer))      
#endif
#define CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].MsgCycTimer.TimerCnt) = CANNM_MSG_CYCLE_TIME(nmChannelHandle))
#define CANNM_SET_MSG_CYC_IMM(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].MsgCycTimer.TimerCnt) = CANNM_IMM_NM_CYCLE_TIME(nmChannelHandle))
/*[SWS_CanNm_00052]*/
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
#define CANNM_SET_MSG_CYC_REDUCED(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].MsgCycTimer.TimerCnt) = CANNM_MSG_REDUCED_TIME(nmChannelHandle))
#endif
#define CANNM_STOP_MSG_CYC(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].MsgCycTimer.TimerCnt) = 0)
#define CANNM_MSG_CYC_TIMER(nmChannelHandle)  \
        (&(CanNm_Timer[nmChannelHandle].MsgCycTimer))
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
#define CANNM_START_RMT_SLP_IND_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].RmtSlpIndTimer.TimerCnt) = CANNM_RMT_SLP_IND_TIME(nmChannelHandle))
#define CANNM_STOP_RMT_SLP_IND_TIMER(nmChannelHandle)  \
        (*(CanNm_Timer[nmChannelHandle].RmtSlpIndTimer.TimerCnt) = 0)
#define CANNM_RMT_SLP_IND_TIMER(nmChannelHandle)  \
        (&(CanNm_Timer[nmChannelHandle].RmtSlpIndTimer))       
#endif
#endif
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(STD_ON == CANNM_NODE_DETECTION_ENABLED)
#define CANNM_CLR_RMB(nmChannelHandle)    CanNm_ClrRptMsgBit(nmChannelHandle)
#define CANNM_SET_RMB(nmChannelHandle)    CanNm_SetRptMsgBit(nmChannelHandle)
#define CANNM_RMB_MASK            ((uint8)0x01u)
#endif
#endif
#define CANNM_SET_ACTIVE_WUB(nmChannelHandle)      CanNm_SetActiveWakeupBit(nmChannelHandle)
#define CANNM_CLR_ACTIVE_WUB(nmChannelHandle)      CanNm_ClrActiveWakeupBit(nmChannelHandle) 
#define CANNM_ACTIVE_WU_MASK      ((uint8)0x10u)
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#define CANNM_TX_PDU_REQ(nmChannelHandle)          (CanNm_TxReqFlg[nmChannelHandle] = STD_ON)
#endif
/*CanNm_LConfig*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*ECUC_CanNm_00084*/
#define CANNM_ACTIVE_WU_BIT_ENABLED(nmChannelHandle)    CanNm_LConfig[nmChannelHandle].CanNmActiveWakeupBitEnabled
#endif
/*ECUC_CanNm_00068*/
#define CANNM_ALL_NMMSG_KEEP_AWAKE(nmChannelHandle)     CanNm_LConfig[nmChannelHandle].CanNmAllNmMessagesKeepAwake
/*[SWS_CanNm_00052]*/
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
/*ECUC_CanNm_00042*/
#define CANNM_BL_REDUCTION_ACTIVE(nmChannelHandle)      CanNm_LConfig[nmChannelHandle].CanNmBusLoadReductionActive
#endif
/*ECUC_CanNm_00075*/
#define CANNM_WU_BIT_POS(nmChannelHandle)               CanNm_LConfig[nmChannelHandle].CanNmCarWakeUpBitPosition
/*ECUC_CanNm_00076*/
#define CANNM_WU_BYTE_POS(nmChannelHandle)              CanNm_LConfig[nmChannelHandle].CanNmCarWakeUpBytePosition
/*ECUC_CanNm_00077*/
#define CANNM_CWU_FILTER_ENABLED(nmChannelHandle)       CanNm_LConfig[nmChannelHandle].CanNmCarWakeUpFilterEnabled
/*ECUC_CanNm_00078*/
#define CANNM_CWU_FILTER_NODE_ID(nmChannelHandle)       CanNm_LConfig[nmChannelHandle].CanNmCarWakeUpFilterNodeId
/*ECUC_CanNm_00074*/
#define CANNM_CWU_RX_ENABLED(nmChannelHandle)           CanNm_LConfig[nmChannelHandle].CanNmCarWakeUpRxEnabled
/*ECUC_CanNm_00057*/
#define CANNM_IMM_NM_CYCLE_TIME(nmChannelHandle)        CanNm_LConfig[nmChannelHandle].CanNmImmediateNmCycleTime
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*ECUC_CanNm_00056*/
#define CANNM_IMM_NM_TRANS(nmChannelHandle)             CanNm_LConfig[nmChannelHandle].CanNmImmediateNmTransmissions
/*ECUC_CanNm_00029*/
#define CANNM_MSG_CYCLE_OFFSET(nmChannelHandle)         CanNm_LConfig[nmChannelHandle].CanNmMsgCycleOffset
/*ECUC_CanNm_00028*/
#define CANNM_MSG_CYCLE_TIME(nmChannelHandle)           CanNm_LConfig[nmChannelHandle].CanNmMsgCycleTime  
/*[SWS_CanNm_00052]*/
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
/*ECUC_CanNm_00043*/
#define CANNM_MSG_REDUCED_TIME(nmChannelHandle)         CanNm_LConfig[nmChannelHandle].CanNmMsgReducedTime
#endif
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF) 
/*ECUC_CanNm_00030*/
#define CANNM_MSG_TIMEOUT_TIME(nmChannelHandle)         CanNm_LConfig[nmChannelHandle].CanNmMsgTimeoutTime
#endif
#endif
#if(CANNM_NODE_ID_ENABLED == STD_ON)
/*ECUC_CanNm_00031*/
#if(CANNM_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_POSTBUILD)
#define CANNM_NODE_ID(nmChannelHandle)                  (&CanNm_PBConfig[nmChannelHandle])->CanNmNodeId
#else
#define CANNM_NODE_ID(nmChannelHandle)                  CanNm_Config[nmChannelHandle].CanNmNodeId
#endif
#endif 
/*ECUC_CanNm_00026*/
/*[SWS_CanNm_00075]*/
#define CANNM_PDU_CBV_POS(nmChannelHandle)              CanNm_LConfig[nmChannelHandle].CanNmPduCbvPosition
/*ECUC_CanNm_00025*/
/*[SWS_CanNm_00074]*/
#define CANNM_PDU_NID_POS(nmChannelHandle)              CanNm_LConfig[nmChannelHandle].CanNmPduNidPosition
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
/*ECUC_CanNm_00023*/
/*[SWS_CanNm_00249]*/
#define CANNM_RMT_SLP_IND_TIME(nmChannelHandle)         CanNm_LConfig[nmChannelHandle].CanNmRemoteSleepIndTime
#endif
#endif
/*ECUC_CanNm_00022*/
/*[SWS_CanNm_00247]*/
#define CANNM_RPT_MSG_TIME(nmChannelHandle)             CanNm_LConfig[nmChannelHandle].CanNmRepeatMessageTime
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
/*ECUC_CanNm_00085*/
#define CANNM_RETRY_FIRST_MSG_REQ(nmChannelHandle)      CanNm_LConfig[nmChannelHandle].CanNmRetryFirstMessageRequest
#endif
/*ECUC_CanNm_00020*/
/*[SWS_CanNm_00246]*/
#define CANNM_TIMEOUT_TIME(nmChannelHandle)             CanNm_LConfig[nmChannelHandle].CanNmTimeoutTime
/*ECUC_CanNm_00021*/
/*[SWS_CanNm_00248]*/
#define CANNM_WBS_TIME(nmChannelHandle)                 CanNm_LConfig[nmChannelHandle].CanNmWaitBusSleepTime
/*ECUC_CanNm_00018*/
#define CANNM_COMM_NETWORK_HANDLE(nmChannelHandle)      CanNm_LConfig[nmChannelHandle].CanNmComMNetworkHandleRef
#if(CANNM_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_POSTBUILD)
#define CANNM_TX_PDU_ID(nmChannelHandle)                (&CanNm_PBConfig[nmChannelHandle])->CanNmTxPduRef
#else
#define CANNM_TX_PDU_ID(nmChannelHandle)                CanNm_Config[nmChannelHandle].CanNmTxPduRef
#endif

#define CANNM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, CANNM_CODE) CanNm_NetworkReqMainFunction
(
    const NetworkHandleType nmChannelHandle
);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
STATIC FUNC(void, CANNM_CODE) CanNm_RptMsgReqMainFunction
(
    const NetworkHandleType nmChannelHandle
);
#endif
#endif
STATIC FUNC(void, CANNM_CODE) CanNm_TxCfmMainFunction
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_RxIndMainFunction
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_NmTOExpires
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_RptMsgTimerExpires
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_MsgCycTimerExpires
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_MsgCycOffsetExpires
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_WbsTimerExpires
(
    const NetworkHandleType nmChannelHandle
);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
STATIC FUNC(void, CANNM_CODE) CanNm_RmtSlpIndTimerExpires
(
    const NetworkHandleType nmChannelHandle
);
#endif
/*[SWS_CanNm_00073]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
STATIC FUNC(void, CANNM_CODE) CanNm_TxTOTimerExpires
(
    const NetworkHandleType nmChannelHandle
);
#endif
#endif
STATIC FUNC(void, CANNM_CODE) CanNm_TimerMainFunction
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_TimerCheckFunction
(
    const NetworkHandleType nmChannelHandle,
    CONSTP2CONST(CanNm_CommTimerType, AUTOMATIC, CANNM_CONST) timer,
    const CanNm_TimerExpiresType TimerExpires
);
STATIC FUNC(void, CANNM_CODE) CanNm_RptMsgStateEnter
(
    const NetworkHandleType nmChannelHandle,
    const CanNm_RptMsgStEnterType nmEnterReason
);
STATIC FUNC(void, CANNM_CODE) CanNm_NormalOpStateEnter
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_RdySlpStateEnter
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_NetworkModeEnter
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_PreBusSlpModeEnter
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_BusSlpModeEnter
(
    const NetworkHandleType nmChannelHandle
);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(STD_ON == CANNM_NODE_DETECTION_ENABLED)
STATIC FUNC(void, CANNM_CODE) CanNm_ClrRptMsgBit
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_SetRptMsgBit
(
    const NetworkHandleType nmChannelHandle
);
#endif
#endif

#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_NODE_ID_ENABLED == STD_ON)
STATIC FUNC(void, CANNM_CODE) CanNm_SetNodeId
(
    const NetworkHandleType nmChannelHandle
);
#endif
STATIC FUNC(void, CANNM_CODE) CanNm_ClrActiveWakeupBit
(
    const NetworkHandleType nmChannelHandle
);
STATIC FUNC(void, CANNM_CODE) CanNm_SetActiveWakeupBit
(
    const NetworkHandleType nmChannelHandle
);
#endif

/*[SWS_CanNm_00072]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
STATIC FUNC(void, CANNM_CODE) CanNm_TxPduMainFunction
(
    const NetworkHandleType nmChannelHandle
);
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_Init
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANNM_CODE) CanNm_Init
( 
    P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_DATA) cannmConfigPtr 
)
{
    
    NetworkHandleType nmChannelHandle;
    uint8 i;
#if(CANNM_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_POSTBUILD)    
    /*[SWS_CanNm_00244]*/
    if(NULL_PTR == cannmConfigPtr)
    {
        CANNM_DET_REPORT_ERROR(CANNM_INIT_APIID, CANNM_E_PARAM_POINTER);
    }
    else
    {
        CanNm_PBConfig = cannmConfigPtr;
#else
        (void)cannmConfigPtr;
#endif
        for(nmChannelHandle = 0; nmChannelHandle < CANNM_CHANNELNUM; nmChannelHandle++ )
        {        
            /*[SWS_CanNm_00141]*/
            CanNm_State[nmChannelHandle] = NM_STATE_BUS_SLEEP;
            /*[SWS_CanNm_00144]*/
            CanNm_Mode[nmChannelHandle] = NM_MODE_BUS_SLEEP;
            CanNm_NetworkReqCmd[nmChannelHandle] = CANNM_NULL_CMD;
            CanNm_RxIndFlg[nmChannelHandle] = STD_OFF;
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
            CanNm_RptMsgReq[nmChannelHandle] = STD_OFF;
#endif
            CanNm_RptMsgReqBit[nmChannelHandle] = STD_OFF; 
#endif
            CANNM_STOP_NMTO_TIMER(nmChannelHandle);
            CANNM_STOP_RPT_MSG_TIMER(nmChannelHandle);
            CANNM_STOP_WBS_TIMER(nmChannelHandle);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_COM_CONTROL_ENABLED == STD_ON)
            CanNm_ComTxEnabled[nmChannelHandle] = STD_ON;
#endif
            CanNm_TxCfmFlg[nmChannelHandle] = STD_OFF;
            CANNM_STOP_MSG_CYCLE_OFFSET(nmChannelHandle);
            /*[SWS_CanNm_00143]*/
            CanNm_NetworkState[nmChannelHandle] = CANNM_NETWORK_RELEASED;
            CanNm_MsgTxEnabled[nmChannelHandle] = STD_OFF;
            /*[SWS_CanNm_00033]*//*[SWS_CanNm_00023]*/
            CANNM_STOP_MSG_CYC(nmChannelHandle);
            /*[SWS_CanNm_00061]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
            CANNM_STOP_TXTO_TIMER(nmChannelHandle);
#endif
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
            CanNm_RmtSlpInd[nmChannelHandle] = STD_OFF;
            CANNM_STOP_RMT_SLP_IND_TIMER(nmChannelHandle);
#endif
            CanNm_ImmTrans[nmChannelHandle] = 0;
            CanNm_TxPdu[nmChannelHandle].SduLength = CANNM_PDU_LENGTH;
            CanNm_TxPdu[nmChannelHandle].SduDataPtr = CanNm_TxPduBuff[nmChannelHandle];

            /*[SWS_CanNm_00025]*/
            for(i = 0;i < CANNM_PDU_LENGTH;i++)
            {
                CanNm_TxPduBuff[nmChannelHandle][i] = CANNM_USER_DATA_DEFAULT_VALUE;     
            }
            
            if(CANNM_PDU_OFF != CANNM_PDU_CBV_POS(nmChannelHandle))
            {
                /*[SWS_CanNm_00085]*/
                CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)] = 0x00u;    
            }
#if(CANNM_NODE_ID_ENABLED == STD_ON)
            /*[SWS_CanNm_00013]*/
            CanNm_SetNodeId(nmChannelHandle);
#endif
            CanNm_TxReqFlg[nmChannelHandle] = STD_OFF;
            CanNm_MsgTxRptCmd[nmChannelHandle] = CANNM_REPEAT_NULL;
#endif/*#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)*/
            CanNm_RxPdu[nmChannelHandle].SduLength = 0;
            CanNm_RxPdu[nmChannelHandle].SduDataPtr = CanNm_RxPduBuff[nmChannelHandle];
        }
        CanNm_InitState = STD_INITIALIZED;
#if(CANNM_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_POSTBUILD)    
    }
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_MainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANNM_CODE) CanNm_MainFunction
(
    void
)
{
    NetworkHandleType nmChannelHandle;
    /*[SWS_CanNm_00234]*/
    if(STD_UNINITIALIZED != CanNm_InitState)
    {
        for(nmChannelHandle = 0;nmChannelHandle < CANNM_CHANNELNUM;nmChannelHandle++)
        {
			CanNm_TimerMainFunction(nmChannelHandle);
			CanNm_NetworkReqMainFunction(nmChannelHandle);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)            
#if(STD_ON == CANNM_NODE_DETECTION_ENABLED)
            CanNm_RptMsgReqMainFunction(nmChannelHandle);
#endif
#endif
            CanNm_RxIndMainFunction(nmChannelHandle);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)            
            CanNm_TxCfmMainFunction(nmChannelHandle);
#endif
    /*[SWS_CanNm_00072]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)        
            CanNm_TxPduMainFunction(nmChannelHandle);
#endif
        }
    }
}

/*[SWS_CanNm_00284]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TxConfirmation
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANNM_CODE) CanNm_TxConfirmation
(
    PduIdType TxPudId
)
{
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
	NetworkHandleType nmChannelHandle;
    /*[SWS_CanNm_00195]*/
    if(TxPudId >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_TXCFM_APIID, CANNM_E_INVALID_CHANNEL);
    }
    /*[SWS_CanNm_00283]*/ 
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_TXCFM_APIID, CANNM_E_NO_INIT);
    }
    else
    {
        nmChannelHandle = (NetworkHandleType)TxPudId;
        if(nmChannelHandle < CANNM_CHANNELNUM)
        {
            CanNm_TxCfmFlg[nmChannelHandle] = STD_ON;
        }
    }
#endif
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RxIndication
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANNM_CODE) CanNm_RxIndication
(
    PduIdType RxPudId,
    const uint16 RxId,
    P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA)PduInfoPtr 
)
{
   
    NetworkHandleType nmChannelHandle;
    nmChannelHandle = (NetworkHandleType)RxPudId;
    (void)RxId;

    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        /*[SWS_CanNm_00244]*/
        CANNM_DET_REPORT_ERROR(CANNM_RXIND_APIID, CANNM_E_INVALID_CHANNEL);    
    }
    else if(NULL_PTR == PduInfoPtr)
    {
        /*[SWS_CanNm_00244]*/
        CANNM_DET_REPORT_ERROR(CANNM_RXIND_APIID, CANNM_E_PARAM_POINTER);
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        /*[SWS_CanNm_00244]*/
        CANNM_DET_REPORT_ERROR(CANNM_RXIND_APIID, CANNM_E_NO_INIT);
    }
    else
    /*[SWS_CanNm_00285]*/
    {
    	nmActive = 1;
        nmTimeoutCnt = 0;
        CanNm_RxIndFlg[nmChannelHandle] = STD_ON;
        /*[SWS_CanNm_00035]*/
        CanNm_RxPdu[nmChannelHandle].SduLength = PduInfoPtr->SduLength;
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_2();
        Bsw_MemCpy(CanNm_RxPdu[nmChannelHandle].SduDataPtr, PduInfoPtr->SduDataPtr,
                   PduInfoPtr->SduLength);
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_2();           
        /*[SWS_CanNm_00127]*/
        if(NM_MODE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
        {
            Nm_NetworkStartIndication(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
            /*[SWS_CanNm_00336]*/
            CANNM_DET_REPORT_ERROR(CANNM_RXIND_APIID, CANNM_E_NET_START_IND);                
        }
/*[SWS_CanNm_00037]*/
#if(CANNM_PDU_RX_INDICATION_ENABLED == STD_ON)
        Nm_PduRxIndication(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
#endif
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00135]*/
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
        if((CANNM_PDU_OFF != (CANNM_PDU_CBV_POS(nmChannelHandle)))
         &&(0x00u != ((CanNm_RxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)]) & CANNM_RMB_MASK)))
        {
            CanNm_RptMsgReqBit[nmChannelHandle] = STD_ON;
            /*[SWS_CanNm_00014]*/
#if(CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)                
            Nm_RepeatMessageIndication(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
#endif                 
        }
#endif 
#endif
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetState
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetState
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(Nm_StateType, AUTOMATIC, CANNM_APPL_DATA) nmStatePtr,
    P2VAR(Nm_ModeType, AUTOMATIC, CANNM_APPL_DATA) nmModePtr
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00277]*//*[SWS_CanNm_00192]*//*[SWS_CanNm_00244]*//*[SWS_CanNm_00039]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETSTATE_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETSTATE_APIID, CANNM_E_NO_INIT);    
        ret = E_NOT_OK;
    }
    else if((NULL_PTR == nmStatePtr)
          ||(NULL_PTR == nmModePtr))
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETSTATE_APIID, CANNM_E_PARAM_POINTER);  
        ret = E_NOT_OK;
    }
    else
    {
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_3(); 
        *nmStatePtr = CanNm_State[nmChannelHandle];
        *nmModePtr = CanNm_Mode[nmChannelHandle];
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_3();
        ret = E_OK;
    }
    return ret;
}
#if(CANNM_VERSION_INFO_API == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetVersionInfo
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANNM_CODE) CanNm_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CANNM_APPL_DATA) versioninfo
)
{
    if(NULL_PTR == versioninfo)
    {
        /*[SWS_CanNm_00244]*/
        CANNM_DET_REPORT_ERROR(CANNM_GETVERSIONINFO_APIID, CANNM_E_PARAM_POINTER);    
    }
    /*[SWS_CanNm_00192]*/
    else
    {
        versioninfo->vendorID = CANNM_VENDOR_ID;
        versioninfo->moduleID = CANNM_MODULE_ID;
        versioninfo->sw_major_version = CANNM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = CANNM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = CANNM_SW_PATCH_VERSION;
    }
}
#endif
/*[SWS_CanNm_00257]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NetworkRequest
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRequest
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00256]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_NETWORKREQUEST_APIID, CANNM_E_INVALID_CHANNEL);
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        /*[SWS_CanNm_00039]*/
        CANNM_DET_REPORT_ERROR(CANNM_NETWORKREQUEST_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else
    {
        CanNm_NetworkReqCmd[nmChannelHandle] = CANNM_NETWORK_REQUEST_CMD;
        ret = E_OK; 
    }
    return ret;
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_PassiveStartUp
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_PassiveStartUp
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00254]*//*[SWS_CanNm_00192]*//*[SWS_CanNm_00244]*//*[SWS_CanNm_00039]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_PASSIVESTARTUP_APIID, CANNM_E_INVALID_CHANNEL);                 
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_PASSIVESTARTUP_APIID, CANNM_E_NO_INIT);                 
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00147]*/
        if(NM_MODE_NETWORK == CanNm_Mode[nmChannelHandle])
        {
            ret = E_NOT_OK;
        }        
        else
        {
            CanNm_NetworkReqCmd[nmChannelHandle] = CANNM_PASSIVE_STARTUP_CMD;
            ret = E_OK;
        }
    }
    return ret;

}
/*[SWS_CanNm_00260]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NetworkRelease
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRelease
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00259]*//*[SWS_CanNm_00192]*//*[SWS_CanNm_00244]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_NETWORKRELEAE_APIID, CANNM_E_INVALID_CHANNEL);
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        /*[SWS_CanNm_00039]*/
        CANNM_DET_REPORT_ERROR(CANNM_NETWORKRELEAE_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else
    {
        CanNm_NetworkReqCmd[nmChannelHandle] = CANNM_NETWORK_RELEASE_CMD;
        ret = E_OK;
    }
    
    return ret;
}
#endif
/*[SWS_CanNm_00266]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00158]*/
#if(CANNM_USER_DATA_ENABLED == STD_ON)
/*[SWS_CanNm_00327]*/
#if(CANNM_COM_USER_DATA_SUPPORT == STD_OFF)
/*[SWS_CanNm_00217]*/
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_SetUserData
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetUserData
(
    NetworkHandleType nmChannelHandle, 
    P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00265]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_SETUSERDATA_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_SETUSERDATA_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmUserDataPtr)
    {
        /*[SWS_CanNm_00039]*/
        CANNM_DET_REPORT_ERROR(CANNM_SETUSERDATA_APIID, CANNM_E_PARAM_POINTER);    
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00159]*/
        CanNm_SetUserDataCall(CanNm_TxPdu[nmChannelHandle].SduDataPtr, nmUserDataPtr);
        ret = E_OK;
    }
    return ret;

}
#endif 
#endif
#endif
/*[SWS_CanNm_00268]*/
#if(CANNM_USER_DATA_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetUserData
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetUserData
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00267]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETUSERDATA_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETUSERDATA_APIID, CANNM_E_NO_INIT);    
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmUserDataPtr)
    {
        /*[SWS_CanNm_00039]*/
        CANNM_DET_REPORT_ERROR(CANNM_GETUSERDATA_APIID, CANNM_E_PARAM_POINTER);    
        ret = E_NOT_OK;
    }
    else
    {
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_2();
        /*[SWS_CanNm_00160]*/
        CanNm_GetUserDataCall(CanNm_RxPdu[nmChannelHandle].SduDataPtr, nmUserDataPtr);
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_2();;
        ret = E_OK;
    }
    return ret;
}
#endif

/*[SWS_CanNm_00262]*//*[SWS_CanNm_00264]*/
#if(CANNM_COM_CONTROL_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_DisableCommunication
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret = E_NOT_OK;
/*[SWS_CanNm_00298]*/    
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00261]*//*[SWS_CanNm_00172]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_DISABLECOMM_APIID, CANNM_E_INVALID_CHANNEL);
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_DISABLECOMM_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else if(NM_MODE_NETWORK != CanNm_Mode[nmChannelHandle])
    {
        /*[SWS_CanNm_00039]*/
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00170]*/
        CanNm_ComTxEnabled[nmChannelHandle] = STD_OFF;
        ret = E_OK;
    }
#endif
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_EnableCommunication
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret = E_NOT_OK;
/*[SWS_CanNm_00297]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00263]*//*[SWS_CanNm_00295]*//*[SWS_CanNm_00177]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_ENABLECOMM_APIID, CANNM_E_INVALID_CHANNEL);
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_ENABLECOMM_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;    
    }
    else if((NM_MODE_NETWORK != CanNm_Mode[nmChannelHandle])
          ||(STD_ON == CanNm_ComTxEnabled[nmChannelHandle]))
    {
        /*[SWS_CanNm_00039]*/
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00176]*/
        CanNm_ComTxEnabled[nmChannelHandle] = STD_ON;
        /*[SWS_CanNm_00180]*/
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        CANNM_START_RMT_SLP_IND_TIMER(nmChannelHandle);
#endif 
		ret = E_OK;
    }
#endif    
    return ret;
  }
#endif
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00274]*/
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RepeatMessageRequest
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RepeatMessageRequest 
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00137]*//*[SWS_CanNm_00273]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_RPTMSGREQ_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_RPTMSGREQ_APIID, CANNM_E_NO_INIT); 
        ret = E_NOT_OK;
    }
    else if((NM_STATE_REPEAT_MESSAGE == CanNm_State[nmChannelHandle])
     ||(NM_MODE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
     ||(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle]))
    {
        /*[SWS_CanNm_00039]*/
        ret = E_NOT_OK;
    }
    else
    {
        CanNm_RptMsgReq[nmChannelHandle] = STD_ON;
        ret = E_OK;
    }
    
    
    return ret;
}
#endif
#endif
/*[SWS_CanNm_00276]*/
#if((CANNM_NODE_DETECTION_ENABLED == STD_ON)||(CANNM_USER_DATA_ENABLED == STD_ON)||(CANNM_NODE_ID_ENABLED == STD_ON))
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetPduData
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetPduData
(
    NetworkHandleType nmChannelHandle,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmPduDataPtr
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00275]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETPDUDATA_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETPDUDATA_APIID, CANNM_E_NO_INIT);    
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmPduDataPtr)
    {
        /*[SWS_CanNm_00039]*/
        CANNM_DET_REPORT_ERROR(CANNM_GETPDUDATA_APIID, CANNM_E_PARAM_POINTER);  
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00138]*/
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_2();
        Bsw_MemCpy(nmPduDataPtr, CanNm_RxPdu[nmChannelHandle].SduDataPtr, 
                   CanNm_RxPdu[nmChannelHandle].SduLength);
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_2(); 
        ret = E_OK;
    }
    
    return ret;
}
#endif
/*[SWS_CanNm_00282]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_CheckRemoteSleepIndication
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_CheckRemoteSleepIndication
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(boolean, AUTOMATIC, CANNM_APPL_DATA) nmRemoteSleepIndPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00281]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {   
        CANNM_DET_REPORT_ERROR(CANNM_CHECKRMTSLEEPIND_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_CHECKRMTSLEEPIND_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmRemoteSleepIndPtr)
    {
        CANNM_DET_REPORT_ERROR(CANNM_CHECKRMTSLEEPIND_APIID, CANNM_E_PARAM_POINTER);
        /*[SWS_CanNm_00039]*/
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00154]*/
        if((NM_MODE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
         ||(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
         ||(NM_STATE_REPEAT_MESSAGE == CanNm_State[nmChannelHandle]))
        {
            ret = E_NOT_OK;    
        }
        else
        {
            /*[SWS_CanNm_00153]*/
            *nmRemoteSleepIndPtr = CanNm_RmtSlpInd[nmChannelHandle];
            ret = E_OK;
        }
    }
    return ret;
}
#endif
#endif
/*[SWS_CanNm_00280]*/
#if(CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RequestBusSynchronization
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynchronization
(
    NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret = E_NOT_OK;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00181]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_REQBUSSYNCH_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK; 
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_REQBUSSYNCH_APIID, CANNM_E_NO_INIT);    
        ret = E_NOT_OK; 
    }
    else if(STD_OFF == CanNm_ComTxEnabled[nmChannelHandle])
    {
        ret = E_NOT_OK;        
    }
    else
    {
        ret = E_OK;
    }
    return ret;
}
#endif
#endif

/*[SWS_CanNm_00270]*//*[SWS_CanNm_00272]*/
#if(CANNM_NODE_ID_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetNodeIdentifier
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNodeIdentifier
(
    NetworkHandleType nmChannelHandle,
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00269]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETNODEID_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETNODEID_APIID, CANNM_E_NO_INIT);
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmNodeIdPtr)
    {   
        CANNM_DET_REPORT_ERROR(CANNM_GETNODEID_APIID, CANNM_E_PARAM_POINTER);
        ret = E_NOT_OK;
    }
    else
    {
        /*[SWS_CanNm_00132]*/
        *nmNodeIdPtr = CanNm_RxPduBuff[nmChannelHandle][CANNM_PDU_NID_POS(nmChannelHandle)]; 
        ret = E_OK;
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_GetLocalNodeIdentifier
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetLocalNodeIdentifier 
(
    NetworkHandleType nmChannelHandle, 
    P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
)
{
    Std_ReturnType ret;
    /*[SWS_CanNm_00244]*//*[SWS_CanNm_00271]*//*[SWS_CanNm_00192]*/
    if(nmChannelHandle >= CANNM_CHANNELNUM)
    {   
        CANNM_DET_REPORT_ERROR(CANNM_GETLOCALNODEID_APIID, CANNM_E_INVALID_CHANNEL);    
        ret = E_NOT_OK;
    }
    else if(STD_UNINITIALIZED == CanNm_InitState)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETLOCALNODEID_APIID, CANNM_E_NO_INIT);    
        ret = E_NOT_OK;
    }
    else if(NULL_PTR == nmNodeIdPtr)
    {
        CANNM_DET_REPORT_ERROR(CANNM_GETLOCALNODEID_APIID, CANNM_E_PARAM_POINTER);    
        ret = E_NOT_OK;
    }
    else
    {
        *nmNodeIdPtr = CANNM_NODE_ID(nmChannelHandle);
        ret = E_OK;
    }
    return ret;
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NetworkReqMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE)CanNm_NetworkReqMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    CanNm_NetworkReqType cmd;
    SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0();
    cmd = CanNm_NetworkReqCmd[nmChannelHandle];
    CanNm_NetworkReqCmd[nmChannelHandle] = CANNM_NULL_CMD;
    SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0();
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
    if(CANNM_NETWORK_RELEASE_CMD == cmd)
    {
        /*[SWS_CanNm_00105]*/
        CanNm_NetworkState[nmChannelHandle] = CANNM_NETWORK_RELEASED;
        if(NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
        {
            /*[SWS_CanNm_00118]*/
            CanNm_RdySlpStateEnter(nmChannelHandle);            
        }
    }
    else if(CANNM_NETWORK_REQUEST_CMD == cmd)
    {
        /*[SWS_CanNm_00255]*/
        /*[SWS_CanNm_00104]*/
        CanNm_NetworkState[nmChannelHandle] = CANNM_NETWORK_REQUESTED;
        if((NM_MODE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
         ||(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle]))
        {
            /*[SWS_CanNm_00401]*/
            if(STD_ON == CANNM_ACTIVE_WU_BIT_ENABLED(nmChannelHandle))
            {
                CANNM_SET_ACTIVE_WUB(nmChannelHandle);
            }
            if(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
            {
                /*[SWS_CanNm_00122]*/
#if(CANNM_IMMEDIATE_RESTART_ENABLED == STD_ON)
                CANNM_TX_PDU_REQ(nmChannelHandle);
#endif
                CANNM_STOP_WBS_TIMER(nmChannelHandle);
            }
            /*[SWS_CanNm_00123]*/
            /*[SWS_CanNm_00129]*/
            CanNm_NetworkModeEnter(nmChannelHandle);
        }
        else if(NM_STATE_READY_SLEEP == CanNm_State[nmChannelHandle])
        {
            /*[SWS_CanNm_00006]*/
            CANNM_TX_PDU_REQ(nmChannelHandle);
            CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle);
            /*[SWS_CanNm_00110]*/
            CanNm_NormalOpStateEnter(nmChannelHandle);            
        }
        else
        {

        }
    }
    else 
#endif
    if(CANNM_PASSIVE_STARTUP_CMD == cmd)
    {
        /*[SWS_CanNm_00128]*/
        if((NM_MODE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
         ||(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle]))
        {
            CanNm_NetworkModeEnter(nmChannelHandle);
        }
    }
    else
    {

    }
            
}
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00135]*/  
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RptMsgReqMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE)CanNm_RptMsgReqMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    if(STD_ON == CanNm_RptMsgReq[nmChannelHandle])
    {
        CanNm_RptMsgReq[nmChannelHandle] = STD_OFF; 
        if((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
         ||(NM_STATE_READY_SLEEP == CanNm_State[nmChannelHandle]))
        {
            /*[SWS_CanNm_00120]*/
            /*[SWS_CanNm_00112]*/
            CanNm_RptMsgStateEnter(nmChannelHandle, CANNM_RPT_MSG_REQ);
/*[SWS_CanNm_00149]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
            /*[SWS_CanNm_00152]*/
            if(STD_ON == CanNm_RmtSlpInd[nmChannelHandle])
            {
                Nm_RemoteSleepCancellation(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
                CanNm_RmtSlpInd[nmChannelHandle] = STD_OFF;
                CANNM_STOP_RMT_SLP_IND_TIMER(nmChannelHandle);
            }
#endif
#endif
            /*[SWS_CanNm_00121]*/
            /*[SWS_CanNm_00113]*/
            CANNM_SET_RMB(nmChannelHandle);
        }
    }            
}
#endif
#endif

#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)            
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TxCfmMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_TxCfmMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    if(STD_ON == CanNm_TxCfmFlg[nmChannelHandle])
    {
        CanNm_TxCfmFlg[nmChannelHandle] = STD_OFF;    
        /*[SWS_CanNm_00099]*/
        CANNM_START_NMTO_TIMER(nmChannelHandle);
        /*[SWS_CanNm_00065]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)        
        CANNM_STOP_TXTO_TIMER(nmChannelHandle);
#endif        
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
        /*[SWS_CanNm_00157]*/
        if((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
         &&(STD_ON == CANNM_BL_REDUCTION_ACTIVE(nmChannelHandle)))
        
        {
            CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle);
        }
#endif 
    }
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RxIndMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_RxIndMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    if(STD_ON == CanNm_RxIndFlg[nmChannelHandle])
    {
        CanNm_RxIndFlg[nmChannelHandle] = STD_OFF;
        /*[SWS_CanNm_00098]*/
        CANNM_START_NMTO_TIMER(nmChannelHandle);
        /*[SWS_CanNm_00124]*/
        if(NM_MODE_PREPARE_BUS_SLEEP == CanNm_Mode[nmChannelHandle])
        {
            CanNm_NetworkModeEnter(nmChannelHandle);
            CANNM_STOP_WBS_TIMER(nmChannelHandle);
        }
/*[SWS_CanNm_00069]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
        /*[SWS_CanNm_00157]*/
        if((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
         &&(STD_ON == CANNM_BL_REDUCTION_ACTIVE(nmChannelHandle)))
        {
            CANNM_SET_MSG_CYC_REDUCED(nmChannelHandle);
        }
#endif
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
        /*[SWS_CanNm_00150]*/
        if(NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
        {
            CANNM_START_RMT_SLP_IND_TIMER(nmChannelHandle);
        }
        /*[SWS_CanNm_00151]*/
        if(((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
          ||(NM_STATE_READY_SLEEP == CanNm_State[nmChannelHandle]))
          &&(STD_ON == CanNm_RmtSlpInd[nmChannelHandle]))
        {
            Nm_RemoteSleepCancellation(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
            CanNm_RmtSlpInd[nmChannelHandle] = STD_OFF;
        }
        
#endif
#endif
    }
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
    /*[SWS_CanNm_00119]*//*[SWS_CanNm_00111]*/
    if(STD_ON == CanNm_RptMsgReqBit[nmChannelHandle])
    {
        CanNm_RptMsgReqBit[nmChannelHandle] = STD_OFF;
        if((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
         ||(NM_STATE_READY_SLEEP == CanNm_State[nmChannelHandle]))
        {
            CanNm_RptMsgStateEnter(nmChannelHandle, CANNM_RPT_MSG_BIT_RX);
        }
    }
#endif
#endif
    
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NmTOExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_NmTOExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00101]*//*[SWS_CanNm_00117]*/
    if((NM_STATE_REPEAT_MESSAGE == CanNm_State[nmChannelHandle])
     ||(NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle]))
    {
        CANNM_START_NMTO_TIMER(nmChannelHandle);
        /*[SWS_CanNm_00193]*//*[SWS_CanNm_00194]*/
        CANNM_DET_REPORT_ERROR(CANNM_MAINFUNC_APIID, CANNM_E_NETWORK_TIMEOUT);
    }
    else if(NM_STATE_READY_SLEEP == CanNm_State[nmChannelHandle])
    {
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)       
        /*[SWS_CanNm_00402]*/
        if(STD_ON == CANNM_ACTIVE_WU_BIT_ENABLED(nmChannelHandle))
        {
            CANNM_CLR_ACTIVE_WUB(nmChannelHandle);
        }
#endif
        /*[SWS_CanNm_00109]*/
        CanNm_PreBusSlpModeEnter(nmChannelHandle);
    }
    else
    {

    }
    
    
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RptMsgTimerExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_RptMsgTimerExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00102]*/
    /*[SWS_CanNm_00103]*/
    if(CANNM_NETWORK_REQUESTED == CanNm_NetworkState[nmChannelHandle])
    {
        CanNm_NormalOpStateEnter(nmChannelHandle);
    }
    /*[SWS_CanNm_00106]*/
    else if(CANNM_NETWORK_RELEASED == CanNm_NetworkState[nmChannelHandle])
    {
        CanNm_RdySlpStateEnter(nmChannelHandle);  
    }
    else
    {
    
    }
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
/*[SWS_CanNm_00107]*/    
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
    CANNM_CLR_RMB(nmChannelHandle);
#endif
#endif
}
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_MsgCycTimerExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_MsgCycTimerExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00032]*/
    CANNM_TX_PDU_REQ(nmChannelHandle);
    if((CanNm_ImmTrans[nmChannelHandle] > 0)
     &&(NM_STATE_REPEAT_MESSAGE == CanNm_State[nmChannelHandle]))
    {
        CanNm_ImmTrans[nmChannelHandle]--;
        if(CanNm_ImmTrans[nmChannelHandle] > 0)
        {
            CANNM_SET_MSG_CYC_IMM(nmChannelHandle);
        }
        else
        {
            /*[SWS_CanNm_00040]*/
            /*[SWS_CanNm_00335]*/
            CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle);
        }
    }
    else
    {     
        CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle);
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_MsgCycOffsetExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_MsgCycOffsetExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    CANNM_TX_PDU_REQ(nmChannelHandle);
    CANNM_SET_MSG_CYC_NORMAL(nmChannelHandle);
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_WbsTimerExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_WbsTimerExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00115]*/
    CanNm_BusSlpModeEnter(nmChannelHandle);
}
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/*[SWS_CanNm_00149]*/
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RmtSlpIndTimerExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_RmtSlpIndTimerExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00150]*//*[SWS_CanNm_00175]*/
    if((NM_STATE_NORMAL_OPERATION == CanNm_State[nmChannelHandle])
     &&(STD_ON == CanNm_ComTxEnabled[nmChannelHandle]))
    {
        CanNm_RmtSlpInd[nmChannelHandle] = STD_ON;
        Nm_RemoteSleepIndication(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
    }
}
#endif
#endif
/*[SWS_CanNm_00073]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TxTOTimerExpires
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_TxTOTimerExpires
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00066]*/
    Nm_TxTimeoutException(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
}
#endif
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TimerMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_TimerMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_NMTO_TIMER(nmChannelHandle),
                             &CanNm_NmTOExpires);
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_WBS_TIMER(nmChannelHandle),
                             &CanNm_WbsTimerExpires);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_MSG_CYCLE_OFFSET_TIMER(nmChannelHandle),
                             &CanNm_MsgCycOffsetExpires);
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_MSG_CYC_TIMER(nmChannelHandle),
                             &CanNm_MsgCycTimerExpires);
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_TXTO_TIMER(nmChannelHandle),
                             &CanNm_TxTOTimerExpires);
#endif
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_RMT_SLP_IND_TIMER(nmChannelHandle),
                             &CanNm_RmtSlpIndTimerExpires);
#endif
#endif
    CanNm_TimerCheckFunction(nmChannelHandle, CANNM_RPT_MSG_TIMER(nmChannelHandle),
                             &CanNm_RptMsgTimerExpires);
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TimerCheckFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_TimerCheckFunction
(
    const NetworkHandleType nmChannelHandle,
    CONSTP2CONST(CanNm_CommTimerType, AUTOMATIC, CANNM_CONST) timer,
    const CanNm_TimerExpiresType TimerExpires
)
{
    CONSTP2VAR(uint16, AUTOMATIC, CANNM_CONST) timerCnt = timer->TimerCnt;
    if(NULL_PTR != timerCnt)
    {
        if(*timerCnt > 0)
        {
            *timerCnt = (*timerCnt) - 1;
            if(0 == *timerCnt)
            {
                if(TimerExpires != NULL_PTR)
                {
				    TimerExpires(nmChannelHandle);
                }
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
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RptMsgStateEnter
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_RptMsgStateEnter
(
    const NetworkHandleType nmChannelHandle,
    const CanNm_RptMsgStEnterType nmEnterReason
)
{
	/*[SWS_CanNm_00166]*/
	#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
    Nm_StateChangeNotification(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle), CanNm_State[nmChannelHandle],
                               NM_STATE_REPEAT_MESSAGE);    
	#endif
	#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
	/*[SWS_CanNm_00007]*/
	if(STD_ON == CANNM_RETRY_FIRST_MSG_REQ(nmChannelHandle))
	{
		if(CanNm_State[nmChannelHandle] == NM_STATE_BUS_SLEEP)
		{
			CanNm_MsgTxRptCmd[nmChannelHandle] = CANNM_REPEAT_PENDING; 
		}
	}
	#endif    
    CanNm_State[nmChannelHandle] = NM_STATE_REPEAT_MESSAGE;
    /*[SWS_CanNm_00102]*/
    CANNM_START_RPT_MSG_TIMER(nmChannelHandle);
    /*[SWS_CanNm_00100]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_MsgTxEnabled[nmChannelHandle] = STD_ON;
    /*[SWS_CanNm_00156]*/
    /*[SWS_CanNm_00334]*/
    if((CANNM_NETWORK_REQUESTED == CanNm_NetworkState[nmChannelHandle])
     &&(CANNM_IMM_NM_TRANS(nmChannelHandle) > 0)
     &&(CANNM_NETWORK_MODE_ENTER == nmEnterReason))
    {
        CANNM_TX_PDU_REQ(nmChannelHandle);
        CanNm_ImmTrans[nmChannelHandle] = CANNM_IMM_NM_TRANS(nmChannelHandle);
        CanNm_ImmTrans[nmChannelHandle]--;
        CANNM_SET_MSG_CYC_IMM(nmChannelHandle);
    }
	else if((CANNM_IMM_NM_TRANS(nmChannelHandle) > 0)
     &&(CANNM_RPT_MSG_REQ == nmEnterReason))
    {/*Geely Requirment 20170114*/
        CANNM_TX_PDU_REQ(nmChannelHandle);
        CanNm_ImmTrans[nmChannelHandle] = CANNM_IMM_NM_TRANS(nmChannelHandle);
        CanNm_ImmTrans[nmChannelHandle]--;
        CANNM_SET_MSG_CYC_IMM(nmChannelHandle);
    }/*Geely Requirment 20170114*/
    /*[SWS_CanNm_00005]*/
    else
    {  
        if(0u != CANNM_MSG_CYCLE_OFFSET(nmChannelHandle))
        {
            CANNM_START_MSG_CYCLE_OFFSET(nmChannelHandle);
        }
        else
        {
            CanNm_MsgCycOffsetExpires(nmChannelHandle);
        }
    }
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NormalOpStateEnter
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_NormalOpStateEnter
(
    const NetworkHandleType nmChannelHandle
)
{
/*[SWS_CanNm_00166]*/
#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
    Nm_StateChangeNotification(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle), CanNm_State[nmChannelHandle],
                               NM_STATE_NORMAL_OPERATION);    
#endif
    CanNm_State[nmChannelHandle] = NM_STATE_NORMAL_OPERATION; 
    /*[SWS_CanNm_00116]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_MsgTxEnabled[nmChannelHandle] = STD_ON;
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
    CANNM_START_RMT_SLP_IND_TIMER(nmChannelHandle);
#endif 
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_RdySlpStateEnter
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_RdySlpStateEnter
(
    const NetworkHandleType nmChannelHandle
)
{
/*[SWS_CanNm_00166]*/
#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
    Nm_StateChangeNotification(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle), CanNm_State[nmChannelHandle],
                               NM_STATE_READY_SLEEP);    
#endif
    CanNm_State[nmChannelHandle] = NM_STATE_READY_SLEEP; 
    /*[SWS_CanNm_00108]]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_MsgTxEnabled[nmChannelHandle] = STD_OFF;
    /*[SWS_CanNm_00051]*/
    CANNM_STOP_MSG_CYC(nmChannelHandle);
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
    CANNM_STOP_RMT_SLP_IND_TIMER(nmChannelHandle);
#endif  
#endif
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_NetworkMode
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_NetworkModeEnter
(
    const NetworkHandleType nmChannelHandle
)
{    
    CanNm_Mode[nmChannelHandle] = NM_MODE_NETWORK;
    /*[SWS_CanNm_00314]*//*[SWS_CanNm_00315]*/
    CanNm_RptMsgStateEnter(nmChannelHandle, CANNM_NETWORK_MODE_ENTER);
    /*[SWS_CanNm_00096]*/
    CANNM_START_NMTO_TIMER(nmChannelHandle);
    /*[SWS_CanNm_00097]*/
    /*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
    Nm_NetworkMode(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_PreBusSlpModeEnter
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_PreBusSlpModeEnter
(
    const NetworkHandleType nmChannelHandle
)
{
/*[SWS_CanNm_00166]*/
#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
    Nm_StateChangeNotification(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle), CanNm_State[nmChannelHandle],
                               NM_STATE_PREPARE_BUS_SLEEP);    
#endif    
    CanNm_State[nmChannelHandle] = NM_STATE_PREPARE_BUS_SLEEP; 
    CanNm_Mode[nmChannelHandle] = NM_MODE_PREPARE_BUS_SLEEP;
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)      
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON) 
    CanNm_RmtSlpInd[nmChannelHandle] = STD_OFF;
#endif 
#endif
    /*[SWS_CanNm_00114]*/
    /*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
    Nm_PrepareBusSleepMode(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
    /*[SWS_CanNm_00115]*/
    CANNM_START_WBS_TIMER(nmChannelHandle);
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_BusSlpModeEnter
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_BusSlpModeEnter
(
    const NetworkHandleType nmChannelHandle
)
{
	/*[SWS_CanNm_00166]*/
	#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
    Nm_StateChangeNotification(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle), CanNm_State[nmChannelHandle],
                               NM_STATE_BUS_SLEEP);    
	#endif
	#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)	  
	/*[SWS_CanNm_00007]*/
	if(STD_ON == CANNM_RETRY_FIRST_MSG_REQ(nmChannelHandle))
	{
		CanNm_MsgTxRptCmd[nmChannelHandle] = CANNM_REPEAT_NULL; 
	}
	#endif	  

    CanNm_State[nmChannelHandle] = NM_STATE_BUS_SLEEP; 
    CanNm_Mode[nmChannelHandle] = NM_MODE_BUS_SLEEP;
    /*[SWS_CanNm_00126]*/
    /*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
    Nm_BusSleepMode(CANNM_COMM_NETWORK_HANDLE(nmChannelHandle));
}
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(STD_ON == CANNM_NODE_DETECTION_ENABLED)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_ClrRptMsgBit
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_ClrRptMsgBit
(
    const NetworkHandleType nmChannelHandle
)
{
    if(CANNM_PDU_OFF != CANNM_PDU_CBV_POS(nmChannelHandle))
    {
        (CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)]) &= (uint8)(~CANNM_RMB_MASK);    
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_SetRptMsgBit
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_SetRptMsgBit
(
    const NetworkHandleType nmChannelHandle
)
{
    if(CANNM_PDU_OFF != CANNM_PDU_CBV_POS(nmChannelHandle))
    {
        CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)] |= CANNM_RMB_MASK;    
    }
}
#endif
#endif

#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_NODE_ID_ENABLED == STD_ON)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_SetNodeId
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_SetNodeId
(
    const NetworkHandleType nmChannelHandle
)
{
    /*[SWS_CanNm_00013]*/
    if(CANNM_PDU_OFF != CANNM_PDU_NID_POS(nmChannelHandle))
    {
        CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_NID_POS(nmChannelHandle)] = CANNM_NODE_ID(nmChannelHandle);    
    }
}
#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_ClrActiveWakeupBit
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_ClrActiveWakeupBit
(
    const NetworkHandleType nmChannelHandle
)
{
    if(CANNM_PDU_OFF != CANNM_PDU_CBV_POS(nmChannelHandle))
    {
        (CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)]) &= (uint8)(~CANNM_ACTIVE_WU_MASK);    
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_SetActiveWakeupBit
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_SetActiveWakeupBit
(
    const NetworkHandleType nmChannelHandle
)
{
    if(CANNM_PDU_OFF != CANNM_PDU_CBV_POS(nmChannelHandle))
    {
        CanNm_TxPduBuff[nmChannelHandle][CANNM_PDU_CBV_POS(nmChannelHandle)] |= CANNM_ACTIVE_WU_MASK;    
    }
}
#endif

/*[SWS_CanNm_00072]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanNm_TxPduMainFunction
*                
* Description:   
*                             
* Inputs:        
*             
* Outputs:      
* 
* Limitations:   
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANNM_CODE) CanNm_TxPduMainFunction
(
    const NetworkHandleType nmChannelHandle
)
{
    Std_ReturnType ret;
    if((STD_ON == CanNm_TxReqFlg[nmChannelHandle])
      ||(CANNM_REPEAT_CFM == CanNm_MsgTxRptCmd[nmChannelHandle]))
    {
#if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        if(STD_ON == CanNm_ComTxEnabled[nmChannelHandle])
        {
#endif
            SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_1(); 
            ret = CanIf_Transmit(CANNM_TX_PDU_ID(nmChannelHandle),&CanNm_TxPdu[nmChannelHandle]);
            SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_1();
            /*[SWS_CanNm_00007]*/ 
			if(STD_ON == CANNM_RETRY_FIRST_MSG_REQ(nmChannelHandle))
			{
	            if( (CANNM_REPEAT_PENDING == CanNm_MsgTxRptCmd[nmChannelHandle])
					||(CANNM_REPEAT_CFM == CanNm_MsgTxRptCmd[nmChannelHandle]) )
	            {
	                if(E_NOT_OK == ret)
	                {
	                    CanNm_MsgTxRptCmd[nmChannelHandle] = CANNM_REPEAT_CFM;
	                }
	                else
	                {
	                    CanNm_MsgTxRptCmd[nmChannelHandle] = CANNM_REPEAT_SUCCESS;
	                }
	            }				
			}
            /*[SWS_CanNm_00071]*/
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON)
            CanNm_TxCfmFlg[nmChannelHandle] = STD_ON;
/*[SWS_CanNm_00073]*/
#else
            /*[SWS_CanNm_00064]*/
            CANNM_START_TXTO_TIMER(nmChannelHandle);           
#endif
#if(CANNM_COM_CONTROL_ENABLED == STD_ON)
        }
#endif
        CanNm_TxReqFlg[nmChannelHandle] = STD_OFF;
    }
}
#endif
#define CANNM_STOP_SEC_CODE
#include "MemMap.h"


