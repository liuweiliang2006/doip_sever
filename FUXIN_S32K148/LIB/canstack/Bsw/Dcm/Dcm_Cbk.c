/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Cbk.c
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Source File 
*   Author          : Hirain
********************************************************************************
*   Description     : Callback source file of the AUTOSAR DCM module,according 
*   to: AUTOSAR_SWS_DiagnosticCommunicationManager.pdf (Release 4.0) and 
*   ISO14229-1.pdf.
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
*   02.03.01    22/07/2016    rui.guo       N/A          HrAsrDcm160722-01
*   02.03.02    29/09/2016    rui.guo       N/A          HrAsrDcm160929-01
*   02.03.03    30/09/2016    rui.guo       N/A          HrAsrDcm160930-01
*   02.04.02    17/11/2016    rui.guo       N/A          HrAsrDcm161117-01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
* Include files
*******************************************************************************/
#include "Dcm.h"
/*#include "Dcm_Cbk.h"*/
/*#include "Dcm_Cfg.h"*/

#define DCM_START_SEC_PRIVATE_CODE
#include "MemMap.h"
/*******************************************************************************
* Global Functin Prototype (Scope:local)
*******************************************************************************/
STATIC FUNC(void,DCM_PUBLIC_CODE) DiagCopy
( 
    CONSTP2VAR(uint8,AUTOMATIC,DCM_APPL_DATA) dest,
    CONSTP2CONST(uint8,AUTOMATIC,DCM_APPL_DATA)  src,
    const uint32 cnt
);

#define DCM_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"
/*******************************************************************************
* Global Function Implementation
*******************************************************************************/

#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_StartOfReception
*                
* Description:   Callbak function Dcm provided by Dcm to Can_PduRouter
*                             
* Inputs:        DcmRxPduId: Receive PduId
*                TpSduLength: Length in Single Frame or Fist Frame
*                Length: Avaliable buffer size Dcm can provided
*                
* Outputs:       BUFREQ_E_NOT_OK,BUFREQ_E_BUSY and BUFREQ_E_OVFL
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_StartOfReception
(
    const PduIdType     DcmRxPduId,
    const PduLengthType TpSduLength,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) Length
)
{   
    BufReq_ReturnType result = BUFREQ_OK;
    /* 
     * If request is under processing, do not receive any other request
     * (including UDS and OBD request) any more,volatile with AUTOSAR 
     * standard 
     */
    /*if((gDiagState&DIAG_UDS_PROCESSING) == DIAG_UDS_PROCESSING)*/
    if(gDiagState != DIAG_IDLE)
    {
        result = BUFREQ_E_NOT_OK;
    }
    else if(TpSduLength > gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)])
    {
        result = BUFREQ_E_OVFL;
    } 
    else
    {
        switch((uint8)(DcmRxPduId & 0x03))
        {
            case UDS_PHYSICAL_ON_CAN_RX:
            Set_ActiveProtocol(DCM_UDS_ON_CAN);
            Clr_DiagState(DIAG_IDLE);
            gMsgContextType.reqData = gUDS_Physical_DiagBuffer;
            break;
            
            case UDS_FUNCTIONAL_ON_CAN_RX:
            Set_ActiveProtocol(DCM_UDS_ON_CAN);
            Clr_DiagState(DIAG_IDLE);
            gMsgContextType.reqData = gUDS_Functional_DiagBuffer;
            break;

            case UDS_FUNCTIONAL_ON_DOIP_RX:
            Set_ActiveProtocol(DCM_UDS_ON_IP);
            Clr_DiagState(DIAG_IDLE);
            gMsgContextType.reqData = gUDS_Doip_Functional_DiagBuffer;
            break;
           
            #if(ISO_15031_5_MultiChannel == STD_ON)
            case OBD_PHYSICAL_ON_CAN_RX:
            Clr_DiagState(DIAG_IDLE);
            Set_ActiveProtocol(DCM_OBD_ON_CAN);
            gMsgContextType.reqData = gOBD_Physical_DiagBuffer;
            break;
            
            case OBD_FUNCTIONAL_ON_CAN_RX:
            Clr_DiagState(DIAG_IDLE);
            Set_ActiveProtocol(DCM_OBD_ON_CAN);
            gMsgContextType.reqData = gOBD_Functional_DiagBuffer; 
            break;
            #endif

            default:

            break;
        }

        *Length = (uint16)gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)];
        gMsgContextType.reqDataLen = TpSduLength;

        /* Stop S3 Timer */
        if(gSesCtrlType != DCM_SESSION_DEFAULT)
        {
            gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        }
    }

    return result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_CopyRxData
