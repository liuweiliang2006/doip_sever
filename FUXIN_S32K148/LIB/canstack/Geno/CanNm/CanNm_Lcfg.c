/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Lcfg.c
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
*   04.03.02    24/09/2019     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/


/*******************************************************************************
*   Includes 
*******************************************************************************/

#include "CanNm_Lcfg.h"
#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
VAR(Nm_StateType, CANNM_VAR_NOINIT) CanNm_State[CANNM_NUMBER_OF_CHANNELS];
VAR(uint8, CANNM_VAR_NOINIT) CanNm_TxPduBuff[CANNM_NUMBER_OF_CHANNELS][CANNM_PDU_LENGTH];
VAR(PduInfoType, CANNM_VAR_NOINIT) CanNm_TxPdu[CANNM_NUMBER_OF_CHANNELS];
VAR(uint8, CANNM_VAR_NOINIT) CanNm_RxPduBuff[CANNM_NUMBER_OF_CHANNELS][CANNM_PDU_LENGTH];
VAR(PduInfoType, CANNM_VAR_NOINIT) CanNm_RxPdu[CANNM_NUMBER_OF_CHANNELS];
VAR(Nm_ModeType, CANNM_VAR_NOINIT) CanNm_Mode[CANNM_NUMBER_OF_CHANNELS];
VAR(CanNm_NetworkStateType, CANNM_VAR_NOINIT) CanNm_NetworkState[CANNM_NUMBER_OF_CHANNELS];
/*[SWS_CanNm_00257]*//*[SWS_CanNm_00260]*/
VAR(boolean, CANNM_VAR_NOINIT) CanNm_MsgTxEnabled[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_MsgCycOffsetTimer[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_MsgCycTimer[CANNM_NUMBER_OF_CHANNELS];
VAR(uint8, CANNM_VAR_NOINIT) CanNm_ImmTrans[CANNM_NUMBER_OF_CHANNELS];
VAR(boolean, CANNM_VAR_NOINIT) CanNm_TxCfmFlg[CANNM_NUMBER_OF_CHANNELS];
VAR(boolean, CANNM_VAR_NOINIT) CanNm_TxReqFlg[CANNM_NUMBER_OF_CHANNELS];
VAR(boolean, CANNM_VAR_NOINIT) CanNm_RxIndFlg[CANNM_NUMBER_OF_CHANNELS];
VAR(boolean, CANNM_VAR_NOINIT) CanNm_RptMsgReq[CANNM_NUMBER_OF_CHANNELS];
VAR(boolean, CANNM_VAR_NOINIT) CanNm_RptMsgReqBit[CANNM_NUMBER_OF_CHANNELS];
VAR(CanNm_NetworkReqType, CANNM_VAR_NOINIT) CanNm_NetworkReqCmd[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_NmTOTimer[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_RptMsgTimer[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_WbsTimer[CANNM_NUMBER_OF_CHANNELS];
STATIC VAR(uint16, CANNM_VAR_NOINIT) CanNm_TxTOTimer[CANNM_NUMBER_OF_CHANNELS];
VAR(CanNm_MsgTxRptType, CANNM_VAR_NOINIT)  CanNm_MsgTxRptCmd[CANNM_NUMBER_OF_CHANNELS];
#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
CONST(CanNm_LConfigType, CANNM_CONST) CanNm_LConfig[CANNM_NUMBER_OF_CHANNELS] =
{
    {
        ((boolean)STD_ON),                                  /*CanNmActiveWakeupBitEnabled*/
        ((boolean)STD_OFF),                                 /*CanNmAllNmMessagesKeepAwake*/
        ((uint8)0),                                         /*CanNmCarWakeUpBitPosition*/
        ((uint8)0),                                         /*CanNmCarWakeUpBytePosition*/
        ((boolean)STD_OFF),                                 /*CanNmCarWakeUpFilterEnabled*/
        ((uint8)0u),                                        /*CanNmCarWakeUpFilterNodeId*/
        ((boolean)STD_OFF),                                 /*CanNmCarWakeUpRxEnabled*/
        ((uint16)2),                                        /*CanNmImmediateNmCycleTime*/
        ((uint8)0u),                                        /*CanNmImmediateNmTransmissions*/
        ((uint16)0),                                        /*CanNmMsgCycleOffset*/
        ((uint16)20),                                       /*CanNmMsgCycleTime*/
        ((uint16)10),                                       /*CanNmMsgTimeoutTime*/
        CANNM_PDU_BYTE_1,                                   /*CanNmPduCbvPosition*/
        CANNM_PDU_BYTE_0,                                   /*CanNmPduNidPosition*/
        ((uint16)160),                                      /*CanNmRepeatMessageTime*/
        ((boolean)STD_OFF),                                 /*CanNmRetryFirstMessageRequest*/
        ((uint16)100),                                      /*CanNmTimeoutTime*/
        ((uint16)100),                                      /*CanNmWaitBusSleepTime*/
        ((NetworkHandleType)0),                             /*CanNmComMNetworkHandleRef*/
    },
};


CONST(CanNm_TimerType, CANNM_CONST) CanNm_Timer[CANNM_NUMBER_OF_CHANNELS] =
{
    {
        {&CanNm_MsgCycOffsetTimer[0]},
        {&CanNm_MsgCycTimer[0]},
        {&CanNm_TxTOTimer[0]},
        {&CanNm_NmTOTimer[0]},
        {&CanNm_RptMsgTimer[0]},
        {&CanNm_WbsTimer[0]},
    },
};


CONST(CanNm_ConfigType, CANNM_CONST) CanNm_Config[CANNM_NUMBER_OF_CHANNELS] =
{
    {0x20, 16},
};

#define CANNM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"



