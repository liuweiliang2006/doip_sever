/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Cfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Com module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Com module configuration File
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
#include "Com.h"

#if(COM_TXIPDUNUM >= 1u)

/*******************************************************************************
*   Tx Msg Buffer 
*******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 
VAR(IpduNew_Message_21_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_21;
VAR(IpduNew_Message_22_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_22;
VAR(IpduNew_Message_23_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_23;
VAR(IpduNew_Message_24_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_24;
VAR(IpduNew_Message_25_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_25;
VAR(IpduNew_Message_26_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_26;
VAR(IpduNew_Message_27_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_27;
VAR(IpduNew_Message_28_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_28;
VAR(IpduNew_Message_29_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_29;
VAR(IpduNew_Message_30_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_30;
VAR(IpduNew_Message_31_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_31;
VAR(IpduNew_Message_32_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_32;
VAR(IpduNew_Message_33_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_33;
VAR(IpduNew_Message_34_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_34;
VAR(IpduPLG_General_Status_bufType, COM_PRIVATE_DATA) TxIpduPLG_General_Status;
VAR(IpduPLG_Setting_Control_Cmd_bufType, COM_PRIVATE_DATA) TxIpduPLG_Setting_Control_Cmd;

#define COM_STOP_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

/*******************************************************************************
*   for Tx Message and Signals 
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

CONST(IpduNew_Message_21_bufType, COM_CONFIG_CONST) TxIpduNew_Message_21DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_22_bufType, COM_CONFIG_CONST) TxIpduNew_Message_22DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_23_bufType, COM_CONFIG_CONST) TxIpduNew_Message_23DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_24_bufType, COM_CONFIG_CONST) TxIpduNew_Message_24DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_25_bufType, COM_CONFIG_CONST) TxIpduNew_Message_25DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_26_bufType, COM_CONFIG_CONST) TxIpduNew_Message_26DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_27_bufType, COM_CONFIG_CONST) TxIpduNew_Message_27DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_28_bufType, COM_CONFIG_CONST) TxIpduNew_Message_28DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_29_bufType, COM_CONFIG_CONST) TxIpduNew_Message_29DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_30_bufType, COM_CONFIG_CONST) TxIpduNew_Message_30DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_31_bufType, COM_CONFIG_CONST) TxIpduNew_Message_31DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_32_bufType, COM_CONFIG_CONST) TxIpduNew_Message_32DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_33_bufType, COM_CONFIG_CONST) TxIpduNew_Message_33DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_34_bufType, COM_CONFIG_CONST) TxIpduNew_Message_34DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduPLG_General_Status_bufType, COM_CONFIG_CONST) TxIpduPLG_General_StatusDefaultValue = 
{
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    }
};

CONST(IpduPLG_Setting_Control_Cmd_bufType, COM_CONFIG_CONST) TxIpduPLG_Setting_Control_CmdDefaultValue = 
{
    {
        0,0,0,0,0,0,0,0,0
    }
};

CONST(PduInfoType, COM_CONFIG_CONST) Com_TxIpduInitTable[COM_TXIPDUNUM] = 
{
	{TxIpduNew_Message_21._c, 8U},
	{TxIpduNew_Message_22._c, 8U},
	{TxIpduNew_Message_23._c, 8U},
	{TxIpduNew_Message_24._c, 8U},
	{TxIpduNew_Message_25._c, 8U},
	{TxIpduNew_Message_26._c, 8U},
	{TxIpduNew_Message_27._c, 8U},
	{TxIpduNew_Message_28._c, 8U},
	{TxIpduNew_Message_29._c, 8U},
	{TxIpduNew_Message_30._c, 8U},
	{TxIpduNew_Message_31._c, 8U},
	{TxIpduNew_Message_32._c, 8U},
	{TxIpduNew_Message_33._c, 8U},
	{TxIpduNew_Message_34._c, 8U},
	{TxIpduPLG_General_Status._c, 8U},
	{TxIpduPLG_Setting_Control_Cmd._c, 8U}
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduSigNum[COM_TXIPDUNUM] = 
{
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    8U,
    13U,
    2U
};

CONST(Com_TxSigTableType, COM_CONFIG_CONST) Com_TxSigTable[COM_TXSIGNUM] = 
{
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {0U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {1U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {2U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {3U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {4U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {5U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {6U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {7U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {8U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {9U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {10U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {11U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {12U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {13U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {14U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

    {15U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},
    {15U, COM_SENDTYPECYCLIC, (Com_SigInActiveType*)0},

};

CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST ) Com_TxIpduDefaultValue[COM_TXIPDUNUM] = 
{
   TxIpduNew_Message_21DefaultValue._c,
   TxIpduNew_Message_22DefaultValue._c,
   TxIpduNew_Message_23DefaultValue._c,
   TxIpduNew_Message_24DefaultValue._c,
   TxIpduNew_Message_25DefaultValue._c,
   TxIpduNew_Message_26DefaultValue._c,
   TxIpduNew_Message_27DefaultValue._c,
   TxIpduNew_Message_28DefaultValue._c,
   TxIpduNew_Message_29DefaultValue._c,
   TxIpduNew_Message_30DefaultValue._c,
   TxIpduNew_Message_31DefaultValue._c,
   TxIpduNew_Message_32DefaultValue._c,
   TxIpduNew_Message_33DefaultValue._c,
   TxIpduNew_Message_34DefaultValue._c,
   TxIpduPLG_General_StatusDefaultValue._c,
   TxIpduPLG_Setting_Control_CmdDefaultValue._c
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduTable[COM_TXIPDUNUM] = 
{
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR)
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduCycleTable[COM_TXIPDUNUM] = 
{
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U,
    100U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduFastCycleTable[COM_TXIPDUNUM] = 
{
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U
};

CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_TxSigOffsetTable[COM_TXIPDUNUM] = 
{
    0U,
    8U,
    16U,
    24U,
    32U,
    40U,
    48U,
    56U,
    64U,
    72U,
    80U,
    88U,
    96U,
    104U,
    112U,
    125U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTdelayTable[COM_TXIPDUNUM] = 
{
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduRepNumTable[COM_TXIPDUNUM] = 
{
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTimeOutTable[COM_TXIPDUNUM] = 
{
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduOffsetTable[COM_TXIPDUNUM] = 
{
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U
};

#ifdef COM_ENABLE_TXTOINDFUN
CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_TxIpduTOIndicationTable[COM_TXIPDUNUM] = 
{
    &AppIpduNew_Message_21_TxTOIndication,
    &AppIpduNew_Message_22_TxTOIndication,
    &AppIpduNew_Message_23_TxTOIndication,
    &AppIpduNew_Message_24_TxTOIndication,
    &AppIpduNew_Message_25_TxTOIndication,
    &AppIpduNew_Message_26_TxTOIndication,
    &AppIpduNew_Message_27_TxTOIndication,
    &AppIpduNew_Message_28_TxTOIndication,
    &AppIpduNew_Message_29_TxTOIndication,
    &AppIpduNew_Message_30_TxTOIndication,
    &AppIpduNew_Message_31_TxTOIndication,
    &AppIpduNew_Message_32_TxTOIndication,
    &AppIpduNew_Message_33_TxTOIndication,
    &AppIpduNew_Message_34_TxTOIndication,
    &AppIpduPLG_General_Status_TxTOIndication,
    &AppIpduPLG_Setting_Control_Cmd_TxTOIndication
};
#endif

#ifdef COM_ENABLE_TXCONFIRMATIONFUN
CONST(Com_TxConfirmationType, COM_CONFIG_CONST) Com_TxIpduConfirmTable[COM_TXIPDUNUM] = 
{
    &AppIpduNew_Message_21_Conf,
    &AppIpduNew_Message_22_Conf,
    &AppIpduNew_Message_23_Conf,
    &AppIpduNew_Message_24_Conf,
    &AppIpduNew_Message_25_Conf,
    &AppIpduNew_Message_26_Conf,
    &AppIpduNew_Message_27_Conf,
    &AppIpduNew_Message_28_Conf,
    &AppIpduNew_Message_29_Conf,
    &AppIpduNew_Message_30_Conf,
    &AppIpduNew_Message_31_Conf,
    &AppIpduNew_Message_32_Conf,
    &AppIpduNew_Message_33_Conf,
    &AppIpduNew_Message_34_Conf,
    &AppIpduPLG_General_Status_Conf,
    &AppIpduPLG_Setting_Control_Cmd_Conf
};
#endif

CONST(PduIdType, COM_CONFIG_CONST) Com_TxIpduIdMapTable[COM_TXIPDUNUM]=
{
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U,
    8U,
    9U,
    10U,
    11U,
    12U,
    13U,
    14U,
    15U
};
 
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
 
#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM >= 1u)

/*******************************************************************************
*   Rx Msg Buffer 
*******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 
VAR(IpduNew_Message_R1_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R1;
VAR(IpduNew_Message_R2_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R2;
VAR(IpduNew_Message_R3_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R3;
VAR(IpduNew_Message_R4_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R4;
VAR(IpduNew_Message_R5_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R5;
VAR(IpduNew_Message_R6_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R6;
VAR(IpduNew_Message_R7_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R7;
VAR(IpduNew_Message_R8_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R8;
VAR(IpduNew_Message_R9_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R9;
VAR(IpduNew_Message_R10_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R10;
VAR(IpduNew_Message_R11_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R11;
VAR(IpduNew_Message_R12_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R12;
VAR(IpduNew_Message_R13_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R13;
VAR(IpduNew_Message_R14_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R14;
VAR(IpduNew_Message_R15_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R15;
VAR(IpduNew_Message_R16_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R16;
VAR(IpduNew_Message_R17_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R17;
VAR(IpduNew_Message_R18_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R18;
VAR(IpduNew_Message_R19_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R19;
VAR(IpduNew_Message_R20_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R20;
VAR(IpduNew_Message_R21_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R21;
VAR(IpduNew_Message_R22_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R22;
VAR(IpduNew_Message_R23_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R23;
VAR(IpduNew_Message_R24_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R24;
VAR(IpduNew_Message_R25_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R25;
VAR(IpduNew_Message_R26_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R26;
VAR(IpduNew_Message_R27_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R27;
VAR(IpduNew_Message_R28_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R28;
VAR(IpduNew_Message_R29_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R29;
VAR(IpduNew_Message_R30_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R30;
VAR(IpduNew_Message_R31_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R31;
VAR(IpduNew_Message_R32_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R32;
VAR(IpduNew_Message_R33_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R33;
VAR(IpduNew_Message_R34_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R34;
VAR(IpduNew_Message_R35_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R35;
VAR(IpduNew_Message_R36_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R36;
VAR(IpduNew_Message_R37_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R37;
VAR(IpduNew_Message_R38_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R38;
VAR(IpduNew_Message_R39_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R39;
VAR(IpduNew_Message_R40_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R40;
VAR(IpduNew_Message_R41_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R41;
VAR(IpduNew_Message_R42_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R42;
VAR(IpduNew_Message_R43_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R43;
VAR(IpduNew_Message_R44_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R44;
VAR(IpduNew_Message_R45_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R45;
VAR(IpduNew_Message_R46_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R46;
VAR(IpduNew_Message_R47_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R47;
VAR(IpduNew_Message_R48_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R48;
VAR(IpduNew_Message_R49_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R49;
VAR(IpduNew_Message_R50_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R50;
VAR(IpduNew_Message_R51_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R51;
VAR(IpduNew_Message_R52_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R52;
VAR(IpduNew_Message_R53_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R53;
VAR(IpduNew_Message_R54_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R54;
VAR(IpduNew_Message_R55_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R55;
VAR(IpduNew_Message_R56_bufType, COM_PRIVATE_DATA) RxIpduNew_Message_R56;
VAR(IpduPPEI_Engine_General_Status_1_bufType, COM_PRIVATE_DATA) RxIpduPPEI_Engine_General_Status_1;
VAR(IpduVehicle_Odometer_bufType, COM_PRIVATE_DATA) RxIpduVehicle_Odometer;
VAR(IpduPEPS_Door_Lock_Command_bufType, COM_PRIVATE_DATA) RxIpduPEPS_Door_Lock_Command;
VAR(IpduAatilock_Brake_and_TC_Status_HS_bufType, COM_PRIVATE_DATA) RxIpduAatilock_Brake_and_TC_Status_HS;
VAR(IpduPPEI_Platform_General_Status_bufType, COM_PRIVATE_DATA) RxIpduPPEI_Platform_General_Status;
VAR(IpduAC_Torque_Status_bufType, COM_PRIVATE_DATA) RxIpduAC_Torque_Status;
VAR(IpduPEPS_General_Status_bufType, COM_PRIVATE_DATA) RxIpduPEPS_General_Status;

#define COM_STOP_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

/*******************************************************************************
*   for Rx Message and Signals 
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

CONST(IpduNew_Message_R1_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R1DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R2_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R2DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R3_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R3DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R4_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R4DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R5_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R5DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R6_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R6DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R7_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R7DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R8_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R8DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R9_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R9DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R10_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R10DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R11_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R11DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R12_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R12DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R13_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R13DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R14_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R14DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R15_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R15DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R16_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R16DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R17_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R17DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R18_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R18DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R19_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R19DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R20_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R20DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R21_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R21DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R22_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R22DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R23_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R23DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R24_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R24DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R25_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R25DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R26_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R26DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R27_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R27DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R28_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R28DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R29_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R29DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R30_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R30DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R31_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R31DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R32_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R32DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R33_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R33DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R34_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R34DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R35_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R35DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R36_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R36DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R37_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R37DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R38_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R38DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R39_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R39DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R40_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R40DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R41_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R41DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R42_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R42DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R43_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R43DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R44_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R44DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R45_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R45DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R46_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R46DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R47_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R47DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R48_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R48DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R49_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R49DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R50_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R50DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R51_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R51DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R52_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R52DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R53_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R53DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R54_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R54DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R55_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R55DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduNew_Message_R56_bufType, COM_CONFIG_CONST) RxIpduNew_Message_R56DefaultValue = 
{
    {
        0,0,0,0,0,0,0,0
    }
};

CONST(IpduPPEI_Engine_General_Status_1_bufType, COM_CONFIG_CONST) RxIpduPPEI_Engine_General_Status_1DefaultValue = 
{
    {
        0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    }
};

CONST(IpduVehicle_Odometer_bufType, COM_CONFIG_CONST) RxIpduVehicle_OdometerDefaultValue = 
{
    {
        0,0,0,0,1,0
    }
};

CONST(IpduPEPS_Door_Lock_Command_bufType, COM_CONFIG_CONST) RxIpduPEPS_Door_Lock_CommandDefaultValue = 
{
    {
        0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0
    }
};

CONST(IpduAatilock_Brake_and_TC_Status_HS_bufType, COM_CONFIG_CONST) RxIpduAatilock_Brake_and_TC_Status_HSDefaultValue = 
{
    {
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0
    }
};

CONST(IpduPPEI_Platform_General_Status_bufType, COM_CONFIG_CONST) RxIpduPPEI_Platform_General_StatusDefaultValue = 
{
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    }
};

CONST(IpduAC_Torque_Status_bufType, COM_CONFIG_CONST) RxIpduAC_Torque_StatusDefaultValue = 
{
    {
        0,0,0,0,0,0,0,0,0,0
    }
};

CONST(IpduPEPS_General_Status_bufType, COM_CONFIG_CONST) RxIpduPEPS_General_StatusDefaultValue = 
{
    {
        1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0
    }
};

CONST(PduInfoType, COM_CONFIG_CONST) Com_RxIpduInitTable[COM_RXIPDUNUM] = 
{
	{RxIpduNew_Message_R1._c, 8U},
	{RxIpduNew_Message_R2._c, 8U},
	{RxIpduNew_Message_R3._c, 8U},
	{RxIpduNew_Message_R4._c, 8U},
	{RxIpduNew_Message_R5._c, 8U},
	{RxIpduNew_Message_R6._c, 8U},
	{RxIpduNew_Message_R7._c, 8U},
	{RxIpduNew_Message_R8._c, 8U},
	{RxIpduNew_Message_R9._c, 8U},
	{RxIpduNew_Message_R10._c, 8U},
	{RxIpduNew_Message_R11._c, 8U},
	{RxIpduNew_Message_R12._c, 8U},
	{RxIpduNew_Message_R13._c, 8U},
	{RxIpduNew_Message_R14._c, 8U},
	{RxIpduNew_Message_R15._c, 8U},
	{RxIpduNew_Message_R16._c, 8U},
	{RxIpduNew_Message_R17._c, 8U},
	{RxIpduNew_Message_R18._c, 8U},
	{RxIpduNew_Message_R19._c, 8U},
	{RxIpduNew_Message_R20._c, 8U},
	{RxIpduNew_Message_R21._c, 8U},
	{RxIpduNew_Message_R22._c, 8U},
	{RxIpduNew_Message_R23._c, 8U},
	{RxIpduNew_Message_R24._c, 8U},
	{RxIpduNew_Message_R25._c, 8U},
	{RxIpduNew_Message_R26._c, 8U},
	{RxIpduNew_Message_R27._c, 8U},
	{RxIpduNew_Message_R28._c, 8U},
	{RxIpduNew_Message_R29._c, 8U},
	{RxIpduNew_Message_R30._c, 8U},
	{RxIpduNew_Message_R31._c, 8U},
	{RxIpduNew_Message_R32._c, 8U},
	{RxIpduNew_Message_R33._c, 8U},
	{RxIpduNew_Message_R34._c, 8U},
	{RxIpduNew_Message_R35._c, 8U},
	{RxIpduNew_Message_R36._c, 8U},
	{RxIpduNew_Message_R37._c, 8U},
	{RxIpduNew_Message_R38._c, 8U},
	{RxIpduNew_Message_R39._c, 8U},
	{RxIpduNew_Message_R40._c, 8U},
	{RxIpduNew_Message_R41._c, 8U},
	{RxIpduNew_Message_R42._c, 8U},
	{RxIpduNew_Message_R43._c, 8U},
	{RxIpduNew_Message_R44._c, 8U},
	{RxIpduNew_Message_R45._c, 8U},
	{RxIpduNew_Message_R46._c, 8U},
	{RxIpduNew_Message_R47._c, 8U},
	{RxIpduNew_Message_R48._c, 8U},
	{RxIpduNew_Message_R49._c, 8U},
	{RxIpduNew_Message_R50._c, 8U},
	{RxIpduNew_Message_R51._c, 8U},
	{RxIpduNew_Message_R52._c, 8U},
	{RxIpduNew_Message_R53._c, 8U},
	{RxIpduNew_Message_R54._c, 8U},
	{RxIpduNew_Message_R55._c, 8U},
	{RxIpduNew_Message_R56._c, 8U},
	{RxIpduPPEI_Engine_General_Status_1._c, 8U},
	{RxIpduVehicle_Odometer._c, 5U},
	{RxIpduPEPS_Door_Lock_Command._c, 8U},
	{RxIpduAatilock_Brake_and_TC_Status_HS._c, 8U},
	{RxIpduPPEI_Platform_General_Status._c, 8U},
	{RxIpduAC_Torque_Status._c, 8U},
	{RxIpduPEPS_General_Status._c, 8U}
};

CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST ) Com_RxIpduDefaultValue[COM_RXIPDUNUM] = 
{
   RxIpduNew_Message_R1DefaultValue._c,
   RxIpduNew_Message_R2DefaultValue._c,
   RxIpduNew_Message_R3DefaultValue._c,
   RxIpduNew_Message_R4DefaultValue._c,
   RxIpduNew_Message_R5DefaultValue._c,
   RxIpduNew_Message_R6DefaultValue._c,
   RxIpduNew_Message_R7DefaultValue._c,
   RxIpduNew_Message_R8DefaultValue._c,
   RxIpduNew_Message_R9DefaultValue._c,
   RxIpduNew_Message_R10DefaultValue._c,
   RxIpduNew_Message_R11DefaultValue._c,
   RxIpduNew_Message_R12DefaultValue._c,
   RxIpduNew_Message_R13DefaultValue._c,
   RxIpduNew_Message_R14DefaultValue._c,
   RxIpduNew_Message_R15DefaultValue._c,
   RxIpduNew_Message_R16DefaultValue._c,
   RxIpduNew_Message_R17DefaultValue._c,
   RxIpduNew_Message_R18DefaultValue._c,
   RxIpduNew_Message_R19DefaultValue._c,
   RxIpduNew_Message_R20DefaultValue._c,
   RxIpduNew_Message_R21DefaultValue._c,
   RxIpduNew_Message_R22DefaultValue._c,
   RxIpduNew_Message_R23DefaultValue._c,
   RxIpduNew_Message_R24DefaultValue._c,
   RxIpduNew_Message_R25DefaultValue._c,
   RxIpduNew_Message_R26DefaultValue._c,
   RxIpduNew_Message_R27DefaultValue._c,
   RxIpduNew_Message_R28DefaultValue._c,
   RxIpduNew_Message_R29DefaultValue._c,
   RxIpduNew_Message_R30DefaultValue._c,
   RxIpduNew_Message_R31DefaultValue._c,
   RxIpduNew_Message_R32DefaultValue._c,
   RxIpduNew_Message_R33DefaultValue._c,
   RxIpduNew_Message_R34DefaultValue._c,
   RxIpduNew_Message_R35DefaultValue._c,
   RxIpduNew_Message_R36DefaultValue._c,
   RxIpduNew_Message_R37DefaultValue._c,
   RxIpduNew_Message_R38DefaultValue._c,
   RxIpduNew_Message_R39DefaultValue._c,
   RxIpduNew_Message_R40DefaultValue._c,
   RxIpduNew_Message_R41DefaultValue._c,
   RxIpduNew_Message_R42DefaultValue._c,
   RxIpduNew_Message_R43DefaultValue._c,
   RxIpduNew_Message_R44DefaultValue._c,
   RxIpduNew_Message_R45DefaultValue._c,
   RxIpduNew_Message_R46DefaultValue._c,
   RxIpduNew_Message_R47DefaultValue._c,
   RxIpduNew_Message_R48DefaultValue._c,
   RxIpduNew_Message_R49DefaultValue._c,
   RxIpduNew_Message_R50DefaultValue._c,
   RxIpduNew_Message_R51DefaultValue._c,
   RxIpduNew_Message_R52DefaultValue._c,
   RxIpduNew_Message_R53DefaultValue._c,
   RxIpduNew_Message_R54DefaultValue._c,
   RxIpduNew_Message_R55DefaultValue._c,
   RxIpduNew_Message_R56DefaultValue._c,
   RxIpduPPEI_Engine_General_Status_1DefaultValue._c,
   RxIpduVehicle_OdometerDefaultValue._c,
   RxIpduPEPS_Door_Lock_CommandDefaultValue._c,
   RxIpduAatilock_Brake_and_TC_Status_HSDefaultValue._c,
   RxIpduPPEI_Platform_General_StatusDefaultValue._c,
   RxIpduAC_Torque_StatusDefaultValue._c,
   RxIpduPEPS_General_StatusDefaultValue._c
};

CONST(PduLengthType, COM_CONFIG_CONST) Com_RxIpduBufferSize[COM_RXIPDUNUM]=
{
    COM_RXIPDUNew_Message_R1_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R2_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R3_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R4_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R5_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R6_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R7_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R8_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R9_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R10_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R11_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R12_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R13_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R14_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R15_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R16_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R17_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R18_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R19_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R20_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R21_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R22_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R23_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R24_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R25_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R26_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R27_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R28_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R29_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R30_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R31_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R32_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R33_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R34_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R35_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R36_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R37_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R38_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R39_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R40_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R41_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R42_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R43_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R44_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R45_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R46_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R47_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R48_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R49_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R50_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R51_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R52_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R53_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R54_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R55_BUFFER_SIZE,
    COM_RXIPDUNew_Message_R56_BUFFER_SIZE,
    COM_RXIPDUPPEI_Engine_General_Status_1_BUFFER_SIZE,
    COM_RXIPDUVehicle_Odometer_BUFFER_SIZE,
    COM_RXIPDUPEPS_Door_Lock_Command_BUFFER_SIZE,
    COM_RXIPDUAatilock_Brake_and_TC_Status_HS_BUFFER_SIZE,
    COM_RXIPDUPPEI_Platform_General_Status_BUFFER_SIZE,
    COM_RXIPDUAC_Torque_Status_BUFFER_SIZE,
    COM_RXIPDUPEPS_General_Status_BUFFER_SIZE
};

CONST(uint8, COM_CONFIG_CONST) Com_RxIpduSigNum[COM_RXIPDUNUM] = 
{
    8U,
    8U,
    8U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    14U,
    2U,
    6U,
    8U,
    4U,
    3U,
    17U
};

CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_RxSigOffsetTable[COM_RXIPDUNUM] = 
{
    0U,
    8U,
    16U,
    24U,
    25U,
    26U,
    27U,
    28U,
    29U,
    30U,
    31U,
    32U,
    33U,
    34U,
    35U,
    36U,
    37U,
    38U,
    39U,
    40U,
    41U,
    42U,
    43U,
    44U,
    45U,
    46U,
    47U,
    48U,
    49U,
    50U,
    51U,
    52U,
    53U,
    54U,
    55U,
    56U,
    57U,
    58U,
    59U,
    60U,
    61U,
    62U,
    63U,
    64U,
    65U,
    66U,
    67U,
    68U,
    69U,
    70U,
    71U,
    72U,
    73U,
    74U,
    75U,
    76U,
    77U,
    91U,
    93U,
    99U,
    107U,
    111U,
    114U
};

CONST(Com_RxSigTableType, COM_CONFIG_CONST) Com_RxSigTable[COM_RXSIGNUM] = 
{
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {0U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {1U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {2U, 0U},
    {3U, 0U},
    {4U, 0U},
    {5U, 0U},
    {6U, 0U},
    {7U, 0U},
    {8U, 0U},
    {9U, 0U},
    {10U, 0U},
    {11U, 0U},
    {12U, 0U},
    {13U, 0U},
    {14U, 0U},
    {15U, 0U},
    {16U, 0U},
    {17U, 0U},
    {18U, 0U},
    {19U, 0U},
    {20U, 0U},
    {21U, 0U},
    {22U, 0U},
    {23U, 0U},
    {24U, 0U},
    {25U, 0U},
    {26U, 0U},
    {27U, 0U},
    {28U, 0U},
    {29U, 0U},
    {30U, 0U},
    {31U, 0U},
    {32U, 0U},
    {33U, 0U},
    {34U, 0U},
    {35U, 0U},
    {36U, 0U},
    {37U, 0U},
    {38U, 0U},
    {39U, 0U},
    {40U, 0U},
    {41U, 0U},
    {42U, 0U},
    {43U, 0U},
    {44U, 0U},
    {45U, 0U},
    {46U, 0U},
    {47U, 0U},
    {48U, 0U},
    {49U, 0U},
    {50U, 0U},
    {51U, 0U},
    {52U, 0U},
    {53U, 0U},
    {54U, 0U},
    {55U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {56U, 0U},
    {57U, 0U},
    {57U, 0U},
    {58U, 0U},
    {58U, 0U},
    {58U, 0U},
    {58U, 0U},
    {58U, 0U},
    {58U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {59U, 0U},
    {60U, 0U},
    {60U, 0U},
    {60U, 0U},
    {60U, 0U},
    {61U, 0U},
    {61U, 0U},
    {61U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
    {62U, 0U},
};

CONST(Com_RxIpduTableType, COM_CONFIG_CONST) Com_RxIpduTable[COM_RXIPDUNUM] = 
{
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 400U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 400U},
    {COM_RXTIMEOUTMONITOR_YES, 400U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},//
    {COM_RXTIMEOUTMONITOR_YES, 200U},
    {COM_RXTIMEOUTMONITOR_YES, 200U},
    {COM_RXTIMEOUTMONITOR_YES, 1000U},
    {COM_RXTIMEOUTMONITOR_YES, 1000U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},//
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 400U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 400U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},//
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 1000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},//
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 4000U},//
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 4000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 2000U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_NO, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},//
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U},
    {COM_RXTIMEOUTMONITOR_YES, 0U}
};

#ifdef COM_ENABLE_RXINDICATIONFUN
CONST(Com_RxIndicationType, COM_CONFIG_CONST) Com_RxIpduIndicationTable[COM_RXIPDUNUM] = 
{
    &AppIpduNew_Message_R1_Ind,
    &AppIpduNew_Message_R2_Ind,
    &AppIpduNew_Message_R3_Ind,
    &AppIpduNew_Message_R4_Ind,
    &AppIpduNew_Message_R5_Ind,
    &AppIpduNew_Message_R6_Ind,
    &AppIpduNew_Message_R7_Ind,
    &AppIpduNew_Message_R8_Ind,
    &AppIpduNew_Message_R9_Ind,
    &AppIpduNew_Message_R10_Ind,
    &AppIpduNew_Message_R11_Ind,
    &AppIpduNew_Message_R12_Ind,
    &AppIpduNew_Message_R13_Ind,
    &AppIpduNew_Message_R14_Ind,
    &AppIpduNew_Message_R15_Ind,
    &AppIpduNew_Message_R16_Ind,
    &AppIpduNew_Message_R17_Ind,
    &AppIpduNew_Message_R18_Ind,
    &AppIpduNew_Message_R19_Ind,
    &AppIpduNew_Message_R20_Ind,
    &AppIpduNew_Message_R21_Ind,
    &AppIpduNew_Message_R22_Ind,
    &AppIpduNew_Message_R23_Ind,
    &AppIpduNew_Message_R24_Ind,
    &AppIpduNew_Message_R25_Ind,
    &AppIpduNew_Message_R26_Ind,
    &AppIpduNew_Message_R27_Ind,
    &AppIpduNew_Message_R28_Ind,
    &AppIpduNew_Message_R29_Ind,
    &AppIpduNew_Message_R30_Ind,
    &AppIpduNew_Message_R31_Ind,
    &AppIpduNew_Message_R32_Ind,
    &AppIpduNew_Message_R33_Ind,
    &AppIpduNew_Message_R34_Ind,
    &AppIpduNew_Message_R35_Ind,
    &AppIpduNew_Message_R36_Ind,
    &AppIpduNew_Message_R37_Ind,
    &AppIpduNew_Message_R38_Ind,
    &AppIpduNew_Message_R39_Ind,
    &AppIpduNew_Message_R40_Ind,
    &AppIpduNew_Message_R41_Ind,
    &AppIpduNew_Message_R42_Ind,
    &AppIpduNew_Message_R43_Ind,
    &AppIpduNew_Message_R44_Ind,
    &AppIpduNew_Message_R45_Ind,
    &AppIpduNew_Message_R46_Ind,
    &AppIpduNew_Message_R47_Ind,
    &AppIpduNew_Message_R48_Ind,
    &AppIpduNew_Message_R49_Ind,
    &AppIpduNew_Message_R50_Ind,
    &AppIpduNew_Message_R51_Ind,
    &AppIpduNew_Message_R52_Ind,
    &AppIpduNew_Message_R53_Ind,
    &AppIpduNew_Message_R54_Ind,
    &AppIpduNew_Message_R55_Ind,
    &AppIpduNew_Message_R56_Ind,
    &AppIpduPPEI_Engine_General_Status_1_Ind,
    &AppIpduVehicle_Odometer_Ind,
    &AppIpduPEPS_Door_Lock_Command_Ind,
    &AppIpduAatilock_Brake_and_TC_Status_HS_Ind,
    &AppIpduPPEI_Platform_General_Status_Ind,
    &AppIpduAC_Torque_Status_Ind,
    &AppIpduPEPS_General_Status_Ind
};
#endif

#ifdef COM_ENABLE_RXTOINDFUN
CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_RxIpduTOIndicationTable[COM_RXIPDUNUM] = 
{
    &AppRxIpduNew_Message_R1_TimeOutInd,
    &AppRxIpduNew_Message_R2_TimeOutInd,
    &AppRxIpduNew_Message_R3_TimeOutInd,
    &AppRxIpduNew_Message_R4_TimeOutInd,
    &AppRxIpduNew_Message_R5_TimeOutInd,
    &AppRxIpduNew_Message_R6_TimeOutInd,
    &AppRxIpduNew_Message_R7_TimeOutInd,
    &AppRxIpduNew_Message_R8_TimeOutInd,
    &AppRxIpduNew_Message_R9_TimeOutInd,
    &AppRxIpduNew_Message_R10_TimeOutInd,
    &AppRxIpduNew_Message_R11_TimeOutInd,
    &AppRxIpduNew_Message_R12_TimeOutInd,
    &AppRxIpduNew_Message_R13_TimeOutInd,
    &AppRxIpduNew_Message_R14_TimeOutInd,
    &AppRxIpduNew_Message_R15_TimeOutInd,
    &AppRxIpduNew_Message_R16_TimeOutInd,
    &AppRxIpduNew_Message_R17_TimeOutInd,
    &AppRxIpduNew_Message_R18_TimeOutInd,
    &AppRxIpduNew_Message_R19_TimeOutInd,
    &AppRxIpduNew_Message_R20_TimeOutInd,
    &AppRxIpduNew_Message_R21_TimeOutInd,
    &AppRxIpduNew_Message_R22_TimeOutInd,
    &AppRxIpduNew_Message_R23_TimeOutInd,
    &AppRxIpduNew_Message_R24_TimeOutInd,
    &AppRxIpduNew_Message_R25_TimeOutInd,
    &AppRxIpduNew_Message_R26_TimeOutInd,
    &AppRxIpduNew_Message_R27_TimeOutInd,
    &AppRxIpduNew_Message_R28_TimeOutInd,
    &AppRxIpduNew_Message_R29_TimeOutInd,
    &AppRxIpduNew_Message_R30_TimeOutInd,
    &AppRxIpduNew_Message_R31_TimeOutInd,
    &AppRxIpduNew_Message_R32_TimeOutInd,
    &AppRxIpduNew_Message_R33_TimeOutInd,
    &AppRxIpduNew_Message_R34_TimeOutInd,
    &AppRxIpduNew_Message_R35_TimeOutInd,
    &AppRxIpduNew_Message_R36_TimeOutInd,
    &AppRxIpduNew_Message_R37_TimeOutInd,
    &AppRxIpduNew_Message_R38_TimeOutInd,
    &AppRxIpduNew_Message_R39_TimeOutInd,
    &AppRxIpduNew_Message_R40_TimeOutInd,
    &AppRxIpduNew_Message_R41_TimeOutInd,
    &AppRxIpduNew_Message_R42_TimeOutInd,
    &AppRxIpduNew_Message_R43_TimeOutInd,
    &AppRxIpduNew_Message_R44_TimeOutInd,
    &AppRxIpduNew_Message_R45_TimeOutInd,
    &AppRxIpduNew_Message_R46_TimeOutInd,
    &AppRxIpduNew_Message_R47_TimeOutInd,
    &AppRxIpduNew_Message_R48_TimeOutInd,
    &AppRxIpduNew_Message_R49_TimeOutInd,
    &AppRxIpduNew_Message_R50_TimeOutInd,
    &AppRxIpduNew_Message_R51_TimeOutInd,
    &AppRxIpduNew_Message_R52_TimeOutInd,
    &AppRxIpduNew_Message_R53_TimeOutInd,
    &AppRxIpduNew_Message_R54_TimeOutInd,
    &AppRxIpduNew_Message_R55_TimeOutInd,
    &AppRxIpduNew_Message_R56_TimeOutInd,
    &AppRxIpduPPEI_Engine_General_Status_1_TimeOutInd,
    &AppRxIpduVehicle_Odometer_TimeOutInd,
    &AppRxIpduPEPS_Door_Lock_Command_TimeOutInd,
    &AppRxIpduAatilock_Brake_and_TC_Status_HS_TimeOutInd,
    &AppRxIpduPPEI_Platform_General_Status_TimeOutInd,
    &AppRxIpduAC_Torque_Status_TimeOutInd,
    &AppRxIpduPEPS_General_Status_TimeOutInd
};
#endif
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif /*#if(COM_RXIPDUNUM>=1)*/

