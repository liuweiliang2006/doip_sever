/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Lcfg.c
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

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanIf.h" 
#include "CanTp_Cbk.h" 
#include "OsekNm_Cbk.h"
#include "CanNm_Cbk.h"
#include "Com_Cbk.h" 

/*******************************************************************************
*   Macro
*******************************************************************************/

#define CANIF_CFG_TOTAL_TXPDUID             (18)  
#define CANIF_CFG_TOTAL_RXPDUID             (66)  

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID) 
    #define CANIF_CFG_RANGE_CANID_RXPDUID   (1)
#endif
#define CANIF_CFG_TOTAL_HRH                 (25)  

/*******************************************************************************
*   Global Data Define, No need to be configed 
*******************************************************************************/
#define CANIF_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    VAR(boolean, CANIF_PRIVATE_DATA) 
                              CanIfTxBufferPDUFillflag[CANIF_CFG_TOTAL_TXPDUID];

    VAR(uint8, CANIF_PRIVATE_DATA)
                        CanIfTxBufferSdu[CANIF_CFG_TOTAL_TXPDUID][CAN_DATA_DLC];

    VAR(Can_PduType, CANIF_PRIVATE_DATA) 
                                      CanIfTxBufferPdu[CANIF_CFG_TOTAL_TXPDUID];
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    VAR(Can_IdType, CANIF_PRIVATE_DATA) 
                             CanIfTxPduCanIdForDynamic[CANIF_CFG_TOTAL_TXPDUID]; 
#endif 

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfTxNotifStatus[CANIF_CFG_TOTAL_TXPDUID];
#endif 

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API) 
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfRxNotifStatus[CANIF_CFG_TOTAL_RXPDUID];
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    VAR(uint8, CANIF_PRIVATE_DATA) 
                    CanIfRxBufferSduData[CANIF_CFG_TOTAL_RXPDUID][CAN_DATA_DLC];
    VAR(PduLengthType, CANIF_PRIVATE_DATA) 
                                CanIfRxBufferSduLength[CANIF_CFG_TOTAL_RXPDUID];
#endif

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanRxPduIds 
                                                      = CANIF_CFG_TOTAL_RXPDUID;
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanTxPduIds 
                                                      = CANIF_CFG_TOTAL_TXPDUID;
CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfInitNumberofHrh 
                                                          = CANIF_CFG_TOTAL_HRH;

/*******************************************************************************
*   Config Parameters   
*******************************************************************************/

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
CONST(CanIf_RxPduCanIdRangeType, CANIF_CONFIG_CONST) 
	                     CanIfRxPduCanIdRangeConfig[CANIF_CFG_RANGE_CANID_RXPDUID] = 
{
    {
        0x400U,
        0x47fU,
        CanNm_RxIndication
    },
}; 
#endif 

CONST(CanIf_RxPduConfigType, CANIF_CONFIG_CONST) 
	                     CanIfRxPduConfig[CANIF_CFG_TOTAL_RXPDUID] = 
{
    /* 0 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x9cU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        0, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 1 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x100U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        1, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        2, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 2 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        2,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x102U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        1, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        3, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 3 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        3,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x116U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        1, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 4 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        4,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x120U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        2, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        5, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 5 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        5,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x121U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        2, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        6, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 6 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        6,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x141U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        2, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 7 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        7,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x150U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        3, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        8, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 8 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        8,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x154U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        3, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        9, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 9 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        9,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x155U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        3, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        10, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 10 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        10,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x159U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        3, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 11 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        11,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x175U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        4, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 12 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        12,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x191U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        5, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        13, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 13 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        13,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x193U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        5, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        14, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 14 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        14,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x194U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        5, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        15, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 15 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        15,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x195U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        5, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        16, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 16 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        16,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x196U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        5, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 17 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        17,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x210U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        6, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        18, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 18 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        18,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x211U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        6, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        19, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 19 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        19,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x214U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        6, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 20 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        20,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x221U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        7, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        21, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 21 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        21,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x222U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        7, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        22, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 22 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        22,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x232U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        7, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 23 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        23,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x243U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        8, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        24, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 24 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        24,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x246U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        8, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        25, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 25 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        25,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x247U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        8, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 26 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        26,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x254U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        9, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        27, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 27 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        27,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x257U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        9, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 28 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        28,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x260U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        10, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        29, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 29 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        29,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x271U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        10, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        30, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 30 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        30,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x299U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        10, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 31 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        31,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x2A4U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        11, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        32, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 32 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        32,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x2DCU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        11, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 33 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        33,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x306U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        12, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        34, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 34 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        34,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x310U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        12, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        35, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 35 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        35,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x330U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        12, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 36 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        36,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x387U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        13, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 37 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        37,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x351U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        14, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        38, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 38 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        38,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x352U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        14, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        39, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 39 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        39,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x353U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        14, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        40, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 40 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        40,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x354U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        14, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        41, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 41 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        41,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x355U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        14, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 42 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        42,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x371U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        15, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        43, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 43 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        43,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x372U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        15, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        44, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 44 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        44,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x373U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        15, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 45 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        45,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x380U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        16, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        46, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 46 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        46,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x3B1U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        16, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		47, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 47 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        47,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x3A0U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        16, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		48, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 48 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        48,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x390U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        16, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 49 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        49,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x3F1U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        17, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 50 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        50,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
		0x398U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        18, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 51 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        51,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x343U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        19, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		52, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 52 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        52,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x3B2U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        19, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
		CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 53 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        53,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x500U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        20, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        54, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 54 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        54,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x502U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        20, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        55, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 55 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        55,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x525U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        20, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        56, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 56 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        56,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x555U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        20, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 57 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        57,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x40BU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */
        5, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        58, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 58 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        58,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x412U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        59, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 59 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        59,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x414U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        60, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 60 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        60,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x415U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        61, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 61 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        61,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x418U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        62, /* CanIfRxPduNextHrh */
        #endif 
    },
    /* 62 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        62,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x565U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        22, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        Com_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 63 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x7dfU, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        24, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        CanTp_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 64 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x710U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        23, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        CanTp_RxIndication, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        NULL_PTR, /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
    /* 65 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfRxPduUpperLayerHandle */ 
        #endif 
        
        0x400U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        21, /* CanIfRxPduHrhIdRef */ 
        8, /* CanIfRxPduDlc */ 
        NULL_PTR, /* CanIfRxPduUserRxIndicationName */ 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfRxPduReadNotifyStatus */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)  
        FALSE, /* CanIfRxPduReadData */ 
        #endif 
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)  
        &CanIfRxPduCanIdRangeConfig[0], /* CanIfRxPduRangePtr */ 
        #endif 
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)  
        CANIF_LAST_HOH_PDUID, /* CanIfRxPduNextHrh */ 
        #endif 
    },
}; 

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
CONST(Can_HwHandleType, CANIF_CONFIG_CONST)
                                     CanIfHrhFirstRxPduID[CANIF_CFG_TOTAL_HRH] = 
{ 
    0,
    1,
    4,
    7,
    11,
    12,
    17,
    20,
    23,
    26,
    28,
    31,
    33,
    36,
    37,
    42,
    45,
    49,
    50,
    51,
    53,
    65,
    57,
    64,
    63,
};

