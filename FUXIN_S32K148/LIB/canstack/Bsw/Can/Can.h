/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : CAN Driver module Header File
*   Author          : Hirain
********************************************************************************
*   Description     : CAN Driver module Header File
*
********************************************************************************
*   Limitations     : only used for S32K14 FlexCAN moudle
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*   Reference to Core C File
********************************************************************************
* END_FILE_HDR*/

#ifndef CAN_H
#define CAN_H

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_PBcfg.h"

#if (STD_ON == CAN_DEV_ERROR_DETECT)
#include "Det.h"
#endif


/*******************************************************************************
*   Macro
*******************************************************************************/

/*CAN104 CAN080*/
#if (CAN_DEV_ERROR_DETECT == STD_ON )
#define  CAN_E_PARAM_POINTER      (0x01U)
#define  CAN_E_PARAM_HANDLE       (0x02U)
#define  CAN_E_PARAM_DLC          (0x03U)
#define  CAN_E_PARAM_CONTROLLER   (0x04U)
#define  CAN_E_UNINIT             (0x05U)
#define  CAN_E_TRANSITION         (0x06U)
#define  CAN_E_DATALOST           (0x07U)
#define  CAN_PL_INIT_ERROR        (0x08U)
#define  CAN_E_PARAM_BAUDRATE     (0x09U)
#define  CAN_E_INT_NEST           (0x0AU)

#define  CAN_INIT_APIID                                 (0x00U)
#define  CAN_MAINFUNCTION_WRITE_APIID                   (0x01U)
#define  CAN_INITCONTROLLER_APIID                       (0x02U)
#define  CAN_SETCONTROLLERMODE_APIID                    (0x03U)
#define  CAN_DISABLECONTROLLERINTERRUPTS_APIID          (0x04U)
#define  CAN_ENABLECONTROLLERINTERRUPTS_APIID           (0x05U)
#define  CAN_WRITE_APIID                                (0x06U)
#define  CAN_GETVERSIONINFO_APIID                       (0x07U)
#define  CAN_MAINFUNCTION_READ_APIID                    (0x08U)
#define  CAN_MAINFUNCTION_BUSOFF_APIID                  (0x09U)
#define  CAN_MAINFUNCTION_WAKEUP_APIID                  (0x0AU)
#define  CAN_CHECK_WAKEUP_APIID                         (0x0BU)
#define  CAN_MAINFUNCTION_MODE_APIID                    (0x0CU)
#define  CAN_SETBAUDRATE_APIID                          (0x0DU)
#define  CAN_MAINFUNCTION_CHECKACKERRAPIID              (0x0EU)
#define  CAN_RX_PROCESS_APIID                           (0x20U)

#endif

#define  CAN_INVALID_BD_INDEX                           (0xFFU)
#define CAN_DATA_DLC     CAN_MAX_DLC //lele add

/* Add for compatibility with EAS. */
#define CAN_CANFD_SUPPORT                                   STD_OFF 
#define CAN_CANFD_BITRATE                                   STD_OFF 
#define CAN_CONFIG_VARIANTS                                 STD_CONFIG_VARIANTS_PRECOMPILE
#define CAN_SW_MAJOR_VERSION_CFG                            1
#define CAN_SW_MINOR_VERSION_CFG                            1
#define CAN_SW_PATCH_VERSION_CFG                            0
#define CAN_SET_BAUDRATE_API                                STD_OFF
#define CAN_OS_COUNTER_USED                                 STD_OFF
#define CanPublicIcomSupport                                STD_OFF
#define CAN_VERSION_CHECK                                   STD_OFF


#define CAN_S32K_142                                        0
//#define CAN_S32K_144                                        1
#define CAN_S32K_146                                        2
#define CAN_S32K_148                                        3

/* generate tool's version*/
#define CAN_SW_MAJOR_VERSION_CFG                            1
#define CAN_SW_MINOR_VERSION_CFG                            1
#define CAN_SW_PATCH_VERSION_CFG                            0
#define CAN_AR_RELEASE_MAJOR_VERSION_CFG                    4
#define CAN_AR_RELEASE_MINOR_VERSION_CFG                    2
#define CAN_AR_RELEASE_REVISION_VERSION_CFG                 2

#define CAN_MAX_HTH_NUM                                     5



/* CAN026 CAN028 CAN091 CAN089 CAN082 CAN083 CAN084*/
#if(STD_ON == CAN_DEV_ERROR_DETECT)

