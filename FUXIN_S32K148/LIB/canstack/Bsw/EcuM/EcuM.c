/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : EcuM.c
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : The ECU state manager
*   Author          : mingqing.tang
********************************************************************************
*   Description     : Implementation of EcuM module.                        
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
*   01.00.00    21/09/2016    mingqing.tang   N/A          Original
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes 
*******************************************************************************/ 
#include "EcuM_Cbk.h"

#define Protected_Write(preg,pstatus,reg,value)   do{\
                                                       (preg)=0xA5u;\
                                                       (reg)=(value);\
                                                       (reg)=~(value);\
                                                       (reg)=(value);\
                                                       }while((pstatus)==1u)
void  Can_EnableWakeupSrcCallout(uint8 ControllerId)
{
}
void  Can_DisableWakeupSrcCallout(uint8 ControllerId)
{
}
void  EcuM_CheckWakeup(EcuM_WakeupSourceType src)
{
   //  APP_CanIf_SetControllerMode();
}


void EcuM_SetWakeupEvent(EcuM_WakeupSourceType src)
{

}

void Shift_Deepstop( void ) //p534
{
}


void SystemDeInit(void)
{
    /*--------- CanTrcv STB deinit --------------*/
    //SBC_CANSetMode(0x01);   
}

/*******************************************************************************
*  PUBLIC Functions define 
*******************************************************************************/
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: EcuM_EnableWakeupSources
*
* Description:   
*                procedure.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   The function will never return.(it calls StartOs) ECUM2811
********************************************************************************
END_FUNCTION_HDR*/
void EcuM_EnableWakeupSources()
{

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: EcuM_DisableWakeupSources
*
* Description:   
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   The function will never return.(it calls StartOs) ECUM2811
********************************************************************************
END_FUNCTION_HDR*/
void EcuM_DisableWakeupSources()
{

}

void EcuM_McuSetMode(uint8 mode)
{

} 

void EcuM_McuEnterSleep(void)
{
} 

void EcuM_McuEnterWakeup(void)   //P534
{
    
    
} 


