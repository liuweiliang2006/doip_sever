/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_IntErrId.h
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : Diagnostic Event Manager IntErr head File
*   Author          : HeYang
********************************************************************************
*   Description     : for BSW event Id symbols   .                   
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
#ifndef DEM_INTERRID_H
#define DEM_INTERRID_H

/*******************************************************************************
*   Macro 
*******************************************************************************/

/*Can Interface*/
/*Production Error,Assigned by DEM,Failed DLC Check   */
#define CANIF_E_INVALID_DLC    (0x6001U)
/*Production Error,Assigned by DEM,CAN Interface controller mode 
                                    state machine is in mode CANIF_CS_STOPPED */
#define CANIF_E_STOPPED        (0x6002U)
/*Production Error,Assigned by DEM,CAN Interface controller mode 
                                  state machine is not in mode CANIF_CS_SLEEP */
#define CANIF_E_NOT_SLEEP      (0x6003U)

#endif/* DEM_INTERRID_H */