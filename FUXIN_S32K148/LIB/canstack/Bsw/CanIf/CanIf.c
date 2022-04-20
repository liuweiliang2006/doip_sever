/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf.c
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Interface module Source File
*   Author          : HeYang
********************************************************************************
*   Description     : Implementation of CAN Interface provided functionality
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

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "Dem.h"
#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#if (STD_ON == CANIF_SUPPORT_OSEK_NM)
#include "OsekNm_Cbk.h"
#endif

/*******************************************************************************
*   Macro 
*******************************************************************************/
#if (1 == CANIF_USED_CONTROLLER_NUM)
    #define CANIF_CANCONTROLLER_TX        (0u)
    #define CANIF_CANCONTROLLER_RX        (0u)
    #define CANIF_CONTROLLER_ID           (0u)
#else 
    #define CANIF_CANCONTROLLER_TX        \
     (CAN_USED_HOH_INFO[(CanIfTxPduConfig[CanTxPduId]).Hth].controllerRef)
    #define CANIF_CANCONTROLLER_RX        \
                                    (CAN_USED_HOH_INFO[Hrh].controllerRef)
    #define CANIF_CONTROLLER_ID           (ControllerId)
#endif
#if(STD_ON == CANIF_HRH_RANGE_FILTER)
    #define CANIF_HRH_CANID_TYPE          \
                             (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduRangeCanIdType)
    #define CANIF_HRH_LOWER_CANID         \
                                 (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduLowerCanId)
    #define CANIF_HRH_UPPER_CANID         \
                                 (CanIfHrhRangeCfg[Hrh].HrhRangeRxPduUpperCanId)

#endif
#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
    #define CANIF_RXPDU_RANGECFG   (CanIfRxPduConfig[handle].RxPduCanIdRangeCfg)
#endif

/*******************************************************************************
*   Local Data Define 
*******************************************************************************/
#define CANIF_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

STATIC VAR(PduIdType, CANIF_PRIVATE_DATA) CanIf_TotalRxPduIds = 0;
STATIC VAR(PduIdType, CANIF_PRIVATE_DATA) CanIf_TotalTxPduIds = 0;

STATIC VAR(CanIf_ControllerModeType, CANIF_PRIVATE_DATA)  
                                CanIf_ControllerMode[CANIF_USED_CONTROLLER_NUM];

/*used for DET ,except for CanIf_Transmit*/
STATIC VAR(CanIf_InitType, CANIF_PRIVATE_DATA) 
                                         CanIf_InitStatus = CANIF_UNINITIALIZED;

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
STATIC VAR(PduIdType, CANIF_PRIVATE_DATA)  CanIfTxBufferFillCount;
#endif

#if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
STATIC VAR(CanIf_PduGetModeType, CANIF_PRIVATE_DATA) 
                                        CanIfPduMode[CANIF_USED_CONTROLLER_NUM];             
#endif

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
               
/*******************************************************************************
*   Local Function Declaration 
*******************************************************************************/
#define CANIF_START_SEC_PRIVATE_CODE
#include "MemMap.h"

STATIC FUNC(void, CANIF_PRIVATE_CODE) CanIf_MemSet
(
    CONSTP2VAR(void, AUTOMATIC, CANIF_PRIVATE_DATA) pDest,
    const uint8  data, 
    uint32 length
);

STATIC FUNC(void, CANIF_PRIVATE_CODE) CanIf_MemCpy
(
    CONSTP2VAR(void, AUTOMATIC, CANIF_PRIVATE_DATA) dest,
    CONSTP2CONST(void, AUTOMATIC, AUTOMATIC) source, 
    uint32  length
); 

STATIC FUNC(Std_ReturnType, CANIF_PRIVATE_CODE) CanIf_RxParCheck
(    
    const Can_HwHandleType Hrh, 
    const Can_IdType CanId,
    const uint8 CanDlc,
    CONSTP2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
);

STATIC FUNC(Std_ReturnType, CANIF_PRIVATE_CODE) CanIf_DlcCheck
(    
    const uint8 CanDlc,
    const PduIdType handle,
    CONSTP2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) dlc 
);

#define CANIF_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

/*******************************************************************************
*   Local Function Define
*******************************************************************************/
#define CANIF_START_SEC_PRIVATE_CODE
#include "MemMap.h"

