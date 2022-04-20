 /*BEGIN_FILE_HDR
***********************************************************************************************
* NOTICE
* This software is the property of HiRain Technologies. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* HiRain Technologies.
***********************************************************************************************
* File Name:       Nm.c
***********************************************************************************************
* Project/Product: AUTOSAR CanNm programe
* Title:           Nm.c
* Author:          Peng.Liu
***********************************************************************************************
* Description:     The file of AUTOSAR Nm programe
*
*
* (Requirements, pseudo code and etc.)
***********************************************************************************************
* Limitations:
*
* (limitations)
***********************************************************************************************
***********************************************************************************************
* Revision History��
*
* Version	Date	      Initials        Descriptions
* -------   ----------    ----------   -----------------
* 1.0	    26/08/11	  Peng.Liu		  Original
* 1.2       06/12/11      Peng.Liu        AUTOSAR R4.0 Rev2
* 2.0       08/12/11      Peng.Liu        Update to AUTOSAR R3.2 Rev1
*                                         Add the PN functional
*                                         Add the Car WakeUp functional
*                                         Immediate Transmission
* 2.1       20/03/12      Peng.Liu        Delete CANNM_IMMEDIATE_TXCONF_ENABLED==STD_ON
* 2.2		12/07/12	  Peng.Liu		  Avoid the bug of Immediate Restart function
* 2.3		31/10/12      Peng.Liu	      Add default in Case syntax.
***********************************************************************************************
*END_FILE_HDR*/

#include "Nm_Cbk.h"
#include "CanNm.h"
#include "CanIf.h"
#include "Com.h"

#include "FreeRTOS.h"
#include "com_task.h"

extern uint8 appstart;
extern uint8 NmSleepMode;
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
void Nm_NetworkMode
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
    Com_TxStart();
    Com_RxStart();
    uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"Nm_NetworkMode");
    // CanIf_SetControllerMode(0,CANIF_CS_STARTED);
    appstart = 1;
    NmSleepMode = 0;
}
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
void Nm_PrepareBusSleepMode
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
    uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"Nm_PrepareBusSleepMode");
    Com_TxStop();
    Com_RxStop();
}
void Nm_NetworkStartIndication
(
    NetworkHandleType nmNetworkHandle
)
{
	uart_printf_char_fml_api(UARTISRPRINT,__FUNCTION__,"Nm_NetworkStartIndication");
	CanNm_PassiveStartUp(0);
    (void)nmNetworkHandle;
}
/*[SWS_CanNm_00092]*//*[SWS_CanNm_00093]*/
void Nm_BusSleepMode
(
    NetworkHandleType nmNetworkHandle
)
{
	uart_printf_char_fml_api(UARTTASKPRINT,__FUNCTION__,"Nm_BusSleepMode");
    (void)nmNetworkHandle;
    NmSleepMode = 1;
    // CanIf_SetControllerMode(0,CANIF_CS_SLEEP);
}

/*[SWS_CanNm_00149]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
void Nm_RemoteSleepIndication
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
}
void Nm_RemoteSleepCancellation
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
}
#endif
#endif
/*[SWS_CanNm_00037]*/
#if(CANNM_PDU_RX_INDICATION_ENABLED == STD_ON)
void Nm_PduRxIndication
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
}
#endif
/*[SWS_CanNm_00166]*/
#if(CANNM_STATE_CHANGE_IND_ENABLED == STD_ON)
void Nm_StateChangeNotification
(
    NetworkHandleType nmNetworkHandle,
    Nm_StateType nmPreviousState,
    Nm_StateType nmCurrentState
)
{
    uint8 sdu[6]={0};
    (void)nmNetworkHandle;
    (void)nmPreviousState;
    if(NM_STATE_REPEAT_MESSAGE == nmCurrentState)
    {
        sdu[1] = 0;
    }
    else
    {
        sdu[1] = 1;
    }
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    CanNm_SetUserData(0,sdu);
#endif
}
#endif

/*[SWS_CanNm_00073]*/
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
void Nm_TxTimeoutException
(
    NetworkHandleType nmNetworkHandle
)
{
	//uart_printf_char_fml_api(UARTTASKPRINT,"Nm_TxTimeoutException");
    (void)nmNetworkHandle;
}
#endif
#endif
/*[SWS_CanNm_00014]*/
#if(CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)
#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if(CANNM_NODE_DETECTION_ENABLED == STD_ON)
void Nm_RepeatMessageIndication
(
    NetworkHandleType nmNetworkHandle
)
{
    (void)nmNetworkHandle;
}
#endif
#endif
#endif

