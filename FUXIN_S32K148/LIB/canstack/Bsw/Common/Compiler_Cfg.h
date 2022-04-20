/*  BEGIN_FILE_HDR
 ********************************************************************************
 *   NOTICE
 *   This software is the property of HiRain Technologies. Any information
 *   contained in this doc should not be reproduced, or used, or disclosed
 *   without the written authorization from HiRain Technologies.
 ********************************************************************************
 *   File Name       : Compiler_Cfg.h
 ********************************************************************************
 *   Project/Product : Common
 *   Title           : Compiler_Cfg.h
 *   Author          : ning.chen
 ********************************************************************************
 *   Description     : AUTOSAR Compiler config file
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
 *   01.00.02    14/08/2013    ning.chen     N/A          DPN_COMMON04_130814_01
 *   01.00.03    13/09/2013    ning.chen     N/A          D10_COMMON04_130913_01
 ********************************************************************************
 * END_FILE_HDR*/

#ifndef _COMPILER_CFG_H_
#define _COMPILER_CFG_H_

/*******************************************************************************
 *   BSW START
 *******************************************************************************/
#define BSW_CODE
#define BSW_VAR_NOINIT
#define BSW_VAR_POWER_ON_INIT
#define BSW_VAR_FAST
#define BSW_VAR
#define BSW_CONST
#define BSW_APPL_CODE
#define BSW_APPL_CONST
#define BSW_APPL_DATA
#define BSW_CALLOUT_CODE
/*******************************************************************************
 *   BSW END
 *******************************************************************************/


/*******************************************************************************
*   CAN START
*******************************************************************************/
#define CAN_CODE
#define CAN_VAR_NOINIT
#define CAN_VAR_POWER_ON_INIT
#define CAN_VAR_FAST
#define CAN_VAR
#define CAN_CONST
#define CAN_APPL_CODE
#define CAN_APPL_CONST
#define CAN_APPL_DATA
#define CAN_CALLOUT_CODE
#define CAN_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */

/*******************************************************************************
*   CAN END
*******************************************************************************/

/*******************************************************************************
 *   CAN Interface START
 *******************************************************************************/
#define CANIF_PUBLIC_CODE                /* API functions                     */
#define CANIF_PUBLIC_CONST               /* API constants                     */

#define CANIF_PRIVATE_CODE               /* Internal functions                */

#define CANIF_PRIVATE_DATA               /* Module internal data              */
#define CANIF_PRIVATE_CONST              /* Internal ROM Data                 */

#define CANIF_APPL_CODE                  /* callbacks of the Application      */
#define CANIF_APPL_CONST                 /* Applications' ROM Data            */
#define CANIF_APPL_DATA                  /* Applications' RAM Data            */
#define CANIF_FAST_DATA                  /* 'Near' RAM Data                   */

#define CANIF_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define CANIF_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define CANIF_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define CANIF_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define CANIF_CONST                      /* Data Constants                    */
/*******************************************************************************
 *   CAN Interface END
 *******************************************************************************/

/*******************************************************************************
 *   CCP START
 *******************************************************************************/
#define CCP_PUBLIC_CODE                /* API functions                       */
#define CCP_PUBLIC_CONST               /* API constants                       */

#define CCP_PRIVATE_CODE               /* Internal functions                  */

#define CCP_PRIVATE_DATA               /* Module internal data                */
#define CCP_PRIVATE_CONST              /* Internal ROM Data                   */

#define CCP_APPL_CODE                  /* callbacks of the Application        */
#define CCP_APPL_CONST                 /* Applications' ROM Data              */
#define CCP_APPL_DATA                  /* Applications' RAM Data              */
#define CCP_FAST_DATA                  /* 'Near' RAM Data                     */

#define CCP_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define CCP_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define CCP_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define CCP_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define CCP_CONST                      /* Data Constants                      */
/*******************************************************************************
 *   CCP END
 *******************************************************************************/
/*******************************************************************************
*   XCP START
*******************************************************************************/

#define XCP_PUBLIC_CODE                /* API functions                       */
#define XCP_PUBLIC_CONST               /* API constants                       */
                                                                              
#define XCP_PRIVATE_CODE               /* Internal functions                  */
                                                                              
#define XCP_PRIVATE_DATA               /* Module internal data                */
#define XCP_PRIVATE_CONST              /* Internal ROM Data                   */
                                                                              
#define XCP_APPL_CODE                  /* callbacks of the Application        */
#define XCP_APPL_CONST                 /* Applications' ROM Data              */
#define XCP_APPL_DATA                  /* Applications' RAM Data              */
#define XCP_FAST_DATA                  /* 'Near' RAM Data                     */


#define XCP_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define XCP_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define XCP_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define XCP_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define XCP_CONST                      /* Data Constants                      */


/*******************************************************************************
*   XCP END
*******************************************************************************/

