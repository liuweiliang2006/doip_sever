/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Interface module head File
*   Author          : HeYang
********************************************************************************
*   Description     : The header file CanIf.h contains the declaration of the 
*                     Can Interface module API;contains 'extern' declarations of
*                     constants,global data, type definitions and services that 
*                     are specified in the Can Interface module SWS.                     
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
*   01.00.00    02/04/2011    HeYang        N/A          Original
*   01.01.00    20/04/2011    HeYang        N/A          the parameter of memset
*   01.02.00    18/05/2011    HeYang        N/A          add the marco 
                                                         CANIF_CANCONTROLLER_TX
*                                                        CANIF_CANCONTROLLER_RX
                                                         CANCONTROLLER_RANGE_RX
*   01.03.00    28/05/2011    HeYang        N/A          modify CanIf_SetPduMode
                                                         
*   01.04.00    15/06/2011    HeYang        N/A          DPN_CANIF_110615_01 
*                                                        
*                                                        
*                                                        
*   02.00.00    06/06/2012    HeYang        N/A          DPN_CANIF_120606_01
*   02.01.00    05/07/2012    HeYang        N/A          DPN_CANIF_120705_01
*   02.02.00    08/07/2013    NingChen      N/A          DPN_CANIF_130708_01
*   02.02.01    16/07/2013    NingChen      N/A          DPN_CANIF_130716_01
*   02.02.02    29/07/2013    NingChen      N/A          DPN_CANIF_130729_01
*   02.02.03    05/08/2013    NingChen      N/A          DPN_CANIF_130805_01
*   02.02.04    15/08/2013    NingChen      N/A          D10_CANIF_130815_01
*   02.02.05    17/09/2013    NingChen      N/A          D10_CANIF_130917_01
*   02.03.00    08/01/2014    NingChen      N/A          D10_CANIF_140108_01
*   02.03.01    17/03/2014    RongjiLuo     N/A          D10_CANIF_140317_01
*   02.03.02    15/09/2015    NingChen      N/A          D10_CANIF_150915_01
*   02.03.03    01/08/2016    NingChen      N/A          D10_CANIF_160801_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _CANIF_H_
#define _CANIF_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "CanIf_Cfg.h"
#include "CanIf_Type.h" 

/*******************************************************************************
*   Macro 
*******************************************************************************/
#define CANIF_MSK_EXT_ID_MSB                    (0x10000000UL)
#define CANIF_ENTER_CRITICAL_SECTION()          Can_DisableGlobalInterrupts()
#define CANIF_LEAVE_CRITICAL_SECTION()          Can_EnableGlobalInterrupts() 
#define CANIF_MAX_CANID                         (0x1fffffffUL)

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    #define CANIF_RX_BUFFER_SDU_LENGTH_INITIAL      (0xffU)
#endif

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
    #if(CAN_USED_HOH_NUM > 255)
    #define  CANIF_LAST_HOH_PDUID       ((PduIdType)0xFFFFU)
    #else
    #define  CANIF_LAST_HOH_PDUID       ((PduIdType)0xFFU)
    #endif
#endif


/* Development Error */

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    /*API service called with invalid parameter*/
    #define CANIF_E_PARAM_CANID                       (0x10u) 
    #define CANIF_E_PARAM_DLC                         (0x11u)
    #define CANIF_E_PARAM_HRH                         (0x12u)
    #define CANIF_E_PARAM_LPDU                        (0x13u)
    #define CANIF_E_PARAM_CONTROLLER                  (0x14u)
    #define CANIF_E_PARAM_CONTROLLERID                (0x15u)
    #define CANIF_E_PARAM_WAKEUPSOURCE                (0x16u)
    #define CANIF_E_PARAM_TRCV                        (0x17u)
    #define CANIF_E_PARAM_TRCVMODE                    (0x18u)
    #define CANIF_E_PARAM_TRCVWAKEUPMODE              (0x19u)
    #define CANIF_E_PARAM_POINTER                     (0x20u)
    
    /*API service used without module initialization*/
    #define CANIF_E_UNINIT                            (0x30u)
    /*Requested API operation is not supported*/
    #define CANIF_E_NOK_NOSUPPORT                     (0x40u) 
    /*Transmit PDU ID invalid*/
    #define CANIF_E_INVALID_TXPDUID                   (0x50u)
    /*Receive PDU ID invalid*/
    #define CANIF_E_INVALID_RXPDUID                   (0x60u) 
        
    #define CANIF_SETCONTROLLERMODE_APIID             (0x03u)
    #define CANIF_GETCONTROLLERMODE_APIID             (0x04u)
    #define CANIF_TRANSMIT_APIID                      (0x05u)
    #define CANIF_READRXPDUDATA_APIID                 (0x06u)
    #define CANIF_READTXNOTIFSTATUS_APIID             (0x07u)
    #define CANIF_READRXNOTIFSTATUS_APIID             (0x08u)
    #define CANIF_SETPDUMODE_APIID                    (0x09u)
    #define CANIF_GETPDUMODE_APIID                    (0x0au)
    #define CANIF_GETVERSIONINFO                      (0x0bu)
    #define CANIF_SETDYNAMICTXID_APIID                (0x0cu)
    #define CANIF_TXCONFIRMATION_APIID                (0x13u)
    #define CANIF_RXINDICATION_APIID                  (0x14u)
    #define CANIF_CANCELTXCONFIRMATION_APIID          (0x15u)
    #define CANIF_CONTROLLERBUSOFF_APIID              (0x16u)
    #define CANIF_CONTROLLERMODEINDICATION_APIID      (0x17u)
