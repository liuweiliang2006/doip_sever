/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can.c
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : CAN Driver module Source File
*   Author          : Hirain
********************************************************************************
*   Description     : Implementation of CAN Driver
*
********************************************************************************
*   Limitations     : only used for S32K14 FlexCAN moudle
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    17/11/2016    Suyun.Ying    N/A          Original
*   01.01.00    17/5/2018     ning.chen     N/A          EAS422_S32K14XCAN_20180517_01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can.h"
#include "CanIf_Cbk.h"/*CAN036*/
#include "Bsw_Common.h"
#include "SchM_Can.h"

void set_busoff_times_fml(void);
/*CAN397*/
#if(STD_ON == CAN_OS_COUNTER_USED)
#include "Os.h"
#endif

#if (STD_ON == CAN_DEV_ERROR_DETECT)
#include "Det.h"
#endif


/*******************************************************************************
*   Version Check
*******************************************************************************/
/*CAN111*/
#if(STD_ON == CAN_VERSION_CHECK)
/* check Version with other import module */


/* check Version with cfg file */
#if ((CAN_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION_CFG) || \
   (CAN_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION_CFG))
#error "AutoSar Version Numbers of Can and its cfg file are different"
#endif

#if ((CAN_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION_CFG) || \
   (CAN_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION_CFG))
#error "SW Version Numbers of Can and its cfg file are different"
#endif

#endif/*#if(STD_ON == CAN_PRIVATE_AR_VERSION_CHECK)*/

/*******************************************************************************
*   Macro
*******************************************************************************/
#if((CAN_CONFIG_VARIANTS == STD_CONFIG_VARIANTS_PRECOMPILE) && (1 == CAN_USED_CONTROLLER_NUM))
#define CAN_SINGLE_NETWORK_OPTIMIZE    STD_ON
#else
#define CAN_SINGLE_NETWORK_OPTIMIZE    STD_OFF
#endif



#if(STD_ON == CAN_SINGLE_NETWORK_OPTIMIZE)
#define CAN_CONTROLLER_ID           (0)
#else
#define CAN_CONTROLLER_ID           (Controller)
#endif


#define CAN_MAX_INT_NEST_COUNT          (250)
#define CAN_NO_INT_MB                   (255)

/*******************************************************************************
*   Local Data Declaration
*******************************************************************************/
#define CAN_START_SEC_VAR_INIT_8
#include "MemMap.h"
/*CAN103*/
VAR(Std_InitStateType, CAN_VAR)  Can_InitStatus = STD_UNINITIALIZED;
STATIC VAR(uint8, CAN_PRIVATE_DATA) CanGlobalInterruptCount;
#define CAN_STOP_SEC_VAR_INIT_8
#include "MemMap.h"

#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define CAN_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/* CAN Controller Base Address */
STATIC CONST(uint32, CAN_CONST) CanBasisAddress[TOTAL_CAN_MODULE_NUM] =
{
#if(CAN_SUPPORT_MCU == CAN_S32K_142)
    0x40024000UL,
    0x40025000UL
#elif(CAN_SUPPORT_MCU == CAN_S32K_144)
    0x40024000UL,
    0x40025000UL,
    0x4002B000UL
#elif(CAN_SUPPORT_MCU == CAN_S32K_146)
    0x40024000UL,
    0x40025000UL,
    0x4002B000UL
#elif(CAN_SUPPORT_MCU == CAN_S32K_148)
    0x40024000UL,
    0x40025000UL,
    0x4002B000UL
#else
#endif
};


/* CAN Controller MB Number */
STATIC CONST(uint8, CAN_CONST) CanMBNumber[TOTAL_CAN_MODULE_NUM] =
{
#if(CAN_SUPPORT_MCU == CAN_S32K_142)
    32,
    16
#elif(CAN_SUPPORT_MCU == CAN_S32K_144)
    32,
    16,
    16
#elif(CAN_SUPPORT_MCU == CAN_S32K_146)
    32,
    32,
    16
#elif(CAN_SUPPORT_MCU == CAN_S32K_148)
    32,
    32,
    32
#else
#endif

};

#if(STD_ON == CAN_CANFD_SUPPORT)
/* CAN Controller MB Number */
STATIC CONST(boolean, CAN_CONST) CanFdSupport[TOTAL_CAN_MODULE_NUM] =
{
#if(CAN_SUPPORT_MCU == CAN_S32K_142)
    TRUE,
    FALSE
#elif(CAN_SUPPORT_MCU == CAN_S32K_144)
    TRUE,
    FALSE,
    FALSE
#elif(CAN_SUPPORT_MCU == CAN_S32K_146)
    TRUE,
    TRUE,
    FALSE
#elif(CAN_SUPPORT_MCU == CAN_S32K_148)
    TRUE,
    TRUE,
    TRUE
#else
#endif

};
#endif


#define CAN_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
*   Local Functions declare
*******************************************************************************/
#define CAN_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, CAN_CODE) Can_SetID
(
    const Can_IdType  CanId,
    const uint8 Dlc,
    const boolean isExtendedCanId,
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg
);

STATIC FUNC(void, CAN_CODE) Can_ClearIntFlag
(
    const uint8 phyController,
    const uint8 MBIndex
);

#if(STD_ON == CAN_TXRX_POLLING_SUPPORT)
STATIC FUNC(uint8, CAN_CODE) Can_GetIntFlag
(
    const uint8 phyController,
    const uint8 MBIndex
);
#endif

STATIC FUNC(void, CAN_CODE) Can_Controller_Transmit_Abort
(
    const uint8 Controller
);

STATIC FUNC(void, CAN_CODE) Can_RxObject_handler
(
    const uint8 Controller,
    const uint8 MBIndex,
    const Can_HwHandleType Hrh
);
STATIC FUNC(uint8, CAN_CODE) Can_GetIntMBNum
(
    const uint8 PhyController
);

#if(STD_OFF == CAN_OS_COUNTER_USED)
STATIC FUNC(Can_ReturnType, CAN_CODE)   Can_TimeOutCheck
(
    const uint32 cnt
);
#else
STATIC FUNC(Can_ReturnType, CAN_CODE)   Can_TimeOutCheck
(
    const uint32 initCnt,
    const uint32 cnt
);
#endif

STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerFreeze
(
    const uint8 Controller
);
STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerStart
(
    const uint8 Controller
);
STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerStop
(
    const uint8 Controller
);

/*******************************************************************************
*   Local Functions define
*******************************************************************************/

