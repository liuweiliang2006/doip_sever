/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Type.h
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Header File 
*   Author          : Hirain
********************************************************************************
*   Description     : Type define file of the AUTOSAR Diagnositc communcation 
*   manager, according to:AUTOSAR_SWS_DiagnosticCommunicationManager.pdf(Release
*   4.0) and ISO14229-1.pdf.
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
*   01.00.00    12/03/2010    xyliu         N/A          Original
*   01.02.01    22/12/2011    xyliu         N/A          HrAsrDcm111222-01
*   01.02.02    12/09/2012    dongeryang    N/A          HrAsrDcm120912-01
*   02.00.01    27/07/2013    jinbiao.li    N/A          HrAsrDcm130727-01
*   02.00.02    14/08/2013    jinbiao.li    N/A          HrAsrDcm130814-01
*   02.00.03    19/08/2013    jinbiao.li    N/A          HrAsrDcm130819-01
*   02.00.04    27/08/2013    jinbiao.li    N/A          HrAsrDcm130827-01
*   02.01.00    03/09/2013    jinbiao.li    N/A          HrAsrDcm130903-01
*   02.02.00    20/02/2014    wenrui.li     N/A          HrAsrDcm140220-01
*   02.03.00    11/04/2014    wenrui.li     N/A          HrAsrDcm140411-01
********************************************************************************
* END_FILE_HDR*/

#ifndef _DCM_TYPES_H_
#define _DCM_TYPES_H_

/*******************************************************************************
* Include files
*******************************************************************************/
#include "Platform_Types.h"
#include "ComStack_Types.h"

