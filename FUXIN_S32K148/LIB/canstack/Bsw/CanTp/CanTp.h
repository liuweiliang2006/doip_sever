/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module head File
*   Author          : HeYang
********************************************************************************
*   Description     : Main header file of the AUTOSAR CAN Transport Protocol, 
*                     according to AUTOSAR_SWS_CANTransportLayer.pdf(Release4.0)
*                     The header file contains the declaration of the Can module 
*                     API;contains 'extern' declarations of constants,global data,
*                     type definitions and services that are specified in the 
*                     CanTp module SWS.
*                                            
********************************************************************************
*   Limitations     : 
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    2010/05/24    qyMa          N/A          Original
*   02.00.00    2014/03/11    rui.guo       N/A          N/A   
*   02.00.01    2014/10/30    rui.guo       N/A          D10_CANTP_141030_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _CANTP_H_
#define _CANTP_H_

/**************************************************************************************************
* Include files
**************************************************************************************************/

#include "ComStack_Types.h"
#include "CanTp_Cfg.h"

#define CANTP_VENDOR_ID             (uint16)(0xFFFFU)  /*Supplier ID */
#define CANTP_MODULE_ID             (uint16)(0x0023U)  /*CanTp Moudle ID */
#define CANTP_INSTANCE_ID           0

/* CanTp Component release Version  */
#define CANTP_SW_MAJOR_VERSION      (uint8)(0x03u)
#define CANTP_SW_MINOR_VERSION      (uint8)(0x02u)
#define CANTP_SW_PATCH_VERSION      (uint8)(0x02u)
/* Autosar release version */
#define CANTP_AR_MAJOR_VERSION      (uint8)(0x04u)
#define CANTP_AR_MINOR_VERSION      (uint8)(0x00u)
#define CANTP_AR_PATCH_VERSION      (uint8)(0x03u)

/**************************************************************************************************
* Global defines
**************************************************************************************************/
#define CANTP_MODE_HALF_DUPLEX      ((uint8)0x00u)
#define CANTP_MODE_FULL_DUPLEX      ((uint8)0x01u)

#define CANTP_MAX_FRAME_LENGTH            8    /* CAN frame max length*/
#define CANTP_MAX_FRAME_LENGTH_UINT8      ((uint8)CANTP_MAX_FRAME_LENGTH)    /* CAN frame max length*/
#define CANTP_MAX_FRAME_LENGTH_UINT16     ((uint16)CANTP_MAX_FRAME_LENGTH)    /* CAN frame max length*/

#define CANTP_UNUSED                ((uint16)0xFFu)




/* --- Vendor and Module Identification ---------------------------------------------------------------------------- */
/*#define CANTP_VENDOR_ID                          (99u)*/
/*#define CANTP_MODULE_ID                          (0x23u)*/


/* --- AUTOSAR Software Specification Version Information ---------------------------------------------------------- */
#define CANTP_AR_RELEASE_MAJOR_VERSION          (4)
#define CANTP_AR_RELEASE_MINOR_VERSION          (0)
#define CANTP_AR_RELEASE_REVISION_VERSION       (3)


/* --- Component Version Information ------------------------------------------------------------------------------- */


#define CANTP_INSTANCE_ID_DET                   (0x00u)
/* --- API Service IDs --------------------------------------------------------------------------------------------- */
#define CANTP_SID_INIT                           (0x01u)
#define CANTP_SID_SHUTDOWN                       (0x02u)
#define CANTP_SID_TRANSMIT                       (0x03u)
#define CANTP_SID_RXINDICATION                   (0x42u)
#define CANTP_SID_TXCONFIRMATION                 (0x05u)
#define CANTP_SID_MAINFUNCTION                   (0x06u)
#define CANTP_SID_GETVERSIONINFO                 (0x07u)
#define CANTP_SID_CANCELTRANSMIT                 (0x08u)
#define CANTP_SID_CANCELRECEIVE                  (0x09u)
#define CANTP_SID_CHANGEPARAMETER                (0x0Au)
#define CANTP_SID_READPARAMETER                  (0x0Bu)
#define CANTP_SID_MAINFUNCTIONRX                 (0x20u)
#define CANTP_SID_MAINFUNCTIONTX                 (0x21u)