#define CANDRV_DEBUG 0
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetID
*
* Description:   used to set id register
* Inputs:        PhyController, MBIndex,Id
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_CODE) Can_SetID
(
    const Can_IdType  CanId,
    const uint8 Dlc,
    const boolean isExtendedCanId,
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint32 tempId = CanId;
    uint8 MBLength = Dlc;

    /* Standrad Id */
    if(FALSE == isExtendedCanId)
    {
        tempId = tempId & CAN_STD_MAX_CANID;
        tempId = tempId << CAN_STD_POS;

    }
    else
    {
        /* Extended Id */
        tempId = (uint32)(tempId & CAN_EXT_MAX_CANID);
        MBLength = MBLength | CAN_SRR_MASK | CAN_IDE_MASK;
    }


    Can_MB_Reg->Id = tempId;
    Can_MB_Reg->Length = MBLength;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_ClearIntFlag
*
* Description:   used to clear interrupt flags
* Inputs:        PhyController, MBIndex
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_CODE) Can_ClearIntFlag
(
    const uint8 phyController,
    const uint8 MBIndex
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint32 shiftValue = MBIndex;

    shiftValue = (uint32)(1UL << shiftValue);
    CAN_IFLAG1(phyController) = shiftValue;
}

#if(STD_ON == CAN_TXRX_POLLING_SUPPORT)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetIntFlag
*
* Description:   used to get interrupt flags  set or not?
* Inputs:        PhyController, MBIndex
*
* Outputs:       0:the flag is not set
*                1:the flag is set
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(uint8, CAN_CODE) Can_GetIntFlag
(
    const uint8 phyController,
    const uint8 MBIndex
)
{
    uint32 intFlag;
    uint8 retflag = 0;

    intFlag = CAN_IFLAG1(phyController);
    intFlag = intFlag >> MBIndex;
    intFlag = intFlag & 0x01UL;
    if(1 == intFlag)
    {
        retflag = 1;
    }

    return retflag;
}

#endif
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetIntMBNum
*
* Description:   used for confim the smallest MB whose interrupt flag is  already set
*
* Inputs:         PhyController
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(uint8, CAN_CODE) Can_GetIntMBNum
(
    const uint8 PhyController
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint8 MBIndex ;
    uint8 temIndex = CAN_NO_INT_MB;
    uint32 temp;
    uint32 intflag1;


    intflag1 = CAN_IFLAG1(PhyController);

    if(0x0UL != intflag1)
    {
        for(MBIndex = 0; MBIndex < CanMBNumber[PhyController]; MBIndex++)
        {
            temp = MBIndex;
            temp = (uint32)(1 << temp);
            temp = temp & intflag1;

            if(0 != temp)
            {
                temIndex = MBIndex;
                break;
            }
        }
    }
    else
    {
        temIndex = CAN_NO_INT_MB;
    }
    return temIndex;
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_RxObject_handler
*
* Description:      This function is used for handle the success RX indication
*
* Inputs:            Controller, MBIndex
*
* Outputs:          None
*
* Limitations:     None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_CODE) Can_RxObject_handler
(
    const uint8 Controller,
    const uint8 MBIndex,
    const Can_HwHandleType Hrh
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    uint32 canID;
    uint8 dlc ;
    uint8 tempMBcode;
    uint8 tempMBcode1;
    uint8 tempLength;
    Can_IdType id;
    Can_HwType mailBox;
    PduInfoType info;
    uint8 i = 0, j;
    uint16 dummy;
    uint32 srcDataAddr;
    uint8 Length;
    boolean isCANFD;
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg;
    uint32 Can_MB_Addr;
    uint8 OffsetAddr = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].OffsetAddr;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];


#if(STD_ON == CAN_CANFD_SUPPORT)
    uint8 temprxbuffer[CANFD_MAX_DLC];
#else
    uint8 temprxbuffer[CAN_MAX_DLC];
#endif


    Can_MB_Addr = CAN_MB_ADDR(phyController, OffsetAddr, MBIndex);
    Can_MB_Reg =  (Can_MsgBufType *)Can_MB_Addr;
    tempMBcode1 = Can_MB_Reg->Code;
    tempMBcode = Can_MB_Reg->Code & CAN_CODE_MASK;
    /* MB is locked when frame is received, new Msg will be lost */
    if(((CAN_RX_MB_CODE_FULL) == tempMBcode)
            || ((CAN_RX_MB_CODE_OVERRUN) == tempMBcode))
    {
        Length = Can_MB_Reg->Length;
        if(CAN_RX_MB_CODE_OVERRUN == tempMBcode)
        {
            CAN_DET_REPORT_ERROR(CAN_RX_PROCESS_APIID, CAN_E_DATALOST);/*CAN395*/
        }
        else if((Length == 0) || (0 != (Length & CAN_RTR_MASK)))
        {
            CAN_DET_REPORT_ERROR(CAN_RX_PROCESS_APIID, CAN_E_PARAM_DLC);
        }
        else
        {
            SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1();/*CAN012*/
            canID = Can_MB_Reg->Id;
            if(CAN_FD_EDL_MASK == (tempMBcode1 & CAN_FD_EDL_MASK))
            {
                isCANFD = TRUE;
            }
            else
            {
                isCANFD = FALSE;
            }

            if(0 == (Length & CAN_IDE_MASK))
            {
                /*Standard ID*/
                canID = canID >> CAN_STD_POS;
                canID = canID & CAN_STD_MAX_CANID;
                id = (Can_IdType)canID;
            }
            else
            {
                /*Externed ID*/
                canID = (uint32)(canID & CAN_EXT_MAX_CANID);
//                id = (Can_IdType)(canID | CAN_EXT_CANID_FLAG);/*CAN423*/
                id = (Can_IdType)(canID);/*CAN423*/
            }
            if(TRUE == isCANFD)
            {
//                id |= CAN_CANFD_MASK;
            }

            dlc = Length & CAN_DLC_MASK;
#if(STD_ON == CAN_CANFD_SUPPORT)
            dlc = Bsw_CanFDDlcMap[dlc];
#endif
            Length = dlc;
            /*   copy data from CanRx register to Local buffer may geberate warning: volatile uint8 * to uint8 *;
                         ignor this warning  CAN060 CAN300 CAN299 */
            srcDataAddr = (uint32)(&(Can_MB_Reg->DataSeg));
            i = 0;
            while(Length > 0)
            {
                if(Length < 4)
                {
                    tempLength = Length;
                }
                else
                {
                    tempLength = 4;
                }
                for(j = 0; j < tempLength; j++)
                {
                    temprxbuffer[(i * 4) + j] = ((uint8 *)srcDataAddr)[3 - j];
                }
                Length -= tempLength;
                srcDataAddr += 4;
                i++;
            }


            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1();

#ifdef CanLPduReceiveCalloutFunction /*CAN443 CAN444*/
            if(TRUE == CanLPduReceiveCalloutFunction(Hrh, (Can_IdType)canID, dlc, temprxbuffer))
#endif
            {
                mailBox.CanId = id;
                mailBox.Hoh = Hrh;
                mailBox.ControllerId = Controller;
                info.SduDataPtr = temprxbuffer;
                info.SduLength = dlc;
                //CanIf_RxIndication(&mailBox, &info) ;/*CAN396 CAN279*/
                CanIf_RxIndication(Hrh,id,dlc,temprxbuffer);//lele mend
            }
        }
    }
    
    /* Read the timer register to release the MB. This code cannot be removed,
       if removed, the MB cannot receive Msg anymore */
    Can_MB_Reg->Code = CAN_MB_CODE_INIT | CAN_RX_MB_CODE_EMPTY;
    dummy = CAN_TIMER(phyController);
}

