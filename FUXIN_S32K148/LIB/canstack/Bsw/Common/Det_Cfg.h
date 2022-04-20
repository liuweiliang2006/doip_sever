/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Det_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Det module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Det module configuration File
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
*   1.0.0       18/10/2017    Eas           N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/
#ifndef _DET_CFG_H_
#define _DET_CFG_H_
/*******************************************************************************
*   Include  
*******************************************************************************/
/*******************************************************************************
*   General  
*******************************************************************************/
#define DET_VERSION_CHECK                                   STD_ON
#define DET_VERSION_INFO_API                                STD_OFF
#define DET_ERROR_LOOP                                      STD_OFF
#define DET_FORWARD_TO_DLT                                  STD_OFF
#define DET_DEBUG                                           STD_OFF
#define DET_ERROR_HOOK                                      //a(ModuleId, InstanceId, ApiId, ErrorId)
#define DET_RUNTIMEERROR_HOOK                               //a(ModuleId, InstanceId, ApiId, ErrorId)
#define DET_TRANSIENTERROR_HOOK                             //a(ModuleId, InstanceId, ApiId, ErrorId)

#define DET_SW_MAJOR_VERSION_CFG                            1
#define DET_SW_MINOR_VERSION_CFG                            0
#define DET_SW_PATCH_VERSION_CFG                            0
#define DET_AR_RELEASE_MAJOR_VERSION_CFG                    4
#define DET_AR_RELEASE_MINOR_VERSION_CFG                    2
#define DET_AR_RELEASE_REVISION_VERSION_CFG                 2

#endif /* _DET_CFG_H_ */ 
