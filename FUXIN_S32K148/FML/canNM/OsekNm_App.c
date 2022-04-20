/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : OsekNm_App.c
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
#include "Can.h"
#include "CanIf.h"
#include "Com.h"
extern uint8 networkFlag;
/*******************************************************************************
*   Call back functions for OsekNm Module
*******************************************************************************/
/*Called only when NM started*/
void ApplNmCanStart(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
    Com_RxStart();
    Com_TxStart();
}
/*************************************************************/
/*Perform when enter limphome mode*/
void ApplNmCanLimpHomeStart(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
/*Perform when Terror TimeOut.*/
void ApplNmLimpHomeState(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
/*Perform when Exit LimpHome State*/
void ApplNmCanLimpHomeEnd(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
/*indicates bus off error occured*/
void ApplNmBusOff(const nmIndexType nmChannelHandle)
{
    /*Stop Com Tx (and Rx)*/
    (void)nmChannelHandle;
    /*Add App code here*/
//    Com_RxStop();
    Com_TxStop();
}
/*************************************************************/
/*indicate end of bus off error */
void ApplNmBusOffEnd(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
    Com_RxStart();
    Com_TxStart();
}
/*************************************************************/
/*This callback function is performed when busOff recovery successed.*/
void ApplNmBusOffRecoverySuccess(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
void ApplNmCanBusOffRecoveryFail(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
	/*Bus Off recovery failed */
   /*Add App code here*/
}

/*************************************************************/
/*This callback sets the communication hardware (CAN controller, bus transceiver)
to a state from which they can be woken up by the CAN bus.*/
void ApplNmCanSleep(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}

/*************************************************************/
/*indicates can bus wake up*/
void ApplNmCanWakeUp(const nmIndexType nmChannelHandle)
{
    /*Be sure Can Trv or Can controller work normal*/
    /*Set CANcontroller started mode*/
	networkFlag = 1;
    CanIf_SetControllerMode(NmToLogCanChn(nmChannelHandle),CANIF_CS_STARTED);
}
/*************************************************************/
void ApplNmWaitBusSleepCancel(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
    Com_RxStart();
    Com_TxStart();
}
/*************************************************************/
void ApplNmWaitBusSleep(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
//    Com_RxStop();
    Com_TxStop();
}
/*************************************************************/
void ApplNmShutDown(const nmIndexType nmChannelHandle)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
void ApplNmRingIndication(const nmIndexType nmChannelHandle,const nmNetIdType SourceID)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}
/*************************************************************/
void ApplNmLimpHIndication(const nmIndexType nmChannelHandle,const nmNetIdType SourceID)
{
    (void)nmChannelHandle;
    /*Add App code here*/
}

#if(NM_ACK_CHECK == STD_ON)
	/*************************************************************/
	void ApplNmAckRecoveryStart(const nmIndexType nmChannelHandle)
	{
	    CanNm_Silent(nmChannelHandle);	
	}
	/*************************************************************/
	void ApplNmAckRecoveryEnd(const nmIndexType nmChannelHandle)
	{
	    CanNm_Talk(nmChannelHandle);
	    
	}
	#endif
