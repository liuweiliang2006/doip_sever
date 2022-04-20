/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Types.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Network Management module type definitions head File
*   Author          : Hirain
********************************************************************************
*   Description     : CAN Network Management module type definitions head File
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

#ifndef _CAN_NM_TYPES_H_
#define _CAN_NM_TYPES_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "ComStack_Types.h"   
#include "NmStack_Types.h"
#include "CanNm_Cfg.h" 
#include "CanNm_Version.h"
#include "CanIf.h"

typedef enum
{
  CANNM_PDU_BYTE_0             =0u, /*Byte 0 is used*/     
  CANNM_PDU_BYTE_1             =1u, /*Byte 1 is used*/
  CANNM_PDU_OFF                =2u /*No Byte is used*/
}CanNm_PduBytePosType;

/*[SWS_CanNm_00202]*/
typedef struct
{
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    /*ECUC_CanNm_00084*/
    boolean CanNmActiveWakeupBitEnabled;
#endif
    /*ECUC_CanNm_00068*/
    boolean CanNmAllNmMessagesKeepAwake;
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
    /*ECUC_CanNm_00042*/
    boolean CanNmBusLoadReductionActive;
#endif
    /*ECUC_CanNm_00075*/
    uint8 CanNmCarWakeUpBitPosition;
    /*ECUC_CanNm_00076*/
    uint8 CanNmCarWakeUpBytePosition;
    /*ECUC_CanNm_00077*/
    boolean CanNmCarWakeUpFilterEnabled;
    /*ECUC_CanNm_00078*/
    uint8 CanNmCarWakeUpFilterNodeId;
    /*ECUC_CanNm_00074*/
    boolean CanNmCarWakeUpRxEnabled;
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) 
    /*ECUC_CanNm_00057*/
    uint16 CanNmImmediateNmCycleTime;
    /*ECUC_CanNm_00056*/
    uint8 CanNmImmediateNmTransmissions;
    /*ECUC_CanNm_00029*/
    uint16 CanNmMsgCycleOffset;
    /*ECUC_CanNm_00028*/
    uint16 CanNmMsgCycleTime;  
#if(CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON)
    /*ECUC_CanNm_00043*/
    uint16 CanNmMsgReducedTime;
#endif
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)  
    /*ECUC_CanNm_00030*/
    uint16 CanNmMsgTimeoutTime;
#endif    
#endif
    /*ECUC_CanNm_00026*/
    CanNm_PduBytePosType CanNmPduCbvPosition;
    /*ECUC_CanNm_00025*/
    CanNm_PduBytePosType CanNmPduNidPosition;
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) 
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
    /*ECUC_CanNm_00023*/
    uint16 CanNmRemoteSleepIndTime;
#endif
#endif
    /*ECUC_CanNm_00022*/
    uint16 CanNmRepeatMessageTime;
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    
    /*ECUC_CanNm_00085*/
    boolean CanNmRetryFirstMessageRequest;
#endif
    /*ECUC_CanNm_00020*/
    uint16 CanNmTimeoutTime;
    /*ECUC_CanNm_00021*/
    uint16 CanNmWaitBusSleepTime; 
    /*ECUC_CanNm_00018*/
    NetworkHandleType CanNmComMNetworkHandleRef;
} CanNm_LConfigType;
typedef struct
{
#if(CANNM_NODE_ID_ENABLED == STD_ON)
    /*ECUC_CanNm_00031*/
    uint8 CanNmNodeId;
#endif
    /*ECUC_CanNm_00037*/
    PduIdType CanNmTxPduRef;
}CanNm_ConfigType;
typedef enum
{
    CANNM_NETWORK_RELEASED             =0u,      /*NetworkReleased State*/
    CANNM_NETWORK_REQUESTED            =1u      /*NetworkRequested State*/
} CanNm_NetworkStateType;

typedef enum
{
    CANNM_NULL_CMD            = 0u,
    CANNM_NETWORK_REQUEST_CMD = 1u,      
    CANNM_NETWORK_RELEASE_CMD = 2u,
    CANNM_PASSIVE_STARTUP_CMD = 3u
} CanNm_NetworkReqType;
typedef enum
{
    CANNM_REPEAT_NULL            = 0u,
    CANNM_REPEAT_PENDING         = 1u,
    CANNM_REPEAT_CFM             = 2u,
    CANNM_REPEAT_SUCCESS         = 3u
} CanNm_MsgTxRptType;
typedef struct
{
    uint16* TimerCnt;
} CanNm_CommTimerType;
typedef struct
{
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_CommTimerType MsgCycOffsetTimer;
    CanNm_CommTimerType MsgCycTimer;
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
    CanNm_CommTimerType TxTOTimer;    
#endif    
#endif
    CanNm_CommTimerType NmTOTimer;
    CanNm_CommTimerType RptMsgTimer;
    CanNm_CommTimerType WbsTimer;
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) 
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
    CanNm_CommTimerType RmtSlpIndTimer;
#endif
#endif
} CanNm_TimerType;

#endif  /*_CAN_NM_TYPES_H_*/

