/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_PBcfg.c
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
#ifndef CAN_PBCFG_H
#define CAN_PBCFG_H
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_Type.h"

/*******************************************************************************
*   Global Vars
*******************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_8
#include "MemMap.h"
extern VAR(boolean, CAN_VAR_NOINIT)    EmptyFlagForHth[7];
extern VAR(uint8, CAN_VAR_NOINIT) Can_CtrlIntCnt[1];
extern VAR(Can_StateTransitionType, CAN_VAR_NOINIT) Can_ModeMonitor[1];
extern VAR(Can_StateType, CAN_VAR)  Can_State[1];
#define CAN_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

#define CAN_START_SEC_VAR_NOINIT_8
#include "MemMap.h"
extern VAR(PduIdType, CAN_VAR_NOINIT) PduIdForHth[7];
#define CAN_STOP_SEC_VAR_NOINIT_8
#include "MemMap.h"

#define CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Can_OldIERType, CAN_VAR_NOINIT)  Can_CtrlIntReg[1];
#define CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
*   ISR declare
*******************************************************************************/
#define CAN_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, CAN_CODE) CAN_PHY0_MB_ISR(void);
extern FUNC(void, CAN_CODE) CAN_PHY0_Busoff_ISR(void);

#define CAN_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
*   Config Parameters
*******************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_8
#include "MemMap.h"
extern CONST(uint8, CAN_CONST) CanControllerIDtoPhys[1];
#define CAN_STOP_SEC_CONFIG_DATA_8
#include "MemMap.h"


#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
extern CONST(Can_CtrlCfgType, CAN_CONST) Can_CtrlCfg[1];
extern CONST(Can_HohCfgType, CAN_CONST) Can_HohCfg[32];
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
#endif/* CAN_PBCFG_H */