#define CANIF_DEBUG 0
                                           
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_MemSet
*                
* Description:   used for setting data value.
*                
* Inputs:        pDest,data,length
*                   
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANIF_PRIVATE_CODE) CanIf_MemSet
(
    CONSTP2VAR(void, AUTOMATIC, CANIF_PRIVATE_DATA) pDest,
    const uint8  data, 
    uint32 length
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if(NULL_PTR != pDest)
    {
        while(length > 0x0UL)
        {  
            length--;
            ((uint8*)pDest)[length] = data;
        } 
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_MemCpy
*                
* Description:   used for copy data value.
*                
* Inputs:        pDest,source,count
*                   
* Outputs:       dest
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CANIF_PRIVATE_CODE) CanIf_MemCpy
(
    CONSTP2VAR(void, AUTOMATIC, CANIF_PRIVATE_DATA) dest,
    CONSTP2CONST(void, AUTOMATIC, AUTOMATIC) source, 
    uint32  length
)
{ 
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    CONSTP2VAR(uint8, AUTOMATIC, CANIF_PRIVATE_DATA) sd = (uint8 * const)dest;
    CONSTP2CONST(uint8, AUTOMATIC, AUTOMATIC) ss = (const uint8 * const )source;
    uint32 i = 0;
    
    if((NULL_PTR != sd)&&(NULL_PTR != ss))
    {
        while (length > 0x0UL)
        {
            sd[i] = ss[i];
            i++;
            length--;
        }
    }  
}

#if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_RxParCheck
*                
* Description:   used to check rxindication's parameters 
*                
* Inputs:        Hrh,CanId,CanDlc,CanSduPtr
*                   
* Outputs:       Std_ReturnType 
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType, CANIF_PRIVATE_CODE) CanIf_RxParCheck
(    
    const Can_HwHandleType Hrh, 
    const Can_IdType CanId,
    const uint8 CanDlc,
    CONSTP2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    

    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_UNINIT);
    }
    else if(Hrh >= CanIfInitNumberofHrh)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_HRH);
    }
    else if(CanId > CANIF_MAX_CANID)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_CANID);
    }
    else if(CanDlc > CAN_DATA_DLC)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_DLC);
    }
    else if(NULL_PTR == CanSduPtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_RXINDICATION_APIID,
                        CANIF_E_PARAM_POINTER);
    }
    else
    {
        ret = E_OK;
    }
    
    return ret;
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_RxParCheck
*                
* Description:   used to check rxindication's dlc
*                
* Inputs:        CanDlc,handle,dlc
*                   
* Outputs:       Std_ReturnType 
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Std_ReturnType, CANIF_PRIVATE_CODE) CanIf_DlcCheck
(    
    const uint8 CanDlc,
    const PduIdType handle,
    CONSTP2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) dlc 
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Std_ReturnType ret = E_OK;
    PduLengthType tempDlc = 0;
    
    #if(STD_ON == CANIF_PRIVATE_DLC_CHECK)
    /* AUTOSAR Standard method */
    #if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_AUTOSAR)
    /*CANIF026: The CanIf shall accept all L-PDUs with a 
    received DLC value equal or greater then the configured DLC value. */
    if(CanDlc < (CanIfRxPduConfig[handle].Length))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*If the CanIf has accepted a L-PDU received via 
        CanIf_RxIndication() during DLC check, the CanIf shall 
        copy the number of bytes according to the configured 
        DLC value to the static receive buffer, if configured 
        for that L-PDU , or allow copying the data to the upper
        layer modules.*/
        tempDlc = CanIfRxPduConfig[handle].Length;
    }
    
    #endif
    
    #if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_UNEQUAL)
    /* The CanIf will accept L-PDU only when its received DLC value equal to
     the configured DLC value. */
    if(CanDlc == (CanIfRxPduConfig[handle].Length))
    {
       tempDlc = CanDlc;
    }
    else
    {
       /* */
       #if(CANIF_DLC_CHECK_FAIL_INDICATION == STD_OFF)
       ret = E_NOT_OK;
       #else
       tempDlc = CanDlc;
       ret = E_OK;
       #endif
           
    }
    #endif
    
    #if(CANIF_DLC_CHECK_TYPE ==  CANIF_DLC_CHECK_USER)
    
    #endif
    
    #else
    /*In case of the DLC check is disabled,  the received DLC value is passed in
    the receive indication type <User_RxIndication>(CanRxPduId,*PduInfoPtr),to 
    upper layer modules .The upper layer module copies the data to its own 
    buffer always according to the received DLC value and not to the configured 
    DLC value.*/
    tempDlc = CanDlc;
    #endif
    
    if(NULL_PTR != dlc)
    {
        *dlc = tempDlc;    
    }

    return ret;

}

#define CANIF_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

/*******************************************************************************
*   Global Function Define
*******************************************************************************/
#define CANIF_START_SEC_PUBLIC_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_Init
*                
* Description:   This service Initializes internal and external interfaces of 
*                the CAN Interface for the further processing.
*
* Inputs:        ConfigPtr: Pointer to configuration parameter set, 
*                           used e.g. for post build parameters
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/* const CanIf_ConfigType* ConfigPtr */ 
FUNC(void, CANIF_PUBLIC_CODE) CanIf_Init(void)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint8 i;
   
    for(i = 0; i < CANIF_USED_CONTROLLER_NUM; i++) 
    {
        #if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
        CanIfPduMode[i] = CANIF_GET_ONLINE;
        #endif   
        
        CanIf_ControllerMode[i] = CANIF_CS_UNINIT;
    }
    
   
    CanIf_TotalRxPduIds = CanIfInitNumberOfCanRxPduIds;
    CanIf_TotalTxPduIds = CanIfInitNumberOfCanTxPduIds;
   
    #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    CanIf_MemSet(CanIfTxBufferPDUFillflag, FALSE, CanIf_TotalTxPduIds);
    
    CanIf_MemSet(CanIfTxBufferSdu, 0, (CanIf_TotalTxPduIds*CAN_DATA_DLC));

    CanIf_MemSet(CanIfTxBufferPdu, 0, 
                    (((PduIdType)(sizeof(Can_PduType))) * CanIf_TotalTxPduIds));
    
    CanIfTxBufferFillCount = 0; 
    #endif 
   
    #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    for(i = 0; i < CanIf_TotalTxPduIds; i++) 
    {
        if(DYNAMIC_TXPDU == CanIfTxPduConfig[i].TxPduType)
        {
            CanIfTxPduCanIdForDynamic[i] = CanIfTxPduConfig[i].CanId;
        }
    }
    #endif
   
    #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    CanIf_MemSet(CanIfTxNotifStatus, CANIF_NO_NOTIFICATION,
            (((PduIdType)sizeof(CanIf_NotifStatusType))) * CanIf_TotalTxPduIds);
    #endif
    
    #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    CanIf_MemSet(CanIfRxNotifStatus, CANIF_NO_NOTIFICATION,
            (((PduIdType)sizeof(CanIf_NotifStatusType))) * CanIf_TotalRxPduIds);
    #endif
    
    
    #if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    CanIf_MemSet(CanIfRxBufferSduData, 0, CAN_DATA_DLC * CanIf_TotalRxPduIds);
    CanIf_MemSet(CanIfRxBufferSduLength, CANIF_RX_BUFFER_SDU_LENGTH_INITIAL,
                    (((PduIdType)sizeof(PduLengthType))) * CanIf_TotalRxPduIds);            
    #endif
  
    for(i = 0; i < CANIF_USED_CONTROLLER_NUM; i++) 
    {

        CanIf_ControllerMode[i] = CANIF_CS_STOPPED;
    }
    CanIf_InitStatus = CANIF_INITIALIZED;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_SetControllerMode
