/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Cfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Can module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Can module configuration File
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
*   04.03.02    29/12/2020     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can.h"

/*******************************************************************************
*   Global Vars
*******************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_8
#include "MemMap.h"
VAR(boolean, CAN_VAR_NOINIT)    EmptyFlagForHth[7];
VAR(uint8, CAN_VAR_NOINIT) Can_CtrlIntCnt[1];
VAR(Can_StateTransitionType, CAN_VAR_NOINIT) Can_ModeMonitor[1];
VAR(Can_StateType, CAN_VAR)  Can_State[1];
#define CAN_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

#define CAN_START_SEC_VAR_NOINIT_8
#include "MemMap.h"
VAR(PduIdType, CAN_VAR_NOINIT) PduIdForHth[7];
#define CAN_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

#define CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
VAR(Can_OldIERType, CAN_VAR_NOINIT)  Can_CtrlIntReg[1];
#define CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
*   Config Parameters
*******************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_8
#include "MemMap.h"
CONST(uint8, CAN_CONST) CanControllerIDtoPhys[1] =
{
    0,
};
#define CAN_STOP_SEC_CONFIG_DATA_8
#include "MemMap.h"

#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
STATIC CONST(Can_ControllerBaudrateConfigType, CAN_CONST) Can_BDCfg[1] =
{
    {500, 0x7, 0x5a, 0x0}
};
CONST(Can_CtrlCfgType, CAN_CONST) Can_CtrlCfg[1] =
{
    {
        1, 0, &Can_BDCfg[0],
        0x1FFFFFFFUL, 0xFFFFFFFFUL, 0x80,
        0, 25, 25, 7,
        8, 0x10
    }
};
CONST(Can_HohCfgType, CAN_CONST) Can_HohCfg[32] =
{
    /* CanObjectId0*/
    {CAN_0, 0, 0x9C,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId1*/
    {CAN_0, 1, 0x100,0x0,FALSE, TRUE, 0x1fA7ffff},
    /* CanObjectId2*/
    {CAN_0, 2, 0x120,0x0,FALSE, TRUE, 0x1e7bffff},
    /* CanObjectId3*/
    {CAN_0, 3, 0x150,0x0,FALSE, TRUE, 0x1FCbffff},
    /* CanObjectId4*/
    {CAN_0, 4, 0x175,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId5*/
    {CAN_0, 5, 0x191,0x0,FALSE, TRUE, 0x1fE3ffff},
    /* CanObjectId6*/
    {CAN_0, 6, 0x210,0x0,FALSE, TRUE, 0x1fEBffff},
    /* CanObjectId7*/
    {CAN_0, 7, 0x221,0x0,FALSE, TRUE, 0x1fB3ffff},
    /* CanObjectId8*/
    {CAN_0, 8, 0x243,0x0,FALSE, TRUE, 0x1fEbffff},
    /* CanObjectId9*/
    {CAN_0, 9, 0x254,0x0,FALSE, TRUE, 0x1ff3ffff},
    /* CanObjectId10*/
    {CAN_0, 10, 0x260,0x0,FALSE, TRUE, 0x1C1Bffff},
    /* CanObjectId11*/
    {CAN_0, 11, 0x2A4,0x0,FALSE, TRUE, 0x1E1Fffff},
    /* CanObjectId12*/
    {CAN_0, 12, 0x306,0x0,FALSE, TRUE, 0x1f27ffff},
    /* CanObjectId13*/
    {CAN_0, 13, 0x387,0x0,FALSE, TRUE, 0x1ffFffff},
    /* CanObjectId14*/
    {CAN_0, 14, 0x351,0x0,FALSE, TRUE, 0x1fE3ffff},
    /* CanObjectId15*/
    {CAN_0, 15, 0x371,0x0,FALSE, TRUE, 0x1ff3ffff},
    /* CanObjectId16*/
    {CAN_0, 16, 0x380,0x0,FALSE, TRUE, 0x1f3Bffff},//0x1fE3ffff
    /* CanObjectId17*/
    {CAN_0, 17, 0x3F1,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId18*/
    {CAN_0, 18, 0x398,0x0,FALSE, TRUE, 0x1FFFffff},
    /* CanObjectId19*/
    {CAN_0, 19, 0x343,0x0,FALSE, TRUE, 0x1C3Bffff},
    /* CanObjectId20*/
    {CAN_0, 20, 0x500,0x0,FALSE, TRUE, 0x1E23ffff},
    /* CanObjectId21*/
    {CAN_0, 21, 0x400,0x0,FALSE, TRUE, 0x1e03ffff},
    /* CanObjectId22*/
    {CAN_0, 22, 0x40B,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId23*/
    {CAN_0, 23, 0x710,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId24*/
    {CAN_0, 24, 0x7df,0x0,FALSE, TRUE, 0x1fffffff},
    /* CanObjectId25*/
    {CAN_0, 25, 0x2A2,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId26*/
    {CAN_0, 26, 0x2DF,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId27*/
    {CAN_0, 27, 0x2FF,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId28*/
    {CAN_0, 28, 0x5D0,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId29*/
    {CAN_0, 29, 0x234,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId30*/
    {CAN_0, 30, 0x420,0x0,FALSE, FALSE, 0x7ff},
    /* CanObjectId31*/
    {CAN_0, 31, 0x718,0x0,FALSE, FALSE, 0x7ff}
};
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
