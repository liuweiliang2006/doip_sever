/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanNm_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanNm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanNm module configuration File
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
*   04.03.02    24/09/2019     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#ifndef _CANNM_CFG_H_
#define _CANNM_CFG_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
/********************ECUC_CanNm_00001 CanNmGlobalConfig******************/
/*ECUC_CanNm_00040
CanNmBusLoadReductionEnabled*/
#define CANNM_BUS_LOAD_REDUCTION_ENABLED                    STD_OFF
/*ECUC_CanNm_00006
CanNmBusSynchronizationEnabled*/
#define CANNM_BUS_SYNCHRONIZATION_ENABLED                   STD_OFF
/*ECUC_CanNm_00013
CanNmComControlEnabled*/
#define CANNM_COM_CONTROL_ENABLED                           STD_OFF
/*ECUC_CanNm_00044
CanNmComUserDataSupport*/
#define CANNM_COM_USER_DATA_SUPPORT                         STD_OFF
/*ECUC_CanNm_00080
CanNmCoordinatorSyncSupport*/
#define CANNM_COORDINATOR_SYNC_SUPPORT                      STD_OFF
/*ECUC_CanNm_00002
CanNmDevErrorDetect*/
#define CANNM_DEV_ERROR_DETECT                              STD_OFF
/*ECUC_CanNm_00009
CanNmImmediateRestartEnabled*/
#define CANNM_IMMEDIATE_RESTART_ENABLED                     STD_OFF
/*ECUC_CanNm_00041
CanNmImmediateTxconfEnabled*/
#define CANNM_IMMEDIATE_TXCONF_ENABLED                      STD_OFF
/*ECUC_CanNm_00007
CanNmNodeDetectionEnabled*/
#define CANNM_NODE_DETECTION_ENABLED                        STD_ON
/*ECUC_CanNm_00083
CanNmNodeIdEnabled*/
#define CANNM_NODE_ID_ENABLED                               STD_ON
/*ECUC_CanNm_00010
CanNmPassiveModeEnabled*/
#define CANNM_PASSIVE_MODE_ENABLED                          STD_OFF
/*ECUC_CanNm_00011
CanNmPduRxIndicationEnabled*/
#define CANNM_PDU_RX_INDICATION_ENABLED                     STD_OFF
/*ECUC_CanNm_00055
CanNmRemoteSleepIndEnabled*/
#define CANNM_REMOTE_SLEEP_IND_ENABLED                      STD_OFF
/*ECUC_CanNm_00005
CanNmRepeatMsgIndEnabled*/
#define CANNM_REPEAT_MSG_IND_ENABLED                        STD_OFF
/*ECUC_CanNm_00012
CanNmStateChangeIndEnabled*/
#define CANNM_STATE_CHANGE_IND_ENABLED                      STD_ON
/*ECUC_CanNm_00004
CanNmUserDataEnabled*/
#define CANNM_USER_DATA_ENABLED                             STD_ON
/*ECUC_CanNm_00003
CanNmVersionInfoApi*/
#define CANNM_VERSION_INFO_API                              STD_OFF
/*ECUC_CanNm_00032
CanNmMainFunctionPeriod : ms*/
#define CANNM_MAIN_FUNCTION_PERIOD                          ((uint8)10u)
/*ECUC_CanNm_00059
CanNmPnResetTime*/
/*ECUC_CanNm_00072
CanNmPnEiraRxNSduRef*/

#define CANNM_CONFIG_VARIANTS                               STD_CONFIG_VARIANTS_PRECOMPILE

#define CANNM_PRIVATE_VERSION_CHECK                         STD_ON

#define CANNM_NUMBER_OF_CHANNELS                            ((uint8)1u)

#define CANNM_SW_MAJOR_VERSION_CFG                          1
#define CANNM_SW_MINOR_VERSION_CFG                          0
#define CANNM_SW_PATCH_VERSION_CFG                          0

#define CANNM_AR_RELEASE_MAJOR_VERSION_CFG                  4
#define CANNM_AR_RELEASE_MINOR_VERSION_CFG                  0
#define CANNM_AR_RELEASE_REVISION_VERSION_CFG               3

#endif