*                
* Description:   Callbak function Dcm provided by Dcm to Can_PduRouter
*                             
* Inputs:        DcmRxPduId:     Receive PduId
*                PduInfoPointer: Pointer to a PduInfoType which indicates
*                the number of bytes to be copied (SduLength) and the 
*                location of the source data (SduDataPtr).
*                -RxBufferSizePtr:Remaining free place in receive buffer after
*                completion of this call.
*                
* Outputs:       BUFREQ_OK,BUFREQ_E_BUSY
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyRxData
(
    const PduIdType  DcmRxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPointer,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  RxBufferSizePtr
)
{
    BufReq_ReturnType result = BUFREQ_OK;

    if(gDiagState == DIAG_UDS_PROCESSING)
    {
        result = BUFREQ_E_BUSY;
    }
    else
    {
        switch((uint8)(DcmRxPduId & 0x03))
        {
            case UDS_PHYSICAL_ON_CAN_RX:
            gMsgContextType.msgAddInfo.reqType = 0u;
            break;
            
            case UDS_FUNCTIONAL_ON_CAN_RX:
            gMsgContextType.msgAddInfo.reqType = 1u;
            break;
            
            case UDS_FUNCTIONAL_ON_DOIP_RX:
            gMsgContextType.msgAddInfo.reqType = 0u;
            break;

            #if(ISO_15031_5_MultiChannel == STD_ON)
            case OBD_PHYSICAL_ON_CAN_RX:
            gMsgContextType.msgAddInfo.reqType = 0u;
            break;
            
            case OBD_FUNCTIONAL_ON_CAN_RX:
            gMsgContextType.msgAddInfo.reqType = 1u;
            break;
            #endif
            
            default:

            break;
        }

        DiagCopy(gMsgContextType.reqData, (const uint8*)PduInfoPointer->SduDataPtr, PduInfoPointer->SduLength);
        /* changed by larry 2013.11.12 QAC */
        /* gMsgContextType.reqData += (uint8)PduInfoPointer->SduLength; */
        gMsgContextType.reqData = (&gMsgContextType.reqData[PduInfoPointer->SduLength]); 
        gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x03)] -= (PduInfoPointer->SduLength);
        *RxBufferSizePtr = (uint16)gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x03)];
     

    }
    return result;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_RxIndication