/* Vector-CanTp specific service-Ids */
#define CANTP_SID_RXGETBUFFER                    (0x30u)
#define CANTP_SID_TXGETBUFFER                    (0x31u)
#define CANTP_SID_RXTRANSMITFRAME                (0x32u)
#define CANTP_SID_TXTRANSMITFRAME                (0x33u)
#define CANTP_SID_RXINIT                         (0x34u)
#define CANTP_SID_TXINIT                         (0x35u)
#define CANTP_SID_STOPSEPARATIONTIME             (0x36u)

/*error code*/

#define CANTP_E_NO_ERROR            0
#define CANTP_E_INVALID_CHANNEL     0xFEU
#define CANTP_E_INVALID_ADDRESS     0xFDU

#define CANTP_E_PARAM_CONFIG        0x01U
#define CANTP_E_PARAM_ID            0x02U
#define CANTP_E_PARAM_POINTER       0x03U
#define CANTP_E_UNINIT              0x20U
#define CANTP_E_INVALID_TX_ID       0x30U 
#define CANTP_E_INVALID_RX_ID       0x40U 
#define CANTP_E_INVALID_TX_BUFFER   0x50U 
#define CANTP_E_INVALID_RX_BUFFER   0x60U 
#define CANTP_E_INVALID_TX_LENGTH   0x70U
#define CANTP_E_INVALID_RX_LENGTH   0x80U 
#define CANTP_E_INVALID_TATYPE      0x90U 
#define CANTP_E_OPER_NOT_SUPPORTED  0xA0U 
#define CANTP_E_COM                 0xB0U 
#define CANTP_E_RX_COM              0xC0U
#define CANTP_E_TX_COM              0xD0U 

#if !defined (CanTp_DetReportError)
# if (CANTP_DEV_ERROR_REPORT == STD_ON)
#  define CanTp_DetReportError(ApiId, ErrorId) ((void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID_DET, (ApiId), (ErrorId) )) /* PRQA S 3412 */ /* MD_CanTp_3412 */
# else
#  define CanTp_DetReportError(ApiId, ErrorId)
# endif
#endif

/**************************************************************************************************
* Global data types and structures
**************************************************************************************************/
/* AUTOSAR compliant */

typedef enum /* CanTpInternalState */
{
    CANTP_OFF = 0,
    CANTP_ON = 1
} CanTpInternalState;

typedef enum
{
    CANTP_RX_CHANNEL = 0,
    CANTP_TX_CHANNEL = 1
} CanTpChannelType;


typedef enum
{
    CANTP_STANDARD = 0,
    CANTP_EXTENDED = 1,
    CANTP_MIXED = 2
} CanTpAddressingFormat;

typedef enum
{
    CANTP_PHYSICAL = 0,
    CANTP_FUNCTIONAL = 1
} CanTpTaType;

typedef enum
{
    CANTP_BS_PARAMETER = 0,
    CANTP_STMIN_PARAMETER = 1
} CanTpParameterType;


