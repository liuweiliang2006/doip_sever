/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Type.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : CAN Driver module type definitions Header File
*   Author          : Hirain
********************************************************************************
*   Description     : The header file Can_Type.h contains the  common type
*                     definitions of Can Driver module
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
*   01.00.00    17/11/2016    SuyunYing     N/A          Original
********************************************************************************
* END_FILE_HDR*/

#ifndef CAN_TYPE_H
#define CAN_TYPE_H

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_Pl.h"

/*******************************************************************************
*   Typedef
*******************************************************************************/

typedef struct
{
    uint8       controllerRef;  /*logic controller*/
    uint8       phyMBIndex;     /*0-32/16*/
    Can_IdType  id;             /*CAN325_Conf*/
    uint8       FdPaddingValue;  /*CAN065_Conf*/
    boolean     isExtended;  /*CAN065_Conf*/
    boolean     isRx;           /*CAN327_Conf*/
    uint32      filterRef;      /*value of Rx Individual Mask Registers*/
} Can_HohCfgType;


/* CAN413 */
typedef struct
{
    Can_HwHandleType hohNum;
    Can_HwHandleType hthNum;
    Can_HwHandleType hrhNum;
    CONSTP2CONST(Can_CtrlCfgType, TYPEDEF, CAN_CONST) CtrlCfg;
    CONSTP2CONST(Can_HohCfgType, TYPEDEF, CAN_CONST) HohCfg;
} Can_ConfigType;

typedef enum
{
    CAN_UNINT   = 0,
    CAN_STOPPED = 1,
    CAN_STARTED = 2,
    CAN_SLEEP   = 3
} Can_StateType;

#endif/* CAN_TYPE_H*/

