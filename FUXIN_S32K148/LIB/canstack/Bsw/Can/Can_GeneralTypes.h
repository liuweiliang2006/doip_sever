/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_GeneralTypes.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : Can_GeneralTypes
*   Author          : Hirain
********************************************************************************
*   Description     : Can_GeneralTypes   .
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
********************************************************************************
* END_FILE_HDR*/
#ifndef CAN_GERERALTYPES_H
#define CAN_GERERALTYPES_H

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_GeneralTypes_Cfg.h"

/* CAN438 CAN439*/
/* CAN142 CAN417 CAN039*/
typedef enum
{
    CAN_T_START  = 0,
    CAN_T_STOP   = 1,
    CAN_T_SLEEP  = 2,
    CAN_T_WAKEUP = 3,
    CAN_T_NONE   = 4
} Can_StateTransitionType;



typedef enum
{
    CAN_OK     = 0,
    CAN_NOT_OK = 1,
    CAN_BUSY   = 2
} Can_ReturnType;


/*CAN415*/
typedef struct
{
    PduIdType   swPduHandle;
    uint8       length ;
    Can_IdType  id ;
    P2VAR(uint8, TYPEDEF, CAN_APPL_DATA)   sdu ;
} Can_PduType;


/*SWS_CAN_00496*/
typedef struct
{
    Can_IdType        CanId;
    Can_HwHandleType  Hoh ;
    uint8             ControllerId ;
} Can_HwType;

typedef enum
{
    CANTRCV_TRCVMODE_NORMAL  = 0,
    CANTRCV_TRCVMODE_SLEEP   = 1,
    CANTRCV_TRCVMODE_STANDBY = 2
} CanTrcv_TrcvModeType;

typedef enum
{
    CANTRCV_WUMODE_ENABLE  = 0,
    CANTRCV_WUMODE_DISABLE = 1,
    CANTRCV_WUMODE_CLEAR   = 2
} CanTrcv_TrcvWakeupModeType;

typedef enum
{
    CANTRCV_WU_ERROR         = 0,
    CANTRCV_WU_BY_BUS        = 1,
    CANTRCV_WU_BY_PIN        = 2,
    CANTRCV_WU_INTERNALLY    = 3,
    CANTRCV_WU_NOT_SUPPORTED = 4,
    CANTRCV_WU_POWER_ON      = 5,
    CANTRCV_WU_RESET         = 6,
    CANTRCV_WU_BY_SYSERR     = 7
} CanTrcv_TrcvWakeupReasonType;



/* Non Autosar Standard */
#define CAN_MAX_DLC                     (8)
#define CANFD_MAX_DLC                   (64)
#define CANFD_PADDING_INDEX_LO          (9)
#define CANFD_PADDING_INDEX_HI          (16)

#define CAN_STD_MAX_CANID               ((Can_IdType)0x07FFU)
#define CAN_EXT_MAX_CANID               (0x1FFFFFFFUL)
#define CAN_EXT_CANID_FLAG              (0x80000000UL)

#endif/* CAN_GERERALTYPES_H */
