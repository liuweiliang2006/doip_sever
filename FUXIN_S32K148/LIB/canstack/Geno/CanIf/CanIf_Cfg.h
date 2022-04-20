/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanIf module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanIf module configuration File
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
#ifndef _CANIF_CFG_H_
#define _CANIF_CFG_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can.h"

/*******************************************************************************
*   Common Macro 
*******************************************************************************/

#define CANIF_FILTER_TYPE_INDEX        2
#define CANIF_FILTER_TYPE_LINEAR       3

/* CanIfDispatchCfg */ 
#define CANIF_DISPATCH_UL_CDD          0
#define CANIF_DISPATCH_UL_CAN_SM       1
#define CANIF_DISPATCH_UL_ECUM         2  
#define CANIF_DISPATCH_UL_OSEKNM       3  

/* CanIf Dlc Check Type*/
#define CANIF_DLC_CHECK_AUTOSAR        0
#define CANIF_DLC_CHECK_UNEQUAL        1
#define CANIF_DLC_CHECK_USER           2

/*******************************************************************************
*   CanIfPrivateCfg  
*******************************************************************************/
/*SWS Item        CANIF245_Conf :     
Container Name    CanIfPrivateCfg{CanInterfacePrivateConfiguration}   
Description       This container contains the private configuration 
                  (parameters) of the CAN Interface.*/

/*CANIF617_Conf   Selects whether the DLC check is supported. 
                  True: Enabled False: Disabled  */
#define CANIF_PRIVATE_DLC_CHECK             STD_OFF
#define CANIF_DLC_CHECK_TYPE                CANIF_DLC_CHECK_AUTOSAR
#define CANIF_DLC_CHECK_FAIL_INDICATION     STD_OFF

/*CANIF619_Conf   Selects the desired software filter mechanism for reception  
                  only.Each implemented software filtering method is identified 
                  by this enumeration number. 
                  Range: Types implemented software filtering methods*/
#define CANIF_PRIVATE_SOFTWARE_FILTER_TYPE             CANIF_FILTER_TYPE_INDEX

/*******************************************************************************
*    CanIfPublicCfg  
*******************************************************************************/
/*SWS Item        CANIF246_Conf :  
Container Name    CanIfPublicCfg{CanInterfacePublicConfiguration}  
Description       This container contains the public configuration (parameters) 
                  of the CAN Interface*/

/*CANIF614_Conf   Enables and disables the development error detection and 
                  notification mechanism. */
#define CANIF_PUBLIC_DEV_ERROR_DETECT             STD_OFF

/*CANIF618_Conf   Enables and disables the buffering of transmit L-PDUs 
                  (rejected by the CanDrv) within the CAN Interface module.*/
#define CANIF_PUBLIC_TX_BUFFERING                 STD_ON

/*CANIF522_Conf   Configuration parameter to enable/disable dummy API for upper 
                  layer modules which allows to request the cancellation of an 
                  I-PDU. */
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT      STD_OFF

/*CANIF610_Conf   Enables and disables the API for reconfiguration of the CAN 
                  Identifier for each Transmit L-PDU.*/
#define CANIF_PUBLIC_SETDYNAMICTXID_API           STD_OFF

/*CANIF607_Conf   Enables / Disables the API CanIf_ReadRxPduData() for reading 
                  received L-PDU data*/
#define CANIF_PUBLIC_READRXPDU_DATA_API           STD_OFF

/*CANIF608_Conf   Enables and disables the API for reading the receive 
                  indication status of any received L-PDU data.*/
#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API         STD_OFF

/*CANIF609_Conf   Enables and disables the API for reading the notification 
                  status of transmit L-PDUs*/
#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API         STD_OFF

/*CANIF613_Conf  Enables and disables the API for reading the version 
                  information about the CAN Interface*/
#define CANIF_PUBLIC_VERSION_INFO_API                    STD_OFF

/*******************************************************************************
*   CanIfInitCfg 
*******************************************************************************/

/*SWS Item        CANIF247_Conf :  
Container Name    CanIfInitCfg{CanInterfaceInitConfiguration}
                  [Multi Config Container] 
Description       This container contains the init parameters of the 
                  CAN Interface. At least one (if only on CanIf with one 
                  possible Configuration), but multiple (CanIf with different 
                  Configurations) instances of this container are possible.*/

#define CANIF_USED_CONTROLLER_NUM         CAN_CONTROLLER_NUM 

#define CANIF_UPPER_LAYER_HANDLE          STD_ON

#define CANIF_PDU_CHANNEL_MODE_CONTROL    STD_ON

#define CANIF_RX_PDU_RANGE_CANID          STD_ON

#define CANIF_HRH_RANGE_FILTER            STD_OFF

#define CANIF_VENDOR_ID_VALUE           ((uint16)26)
#define CANIF_MODULE_ID_VALUE           ((uint16)60)
#define CANIF_INSTANCE_ID_VALUE_0       ((uint8)0)
#define CANIF_SW_MAJOR_VERSION_VALUE    (2)
#define CANIF_SW_MINOR_VERSION_VALUE    (3)
#define CANIF_SW_PATCH_VERSION_VALUE    (0)


/*******************************************************************************
*   CanIfDispatchCfg 
*******************************************************************************/

/*SWS Item        CANIF250_Conf :  
Container Name    CanIfDispatchCfg{CanInterfaceDispatcherConfiguration}
Description       Callback functions provided by upper layer modules of the
                  CanIf. The callback functions defined in this container are 
                  common to all configured CAN Driver / CAN Transceiver 
                  Driver modules. */


/*add for OSEK NM*/
#define CANIF_SUPPORT_OSEK_NM          STD_OFF

/*CANIF547_Conf*/
/*This parameter defines the upper layer (UL) module to which the notifications 
of all ControllerBusOff events from the CAN Driver modules have to be routed via
<User_ControllerBusOff>. There is no possibility to configure no upper layer 
(UL) module as the provider of <User_ControllerBusOff>.*/
#define CANIF_DISPATCH_USERCTRLBUSOFF_UL         CANIF_DISPATCH_UL_OSEKNM 
/*CANIF548_Conf*/
#define CANIF_DISPATCH_USERSETWAKEUPEVENT_UL     CANIF_DISPATCH_UL_OSEKNM 

#define CANIF_DISPATCH_USERCTRLBUSOFF_DEFINED_NAME    //CanNm_BusOff(Controller)


#define CANIF_DISPATCH_USERSETWAKEUPEVENT_DEFINED_NAME //CanNm_WakeUp(Controller)

#endif /* _CANIF_CFG_H_ */ 
