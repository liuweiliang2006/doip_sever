/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : OsekNm.h
********************************************************************************
*   Project/Product : OsekNm
*   Title                : OsekNm.h
*   Author             : Hirain
********************************************************************************
*   Description     : Header of OsekNm module.
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*   Reference to Core C File
********************************************************************************
* END_FILE_HDR*/

#ifndef _OSEKNM_H_
#define _OSEKNM_H_


/*******************************************************************************
*   Includes
*******************************************************************************/
#include "CanIf.h"
#include "OsekNm_Types.h"

/*******************************************************************************
*   Macro definitions
*******************************************************************************/
#define DATA_INIT                        ((uint8)0x00u)
#define NM_BIT_SET                       (1)
#define NM_BIT_CLEAR                     (0)

/* configuration needed :relate to Licence */
#define V_DEF_SUPPORTED_PLATFORM
#define C_COMP_DIABDATA_MPC55XX

/* NM State Code Mask */
/* mask: 00011111 */
#define NM_STATE_CODE_MASK                ((uint8)0x1Fu)
/* mask: 11100000 */
#define NM_STATE_DECODE_MASK              ((uint8)0xE0u)

/*NM State start*/
#define NM_STATE_CODE_OFF                 ((nmStateType)0x00u)
#define NM_STATE_CODE_LIMPHOME            ((nmStateType)0x01u)
#define NM_STATE_CODE_NORMALPREPSLEEP     ((nmStateType)0x02u)
#define NM_STATE_CODE_LIMPHOMEPREPSLEEP   ((nmStateType)0x03u)
#define NM_STATE_CODE_TWBSNORMAL          ((nmStateType)0x04u)
#define NM_STATE_CODE_TWBSLIMPHOME        ((nmStateType)0x05u)
#define NM_STATE_CODE_BUSSLEEP            ((nmStateType)0x08u)
#define NM_STATE_CODE_NORMAL              ((nmStateType)0x09u)
#define NM_STATE_CODE_SHUTDOWN            ((nmStateType)0x0Au)

/*NM State end*/
#define NM_OWN_STATION     nmChannelNodeID[nmCurChannel]
#define NMTXPDUID          nmTxPduIdAry[nmCurChannel]
#define nmStatus           nmStatusAry[nmCurChannel]
#define nmTxDataFld        nmTxDataFldAry[nmCurChannel]
#define nmRxDataFld        nmRxDataFldAry[nmCurChannel]
/*Msg Rx ISR Buff*/
#define nmRxDataBuff       nmRxDataBuffAry[nmCurChannel]
#if defined ( NM_FOR_FAW )
#define nmTxMsgIndFld      nmTxMsgIndFldAry[nmCurChannel]
#define nmRxMsgIndFld      nmRxMsgIndFldAry[nmCurChannel]
#endif
#define nmLogicalSuccessor  nmLogicalSuccessorAry[nmCurChannel]
#define nmLogicalSuccessorl nmLogicalSuccessorlAry[nmCurChannel]
#define nmLogicalSuccessort nmLogicalSuccessortAry[nmCurChannel]

#define nmRxSourceAddr     nmRxSrcAddAry[nmCurChannel]
#define nmRxSrcAddrl       nmRxSrcAddlAry[nmCurChannel]
#define nmRxCount          nmRxCountAry[nmCurChannel]
#define nmTxCount          nmTxCountAry[nmCurChannel]
#define nmTimerCntTtyp     nmTimerCntTtypAry[nmCurChannel]
#define nmTimerCntTmax     nmTimerCntTmaxAry[nmCurChannel]
#define nmTimerCntTerr     nmTimerCntTerrAry[nmCurChannel]
#define nmTimerCntTwbs     nmTimerCntTwbsAry[nmCurChannel]
#define nmTimerCntTtx      nmTimerCntTtxAry[nmCurChannel]
#define nmTimerCntTbusoff  nmTimerCntTbusoffAry[nmCurChannel]
#if(NM_ACK_CHECK == STD_ON)
#define nmTimerCntTAck     nmTimerCntTAckAry[nmCurChannel]
#define nmTimerCntTAckRcy  nmTimerCntTAckRcyAry[nmCurChannel]

#endif

#if(T_ACTIVE_MINI_ON == STD_ON)
#define nmTimerCntTactivemini nmTimerCntTactiveminiAry[nmCurChannel]
#endif
#if(T_LIMPHOME_MINI_ON == STD_ON)
#define nmTimerCntTlimphome   nmTimerCntTlimphomeAry[nmCurChannel]
#endif