#ifdef COM_ENABLE_ROUTESIGNAL

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))
CONST(Com_SignalGatewayTableType, COM_CONFIG_CONST) Com_SignalGatewayTable[COM_GWSIGNUM]=
{
};

CONST(Com_SignalGatewayIpduTableType, COM_CONFIG_CONST) Com_SignalGatewayIpduTable[COM_GWIPDUNUM]=
{
};
#endif/*#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))*/

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif/*#ifdef COM_ENABLE_ROUTESIGNAL*/

#if(COM_GROUPIPDUNUM >= 1)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

CONST(Com_GroupIpduTableType, COM_CONFIG_CONST) Com_GroupIpduTable[COM_GROUPIPDUNUM]=
{
    {0U, COM_DIRECTION_TX},
    {1U, COM_DIRECTION_TX},
    {2U, COM_DIRECTION_TX},
    {3U, COM_DIRECTION_TX},
    {4U, COM_DIRECTION_TX},
    {5U, COM_DIRECTION_TX},
    {6U, COM_DIRECTION_TX},
    {7U, COM_DIRECTION_TX},
    {8U, COM_DIRECTION_TX},
    {9U, COM_DIRECTION_TX},
    {10U, COM_DIRECTION_TX},
    {11U, COM_DIRECTION_TX},
    {12U, COM_DIRECTION_TX},
    {13U, COM_DIRECTION_TX},
    {14U, COM_DIRECTION_TX},
    {15U, COM_DIRECTION_TX},
    {0U, COM_DIRECTION_RX},
    {1U, COM_DIRECTION_RX},
    {2U, COM_DIRECTION_RX},
    {3U, COM_DIRECTION_RX},
    {4U, COM_DIRECTION_RX},
    {5U, COM_DIRECTION_RX},
    {6U, COM_DIRECTION_RX},
    {7U, COM_DIRECTION_RX},
    {8U, COM_DIRECTION_RX},
    {9U, COM_DIRECTION_RX},
    {10U, COM_DIRECTION_RX},
    {11U, COM_DIRECTION_RX},
    {12U, COM_DIRECTION_RX},
    {13U, COM_DIRECTION_RX},
    {14U, COM_DIRECTION_RX},
    {15U, COM_DIRECTION_RX},
    {16U, COM_DIRECTION_RX},
    {17U, COM_DIRECTION_RX},
    {18U, COM_DIRECTION_RX},
    {19U, COM_DIRECTION_RX},
    {20U, COM_DIRECTION_RX},
    {21U, COM_DIRECTION_RX},
    {22U, COM_DIRECTION_RX},
    {23U, COM_DIRECTION_RX},
    {24U, COM_DIRECTION_RX},
    {25U, COM_DIRECTION_RX},
    {26U, COM_DIRECTION_RX},
    {27U, COM_DIRECTION_RX},
    {28U, COM_DIRECTION_RX},
    {29U, COM_DIRECTION_RX},
    {30U, COM_DIRECTION_RX},
    {31U, COM_DIRECTION_RX},
    {32U, COM_DIRECTION_RX},
    {33U, COM_DIRECTION_RX},
    {34U, COM_DIRECTION_RX},
    {35U, COM_DIRECTION_RX},
    {36U, COM_DIRECTION_RX},
    {37U, COM_DIRECTION_RX},
    {38U, COM_DIRECTION_RX},
    {39U, COM_DIRECTION_RX},
    {40U, COM_DIRECTION_RX},
    {41U, COM_DIRECTION_RX},
    {42U, COM_DIRECTION_RX},
    {43U, COM_DIRECTION_RX},
    {44U, COM_DIRECTION_RX},
    {45U, COM_DIRECTION_RX},
    {46U, COM_DIRECTION_RX},
    {47U, COM_DIRECTION_RX},
    {48U, COM_DIRECTION_RX},
    {49U, COM_DIRECTION_RX},
    {50U, COM_DIRECTION_RX},
    {51U, COM_DIRECTION_RX},
    {52U, COM_DIRECTION_RX},
    {53U, COM_DIRECTION_RX},
    {54U, COM_DIRECTION_RX},
    {55U, COM_DIRECTION_RX},
    {56U, COM_DIRECTION_RX},
    {57U, COM_DIRECTION_RX},
    {58U, COM_DIRECTION_RX},
    {59U, COM_DIRECTION_RX},
    {60U, COM_DIRECTION_RX},
    {61U, COM_DIRECTION_RX},
    {62U, COM_DIRECTION_RX},
};

CONST(Com_IpduGroupTableType, COM_CONFIG_CONST) Com_IpduGroupTable[COM_IPDUGROUPNUM]=
{
    {0, 16},
    {16, 63},
};

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#endif
