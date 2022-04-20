/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : MCU_Cfg.h
********************************************************************************
*   Project/Product : MPC56xx_MCU_DriverCBB
*   Title           : MCU Driver module config File
*   Author          : suyun.ying
********************************************************************************
*   Description     : Implementation of MCU Driver                        
*
********************************************************************************
*   Limitations     : only used for MPC5xxx 
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    2014/08/07    suyun.ying    N/A          Original
********************************************************************************
* END_FILE_HDR*/

#ifndef _MCU_CFG_H
#define _MCU_CFG_H
#include "Std_Types.h"

/* Bus Clock Source
MCU_IRC_16M: 16M internal RC oscillator
MCU_OSC_4M: 4M extern OSC oscillator
MCU_OSC_8M: 8M extern OSC oscillator
MCU_OSC_16M: 16M extern OSC oscillator
*/
#define MCU_CLK_SOURCE          MCU_OSC_8M

/*Bus Clock Frequence
MCU_BUS_20M: 20M
MCU_BUS_40M: 40M
MCU_BUS_50M: 50M
MCU_BUS_64M: 64M
*/
#define MCU_BUS_CLK             MCU_BUS_64M

/* FMPLL LOCK LOSS  
MCU_UNLOCK_RESET:FMPLL unlock enter into Reset Mode
MCU_UNLOCK_SAFE :FMPLL unlock enter into Safe Mode
MCU_UNLOCK_INT  :FMPLL unlock enter into Interrupt
*/
#define MCU_FMPLL_UNLOCK        MCU_UNLOCK_INT

/* FMPLL Frequency Monitor 
MCU_FREQ_NONE :Not Monitor FMPLL frequency error
MCU_FREQ_RESET:FMPLL frequency error enter into Reset Mode
MCU_FREQ_SAFE :FMPLL frequency error enter into Safe Mode
MCU_FREQ_INT  :FMPLL frequency error enter into Interrupt
*/      
#define MCU_FMPLL_REFR          MCU_FREQ_NONE

/* FMPLL High Frequency Reference 
High Frequency = HFREF / 4
Range: MCU_BUS_CLK*4 ~ 65535
*/
#define MCU_FMPLL_HFREFR        (84U) /* High Frequency = 21M */ 

/* FMPLL Low Frequency Reference 
Low Frequency = HFREF / 4
Range: 0 ~ MCU_BUS_CLK*4
*/
#define MCU_FMPLL_LFREFR        (76U) /* Low Frequency = 19M */

/* MCU SUPPORT RUN0 MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_RUN0_MODE           STD_ON

/* MCU SUPPORT RUN1 MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_RUN1_MODE           STD_ON

/* MCU SUPPORT RUN2 MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_RUN2_MODE           STD_ON

/* MCU SUPPORT RUN3 MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_RUN3_MODE           STD_ON


/* MCU SUPPORT DRUN MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_DRUN_MODE       STD_ON

/* MCU SUPPORT RESET MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_RESET_MODE      STD_ON

/* MCU SUPPORT STANDBY MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_STANDBY_MODE    STD_ON

/* MCU SUPPORT SAFE MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_SAFE_MODE       STD_ON

/* MCU SUPPORT STOP MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_STOP_MODE       STD_ON

/* MCU SUPPORT HLAT MODE
STD_ON : support
STD_OFF: not support
*/
#define MCU_HALT_MODE       STD_ON

#endif 
