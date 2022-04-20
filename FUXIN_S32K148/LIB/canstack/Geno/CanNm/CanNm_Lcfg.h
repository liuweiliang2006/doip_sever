/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Lcfg.h
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
#ifndef _CANNM_LCFG_H_
#define _CANNM_LCFG_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanNm_Types.h"

#define CANNM_PDU_LENGTH                                    ((uint8)8u)
#define CANNM_CH0_NODE_ID                                   ((uint8)0x28)
#define CANNM_CH0_TX_PDU_ID                                 ((uint8)0u)


#define CANNM_CHANNELNUM       CANNM_NUMBER_OF_CHANNELS
#define CANNM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
extern CONST(CanNm_ConfigType, CANNM_CONST) CanNm_Config[CANNM_NUMBER_OF_CHANNELS];
extern CONST(CanNm_LConfigType, CANNM_CONST) CanNm_LConfig[CANNM_NUMBER_OF_CHANNELS];
extern CONST(CanNm_TimerType, CANNM_CONST) CanNm_Timer[CANNM_NUMBER_OF_CHANNELS];
#define CANNM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
#define CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Nm_StateType, CANNM_VAR_NOINIT) CanNm_State[CANNM_NUMBER_OF_CHANNELS];
extern VAR(uint8, CANNM_VAR_NOINIT) CanNm_TxPduBuff[CANNM_NUMBER_OF_CHANNELS][CANNM_PDU_LENGTH];
extern VAR(PduInfoType, CANNM_VAR_NOINIT) CanNm_TxPdu[CANNM_NUMBER_OF_CHANNELS];
extern VAR(uint8, CANNM_VAR_NOINIT) CanNm_RxPduBuff[CANNM_NUMBER_OF_CHANNELS][CANNM_PDU_LENGTH];
extern VAR(PduInfoType, CANNM_VAR_NOINIT) CanNm_RxPdu[CANNM_NUMBER_OF_CHANNELS];
extern VAR(Nm_ModeType, CANNM_VAR_NOINIT) CanNm_Mode[CANNM_NUMBER_OF_CHANNELS];
extern VAR(CanNm_NetworkStateType, CANNM_VAR_NOINIT) CanNm_NetworkState[CANNM_NUMBER_OF_CHANNELS];
/*[SWS_CanNm_00257]*//*[SWS_CanNm_00260]*/
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_MsgTxEnabled[CANNM_NUMBER_OF_CHANNELS];
extern VAR(uint8, CANNM_VAR_NOINIT) CanNm_ImmTrans[CANNM_NUMBER_OF_CHANNELS];
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_TxCfmFlg[CANNM_NUMBER_OF_CHANNELS];
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_TxReqFlg[CANNM_NUMBER_OF_CHANNELS];
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_RxIndFlg[CANNM_NUMBER_OF_CHANNELS];
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_RptMsgReq[CANNM_NUMBER_OF_CHANNELS];
extern VAR(boolean, CANNM_VAR_NOINIT) CanNm_RptMsgReqBit[CANNM_NUMBER_OF_CHANNELS];
extern VAR(CanNm_NetworkReqType, CANNM_VAR_NOINIT) CanNm_NetworkReqCmd[CANNM_NUMBER_OF_CHANNELS];
extern VAR(CanNm_MsgTxRptType, CANNM_VAR_NOINIT)  CanNm_MsgTxRptCmd[CANNM_NUMBER_OF_CHANNELS];
#define CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
#endif