/************************************************
* Types for static-configuration (ROM/Flash) 
************************************************/
/*************
* CanTp (ROM) 
*************/
typedef struct /*RxNsdu (ROM)*/ 
{ 
    PduIdType      CanTpChannelId;
    PduIdType      CanTpRxNPduId;    /* from CanIf */
    PduIdType      CanTpTxFcNPduId;  /* to   CanIf */
    /*uint16         CanTpRxDl;*/ /*NO used any more*/
    uint16         CanTpNar;
    uint16         CanTpNbr;
    uint16         CanTpNcr;  
    #if !defined(CANTP_RXSDU_RXPDU_PADDING_ENABLE)&&!defined(CANTP_RXSDU_RXPDU_PADDING_DISABLE)
    uint8          CanTpRxPaddingActive;
    #endif
    #if !defined(CANTP_RXSDU_TXFC_PADDING_ENABLE)&&!defined(CANTP_RXSDU_TXFC_PADDING_DISABLE)
    uint8          CanTpTxFcPaddingActive;
    #endif
    CanTpTaType          CanTpRxTaType;
    #if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
    CanTpAddressingFormat          CanTpRxAddrFormat;
    #endif
    uint8          CanTpBs;
    uint8          CanTpSTmin;
    uint8          CanTpRxWftMax;
    uint8          CanTpRxNAe;
    uint8          CanTpRxNSa;
    uint8          CanTpRxNTa;
} CanTp_RxNsduCfgType;

typedef struct /*TxNsdu (ROM)*/
{ 
    PduIdType      CanTpChannelId;
    PduIdType      CanTpTxNPduId;    /* to   CanIf */
    PduIdType      CanTpRxFcNPduId;  /* from CanIf */
    /*uint16         CanTpTxDl;*/
    uint16         CanTpNas;
    uint16         CanTpNbs;
    uint16         CanTpNcs;
    #if !defined(CANTP_TXSDU_TXPDU_PADDING_ENABLE)&&!defined(CANTP_TXSDU_TXPDU_PADDING_DISABLE)
    uint8          CanTpTxPaddingActive;
    #endif
    #if !defined(CANTP_TXSDU_RXFC_PADDING_ENABLE)&&!defined(CANTP_TXSDU_RXFC_PADDING_DISABLE)
    uint8          CanTpRxFcPaddingActive;
    #endif
    CanTpTaType          CanTpTxTaType;
    #if !defined(CANTP_ADDRESSING_STANDARD_ONLY)&&!defined(CANTP_ADDRESSING_EXTENDED_ONLY)&&!defined(CANTP_ADDRESSING_MIX_ONLY)
    CanTpAddressingFormat          CanTpTxAddrFormat;
    #endif
    uint8          CanTpTxNAe;
    uint8          CanTpTxNSa;
    uint8          CanTpTxNTa;
} CanTp_TxNsduCfgType;



typedef struct
{
    uint8  CanTpChannelMode;
}CanTp_ChannelModeType;

