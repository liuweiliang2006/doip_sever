/*BEGIN_FILE_HDR
***********************************************************************************************
* NOTICE
* This software is the property of HiRain Technologies. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* HiRain Technologies.
***********************************************************************************************
* File Name:       NmStack_Types.h
***********************************************************************************************
* Project/Product: AUTOSAR CanNm programe 
* Title:           NmStack_Types
* Author:          Peng.Liu
***********************************************************************************************
* Description:     The type of CanNm Network State
* 
*
* (Requirements, pseudo code and etc.)
***********************************************************************************************
* Limitations:
*
* (limitations)
***********************************************************************************************
***********************************************************************************************
* Revision History£º
*
* Version		Date		  	  Initials			CR#			Descriptions
* -------   ----------    ----------    ------  -----------------    -----------------
* 1.0			  26/08/11	  	Peng.Liu			N/A			Original
* 
***********************************************************************************************
END_FILE_HDR*/

#ifndef NM_STACK_TYPES_H
#define NM_STACK_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"                                                                     /* Include standard types */
//#include "CanNm_Types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



/* Return values for NM functions */
//#define NM_E_OK                       ((uint8)E_OK)      /* Function call has been successfully accomplished and
//                                                            returned */
//#define NM_E_NOT_OK                   ((uint8)E_NOT_OK)  /* Function call has been unsuccessfully accomplished and
//                                                            returned because of an internal execution error.  */
//#define NM_E_NOT_EXECUTED             ((uint8)2u)        /* Function call has been successfully accomplished and
//                                                            returned since execution of a service in the current 
//                                                            state is not allowed. */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Return type for NM functions */
typedef uint8 Nm_ReturnType;

/* State of the CanNm state machine */
typedef enum
{
  NM_STATE_UNINIT                 = 0u,   /* Uninitialized State */
  NM_STATE_BUS_SLEEP              = 1u,   /* Bus-Sleep State */
  NM_STATE_PREPARE_BUS_SLEEP      = 2u,   /* Prepare Bus-Sleep State */
  NM_STATE_READY_SLEEP            = 3u,   /* Ready Sleep State */
  NM_STATE_NORMAL_OPERATION       = 4u,   /* Normal Operation State */
  NM_STATE_REPEAT_MESSAGE         = 5u,   /* Repeat Message State */
  NM_STATE_SYNCHRONIZE            = 6u,   /* Synchronized State */
  NM_STATE_WAIT_CHECK_ACTIVATION  = 7u,   /* Wait Check Activation */
  NM_STATE_WAIT_NETWORK_STARTUP   = 8u    /* Wait Network Startup */
} Nm_StateType;
 
/* Modes of the network management state machine */
typedef enum
{
  NM_MODE_BUS_SLEEP           = 0u,   /* Bus-Sleep Mode */
  NM_MODE_PREPARE_BUS_SLEEP   = 1u,   /* Prepare Bus-Sleep Mode */
  NM_MODE_SYNCHRONIZE         = 2u,   /* Synchronized Mode */
  NM_MODE_NETWORK             = 3u    /* Network Mode */
} Nm_ModeType;




/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* NM_STACK_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: NmStack_Types.h
 *********************************************************************************************************************/
/************   Organi, Version 3.9.0 Vector-Informatik GmbH  ****/