/*******************************************************************************
* Local Macro and Tyedef
*******************************************************************************/
/* General Define */
#define DCM_HAVE_ERRORS                                     (0x01u)
#define DCM_HAVE_NO_ERRORS                                  (0x00u)
#define DCM_SID_OFF_SET                                     (0x40u)
#define DCM_DIVIDE_TOW                                      (0x01u)                 
#define DCM_TIME_EXPIRED                                    (0x00u)
#define DCM_SID_POSITION                                    (0x00u)
#define DCM_AMPLIFY_8_TIMES                                 (0x08u)
#define THE_OFFSET_DATA                                     (0x40u)
#define DCM_COMMON_DEFINED_TASK_TIME                        (0x10u) 
#define DCM_REQUIRE_DATA_LENGTH_1_BYTE                      (0x01u)
#define DCM_REQUIRE_DATA_LENGTH_2_BYTE                      (0x02u)
#define DCM_REQUIRE_DATA_LENGTH_3_BYTE                      (0x03u)
#define DCM_REQUIRE_DATA_LENGTH_4_BYTE                      (0x04u)
#define DCM_REQUIRE_DATA_LENGTH_5_BYTE                      (0x05u)
#define DCM_REQUIRE_DATA_LENGTH_6_BYTE                      (0x06u)
#define DCM_REQUIRE_DATA_LENGTH_7_BYTE                      (0x07u)
#define DCM_RESPONSE_DATA_LENGTH_1_BYTE                     (0x01u)
#define DCM_RESPONSE_DATA_LENGTH_2_BYTE                     (0x02u)
#define DCM_RESPONSE_DATA_LENGTH_3_BYTE                     (0x03u)
#define DCM_RESPONSE_DATA_LENGTH_4_BYTE                     (0x04u)
#define DCM_RESPONSE_DATA_LENGTH_5_BYTE                     (0x05u)
#define DCM_NUMBER_OF_CHANNEL_BUFFER_OBD_INCLUDE            (0x04u)
#define DCM_NUMBER_OF_CHANNEL_BUFFER_WITHOUT_OBD            (0x03u)
#define DCM_SERVICE_AND_SUB_SERVICE_REQUIRE_LENGTH          (0x02u)
#define DCM_SERVICE_AND_SUB_SERVICE_RESPONSE_LENGTH         (0x02u)
#define SETSUPPRESSPOSRESPONSEBITMASK                       (0x80u)
#define SUPPRESS_POS_RSP_BYTE                               (0x80u)
#define THE_LARGEST_SERVICE_ID                              (0x85u)
#define RIGHT_ROLLING_SUPPRESS_POS_RSP_BIT                  (0x07u)
#define GET_THE_SECURITY_LEVEL                              (0xFEu)
#define DCM_SESSION_TYPE_NOT_CORRECT                        (0x00u)
#define DCM_SECURITY_LEVEL_NOT_CORRECT                      (0x00u)
#define DCM_REQUEST_ADDRESS_NOT_CORRECT                     (0x00u)
/* for negative response 0x78 */
#define FORCERCR_RP                                         (0x01u)
#define UNFORCERCR_RP                                       (0x00u)
/* for 0x10 */
#define DCM_SERVICE_10_SESSION_TYPE_0                       (0x00u)
#define DCM_SERVICE_10_SESSION_TYPE_1                       (0x01u)
#define DCM_SERVICE_10_SESSION_TYPE_2                       (0x02u)
#define DCM_SERVICE_10_SESSION_TYPE_3                       (0x03u)
#define DCM_SERVICE_10_SESSION_TYPE_4                       (0x04u)
#define DCM_SERVICE_10_SESSION_TYPE_5                       (0x05u)
#define DCM_SERVICE_10_SESSION_TYPE_6                       (0x06u)
#define DCM_SERVICE_10_SESSION_TYPE_7                       (0x07u)
#define DCM_SERVICE_10_POSITIVE_RESPONSE_DATA               (0x50u)
/* for 0x14 */
#define DCM_SERVICE_14_REQ_LENGTH                           (0x04u)
/* for 0x22 */
#define DCM_SERVICE_22_NO_DID_TO_STORE                      (0x00u)
#define DCM_SERVICE_22_DID_DATA_LENGTH                      (0x02u)
#define DCM_SERVICE_22_RIGHT_ROLLING_8_BIT                  (0x08u)
#define DCM_SERVICE_22_INVALID_DID_POSITION                 (0xFFu)
#define DCM_SERVICE_22_NO_DIDPOSITION_TO_STORE              (0x00u)
/* for 0x23 */
#define DCM_SERVICE_23_GET_MEMORY_AND_ADDRESS_BYTE_LOW_NIBBLE   (0x0Fu)
#define DCM_SERVICE_23_GET_MEMORY_AND_ADDRESS_BYTE_HIGH_NIBBLE  (0x04u)
/* for 0x24 */
#define DCM_SERVICE_24_REQ_LENGTH                           (0x03u)
/* for 0x27 */
#define DCM_SERVICE_27_SECURITY_MAP_LOCK                    (0x00u)
#define DCM_SERVICE_27_SECURITY_MAP_L1                      (0x01u)
#define DCM_SERVICE_27_SECURITY_MAP_L2                      (0x02u)
#define DCM_SERVICE_27_SECURITY_MAP_L3                      (0x03u)
#define DCM_SERVICE_27_SECURITY_MAP_L4                      (0x04u)
#define DCM_SERVICE_27_SECURITY_MAP_L5                      (0x05u)
#define DCM_SERVICE_27_SECURITY_MAP_L6                      (0x06u)
#define DCM_SERVICE_27_SECURITY_MAP_L7                      (0x07u)
#define DCM_SERVICE_27_SECURITY_MAP_L8                      (0x08u)
#define DCM_SERVICE_27_SEND_KEEY                            (0x00u)
/* for 0x28 */
#define DCM_SERVICE_28_REQ_LENGTH                           (0x03u)
/* for 0x2A */
#define DCM_SERVICE_2A_NO_PERIODIC_DID_TO_STORE             (0x00u)
#define DCM_SERVICE_2A_HIGH_SUB_SERVICE_NUMBER              (0x04u)
#define DCM_SERVICE_2A_LOW_SUB_SERVICE_NUMBER               (0x01u)
#define DCM_SERVICE_2A_SEND_AT_SLOW_RATE                    (0x01u)
#define DCM_SERVICE_2A_SEND_AT_MEDIUM_RATE                  (0x02u)
#define DCM_SERVICE_2A_SEND_AT_FAST_RATE                    (0x03u)
#define DCM_SERVICE_2A_STOP_SENDING                         (0x04u)
#define DCM_SERVICE_2A_POSITIVE_RESPONSE                    (0x6Au)
#define DCM_SERVICE_2A_NO_PERIODIC_DIDPOSITION_TO_STORE     (0x00u)
/* for 0x2C */
#define DCM_SERVICE_2C_JUDGE_THE_LENGTH_IS_MULTIPLE_OF_4    (0x04u)
#define DCM_SERVICE_2C_LEAST_REQ_LENGTH                     (0x04u)
#define DCM_SERVICE_2C_DEFINE_BY_MEMORY_ADDRESS             (0x02u)
#define DCM_SERVICE_2C_SUB_SERVICE_03_REQ_LENGTH            (0x04u)
#define DCM_SERVICE_2C_NUMBER_OF_ARRAY                      (16u)
/* for 0x2F */
#define DCM_SERVICE_2F_RETURN_CONTROL_TO_ECU_REQ_LENGTH     (0x04u)
#define DCM_SERVICE_2F_RESET_TO_DEFAULT_REQ_LENGTH          (0x04u)
#define DCM_SERVICE_2F_FREEZE_CURRENT_STATE_REQ_LENGTH      (0x04u)  
/* for 0x31 */
#define HAVE_GOTTON_SEED                                    (0x01u)
#define HAVE_STARTED_ROUNTINE                               (0x01u)
#define HAVE_STOPPED_ROUNTINE                               (0x02u)
#define HAVE_REQ_ROUNTINE_RESULT                            (0x04u)
#define INVALID_SECURITY_LEVEL                              (0xFFu)
#define INVALID_SESSION_TYPE                                (0xFFu)
#define INVALID_SUB_SERVICE_POSITION                        (0xFFu)
/* for 0x3D */
#define DCM_SERVICE_3D_GET_MEMORY_AND_ADDRESS_BYTE_LOW_NIBBLE   (0x0Fu)
#define DCM_SERVICE_3D_GET_MEMORY_AND_ADDRESS_BYTE_HIGH_NIBBLE  (0x04u)
/* for 0x3E */
#define DCM_SERVICE_3E_RESPONSE_DATA_LENGTH                 (0x02u)
#define DCM_SERVICE_3E_REQUIRE_DATA_LENGTH                  (0x02u) 
/* for 0x10 0x11 0x85 */
#define DCM_SERVICE_10_11_85_REQUIRE_DATA_LENGTH            (0x02u) 

