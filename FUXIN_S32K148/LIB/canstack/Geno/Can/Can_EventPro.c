/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_EventPro.c
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
*   ISR
*******************************************************************************/
#define CAN_START_SEC_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_PHYx_MB_ISR \ Can_Controller_Busoff_handler
*
* Description:   These functions are ISR for can event
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) CAN0_ORed_0_15_MB_IRQHandler(void)
{
    Can_Controller_MB_handler(0);
}
FUNC(void, CAN_CODE) CAN0_ORed_16_31_MB_IRQHandler(void)
{
    Can_Controller_MB_handler(0);
}
FUNC(void, CAN_CODE) CAN0_ORed_IRQHandler(void)
{
    Can_Controller_Busoff_handler(0);
}

#define CAN_STOP_SEC_CODE
#include "MemMap.h"

#define CAN_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
*   MainFunctions
*******************************************************************************/
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Write  CAN225
*
* Description:   This function performs the polling of TX confirmation
*                when CAN_TX_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_MainFunction_Write(void)
{
    /*CAN179 CAN031 CAN178*/
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_MAINFUNCTION_WRITE_APIID, CAN_E_UNINIT);
    }
    else
    {
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Read CAN226
*
* Description:   This function performs the polling of RX indications
*                when CAN_RX_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_MainFunction_Read(void)
{
    /*CAN181 CAN108 CAN180*/
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_MAINFUNCTION_READ_APIID, CAN_E_UNINIT);
    }
    else
    {
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_BusOff CAN227
*
* Description:   This function performs the polling of  bus-off events
*                when CAN_BUSOFF_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_MainFunction_BusOff(void)
{
    /*CAN184 CAN109 CAN183 */
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_MAINFUNCTION_BUSOFF_APIID, CAN_E_UNINIT);
    }
    else
    {
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Wakeup CAN228
*
* Description:   This function performs the polling of  Wakeup events
*                when CAN_WAKEUP_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_MainFunction_Wakeup(void)
{
    /*CAN186 CAN112 CAN185 */
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_MAINFUNCTION_WAKEUP_APIID, CAN_E_UNINIT);
    }
    else
    {
    }
}
#define CAN_STOP_SEC_CODE
#include "MemMap.h"

