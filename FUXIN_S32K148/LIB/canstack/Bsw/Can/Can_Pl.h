/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Pl.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : CAN Driver platform head File
*   Author          : Hirain
********************************************************************************
*   Description     : The header file Can_Pl.h contains type definitions and
*                      macros which relate to specific MCU .
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
*   01.00.00    17/11/2016    SuyunYing     N/A          Original
********************************************************************************
* END_FILE_HDR*/

#ifndef CAN_PL_H
#define CAN_PL_H

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "Can_Version.h"
#include "EcuM_Cbk.h"


/*******************************************************************************
*   Macro
*******************************************************************************/
/* USE FOR EEM */
#define CAN0_BUSOFF_VECTOR                 (78u)
#define CAN0_ERROR_VECTOR                  (79u)
#define CAN0_WAKEUP_VECTOR                 (80u)
#define CAN0_0_15_MB_VECTOR                (81u)
#define CAN0_16_31_MB_VECTOR               (82u)

#define CAN1_BUSOFF_VECTOR                 (85u)
#define CAN1_ERROR_VECTOR                  (86u)
#define CAN1_WAKEUP_VECTOR                 (87u)
#define CAN1_0_15_MB_VECTOR                (88u)

#define CAN2_BUSOFF_VECTOR                 (92u)
#define CAN2_ERROR_VECTOR                  (93u)
#define CAN2_WAKEUP_VECTOR                 (94u)
#define CAN2_0_15_MB_VECTOR                (95u)


#if(CAN_SUPPORT_MCU == CAN_S32K_142)
#define TOTAL_CAN_MODULE_NUM                (0x2U)
#elif(CAN_SUPPORT_MCU == CAN_S32K_144)
#define TOTAL_CAN_MODULE_NUM                (0x3U)
#elif(CAN_SUPPORT_MCU == CAN_S32K_146)
#define TOTAL_CAN_MODULE_NUM                (0x3U)
#elif(CAN_SUPPORT_MCU == CAN_S32K_148)
#define TOTAL_CAN_MODULE_NUM                (0x3U)
#else
#endif
#define CAN_MAX_MB_REG_NUM0                 (128)
#define CAN_MAX_MB_REG_NUM1                 (64)
#define CAN_DATA_COPY_OFFSET                (4)

#define CAN_STD_POS                         (18)
#define CAN_INIT_MCR2                       ((uint8)0x83U)
#define CAN_MB_OFFSET                       ((uint8)0x80)

/*AEN is Always Set so that pengding TxReq can Be cancel when enter stop mode*/



#if(STD_ON == CAN_CANFD_SUPPORT)
#define CAN_MB_EDL      (1U)
#define CAN_MCR1_FDEN   (1U)

#if(STD_ON == CAN_CANFD_BITRATE)
#define CAN_MB_BRS      (1U)
#else
#define CAN_MB_BRS      (0U)
#endif
#else
#define CAN_MB_EDL      (0U)
#define CAN_MB_BRS      (0U)
#define CAN_MCR1_FDEN   (0U)

#endif
#define CAN_AEN                        (1U)
#define CAN_MB_CODE_INIT            (CAN_MB_BRS<<6U)
#define CAN_INIT_MCR1               ((CAN_AEN<<4U)|(CAN_MCR1_FDEN<<3U))


/*******************************************************************************
*   Typedef
*******************************************************************************/
/*******************************************************************************
* PRQA S 3132
* Hard coded 'magic' number used in Can_RegType and Can_MsgBufType.
* These numbers are only used once in this file and they are used to define
* hw registers, so its not necessary to use macro.
* This part of code is verified manually and has no impact.
*******************************************************************************/
typedef struct
{
    volatile uint8      CanReserved1[1];
    volatile uint8      Length;         /* SRR,IDE,RTR,LENGTH */
    volatile uint8      CanReserved2[2];
    volatile uint32     Id;             /* Identifier Register 0,1*/
    volatile uint8      DataSeg[8];     /* Data 0 .. 7 */
} Can_WakeupMsgBufType;