*                
* Description:   This service calls the corresponding CAN Driver service for 
*                changing of the CAN controller mode.
*
* Inputs:        ControllerId: Abstracted CanIf ControllerId which is assigned 
*                              to a CAN controller, which is requested for mode
*                              transition.
*                ControllerMode: Requested mode transition
*                
* Outputs:       Std_ReturnType:E_OK: Controller mode request has been accepted
*                               E_NOT_OK: Controller mode request has not been 
*                               accepted  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetControllerMode
( 
    uint8 ControllerId, 
    CanIf_ControllerModeType ControllerMode 
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Std_ReturnType ret= E_OK;

    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETCONTROLLERMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;                          
    }
    else if(ControllerId >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;   
    }
    else
    #endif
    {
        switch(ControllerMode)
        {
            case CANIF_CS_STARTED: 

            if(CANIF_CS_SLEEP == CanIf_ControllerMode[CANIF_CONTROLLER_ID])
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                  CAN_T_WAKEUP); 
            }
            if(E_OK == ret)
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                   CAN_T_START); 
            }
            
            break;
        
            case CANIF_CS_SLEEP:
            
            if(CANIF_CS_STOPPED != CanIf_ControllerMode[CANIF_CONTROLLER_ID])
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                  CAN_T_STOP);
            }
            
            if(E_OK == ret)
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                  CAN_T_SLEEP); 
            }
                                                                                                                       
            #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING) 
            if(E_OK == ret) 
            {
                CanIf_ClearTransmitBuffer(CANIF_CONTROLLER_ID);
            }
            #endif 
            
            break;
          
            case CANIF_CS_STOPPED:
            if(CANIF_CS_SLEEP == CanIf_ControllerMode[CANIF_CONTROLLER_ID])
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                  CAN_T_WAKEUP);
            }
            if(E_OK == ret)
            {
                ret = (Std_ReturnType)Can_SetControllerMode(CANIF_CONTROLLER_ID,
                                                                    CAN_T_STOP);
            }
            
           
            #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING) 
            if(E_OK == ret) 
            {
                CanIf_ClearTransmitBuffer(CANIF_CONTROLLER_ID) ;
            }
            #endif   
 
            break;
            
            default:
            ret = E_NOT_OK;
            break;
        }
            
    }

    return ret;
 
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_GetControllerMode
*                
* Description:   This service reports about the current status of the requested 
*                CAN controller.
*
* Inputs:        ControllerId      Abstracted CanIf ControllerId which is 
*                                  assigned to a CAN controller, which is 
*                                  requested for current operation mode.  
*                ControllerModePtr Pointer to a memory location, where the 
*                                  current mode of the CAN controller will be 
*                                  stored.
*                
* Outputs:       Std_ReturnType:E_OK: Controller mode request has been accepted
*                               E_NOT_OK: Controller mode request has not been 
*                               accepted  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_GetControllerMode
( 
    uint8 ControllerId, 
    P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA) 
                                                               ControllerModePtr
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Std_ReturnType ret = E_OK;
  
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;                          
    }
    else if(ControllerId >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;    
    }
    else if(NULL_PTR == ControllerModePtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETCONTROLLERMODE_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;    
    }
    else
    #endif
    
    {
        *ControllerModePtr = (CanIf_ControllerMode[CANIF_CONTROLLER_ID]);
    }

    return ret;
 
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_SetPduMode
*                
* Description:   This service sets the requested mode at the L-PDUs of a 
*                predefined logical PDU channel.
*
* Inputs:        ControllerId   All PDUs of the own ECU connected to the 
*                               corresponding CanIf ControllerId, which is 
*                               assigned to a physical CAN controller are 
*                               addressed.  
*                PduModeRequest Requested PDU mode change 
*                               (see CanIf_PduSetModeType) 
*                
* Outputs:       Std_ReturnType:E_OK: Controller mode request has been accepted
*                               E_NOT_OK: Controller mode request has not been 
*                               accepted  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetPduMode
( 
    uint8 ControllerId,
    CanIf_PduSetModeType PduModeRequest
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Std_ReturnType ret = E_OK;
    uint8 tempMode = (uint8)CanIfPduMode[CANIF_CONTROLLER_ID]; 
      
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETPDUMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;                         
    }
    else if(ControllerId >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETPDUMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;  
    }
    else
    #endif
    {
        switch(PduModeRequest) 
        {
            case CANIF_SET_OFFLINE:
            tempMode = (uint8)CANIF_GET_OFFLINE;
            break;
        
            case CANIF_SET_ONLINE:
            tempMode = (uint8)CANIF_GET_ONLINE;
            break;
        
            case CANIF_SET_RX_OFFLINE:
            tempMode = tempMode & CANIF_RX_INDICATION_DISABLE_MASK;
            break;

            case CANIF_SET_RX_ONLINE:
            tempMode = tempMode | CANIF_RX_INDICATION_ENABLE_MASK;
            break;

            case CANIF_SET_TX_OFFLINE:
            tempMode = tempMode & CANIF_TX_REQUEST_DISABLE_MASK;
            tempMode = tempMode & CANIF_TX_NOTIFY_DISABLE_MASK;
            break;

            case CANIF_SET_TX_OFFLINE_ACTIVE:
            tempMode = tempMode & CANIF_TX_REQUEST_DISABLE_MASK;
            tempMode = tempMode | CANIF_TX_NOTIFY_ENABLE_MASK;
            break;

            case CANIF_SET_TX_ONLINE:
            tempMode = tempMode | CANIF_TX_REQUEST_ENABLE_MASK;
            tempMode = tempMode | CANIF_TX_NOTIFY_ENABLE_MASK;
            break;

            default:
            break;
        
        }
        tempMode = tempMode & CANIF_PDU_GETMODE_MASK;
        /*******************************************************************
        * PRQA S 1482
        * Uint8 cast to enum type, to fulfill the AUTOSAR type and function. 
        * This part of code is verified manually and has no impact.
        *******************************************************************/    
        CanIfPduMode[CANIF_CONTROLLER_ID] = (CanIf_PduGetModeType)tempMode;
    }    
    return ret;    
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_GetPduMode
*                
* Description:   This service reports the current mode of a requested PDU 
*                channel. 
*
* Inputs:        ControllerId   All PDUs of the own ECU connected to the 
*                               corresponding CanIf ControllerId, which is 
*                               assigned to a physical CAN controller are 
*                               addressed.  
*                PduModePtr     Pointer to a memory location, where the current 
*                               mode of the logical PDU channel will be stored. 
*                
* Outputs:       Std_ReturnType:E_OK: Controller mode request has been accepted
*                               E_NOT_OK: Controller mode request has not been 
*                               accepted  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_GetPduMode
( 
    uint8 ControllerId,
    P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr
)
{  
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Std_ReturnType ret = E_OK;

    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;                         
    }
    else if(ControllerId >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_PARAM_CONTROLLERID);
        ret = E_NOT_OK;     
    }
    else if(NULL_PTR == PduModePtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETPDUMODE_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;     
    }
    else
    #endif

    {
        *PduModePtr = CanIfPduMode[CANIF_CONTROLLER_ID];
    } 
     
    return ret;
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_Transmit
*                
* Description:   This service Transmit a can PDU
*                
*
* Inputs:        CanTxPduId   L-PDU handle of CAN L-PDU to be transmitted. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device. 
*                PduInfoPtr   Pointer to a structure with CAN L-PDU related data
*                             DLC and pointer to CAN L-SDU buffer    
*                
* Outputs:       Std_ReturnType:E_OK: request has been accepted
*                               E_NOT_OK: request has not been accepted  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_Transmit
( 
    PduIdType CanTxPduId, 
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint8 i;
    uint8 CanIfTxPduBuffer[CAN_DATA_DLC]; 
    Can_PduType CanIfTxPduObject;
    Can_ReturnType CanTxResult;
    Std_ReturnType ret;
    #if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
    CanIf_PduGetModeType tempMode; 
    #endif

    
    CanIfTxPduObject.sdu = CanIfTxPduBuffer;
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        ret = E_NOT_OK;
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_UNINIT);
            
    }
    else if(CanTxPduId >= CanIf_TotalTxPduIds)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_INVALID_TXPDUID);
        ret = E_NOT_OK;  
    }
    else if(NULL_PTR == PduInfoPtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TRANSMIT_APIID,
                        CANIF_E_PARAM_POINTER);
        ret = E_NOT_OK;  
    }
    else
    #endif
    {

        
        #if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
        tempMode = CanIfPduMode[CANIF_CANCONTROLLER_TX]; 
        #endif
        
        /* if controller is not in start or the channel is in txoffline 
           the tx request will not accept */
        if
        ((CANIF_CS_STARTED !=  CanIf_ControllerMode[CANIF_CANCONTROLLER_TX])
        #if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
        || (CANIF_GET_OFFLINE == tempMode) ||(CANIF_GET_RX_ONLINE == tempMode)
        #endif
        ) 
        {

            Dem_ReportErrorStatus(CANIF_E_STOPPED, DEM_EVENT_STATUS_FAILED);
            ret = E_NOT_OK;
        }
        else
        {   
            #if(CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON)
            if((CANIF_GET_OFFLINE_ACTIVE == tempMode)
            || (CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE == tempMode))
            {
                ret = E_OK;
                CanIf_TxConfirmation(CanTxPduId);
            }
            else
            #endif
            {
                CanIfTxPduObject.swPduHandle=CanTxPduId;

                #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
                /*So that,CanIf_SetDynamicTxId()will not be interrupted 
                by CanIf_Transmit()*/
                
                if(DYNAMIC_TXPDU == CanIfTxPduConfig[CanTxPduId].TxPduType)
                {
                    CanIfTxPduObject.id = CanIfTxPduCanIdForDynamic[CanTxPduId];
                }
                else
                #endif
                {
                    CanIfTxPduObject.id = CanIfTxPduConfig[CanTxPduId].CanId;
                }
                
                /*DLC Check,must be smaller or equal to 8*/
                if((PduInfoPtr->SduLength) > ((PduLengthType)CAN_DATA_DLC))
                {
                    CanIfTxPduObject.length = CAN_DATA_DLC;
                }
                else
                {
                    CanIfTxPduObject.length = (uint8)PduInfoPtr->SduLength;
                }
                
                for(i = 0; i < (CanIfTxPduObject.length); i++)
                {
                    CanIfTxPduObject.sdu[i] = PduInfoPtr->SduDataPtr[i];
                }
                
                CanTxResult = Can_Write((CanIfTxPduConfig[CanTxPduId].Hth), 
                                                             &CanIfTxPduObject);
                
                if(CAN_OK == CanTxResult )
                {
                    ret = E_OK;
                }
                else
                {
                    ret =  E_NOT_OK;
                }
                
                #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
                /*when CAN driver is return busy ,CAN Interface store the 
                complete CANIF Tx L-PDU in the appropriate*/
                if(CAN_BUSY == CanTxResult)
                {
                    /*CanIfTxBufferFillCount is used for counting the num of 
                    CanIfTxBufferPdu which is used*/ 
                    if(FALSE == CanIfTxBufferPDUFillflag[CanTxPduId])
                    {
                        CanIfTxBufferPDUFillflag[CanTxPduId] = TRUE;
                        CanIfTxBufferFillCount++;
                    }
                    
                    /* CANIF068:If the function CanIf_Transmit() is called and 
                    if the CanIf has to store the L-PDU in the transmit L-PDU 
                    buffer, then if the corresponding CanIfTxBuffer is already 
                    filled, the CanIf shall overwrite the older L-PDU with the 
                    recent L-PDU.*/
                    CanIf_MemCpy(CanIfTxBufferSdu[CanTxPduId],
                                 CanIfTxPduObject.sdu, 
                                 CanIfTxPduObject.length); 
                    
                    CanIfTxBufferPdu[CanTxPduId].id = CanIfTxPduObject.id;
                    CanIfTxBufferPdu[CanTxPduId].length = 
                                                        CanIfTxPduObject.length;
                    CanIfTxBufferPdu[CanTxPduId].sdu = 
                                                   CanIfTxBufferSdu[CanTxPduId];
                    CanIfTxBufferPdu[CanTxPduId].swPduHandle = CanTxPduId;   
                    
                    ret = E_OK;
                
                }
                #endif /*end of #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)*/
 
            }
        }
    }
    return ret;
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_CancelTransmit
*                
* Description:   This is a dummy API introduced for interface compatibility.
*                
*
* Inputs:        CanTxPduId   L-PDU handle of CAN L-PDU to be transmitted. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device.    
*                
* Outputs:       Std_ReturnType:Always return E_OK
*                              
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_CancelTransmit
( 
    PduIdType CanTxPduId 
)
{
    /*******************************************************************
    * PRQA S 3112   MISRA-C:2004 Rule 14.2
    * CanTxPduId is not used because this is a dummy API introduced for 
    * interface compatibility.
    * The "(void)" is to avoid generate warning information. 
    * This part of code is verified manually and has no impact.
    *******************************************************************/
    (void)CanTxPduId;
    return E_OK;
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_SetDynamicTxId
*                
* Description:   This service set dynamic id 
*
* Inputs:        CanTxPduId   L-PDU handle of CAN L-PDU to be transmitted. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device. 
*                CanId        Standard/Extended CAN ID of CAN L-PDU that shall 
*                             be transmitted    
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_SetDynamicTxId
( 
    PduIdType CanTxPduId, 
    Can_IdType CanId 
)
{
    Std_ReturnType  ret = E_OK;

    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_UNINIT);
        ret = E_NOT_OK;                          
    }
    else if((CanTxPduId >= CanIf_TotalTxPduIds) ||
                       (STATIC_TXPDU == CanIfTxPduConfig[CanTxPduId].TxPduType))
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_INVALID_TXPDUID);
        ret = E_NOT_OK;  
    }

    else if(CanId > CANIF_MAX_CANID)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_SETDYNAMICTXID_APIID,
                        CANIF_E_PARAM_CANID);
        ret = E_NOT_OK;  
    }
    else
    #endif

    {
        CANIF_ENTER_CRITICAL_SECTION(); 
        CanIfTxPduCanIdForDynamic[CanTxPduId] = CanId; 
        CANIF_LEAVE_CRITICAL_SECTION(); 
    }           
    
    return ret;
}
#endif 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ReadTxNotifStatus
*                
* Description:   This service returns the confirmation status 
*                (confirmation occured of not) of a specific 
*                static or dynamic CAN Tx L-PDU, requested by the CanTxPduId. 
*
* Inputs:        CanTxPduId   L-PDU handle of CAN L-PDU to be transmitted. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device.   
*                
* Outputs:       CanIf_NotifStatusType   Current confirmation status of the 
*                                        corresponding CAN Tx L-PDU.
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
FUNC(CanIf_NotifStatusType, CANIF_PUBLIC_CODE) CanIf_ReadTxNotifStatus
( 
    PduIdType CanTxPduId
)
{    
    CanIf_NotifStatusType ret = CANIF_NO_NOTIFICATION; 
    
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READTXNOTIFSTATUS_APIID,
                        CANIF_E_UNINIT);
    }
    else if((CanTxPduId >= CanIf_TotalTxPduIds) ||
                  (FALSE == CanIfTxPduConfig[CanTxPduId].TxPduReadNotifyStatus))
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READTXNOTIFSTATUS_APIID,
                        CANIF_E_INVALID_TXPDUID);
    }
    else
    #endif 
    {
        if(CANIF_TX_RX_NOTIFICATION == CanIfTxNotifStatus[CanTxPduId])
        {
            ret =  CANIF_TX_RX_NOTIFICATION;
            CanIfTxNotifStatus[CanTxPduId] = CANIF_NO_NOTIFICATION;
        }
    
    }
    return ret;
}
#endif   

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ReadRxNotifStatus
*                
* Description:   This service returns the indication status 
*                (indication occured of not) of a specific 
*                static or dynamic CAN Rx L-PDU, requested by the CanRxPduId. 
*
* Inputs:        CanRxPduId   L-PDU handle of CAN L-PDU to be received. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device.   
*                
* Outputs:       CanIf_NotifStatusType   Current confirmation status of the 
*                                        corresponding CAN Rx L-PDU.
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
FUNC(CanIf_NotifStatusType, CANIF_PUBLIC_CODE) CanIf_ReadRxNotifStatus
( 
    PduIdType CanRxPduId
)
{
    CanIf_NotifStatusType ret = CANIF_NO_NOTIFICATION; 
    
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXNOTIFSTATUS_APIID,
                        CANIF_E_UNINIT);
    }
    else if((CanRxPduId >= CanIf_TotalRxPduIds) || 
                  (FALSE == CanIfRxPduConfig[CanRxPduId].RxPduReadNotifyStatus))
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXNOTIFSTATUS_APIID,
                        CANIF_E_INVALID_RXPDUID);
    }
    else
    #endif  
    {
        if(CANIF_TX_RX_NOTIFICATION == CanIfRxNotifStatus[CanRxPduId])
        {
            ret =  CANIF_TX_RX_NOTIFICATION;
            CanIfRxNotifStatus[CanRxPduId] = CANIF_NO_NOTIFICATION;
        }
    }
    return ret;
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ReadRxPduData
*                
* Description:   This service provides the CAN DLC and the received data of the
*                requested CanRxPduId to the calling upper layer.
*                NOTE:This API must not be used for CanRxPduIds, which are 
*                defined to receive multiple CAN-Ids (range reception).    
*
* Inputs:        CanRxPduId   L-PDU handle of CAN L-PDU to be received. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device. 
*                PduInfoPtr   Pointer to a structure with CAN L-PDU related data
*                             DLC and pointer to CAN L-SDU buffer
*                
* Outputs:       Std_ReturnType  E_OK: Request for L-PDU data has been accepted
*                                E_NOT_OK: No valid data has been received
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
FUNC(Std_ReturnType, CANIF_PUBLIC_CODE) CanIf_ReadRxPduData
( 
    PduIdType CanRxPduId, 
    P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
)

