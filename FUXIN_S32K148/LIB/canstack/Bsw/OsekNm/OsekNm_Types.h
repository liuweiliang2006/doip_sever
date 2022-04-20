/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : OsekNm_Type.h
********************************************************************************
*   Project/Product : OsekNm module
*   Title                : OsekNm module Header File
*   Author             : Hirain
********************************************************************************
*   Description       : Type define file of the OsekNm
*
********************************************************************************
*   Limitations       : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*   Reference to Core C File
********************************************************************************
* END_FILE_HDR*/

#ifndef _OSEKNM_TYPES_H_
#define _OSEKNM_TYPES_H_

/*******************************************************************************
* Include files
*******************************************************************************/
#include "Platform_Types.h"
#include "ComStack_Types.h"
#include "OsekNm_Cfg.h"
/*******************************************************************************
  Local data types and structures
*******************************************************************************/
/*Description: This type represents the various status flags.*/
typedef union
{
    uint8 R[5];
    struct
    {
        uint8     NMStateCode        : 8;

#if defined(NM_BITORDER_LSB)
        uint8     NMInited           : 1;      /* byte0 bit0 */
        uint8     NMActive           : 1;      /* byte0 bit1 */
        uint8     NMBusError         : 1;      /* byte0 bit2 */
        uint8     NMCfgStable        : 1;      /* byte0 bit3 */
        uint8     NMBusOffFlag       : 1;      /* byte0 bit4 */
        uint8     ErrRestoring       : 1;      /* byte0 bit5 */
        uint8     SlowRecovery       : 1;      /* byte0 bit6 */
        uint8     NMAckErrFlag       : 1;      /* byte0 bit7 */

        uint8     TransmitFlag       : 1;      /* byte1 bit0 */
        uint8     UseRingData        : 1;      /* byte1 bit1 */
        uint8     ImDestined         : 1;      /* byte1 bit2 */
        uint8     ImSkipped          : 1;      /* byte1 bit3 */
        uint8     MerkerLimpHome     : 1;      /* byte1 bit4 */
        uint8     MerkerStable       : 1;      /* byte1 bit5 */
        uint8     LocalSleepAck      : 1;      /* byte1 bit6 */
        uint8     LocalSleepInd      : 1;      /* byte1 bit7 */

        /*Indicate whether T[ActiveMini] has reached*/
        uint8     ActTimeReach       : 1;      /* byte1 bit0 */
        /*Indicate whether The first Alive message has sent after wake up*/
        uint8     AliveSended        : 1;      /* byte1 bit1 */
        /*Indicate whether T[LimpHome] has reached*/
        uint8     LHTimeReach        : 1;      /* byte1 bit2 */
        uint8     LHtoBusSleep       : 1;      /* byte1 bit3 */
        /*Indicate whether from state Normal to WaitBusSleep is directly*/
        uint8     NMCanDiagFlag      : 1;      /* byte1 bit4 */
        /*Indicate whether from state LimpHome to WaitBusSleep is directly*/
        uint8     Reserved2          : 1;      /* byte1 bit5 */
        uint8     NMModeInd          : 2;      /* byte3 bit6~7 */
        uint8     NMTxCfm            : 1;
        uint8     NMRxInd            : 1;
        uint8     NMStartFlg         : 2;
        uint8     NMModeCtrl         : 2;
        uint8     Reserved3          : 2;

#else
        uint8     NMAckErrFlag       : 1;
        uint8     SlowRecovery       : 1;      /* byte0 bit1 */
        uint8     ErrRestoring       : 1;      /* byte0 bit2 */
        uint8     NMBusOffFlag       : 1;      /* byte0 bit3 */
        uint8     NMCfgStable        : 1;      /* byte0 bit4 */
        uint8     NMBusError         : 1;      /* byte0 bit5 */
        uint8     NMActive           : 1;      /* byte0 bit6 */
        uint8     NMInited           : 1;      /* byte0 bit7 */

        uint8     LocalSleepInd      : 1;      /* byte1 bit0 */
        uint8     LocalSleepAck      : 1;      /* byte1 bit1 */
        uint8     MerkerStable       : 1;      /* byte1 bit2 */
        uint8     MerkerLimpHome     : 1;      /* byte1 bit3 */
        uint8     ImSkipped          : 1;      /* byte1 bit4 */
        uint8     ImDestined         : 1;      /* byte1 bit5 */
        uint8     UseRingData        : 1;      /* byte1 bit6 */
        uint8     TransmitFlag       : 1;      /* byte1 bit7 */

        uint8     NMModeInd          : 2;      /* byte3 bit0~1 */
        uint8     Reserved2          : 1;      /* byte1 bit2 */
        uint8     NMCanDiagFlag      : 1;      /* byte1 bit3 */
        uint8     LHtoBusSleep       : 1;      /* byte1 bit4 */
        uint8     LHTimeReach        : 1;      /* byte1 bit5 */
        uint8     AliveSended        : 1;      /* byte1 bit6 */
        uint8     ActTimeReach       : 1;      /* byte1 bit7 */
        uint8     Reserved3          : 2;
        uint8     NMModeCtrl         : 2; 
        uint8     NMStartFlg         : 2; 
        uint8     NMRxInd            : 1;
        uint8     NMTxCfm            : 1;
#endif
    } B;
} nmStatusType;