/*******************************************************************************
 *   CANTP START
 *******************************************************************************/
#define CANTP_PUBLIC_CODE              /* API functions                       */
#define CANTP_PUBLIC_CONST             /* API constants                       */

#define CANTP_PRIVATE_CODE             /* Internal functions                  */

#define CANTP_PRIVATE_DATA             /* Module internal data                */
#define CANTP_PRIVATE_CONST            /* Internal ROM Data                   */

#define CANTP_APPL_CODE                /* callbacks of the Application        */
#define CANTP_APPL_CONST               /* Applications' ROM Data              */
#define CANTP_APPL_DATA                /* Applications' RAM Data              */
#define CANTP_FAST_DATA                /* 'Near' RAM Data                     */

#define CANTP_CONFIG_CONST             /* Desc. Tables -> Config-dependent    */
#define CANTP_CONFIG_DATA              /* Config. dependent (reg. size) data  */

#define CANTP_INIT_DATA                /* Data which is initialized during
                                        Startup                               */
#define CANTP_NOINIT_DATA              /* Data which is not initialized during
                                        Startup                               */
#define CANTP_CONST                    /* Data Constants                      */
/*******************************************************************************
 *   CANTP END
 *******************************************************************************/

/*******************************************************************************
 *   DCM START
 *******************************************************************************/
#define DCM_CODE                       /* FOR CONFIG DOCUMENT                 */
#define DCM_VARIABLE                   /* FOR CONFIG DOCUMENT                 */
#define DCM_PUBLIC_CODE                /* API functions                       */
#define DCM_PUBLIC_CONST               /* API constants                       */

#define DCM_PRIVATE_CODE               /* Internal functions                  */

#define DCM_PRIVATE_DATA               /* Module internal data                */
#define DCM_PRIVATE_CONST              /* Internal ROM Data                   */

#define DCM_APPL_CODE                  /* callbacks of the Application        */
#define DCM_APPL_CONST                 /* Applications' ROM Data              */
#define DCM_APPL_DATA                  /* Applications' RAM Data              */

#define DCM_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define DCM_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define DCM_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define DCM_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define DCM_CONST                      /* Data Constants                      */
/*******************************************************************************
 *   DCM END
 *******************************************************************************/

/*******************************************************************************
 *   COM START
 *******************************************************************************/
#define COM_PUBLIC_CODE                /* API functions                       */
#define COM_PUBLIC_CONST               /* API constants                       */

#define COM_PRIVATE_CODE               /* Internal functions                  */

#define COM_PRIVATE_DATA               /* Module internal data                */
#define COM_PRIVATE_CONST              /* Internal ROM Data                   */

#define COM_APPL_CODE                  /* callbacks of the Application        */
#define COM_APPL_CONST                 /* Applications' ROM Data              */
#define COM_APPL_DATA                  /* Applications' RAM Data              */
#define COM_FAST_DATA                  /* 'Near' RAM Data                     */

#define COM_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define COM_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define COM_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define COM_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define COM_CONST                      /* Data Constants                      */
#define COM_AUTOMOTIVE                 /* Automotive                          */
/*******************************************************************************
 *   COM END
 *******************************************************************************/

/*******************************************************************************
 *   OSEKNM START
 *******************************************************************************/
#define OSEKNM_PUBLIC_CODE             /* API functions                       */
#define OSEKNM_PUBLIC_CONST            /* API constants                       */

#define OSEKNM_PRIVATE_CODE            /* Internal functions                  */

#define OSEKNM_PRIVATE_DATA            /* Module internal data                */
#define OSEKNM_PRIVATE_CONST           /* Internal ROM Data                   */

#define OSEKNM_APPL_CODE               /* callbacks of the Application        */
#define OSEKNM_APPL_CONST              /* Applications' ROM Data              */
#define OSEKNM_APPL_DATA               /* Applications' RAM Data              */
#define OSEKNM_FAST_DATA               /* 'Near' RAM Data                     */

#define OSEKNM_CONFIG_CONST            /* Desc. Tables -> Config-dependent    */
#define OSEKNM_CONFIG_DATA             /* Config. dependent (reg. size) data  */

#define OSEKNM_INIT_DATA               /* Data which is initialized during
                                          Startup                             */
#define OSEKNM_NOINIT_DATA             /* Data which is not initialized during
                                          Startup                             */
#define OSEKNM_CONST                   /* Data Constants                      */
/*******************************************************************************
 *   OSEKNM END
 *******************************************************************************/

/*******************************************************************************
 *   CAN Communication Stack END
 *******************************************************************************/

/*******************************************************************************
 *   LIN Communication Stack START
 *******************************************************************************/

/*******************************************************************************
 *   LIN Driver START
 *******************************************************************************/
#define LIN_PUBLIC_CODE                /* API functions                       */
#define LIN_PUBLIC_CONST               /* API constants                       */