#if(STD_ON == CAN_TXRX_INTERRUPT_SUPPORT)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_MB_handler
*
* Description:   This function is used for handle the MB rx or tx event
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/ uint8 tempaa,tempbb,tempcc;
FUNC(void, CAN_CODE) Can_Controller_MB_handler
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 MBIndex = 0;
    const uint8 hrhNum = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhNum;
    Can_HwHandleType hohIndex;

    while(0 != CAN_IFLAG1(phyController))
    {
        MBIndex = Can_GetIntMBNum(phyController);
        tempaa = MBIndex;
        /* MBIndex to Hoh */
        if(MBIndex < hrhNum)/* Rx */
        {
            hohIndex = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhStart + MBIndex;tempbb = hohIndex;
            /*
               interrupt flag must be clear after Rx Indication, as new incoming data
               may cause data inconsistent!
            */
            Can_RxObject_handler(CAN_CONTROLLER_ID, MBIndex, hohIndex);
            Can_ClearIntFlag(phyController, MBIndex);
        }
#if(CAN_USED_HTH_NUM > 0)
        else/*Tx*/
        {
            hohIndex = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hthStart + (MBIndex - hrhNum);
            EmptyFlagForHth[hohIndex - CAN_USED_HRH_NUM] = TRUE;
            /* this flag must be cleared before TxConf, as new Msg of same hth may be send within the
            TxConf(when TXBuffering is on)*/
            Can_ClearIntFlag(phyController, MBIndex);
            /*the message was sented */
            CanIf_TxConfirmation(PduIdForHth[hohIndex - CAN_USED_HRH_NUM]);

        }
#endif
    }
}
#endif



#if(STD_ON == CAN_TXRX_POLLING_SUPPORT)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Tx_handler
*
* Description:   This function is used for handle the success TX confirmation
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   Only Called in MainFunctionWrite
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_Controller_Tx_handler
(
    const uint8 Controller
)
{

    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType hthStart = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hthStart;
    const uint8 HthNum = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hthNum;
    uint8 Index;
    uint8 MBIndex;
    uint8 tempIntFlag;
    Can_HwHandleType HthIndex;


    if(HthNum > 0)  /*has TX MB*/
    {
        /*dont need to check if this ctrl is txPolling as this has been checked in mainWrite */
        for(Index = 0; Index < HthNum; Index++)
        {
            /*MB has sent message succeed*/
            HthIndex = hthStart + Index;
            MBIndex = CAN_USED_HOH_INFO[HthIndex].phyMBIndex;
            tempIntFlag = Can_GetIntFlag(phyController, MBIndex);
            if(0 != tempIntFlag)
            {
                EmptyFlagForHth[HthIndex - CAN_USED_HRH_NUM] = TRUE;
                /*the message was sented */
                CanIf_TxConfirmation(PduIdForHth[HthIndex - CAN_USED_HRH_NUM]);
                Can_ClearIntFlag(phyController, MBIndex);
            }
        }

    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Rx_handler
*
* Description:   This function is used for handle the success RX indication
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_Controller_Rx_handler
(
    const uint8 Controller
)
{
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType hrhStart = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhStart;
    const uint8 HrhNum = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhNum;
    uint8 Index;
    uint8 MBIndex;
    uint8 tempIntFlag;



    if(HrhNum > 0)  /*has RX MB*/
    {
        /*dont need to check if this ctrl is rxPolling as this has been checked in mainRead */
        for(Index = 0; Index < HrhNum; Index++)
        {
            /*MB has new received message*/
            MBIndex = CAN_USED_HOH_INFO[hrhStart + Index].phyMBIndex;
            tempIntFlag = Can_GetIntFlag(phyController, MBIndex);
            if(0 != tempIntFlag)
            {
                Can_RxObject_handler(phyController, MBIndex, hrhStart + Index);
                Can_ClearIntFlag(phyController, MBIndex);
            }
        }
    }
}
#endif/*#if(STD_ON == CAN_TXRX_POLLING_SUPPORT)*/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Busoff_handler
*
* Description:   This function is used for handle the bus off event
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_Controller_Busoff_handler
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint16 errStatusL;

    errStatusL = CAN_ESR1L(phyController);
    errStatusL = errStatusL & CAN_BOFF_MASK;

    if(CAN_BOFF_MASK == errStatusL)
        /*CAN020 CAN272 CAN273 cancel pengding txMsg without cancel notify
        this controller has entered the bus off state*/
    {

        /* dont use Can_SetControllerMode, as cannot modeindication to canif here
           reinit con with no BD change
        */
    	set_busoff_times_fml();
        (void)Can_InitController(CAN_CONTROLLER_ID, CAN_INVALID_BD_INDEX);
        (void)Can_SetControllerMode(CAN_CONTROLLER_ID, CAN_T_STOP);
        CanIf_ControllerBusOff(CAN_CONTROLLER_ID);
        /*clear the bus off bitmask*/
        CAN_ESR1L(phyController) = CAN_BOFF_MASK;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Transmit_Abort
*
* Description:   This function is used for abort all the message in the
*                transmission buffer which is belong to one controller
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_CODE) Can_Controller_Transmit_Abort
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType hthStart = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hthStart;
    const uint8 HthNum = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hthNum;
    uint8 Index;
    Can_HwHandleType HthIndex;
    uint8 MBIndex;
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg ;
    uint32 Can_MB_Addr;
    const uint8 OffsetAddr = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].OffsetAddr;
    uint32 tempMask;
    
    /* abort opration will cause txinterrupt*/
    tempMask = CAN_IMASK1(phyController);
    CAN_IMASK1(phyController) = 0;

#if(CAN_MAX_HTH_NUM > 0)
    for(Index = 0; Index < HthNum; Index++)
    {
        MBIndex = CAN_USED_HOH_INFO[hthStart + Index].phyMBIndex;
        Can_MB_Addr = CAN_MB_ADDR(phyController, OffsetAddr, MBIndex);
        Can_MB_Reg =  (Can_MsgBufType *)Can_MB_Addr;

        /* also clear sw buffers */
        HthIndex = (hthStart + Index) - CAN_USED_HRH_NUM;
        EmptyFlagForHth[HthIndex] = TRUE;
        PduIdForHth[HthIndex] = COMSTACK_INVALID_PDUID;
        Can_MB_Reg->Code = CAN_TX_MB_CODE_ABORT;
    }
#endif
    CAN_IFLAG1(phyController) = 0xFFFFFFFFUL;/*clear all int flags*/
    CAN_IMASK1(phyController) = tempMask;

}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_TimeOutCheck
*
* Description:   This function used to check timeout
*
* Inputs:        cnt,initCnt
*
* Outputs:       boolean
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(STD_OFF == CAN_OS_COUNTER_USED)
STATIC FUNC(Can_ReturnType, CAN_CODE)   Can_TimeOutCheck
(
    const uint32 cnt
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_ReturnType flag = CAN_OK;

    if(cnt > CAN_TIMEOUT_DURATION)
    {
        flag = CAN_NOT_OK;
    }
    return flag;
}
#else
STATIC FUNC(Can_ReturnType, CAN_CODE)   Can_TimeOutCheck
(
    const uint32 initCnt,
    const uint32 cnt
)
{
    Can_ReturnType flag = CAN_OK;
    uint32 dCnt = 0;

    if(cnt >= initCnt)
    {
        dCnt = cnt - initCnt;
    }
    else
    {
        dCnt = (CanCounterMaxValue - initCnt) + cnt + 1;
    }

    if(dCnt > CAN_TIMEOUT_DURATION)
    {
        flag = CAN_NOT_OK;
    }
    return flag;
}
#endif


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerFreeze
*
* Description:   This function Accesss the hw registers to set can controller to Freeze Mode
*
* Inputs:        Controller

* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerFreeze
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempRegVal;
#if(STD_ON == CAN_OS_COUNTER_USED)
    uint32 timerInitCnt;
#endif
    uint32 timerCnt = 0;
    Can_ReturnType ret = CAN_OK;

    /*request enter into freeze mode*/
    CAN_MCR3(phyController) =
        (uint8)(CAN_FRZ_MASK | CAN_HALT_MASK | CAN_NOT_READY_MASK | CAN_SOFT_RST_MASK);

    CAN_TIMER_START();
    do
    {
        tempRegVal = CAN_MCR3(phyController);
        tempRegVal = tempRegVal & CAN_FRZ_ACK_MASK;

        if(0 != tempRegVal)
        {
            break;/* ACK set break loop*/
        }
        else
        {
            CAN_TIMER_LOOP();
            ret = CAN_TIMER_CHECK();
        }
    }
    while(CAN_OK == ret);

    return ret;
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerStop
*
* Description:   This function Accesss the hw registers to set can controller to Stop Mode
*
* Inputs:        Controller

* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerStop
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempRegVal;
#if(STD_ON == CAN_OS_COUNTER_USED)
    uint32 timerInitCnt;
#endif
    uint32 timerCnt = 0;
    Can_ReturnType ret = CAN_OK;

    /*Disable CAN Module,enter CAN_STOP_MODE*/
    /*Here must set MCR with 4 dis,frz,halt amd ready bits,otherwise it will cause
      unexpected interrupt---!!!
    */
    CAN_MCR3(phyController) = CAN_MDIS_MASK | CAN_FRZ_MASK | CAN_HALT_MASK | CAN_NOT_READY_MASK ;

    CAN_TIMER_START();

    do
    {
        tempRegVal = CAN_MCR3(phyController);
        tempRegVal = tempRegVal & CAN_NOT_READY_MASK;
        if(0 != tempRegVal)
        {
            break;/* NotRead Set break loop*/
        }
        else
        {
            CAN_TIMER_LOOP();
            ret = CAN_TIMER_CHECK();
        }
    }
    while(CAN_OK == ret);

    return ret;
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerStart
*
* Description:   This function Accesss the hw registers to set can controller to Start Mode
*
* Inputs:        Controller

* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerStart
(
    const uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempRegVal;
#if(STD_ON == CAN_OS_COUNTER_USED)
    uint32 timerInitCnt;
#endif
    uint32 timerCnt = 0;
    Can_ReturnType ret = CAN_OK;

    /*Enable CAN Module ,Clear MDIS*/
    /* MDIS FRZ FEN HALT SOFTRET are all clear */
    CAN_MCR3(phyController) = 0;

    CAN_TIMER_START();
    do
    {
        tempRegVal = CAN_MCR3(phyController);
        tempRegVal = tempRegVal & CAN_NOT_READY_MASK;
        if(0 == tempRegVal)
        {
            break;/* NotRead Set break loop*/
        }
        else
        {
            CAN_TIMER_LOOP();
            ret = CAN_TIMER_CHECK();
        }
    }
    while(CAN_OK == ret);


    return ret;
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_InitController
*
* Description:   This function initializes the bit timing related settings
*                of a CAN controller.
*
* Inputs:        Controller:  CAN controller to be initialized
*                config: paramter config pointer
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CAN_CODE)Can_InitController
(
    const uint8 Controller,
    const uint16 BaudRateConfigID
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_HwHandleType HohIndex;
    uint32 MBIndex = 0;
    const Can_HwHandleType rxMBstart = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhStart;

    const uint8 rxMBNum = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhNum;

    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    Std_ReturnType ret = E_NOT_OK;
    uint8 i;
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg;
    uint32 Can_MB_Addr;
    const uint32 OffsetAddr = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].OffsetAddr;
    const uint8 totalMbNum = CanMBNumber[phyController];

    if(phyController < CAN_PCC_TYPE2 )
    {
        CAN_PCC(phyController) |= CAN_PCC_INIT;
    }
    else
    {
        CAN_PCC2 |= CAN_PCC_INIT;
    }


    if(E_OK == Can_SetControllerFreeze(CAN_CONTROLLER_ID))
        /*already in initialization mode*/
    {
        /* select CAN clock */
        CAN_CTRL11(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CanCtrl11;

        /* clear all interrupt flag */
        CAN_ESR1H(phyController) = 0xFFFFU;
        CAN_ESR1L(phyController) = 0xFFFFU;
        CAN_IFLAG1(phyController) = 0xFFFFFFFFUL;/*clear int flag*/

        /* Init Can Registers */
        CAN_MCR1(phyController) = CAN_INIT_MCR1;
        CAN_MCR2(phyController) = CAN_INIT_MCR2;
        CAN_MCR0(phyController) = totalMbNum - 1; /* see UM, this value must--*/
        if(BaudRateConfigID != CAN_INVALID_BD_INDEX)
        {
#if(STD_ON == CAN_CANFD_SUPPORT)
            if(TRUE == CanFdSupport[phyController])
            {
                CAN_CBT(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlFDBDCfg[BaudRateConfigID].CanCBT;
                CAN_CTRL2(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlFDBDCfg[BaudRateConfigID].CanCTRL2;
                CAN_FDCTRL(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlFDBDCfg[BaudRateConfigID].CanFDCTRL;
                CAN_FDCBT(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlFDBDCfg[BaudRateConfigID].CanFDCBT;      
            }
            else
#endif
            {
                CAN_CTRL12(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlBDCfg[BaudRateConfigID].CanCtrl12;
                CAN_CTRL13(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlBDCfg[BaudRateConfigID].CanCtrl13;
            }


            /* CAN_BOFF_REC_MASK always disable busoff auto recorvery */
            /*in fd mode, only use smp and of ctrl0;
              in normal mode, use smp and PROPSEG  bits of ctrl0;
            */
            CAN_CTRL10(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CtrlBDCfg[BaudRateConfigID].CanCtrl10 | CAN_BOFF_REC_MASK;

        }



        /* GMASK R14 R15  Keep reset value all 0xFF */
        CAN_GMASK(phyController)   = 0xFFFFFFFFUL;
        CAN_R14MASK(phyController) = 0xFFFFFFFFUL;
        CAN_R15MASK(phyController) = 0xFFFFFFFFUL;

		for(i = 0; i < totalMbNum*4; i++ )
		{
			/* Clear all of  Message buffers */
			CAN_MB_DATA(phyController, i) = 0;				 /* Clear MB */
		}


        /* disable all mb first*/
        for(i = 0; i < totalMbNum ; i++ )
        {
            CAN_RXIMR(phyController, i) = 0x1FFFFFFF; /* Init all Filter Mask to full first */

            Can_MB_Addr = CAN_MB_ADDR(phyController, 0, i);
            Can_MB_Reg =  (Can_MsgBufType *)Can_MB_Addr;
            Can_MB_Reg->Code = CAN_RX_MB_CODE_NOT_ACTIVE;
        }

        for(MBIndex = 0; MBIndex < CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].hrhNum; MBIndex++)
        {
            Can_MB_Addr = CAN_MB_ADDR(phyController, OffsetAddr, MBIndex);
            Can_MB_Reg =  (Can_MsgBufType *)Can_MB_Addr;
            HohIndex = (uint8)(rxMBstart + MBIndex);
            if(MBIndex < rxMBNum)   /*RX MB*/
            {

                Can_SetID(CAN_USED_HOH_INFO[HohIndex].id, 0, CAN_USED_HOH_INFO[HohIndex].isExtended, Can_MB_Reg);
                CAN_RXIMR(phyController, MBIndex) = CAN_USED_HOH_INFO[HohIndex].filterRef;
                Can_MB_Reg->Code = CAN_MB_CODE_INIT | CAN_RX_MB_CODE_EMPTY;
            }
            /* tx and unused mb remain inactive, txmb will be set in CanWrite*/
        }

        /*enable all interrupt of MB*/
        CAN_IMASK1(phyController) = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].CanIMask1;


        if(E_OK == Can_SetControllerStop(CAN_CONTROLLER_ID))
        {
            ret = E_OK;
            Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED; /*CAN259*/
        }

    }

#if(STD_ON == CAN_DEV_ERROR_DETECT)
    if(E_NOT_OK == ret)
    {
        /*fail to enter into freeze mode*/
        CAN_DET_REPORT_ERROR(CAN_INITCONTROLLER_APIID, CAN_PL_INIT_ERROR);
    }
#endif

    return ret;

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Wakeup_handler
*
* Description:   This function report the wakeup event to EcuM module
*
* Inputs:        Controller:  CAN controller to be initialized
*                config: paramter config pointer
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(STD_ON == CAN_WAKEUP_SUPPORT)
FUNC(void, CAN_CODE) Can_Controller_Wakeup_handler
(
    const uint8 Controller
)
{
    EcuM_WakeupSourceType src;


    src = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].src;
    if(0 != src)
    {
        //Can_SetControllerMode(CAN_CONTROLLER_ID, CAN_T_WAKEUP);/* need to be discussed*/
        Can_WakeupFlag[CAN_CONTROLLER_ID] = TRUE;
        EcuM_CheckWakeup(src);
    }
}

#endif

/*******************************************************************************
*  PUBLIC Functions define
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetVersionInfo CAN224
*
* Description:   This function returns the version information of this module.
*
* Inputs:        versioninfo:Pointer to where to store the version information
*                            of this module
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CAN_VERSION_INFO_API)/*CAN252*/
FUNC(void, CAN_CODE) Can_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo
)
{
    /*CAN177*/
    if(NULL_PTR == versioninfo)
    {
        CAN_DET_REPORT_ERROR(CAN_GETVERSIONINFO_APIID, CAN_E_PARAM_POINTER);
    }
    else
    {
        /*CAN105*/
        /* Copy the vendor Id */
        versioninfo->vendorID = CAN_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = CAN_MODULE_ID;

        /* Copy Software Major Version */
        versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Init  CAN223
*
* Description:   This function initializes the module. CAN250 CAN053 CAN407 CAN056
*
* Inputs:        ConfigPtr
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_Init(void)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
    uint8 Controller;
#endif
    Can_HwHandleType hohIndex;
#if(CAN_DEV_ERROR_DETECT == STD_ON)
    boolean flag = TRUE;
#endif

    /*CAN174*/
    if(STD_UNINITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_INIT_APIID, CAN_E_TRANSITION);
    }
    else
    {
        /*CAN175 CAN021 CAN291*/

#if(CAN_USED_HTH_NUM > 0)
        for(hohIndex = 0; hohIndex < CAN_USED_HTH_NUM; hohIndex++)
        {
            EmptyFlagForHth[hohIndex] = TRUE;
            PduIdForHth[hohIndex] = COMSTACK_INVALID_PDUID;
        }
#endif

#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
        for(Controller = 0; Controller < CAN_USED_CONTROLLER_NUM; Controller++)
#endif
        {
#if(STD_ON == CAN_WAKEUP_SUPPORT)
            Can_WakeupFlag[CAN_CONTROLLER_ID] = FALSE;
#endif

            /*CAN408 Not check can contrller's state*/
            /*CAN245*/
            Can_CtrlIntCnt[CAN_CONTROLLER_ID] = 0;
            Can_CtrlIntReg[CAN_CONTROLLER_ID].CanCtrl11 = 0;
            Can_CtrlIntReg[CAN_CONTROLLER_ID].CanIMask1 = 0;
#if(CAN_DEV_ERROR_DETECT == STD_ON)
            if(E_NOT_OK == Can_InitController(CAN_CONTROLLER_ID, CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].DefaultBD))
            {
                flag = FALSE;
#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
                break;
#endif
            }
#else
            (void)Can_InitController(CAN_CONTROLLER_ID, CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].DefaultBD);
#endif
        }

#if(CAN_DEV_ERROR_DETECT == STD_ON)
        if(TRUE != flag)
        {
#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
            for(Controller = 0; Controller < CAN_USED_CONTROLLER_NUM; Controller++)
#endif
            {
                Can_State[CAN_CONTROLLER_ID] = CAN_UNINT;
            }
        }
        else
#endif
        {
            Can_InitStatus = STD_INITIALIZED;/*CAN246*/
        }
    }

}


#if (STD_ON == CAN_SET_BAUDRATE_API)
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetBaudrate  CAN449
*
* Description:   This function set the Baudrate of Controller
*
* Inputs:        Controller,Baudrate
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Std_ReturnType, CAN_CODE) Can_SetBaudrate
(
    uint8 Controller,
    uint16 BaudRateConfigID
)
{
    Std_ReturnType ret = E_NOT_OK;
#if(STD_ON == CAN_DEV_ERROR_DETECT)
    boolean validFlag = FALSE;
#endif

    /*CAN450  CAN459*/
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_SETBAUDRATE_APIID, CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        CAN_DET_REPORT_ERROR(CAN_SETBAUDRATE_APIID, CAN_E_PARAM_CONTROLLER);
    }
    else if(CAN_STOPPED != Can_State[CAN_CONTROLLER_ID])
    {
        CAN_DET_REPORT_ERROR(CAN_SETBAUDRATE_APIID, CAN_E_TRANSITION);
    }
    else
    {
        ret = Can_InitController(CAN_CONTROLLER_ID, BaudRateConfigID); /*CAN062 CAN255 CAN260 CAN422*/

#if(STD_ON == CAN_DEV_ERROR_DETECT)/*CAN451*/
        if(FALSE == validFlag)
        {
            CAN_DET_REPORT_ERROR(CAN_SETBAUDRATE_APIID, CAN_E_PARAM_BAUDRATE);
        }
#endif
    }

    return ret;

}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerMode  CAN230
*
* Description:   This function performs software triggered state
*                transitions of the CAN controller State machine.
*
* Inputs:        Controller:CAN controller for which the status
*                           shall be changed
*                Transition:Transition value to request new
*                           CAN controller state
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_CODE) Can_SetControllerMode
(
    uint8 Controller,
    Can_StateTransitionType Transition
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_ReturnType ret = CAN_NOT_OK;

    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_PARAM_CONTROLLER);
    }
    else
    {

        /*CAN017*/
        /*CAN398 CAN372
          setMode cannot be blocking, need use osCounter to check timeout
          if timeout, the modeswitch need to be polled in modeMainFunction
        */
        switch(Transition)
        {
            case CAN_T_START:
                if(Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)/*CAN409*/
                {
                    ret = CAN_NOT_OK;
                    CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_TRANSITION);
                }
                else
                {
                    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3();

                    /*CAN261 CAN262*/
                    Can_Controller_Transmit_Abort(CAN_CONTROLLER_ID) ;
                    ret = Can_SetControllerStart(CAN_CONTROLLER_ID);
                    if(CAN_OK == ret)
                    {
                        Can_State[CAN_CONTROLLER_ID] = CAN_STARTED;
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STARTED);
                    }
                    else
                    {
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_START;
                    }
                    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3();
                }
                break;

            case CAN_T_STOP:
                if((Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
                        && (Can_State[CAN_CONTROLLER_ID] != CAN_STARTED))
                {
                    ret = CAN_NOT_OK;
                    CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_TRANSITION);
                }
                else
                {
                    ret = CAN_OK;
                    if(Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
                    {
                        /*CAN282 CAN283 when in Stop Mode should clear all Tx Buffer*/
                        Can_Controller_Transmit_Abort(CAN_CONTROLLER_ID) ;
                        /*CAN263 CAN264*/
                        ret = Can_SetControllerStop(CAN_CONTROLLER_ID);
                    }
                    if(CAN_OK == ret)
                    {
                        Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STOPPED);
                    }
                    else
                    {
                        /*fail to enter into disable can module*/
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_STOP;
                    }
                }
                break;


            /* CAN258 CAN404
               if hw not support sleep, SW shall set to logical Sleep,but hw is still in stop
            */
            case CAN_T_SLEEP: /* 5604 no sleep mode ,enter stop mode instead*/
                if((Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
                        && (Can_State[CAN_CONTROLLER_ID] != CAN_SLEEP))
                {
                    CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_TRANSITION);
                    ret = CAN_NOT_OK;
                }
                else
                {
                    ret = CAN_OK;
                    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_2();
                    if(Can_State[CAN_CONTROLLER_ID] != CAN_SLEEP)
                    {
                        /*Disable CAN Module,enter CAN_SLEEP*/
                        ret = Can_SetControllerStop(CAN_CONTROLLER_ID);
                    }
                    if(CAN_OK == ret)
                    {
                        Can_State[CAN_CONTROLLER_ID] = CAN_SLEEP; /*CAN290*/
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_SLEEP);
                    }
                    else
                    {
                        /*fail to enter into disable can module*/
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_SLEEP;
                    }
                    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_2();
                }
                break;


            case CAN_T_WAKEUP:/* from sleep to stop */

                if((Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
                        && (Can_State[CAN_CONTROLLER_ID] != CAN_SLEEP))
                {
                    CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_TRANSITION);
                    ret = CAN_NOT_OK;
                }
                else
                {
                    ret = CAN_OK;
                    if(Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
                    {
                        /*CAN267 CAN268 Disable CAN Module,enter CAN_STOP_MODE*/
                        ret = Can_SetControllerStop(CAN_CONTROLLER_ID);
                    }
                    if(CAN_OK == ret)
                    {
                        Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STOPPED);
                    }
                    else
                        /*fail to enter into disable can module*/
                    {
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_WAKEUP;
                    }
                }

                break;

            default:
                CAN_DET_REPORT_ERROR(CAN_SETCONTROLLERMODE_APIID, CAN_E_TRANSITION);
                ret = CAN_NOT_OK;
                break;
        }
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableControllerInterrupts CAN231
*
* Description:   This function used to disable all can controller interrupts
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_DisableControllerInterrupts
(
    uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8  phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempCtrl1;
    Can_OldIERType tempIer;
    /*CAN206*/
    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_DISABLECONTROLLERINTERRUPTS_APIID, CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        CAN_DET_REPORT_ERROR(CAN_DISABLECONTROLLERINTERRUPTS_APIID, CAN_E_PARAM_CONTROLLER);
    }
    else
    {
        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();

        /*CAN049  CAN202  CAN204*/
        if(0 == (Can_CtrlIntCnt[CAN_CONTROLLER_ID]))
        {
            /* use local tempIer to ensure Reentrant*/
            tempIer.CanCtrl11 = CAN_CTRL11(phyController);
            tempIer.CanIMask1 = CAN_IMASK1(phyController);

            tempCtrl1 = CAN_CTRL11(phyController);
            /*clear BOFF_MSK ERR_MSK TWRN_MSK RWRN_MSK*/
            tempCtrl1 = tempCtrl1 & CAN_ERR_CTRL2INT_MASK;
            CAN_CTRL11(phyController) = tempCtrl1;
            CAN_IMASK1(phyController) = 0;

            Can_CtrlIntReg[CAN_CONTROLLER_ID].CanCtrl11 = tempIer.CanCtrl11;
            Can_CtrlIntReg[CAN_CONTROLLER_ID].CanIMask1 = tempIer.CanIMask1;
        }
        Can_CtrlIntCnt[CAN_CONTROLLER_ID]++;
        if(Can_CtrlIntCnt[CAN_CONTROLLER_ID] > CAN_MAX_INT_NEST_COUNT)
        {
            Can_CtrlIntCnt[CAN_CONTROLLER_ID] = CAN_MAX_INT_NEST_COUNT;
            CAN_DET_REPORT_ERROR(CAN_DISABLECONTROLLERINTERRUPTS_APIID, CAN_E_INT_NEST);
        }

        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableControllerInterrupts CAN232
*
* Description:   This function enables all allowed interrupts.
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE)Can_EnableControllerInterrupts
(
    uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    const uint8  phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];

    if(STD_INITIALIZED != Can_InitStatus)
    {
        CAN_DET_REPORT_ERROR(CAN_ENABLECONTROLLERINTERRUPTS_APIID, CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        CAN_DET_REPORT_ERROR(CAN_ENABLECONTROLLERINTERRUPTS_APIID, CAN_E_PARAM_CONTROLLER);
    }
    else if(CAN_MAX_INT_NEST_COUNT <= Can_CtrlIntCnt[CAN_CONTROLLER_ID])
    {
        CAN_DET_REPORT_ERROR(CAN_ENABLECONTROLLERINTERRUPTS_APIID, CAN_E_INT_NEST);
    }
    else
    {
        /*CAN050  CAN208  CAN204*/
        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();
        if(Can_CtrlIntCnt[CAN_CONTROLLER_ID] > 0U)
        {
            Can_CtrlIntCnt[CAN_CONTROLLER_ID]--;
            if(0 == Can_CtrlIntCnt[CAN_CONTROLLER_ID])
            {
                CAN_CTRL11(phyController) = Can_CtrlIntReg[CAN_CONTROLLER_ID].CanCtrl11;
                CAN_IMASK1(phyController) = Can_CtrlIntReg[CAN_CONTROLLER_ID].CanIMask1;
            }
        }
        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableGlobalInterrupt
*                
* Description:   This function enables all maskable interrupts 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3006  MISRA-C:2004 Rule 2.1
* PRQA S 1006  MISRA-C:2004 Rule 1.1
* This function is used to disable global interrupts, which need to access or  
* save MCU registers. So this code used assembler code.  
* This part of code is verified manually and has no impact.
*******************************************************************************/
FUNC(void, CAN_CODE) Can_EnableGlobalInterrupt(void) 
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if(CanGlobalInterruptCount>0)
    {
        CanGlobalInterruptCount--;
    }
    
    if(0 == CanGlobalInterruptCount)
    {       
         /* Enable the global interrupt*/
        __asm("cpsie i");      
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableGlobalInterrupt
*                
* Description:   This function disables all maskable interrupts 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3006  MISRA-C:2004 Rule 2.1
* PRQA S 1006  MISRA-C:2004 Rule 1.1
* This function is used to disable global interrupts, which need to access or  
* save MCU registers. So this code used assembler code.  
* This part of code is verified manually and has no impact.
*******************************************************************************/
FUNC(void, CAN_CODE)Can_DisableGlobalInterrupt(void) 
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    if(0 == CanGlobalInterruptCount)
    {
      /* Disable the global interrupt */
      __asm("cpsid i");
    } 
    
    CanGlobalInterruptCount++;
    if(CanGlobalInterruptCount > CAN_CONTROL_COUNT)
    {
        CanGlobalInterruptCount = CAN_CONTROL_COUNT;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_CheckWakeup CAN232
*
* Description:   This function checks if a wakeup has occurred for the given controller
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_CODE)Can_CheckWakeup
(
    uint8 Controller
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_ReturnType ret = CAN_NOT_OK;

    if(STD_INITIALIZED != Can_InitStatus)
    {
        /*CAN362*/
        CAN_DET_REPORT_ERROR(CAN_CHECK_WAKEUP_APIID, CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        /*CAN363*/
        CAN_DET_REPORT_ERROR(CAN_CHECK_WAKEUP_APIID, CAN_E_PARAM_CONTROLLER);
    }
    else
    {
#if(STD_ON == CAN_WAKEUP_SUPPORT)
        if(TRUE == Can_WakeupFlag[CAN_CONTROLLER_ID])
        {
            Can_WakeupFlag[CAN_CONTROLLER_ID] = FALSE;
            EcuM_SetWakeupEvent(CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].src);
            ret = CAN_OK;
        }
#endif
    }
    return ret;

}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Write CAN233
*
* Description:   This function used to send 1 can frame CAN100
*
* Inputs:        PduInfo:  Pointer to SDU user memory, DLC and Identifier.
*                Hth:  information which HW-transmit handle shall be used
*                      for transmit. Implicitly this is also the information
*                      about the controller to use because the Hth numbers
*                      are unique inside one hardware unit.
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_CODE) Can_Write
(
    Can_HwHandleType Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
    Can_ReturnType ret = CAN_NOT_OK;
    boolean hthEmptyFlag = FALSE;
    Can_HwHandleType HthIndex;
    uint8 MBIndex;
    uint8 phyController;
    uint8 j;
    uint8 tempIndex;
    uint8 FdLength;
    uint8 DataLen;
    uint8 tempLen;
    P2VAR(Can_MsgBufType,AUTOMATIC, AUTOMATIC)Can_MB_Reg;
    uint32 Can_MB_Addr;

#if(STD_ON == CAN_CANFD_SUPPORT)
    uint8 PaddingLen;
    uint8 Can_TxBuff[CANFD_MAX_DLC];
#else
    uint8 Can_TxBuff[CAN_MAX_DLC];
#endif
    uint8 Controller = CAN_USED_HOH_INFO[Hth].controllerRef;
    boolean isExtendedCanId = CAN_USED_HOH_INFO[Hth].isExtended;
    boolean isCANFD = FALSE;
    uint8 tempCode = 0;
    const uint8 OffsetAddr = CAN_USED_CTRL_INFO[CAN_CONTROLLER_ID].OffsetAddr;

    if(STD_INITIALIZED != Can_InitStatus)
    {
        /*CAN216*/
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_UNINIT);
    }
    else if(Hth >= CAN_USED_HOH_NUM)
    {
        /*CAN217*/
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_HANDLE);
    }
    else if(TRUE == CAN_USED_HOH_INFO[Hth].isRx)
    {
        /*CAN217*/
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_HANDLE);
    }
    else if(NULL_PTR == PduInfo)
    {
        /*CAN219*/
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_POINTER);
    }
    else if((PduInfo->length) == 0)
    {
        /*CAN218*/
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_DLC);
    }
