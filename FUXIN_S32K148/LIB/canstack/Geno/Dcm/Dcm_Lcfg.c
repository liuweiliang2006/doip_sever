/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Lcfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dcm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dcm module configuration File
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
*   04.03.02    16/08/2019     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Include files
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/* Config S3 time */
CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_CONFIG_CONST) gDcmDspNonDefaultSessionS3Server = 5000UL;/*Unit:ms*/

/* Config Session */
CONST(DcmDspSessionRow, DCM_CONFIG_CONST) gDcmDspSessionRow[KIND_OF_SESSION] = 
{
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_DEFAULT,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        2000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_PROGRAMMING,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        2000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* P2Server */ 
        50UL,
        /* P2*Server */ 
        2000UL,
    }
};

#if(DCM_SERVICE_27_ENABLED == STD_ON)
CONST(DcmDspSecurityRow, DCM_CONFIG_CONST)  gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL] = 
{
    /*L1*/
    {
        10000UL,  /* Delay Time */
        1000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        3UL,  /* Attempt Number */
        4UL  /* Seed Size */
    },
    /*L2*/
    {
        10000UL,  /* Delay Time */
        1000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        3UL,  /* Attempt Number */
        4UL  /* Seed Size */
    },
    /*L3*/
    {
        10000UL,  /* Delay Time */
        1000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        3UL,  /* Attempt Number */
        4UL  /* Seed Size */
    },
};
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
CONST(Dcm_22_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_22[NUMBER_OF_READ_DID] =  
{
    /* Index 0 */
    {
        /* DID */
        (uint32)0x2001U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0x2001,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 1 */
    {
        /* DID */
        (uint32)0xF101U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0xF101,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 2 */
    {
        /* DID */
        (uint32)0xF100U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        1U,
        /* App Callback Funtion */
        &App_Read0xF100,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 3 */
    {
        /* DID */
        (uint32)0xF112U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        3U,
        /* App Callback Funtion */
        &App_Read0xF112,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 4 */
    {
        /* DID */
        (uint32)0xF150U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        12U,
        /* App Callback Funtion */
        &App_Read0xF150,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 5 */
    {
        /* DID */
        (uint32)0xF18AU,
        /* Switch */
        STD_ON,  
        /* Data Size */
        7U,
        /* App Callback Funtion */
        &App_Read0xF18A,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 6 */
    {
        /* DID */
        (uint32)0xF187U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        10U,
        /* App Callback Funtion */
        &App_Read0xF187,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 7 */
    {
        /* DID */
        (uint32)0xF18BU,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0xF18B,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 8 */
    {
        /* DID */
        (uint32)0xF18CU,
        /* Switch */
        STD_ON,  
        /* Data Size */
        8U,
        /* App Callback Funtion */
        &App_Read0xF18C,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 9 */
    {
        /* DID */
        (uint32)0xF190U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        17U,
        /* App Callback Funtion */
        &App_Read0xF190,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 10 */
    {
        /* DID */
        (uint32)0xF198U,
        /* Switch */
        STD_ON,
        /* Data Size */
        16U,
        /* App Callback Funtion */
        &App_Read0xF198,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 11 */
    {
        /* DID */
        (uint32)0xF192U,
        /* Switch */
        STD_ON,
        /* Data Size */
        16U,
        /* App Callback Funtion */
        &App_Read0xF192,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 12 */
    {
        /* DID */
        (uint32)0xF193U,
        /* Switch */
        STD_ON,
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0xF193,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 13 */
    {
        /* DID */
        (uint32)0xF194U,
        /* Switch */
        STD_ON,
        /* Data Size */
        16U,
        /* App Callback Funtion */
        &App_Read0xF194,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 14 */
    {
        /* DID */
        (uint32)0xF195U,
        /* Switch */
        STD_ON,
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0xF195,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 15 */
    {
        /* DID */
        (uint32)0xF19DU,
        /* Switch */
        STD_ON,
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Read0xF19D,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
};
#endif

/* 0x23 0x3D */
#if((DCM_SERVICE_23_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
/* Config AddressFormat Bytes and SizeFormat Bytes */
CONST(Dcm_MemoryAddressFormatType, DCM_CONFIG_CONST)  gMemoryAddressFormat = 0U;
CONST(Dcm_MemorySizeFormatType, DCM_CONFIG_CONST) gMemorySizeFormat = 0U;
#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
CONST(DcmDspReadMemoryRangeInfo, DCM_CONFIG_CONST)   gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG] =
{
};
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
CONST(Dcm_24_ServiceInfoType, DCM_CONFIG_CONST)  gDcmDsdSubService_24[NUMBER_OF_READ_DID_24] =
{
};
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
CONST(Dcm_2A_ServiceInfoType, DCM_CONFIG_CONST)   gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID] =
{
};
#endif

/* 0x2C */
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
CONST(Dcm_2C_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2C[NUMBER_OF_DYN_DID] =
{
};
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
CONST(Dcm_2E_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID] =  
{
    /* Index 0 */
    {
        /* DID */
        (uint32)0x2001U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        4U,
        /* App Callback Funtion */
        &App_Write0x2001,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    /* Index 1 */
    {
        /* DID */
        (uint32)0xF190U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        17U,
        /* App Callback Funtion */
        &App_Write0xF190,
        /* Supported Security Level */
        (DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
	/* Index 2 */
	    {
	        /* DID */
	        (uint32)0xF198U,
	        /* Switch */
	        STD_ON,
	        /* Data Size */
	        16U,
	        /* App Callback Funtion */
	        &App_Write0xF198,
	        /* Supported Security Level */
	        (DCM_SEC_LEV_L1),
	        /* Supported Session */
	        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
	        /* Supported Address Type */
	        PHYSICAL_REQ_SUPPORTED
	    },
		/* Index 3 */
		    {
		        /* DID */
		        (uint32)0xF19DU,
		        /* Switch */
		        STD_ON,
		        /* Data Size */
		        4U,
		        /* App Callback Funtion */
		        &App_Write0xF19D,
		        /* Supported Security Level */
		        (DCM_SEC_LEV_L1),
		        /* Supported Session */
		        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		        /* Supported Address Type */
		        PHYSICAL_REQ_SUPPORTED
		    },
};
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
CONST(Dcm_2F_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID] =
{
};
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
CONST(DcmDspRoutine, DCM_CONFIG_CONST)  DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID] = 
{
    /* Index 0 */
    {
        /* SID */
        (uint32)0x0203U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0203,
        /* StopRoutineFnc */
        &App_StopRoutine0x0203,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0x0203,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    /* Index 1 */
    {
        /* SID */
        (uint32)0xFF02U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xFF02,
        /* StopRoutineFnc */
        &App_StopRoutine0xFF02,
        /* RequestResultsRoutineFnc */
        &App_RequestRoutineResults0xFF02,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                0UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
};
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
CONST(DcmDspWriteMemoryRangeInfo, DCM_CONFIG_CONST)  gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG] =
{
};
#endif
