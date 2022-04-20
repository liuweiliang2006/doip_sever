/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanTp_PBCfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : CanTp module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : CanTp module configuration File
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
#include "CanTp.h"
#include "CanTp_Cfg.h"
  
#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
  
/******************************************************************************* 
*   declaration 
*******************************************************************************/ 
/* struct to hold the complete CanTp-configuration */
STATIC CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST) CanTp_RxNsduCfgInfo[CANTP_NUM_RX_SDUS];
STATIC CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST) CanTp_TxNsduCfgInfo[CANTP_NUM_TX_SDUS];
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
STATIC CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST) CanTp_ChannelModeInfo[CANTP_CHANNELS];
#endif
  
CONST(CanTp_ConfigType,CANTP_CONFIG_CONST) CanTp_Cfg =
{   
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    CanTp_ChannelModeInfo /* Extended SDU indirection table */, 
#endif

    CanTp_RxNsduCfgInfo /* Pointer to RxNsdu-cfg-table */, 
    CanTp_TxNsduCfgInfo /* Pointer to TxNsdu-cfg-table */, 
};
  
/******************************************************************************* 
*   RxNsdu 
*******************************************************************************/ 
STATIC CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST) CanTp_RxNsduCfgInfo[CANTP_NUM_RX_SDUS] =
{
    /* NSDU ID 0:CANTP_RXNSDU_ID to PduR Diag_PHY_Req */
    {
        1,   /* Tp Channel Num */
        1,   /* CANTP_RXNPDU_ID; from  CanIf */ 
        17,   /* CANTP_TXFC_NPDU_ID; to CanIf */  
        70,   /* CANTP_NAR */ 
        70,   /* CANTP_NBR (N_Br+N_Ar) < 0.9*N_Bs */  
        150,   /* CANTP_NCR */  
        #if !defined(CANTP_RXSDU_RXPDU_PADDING_ENABLE)&&!defined(CANTP_RXSDU_RXPDU_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_RXSDU_RXPDU Padding */  
        #endif
        #if !defined(CANTP_RXSDU_TXFC_PADDING_ENABLE)&&!defined(CANTP_RXSDU_TXFC_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_RXSDU_TXFC Padding*/  
        #endif
        CANTP_PHYSICAL,   /* CANTP_TA_TYPE */  
        #if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        #endif
        8,   /* CANTP_BS */ 
        50,   /* CANTP_STMIN */
        10,   /* CANTP_WFTMAX */ 
        CANTP_UNUSED,   /* CANTP_RX_NAE */ 
        CANTP_UNUSED,   /* CANTP_RX_NSA */ 
        CANTP_UNUSED,   /* CANTP_RX_NTA */ 
    },
    /* NSDU ID 1:CANTP_RXNSDU_ID to PduR Diag_FUN_Req */
    {
        0,   /* Tp Channel Num */
        0,   /* CANTP_RXNPDU_ID; from  CanIf */ 
        CANTP_UNUSED,   /* CANTP_TXFC_NPDU_ID; to CanIf */  
        70,   /* CANTP_NAR */ 
        70,   /* CANTP_NBR (N_Br+N_Ar) < 0.9*N_Bs */  
        150,   /* CANTP_NCR */  
        #if !defined(CANTP_RXSDU_RXPDU_PADDING_ENABLE)&&!defined(CANTP_RXSDU_RXPDU_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_RXSDU_RXPDU Padding */  
        #endif
        #if !defined(CANTP_RXSDU_TXFC_PADDING_ENABLE)&&!defined(CANTP_RXSDU_TXFC_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_RXSDU_TXFC Padding*/  
        #endif
        CANTP_FUNCTIONAL,   /* CANTP_TA_TYPE */  
        #if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        #endif
        8,   /* CANTP_BS */ 
        20,   /* CANTP_STMIN */ 
        10,   /* CANTP_WFTMAX */ 
        CANTP_UNUSED,   /* CANTP_RX_NAE */ 
        CANTP_UNUSED,   /* CANTP_RX_NSA */ 
        CANTP_UNUSED,   /* CANTP_RX_NTA */ 
    }
};
  
/******************************************************************************* 
*   TxNsdu 
*******************************************************************************/ 
STATIC CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST) CanTp_TxNsduCfgInfo[CANTP_NUM_TX_SDUS] =
{
    /* NSDU ID 0:CANTP_TXNSDU_ID from PduR Diag_Resp*/
    {
        1,   /* Tp Channel Num */
        17,   /* CANTP_TXNPDU_ID; to CanIf */  
        1,   /* CANTP_RXFC_ID; from  CanIf */ 
        70,   /* CANTP_NAS */ 
        150,   /* CANTP_NBS */  
        70,   /* CANTP_NCS */  
        #if !defined(CANTP_TXSDU_TXPDU_PADDING_ENABLE)&&!defined(CANTP_TXSDU_TXPDU_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_TXSDU_TXPDU Padding */  
        #endif
        #if !defined(CANTP_TXSDU_RXFC_PADDING_ENABLE)&&!defined(CANTP_TXSDU_RXFC_PADDING_DISABLE)
        CANTP_ON,   /* CANTP_TXSDU_RXFC Padding */  
        #endif
        CANTP_PHYSICAL,   /* CANTP_TA_TYPE */  
        #if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
        CANTP_STANDARD,   /* CANTP_ADDRESSING_FORMAT */  
        #endif
        CANTP_UNUSED,   /* CANTP_TX_NAE */ 
        CANTP_UNUSED,   /* CANTP_TX_NSA */ 
        CANTP_UNUSED,   /* CANTP_TX_NTA */ 
    }
};
  
/******************************************************************************* 
*   CanTp Channel Mode  
*******************************************************************************/ 
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
STATIC CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST) CanTp_ChannelModeInfo[CANTP_CHANNELS] =
{
    {
        CANTP_MODE_HALF_DUPLEX
    },
    {
        CANTP_MODE_HALF_DUPLEX
    }
};

#endif
#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