#if(STD_OFF == CAN_CANFD_SUPPORT)
    else if((PduInfo->id & CAN_CANFD_MASK) == CAN_CANFD_MASK)
    {
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_HANDLE);
    }
#endif
    else if(((PduInfo->id & CAN_CANFD_MASK) == 0) && (CAN_MAX_DLC < (PduInfo->length)))
    {
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_DLC);
    }
    else if(((PduInfo->id & CAN_CANFD_MASK) == CAN_CANFD_MASK) &&
            (CAN_USED_CTRL_INFO[Controller].CanFdDlc < (PduInfo->length)))
    {
        CAN_DET_REPORT_ERROR(CAN_WRITE_APIID, CAN_E_PARAM_DLC);
    }
    else
    {
        if((PduInfo->id & CAN_CANFD_MASK) == CAN_CANFD_MASK)
        {
            isCANFD = TRUE;
        }
//        if((PduInfo->id & CAN_EXT_CANID_FLAG) == CAN_EXT_CANID_FLAG)
//        {
//            isExtendedCanId = TRUE;
//        }
        /*CAN212 */
        phyController = CanControllerIDtoPhys[CAN_USED_HOH_INFO[Hth].controllerRef];
#if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION)

#else
        MBIndex = CAN_USED_HOH_INFO[Hth].phyMBIndex;
        HthIndex = Hth - CAN_USED_HRH_NUM;
        hthEmptyFlag = EmptyFlagForHth[HthIndex];
        DataLen = PduInfo->length;
#endif
        if(TRUE == hthEmptyFlag)/*CAN214*/
            /*Hth is empty*/
        {
            ret = CAN_OK;
            for(j = 0; j < PduInfo->length; j++)
            {
                Can_TxBuff[j] = PduInfo->sdu[j];
            }
            FdLength = PduInfo->length;
#if(STD_ON == CAN_CANFD_SUPPORT)
            if(PduInfo->length > CAN_MAX_DLC)
            {
                for (j = CANFD_PADDING_INDEX_LO; j < CANFD_PADDING_INDEX_HI; j++)
                {
                    if (PduInfo->length <= Bsw_CanFDDlcMap[j])
                    {
                        PaddingLen = Bsw_CanFDDlcMap[j] - PduInfo->length;

                        if (PaddingLen > 0)
                        {
                            Bsw_MemSet(Can_TxBuff + PduInfo->length, CAN_USED_HOH_INFO[Hth].FdPaddingValue, PaddingLen);
                        }

                        FdLength = j;
                        DataLen = Bsw_CanFDDlcMap[j];
                        break;
                    }
                }
            }
#endif
            Can_MB_Addr = CAN_MB_ADDR(phyController, OffsetAddr, MBIndex);
            Can_MB_Reg =  (Can_MsgBufType *)Can_MB_Addr;

            SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
            PduIdForHth[HthIndex] = PduInfo->swPduHandle ;/*CAN276*/
            /*stores the identifier, the control bits, and the data content into one of the transmit buffers*/
            /*Identifier Registers*/
            Can_SetID(PduInfo->id, FdLength, isExtendedCanId, Can_MB_Reg);

            /*copy data from Local buffer to CanTx register may geberate warning: volatile uint8 * to uint8 *; CAN059 CAN427  */
            tempIndex = 0;
            while(DataLen > 0)
            {
                tempLen = CAN_DATA_COPY_OFFSET;
                if(DataLen < CAN_DATA_COPY_OFFSET)
                {
                    tempLen = DataLen;
                }

                /*  Byte order process
                    data copy
                    3-->0
                    2-->1
                    1-->2
                    0-->4
                */
                for(j = 0; j < tempLen; j++)
                {
                    ((uint8 *)&Can_MB_Reg->DataSeg)[tempIndex + (CAN_DATA_COPY_OFFSET - j - 1)] = Can_TxBuff[tempIndex + j];
                }

                DataLen = DataLen - tempLen;
                tempIndex = tempIndex + tempLen;
            }

            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
            EmptyFlagForHth[HthIndex] = FALSE;
#if(STD_ON == CAN_CANFD_SUPPORT)
            if(isCANFD == TRUE)
            {
                tempCode |= CAN_EDL_MASK;
#if(STD_ON == CAN_CANFD_BITRATE)
                tempCode |= CAN_BRS_MASK;
#endif
            }
#endif
            tempCode |= CAN_MB_CODE_INIT | CAN_TX_MB_CODE_TRANS;


            Can_MB_Reg->Code = tempCode; /*CAN275*/
        }
        else
        {
            /*CAN213 CAN215 CAN434*/
            /*Hth is full*/
            ret = CAN_BUSY;
        }
    }
    return ret;
}


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Mode CAN368
*
* Description:   This function performs the polling of CAN controller
*                mode transitions.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_CODE) Can_MainFunction_Mode(void)
{
#if CANDRV_DEBUG
    Printf("%s,%d\r\n",__func__,__LINE__);
#endif
#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
    uint8 Controller;
#endif
    uint8 phyController;
    uint8 tempRegVal;

    if(STD_INITIALIZED != Can_InitStatus)
    {
        /*CAN216*/
        CAN_DET_REPORT_ERROR(CAN_MAINFUNCTION_MODE_APIID, CAN_E_UNINIT);
    }
    else
    {
        /*CAN369  CAN373 CAN372 CAN370*/
#if (STD_OFF == CAN_SINGLE_NETWORK_OPTIMIZE)
        for(Controller = 0; Controller < CAN_USED_CONTROLLER_NUM; Controller++)
#endif
        {
            phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
            switch(Can_ModeMonitor[CAN_CONTROLLER_ID])
            {
                case CAN_T_START:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & (CAN_MDIS_MASK | CAN_NOT_READY_MASK);
                    if(0 == tempRegVal)
                    {
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STARTED);
                        Can_State[CAN_CONTROLLER_ID] = CAN_STARTED;
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_NONE;
                    }
                }
                break;
                case CAN_T_STOP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & (CAN_MDIS_MASK | CAN_NOT_READY_MASK);
                    if((CAN_MDIS_MASK | CAN_NOT_READY_MASK) == tempRegVal)
                    {
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STOPPED);
                        Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_NONE;
                    }
                }
                break;

                case CAN_T_SLEEP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & (CAN_MDIS_MASK | CAN_NOT_READY_MASK);
                    if((CAN_MDIS_MASK | CAN_NOT_READY_MASK) == tempRegVal)
                    {
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_SLEEP);
                        Can_State[CAN_CONTROLLER_ID] = CAN_SLEEP;
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_NONE;
                    }
                }
                break;

                case CAN_T_WAKEUP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & (CAN_MDIS_MASK | CAN_NOT_READY_MASK);
                    if((CAN_MDIS_MASK | CAN_NOT_READY_MASK) == tempRegVal)
                    {
                        CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                       CANIF_CS_STOPPED);

                        Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED ;
                        Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_NONE;
                    }
                }
                break;
                default:

                    break;

            }
        }
    }
}
#if(STD_ON == CanPublicIcomSupport)
Std_ReturnType Can_SetIComConfigration
(
    uint8 Controller,
    IcomConfigIdType ConfigurationId
)
{

    return 0;
}
#endif

#define CAN_STOP_SEC_CODE
#include "MemMap.h"