typedef struct
{
    volatile uint16     TimeStamp;
    volatile uint8      Length;         /* SRR,IDE,RTR,LENGTH */
    volatile uint8      Code;           /* EDL,BRS,ESI,CODE*/
    volatile uint32     Id;             /* Identifier Register 0,1*/
    volatile uint32     DataSeg;        /* Data 0 .. 3 */
} Can_MsgBufType;



typedef struct
{
    volatile uint8      CanMCR0;
    volatile uint8      CanMCR1;
    volatile uint8      CanMCR2;
    volatile uint8      CanMCR3;
    volatile uint8      CanCTRL10;
    volatile uint8      CanCTRL11;
    volatile uint8      CanCTRL12;
    volatile uint8      CanCTRL13;
    volatile uint8      CanReserved1[2];
    volatile uint16     CanTimer;
    volatile uint8      CanReserved2[4];
    volatile uint32     CanGMask;
    volatile uint32     CanR14Mask;
    volatile uint32     CanR15Mask;
    volatile uint32     CanECR;
    volatile uint16     CanESR1L;
    volatile uint16     CanESR1H;
    volatile uint8      CanReserved3[4];
    volatile uint32     CanIMask1;
    volatile uint8      CanReserved4[4];
    volatile uint32     CanIFlag1;
    volatile uint32     CanCTRL2;
    volatile uint16     CanESR2L;
    volatile uint16     CanESR2H;
    volatile uint8      CanReserved5[8];
    volatile uint32     CanCRC;
    volatile uint32     CanRXFGMask;
    volatile uint32     CanRXFIR;
    volatile uint32     CanCBT;
    volatile uint8      CanReserved6[44];
    volatile uint32     CanMBData[128];
    volatile uint8      CanReserved7[1536];
    volatile uint32     CanRXIMR[32];
    volatile uint8      CanReserved8[512];
    volatile uint32     CanCTRL1_PN;
    volatile uint32     CanCTRL2_PN;
    volatile uint32     CanWU_MTC;
    volatile uint32     CanFLT_ID1;
    volatile uint32     CanFLT_DLC;
    volatile uint32     CanPL1_LO;
    volatile uint32     CanPL1_HI;
    volatile uint32     CanFLT_ID2_IDMASK;
    volatile uint32     CanPL2_PLMASK_LO;
    volatile uint32     CanPL2_PLMASK_HI;
    volatile uint8      CanReserved9[24];
    volatile Can_WakeupMsgBufType   CanWMB[4];
    volatile uint8      CanReserved10[128];
    volatile uint32     CanFDCTRL;
    volatile uint32     CanFDCBT;
    volatile uint32     CanFDCRC;
} Can_RegType;


/*CAN414*/
/*CAN_Conf:073-075,383*/
typedef struct
{
    uint16  Baudrate;    /*CAN005_Conf*/
    uint8  CanCtrl10;
    uint8  CanCtrl12;
    uint8  CanCtrl13;
} Can_ControllerBaudrateConfigType;

/*CAN437*/
/*CAN_Conf:481,475-480*/
typedef struct
{
    uint16  CanFdBaudRate;    /*CAN005_Conf*/
    uint32  CanFDCTRL;
    uint32  CanCBT;
    uint32  CanCTRL2;
    uint32  CanFDCBT;
} Can_ControllerFDBaudrateConfigType;

typedef struct
{
    uint8      BDNum;
    uint8      DefaultBD;
    CONSTP2CONST(Can_ControllerBaudrateConfigType, TYPEDEF, CANIF_APPL_DATA) CtrlBDCfg;
#if(STD_ON == CAN_CANFD_SUPPORT)
    uint8      DefaultFDBD;
    CONSTP2CONST(Can_ControllerFDBaudrateConfigType, TYPEDEF, CANIF_APPL_DATA) CtrlFDBDCfg;
#endif
    uint32     CanGMask;
    uint32     CanIMask1;
    uint8      CanCtrl11;
#if(STD_ON == CAN_WAKEUP_SUPPORT)
    EcuM_WakeupSourceType src;
#endif
    Can_HwHandleType hrhStart;
    uint8 hrhNum;
    Can_HwHandleType hthStart;
    uint8 hthNum;
    uint8 CanFdDlc;
    uint8 OffsetAddr;
} Can_CtrlCfgType;

