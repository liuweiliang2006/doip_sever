/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_GeneralTypes_Cfg.h
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
#ifndef CAN_GERERALTYPES_CFG_H
#define CAN_GERERALTYPES_CFG_H
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "ComStack_Types.h"
/*******************************************************************************
*   Types
*******************************************************************************/
/*CAN429*/
typedef uint8 Can_HwHandleType;
#define CAN_INVALID_HOH     ((Can_HwHandleType)0xFFU)
/*CAN416*/
typedef uint16 Can_IdType;
#define CAN_CANID_MASK         ((Can_IdType)0x07FFU)
#define CAN_CANFD_INV_MASK     ((Can_IdType)0xBFFFU)
#define CAN_CANFD_MASK         ((Can_IdType)0x4000U)
#define CAN_IDTYPE_MASK        ((Can_IdType)0xC000U)
#endif/* CAN_GERERALTYPES_CFG_H */
