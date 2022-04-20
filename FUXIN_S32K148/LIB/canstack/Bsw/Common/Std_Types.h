/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Std_Types.h
********************************************************************************
*   Project/Product : AUTOSAR 4.2
*   Title           : Std_Types.h 
*   Author          : Hirain
********************************************************************************
*   Description     : AUTOSAR Standard types file                    
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
*   01.00.00    13/06/2013    ning.chen     N/A          Original
*   01.00.01    17/07/2013    ning.chen     N/A          DPN_COMMON_130717_01
*   01.00.02    15/08/2013    ning.chen     N/A          D10_COMMON01_130815_01
*   01.00.03    08/01/2014    ning.chen     N/A          D10_COMMON01_140108_01
********************************************************************************
* END_FILE_HDR*/

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Platform_Types.h"
#include "Compiler.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/
#define STD_HIGH     (1)  
#define STD_LOW      (0) 

#define STD_ACTIVE   (1)       
#define STD_IDLE     (0) 

#define STD_ON       (1)                                       
#define STD_OFF      (0)

/* This typedef has been addedf or OSEK compliance */
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK    (0)
/* OSEK compliance */
typedef unsigned char StatusType;
#endif

#define E_NOT_OK  (1)

/*******************************************************************************
*   Typedef 
*******************************************************************************/                                                                   
typedef uint8 Std_ReturnType;

typedef struct                                          
{
    uint16 vendorID;                           
    uint16 moduleID;
    uint8  instanceID;
    uint8  sw_major_version;                         
    uint8  sw_minor_version;
    uint8  sw_patch_version;
}Std_VersionInfoType;

/*******************************************************************************
*   Insos Special 
*******************************************************************************/

#define STD_CONFIG_VARIANTS_PRECOMPILE  (1) 
#define STD_CONFIG_VARIANTS_LINKTIME    (2) 
#define STD_CONFIG_VARIANTS_POSTBUILD   (3)  

/* Vender ID */
#define STD_HIRAIN_VENDOR_ID   ((uint16)0x0056U)

/* Module ID */


/* Init State */
typedef enum
{
    STD_UNINITIALIZED = 0,
    STD_INITIALIZED = 1  
}Std_InitStateType; 



#endif  /* _STD_TYPES_H_ */