/* *********************************************** */
/* CanTp Overall (ROM)                             */
/* *********************************************** */
typedef struct /* Struct to hold the complete CanTp-configuration */
{ 
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    CONSTP2CONST(CanTp_ChannelModeType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_ChannelMode;
#endif
    CONSTP2CONST(CanTp_RxNsduCfgType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_RxNsduCfg;
    CONSTP2CONST(CanTp_TxNsduCfgType,CANTP_CONFIG_CONST,TYPEDEF) CanTp_TxNsduCfg;
} CanTp_ConfigType;

/*******************************************************************************
*   Internal data types and structures define
*******************************************************************************/

/* *************** */
/* Rx-status (RAM) */
/* *************** */
typedef struct 
{
    PduInfoType   RxNPduInfo;
    PduIdType     CurrentRxSduId; 
    /*PduLengthType DataIndex;*/  
    PduLengthType DataLength;
    /*PduLengthType FrameIndex;*/
    PduLengthType MinBuffSize;
    PduLengthType AvailableBufLength;
    uint16        Timer;
    uint8         ChannelState;/* activation status */ 
    uint8         WFTCounter;
    uint8         BlockSizeCounter;  /* actual values */
    uint8         BlockSize;
    uint8         STMin; 
    uint8         FlowStatus;
    uint8         ExpectedSN;
    uint8         ChannelLastState;  
    uint8         RxErrorType; 
    uint8         RxFormatOffset;
    uint8*        RxBufPtr;
    uint8*        TxFCPtr;
    uint8         RxData[CANTP_MAX_FRAME_LENGTH];
    uint8         FCData[CANTP_MAX_FRAME_LENGTH];
    
}CanTp_RxStateType;

/* *************** */
/* Tx-status (RAM) */
/* *************** */
typedef struct 
{
    PduInfoType   TxNPduInfo;
    PduIdType     CurrentTxSduId;
    /*PduLengthType DataIndex;*/
    PduLengthType DataLength;
    /*PduLengthType FrameIndex;*/
    PduLengthType RemainTxDataCnt;
    uint16        Timer;
    /*uint8         PaddingLength;*/
    /*uint8         CurrentTxFormatOffset;*/
    uint8         ChannelState;
    uint8         BlockSizeCounter;
    uint8         STMin;
    uint8         SeqNumber;
    /*uint8         TxErrorType; TBD */
    uint8         TxFormatOffset;
    uint8         TxData[CANTP_MAX_FRAME_LENGTH];
}CanTp_TxStateType;

/* *********************************************** */
/* External administration data (RAM)              */
/* *********************************************** */
typedef struct 
{
    P2CONST(CanTp_RxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pRxNsduCfg;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   pTxNsduCfg;
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    P2CONST(CanTp_ChannelModeType,AUTOMATIC,CANTP_PRIVATE_CONST) pChnModeCfg;
#endif
    P2VAR(CanTp_RxStateType,AUTOMATIC,AUTOMATIC)                 pRxState;
    P2VAR(CanTp_TxStateType,AUTOMATIC,AUTOMATIC)                 pTxState;
    CanTpInternalState InternalState; /* keep track of the initialization status */
} CanTp_AdminDataType;


typedef struct 
{
    P2CONST(CanTp_RxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   _pRxSduCfg;
    P2CONST(CanTp_TxNsduCfgType,AUTOMATIC,CANTP_PRIVATE_CONST)   _pTxSduCfg;
#if !defined(CANTP_CHANNEL_HALF_DUPLEX_ONLY) && !defined(CANTP_CHANNEL_FULL_DUPLEX_ONLY)
    P2CONST(CanTp_ChannelModeType,AUTOMATIC,CANTP_PRIVATE_CONST) _pChnMdCfg;
#endif
    CanTp_RxStateType*     _pRxChnSt;
    CanTp_TxStateType*     _pTxChnSt;
    uint8*                 _pTmpData;
    PduIdType              _sduid;              
    PduLengthType          _candlc;
}CanTp_ContextType;
/**************************************************************************************************
* Gloable Data definitions
**************************************************************************************************/
#define CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*extern CONST(CanTp_CfgType,CANTP_CONFIG_CONST) CanTp_Cfg;*/

#define CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_Init
(
    CONSTP2CONST(CanTp_ConfigType, CANTP_APPL_CONST, AUTOMATIC) pCfgPtr
);
#if(CANTP_SHUTDOWN_API == STD_ON)
extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_Shutdown(void);
#endif
extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_MainFunction(void);
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_Transmit
(
    PduIdType CanTpTxSduId,
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA) CanTpTxInfoPtr
);
#if (CANTP_TC == STD_ON)  
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelTransmit
(
    PduIdType CanTpTxSduId
);
#endif      
#if(CANTP_RC == STD_ON)
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_CancelReceive
(
    PduIdType CanTpRxSduId
);
#endif
extern FUNC(Std_ReturnType,CANTP_PUBLIC_CODE) CanTp_ChangeParameter
(
    PduIdType CanTpSduId,
    CanTpParameterType parameter,
    uint16 value
);

#if (CANTP_VERSION_INFO_API == STD_ON)
extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_GetVersionInfo
(
    P2VAR(Std_VersionInfoType,AUTOMATIC,CANTP_APPL_DATA) VersionInfo
);
#endif                                                     
#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
extern CONST(CanTp_ConfigType,CANTP_CONFIG_CONST) CanTp_Cfg;
#endif/* ifndef CANTP_H */

/*******************************************************************************
 *  END OF FILE: CanTp.h
 ******************************************************************************/ 

