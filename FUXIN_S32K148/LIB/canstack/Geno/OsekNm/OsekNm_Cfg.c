/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : OsekNm_Cfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : OsekNm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : OsekNm module configuration File
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
#include "OsekNm.h"

/*const configuaration array*/
#define  OSEKNM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include  "MemMap.h" /* PRQA S 5087 */
CONST(nmChannelConfigUnion,OSEKNM_CONFIG_CONST) nmChannelConfigAry[NM_NUMBER_OF_CHANNELS]  =
{
    (uint8)CN0_CONFIGURATION 
};/*Configuration for each channel*/
/*NM Channel  to Can(Logic can controller) */
CONST(uint8,OSEKNM_CONFIG_CONST) NmToLogCanChnAry[NM_NUMBER_OF_CHANNELS] = 
{
    0
};
/*Can (Logic can controller) to NM Channel */
CONST(uint8,OSEKNM_CONFIG_CONST) LogCanToNmChnAry[NM_CANIF_USED_CONTROLLER_NUM] = 
{
    0
};
/*NM TxPDUID in CanIfTxPduConfig*/
CONST(PduIdType,OSEKNM_CONFIG_CONST) nmTxPduIdAry[NM_NUMBER_OF_CHANNELS] = 
{
    16
};
/*the node ID for different channel.*/
CONST(nmNetIdType,OSEKNM_CONFIG_CONST) nmChannelNodeID[NM_NUMBER_OF_CHANNELS] = 
{
    0x20
};
/* NM Basic ID in the network */
CONST(uint32,OSEKNM_CONFIG_CONST)  nmPduBasicIDAry[NM_NUMBER_OF_CHANNELS] = 
{
    0x400
};
/* NM Message idbase mask*/
CONST(uint32,OSEKNM_CONFIG_CONST) nmPduBasicIDMaskAry[NM_NUMBER_OF_CHANNELS] = 
{
    0x780
};
/*NM Message source id mask*/
/*NmMessageCount - 1*/
CONST(uint32,OSEKNM_CONFIG_CONST) nmPduSouceIDMaskAry[NM_NUMBER_OF_CHANNELS] = 
{
    0x7F
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST)  nmCountTypAry[NM_NUMBER_OF_CHANNELS] = 
{
    100
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST)  nmCountMaxAry[NM_NUMBER_OF_CHANNELS] = 
{
    260
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST) nmCountErrAry[NM_NUMBER_OF_CHANNELS] = 
{
    1000
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST) nmCountWbsAry[NM_NUMBER_OF_CHANNELS] = 
{
    5000
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST) nmCountTxAry [NM_NUMBER_OF_CHANNELS] = 
{
    30
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST) 
    nmCountBusoffFastTimerAry[NM_NUMBER_OF_CHANNELS] = 
{
    200
};
CONST(nmTimerCntType,OSEKNM_CONFIG_CONST)  
    nmCountBusoffSlowTimerAry[NM_NUMBER_OF_CHANNELS] =
{
    1000
};
/*Fast Recover times*/
CONST(uint16,OSEKNM_CONFIG_CONST) 
    nmBusOffFastRecoveryAry[NM_NUMBER_OF_CHANNELS] =  
{
    255
};
/*Slow Recover times*/
CONST(uint16,OSEKNM_CONFIG_CONST) 
    nmBusOffSlowRecoveryAry[NM_NUMBER_OF_CHANNELS] =  
{
    255
};
CONST(nmRxTxCntType,OSEKNM_CONFIG_CONST) nmRxLimitAry[NM_NUMBER_OF_CHANNELS] = 
{
    4
};
CONST(nmRxTxCntType,OSEKNM_CONFIG_CONST) nmTxLimitAry[NM_NUMBER_OF_CHANNELS] = 
{
    8
};

#if(T_ACTIVE_MINI_ON == STD_ON)						
const nmTimerCntType nmCountActMinAry[NM_NUMBER_OF_CHANNELS] = {};/*Timer:ms*/
#endif
#if(T_LIMPHOME_MINI_ON == STD_ON)
const nmTimerCntType nmCountTLimpHAry[NM_NUMBER_OF_CHANNELS] = {};/*Timer:ms*/
#endif
#if(NM_ACK_CHECK == STD_ON)						
const nmTimerCntType nmCountTAckAry[NM_NUMBER_OF_CHANNELS] = {150};/*Timer:ms*/
const nmTimerCntType nmCountTAckRcyAry[NM_NUMBER_OF_CHANNELS] = {150};/*Timer:ms*/
#endif
#define  OSEKNM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include  "MemMap.h" /* PRQA S 5087 */
