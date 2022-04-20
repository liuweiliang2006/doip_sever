/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Det.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : Development Error Tracer Header File
*   Author          : HeYang
********************************************************************************
*   Description     : Includes all user relevant information for the tracing of
*                     development errors.   .                   
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

#ifndef DET_H
#define DET_H
/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
*   Global Function Declaration 
*******************************************************************************/
extern void Det_ReportError
(         
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId
);
  
#endif/* DET_H */