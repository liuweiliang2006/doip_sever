/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : EcuM_Cbk.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : The ECU state manager
*   Author          : mingqing.tang
********************************************************************************
*   Description     : The header file EcuM.h contains the declaration of the 
*                     EcuM module API, 'extern' declarations of constants,
*                     global data,type definitions and services that are 
*                     specified in the EcuM module SWS.
*                                            
********************************************************************************
*   Limitations     : only used for AUTOSAR 4.2 version
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials        CR#          Descriptions
*   ---------   ----------    -------------   ----------   ---------------
*   01.00.00    21/09/2017    Suyun.Ying   N/A          Original
********************************************************************************
* END_FILE_HDR*/
#ifndef _ECUM_CBK_H_
#define _ECUM_CBK_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
*  Register definitions
*******************************************************************************/ 
typedef uint32 EcuM_WakeupSourceType;

extern void EcuM_McuEnterSleep(void);
extern void EcuM_McuEnterWakeup(void);
extern  void  Can_EnableWakeupSrcCallout(uint8 ControllerId);
extern  void  Can_DisableWakeupSrcCallout(uint8 ControllerId);
extern void EcuM_SetWakeupEvent(EcuM_WakeupSourceType src);
extern void  EcuM_CheckWakeup(EcuM_WakeupSourceType src);

#endif /* _ECUM_H_ */