{
    Std_ReturnType ret = E_NOT_OK;

    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_UNINIT);
    }
    else if((CanRxPduId >= CanIf_TotalRxPduIds) || 
                          (FALSE == CanIfRxPduConfig[CanRxPduId].RxPduReadData))
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_INVALID_RXPDUID);
    }
    else if(NULL_PTR == PduInfoPtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_READRXPDUDATA_APIID,
                        CANIF_E_PARAM_POINTER);
    }
    else
    #endif
    {  
        /*already has data in buffer*/
        if(CAN_DATA_DLC >= CanIfRxBufferSduLength[CanRxPduId])
        {
            #if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
            if(NULL_PTR == CanIfRxPduConfig[CanRxPduId].RxPduCanIdRangeCfg)
            #endif
            {
                /*During the call of this API the buffer of PduInfoPtr is 
                controlled by the CanIf and this buffer should not be accessed 
                for read/write from another call context. After return of this 
                call the ownership changes to the upper layer.*/
                
                CANIF_ENTER_CRITICAL_SECTION();

                CanIf_MemCpy(PduInfoPtr->SduDataPtr,
                             CanIfRxBufferSduData[CanRxPduId],
                             (CanIfRxBufferSduLength[CanRxPduId]));          
                PduInfoPtr->SduLength = CanIfRxBufferSduLength[CanRxPduId];

                CANIF_LEAVE_CRITICAL_SECTION();

                ret = E_OK ;
            }
        }

    }
    return ret;
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_GetVersionInfo
*                
* Description:   This service returns the version information of the called 
*                CAN Interface module    
*
* Inputs:        VersionInfo  Pointer to where to store the version information
*                             of this module.DLC and pointer to CAN L-SDU buffer  
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CANIF_PUBLIC_VERSION_INFO_API)
FUNC(void, CANIF_PUBLIC_CODE) CanIf_GetVersionInfo
( 
    P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA) VersionInfo
)
{
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(NULL_PTR == VersionInfo)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_GETVERSIONINFO,
                        CANIF_E_PARAM_POINTER);                          
    }
    else
    #endif

    {
        /* Copy the vendor Id */
        VersionInfo->vendorID = CANIF_VENDOR_ID_VALUE;
        /* Copy the module Id */
        VersionInfo->moduleID = CANIF_MODULE_ID_VALUE;
        /* Copy the instance Id */
        VersionInfo->instanceID = CANIF_INSTANCE_ID_VALUE_0;
        /* Copy Software Major Version */
        VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION_VALUE;
        /* Copy Software Minor Version */
        VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION_VALUE;
        /* Copy Software Patch Version */
        VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION_VALUE;
    }
 
}
#endif