typedef struct
{
    uint8               CanCtrl11;
    uint32              CanIMask1;
} Can_OldIERType;

/*******************************************************************************
*  Register definitions
*******************************************************************************/

/**************** Can_RegType *****************************************/

#define CAN_CONTROLLER_BASIS_ADR(phyController)     \
    ((Can_RegType *)(CanBasisAddress[phyController]))

#define CAN_MCR0(phyController)                     \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR0)

#define CAN_MCR1(phyController)                     \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR1)

#define CAN_MCR2(phyController)                     \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR2)

#define CAN_MCR3(phyController)                     \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR3)

#define CAN_CTRL10(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL10)
#define CAN_CTRL11(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL11)
#define CAN_CTRL12(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL12)
#define CAN_CTRL13(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL13)

#define CAN_TIMER(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanTimer)

#define CAN_GMASK(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanGMask)

#define CAN_R14MASK(phyController)                  \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanR14Mask)

#define CAN_R15MASK(phyController)                  \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanR15Mask)

#define CAN_ESR1H(phyController)               \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanESR1H)

#define CAN_ESR1L(phyController)               \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanESR1L)

#define CAN_IMASK1(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIMask1)

#define CAN_IFLAG1(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIFlag1)
#define CAN_CTRL2(phyController)                    \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL2)

#define CAN_ESR2H(phyController)               \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanESR2H)

#define CAN_ESR2L(phyController)               \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanESR2L)
#define CAN_CRC(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCRC)
#define CAN_RXFGMASK(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanRXFGMask)
#define CAN_RXFIR(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanRXFIR)
#define CAN_CBT(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCBT)

#define CAN_MB_DATA(phyController,MBNum)                 \
    ((CAN_CONTROLLER_BASIS_ADR(phyController)->CanMBData)[MBNum])


#define CAN_MB_ADDR(phyController,OffsetAddr,MBNum)                 \
    (CanBasisAddress[phyController]+ ((uint32)0x80)+((OffsetAddr)*(MBNum)))

#define CAN_RXIMR(phyController,MBNum)        \
    ((CAN_CONTROLLER_BASIS_ADR(phyController)->CanRXIMR)[MBNum])
#define CAN_CTRL1_PN(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL1_PN)
#define CAN_CTRL2_PN(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL2_PN)
#define CAN_WU_MTC(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanWU_MTC)
#define CAN_FLT_ID1(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFLT_ID1)
#define CAN_FLT_DLC(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFLT_DLC)
#define CAN_PL1_LO(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanPL1_LO)
#define CAN_PL1_HI(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanPL1_HI)
#define CAN_FLT_ID2_IDMASK(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFLT_ID2_IDMASK)
#define CAN_PL2_PLMASK_LO(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanPL2_PLMASK_LO)
#define CAN_PL2_PLMASK_HI(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanPL2_PLMASK_HI)
#define CAN_FDCTRL(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFDCTRL)
#define CAN_FDCBT(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFDCBT)
#define CAN_FDCRC(phyController)                 \
    (CAN_CONTROLLER_BASIS_ADR(phyController)->CanFDCRC)
#define CAN_WMB(phyController,MBNum)                 \
    ((CAN_CONTROLLER_BASIS_ADR(phyController)->CanWMB)[MBNum])


#define CAN_PCC(phyController)     (*((volatile uint32 *)(0x40065090UL+0x4U*(phyController))))
#define CAN_PCC2                   (*((volatile uint32 *)(0x400650ACUL)))