/* Dcm_StatusType */
#define DCM_E_OK                                            (0x00u)
#define DCM_E_COMPARE_KEY_FAILED                            (0x01u)
#define DCM_E_TI_PREPARE_LIMITS                             (0x02u)
#define DCM_E_TI_PREPARE_INCONSTENT                         (0x03u)
#define DCM_E_SESSION_NOT_ALLOWED                           (0x04u)
#define DCM_E_PROTOCOL_NOT_ALLOWED                          (0x05u)
#define DCM_E_ROE_NOT_ACCEPTED                              (0x06u)
#define DCM_E_PERIODICID_NOT_ACCEPTED                       (0x07u)
#define DCM_E_REQUEST_NOT_ACCEPTED                          (0x08u)
#define DCM_E_REQUEST_ENV_NOK                               (0x09u)
/* Dcm_ProtocolType */
#define DCM_OBD_ON_CAN                                      (0x00u)
#define DCM_OBD_ON_FLEXRAY                                  (0x01u)
#define DCM_OBD_ON_IP                                       (0x02u)
#define DCM_UDS_ON_CAN                                      (0x03u)
#define DCM_UDS_ON_FLEXRAY                                  (0x04u)
#define DCM_UDS_ON_IP                                       (0x05u)
#define DCM_ROE_ON_CAN                                      (0x06u) 
#define DCM_ROE_ON_FLEXRAY                                  (0x07u)
#define DCM_ROE_ON_IP                                       (0x08u)
#define DCM_PERIODICTRANS_ON_CAN                            (0x09u)
#define DCM_PERIODICTRANS_ON_FLEXRAY                        (0x0Au)
#define DCM_PERIODICTRANS_ON_IP                             (0x0Bu)
/* Dcm_SesCtrlType */
#define DCM_DEFAULT_SESSION                                 (0x01u)
#define DCM_PROGRAMMING_SESSION                             (0x02u)
#define DCM_EXTENDED_DIAGNOSTIC_SESSION                     (0x03u)
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION                (0x04u)
/* Dcm_SessionType*/
#define DCM_SESSION_DEFAULT                                 (0x01u)
#define DCM_SESSION_PROGRAMMING                             (0x02u)        
#define DCM_SESSION_EXTENDED_DIAGNOSTIC                     (0x04u)
#define DCM_SESSION_USERDEFINED1                            (0x08u)
#define DCM_SESSION_USERDEFINED2                            (0x10u)
#define DCM_SESSION_USERDEFINED3                            (0x20u)
#define DCM_SESSION_USERDEFINED4                            (0x40u)
#define DCM_SESSION_USERDEFINED5                            (0x80u)
/* Dcm Flag status */
#define DCM_FLAG_ACTIVE                                     (0x01u)
#define DCM_FLAG_DISACTIVE                                  (0x00u)


