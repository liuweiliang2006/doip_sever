/*BEGIN_FILE_HDR
***********************************************************************************************
* NOTICE
* This software is the property of HiRain Technologies. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* HiRain Technologies.
***********************************************************************************************
* File Name:       Nm_Cbk.h
***********************************************************************************************
* Project/Product: AUTOSAR CanNm programe
* Title:           _CanNm_H_
* Author:          Peng.Liu
***********************************************************************************************
* Description:     Header file of AUTOSAR CanNm programe
* 
*
* (Requirements, pseudo code and etc.)
***********************************************************************************************
* Limitations:
*
* (limitations)
***********************************************************************************************
***********************************************************************************************
* Revision History£º
*
* Version		Date		  	  Initials			CR#			Descriptions
* -------   ----------    ----------    ------  -----------------    -----------------
* 1.0		26/08/11	  	Peng.Liu			      N/A			Original
* 2.0	    22/07/16	  	liya.zhu			      N/A			HrAsrOsekNm160722-01
***********************************************************************************************
*END_FILE_HDR*/

#ifndef _NM_CBK_H_
#define _NM_CBK_H_


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "NmStack_Types.h"
#include "ComStack_Types.h" 
#include "CanNm_Cfg.h"

extern uint8 sleepFlg;
 /**********************************************************************************************************************
 * Functions
 *********************************************************************************************************************/
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
extern void Nm_NetworkMode
(
    NetworkHandleType nmNetworkHandle
);
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
extern void Nm_PrepareBusSleepMode
(
    NetworkHandleType nmNetworkHandle
);
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
extern void Nm_BusSleepMode
(
    NetworkHandleType nmNetworkHandle
);
extern void Nm_NetworkStartIndication
(
    NetworkHandleType nmNetworkHandle
);
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) 
/*[SWS_CanNm_00149]*/
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
extern void Nm_RemoteSleepIndication
(
    NetworkHandleType nmNetworkHandle
);
extern void Nm_RemoteSleepCancellation
(
    NetworkHandleType nmNetworkHandle
);
#endif
#endif
/*[SWS_CanNm_00037]*/
#if(CANNM_PDU_RX_INDICATION_ENABLED == STD_ON)
extern void Nm_PduRxIndication
(
    NetworkHandleType nmNetworkHandle
);
#endif
/*[SWS_CanNm_00166]*/
#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
extern void Nm_StateChangeNotification
(
    NetworkHandleType nmNetworkHandle,
    Nm_StateType nmPreviousState,
    Nm_StateType nmCurrentState
);
#endif
/*[SWS_CanNm_00073]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
extern void Nm_TxTimeoutException
(
    NetworkHandleType nmNetworkHandle
);
#endif
#endif
/*[SWS_CanNm_00014]*/
#if(CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
extern void Nm_RepeatMessageIndication
(
    NetworkHandleType nmNetworkHandle
);
#endif
#endif
#endif
#endif