#endif

/* Production Error */
#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
    #define CANIF_RX_INDICATION_ENABLE_MASK   ((uint8)0x01U)
    #define CANIF_RX_INDICATION_DISABLE_MASK  ((uint8)0xfeU)
    #define CANIF_TX_REQUEST_ENABLE_MASK      ((uint8)0x02U)
    #define CANIF_TX_REQUEST_DISABLE_MASK     ((uint8)0xfdU)
    #define CANIF_TX_NOTIFY_ENABLE_MASK       ((uint8)0x04U)
    #define CANIF_TX_NOTIFY_DISABLE_MASK      ((uint8)0xfbU)
    #define CANIF_PDU_GETMODE_MASK            ((uint8)0x07U)   
#endif
  
/*******************************************************************************
*   Typedef 
*******************************************************************************/
typedef enum
{
    CANIF_UNINITIALIZED = 0,
    CANIF_INITIALIZED = 1  
}CanIf_InitType;

typedef enum
{
    STATIC_TXPDU = 0,
    DYNAMIC_TXPDU = 1
}CanIf_TxPduType;

typedef enum 
{
    STANDARD_CAN = 0,
    EXTENDED_CAN = 1
}CanIf_PduCanIdType;

/* callback function pointer types */

typedef P2FUNC(void, TYPEDEF, User_RxIndication)
(
    PduIdType CanUserRxPduId, 
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);

typedef P2FUNC(void, TYPEDEF, Range_RxIndication)
(
    PduIdType CanUserRxPduId,
    Can_IdType CanId, 
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);

typedef P2FUNC(void, TYPEDEF, User_TxConfirmation)
(
    PduIdType CanUserTxPduId 
);

/* config pdu structs types */
typedef struct  
{
    #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
    PduIdType               UpperLayerHandle; /*Remap the PduId for UpperLayer*/
    #endif
    Can_IdType              CanId;                 /* Can_IdType 16 or 32 bit */
    CanIf_PduCanIdType      CanIdType;               /* CANIF_TXPDU_CANIDTYPE */
    Can_HwHandleType        Hth;                  /* Hardware transmit handle */
    uint8                   Length;               /* DLC                      */
    User_TxConfirmation     TxConfirmation;       /* Confirmation function    */
    #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    CanIf_TxPduType         TxPduType;     /* CanIfTxPduType DYNAMIC or STATIC*/
    #endif
    #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    /*Enables and disables transmit confirmation for each transmit CAN L-PDU for 
    reading its notification status. True: Enabled False: Disabled*/
    boolean                 TxPduReadNotifyStatus;   
    #endif
    
    #if((CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE) \
    &&(STD_ON == CANIF_PUBLIC_TX_BUFFERING))
    PduIdType                     HthNextTxPduID;          
    #endif
    
} CanIf_TxPduConfigType;

typedef struct
{
    /* Lower CAN Identifier of a receive CAN L-PDU for identifier range 
    definition, in which all CAN Ids are mapped to one PduId. */
    Can_IdType                      RxPduCanIdRangeLowerCanId ; 
    /* Upper CAN Identifier of a receive CAN L-PDU for identifier range 
    definition, in which all CAN Ids are mapped to one PduId.  */
    Can_IdType                      RxPduCanIdRangeUpperCanId;   
    
    Range_RxIndication              RangeRxIndication;
}CanIf_RxPduCanIdRangeType;


typedef struct  
{
    #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
    PduIdType                     UpperLayerHandle;
    #endif
    Can_IdType                    CanId;          /* Can_IdType 16 or 32 bit  */
    CanIf_PduCanIdType            CanIdType;      /* CANIF_RXPDU_CANIDTYPE    */
    Can_HwHandleType              Hrh;            /* Hardware transmit handle */
    uint8                         Length;         /* DLC                      */
    
    User_RxIndication             RxIndication;   /* Indication function      */
    
    #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    /*Enables and disables receive indication for each receive CAN L-PDU for 
    reading its notification status. True: Enabled False: Disabled*/
    boolean                       RxPduReadNotifyStatus;  
    #endif 
    
    #if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    /*Enables and disables the Rx buffering for reading of received L-PDU data. 
    True: Enabled False: Disabled*/
    boolean                       RxPduReadData;
    #endif
    
    #if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
    P2CONST(CanIf_RxPduCanIdRangeType, TYPEDEF, CANIF_CONFIG_CONST) 
                                                             RxPduCanIdRangeCfg;
    #endif
    
    #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
    PduIdType                     HrhNextRxPduID;          
    #endif
} CanIf_RxPduConfigType;
    