#define CAN_PCC0                   (*((volatile uint32 *)(0x40065090UL)))

#define CAN_MCR            (*((volatile uint32 *)(0x40024000UL)))

#define CAN_CTRL1            (*((volatile uint32 *)(0x40024004UL)))


/*******************************************************************************
*  Register Mask Value define
*******************************************************************************/
#define CAN_PCC_INIT                                (0xC0000000UL)
#define CAN_PCC_TYPE01                              (0)
#define CAN_PCC_TYPE2                               (2)

#define CAN_EDL_MASK                                ((uint8)0x80U)
#define CAN_BRS_MASK                                ((uint8)0x40U)
#define CAN_ESI_MASK                                ((uint8)0x20U)
#define CAN_CODE_MASK                               ((uint8)0x0FU)

#define CAN_TX_MB_CODE_INACTIVE                     ((uint8)0x08U)
#define CAN_TX_MB_CODE_ABORT                        ((uint8)0x09U)
#define CAN_TX_MB_CODE_TRANS                        ((uint8)0x0CU)
#define CAN_TX_MB_CODE_TRANSED_REMOTE               ((uint8)0x04U)
#define CAN_TX_MB_CODE_TRANS_RESPOND_REMOTE         ((uint8)0x0AU)
#define CAN_TX_MB_CODE_TRANS_RESPONDING_REMOTE      ((uint8)0x0EU)

#define CAN_RX_MB_CODE_NOT_ACTIVE                   ((uint8)0x00U)
#define CAN_RX_MB_CODE_EMPTY                        ((uint8)0x04U)
#define CAN_RX_MB_CODE_FULL                         ((uint8)0x02U)
#define CAN_RX_MB_CODE_OVERRUN                      ((uint8)0x06U)
#define CAN_RX_MB_CODE_BUSY_TO_EMPTY                ((uint8)0x03U)
#define CAN_RX_MB_CODE_BUSY_TO_NOTEMP               ((uint8)0x07U)

/* Bitmask of CanMCR3*/
#define CAN_FRZ_ACK_MASK    ((uint8)0x01U)    /* Freeze Mode Acknowledge  */
#define CAN_SOFT_RST_MASK   ((uint8)0x02U)    /* Soft Reset */
#define CAN_NOT_READY_MASK  ((uint8)0x08U)    /* FlexCAN Not Ready */
#define CAN_HALT_MASK       ((uint8)0x10U)    /* Halt FlexCAN */
#define CAN_FEN_MASK        ((uint8)0x20U)    /* FIFO Enable */
#define CAN_FRZ_MASK        ((uint8)0x40U)    /* Freeze Enable */
#define CAN_MDIS_MASK       ((uint8)0x80U)    /* Module Disable */

/* Bitmask of CanMCR1*/
#define CAN_BCC_MASK        ((uint8)0x01U) /*Backwards Compatibility Configuration*/

/* Bitmask of CanCTRL3*/
#define CAN_BOFF_REC_MASK   ((uint8)0x40U)


/*Bitmask of CanMB.Length*/
#define CAN_SRR_MASK        ((uint8)0x40U)
#define CAN_IDE_MASK        ((uint8)0x20U)
#define CAN_FD_EDL_MASK     ((uint8)0x80UL)



#define CAN_RTR_MASK        ((uint8)0x10U)
#define CAN_DLC_MASK        ((uint8)0x0fU)

/*Bitmask of CanESRL*/
#define CAN_BOFF_MASK       ((uint16)0x04U)

#define CAN_TX_INT_MASK            ((uint8)0x01U)
#define CAN_RX_INT_MASK            ((uint8)0x02U)
#define CAN_BUSOFF_INT_MASK        ((uint8)0x80U)
#define CAN_ERR_INT_MASK           ((uint8)0x40U)
#define CAN_ERR_CTRL2INT_MASK      ((uint8)0x30U)

#define CAN_CONTROL_COUNT               ((uint8)250U)



#endif/* CAN_PL_H*/

