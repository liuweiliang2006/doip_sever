/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : Diagnostic Event Manager head File
*   Author          : HeYang
********************************************************************************
*   Description     : Includes all user relevant information for the tracing of
*                     product errors.                   
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
*   01.00.00    06/06/2012    HeYang        N/A          Original
*   01.01.00    08/07/2013    Ning.Chen     N/A          
********************************************************************************
* END_FILE_HDR*/
#ifndef DEM_H
#define DEM_H

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Std_Types.h"
#include "Dem_IntErrId.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define DEM_VENDOR_ID        43
#define DEM_MODULE_ID        54
#define DEM_AR_RELEASE_MAJOR_VERSION        4
#define DEM_AR_RELEASE_MINOR_VERSION        0
#define DEM_AR_RELEASE_REVISION_VERSION     3
#define DEM_SW_MAJOR_VERSION 1
#define DEM_SW_MINOR_VERSION 0
#define DEM_SW_PATCH_VERSION 1


typedef uint16 Dem_EventIdType;

typedef enum
{
    DEM_EVENT_STATUS_PASSED,
    DEM_EVENT_STATUS_FAILED,
    DEM_EVENT_STATUS_PREPASSED, 
    DEM_EVENT_STATUS_PREFAILED
}Dem_EventStatusType;
/*******************************************************************************
*   Global Function Define
*******************************************************************************/
extern void Dem_ReportErrorStatus
(
    Dem_EventIdType EventId, 
    uint8 EventStatus
);

#endif/* DEM_H */