#define LIN_PRIVATE_CODE               /* Internal functions                  */

#define LIN_PRIVATE_DATA               /* Module internal data                */
#define LIN_PRIVATE_CONST              /* Internal ROM Data                   */

#define LIN_APPL_CODE                  /* callbacks of the Application        */
#define LIN_APPL_CONST                 /* Applications' ROM Data              */
#define LIN_APPL_DATA                  /* Applications' RAM Data              */
#define LIN_FAST_DATA                  /* 'Near' RAM Data                     */

#define LIN_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define LIN_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define LIN_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define LIN_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define LIN_CONST                      /* Data Constants                      */
/*******************************************************************************
 *   LIN Driver END
 *******************************************************************************/

/*******************************************************************************
 *   LIN Interface START
 *******************************************************************************/
#define LINIF_PUBLIC_CODE                /* API functions                     */
#define LINIF_PUBLIC_CONST               /* API constants                     */

#define LINIF_PRIVATE_CODE               /* Internal functions                */

#define LINIF_PRIVATE_DATA               /* Module internal data              */
#define LINIF_PRIVATE_CONST              /* Internal ROM Data                 */

#define LINIF_APPL_CODE                  /* callbacks of the Application      */
#define LINIF_APPL_CONST                 /* Applications' ROM Data            */
#define LINIF_APPL_DATA                  /* Applications' RAM Data            */
#define LINIF_FAST_DATA                  /* 'Near' RAM Data                   */

#define LINIF_CONFIG_CONST               /* Desc. Tables -> Config-dependent  */
#define LINIF_CONFIG_DATA                /* Config. dependent (reg. size) data*/

#define LINIF_INIT_DATA                  /* Data which is initialized during
                                            Startup                           */
#define LINIF_NOINIT_DATA                /* Data which is not initialized during
                                            Startup                           */
#define LINIF_CONST                      /* Data Constants                    */
/*******************************************************************************
 *   LIN Interface END
 *******************************************************************************/

/*******************************************************************************
 *   LIN Communication Stack END
 *******************************************************************************/

/*******************************************************************************
 *   NVM START
 *******************************************************************************/
#define NVM_CODE
#define NVM_VAR_NOINIT
#define NVM_VAR_POWER_ON_INIT
#define NVM_VAR_FAST
#define NVM_VAR
#define NVM_CONST
#define NVM_APPL_CODE
#define NVM_APPL_CONST
#define NVM_APPL_DATA
#define NVM_CALLOUT_CODE
/*******************************************************************************
 *   NVM END
 *******************************************************************************/
/*******************************************************************************
*   CAN Network Management START 
*******************************************************************************/
#define CANNM_CODE                
#define CANNM_VAR_NOINIT          
#define CANNM_VAR_POWER_ON_INIT               

#define CANNM_VAR_FAST               
#define CANNM_VAR         
#define CANNM_CONST 

#define CANNM_APPL_CODE                  
#define CANNM_APPL_CONST                
#define CANNM_APPL_DATA  

#define CANNM_CALLOUT_CODE                       
/*******************************************************************************
*   CAN Network Management END 
*******************************************************************************/

/*******************************************************************************
 *   MEMIF START
 *******************************************************************************/
#define MEMIF_CODE
#define MEMIF_VAR_NOINIT
#define MEMIF_VAR_POWER_ON_INIT
#define MEMIF_VAR_FAST
#define MEMIF_VAR
#define MEMIF_CONST
#define MEMIF_APPL_CODE
#define MEMIF_APPL_CONST
#define MEMIF_APPL_DATA
#define MEMIF_CALLOUT_CODE
/*******************************************************************************
 *   MEMIF END
 *******************************************************************************/

/*******************************************************************************
 *   DEM START
 *******************************************************************************/
#define DEM_CODE /* FOR CONFIG DOCUMENT */
#define DEM_VARIABLE /* FOR CONFIG DOCUMENT */
#define DEM_PUBLIC_CODE /* API functions */
#define DEM_PUBLIC_CONST /* API constants */

#define DEM_PRIVATE_CODE /* Internal functions */

#define DEM_PRIVATE_DATA /* Module internal data */
#define DEM_PRIVATE_CONST /* Internal ROM Data */

#define DEM_APPL_CODE /* callbacks of the Application */
#define DEM_APPL_CONST /* Applications' ROM Data */
#define DEM_APPL_DATA /* Applications' RAM Data */

#define DEM_CONFIG_CONST /* Desc. Tables -> Config-dependent */
#define DEM_CONFIG_DATA /* Config. dependent (reg. size) data */

#define DEM_INIT_DATA /* Data which is initialized during
    Startup */
#define DEM_NOINIT_DATA /* Data which is not initialized during
    Startup */
#define DEM_CONST /* Data Constants */
/*******************************************************************************
 *   DEM END
 *******************************************************************************/

#endif/* _COMPILER_CFG_H_ */
