/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Com.c
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
#include "Dcm_Cfg.h"
void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}
unsigned char canMessageReFlag;
void AppIpduNew_Message_21_Conf(void)
{
    canMessageReFlag = 1;
}

void AppIpduNew_Message_22_Conf(void)
{
}

void AppIpduNew_Message_23_Conf(void)
{
}

void AppIpduNew_Message_24_Conf(void)
{
}

void AppIpduNew_Message_25_Conf(void)
{
}

void AppIpduNew_Message_26_Conf(void)
{
}

void AppIpduNew_Message_27_Conf(void)
{
}

void AppIpduNew_Message_28_Conf(void)
{
}

void AppIpduNew_Message_29_Conf(void)
{
}

void AppIpduNew_Message_30_Conf(void)
{
}

void AppIpduNew_Message_31_Conf(void)
{
}

void AppIpduNew_Message_32_Conf(void)
{
}

void AppIpduNew_Message_33_Conf(void)
{
}

void AppIpduNew_Message_34_Conf(void)
{
}

void AppIpduPLG_General_Status_Conf(void)
{
}

void AppIpduPLG_Setting_Control_Cmd_Conf(void)
{
}

void AppIpduNew_Message_21_TxTOIndication(void)
{
}

void AppIpduNew_Message_22_TxTOIndication(void)
{
}

void AppIpduNew_Message_23_TxTOIndication(void)
{
}

void AppIpduNew_Message_24_TxTOIndication(void)
{
}

void AppIpduNew_Message_25_TxTOIndication(void)
{
}

void AppIpduNew_Message_26_TxTOIndication(void)
{
}

void AppIpduNew_Message_27_TxTOIndication(void)
{
}

void AppIpduNew_Message_28_TxTOIndication(void)
{
}

void AppIpduNew_Message_29_TxTOIndication(void)
{
}

void AppIpduNew_Message_30_TxTOIndication(void)
{
}

void AppIpduNew_Message_31_TxTOIndication(void)
{
}

void AppIpduNew_Message_32_TxTOIndication(void)
{
}

void AppIpduNew_Message_33_TxTOIndication(void)
{
}

void AppIpduNew_Message_34_TxTOIndication(void)
{
}

void AppIpduPLG_General_Status_TxTOIndication(void)
{
}

void AppIpduPLG_Setting_Control_Cmd_TxTOIndication(void)
{
}
uint8 DTCStatusCount[NUM_OF_DTC];
void AppIpduNew_Message_R1_Ind(void)
{
	;
}