#if(STD_ON == CANIF_PUBLIC_TX_BUFFERING)
CONST(Can_HwHandleType, CANIF_CONFIG_CONST)
	                                     CanIfHthFirstTxPduID[7] =
{
    0,
    3,
    7,
    14,
    15,
    16,
    17,
};
#endif
#endif 

#if(STD_ON == CANIF_HRH_RANGE_FILTER)
CONST(CanIf_HrhRangeCfgType, CANIF_CONFIG_CONST)
                                         CanIfHrhRangeCfg[CANIF_CFG_TOTAL_HRH] =
{
    /* not supported */  
};
#endif 

CONST(CanIf_TxPduConfigType, CANIF_CONFIG_CONST)
	                     CanIfTxPduConfig[CANIF_CFG_TOTAL_TXPDUID] = 
{
    /* 0 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2A2U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        25, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        1   /* HthNextTxPduID */  
        #endif
    },
    /* 1 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2DDU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        25, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        2   /* HthNextTxPduID */  
        #endif
    },
    /* 2 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        2,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2DEU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        25, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 3 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        3,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2DFU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        26, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        4   /* HthNextTxPduID */  
        #endif
    },
    /* 4 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        4,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2E1U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        26, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        5   /* HthNextTxPduID */  
        #endif
    },
    /* 5 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        5,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2E2U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        26, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        6   /* HthNextTxPduID */  
        #endif
    },
    /* 6 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        6,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2FEU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        26, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 7 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        7,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x2FFU, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        8   /* HthNextTxPduID */  
        #endif
    },
    /* 8 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        8,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x3A2U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        9   /* HthNextTxPduID */  
        #endif
    },
    /* 9 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        9,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x3A3U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        10   /* HthNextTxPduID */  
        #endif
    },
    /* 10 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        10,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x3A4U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        11   /* HthNextTxPduID */  
        #endif
    },
    /* 11 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        11,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x3A5U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        12   /* HthNextTxPduID */  
        #endif
    },
    /* 12 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        12,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x3A7U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        13   /* HthNextTxPduID */  
        #endif
    },
    /* 13 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        13,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x556U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        27, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 14 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        14,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x5D0U, /* CanId*/
        STANDARD_CAN, /* CanIdType */ 
        28, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 15 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        15,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x234U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        29, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        Com_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 16 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x420U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        30, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        CanNm_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
    /* 17 */ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        17,    /* CanIfTxPduUpperLayerHandle */ 
        #endif 
        
        0x718U, /* CanId*/ 
        STANDARD_CAN, /* CanIdType */ 
        31, /* CanIfTxPduHthIdRef */ 
        8, /* CanIfTxPduDlc */ 
        CanTp_TxConfirmation, /* CanIfTxPduUserTxConfirmationUL */ 
        #if(STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)  
        STATIC_TXPDU, /* CanIfTxPduType */ 
        #endif 
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)  
        FALSE, /* CanIfTxPduReadData */ 
        #endif 
        #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
        &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
        CANIF_LAST_HOH_PDUID   /* HthNextTxPduID */  
        #endif
    },
}; 

#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
