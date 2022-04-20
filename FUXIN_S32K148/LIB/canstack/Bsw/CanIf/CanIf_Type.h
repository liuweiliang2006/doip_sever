/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Type.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Interface module type definitions head File
*   Author          : HeYang
********************************************************************************
*   Description     : The header file CanIf_Type.h contains the  common type 
*                     definitions of the module Can Interface                    
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
#ifndef _CANIF_TYPE_H_
#define _CANIF_TYPE_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/

/*******************************************************************************
*   Typedef 
*******************************************************************************/
/*Operating modes of the CAN Controller and CAN Driver*/
typedef enum  
{
    /*UNINIT mode. Default mode of the CAN Driver and all CAN controllers 
    connected to one CAN network after power on. */
    CANIF_CS_UNINIT = 0,
    /*SLEEP mode. At least one of all CAN controllers connected to one CAN 
    network are set into the SLEEP mode and can be woken up by request of the 
    CAN Driver or by a network event (must be supported by CAN hardware) */
    CANIF_CS_SLEEP = 1,     
    /*STARTED mode. All CAN controllers connected to one CAN network are started

    by the CAN Driver and in full-operational mode. */
    CANIF_CS_STARTED = 2,   
    /*STOPPED mode. At least one of all CAN controllers connected to one CAN 
    network is halted and does not operate on the network. */
    CANIF_CS_STOPPED = 3                       

}CanIf_ControllerModeType;  


/*Request for PDU channel group. The request type of the channel defines it's 
transmit or receive activity. Communication direction (transmission and/or 
reception) of the channel can be controlled separately or together
by upper layers.*/
typedef enum
{
    /*0000,Channel shall be set to the offline mode => no transmission and 
    reception */
    CANIF_SET_OFFLINE           = 0,      
    /*0111,Channel shall be set to online mode => full operation mode */
    CANIF_SET_ONLINE            = 1, 
    /*0110,Receive path of the corresponding channel shall be disabled*/
    CANIF_SET_RX_OFFLINE        = 2,  
    /*1001,Receive path of the corresponding channel shall be enabled*/
    CANIF_SET_RX_ONLINE         = 3,    
    /*0001,Transmit path of the corresponding channel shall be disabled*/
    CANIF_SET_TX_OFFLINE        = 4,  
    /*0100,Transmit path of the corresponding channel shall be set to the 
    offline active mode => notifications are processed but transmit
    requests are blocked.*/
    CANIF_SET_TX_OFFLINE_ACTIVE = 5,
     /*1110,Transmit path of the corresponding channel shall be enabled*/
    CANIF_SET_TX_ONLINE         = 6             
}CanIf_PduSetModeType ;                  


 /*Status of the PDU channel group. Current mode of the channel defines
 its transmit or receive activity. Communication direction (transmission and
 /or reception) of the channel can be controlled separately or together
 by upper layers*/
typedef enum
{
    /*000,Channel is in the offline mode => no transmission and reception*/
    CANIF_GET_OFFLINE                  = 0,
    /*100,Transmit path of the corresponding channel is in the offline active 
    mode => transmit notifications are processed but transmit requests are 
    blocked.The receive path is disabled.*/
    CANIF_GET_OFFLINE_ACTIVE           = 4,
    /*101,Transmit path of the corresponding channel is in the offline active 
    mode => transmit notifications are processed but transmit requests are 
    blocked.The receive path is enabled.*/
    CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE = 5,  
    /*111,Channel is in the online mode => full operation mode*/
    CANIF_GET_ONLINE                   = 7, 
    /*001,Receive path of the corresponding channel is enabled and transmit path
    is disabled.*/
    CANIF_GET_RX_ONLINE                = 1, 
    /*110,Transmit path of the corresponding channel is enabled and receive path
    is disabled.*/
    CANIF_GET_TX_ONLINE                = 6                  
}CanIf_PduGetModeType ;                 

/*Return value of CAN L-PDU notification status.*/  
typedef enum
{
    /*No transmit or receive event occurred for the requested L-PDU.*/
    CANIF_NO_NOTIFICATION    = 0,   
    /*The requested Rx/Tx CAN L-PDU was successfully transmitted or received.*/
    CANIF_TX_RX_NOTIFICATION = 1             
}CanIf_NotifStatusType ;                 
 
#endif/* _CANIF_TYPE_H_  */