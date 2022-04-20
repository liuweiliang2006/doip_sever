/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Cfg.h
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
#ifndef CAN_CFG_H
#define CAN_CFG_H
/*******************************************************************************
*   Common Macro
*******************************************************************************/
#define CAN_INTERRUPT  0
#define CAN_POLLING    1

/*******************************************************************************
*   CanGeneral
*******************************************************************************/
#define CAN_DEV_ERROR_DETECT                                STD_OFF
#define CAN_HW_TRANSMIT_CANCELLATION                        STD_OFF
#define CAN_IDENTICAL_ID_CANCELLATION                       STD_OFF
#define CAN_VERSION_INFO_API                                STD_OFF
#define CAN_MULTIPLEXED_TRANSMISSION                        STD_OFF
#define CAN_TIMEOUT_DURATION                                100
#define Can_EnableGlobalInterrupts           Can_EnableGlobalInterrupt
#define Can_DisableGlobalInterrupts          Can_DisableGlobalInterrupt

/*******************************************************************************
*   Non Standard
*******************************************************************************/
#define CAN_S32K_144                                        1

#define CAN_SUPPORT_MCU                                     CAN_S32K_144


#define CAN_CLK_SRC_OSC                                     STD_ON

#define CAN_WAKEUP_SUPPORT                                  STD_OFF
#define CAN_TXRX_POLLING_SUPPORT                            STD_OFF
#define CAN_TXRX_INTERRUPT_SUPPORT                          STD_ON
#define CAN_BUSOFF_POLLING_SUPPORT                          STD_OFF
#define CAN_BUSOFF_INTERRUPT_SUPPORT                        STD_ON
#define CAN_WAKEUP_POLLING_SUPPORT                          STD_OFF
#define CAN_WAKEUP_INTERRUPT_SUPPORT                        STD_OFF

/* CanCtrlHandle */
#define CAN_0                                               0

/*******************************************************************************
*   Access macro
*******************************************************************************/
#define CAN_TIMER_START()                                   timerCnt = 0
#define CAN_TIMER_LOOP()                                    timerCnt++
#define CAN_TIMER_CHECK()                                   Can_TimeOutCheck(timerCnt)
#define CAN_USED_CONTROLLER_NUM                             1
#define CAN_CONTROLLER_NUM                                  1
#define CAN_USED_HOH_NUM                                    32
#define CAN_USED_HTH_NUM                                    7
#define CAN_USED_HRH_NUM                                    25
#define CAN_USED_CTRL_INFO                                  Can_CtrlCfg
#define CAN_USED_HOH_INFO                                   Can_HohCfg
#endif/* CAN_CFG_H */