/*******************************************************************************
* Name:    nmAlarmType
* Used by: NmSetAlarm() (parameter)
*******************************************************************************/

typedef enum
{
    /* nmAlarm=0, Timer TTyp */
    NM_TIMER_TYP = 0
    /* nmAlarm=1, Timer TMax */
    , NM_TIMER_MAX = 1
    /* nmAlarm=2, Timer TErr */
    , NM_TIMER_ERR = 2
    /* nmAlarm=3, Timer TWbs */
    , NM_TIMER_WBS = 3
    /* nmAlarm=4, Timer TTx */
    , NM_TIMER_TX = 4
    /* nmAlarm=5, fast Timer Tbusoff,OsekNm_006*/
    , NM_FAST_TIMER_TBUSOFF = 5
    /* nmAlarm=6, Slow Timer Tbusoff,OsekNm_008*/
    , NM_SLOW_TIMER_TBUSOFF = 6
#if(T_ACTIVE_MINI_ON == STD_ON)
    /* nmAlarm=7, Timer Tactivemini */
    , NM_TIMER_ACTIVEMINI  = 7
#endif
#if(T_LIMPHOME_MINI_ON == STD_ON)
    /* nmAlarm=8, Timer TLimpHome */
    , NM_TIMER_LIMPHOME    = 8
#endif
    /* nmAlarm=9, All Timer*/
    , NM_TIMER_All = 9
#if(NM_ACK_CHECK == STD_ON)
    , NM_ACK_TIMEOUT = 10
    , NM_ACK_RECOVERY = 11
#endif
} nmAlarmType;


/*******************************************************************************
* Name:    nmInitModeType
* Used by: NmInit() (parameter)
*******************************************************************************/
typedef enum
{
    /* SDL Enter0: NM first Init ---> OsekDirNmInit() and NmStart()*/
    NM_D_BUSINIT = 0,
    /* SDL Enter1: from bus off or normal */
    NM_D_BUSOFF = 1,
    /* SDL Enter2: NMInitBusSleep to NMTwbsNormal From --->
      NMNormal/NMNormalPreSleep to NMTwbsNormal*/
    NM_D_NORMAL_TO_BUSSLEEP = 2,
    /* SDL Enter3: leave NMBusSleep ---> NM state is sleep and GotoMode(Awake)
      is called or WakeUp signal is received*/
    NM_D_BUSAWAKE = 3,
    /* SDL Enter4: do not Init NM */
    NM_D_NOTINIT = 4,
    /* SDL Enter5: leave NMLimpHome */
    NM_D_LIMPHOME = 5,
    /* SDL Enter6: leave NMNormal */
    NM_D_NORMAL = 6,
    /* SDL Enter7: NMInitBusSleep to NMTwbsLimpHome */
    NM_D_LIMPHOME_TO_BUSSLEEP = 7
} nmInitModeType;

/*******************************************************************************
* Name:    nmSleepAwakeModeType
* Used by: GotoMode() (parameter)
*******************************************************************************/
typedef enum
{
    GOTO_INIT = 0,
    GOTO_BUSSLEEP = 1,
    GOTO_AWAKE = 2
} nmSleepAwakeModeType;

typedef enum
{
    START_INIT = 0,
    START_ON = 1,
    START_OFF = 2
} nmStartType;

/*******************************************************************************
* Name:    nmStateType
* Used by: NmGetCurState() (return type)
*          OsekNm_SetNxtState() (parameter)
* Description:
*******************************************************************************/
typedef uint8 nmStateType;
/*******************************************************************************
* Name:        nmIndexType
* Description: This type is used for the Index counter.
* Note:
*******************************************************************************/
typedef uint16 nmIndexType;
/*******************************************************************************
* Name:    NmReturnType
* Used by: CmpConfig() (return type)
*******************************************************************************/
/*typedef uint8 nmReturnType;*/

typedef enum
{
    NM_E_OK,
    NM_E_NOT_OK,
    NM_E_NOT_EXECUTED
} NmReturnType;
/*******************************************************************************
* Name:    NmNodeStateType
* Used by: NmSetConfig()/NmResetConfig()
*******************************************************************************/
/*typedef uint8 nmReturnType;*/
#if defined NM_ENABLE_CONFIG_NORMAL_LIMPHOME
typedef enum
{
    NM_NODE_OFFLINE  = 0,
    NM_NODE_NORMAL   = 1,
    NM_NODE_LIMPHOME = 2
} NmNodeStateType;
#endif

/*******************************************************************************
* Name:    CopyDirectionType
* Used by: 
*******************************************************************************/
typedef enum
{
    NM_NMRXBUF_TO_OTHERBUF,
    NM_OTHERBUF_TO_NMRXBUF    
} CopyDirectionType;


#endif