#define nubNmBusOffCnt        nubNmBusOffCntAry[nmCurChannel]

#define NM_PDU_DLC            ((uint8)0x08u)
#define NM_PDU_CONTROL_DLC    ((uint8)0x02u)
#define NM_PDU_BASICID        nmPduBasicIDAry[nmCurChannel]
#define NM_PDU_BASICID_MASK   nmPduBasicIDMaskAry[nmCurChannel]
#define NM_PDU_SOUCEID_MASK   nmPduSouceIDMaskAry[nmCurChannel]

#define NM_COUNT_TYP            \
    (nmCountTypAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_MAX            \
    (nmCountMaxAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_ERR            \
    (nmCountErrAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_WBS            \
    (nmCountWbsAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_TX             \
    (nmCountTxAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_FAST_TBUSOFF   \
    (nmCountBusoffFastTimerAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_SLOW_TBUSOFF   \
    (nmCountBusoffSlowTimerAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#if(T_ACTIVE_MINI_ON == STD_ON)
#define NM_COUNT_TACTIVEMINI    \
    (nmCountActMinAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#endif
#if(T_LIMPHOME_MINI_ON == STD_ON)
#define NM_COUNT_TLIMPHOME      \
    (nmCountTLimpHAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#endif

#if(NM_ACK_CHECK == STD_ON)
#define NM_COUNT_TACK      \
    (nmCountTAckAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#define NM_COUNT_TACKRCY      \
    (nmCountTAckRcyAry[nmCurChannel]/NM_MAINFUNCTION_PERIOD)
#endif

#define NM_BUSOFF_FAST_RECOVERY_TIMES     nmBusOffFastRecoveryAry[nmCurChannel]
#define NM_BUSOFF_SLOW_RECOVERY_TIMES     nmBusOffSlowRecoveryAry[nmCurChannel]
#define RX_LIMIT                          nmRxLimitAry[nmCurChannel]
#define TX_LIMIT                          nmTxLimitAry[nmCurChannel]

#if defined NM_ENABLE_CONFIG_NORMAL_LIMPHOME
#define NM_NUMBER_OF_CFG_NODE             nmNumberOfCfgNodeAry[nmCurChannel]
#define NM_NORMAL_CFG_RECORD(x)           (*(nmNormalCfgPtrAry[nmCurChannel] + x))
#define NM_LIMPHOME_CFG_RECORD(x)         (*(nmLimpHomeCfgPtrAry[nmCurChannel] + x))
#endif

/*CAN ID mode : standrd or extended*/
#define NM_CAN_ID_STANDARD_ENABLE     \
    (nmChannelConfigAry[nmCurChannel].B.NMIDStandardEn)
/* remote wakeup signal */
#define NM_REMOTE_WAKEUP_ENABLE       \
    (nmChannelConfigAry[nmCurChannel].B.NMRemoteWakeUpEn)
/* Congfig functions */
#define NM_CHN_CONFIG_NORMAL              \
    (nmChannelConfigAry[nmCurChannel].B.NMCfgNormalEn)
#define NM_CHN_CONFIG_LIMPHOME              \
    (nmChannelConfigAry[nmCurChannel].B.NMCfgLimpHEn)
/* Extended Callback functions */
#define NM_EXTENDED_CALLBACK_ENABLE   \
    (nmChannelConfigAry[nmCurChannel].B.NMExtCallBackEn)
#define NM_DEFAULT_ACTIVE    \
    (nmChannelConfigAry[nmCurChannel].B.NMDefaultActive)
#define NM_DEFAULT_STRATED   \
    (nmChannelConfigAry[nmCurChannel].B.NMDefaultStarted)
#define NM_USED_SWITCH     \
    (nmChannelConfigAry[nmCurChannel].B.NMUsedSwitch)

#define nmRealTimeStateCode             (nmStatus.B.NMStateCode)

#define nmStatusChnInit                 (nmStatus.B.NMInited)
#define nmStatusNMActive                (nmStatus.B.NMActive)
#define nmStatusNMBusError              (nmStatus.B.NMBusError)
#define nmStatusNMCfgStable             (nmStatus.B.NMCfgStable)
#define nmStatusNMBusOffFlag            (nmStatus.B.NMBusOffFlag)/*nmCanBusOffFlg*/
#define nmStatusErrRestoring            (nmStatus.B.ErrRestoring)/*nmCanBusOffBeing */
#define nmStatusSlowRecovery            (nmStatus.B.SlowRecovery)
#define nmStatusNMAckErrFlag            (nmStatus.B.NMAckErrFlag)
#define nmStatusNMCanDiagFlag           (nmStatus.B.NMCanDiagFlag)

#define nmStatusLocalSleepInd           (nmStatus.B.LocalSleepInd)
#define nmStatusLocalSleepAck           (nmStatus.B.LocalSleepAck)
#define nmStatusMerkerStable            (nmStatus.B.MerkerStable)
#define nmStatusMerkerLimpHome          (nmStatus.B.MerkerLimpHome)
#define nmStatusImSkipped               (nmStatus.B.ImSkipped)
#define nmStatusImDestined              (nmStatus.B.ImDestined)
#define nmStatusUseRingData             (nmStatus.B.UseRingData)
#define nmStatusTransmitFlag            (nmStatus.B.TransmitFlag)
#define nmStatusActTimeReach            (nmStatus.B.ActTimeReach)
#define nmStatusAliveSended             (nmStatus.B.AliveSended)
#define nmStatusLHTimeReach             (nmStatus.B.LHTimeReach)
#define nmStatusNortoBusSleep           (nmStatus.B.NortoBusSleep)
#define nmStatusLHtoBusSleep            (nmStatus.B.LHtoBusSleep)
#define nmStatusNMModeInd               (nmStatus.B.NMModeInd)
#define nmStatusNMModeCtrl              (nmStatus.B.NMModeCtrl)

#define nmStatusTxCfm                   (nmStatus.B.NMTxCfm)
#define nmStatusRxInd                   (nmStatus.B.NMRxInd)
#define nmStatusStartFlg                (nmStatus.B.NMStartFlg)

#define nmSkippedFlg                    nmSkippedFlgAry[nmCurChannel]
/* About two important algorithms */
/* Skipped in the logical ring & Determine logical successor */
#define nmRxMsgSourceId_S               nmRxSourceAddr
#define nmRxMsgDestId_D                 (nmRxDataBuff.B.DestID)
#define nmReceiverId_R                  NM_OWN_STATION
#define nmLogSucId_L                    nmLogicalSuccessor

/*MsgType in Rx Ind ISR*/
#define nmRxDataBuffMsgType             (nmRxDataBuff.B.OpCodeMsgType)
#define nmRxDataBuffByteDestID          (nmRxDataBuff.B.DestID)
#define nmRxDataBuffByteSleepInd        (nmRxDataBuff.B.OpCodeSleepInd)
#define nmRxDataBuffByteSleepAck        (nmRxDataBuff.B.OpCodeSleepAck)

/* nmRxDataFld */
#if defined (NM_FOR_FAW)
#define nmRxDataFldByteOpCode           (nmRxDataFld.B.OpCode)
#else
#define nmRxDataFldOpCodeMsgType        (nmRxDataFld.B.OpCodeMsgType)
#define nmRxDataFldOpCodeSleepInd       (nmRxDataFld.B.OpCodeSleepInd)
#define nmRxDataFldOpCodeSleepAck       (nmRxDataFld.B.OpCodeSleepAck)
#endif
#define nmRxDataFldByteDestID           (nmRxDataFld.B.DestID)


/* nmTxDataFld */
#if defined (NM_FOR_FAW)
#define nmTxDataFldByteOpCode           (nmTxDataFld.B.OpCode)
#else
#define nmTxDataFldOpCodeMsgType        (nmTxDataFld.B.OpCodeMsgType)
#define nmTxDataFldOpCodeSleepInd       (nmTxDataFld.B.OpCodeSleepInd)
#define nmTxDataFldOpCodeSleepAck       (nmTxDataFld.B.OpCodeSleepAck)
#endif
#define nmTxDataFldByteDestID           (nmTxDataFld.B.DestID)

#if defined (NM_FOR_FAW)
#define nmRxDataFldOpCodeMsgType        (nmRxMsgIndFld.B.OpCodeMsgType)
#define nmRxDataFldOpCodeSleepInd       (nmRxMsgIndFld.B.OpCodeSleepInd)
#define nmRxDataFldOpCodeSleepAck       (nmRxMsgIndFld.B.OpCodeSleepAck)
#define nmTxDataFldOpCodeMsgType        (nmTxMsgIndFld.B.OpCodeMsgType)
#define nmTxDataFldOpCodeSleepInd       (nmTxMsgIndFld.B.OpCodeSleepInd)
#define nmTxDataFldOpCodeSleepAck       (nmTxMsgIndFld.B.OpCodeSleepAck)
#endif


#define OSEKNM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"/* PRQA S 5087 */


#define OSEKNM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"/* PRQA S 5087 */



/*******************************************************************************
  Global function prototypes
*******************************************************************************/
/*******************************************************************************
  Global function prototypes
*******************************************************************************/
#define OSEKNM_START_SEC_PUBLIC_CODE
#include "MemMap.h"/* PRQA S 5087 */

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_Init_osek(void);
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_Talk
(
    const nmIndexType nmCurChannel
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_Silent
(
    const nmIndexType nmCurChannel
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_Start
(
    const nmIndexType nmCurChannel
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_Stop
(
    const nmIndexType nmCurChannel
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_GotoMode
(
    const nmIndexType nmCurChannel,
    const nmSleepAwakeModeType modeSleepAwake
);

extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_MainFunction_osek(void);

#if(NM_ACK_CHECK == STD_ON)
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_DiagStart
(
    const nmIndexType nmCurChannel
);
extern FUNC(void, OSEKNM_PUBLIC_CODE) CanNm_DiagStop
(
    const nmIndexType nmCurChannel
);
#endif


#if defined NM_ENABLE_DATA_ACCESS
extern FUNC(NmReturnType, OSEKNM_PUBLIC_CODE) CanNm_GetUserData
(
    const nmIndexType nmCurChannel,
    CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmUserData
);

extern FUNC(NmReturnType, OSEKNM_PUBLIC_CODE) CanNm_SetUserData
(
    const nmIndexType nmCurChannel,
    CONSTP2CONST(uint8, AUTOMATIC, OSEKNM_PUBLIC_CODE) nmUserData
);

extern FUNC(NmReturnType, OSEKNM_PUBLIC_CODE) CanNm_ReadNmData
(
    const nmIndexType nmCurChannel,
    CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) nmData
);
#endif

#if defined NM_ENABLE_CONFIG_NORMAL_LIMPHOME
extern FUNC(NmReturnType, OSEKNM_PUBLIC_CODE) CanNm_GetConfig
(
    const nmIndexType nmCurChannel,
    const NmNodeStateType nmNodeState,
    CONSTP2VAR(uint8, AUTOMATIC, OSEKNM_APPL_DATA) dataPtr
);
#endif

/*Basic NM CallBack function for the Application*/
/*indicate nm normal*/
extern void ApplNmCanStart(const nmIndexType nmChannelHandle);
/*This callback sets the communication hardware (CAN controller,bus transceiver)
* to a state from which they can be woken up by the CAN bus.*/
extern void ApplNmCanSleep(const nmIndexType nmChannelHandle);
/*indicates bus off error occured*/
extern void ApplNmBusOff(const nmIndexType nmChannelHandle);
/*indicates can bus wake up*/
extern void ApplNmCanWakeUp(const nmIndexType nmChannelHandle);
/*Enter LimpHome State,OsekNm_007*/
extern void ApplNmCanLimpHomeStart(const nmIndexType nmChannelHandle);
extern void ApplNmLimpHomeState(const nmIndexType nmChannelHandle);
/*Exit LimpHome State,OsekNm_007*/
extern void ApplNmCanLimpHomeEnd(const nmIndexType nmChannelHandle);
/*Slow Bus Off recovery failed*/
extern void ApplNmCanBusOffRecoveryFail(const nmIndexType nmChannelHandle);
/*indicate end of bus off error */
extern void ApplNmBusOffEnd(const nmIndexType nmChannelHandle);
/*This callback function is performed when busOff recovery successed.*/
extern void ApplNmBusOffRecoverySuccess(const nmIndexType nmChannelHandle);
extern void ApplNmWaitBusSleepCancel(const nmIndexType nmChannelHandle);
extern void ApplNmWaitBusSleep(const nmIndexType nmChannelHandle);
extern void ApplNmShutDown(const nmIndexType nmChannelHandle);
extern void ApplNmRingIndication(const nmIndexType nmChannelHandle, const nmNetIdType SourceID);
extern void ApplNmLimpHIndication(const nmIndexType nmChannelHandle, const nmNetIdType SourceID);
#if(NM_ACK_CHECK == STD_ON)
extern void ApplNmAckRecoveryStart(const nmIndexType nmChannelHandle);
extern void ApplNmAckRecoveryEnd(const nmIndexType nmChannelHandle);
#endif
#define OSEKNM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"/* PRQA S 5087 */


#endif  /* _OSEKNM_H_ */