#define  CAN_DET_ERROR_DETECT(cond, ApiId, errcode)  \
    Det_ReportError((cond), CAN_MODULE_ID, CAN_INSTANCE_ID,(ApiId),(errcode))

#define  CAN_DET_ERROR_DETECT_RET(cond, ApiId, errcode, ret) \
    Det_ReportError((cond), CAN_MODULE_ID,CAN_INSTANCE_ID,(ApiId),(errcode), (ret))

#define  CAN_DET_REPORT_ERROR(ApiId, errcode)  \
    Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (ApiId), (errcode))

#else/*CAN027 CAN424*/

#define  CAN_DET_ERROR_DETECT(cond, ApiId, errcode)
#define  CAN_DET_ERROR_DETECT_RET(cond, ApiId, errcode, ret)
#define  CAN_DET_REPORT_ERROR(ApiId, errcode)

#endif

/*******************************************************************************
*   Critical Area
*******************************************************************************/


/*******************************************************************************
*   Global Function Declaration
*******************************************************************************/

/* used in Can_EventPro.c */

#define CAN_START_SEC_VAR_INIT_8
#include "MemMap.h"
/*CAN103*/
extern VAR(Std_InitStateType, CAN_VAR)  Can_InitStatus;

#define CAN_STOP_SEC_VAR_INIT_8
#include "MemMap.h"


#define CAN_START_SEC_CODE
#include "MemMap.h"


#if(STD_ON == CAN_TXRX_INTERRUPT_SUPPORT)
extern FUNC(void, CAN_CODE) Can_Controller_MB_handler
(
    const uint8 Controller
);
#endif

#if(STD_ON == CAN_TXRX_POLLING_SUPPORT)

extern FUNC(void, CAN_CODE) Can_Controller_Tx_handler
(
    const uint8 Controller
);

extern FUNC(void, CAN_CODE) Can_Controller_Rx_handler
(
    const uint8 Controller
);
#endif

extern FUNC(void, CAN_CODE) Can_Controller_Busoff_handler
(
    const uint8 Controller
);

#if(STD_ON == CAN_WAKEUP_SUPPORT)
extern FUNC(void, CAN_CODE) Can_Controller_Wakeup_handler
(
    const uint8 Controller
);
#endif

#if (STD_ON == CAN_VERSION_INFO_API)
extern FUNC(void, CAN_CODE) Can_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo
);
#endif

extern FUNC(void, CAN_CODE) Can_Init(void);

#if (STD_ON == CAN_SET_BAUDRATE_API)
extern FUNC(Std_ReturnType, CAN_CODE) Can_SetBaudrate
(
    uint8 Controller,
    uint16 BaudRateConfigID
);
#endif

extern FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerMode
(
    uint8 Controller,
    Can_StateTransitionType Transition
);

extern FUNC(void, CAN_CODE) Can_DisableControllerInterrupts
(
    uint8 Controller
);

extern FUNC(void, CAN_CODE)Can_EnableControllerInterrupts
(
    uint8 Controller
);

extern FUNC(void, CAN_CODE)Can_DisableGlobalInterrupt(void);

extern FUNC(void, CAN_CODE) Can_EnableGlobalInterrupt(void);


extern FUNC(Can_ReturnType, CAN_CODE)Can_CheckWakeup
(
    uint8 Controller
);

extern FUNC(Can_ReturnType, CAN_CODE) Can_Write
(
    Can_HwHandleType Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
);

extern FUNC(Std_ReturnType, CAN_CODE)Can_InitController
(
    const uint8 Controller,
    const uint16 BaudRateConfigID
);


/* Scheduled functions */
extern FUNC(void, CAN_CODE) Can_MainFunction_Write(void);

extern FUNC(void, CAN_CODE) Can_MainFunction_Read(void);

extern FUNC(void, CAN_CODE) Can_MainFunction_BusOff(void);

extern FUNC(void, CAN_CODE) Can_MainFunction_Wakeup(void);

extern FUNC(void, CAN_CODE) Can_MainFunction_Mode(void);
#if(STD_ON == CanPublicIcomSupport)
extern Std_ReturnType Can_SetIComConfigration
(
    uint8 Controller,
    IcomConfigIdType ConfigurationId
);
#endif
#define CAN_STOP_SEC_CODE
#include "MemMap.h"


#endif /* CAN_H */