*                
* Description:   Callbak function Dcm provided by Dcm to Can_PduRouter
*                             
* Inputs:        DcmRxPduId: Receive PduId
*                Result: NTFRSLT_OK means the complete N-PDU has been 
*                received and is stored in the receive buffer.Any other value 
*                means the N_PDU has not been received,
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) Dcm_RxIndication
(
    const PduIdType       DcmRxPduId,
    const NotifResultType Result
)
{
    uint8 i;
    uint8 SessionId;
    if(Result == NTFRSLT_OK)
    {
        Set_PduId(DcmRxPduId);
#if 0
        /* Start P2 Timer */
        gP2ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        SessionId = Dsd_GetSessionMapId(gSesCtrlType) ;
        Set_P2_Server_Timer(gDcmDspSessionRow[SessionId].DcmDspSessionP2ServerMax);
#endif
        switch((uint8)(DcmRxPduId & 0x01))
        {
            case UDS_PHYSICAL_ON_CAN_RX:
            gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)] = (uint32)UDS_PHYS_BUFFER_SIZE;
            gMsgContextType.reqData = gUDS_Physical_DiagBuffer;
            gMsgContextType.resData = gUDS_Physical_DiagBuffer;
            Set_DiagState(DIAG_UDS_INDICATION);

            /* Start P2 Timer */
            gP2ServerTimerStartFlag = DCM_FLAG_ACTIVE;
            SessionId = Dsd_GetSessionMapId(gSesCtrlType) ;
            Set_P2_Server_Timer(gDcmDspSessionRow[SessionId].DcmDspSessionP2ServerMax);

            break;
            
            case UDS_FUNCTIONAL_ON_CAN_RX:
            gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)] = (uint32)UDS_FUNC_BUFFER_SIZE;
            gMsgContextType.reqData = gUDS_Functional_DiagBuffer;
            gMsgContextType.resData = gUDS_Physical_DiagBuffer; 
            /* 
             * Response is always put in physical buffer since it is always 
             * phisical.And only request has two kinds(functional and phisical) 
             */ 
            /*start 20160422*/
            if((gMsgContextType.reqDataLen == 2)&&(gUDS_Functional_DiagBuffer[0] == 0x3E)&&\
                (gUDS_Functional_DiagBuffer[1] == 0x80))
            {
                Reset_DiagState();
                Clr_ActiveProtocol();
                Reset_PduId();
                ClrNegativeResponseCode();
                gMsgContextType.reqData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resDataLen = (uint32)0u;

                if(gSesCtrlType != DCM_DEFAULT_SESSION)
                {
                    gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
                    Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
                }
            }
            /*end*/
            else
            {
                for(i = 0u; i < UDS_FUNC_BUFFER_SIZE; i++)                                                           
                {
                    gUDS_Physical_DiagBuffer[i] = gUDS_Functional_DiagBuffer[i];
                }
                Set_DiagState(DIAG_UDS_INDICATION);

                
                /* Start P2 Timer */
                gP2ServerTimerStartFlag = DCM_FLAG_ACTIVE;
                SessionId = Dsd_GetSessionMapId(gSesCtrlType) ;
                Set_P2_Server_Timer(gDcmDspSessionRow[SessionId].DcmDspSessionP2ServerMax);
            }
            break;
          
            #if(ISO_15031_5_MultiChannel == STD_ON)
            case OBD_PHYSICAL_ON_CAN_RX:
            gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)] = (uint32)OBD_PHYS_BUFFER_SIZE;
            gMsgContextType.reqData = gOBD_Physical_DiagBuffer;
            gMsgContextType.resData = gOBD_Physical_DiagBuffer; 
            Set_DiagState(DIAG_OBD_INDICATION);
            break;
            
            case OBD_FUNCTIONAL_ON_CAN_RX:
            gDcmDslAvailableBufferSize[(uint8)(DcmRxPduId & 0x01)] = (uint32)OBD_FUNC_BUFFER_SIZE;
            gMsgContextType.reqData = gOBD_Functional_DiagBuffer;
            gMsgContextType.resData = gOBD_Functional_DiagBuffer; 
            Set_DiagState(DIAG_OBD_INDICATION);
            break;
            #endif
            default:
            break;
        }
    }
    else
    {
        Reset_DiagState();
    
#if(ISO_15031_5_MultiChannel == STD_ON)
        gDcmDslAvailableBufferSize[DCM_INDEX_0] = (uint32)UDS_PHYS_BUFFER_SIZE;
        gDcmDslAvailableBufferSize[DCM_INDEX_1] = (uint32)UDS_FUNC_BUFFER_SIZE;
        gDcmDslAvailableBufferSize[DCM_INDEX_2] = (uint32)OBD_PHYS_BUFFER_SIZE;
        gDcmDslAvailableBufferSize[3] = (uint32)OBD_FUNC_BUFFER_SIZE;
#else
        gDcmDslAvailableBufferSize[DCM_INDEX_0] = (uint32)UDS_PHYS_BUFFER_SIZE;
        gDcmDslAvailableBufferSize[DCM_INDEX_1] = (uint32)UDS_FUNC_BUFFER_SIZE;
#endif
        /* Start S3 Timer */
        if(gSesCtrlType != DCM_DEFAULT_SESSION)
        {
            gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
            Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
        }
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_CopyTxData
*                
* Description:   Callbak function Dcm provided by Dcm to Can_PduRouter
*                             
* Inputs:        DcmTxPduId: Transmitt PduId
*                PduInfoPtr: Pointer to a PduInfoType, which indicates the 
*                number of bytes to be copied (SduLength) and the location 
*                where the data have to be copied to (SduDataPtr).
*                RetryInfoPtr: None used
*                TxDataCntPtr:   Remaining Tx data after completion of this call
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyTxData
(
    const PduIdType  DcmTxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPtr,
    CONSTP2CONST(RetryInfoType,AUTOMATIC,DCM_APPL_DATA)  RetryInfoPtr,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  TxDataCntPtr
)
{
    (void)RetryInfoPtr;
    (void)(DcmTxPduId);

    if( (gDiagState&DIAG_UDS_RCRP) == DIAG_UDS_RCRP)
    {
        DiagCopy(PduInfoPtr->SduDataPtr, (const uint8*)gNegativeResponseBufferForRRCP, NEG_RESP_BUFFER_SIZE);
    }
    else
    {
        if((gNegativeResponseCode != DCM_E_POSITIVERESPONSE) && (gNegativeResponseCode != DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING))
        {
            DiagCopy(PduInfoPtr->SduDataPtr, (const uint8*)gNegativeResponseBuffer, NEG_RESP_BUFFER_SIZE);
        }
        else
        {
            DiagCopy(PduInfoPtr->SduDataPtr, (const uint8*)gMsgContextType.resData, PduInfoPtr->SduLength);
            /* changed by larry 2013.11.12 QAC */
            /* (gMsgContextType.resData) += (PduInfoPtr->SduLength);*/
            (gMsgContextType.resData) = (&gMsgContextType.resData[(PduInfoPtr->SduLength)]);
        }
    }
    if(gResponseLength >= PduInfoPtr->SduLength)
    {
        gResponseLength -= (PduInfoPtr->SduLength);
    }
    else
    {
        /* Last frame */
        gResponseLength = 0u; 
    }
    if(TxDataCntPtr != DCM_NULL)
    {
        *TxDataCntPtr = gResponseLength;
    }
    else
    {
    }
    return BUFREQ_OK;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Dcm_TxConfirmation
*                
* Description:   Callbak function Dcm provided by Dcm to Can_PduRouter
*                             
* Inputs:        DcmTxPduId: Transmitt PduId
*                Result: NTFRSLT_OK means the complete N-PDU has been 
*                transmitted.Any other value means an error occurred during 
*                transmission.
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void,DCM_PUBLIC_CODE) Dcm_TxConfirmation
(
    const PduIdType       DcmTxPduId,
    const NotifResultType Result
)
{
    /*uint8 SessionId;*/
    uint8 RespPending;
    (void) DcmTxPduId;
    RespPending = 0;
    
    switch(Result)
    {
        case NTFRSLT_OK:
        {
            if((gDiagState&DIAG_UDS_RCRP) == DIAG_UDS_RCRP)
            {
                Clr_DiagState(DIAG_UDS_RCRP);
                RespPending = 1;
                /*SessionId = Dsd_GetSessionMapId(gSesCtrlType) ;*/

                /* Set enhances P2 timer */
                /*Set_P2_Server_Timer(gDcmDspSessionRow[SessionId].DcmDspSessionP2StarServerMax);*/
            }
            
            #if(DCM_SERVICE_2A_ENABLED == STD_ON)
            else if((gDiagState&DIAG_UDS_PERIODIC_TX) == DIAG_UDS_PERIODIC_TX) 
            {
                Clr_DiagState(DIAG_UDS_PERIODIC_TX);
                Clr_ActiveProtocol();
                Reset_PduId();
                ClrNegativeResponseCode();
                gMsgContextType.reqData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resDataLen = (uint32)0u;
            }
            #endif

            /* Positive response or other negative response */
            else
            {
                Clr_DiagState(DIAG_UDS_PROCESSING); 
                /* added by larry 20140410 for avoid gDiagState equal to 0 */
                if(gDiagState == 0u)
                {
                    Reset_DiagState();
                }
                else
                {
                    /* do nothing */
                }
                Clr_ActiveProtocol();
                Reset_PduId();
                ClrNegativeResponseCode();
                gMsgContextType.reqData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resData = gUDS_Physical_DiagBuffer;
                gMsgContextType.resDataLen = (uint32)0u;
            }
 
        }
        break;

        default:
        {
            Dsd_InteralInit();
        }
        break;
    }

    /* Start S3 Timer */
    if((gSesCtrlType != DCM_DEFAULT_SESSION)&&(0 == RespPending))
    {
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
    }
}

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

/*******************************************************************************
* Global Functin Implementation (Scope:local)  
*******************************************************************************/

#define DCM_START_SEC_PRIVATE_CODE
#include "MemMap.h"      

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: DiagCopy
*                
* Description:   Move number of cnt data from source to destination 
*                             
* Inputs:        dest:pointing to the destination where data should be copied to
*                src: pointing to the source where data should be copied frome
*                cnt: the total length of the data should be copied
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void,DCM_PUBLIC_CODE) DiagCopy
( 
    CONSTP2VAR(uint8,AUTOMATIC,DCM_APPL_DATA) dest,
    CONSTP2CONST(uint8,AUTOMATIC,DCM_APPL_DATA)  src,
    const uint32 cnt
)
{
    uint32 i;

    if((dest != DCM_NULL)&&(src != DCM_NULL))
    {
        for(i = (uint32)0u; i < cnt; i++)
        {
            dest[i] = src[i] ;
        }
    }
    else
    {
        /* do nothing */
    }
}

#define DCM_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