/* invalid handle or received id*/
#define DCM_INVALID_HANDLE_OR_ID                            (0xFFu)
/* Negative Response Service Id */
#define DCM_NEGATIVE_RES_SERVICE_ID                         (0x7Fu)
/* Dcm_NegativeResponseCodeType */
#define DCM_E_POSITIVERESPONSE                              (0x00u)
#define DCM_E_GENERALREJECT                                 (0x10u)
#define DCM_E_SERVICENOTSUPPORTED                           (0x11u)
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                       (0x12u)
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT         (0x13u)
#define DCM_E_RESPONSETOOLONG                               (0x14u)
#define DCM_E_BUSYREPEATREQUEST                             (0x21u)
#define DCM_E_CONDITIONSNOTCORRECT                          (0x22u)
#define DCM_E_REQUESTSEQUENCEERROR                          (0x24u)
#define DCM_E_REQUESTOUTOFRANGE                             (0x31u)
#define DCM_E_SECURITYACCESSDENIED                          (0x33u)
#define DCM_E_INVALIDKEY                                    (0x35u)
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                        (0x36u)
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED                   (0x37u)
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED                     (0x70u)
#define DCM_E_TRANSFERDATASUSPENDED                         (0x71u)
#define DCM_E_GENERALPROGRAMMINGFAILURE                     (0x72u)
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER                     (0x73u)
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING      (0x78u)
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION        (0x7Eu)
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION            (0x7Fu)
#define DCM_E_RPMTOOHIGH                                    (0x81u)
#define DCM_E_RPMTOOLOW                                     (0x82u)
#define DCM_E_ENGINEISRUNNING                               (0x83u)
#define DCM_E_ENGINEISNOTRUNNING                            (0x84u)
#define DCM_E_ENGINERUNTIMETOOLOW                           (0x85u)
#define DCM_E_TEMPERATURETOOHIGH                            (0x86u)
#define DCM_E_TEMPERATURETOOLOW                             (0x87u)
#define DCM_E_VEHICLESPEEDTOOHIGH                           (0x88u)
#define DCM_E_VEHICLESPEEDTOOLOW                            (0x89u)
#define DCM_E_THROTTLE_PEDALTOOHIGH                         (0x8Au)
#define DCM_E_THROTTLE_PEDALTOOLOW                          (0x8Bu)
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL                 (0x8Cu)
#define DCM_E_TRANSMISSIONRANGENOTINGEAR                    (0x8Du)
#define DCM_E_BRAKESWITCH_NOTCLOSED                         (0x8Fu)
#define DCM_E_SHIFTERLEVERNOTINPARK                         (0x90u)
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED                   (0x91u)
#define DCM_E_VOLTAGETOOHIGH                                (0x92u)
#define DCM_E_VOLTAGETOOLOW                                 (0x93u)
/* Dcm_CommunicationModeType */                        
#define DCM_ENABLE_RX_TX_NORM                               (0x00u)
#define DCM_ENABLE_RX_DISABLE_TX_NORM                       (0x01u)
#define DCM_DISABLE_RX_ENABLE_TX_NORM                       (0x02u)
#define DCM_DISABLE_RX_TX_NORMAL                            (0x03u)
#define DCM_ENABLE_RX_TX_NM                                 (0x04u)
#define DCM_ENABLE_RX_DISABLE_TX_NM                         (0x05u)
#define DCM_DISABLE_RX_ENABLE_TX_NM                         (0x06u)
#define DCM_DISABLE_RX_TX_NM                                (0x07u)
#define DCM_ENABLE_RX_TX_NORM_NM                            (0x08u)
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM                    (0x09u)
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM                    (0x0Au)
#define DCM_DISABLE_RX_TX_NORM_NM                           (0x0Bu)
/* Dcm_ConfirmationStatusType */
#define DCM_RES_POS_OK                                      (0x00u)
#define DCM_RES_POS_NOT_OK                                  (0x01u)
#define DCM_RES_NEG_OK                                      (0x02u)
#define DCM_RES_NEG_NOT_OK                                  (0x03u)
/* Dcm_OpStatusType */
#define DCM_INITIAL                                         (0x00u)
#define DCM_PENDING                                         (0x01u)
#define DCM_CANCEL                                          (0x02u)
#define DCM_FORCE_RCRRP_OK                                  (0x03u)
/* Dcm_ReturnReadMemoryType */
#define DCM_READ_OK                                         (0x00u)
#define DCM_READ_PENDIN                                     (0x01u)
#define DCM_READ_FAILED                                     (0x02u)
/* Dcm_ReturnWriteMemoryType */
#define DCM_WRITE_OK                                        (0x00u)
#define DCM_WRITE_PENDIN                                    (0x01u)
#define DCM_WRITE_FAILED                                    (0x02u)
/* Dcm_RoeStateType */
#define DCM_ROE_ACTIVE                                      (0x00u)
#define DCM_ROE_UNACTIV                                     (0x01u)
/* Dcm_EcuStartModeType */
#define DCM_COLD_START                                      (0x00u)
#define DCM_WARM_START                                      (0x01u)
/* Dcm_ResetModeType */
#define DCM_NO_RESET                                        (0x00u)
#define DCM_HARD_RESET                                      (0x01u)
#define DCM_KEY_ON_OFF_RESET                                (0x02u)
#define DCM_SOFT_RESET                                      (0x03u)
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET               (0x04u)
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET              (0x05u)
#define DCM_BOOTLOADER_RESET                                (0x06u)
#define DCM_SS_BOOTLOADER_RESET                             (0x07u)
#define DCM_RESET_EXECUTION                                 (0x08u)

