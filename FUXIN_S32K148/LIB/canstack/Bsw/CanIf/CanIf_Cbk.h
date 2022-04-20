/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Cbk.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Interface module call back head File
*   Author          : HeYang
********************************************************************************
*   Description     : The header file CanIf_Cbk.h contains the declaration of 
*                     callback functions which is called by the Can module                     
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

#ifndef _CANIF_CBK_H_
#define _CANIF_CBK_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "CanIf_Cfg.h"
#include "CanIf_Type.h"

/*******************************************************************************
*   Callback Function Declaration 
*******************************************************************************/
#define CANIF_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_TxConfirmation
( 
    PduIdType CanTxPduId
);

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_RxIndication
( 
    Can_HwHandleType Hrh, 
    Can_IdType CanId,
    uint8 CanDlc,
    P2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
);
#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON) 
extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_CancelTxConfirmation
( 
    P2CONST(Can_PduType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);
#endif

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerBusOff
( 
    uint8 Controller 
);

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerWakeUp
( 
    uint8 Controller 
); 

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerModeIndication
( 
    uint8 Controller,
    CanIf_ControllerModeType ControllerMode
);

#define CANIF_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
                           
#endif/* _CANIF_CBK_H_ */