void AppIpduNew_Message_R2_Ind(void)
{
	if(DTCStatus[2] & 0x08)
	{
		DTCStatusCount[2]++;
		if(DTCStatusCount[2] >=20)
		{
			DTCStatusCount[2] = 0;
			DTCStatus[2] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R3_Ind(void)
{
}

void AppIpduNew_Message_R4_Ind(void)
{
}

void AppIpduNew_Message_R5_Ind(void)
{
}

void AppIpduNew_Message_R6_Ind(void)
{
	if(DTCStatus[3] & 0x08)
	{
		DTCStatusCount[3]++;
		if(DTCStatusCount[3] >=20)
		{
			DTCStatusCount[3] = 0;
			DTCStatus[3] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R7_Ind(void)
{
	if(DTCStatus[4] & 0x08)
	{
		DTCStatusCount[4]++;
		if(DTCStatusCount[4] >=20)
		{
			DTCStatusCount[4] = 0;
			DTCStatus[4] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R8_Ind(void)
{
}

void AppIpduNew_Message_R9_Ind(void)
{
}

void AppIpduNew_Message_R10_Ind(void)
{
}

void AppIpduNew_Message_R11_Ind(void)
{
	if(DTCStatus[20] & 0x08)
	{
		DTCStatusCount[20]++;
		if(DTCStatusCount[20] >=20)
		{
			DTCStatusCount[20] = 0;
			DTCStatus[20] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R12_Ind(void)
{
	if(DTCStatus[19] & 0x08)
	{
		DTCStatusCount[19]++;
		if(DTCStatusCount[19] >=20)
		{
			DTCStatusCount[19] = 0;
			DTCStatus[19] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R13_Ind(void)
{
	if(DTCStatus[18] & 0x08)
	{
		DTCStatusCount[18]++;
		if(DTCStatusCount[18] >=20)
		{
			DTCStatusCount[18] = 0;
			DTCStatus[18] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R14_Ind(void)
{
	if(DTCStatus[15] & 0x08)
	{
		DTCStatusCount[15]++;
		if(DTCStatusCount[15] >=20)
		{
			DTCStatusCount[15] = 0;
			DTCStatus[15] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R15_Ind(void)
{
	if(DTCStatus[9] & 0x08)
	{
		DTCStatusCount[9]++;
		if(DTCStatusCount[9] >=20)
		{
			DTCStatusCount[9] = 0;
			DTCStatus[9] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R16_Ind(void)
{
}

void AppIpduNew_Message_R17_Ind(void)
{
}

void AppIpduNew_Message_R18_Ind(void)
{
}

void AppIpduNew_Message_R19_Ind(void)
{
}

void AppIpduNew_Message_R20_Ind(void)
{
	;
}

void AppIpduNew_Message_R21_Ind(void)
{
	if(DTCStatus[12] & 0x08)
	{
		DTCStatusCount[12]++;
		if(DTCStatusCount[12] >=20)
		{
			DTCStatusCount[12] = 0;
			DTCStatus[12] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R22_Ind(void)
{
}

void AppIpduNew_Message_R23_Ind(void)
{
	if(DTCStatus[7] & 0x08)
	{
		DTCStatusCount[7]++;
		if(DTCStatusCount[7] >=20)
		{
			DTCStatusCount[7] = 0;
			DTCStatus[7] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R24_Ind(void)
{

}

void AppIpduNew_Message_R25_Ind(void)
{
	if(DTCStatus[8] & 0x08)
	{
		DTCStatusCount[8]++;
		if(DTCStatusCount[8] >=20)
		{
			DTCStatusCount[8] = 0;
			DTCStatus[8] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R26_Ind(void)
{
}

void AppIpduNew_Message_R27_Ind(void)
{
	if(DTCStatus[6] & 0x08)
	{
		DTCStatusCount[6]++;
		if(DTCStatusCount[6] >=20)
		{
			DTCStatusCount[6] = 0;
			DTCStatus[6] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R28_Ind(void)
{
}

void AppIpduNew_Message_R29_Ind(void)
{
}

void AppIpduNew_Message_R30_Ind(void)
{
}

void AppIpduNew_Message_R31_Ind(void)
{
}

void AppIpduNew_Message_R32_Ind(void)
{
	if(DTCStatus[10] & 0x08)
	{
		DTCStatusCount[10]++;
		if(DTCStatusCount[10] >=20)
		{
			DTCStatusCount[10] = 0;
			DTCStatus[10] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R33_Ind(void)
{
	if(DTCStatus[23] & 0x08)
	{
		DTCStatusCount[23]++;
		if(DTCStatusCount[23] >=20)
		{
			DTCStatusCount[23] = 0;
			DTCStatus[23] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R34_Ind(void)
{
}

void AppIpduNew_Message_R35_Ind(void)
{
	if(DTCStatus[5] & 0x08)
	{
		DTCStatusCount[5]++;
		if(DTCStatusCount[5] >=20)
		{
			DTCStatusCount[5] = 0;
			DTCStatus[5] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R36_Ind(void)
{
}

void AppIpduNew_Message_R37_Ind(void)
{
	if(DTCStatus[24] & 0x08)
	{
		DTCStatusCount[24]++;
		if(DTCStatusCount[24] >=20)
		{
			DTCStatusCount[24] = 0;
			DTCStatus[24] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R38_Ind(void)
{
}

void AppIpduNew_Message_R39_Ind(void)
{
}

void AppIpduNew_Message_R40_Ind(void)
{
}

void AppIpduNew_Message_R41_Ind(void)
{
}

void AppIpduNew_Message_R42_Ind(void)
{
}

void AppIpduNew_Message_R43_Ind(void)
{
}

void AppIpduNew_Message_R44_Ind(void)
{
}

void AppIpduNew_Message_R45_Ind(void)
{
}

void AppIpduNew_Message_R46_Ind(void)
{
}

void AppIpduNew_Message_R47_Ind(void)
{
}

void AppIpduNew_Message_R48_Ind(void)
{
	if(DTCStatus[21] & 0x08)
	{
		DTCStatusCount[21]++;
		if(DTCStatusCount[21] >=20)
		{
			DTCStatusCount[21] = 0;
			DTCStatus[21] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R49_Ind(void)
{
}

void AppIpduNew_Message_R50_Ind(void)
{
	if(DTCStatus[14] & 0x08)
	{
		DTCStatusCount[14]++;
		if(DTCStatusCount[14] >=20)
		{
			DTCStatusCount[14] = 0;
			DTCStatus[14] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R51_Ind(void)
{
	if(DTCStatus[17] & 0x08)
	{
		DTCStatusCount[17]++;
		if(DTCStatusCount[17] >=20)
		{
			DTCStatusCount[17] = 0;
			DTCStatus[17] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R52_Ind(void)
{
	if(DTCStatus[11] & 0x08)
	{
		DTCStatusCount[11]++;
		if(DTCStatusCount[11] >=20)
		{
			DTCStatusCount[11] = 0;
			DTCStatus[11] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R53_Ind(void)
{
}

void AppIpduNew_Message_R54_Ind(void)
{
	if(DTCStatus[22] & 0x08)
	{
		DTCStatusCount[22]++;
		if(DTCStatusCount[22] >=20)
		{
			DTCStatusCount[22] = 0;
			DTCStatus[22] &= 0xf7;
		}
	}
}

void AppIpduNew_Message_R55_Ind(void)
{
}

void AppIpduNew_Message_R56_Ind(void)
{
	if(DTCStatus[13] & 0x08)
	{
		DTCStatusCount[13]++;
		if(DTCStatusCount[13] >=20)
		{
			DTCStatusCount[13] = 0;
			DTCStatus[13] &= 0xf7;
		}
	}
}

void AppIpduPPEI_Engine_General_Status_1_Ind(void)
{
	if(DTCStatus[16] & 0x08)
	{
		DTCStatusCount[16]++;
		if(DTCStatusCount[16] >=20)
		{
			DTCStatusCount[16] = 0;
			DTCStatus[16] &= 0xf7;
		}
	}
}

void AppIpduVehicle_Odometer_Ind(void)
{
}

void AppIpduPEPS_Door_Lock_Command_Ind(void)
{
}

void AppIpduAatilock_Brake_and_TC_Status_HS_Ind(void)
{
}

void AppIpduPPEI_Platform_General_Status_Ind(void)
{
}

void AppIpduAC_Torque_Status_Ind(void)
{
}

void AppIpduPEPS_General_Status_Ind(void)
{
}

void AppRxIpduNew_Message_R1_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R2_TimeOutInd(void)
{
	DTCStatus[2] = 0x09;
}

void AppRxIpduNew_Message_R3_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R4_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R5_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R6_TimeOutInd(void)
{
	DTCStatus[3] = 0x09;
}

void AppRxIpduNew_Message_R7_TimeOutInd(void)
{
	DTCStatus[4] = 0x09;
}

void AppRxIpduNew_Message_R8_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R9_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R10_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R11_TimeOutInd(void)
{
	DTCStatus[20] = 0x09;
}

void AppRxIpduNew_Message_R12_TimeOutInd(void)
{
	DTCStatus[19] = 0x09;
}

void AppRxIpduNew_Message_R13_TimeOutInd(void)
{
	DTCStatus[18] = 0x09;
}

void AppRxIpduNew_Message_R14_TimeOutInd(void)
{
	DTCStatus[15] = 0x09;
}

void AppRxIpduNew_Message_R15_TimeOutInd(void)
{
	DTCStatus[9] = 0x09;
}

void AppRxIpduNew_Message_R16_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R17_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R18_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R19_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R20_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R21_TimeOutInd(void)
{
	DTCStatus[12] = 0x09;
}

void AppRxIpduNew_Message_R22_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R23_TimeOutInd(void)
{
	DTCStatus[7] = 0x09;
}

void AppRxIpduNew_Message_R24_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R25_TimeOutInd(void)
{
	DTCStatus[8] = 0x09;
}

void AppRxIpduNew_Message_R26_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R27_TimeOutInd(void)
{
	DTCStatus[6] = 0x09;
}

void AppRxIpduNew_Message_R28_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R29_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R30_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R31_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R32_TimeOutInd(void)
{
	DTCStatus[10] = 0x09;
}

void AppRxIpduNew_Message_R33_TimeOutInd(void)
{
	//RES
	DTCStatus[23] = 0x09;
}

void AppRxIpduNew_Message_R34_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R35_TimeOutInd(void)
{
	DTCStatus[5] = 0x09;
}

void AppRxIpduNew_Message_R36_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R37_TimeOutInd(void)
{
	//AFS 100
	DTCStatus[24] = 0x09;
}

void AppRxIpduNew_Message_R38_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R39_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R40_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R41_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R42_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R43_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R44_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R45_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R46_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R47_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R48_TimeOutInd(void)
{
	//ICM 100
	DTCStatus[21] = 0x09;
}

void AppRxIpduNew_Message_R49_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R50_TimeOutInd(void)
{
	//DVR 200
	DTCStatus[14] = 0x09;
}

void AppRxIpduNew_Message_R51_TimeOutInd(void)
{
	//orm 100
	DTCStatus[17] = 0x09;
}

void AppRxIpduNew_Message_R52_TimeOutInd(void)
{
	//PLG 100
	DTCStatus[11] = 0x09;
}

void AppRxIpduNew_Message_R53_TimeOutInd(void)
{

}

void AppRxIpduNew_Message_R54_TimeOutInd(void)
{
	//MPWC 200
	DTCStatus[22] = 0x09;
}

void AppRxIpduNew_Message_R55_TimeOutInd(void)
{
}

void AppRxIpduNew_Message_R56_TimeOutInd(void)
{
	//AVAS 100
	DTCStatus[13] = 0x09;
}

void AppRxIpduPPEI_Engine_General_Status_1_TimeOutInd(void)
{
	//APL 100
	DTCStatus[16] = 0x09;
}

void AppRxIpduVehicle_Odometer_TimeOutInd(void)
{
}

void AppRxIpduPEPS_Door_Lock_Command_TimeOutInd(void)
{
}

void AppRxIpduAatilock_Brake_and_TC_Status_HS_TimeOutInd(void)
{

}

void AppRxIpduPPEI_Platform_General_Status_TimeOutInd(void)
{
}

void AppRxIpduAC_Torque_Status_TimeOutInd(void)
{
}

void AppRxIpduPEPS_General_Status_TimeOutInd(void)
{
}