/*******************************************************************************
* Macros Define for magic word
*******************************************************************************/
#define DCM_ALL_BITS_ON_8                                   (0xFFu)
#define DCM_ALL_BITS_ON_16                                  (0xFFFFu) 
#define DCM_MAX_NUMBER_OF_SID_MAP                           (72u)             

/* Dcm_Index_Def */
#define DCM_INDEX_0                                         (0u)
#define DCM_INDEX_1                                         (1u)
#define DCM_INDEX_2                                         (2u)
#define DCM_INDEX_3                                         (3u)
#define DCM_INDEX_4                                         (4u)
#define DCM_INDEX_5                                         (5u)
#define DCM_INDEX_6                                         (6u)
#define DCM_INDEX_7                                         (7u)
#define DCM_INDEX_8                                         (8u)

/* Dcm_Index_Def */
#define DCM_UINT8_0                                         (0x00u)
#define DCM_UINT8_1                                         (0x01u)
#define DCM_UINT8_2                                         (0x02u)
#define DCM_UINT8_3                                         (0x03u)
#define DCM_UINT8_4                                         (0x04u)
#define DCM_UINT8_5                                         (0x05u)
#define DCM_UINT8_6                                         (0x06u)
#define DCM_UINT8_7                                         (0x07u)
#define DCM_UINT8_8                                         (0x08u)

/*******************************************************************************
* Macros and Tyedef
*******************************************************************************/
typedef uint8 Dcm_StatusType;
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_CommunicationModeType;
typedef struct
{
    Dcm_ProtocolType protocolType;
}Dcm_ConfigType;  /* Need change */
typedef uint8 Dcm_ConfirmationStatusType;
typedef uint8 Dcm_OpStatusType;
typedef uint8 Dcm_ReturnReadMemoryType;
typedef uint8 Dcm_ReturnWriteMemoryType;
typedef uint8 Dcm_RoeStateType;
typedef uint8 Dcm_EcuStartModeType;
typedef struct
{
    uint8 ProtocolId; 
    uint8 TesterSourceAddr;
    uint8 Sid;
    uint8 SubFncId;
    Dcm_EcuStartModeType EcuStartMode;
}Dcm_ProgConditionsType;
typedef uint8 Dcm_MsgItemType;
typedef uint8 CurrentSidMapType;
typedef uint8 CurrentOBDSidMapType;
typedef Dcm_MsgItemType *Dcm_MsgType;
typedef uint16 Dcm_DspMaxDidToReadType;
typedef uint32 Dcm_MsgLenType;
typedef uint32 Dcm_CurentDcmDsdServiceTableSizeType;
typedef uint32 Dcm_CurentDcmOBDServiceTableSizeType;
typedef uint32 Dcm_DspNonDefaultSessionS3ServerType;
typedef uint8 Dcm_IdContextType; /* Need change */
typedef struct
{
    uint8 reqType; /* 0=physical request; 1=functional request */
    uint8 suppressPosResponse;/* 0=no; 1=yes;*/
    uint8 cancelOperation;/* 0=no;1=cancel pending operation */
}Dcm_MsgAddInfoType;

typedef struct 
{
    Dcm_MsgType reqData;
    Dcm_MsgLenType reqDataLen;
    Dcm_MsgType resData;
    Dcm_MsgLenType resDataLen;
    Dcm_MsgAddInfoType msgAddInfo;
    Dcm_MsgLenType resMaxDataLen;
    Dcm_IdContextType idContext;
    PduIdType dcmRxPduId;
}Dcm_MsgContextType;
typedef uint8 Dcm_ResetModeType;

typedef enum
{
    DCM_UNINITIALIZED = 0u,
    DCM_INITIALIZED = 1u  
}DCM_InitType;

#endif