typedef struct
{
    /*Lower CAN Identifier of a receive CAN L-PDU for identifier range 
    definition, in which all CAN Ids shall pass the software filtering. */
    Can_IdType                      HrhRangeRxPduLowerCanId;
    /*Upper CAN Identifier of a receive CAN L-PDU for identifier range 
    definition, in which all CAN Ids shall pass the software filtering.*/
    Can_IdType                      HrhRangeRxPduUpperCanId;

    CanIf_PduCanIdType              HrhRangeRxPduRangeCanIdType; 
}CanIf_HrhRangeCfgType;

/*******************************************************************************
*   Global Data Define, No need to be configed
*******************************************************************************/
#define CANIF_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
* PRQA S 3684   MISRA-C:2004 Rule 8.12
* The following arrays are configurable parameters, they are declared without 
* any size to ensure that users can config these parameters even in lib code. 
* This part of code is verified manually and has no impact.
*******************************************************************************/
#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)

extern VAR(boolean, CANIF_PRIVATE_DATA) CanIfTxBufferPDUFillflag[];
extern VAR(uint8, CANIF_PRIVATE_DATA) CanIfTxBufferSdu[][CAN_DATA_DLC];
extern VAR(Can_PduType, CANIF_PRIVATE_DATA) CanIfTxBufferPdu[];
                                  
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
extern VAR(Can_IdType, CANIF_PRIVATE_DATA) CanIfTxPduCanIdForDynamic[];           
#endif 

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
extern VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA) CanIfTxNotifStatus[];      
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
extern VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA) CanIfRxNotifStatus[];      
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)

extern VAR(uint8, CANIF_PRIVATE_DATA) CanIfRxBufferSduData[][CAN_DATA_DLC]; 
extern VAR(PduLengthType, CANIF_PRIVATE_DATA) CanIfRxBufferSduLength[]; 
         
#endif

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

extern CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanRxPduIds ;
extern CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanTxPduIds ; 
extern CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfInitNumberofHrh ;  

/*******************************************************************************
*   Config Parameters   
*******************************************************************************/
#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
extern CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfHrhFirstRxPduID[];
extern CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfHthFirstTxPduID[];
#endif

#if(STD_ON == CANIF_HRH_RANGE_FILTER)
extern CONST(CanIf_HrhRangeCfgType, CANIF_CONFIG_CONST) CanIfHrhRangeCfg[];
#endif

extern CONST(CanIf_RxPduConfigType, CANIF_CONFIG_CONST) CanIfRxPduConfig[];
extern CONST(CanIf_TxPduConfigType, CANIF_CONFIG_CONST) CanIfTxPduConfig[]; 

#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
*   Global Function Declaration 
*******************************************************************************/
#define CANIF_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_Init(void);

extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetControllerMode
( 
    uint8 ControllerId, 
    CanIf_ControllerModeType ControllerMode 
);
extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_GetControllerMode
( 
    uint8 ControllerId, 
    P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) 
                                                               ControllerModePtr
);


extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_Transmit
( 
    PduIdType CanTxPduId, 
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);

#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_CancelTransmit
( 
    PduIdType CanTxPduId 
);
#endif

#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetPduMode
( 
    uint8 ControllerId,
    CanIf_PduSetModeType PduModeRequest
);

extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_GetPduMode
( 
    uint8 ControllerId,
    P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr
);
#endif                  

                               
#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API) 
extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetDynamicTxId
( 
    PduIdType CanTxPduId, 
    Can_IdType CanId 
);
#endif 




#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
extern FUNC(CanIf_NotifStatusType, CANIF_PUBLIC_CODE) CanIf_ReadTxNotifStatus
( 
    PduIdType CanTxPduId
); 
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API) 
extern FUNC(CanIf_NotifStatusType, CANIF_PUBLIC_CODE) CanIf_ReadRxNotifStatus
( 
    PduIdType CanRxPduId 
);   
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)   
extern FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_ReadRxPduData
( 
    PduIdType CanRxPduId, 
    P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);
#endif 

#if (STD_ON == CANIF_PUBLIC_VERSION_INFO_API)
extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_GetVersionInfo
( 
    P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA) VersionInfo
);
#endif
                          
extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ClearTransmitBuffer
( 
    uint8 ControllerId
);                     

#define CANIF_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif/* _CANIF_H_ */                          