/*******************************************************************************
*   Global callback  Function Define
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_TxConfirmation
*                
* Description:   This service confirms a previously successfully processed 
*                transmission of a CAN TxPDU. 
*                
* Inputs:        CanTxPduId   L-PDU handle of CAN L-PDU to be transmitted. 
*                             This handle specifies the corresponding CAN L-PDU 
*                             ID and implicitly the CAN Driver instance as well
*                             as the corresponding CAN controller device.   
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANIF_PUBLIC_CODE) CanIf_TxConfirmation
( 
    PduIdType CanTxPduId
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    PduIdType handle;
    
    #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
    Can_HwHandleType hth;
    #endif
    #endif
    Can_ReturnType Can_RetVal;
    #if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
    uint8 tempMode;
    #endif

    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TXCONFIRMATION_APIID,
                        CANIF_E_UNINIT);
    }
    else if(CanTxPduId >= CanIf_TotalTxPduIds)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_TXCONFIRMATION_APIID,
                        CANIF_E_INVALID_TXPDUID);
    }
    else
    #endif

    {     
        #if (CANIF_PDU_CHANNEL_MODE_CONTROL == STD_ON) 
        tempMode = (uint8)CanIfPduMode[CANIF_CANCONTROLLER_TX];
        if(0 != (tempMode & CANIF_TX_NOTIFY_ENABLE_MASK))
        #endif 
        {    
            if(NULL_PTR != CanIfTxPduConfig[CanTxPduId].TxConfirmation)
            {
                #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
                (CanIfTxPduConfig[CanTxPduId].TxConfirmation)
                                (CanIfTxPduConfig[CanTxPduId].UpperLayerHandle);
                #else
                (CanIfTxPduConfig[CanTxPduId].TxConfirmation)(CanTxPduId);
                #endif
            }  
            /*
            If configuration parameters CANIF_READTXPDU_NOTIFY_STATUS_API 
            (CANIF609_Conf) and CANIF_READTXPDU_NOTIFY_STATUS CANIF589_Conf for 
            the transmitted L-PDU are set to TRUE, and if CanIf_TxConfirmation() 
            is called, then the CanIf shall set the notification status for the 
            transmitted L-PDU.
            */
            #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
            if(TRUE == CanIfTxPduConfig[CanTxPduId].TxPduReadNotifyStatus)
            {
                CanIfTxNotifStatus[CanTxPduId] = CANIF_TX_RX_NOTIFICATION;
            }
            #endif

            #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            /*After one HTH is free,CANIF shoule initiate a new transmit request 
            of that pending CanIf Tx L-PDU*/
            if(0 != CanIfTxBufferFillCount)
            {
                #if(CANIF_FILTER_TYPE_LINEAR == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
                for(handle = 0;handle < CanIf_TotalTxPduIds;handle++)
                {
                    if((CanIfTxPduConfig[handle].Hth == 
                                               CanIfTxPduConfig[CanTxPduId].Hth)
                    &&(TRUE == CanIfTxBufferPDUFillflag[handle]))
                    {
                        Can_RetVal = Can_Write(CanIfTxPduConfig[handle].Hth,
                                                &CanIfTxBufferPdu[handle]);
                        if(CAN_OK == Can_RetVal)
                        {
                            CanIfTxBufferPDUFillflag[handle] = FALSE;
                            CanIfTxBufferFillCount--;
                        }
                    
                        break; /*jump out ,only send once*/
                    }
                }
                #endif
                
                
                /* index search method,
                */
                #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
                hth =  CanIfTxPduConfig[CanTxPduId].Hth;
                
                /* caculate offset  hth is after hrh */
                if(hth >= CanIfInitNumberofHrh)
                {
                    hth = hth  - CanIfInitNumberofHrh;
                    
                    for(handle = CanIfHthFirstTxPduID[hth]; 
                    CANIF_LAST_HOH_PDUID != handle; 
                    handle = CanIfTxPduConfig[handle].HthNextTxPduID)
                    {
                        if((CanIfTxPduConfig[handle].Hth == 
                                               CanIfTxPduConfig[CanTxPduId].Hth)
                        &&(TRUE == CanIfTxBufferPDUFillflag[handle]))
                        {
                            Can_RetVal = Can_Write(CanIfTxPduConfig[handle].Hth,
                                                    &CanIfTxBufferPdu[handle]);
                            if(CAN_OK == Can_RetVal)
                            {
                                CanIfTxBufferPDUFillflag[handle] = FALSE;
                                CanIfTxBufferFillCount--;
                            }
                            break; /*jump out ,only send once*/
                        }
                    }
                    
                }
                #endif
   
            }
            #endif /*end of #if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)*/ 

        }

    }
   
}
  
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_RxIndication
*                
* Description:   This service indicates a successful reception of a received CAN 
*                Rx L-PDU to the CanIf after passing all filters and validation 
*                checks. 
*                
* Inputs:        Hrh         ID of the corresponding Hardware Object 
*                            Range: 0..(total number of HRH -1) 
*                CanId       Standard/Extended CAN ID of CAN L-PDU that has been 
*                            successfully received 
*                CanDlc      Data Length Code (length of CAN L-PDU payload) 
*                CanSduPtr   Pointer to received L-SDU (payload)    
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANIF_PUBLIC_CODE) CanIf_RxIndication
( 
    Can_HwHandleType Hrh, 
    Can_IdType CanId,
    uint8 CanDlc,
    P2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    PduIdType    handle;
    PduIdType    canIfRxPduId;
    PduInfoType  CanIf_PduRRxPduInfo;
    uint8 handleGetFlag = 0;
    #if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
    uint8 tempMode;
    #endif
    uint8 dlcResult;
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    Std_ReturnType parResult;
    
    parResult = CanIf_RxParCheck(Hrh, CanId, CanDlc, CanSduPtr);
    if(E_OK == parResult)
    #endif
    {     
        #if (STD_ON == CANIF_PDU_CHANNEL_MODE_CONTROL)
        tempMode = (uint8)CanIfPduMode[CANIF_CANCONTROLLER_RX];
        if(0 != (tempMode & CANIF_RX_INDICATION_ENABLE_MASK))
        #endif
        {
            #if(STD_ON == CANIF_HRH_RANGE_FILTER)
            if(((1UL == (CanId & CANIF_MSK_EXT_ID_MSB)) 
            && (STANDARD_CAN == CANIF_HRH_CANID_TYPE))
            || ((0UL == (CanId & CANIF_MSK_EXT_ID_MSB))
            && (EXTENDED_CAN == CANIF_HRH_CANID_TYPE))
            || (CanId < CANIF_HRH_LOWER_CANID)
            || (CanId > CANIF_HRH_UPPER_CANID))
            {
            }
            else
            #endif

            {
         
                #if(CANIF_FILTER_TYPE_INDEX == \
                                             CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
                for(handle = CanIfHrhFirstRxPduID[Hrh]; 
                    CANIF_LAST_HOH_PDUID != handle; 
                    handle = CanIfRxPduConfig[handle].HrhNextRxPduID)
                #else
                for(handle = 0; handle < CanIf_TotalRxPduIds; handle++)
                #endif

                {
                    #if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
                    if(NULL_PTR != CANIF_RXPDU_RANGECFG)
                    {
                        if((CanId >= CANIF_RXPDU_RANGECFG->RxPduCanIdRangeLowerCanId)
                        &&(CanId <= CANIF_RXPDU_RANGECFG->RxPduCanIdRangeUpperCanId))
                        {
                            handleGetFlag = 1;
                        }
                    }
                    else
                    #endif
                    {
                        if(((CanIfRxPduConfig[handle].CanId) == CanId)
                          &&((CanIfRxPduConfig[handle].Hrh) == Hrh))
                        {
                            handleGetFlag = 1;
                        }
                    }
                    if(1 == handleGetFlag)
                    {
                        break;
                    }
                }
                #if(CANIF_FILTER_TYPE_INDEX == \
                                            CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)

                if(CANIF_LAST_HOH_PDUID != handle)
                #else

                if(handle < CanIf_TotalRxPduIds)

                #endif
                {
                    #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
                    canIfRxPduId = CanIfRxPduConfig[handle].UpperLayerHandle ;
                    #else 
                    canIfRxPduId = handle;
                    #endif

                    dlcResult = CanIf_DlcCheck(CanDlc, handle, 
                                                &CanIf_PduRRxPduInfo.SduLength);
                    if(E_NOT_OK == dlcResult)
                    {
                         /*abort this message*/
                        Dem_ReportErrorStatus(
                                              CANIF_E_INVALID_DLC, 
                                              DEM_EVENT_STATUS_FAILED
                                             );
                    }
                    else
                    {
                        /**********************************************************
                        * PRQA S 0311   MISRA-C:2004 Rule 11.5
                        * Pointer cast lost const qualification.
                        * This cast is to fulfill the AUTOSAR RxIndication API 
                        * between CanIf and uplayer service moudle.
                        * This part of code is verified manually and has no impact.
                        **********************************************************/
                        CanIf_PduRRxPduInfo.SduDataPtr = (uint8 *)CanSduPtr;
                        
                        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
                        if(TRUE == CanIfRxPduConfig[handle].RxPduReadNotifyStatus)
                        {
                            CanIfRxNotifStatus[handle] = CANIF_TX_RX_NOTIFICATION;
                        }
                        #endif
                        
                        #if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
                            
                        if(TRUE == CanIfRxPduConfig[handle].RxPduReadData)
                        {
                            #if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
                            /*CanIf_ReadRxPduData must not be used for 
                            CanRxPduIds, which are defined to receive multiple 
                            CAN-Ids (range reception)*/
                            if(NULL_PTR == 
                                    CanIfRxPduConfig[handle].RxPduCanIdRangeCfg)
                            #endif
                            {
                                /*If the CanIf has accepted a L-PDU received 
                                via CanIf_RxIndication() during DLC check, 
                                the CanIf shall copy the number of bytes 
                                according to the configured DLC valueto the 
                                static receive buffer, if configured for that 
                                L-PDU , or allow copying the data to the upper 
                                layer modules.*/
                  
                                CanIf_MemCpy(
                                              CanIfRxBufferSduData[handle],
                                              CanSduPtr,
                                              CanIf_PduRRxPduInfo.SduLength);    

                                CanIfRxBufferSduLength[handle] = 
                                                  CanIf_PduRRxPduInfo.SduLength;  
                            }
                        }
                        #endif
                        
                        #if (STD_ON==CANIF_RX_PDU_RANGE_CANID)
                        if(NULL_PTR != CANIF_RXPDU_RANGECFG)
                        {
                            if(NULL_PTR != CANIF_RXPDU_RANGECFG->RangeRxIndication)
                            {
                                (CANIF_RXPDU_RANGECFG->RangeRxIndication)
                                   ( canIfRxPduId, CanId, &CanIf_PduRRxPduInfo);          
                            }
                        }
                        else
                        #endif
                        {
                            if(NULL_PTR != CanIfRxPduConfig[handle].RxIndication)
                            {
                                (CanIfRxPduConfig[handle].RxIndication)
                                           (canIfRxPduId, &CanIf_PduRRxPduInfo);
                            
                            }
                        }
                        

                    }
        
                }

            }
              
        }

    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_CancelTxConfirmation
*                
* Description:   This service confirms a previously successfully performed 
*                cancellation of a pending Tx L-PDU transmit request.
*                
*
* Inputs:        PduInfoPtr   Pointer to a structure with CAN L-PDU related data
*                             DLC and pointer to CAN L-SDU buffer    
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON) 
FUNC(void, CANIF_PUBLIC_CODE) CanIf_CancelTxConfirmation
( 
    P2CONST(Can_PduType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
)
{
    PduIdType CanTxPduId;
    
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CANCELTXCONFIRMATION_APIID,
                        CANIF_E_UNINIT);
    }
    else if(NULL_PTR == PduInfoPtr)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CANCELTXCONFIRMATION_APIID,
                        CANIF_E_PARAM_POINTER);      
    }
    else
    #endif
    {
        CanTxPduId = PduInfoPtr->swPduHandle;
        #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
        if(CanTxPduId >= CanIf_TotalTxPduIds)
        {
            Det_ReportError(CANIF_MODULE_ID_VALUE,
                            CANIF_INSTANCE_ID_VALUE_0,
                            CANIF_CANCELTXCONFIRMATION_APIID,
                            CANIF_E_INVALID_TXPDUID);
        }
        else
        #endif
        {
            #if(STD_ON == CANIF_PUBLIC_TX_BUFFERING)
            /*CanIfTxBufferFillCount is used for counting the num of 
            CanIfTxBufferPdu which is used*/ 
            if(FALSE == CanIfTxBufferPDUFillflag[CanTxPduId])
            {
                CANIF_ENTER_CRITICAL_SECTION(); 
                CanIfTxBufferPDUFillflag[CanTxPduId] = TRUE;
                CanIfTxBufferFillCount++;
                
                /*CANIF054: When callback notification service 
                CanIf_CancelTxConfirmation() is called, 
                the CanIf shall store the aborted old L-PDU, which is referenced
                in parameter PduInfoPtr of CanIf_CancelTxConfirmation(), inside 
                its transmit L-PDU buffer as long it is configured and free.*/  
                /*This way of L-PDU storage ensures to keep the latest data of
                several pending transmit L-PDUs with the same L-PDU handle 
                inside the CanIf's transmit L-PDU buffers.*/ 
                CanIf_MemCpy(CanIfTxBufferSdu[CanTxPduId],
                             PduInfoPtr->sdu, PduInfoPtr->length); 
                
                CanIfTxBufferPdu[CanTxPduId].id = PduInfoPtr->id;
                CanIfTxBufferPdu[CanTxPduId].length = PduInfoPtr->length;
                CanIfTxBufferPdu[CanTxPduId].sdu = CanIfTxBufferSdu[CanTxPduId];
                CanIfTxBufferPdu[CanTxPduId].swPduHandle 
                                                      = PduInfoPtr->swPduHandle;   
                CANIF_LEAVE_CRITICAL_SECTION();  
            }
            #endif

        }
        
    }

}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ControllerBusOff
*                
* Description:   This service indicates a Controller BusOff event referring to 
*                the corresponding CAN Controller.
*                
*
* Inputs:        Controller   CAN controller, where a BusOff occured     
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerBusOff
( 
    uint8 Controller 
)
{         
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_UNINIT);
    }
    else if(Controller >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    }
    else
    #endif

    {
        /*******************************************************************
        * PRQA S 3138   MISRA-C:2004 Rule 14.3
        * PRQA S 3141
        * If not configed by user,CANIF_USERCTRLBUSOFF_FUN is Null.
        * This part of code is verified manually and has no impact.
        *******************************************************************/
        CANIF_DISPATCH_USERCTRLBUSOFF_DEFINED_NAME;  
          
    }
     
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ControllerWakeUp
*                
* Description:   This service indicates a Controller wakeup event referring to 
*                the corresponding CAN Controller.
*                
*
* Inputs:        Controller   CAN controller, where a wakeup occured     
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerWakeUp
( 
    uint8 Controller 
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    #if(CANIF_DISPATCH_UL_OSEKNM != CANIF_DISPATCH_USERSETWAKEUPEVENT_UL)  
    EcuM_WakeupSourceType WakeupSourceRef = 0;
    #endif
    
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)

    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_UNINIT);
    }
    else if(Controller >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERBUSOFF_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    }
    else
    #endif
    {
        #if(CANIF_DISPATCH_UL_OSEKNM != CANIF_DISPATCH_USERSETWAKEUPEVENT_UL)  
        /* get wakeup source here */
        #endif    
        
        
        /*******************************************************************
        * PRQA S 3138   MISRA-C:2004 Rule 14.3
        * PRQA S 3141
        * If not configed by user,CANIF_USERWAKEUP_FUN is Null.
        * This part of code is verified manually and has no impact.
        *******************************************************************/ 
        CANIF_DISPATCH_USERSETWAKEUPEVENT_DEFINED_NAME;
    }
}
                            
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ControllerModeIndication
*                
* Description:   This service indicates a Controller state transition event 
*                referring to the corresponding CAN Controller.
*                
* Inputs:        ControllerId:CAN controller, which state has been transitioned.
*                ControllerMode:  Mode to which the CAN controller transitioned 
*                
* Outputs:       None  
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerModeIndication
( 
    uint8 Controller,
    CanIf_ControllerModeType ControllerMode
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    #if (STD_ON == CANIF_PUBLIC_DEV_ERROR_DETECT)
    if(CANIF_UNINITIALIZED == CanIf_InitStatus)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERMODEINDICATION_APIID,
                        CANIF_E_UNINIT);
    }
    else if(Controller >= CANIF_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CANIF_MODULE_ID_VALUE,
                        CANIF_INSTANCE_ID_VALUE_0,
                        CANIF_CONTROLLERMODEINDICATION_APIID,
                        CANIF_E_PARAM_CONTROLLER);
    }
    else
    #endif  
    {
        switch(ControllerMode)
        {
            case CANIF_CS_SLEEP:
            CanIf_ControllerMode[Controller] = CANIF_CS_SLEEP;  
            break;

            case CANIF_CS_STARTED: 
            CanIf_ControllerMode[Controller] = CANIF_CS_STARTED;   
            break;

            case CANIF_CS_STOPPED:
            CanIf_ControllerMode[Controller] = CANIF_CS_STOPPED;     
            break;

            default:
            
            break;
        }

    }      

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CanIf_ClearTransmitBuffer
*                
* Description:   Clear the  CanIfTxBufferPDUFillflag of CanTxPdu which 
*                belong to the specific  controller          
* Inputs:        ControllerId : controller which wanted to clear the buffer
*                
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/


FUNC(void, CANIF_PRIVATE_CODE)  CanIf_ClearTransmitBuffer
(
    uint8 ControllerId
)
{
#if CANIF_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    #if(STD_ON == CANIF_PUBLIC_TX_BUFFERING) 
    Can_HwHandleType CanTxPduId;
    for(CanTxPduId = 0; CanTxPduId < CanIf_TotalTxPduIds; CanTxPduId++)
    {
        if(CANIF_CONTROLLER_ID == CANIF_CANCONTROLLER_TX)
        {
            if(TRUE == CanIfTxBufferPDUFillflag[CanTxPduId])
            {
                CanIfTxBufferFillCount--;
                CanIfTxBufferPDUFillflag[CanTxPduId] = FALSE;
            }    
        }
    }
    #endif
}



#define CANIF_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
                           
