/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Cfg.h
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
#ifndef _COM_CFG_H_
#define _COM_CFG_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com_Types.h"
/*adding underlying layer's head files here if necessary*/ 
#include "CanIf.h" 

/*******************************************************************************
*   Macro define
*******************************************************************************/
#define COM_VERSION_INFO_API                         STD_OFF
#define COM_ENABLE_ACTIVEPORPERTY
#define COM_ENABLE_TXCONFIRMATIONFUN
#define COM_ENABLE_TXTOINDFUN
#define COM_ENABLE_RXINDICATIONFUN
#define COM_ENABLE_RXTOINDFUN
#define COM_TXMAIN_FUNCTION_PERIOD                   (10U)
#define COM_RXMAIN_FUNCTION_PERIOD                   (10U)
#define COM_SIGNALROUTINEMAIN_FUNCTION_PERIOD        (10U)

/******************************************************************************
*    number of Tx object                                                       
******************************************************************************/
#define COM_TXIPDUNUM    (16U)
/******************************************************************************
*    Handles of send messages                                                  
******************************************************************************/
#define COM_TXIPDUNew_Message_21    (0U)
#define COM_TXIPDUNew_Message_22    (1U)
#define COM_TXIPDUNew_Message_23    (2U)
#define COM_TXIPDUNew_Message_24    (3U)
#define COM_TXIPDUNew_Message_25    (4U)
#define COM_TXIPDUNew_Message_26    (5U)
#define COM_TXIPDUNew_Message_27    (6U)
#define COM_TXIPDUNew_Message_28    (7U)
#define COM_TXIPDUNew_Message_29    (8U)
#define COM_TXIPDUNew_Message_30    (9U)
#define COM_TXIPDUNew_Message_31    (10U)
#define COM_TXIPDUNew_Message_32    (11U)
#define COM_TXIPDUNew_Message_33    (12U)
#define COM_TXIPDUNew_Message_34    (13U)
#define COM_TXIPDUPLG_General_Status    (14U)
#define COM_TXIPDUPLG_Setting_Control_Cmd    (15U)
/******************************************************************************
*    number of Tx object Signal                                                
******************************************************************************/
#define COM_TXSIGNUM    (127U)
/******************************************************************************
*    Handles of send signals                                                  
******************************************************************************/
/*New_Message_21 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_21    (0U)
#define COM_TXSIGNew_Signal_211    (1U)
#define COM_TXSIGNew_Signal_212    (2U)
#define COM_TXSIGNew_Signal_213    (3U)
#define COM_TXSIGNew_Signal_214    (4U)
#define COM_TXSIGNew_Signal_215    (5U)
#define COM_TXSIGNew_Signal_216    (6U)
#define COM_TXSIGNew_Signal_217    (7U)
/*New_Message_22 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_22    (8U)
#define COM_TXSIGNew_Signal_221    (9U)
#define COM_TXSIGNew_Signal_222    (10U)
#define COM_TXSIGNew_Signal_223    (11U)
#define COM_TXSIGNew_Signal_224    (12U)
#define COM_TXSIGNew_Signal_225    (13U)
#define COM_TXSIGNew_Signal_226    (14U)
#define COM_TXSIGNew_Signal_227    (15U)
/*New_Message_23 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_23    (16U)
#define COM_TXSIGNew_Signal_231    (17U)
#define COM_TXSIGNew_Signal_232    (18U)
#define COM_TXSIGNew_Signal_233    (19U)
#define COM_TXSIGNew_Signal_234    (20U)
#define COM_TXSIGNew_Signal_235    (21U)
#define COM_TXSIGNew_Signal_236    (22U)
#define COM_TXSIGNew_Signal_237    (23U)
/*New_Message_24 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_24    (24U)
#define COM_TXSIGNew_Signal_241    (25U)
#define COM_TXSIGNew_Signal_242    (26U)
#define COM_TXSIGNew_Signal_243    (27U)
#define COM_TXSIGNew_Signal_244    (28U)
#define COM_TXSIGNew_Signal_245    (29U)
#define COM_TXSIGNew_Signal_246    (30U)
#define COM_TXSIGNew_Signal_247    (31U)
/*New_Message_25 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_25    (32U)
#define COM_TXSIGNew_Signal_251    (33U)
#define COM_TXSIGNew_Signal_252    (34U)
#define COM_TXSIGNew_Signal_253    (35U)
#define COM_TXSIGNew_Signal_254    (36U)
#define COM_TXSIGNew_Signal_255    (37U)
#define COM_TXSIGNew_Signal_256    (38U)
#define COM_TXSIGNew_Signal_257    (39U)
/*New_Message_26 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_26    (40U)
#define COM_TXSIGNew_Signal_261    (41U)
#define COM_TXSIGNew_Signal_262    (42U)
#define COM_TXSIGNew_Signal_263    (43U)
#define COM_TXSIGNew_Signal_264    (44U)
#define COM_TXSIGNew_Signal_265    (45U)
#define COM_TXSIGNew_Signal_266    (46U)
#define COM_TXSIGNew_Signal_267    (47U)
/*New_Message_27 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_27    (48U)
#define COM_TXSIGNew_Signal_271    (49U)
#define COM_TXSIGNew_Signal_272    (50U)
#define COM_TXSIGNew_Signal_273    (51U)
#define COM_TXSIGNew_Signal_274    (52U)
#define COM_TXSIGNew_Signal_275    (53U)
#define COM_TXSIGNew_Signal_276    (54U)
#define COM_TXSIGNew_Signal_277    (55U)
/*New_Message_28 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_28    (56U)
#define COM_TXSIGNew_Signal_281    (57U)
#define COM_TXSIGNew_Signal_282    (58U)
#define COM_TXSIGNew_Signal_283    (59U)
#define COM_TXSIGNew_Signal_284    (60U)
#define COM_TXSIGNew_Signal_285    (61U)
#define COM_TXSIGNew_Signal_286    (62U)
#define COM_TXSIGNew_Signal_287    (63U)
/*New_Message_29 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_29    (64U)
#define COM_TXSIGNew_Signal_291    (65U)
#define COM_TXSIGNew_Signal_292    (66U)
#define COM_TXSIGNew_Signal_293    (67U)
#define COM_TXSIGNew_Signal_294    (68U)
#define COM_TXSIGNew_Signal_295    (69U)
#define COM_TXSIGNew_Signal_296    (70U)
#define COM_TXSIGNew_Signal_297    (71U)
/*New_Message_30 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_30    (72U)
#define COM_TXSIGNew_Signal_301    (73U)
#define COM_TXSIGNew_Signal_302    (74U)
#define COM_TXSIGNew_Signal_303    (75U)
#define COM_TXSIGNew_Signal_304    (76U)
#define COM_TXSIGNew_Signal_305    (77U)
#define COM_TXSIGNew_Signal_306    (78U)
#define COM_TXSIGNew_Signal_307    (79U)
/*New_Message_31 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_31    (80U)
#define COM_TXSIGNew_Signal_311    (81U)
#define COM_TXSIGNew_Signal_312    (82U)
#define COM_TXSIGNew_Signal_313    (83U)
#define COM_TXSIGNew_Signal_314    (84U)
#define COM_TXSIGNew_Signal_315    (85U)
#define COM_TXSIGNew_Signal_316    (86U)
#define COM_TXSIGNew_Signal_317    (87U)
/*New_Message_32 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_32    (88U)
#define COM_TXSIGNew_Signal_321    (89U)
#define COM_TXSIGNew_Signal_322    (90U)
#define COM_TXSIGNew_Signal_323    (91U)
#define COM_TXSIGNew_Signal_324    (92U)
#define COM_TXSIGNew_Signal_325    (93U)
#define COM_TXSIGNew_Signal_326    (94U)
#define COM_TXSIGNew_Signal_327    (95U)
/*New_Message_33 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_33    (96U)
#define COM_TXSIGNew_Signal_331    (97U)
#define COM_TXSIGNew_Signal_332    (98U)
#define COM_TXSIGNew_Signal_333    (99U)
#define COM_TXSIGNew_Signal_334    (100U)
#define COM_TXSIGNew_Signal_335    (101U)
#define COM_TXSIGNew_Signal_336    (102U)
#define COM_TXSIGNew_Signal_337    (103U)
/*New_Message_34 MEIJIA_11RX_mix*/
#define COM_TXSIGNew_Signal_34    (104U)
#define COM_TXSIGNew_Signal_341    (105U)
#define COM_TXSIGNew_Signal_342    (106U)
#define COM_TXSIGNew_Signal_343    (107U)
#define COM_TXSIGNew_Signal_344    (108U)
#define COM_TXSIGNew_Signal_345    (109U)
#define COM_TXSIGNew_Signal_346    (110U)
#define COM_TXSIGNew_Signal_347    (111U)
/*PLG_General_Status MEIJIA_11RX_mix*/
#define COM_TXSIGPLGSysMSt    (112U)
#define COM_TXSIGPLGMaxOpePosSSt    (113U)
#define COM_TXSIGPLGCrtOpePos    (114U)
#define COM_TXSIGPLGCrtOpePosV    (115U)
#define COM_TXSIGPLGPwOptCmdAct    (116U)
#define COM_TXSIGPLGLmSt    (117U)
#define COM_TXSIGPLGLtMSt    (118U)
#define COM_TXSIGPLGFlurAnls    (119U)
#define COM_TXSIGPLGLtPrySglSwSt    (120U)
#define COM_TXSIGPLGLtScdSglSwSt    (121U)
#define COM_TXSIGPLGLtPwSglSwSt    (122U)
#define COM_TXSIGPLGLtRstSglSwSt    (123U)
#define COM_TXSIGPLGLtSnwLdIO    (124U)
/*PLG_Setting_Control_Cmd MEIJIA_11RX_mix*/
#define COM_TXSIGPLGMaxOpePosSRq    (125U)
#define COM_TXSIGPLGMaxOpePosSRqSt    (126U)

/******************************************************************************
*    Send Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 New_Signal_21 : 8;
    uint8 New_Signal_211 : 8;
    uint8 New_Signal_212 : 8;
    uint8 New_Signal_213 : 8;
    uint8 New_Signal_214 : 8;
    uint8 New_Signal_215 : 8;
    uint8 New_Signal_216 : 8;
    uint8 New_Signal_217 : 8;
}IpduNew_Message_21_Type;

typedef struct {
    uint8 New_Signal_22 : 8;
    uint8 New_Signal_221 : 8;
    uint8 New_Signal_222 : 8;
    uint8 New_Signal_223 : 8;
    uint8 New_Signal_224 : 8;
    uint8 New_Signal_225 : 8;
    uint8 New_Signal_226 : 8;
    uint8 New_Signal_227 : 8;
}IpduNew_Message_22_Type;

typedef struct {
    uint8 New_Signal_23 : 8;
    uint8 New_Signal_231 : 8;
    uint8 New_Signal_232 : 8;
    uint8 New_Signal_233 : 8;
    uint8 New_Signal_234 : 8;
    uint8 New_Signal_235 : 8;
    uint8 New_Signal_236 : 8;
    uint8 New_Signal_237 : 8;
}IpduNew_Message_23_Type;

typedef struct {
    uint8 New_Signal_24 : 8;
    uint8 New_Signal_241 : 8;
    uint8 New_Signal_242 : 8;
    uint8 New_Signal_243 : 8;
    uint8 New_Signal_244 : 8;
    uint8 New_Signal_245 : 8;
    uint8 New_Signal_246 : 8;
    uint8 New_Signal_247 : 8;
}IpduNew_Message_24_Type;

typedef struct {
    uint8 New_Signal_25 : 8;
    uint8 New_Signal_251 : 8;
    uint8 New_Signal_252 : 8;
    uint8 New_Signal_253 : 8;
    uint8 New_Signal_254 : 8;
    uint8 New_Signal_255 : 8;
    uint8 New_Signal_256 : 8;
    uint8 New_Signal_257 : 8;
}IpduNew_Message_25_Type;

typedef struct {
    uint8 New_Signal_26 : 8;
    uint8 New_Signal_261 : 8;
    uint8 New_Signal_262 : 8;
    uint8 New_Signal_263 : 8;
    uint8 New_Signal_264 : 8;
    uint8 New_Signal_265 : 8;
    uint8 New_Signal_266 : 8;
    uint8 New_Signal_267 : 8;
}IpduNew_Message_26_Type;

typedef struct {
    uint8 New_Signal_27 : 8;
    uint8 New_Signal_271 : 8;
    uint8 New_Signal_272 : 8;
    uint8 New_Signal_273 : 8;
    uint8 New_Signal_274 : 8;
    uint8 New_Signal_275 : 8;
    uint8 New_Signal_276 : 8;
    uint8 New_Signal_277 : 8;
}IpduNew_Message_27_Type;

typedef struct {
    uint8 New_Signal_28 : 8;
    uint8 New_Signal_281 : 8;
    uint8 New_Signal_282 : 8;
    uint8 New_Signal_283 : 8;
    uint8 New_Signal_284 : 8;
    uint8 New_Signal_285 : 8;
    uint8 New_Signal_286 : 8;
    uint8 New_Signal_287 : 8;
}IpduNew_Message_28_Type;

typedef struct {
    uint8 New_Signal_29 : 8;
    uint8 New_Signal_291 : 8;
    uint8 New_Signal_292 : 8;
    uint8 New_Signal_293 : 8;
    uint8 New_Signal_294 : 8;
    uint8 New_Signal_295 : 8;
    uint8 New_Signal_296 : 8;
    uint8 New_Signal_297 : 8;
}IpduNew_Message_29_Type;

typedef struct {
    uint8 New_Signal_30 : 8;
    uint8 New_Signal_301 : 8;
    uint8 New_Signal_302 : 8;
    uint8 New_Signal_303 : 8;
    uint8 New_Signal_304 : 8;
    uint8 New_Signal_305 : 8;
    uint8 New_Signal_306 : 8;
    uint8 New_Signal_307 : 8;
}IpduNew_Message_30_Type;

typedef struct {
    uint8 New_Signal_31 : 8;
    uint8 New_Signal_311 : 8;
    uint8 New_Signal_312 : 8;
    uint8 New_Signal_313 : 8;
    uint8 New_Signal_314 : 8;
    uint8 New_Signal_315 : 8;
    uint8 New_Signal_316 : 8;
    uint8 New_Signal_317 : 8;
}IpduNew_Message_31_Type;

typedef struct {
    uint8 New_Signal_32 : 8;
    uint8 New_Signal_321 : 8;
    uint8 New_Signal_322 : 8;
    uint8 New_Signal_323 : 8;
    uint8 New_Signal_324 : 8;
    uint8 New_Signal_325 : 8;
    uint8 New_Signal_326 : 8;
    uint8 New_Signal_327 : 8;
}IpduNew_Message_32_Type;

typedef struct {
    uint8 New_Signal_33 : 8;
    uint8 New_Signal_331 : 8;
    uint8 New_Signal_332 : 8;
    uint8 New_Signal_333 : 8;
    uint8 New_Signal_334 : 8;
    uint8 New_Signal_335 : 8;
    uint8 New_Signal_336 : 8;
    uint8 New_Signal_337 : 8;
}IpduNew_Message_33_Type;

typedef struct {
    uint8 New_Signal_34 : 8;
    uint8 New_Signal_341 : 8;
    uint8 New_Signal_342 : 8;
    uint8 New_Signal_343 : 8;
    uint8 New_Signal_344 : 8;
    uint8 New_Signal_345 : 8;
    uint8 New_Signal_346 : 8;
    uint8 New_Signal_347 : 8;
}IpduNew_Message_34_Type;

typedef struct {
    uint8 unused0 : 1;
    uint8 PLGSysMSt : 3;
    uint8 unused1 : 4;
    uint8 PLGMaxOpePosSSt : 7;
    uint8 unused2 : 1;
    uint8 PLGCrtOpePos : 7;
    uint8 PLGCrtOpePosV : 1;
    uint8 PLGPwOptCmdAct : 4;
    uint8 PLGLmSt : 1;
    uint8 PLGLtMSt : 3;
    uint8 PLGFlurAnls : 8;
    uint8 PLGLtPrySglSwSt : 1;
    uint8 PLGLtScdSglSwSt : 1;
    uint8 PLGLtPwSglSwSt : 1;
    uint8 PLGLtRstSglSwSt : 1;
    uint8 PLGLtSnwLdIO : 1;
    uint8 unused3_Byte0 : 3;
    uint8 unused3_Byte1 : 8;
    uint8 unused3_Byte2 : 8;
}IpduPLG_General_Status_Type;

typedef struct {
    uint8 unused0 : 8;
    uint8 PLGMaxOpePosSRq : 7;
    uint8 PLGMaxOpePosSRqSt : 1;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 unused1_Byte5 : 8;
}IpduPLG_Setting_Control_Cmd_Type;


/******************************************************************************
*    Send Message unions                                                       
******************************************************************************/
typedef union {
    IpduNew_Message_21_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_21_bufType;

typedef union {
    IpduNew_Message_22_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_22_bufType;

typedef union {
    IpduNew_Message_23_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_23_bufType;

typedef union {
    IpduNew_Message_24_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_24_bufType;

typedef union {
    IpduNew_Message_25_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_25_bufType;

typedef union {
    IpduNew_Message_26_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_26_bufType;

typedef union {
    IpduNew_Message_27_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_27_bufType;

typedef union {
    IpduNew_Message_28_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_28_bufType;

typedef union {
    IpduNew_Message_29_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_29_bufType;

typedef union {
    IpduNew_Message_30_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_30_bufType;

typedef union {
    IpduNew_Message_31_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_31_bufType;

typedef union {
    IpduNew_Message_32_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_32_bufType;

typedef union {
    IpduNew_Message_33_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_33_bufType;

typedef union {
    IpduNew_Message_34_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_34_bufType;

typedef union {
    IpduPLG_General_Status_Type  Ipdu;
    uint8  _c[8];
}IpduPLG_General_Status_bufType;

typedef union {
    IpduPLG_Setting_Control_Cmd_Type  Ipdu;
    uint8  _c[8];
}IpduPLG_Setting_Control_Cmd_bufType;


/******************************************************************************
*    Databuffer for sended objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduNew_Message_21_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_21;
extern VAR(IpduNew_Message_22_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_22;
extern VAR(IpduNew_Message_23_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_23;
extern VAR(IpduNew_Message_24_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_24;
extern VAR(IpduNew_Message_25_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_25;
extern VAR(IpduNew_Message_26_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_26;
extern VAR(IpduNew_Message_27_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_27;
extern VAR(IpduNew_Message_28_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_28;
extern VAR(IpduNew_Message_29_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_29;
extern VAR(IpduNew_Message_30_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_30;
extern VAR(IpduNew_Message_31_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_31;
extern VAR(IpduNew_Message_32_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_32;
extern VAR(IpduNew_Message_33_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_33;
extern VAR(IpduNew_Message_34_bufType, COM_PRIVATE_DATA) TxIpduNew_Message_34;
extern VAR(IpduPLG_General_Status_bufType, COM_PRIVATE_DATA) TxIpduPLG_General_Status;
extern VAR(IpduPLG_Setting_Control_Cmd_bufType, COM_PRIVATE_DATA) TxIpduPLG_Setting_Control_Cmd;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Sended Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduNew_Message_21_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_21DefaultValue;
extern CONST(IpduNew_Message_22_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_22DefaultValue;
extern CONST(IpduNew_Message_23_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_23DefaultValue;
extern CONST(IpduNew_Message_24_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_24DefaultValue;
extern CONST(IpduNew_Message_25_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_25DefaultValue;
extern CONST(IpduNew_Message_26_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_26DefaultValue;
extern CONST(IpduNew_Message_27_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_27DefaultValue;
extern CONST(IpduNew_Message_28_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_28DefaultValue;
extern CONST(IpduNew_Message_29_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_29DefaultValue;
extern CONST(IpduNew_Message_30_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_30DefaultValue;
extern CONST(IpduNew_Message_31_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_31DefaultValue;
extern CONST(IpduNew_Message_32_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_32DefaultValue;
extern CONST(IpduNew_Message_33_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_33DefaultValue;
extern CONST(IpduNew_Message_34_bufType, COM_CONFIG_CONST)  TxIpduNew_Message_34DefaultValue;
extern CONST(IpduPLG_General_Status_bufType, COM_CONFIG_CONST)  TxIpduPLG_General_StatusDefaultValue;
extern CONST(IpduPLG_Setting_Control_Cmd_bufType, COM_CONFIG_CONST)  TxIpduPLG_Setting_Control_CmdDefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_TXIPDUNUM >= 1u)
/******************************************************************************
*    used for application:message tx timeout indication Function               
******************************************************************************/
#ifdef COM_ENABLE_TXTOINDFUN 
extern void AppIpduNew_Message_21_TxTOIndication(void);
extern void AppIpduNew_Message_22_TxTOIndication(void);
extern void AppIpduNew_Message_23_TxTOIndication(void);
extern void AppIpduNew_Message_24_TxTOIndication(void);
extern void AppIpduNew_Message_25_TxTOIndication(void);
extern void AppIpduNew_Message_26_TxTOIndication(void);
extern void AppIpduNew_Message_27_TxTOIndication(void);
extern void AppIpduNew_Message_28_TxTOIndication(void);
extern void AppIpduNew_Message_29_TxTOIndication(void);
extern void AppIpduNew_Message_30_TxTOIndication(void);
extern void AppIpduNew_Message_31_TxTOIndication(void);
extern void AppIpduNew_Message_32_TxTOIndication(void);
extern void AppIpduNew_Message_33_TxTOIndication(void);
extern void AppIpduNew_Message_34_TxTOIndication(void);
extern void AppIpduPLG_General_Status_TxTOIndication(void);
extern void AppIpduPLG_Setting_Control_Cmd_TxTOIndication(void);
#endif

/******************************************************************************
*    Ipdu Tx Confirmation function declare                                     
******************************************************************************/
#ifdef COM_ENABLE_TXCONFIRMATIONFUN 
extern void AppIpduNew_Message_21_Conf(void);
extern void AppIpduNew_Message_22_Conf(void);
extern void AppIpduNew_Message_23_Conf(void);
extern void AppIpduNew_Message_24_Conf(void);
extern void AppIpduNew_Message_25_Conf(void);
extern void AppIpduNew_Message_26_Conf(void);
extern void AppIpduNew_Message_27_Conf(void);
extern void AppIpduNew_Message_28_Conf(void);
extern void AppIpduNew_Message_29_Conf(void);
extern void AppIpduNew_Message_30_Conf(void);
extern void AppIpduNew_Message_31_Conf(void);
extern void AppIpduNew_Message_32_Conf(void);
extern void AppIpduNew_Message_33_Conf(void);
extern void AppIpduNew_Message_34_Conf(void);
extern void AppIpduPLG_General_Status_Conf(void);
extern void AppIpduPLG_Setting_Control_Cmd_Conf(void);
#endif

#endif /*#if (COM_TXIPDUNUM>=1)*/ 

/******************************************************************************
*    number of Rx object                                                       
******************************************************************************/
#define COM_RXIPDUNUM    (63U)
/******************************************************************************
*    Handles of receive messages                                                  
******************************************************************************/
#define COM_RXIPDUNew_Message_R1    (0U)
#define COM_RXIPDUNew_Message_R2    (1U)
#define COM_RXIPDUNew_Message_R3    (2U)
#define COM_RXIPDUNew_Message_R4    (3U)
#define COM_RXIPDUNew_Message_R5    (4U)
#define COM_RXIPDUNew_Message_R6    (5U)
#define COM_RXIPDUNew_Message_R7    (6U)
#define COM_RXIPDUNew_Message_R8    (7U)
#define COM_RXIPDUNew_Message_R9    (8U)
#define COM_RXIPDUNew_Message_R10    (9U)
#define COM_RXIPDUNew_Message_R11    (10U)
#define COM_RXIPDUNew_Message_R12    (11U)
#define COM_RXIPDUNew_Message_R13    (12U)
#define COM_RXIPDUNew_Message_R14    (13U)
#define COM_RXIPDUNew_Message_R15    (14U)
#define COM_RXIPDUNew_Message_R16    (15U)
#define COM_RXIPDUNew_Message_R17    (16U)
#define COM_RXIPDUNew_Message_R18    (17U)
#define COM_RXIPDUNew_Message_R19    (18U)
#define COM_RXIPDUNew_Message_R20    (19U)
#define COM_RXIPDUNew_Message_R21    (20U)
#define COM_RXIPDUNew_Message_R22    (21U)
#define COM_RXIPDUNew_Message_R23    (22U)
#define COM_RXIPDUNew_Message_R24    (23U)
#define COM_RXIPDUNew_Message_R25    (24U)
#define COM_RXIPDUNew_Message_R26    (25U)
#define COM_RXIPDUNew_Message_R27    (26U)
#define COM_RXIPDUNew_Message_R28    (27U)
#define COM_RXIPDUNew_Message_R29    (28U)
#define COM_RXIPDUNew_Message_R30    (29U)
#define COM_RXIPDUNew_Message_R31    (30U)
#define COM_RXIPDUNew_Message_R32    (31U)
#define COM_RXIPDUNew_Message_R33    (32U)
#define COM_RXIPDUNew_Message_R34    (33U)
#define COM_RXIPDUNew_Message_R35    (34U)
#define COM_RXIPDUNew_Message_R36    (35U)
#define COM_RXIPDUNew_Message_R37    (36U)
#define COM_RXIPDUNew_Message_R38    (37U)
#define COM_RXIPDUNew_Message_R39    (38U)
#define COM_RXIPDUNew_Message_R40    (39U)
#define COM_RXIPDUNew_Message_R41    (40U)
#define COM_RXIPDUNew_Message_R42    (41U)
#define COM_RXIPDUNew_Message_R43    (42U)
#define COM_RXIPDUNew_Message_R44    (43U)
#define COM_RXIPDUNew_Message_R45    (44U)
#define COM_RXIPDUNew_Message_R46    (45U)
#define COM_RXIPDUNew_Message_R47    (46U)
#define COM_RXIPDUNew_Message_R48    (47U)
#define COM_RXIPDUNew_Message_R49    (48U)
#define COM_RXIPDUNew_Message_R50    (49U)
#define COM_RXIPDUNew_Message_R51    (50U)
#define COM_RXIPDUNew_Message_R52    (51U)
#define COM_RXIPDUNew_Message_R53    (52U)
#define COM_RXIPDUNew_Message_R54    (53U)
#define COM_RXIPDUNew_Message_R55    (54U)
#define COM_RXIPDUNew_Message_R56    (55U)
#define COM_RXIPDUPPEI_Engine_General_Status_1    (56U)
#define COM_RXIPDUVehicle_Odometer    (57U)
#define COM_RXIPDUPEPS_Door_Lock_Command    (58U)
#define COM_RXIPDUAatilock_Brake_and_TC_Status_HS    (59U)
#define COM_RXIPDUPPEI_Platform_General_Status    (60U)
#define COM_RXIPDUAC_Torque_Status    (61U)
#define COM_RXIPDUPEPS_General_Status    (62U)
/******************************************************************************
*    the buffer size of Message received                                       
******************************************************************************/
#define COM_RXIPDUNew_Message_R1_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R2_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R3_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R4_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R5_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R6_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R7_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R8_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R9_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R10_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R11_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R12_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R13_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R14_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R15_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R16_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R17_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R18_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R19_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R20_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R21_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R22_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R23_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R24_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R25_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R26_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R27_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R28_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R29_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R30_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R31_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R32_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R33_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R34_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R35_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R36_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R37_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R38_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R39_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R40_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R41_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R42_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R43_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R44_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R45_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R46_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R47_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R48_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R49_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R50_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R51_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R52_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R53_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R54_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R55_BUFFER_SIZE    (8U)
#define COM_RXIPDUNew_Message_R56_BUFFER_SIZE    (8U)
#define COM_RXIPDUPPEI_Engine_General_Status_1_BUFFER_SIZE    (8U)
#define COM_RXIPDUVehicle_Odometer_BUFFER_SIZE    (5U)
#define COM_RXIPDUPEPS_Door_Lock_Command_BUFFER_SIZE    (8U)
#define COM_RXIPDUAatilock_Brake_and_TC_Status_HS_BUFFER_SIZE    (8U)
#define COM_RXIPDUPPEI_Platform_General_Status_BUFFER_SIZE    (8U)
#define COM_RXIPDUAC_Torque_Status_BUFFER_SIZE    (8U)
#define COM_RXIPDUPEPS_General_Status_BUFFER_SIZE    (8U)
/******************************************************************************
*    number of Rx object Signal                                                
******************************************************************************/
#define COM_RXSIGNUM    (131U)
/******************************************************************************
*    Handles of receive signals                                                  
******************************************************************************/
/*New_Message_R1 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R1    (0U)
#define COM_RXSIGNew_Signal_111R101    (1U)
#define COM_RXSIGNew_Signal_111R102    (2U)
#define COM_RXSIGNew_Signal_111R103    (3U)
#define COM_RXSIGNew_Signal_111R104    (4U)
#define COM_RXSIGNew_Signal_111R105    (5U)
#define COM_RXSIGNew_Signal_111R106    (6U)
#define COM_RXSIGNew_Signal_111R107    (7U)
/*New_Message_R2 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R2    (8U)
#define COM_RXSIGNew_Signal_111R204    (9U)
#define COM_RXSIGNew_Signal_111R203    (10U)
#define COM_RXSIGNew_Signal_111R202    (11U)
#define COM_RXSIGNew_Signal_111R201    (12U)
#define COM_RXSIGNew_Signal_111R205    (13U)
#define COM_RXSIGNew_Signal_111R206    (14U)
#define COM_RXSIGNew_Signal_111R207    (15U)
/*New_Message_R3 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R3    (16U)
#define COM_RXSIGNew_Signal_111R301    (17U)
#define COM_RXSIGNew_Signal_111R302    (18U)
#define COM_RXSIGNew_Signal_111R303    (19U)
#define COM_RXSIGNew_Signal_111R304    (20U)
#define COM_RXSIGNew_Signal_111R305    (21U)
#define COM_RXSIGNew_Signal_111R306    (22U)
#define COM_RXSIGNew_Signal_111R307    (23U)
/*New_Message_R4 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R4    (24U)
/*New_Message_R5 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R5    (25U)
/*New_Message_R6 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R6    (26U)
/*New_Message_R7 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R7    (27U)
/*New_Message_R8 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R8    (28U)
/*New_Message_R9 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R9    (29U)
/*New_Message_R10 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R10    (30U)
/*New_Message_R11 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R11    (31U)
/*New_Message_R12 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R12    (32U)
/*New_Message_R13 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R13    (33U)
/*New_Message_R14 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R14    (34U)
/*New_Message_R15 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R15    (35U)
/*New_Message_R16 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R16    (36U)
/*New_Message_R17 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R17    (37U)
/*New_Message_R18 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R18    (38U)
/*New_Message_R19 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R19    (39U)
/*New_Message_R20 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R20    (40U)
/*New_Message_R21 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R21    (41U)
/*New_Message_R22 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R22    (42U)
/*New_Message_R23 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R23    (43U)
/*New_Message_R24 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R24    (44U)
/*New_Message_R25 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R25    (45U)
/*New_Message_R26 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R26    (46U)
/*New_Message_R27 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R27    (47U)
/*New_Message_R28 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R28    (48U)
/*New_Message_R29 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R29    (49U)
/*New_Message_R30 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R30    (50U)
/*New_Message_R31 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R31    (51U)
/*New_Message_R32 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R32    (52U)
/*New_Message_R33 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R33    (53U)
/*New_Message_R34 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R34    (54U)
/*New_Message_R35 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R35    (55U)
/*New_Message_R36 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R36    (56U)
/*New_Message_R37 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R37    (57U)
/*New_Message_R38 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R38    (58U)
/*New_Message_R39 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R39    (59U)
/*New_Message_R40 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R40    (60U)
/*New_Message_R41 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R41    (61U)
/*New_Message_R42 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R42    (62U)
/*New_Message_R43 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R43    (63U)
/*New_Message_R44 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R44    (64U)
/*New_Message_R45 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R45    (65U)
/*New_Message_R46 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R46    (66U)
/*New_Message_R47 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R47    (67U)
/*New_Message_R48 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R48    (68U)
/*New_Message_R49 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R49    (69U)
/*New_Message_R50 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R50    (70U)
/*New_Message_R51 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R51    (71U)
/*New_Message_R52 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R52    (72U)
/*New_Message_R53 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R53    (73U)
/*New_Message_R54 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R54    (74U)
/*New_Message_R55 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R55    (75U)
/*New_Message_R56 MEIJIA_11RX_mix*/
#define COM_RXSIGNew_Signal_111R56    (76U)
/*PPEI_Engine_General_Status_1 MEIJIA_11RX_mix*/
#define COM_RXSIGEngSpdStat    (77U)
#define COM_RXSIGEngIdlAtv    (78U)
#define COM_RXSIGEngRunAtv    (79U)
#define COM_RXSIGEngSpd    (80U)
#define COM_RXSIGDrvThrottlOvrrdDet    (81U)
#define COM_RXSIGCrsCntEnbld    (82U)
#define COM_RXSIGCrsCntAtv    (83U)
#define COM_RXSIGAccActPosV    (84U)
#define COM_RXSIGAccActPos    (85U)
#define COM_RXSIGPT_BrkPedDscrtInpStat    (86U)
#define COM_RXSIGPT_BrkPedDscrtInpStatV    (87U)
#define COM_RXSIGEngRelSta    (88U)
#define COM_RXSIGPPEI_Eng_Gen_Sta_1_ACR    (89U)
#define COM_RXSIGEngGenSta_1Cksm    (90U)
/*Vehicle_Odometer MEIJIA_11RX_mix*/
#define COM_RXSIGVehOdo    (91U)
#define COM_RXSIGVehOdoV    (92U)
/*PEPS_Door_Lock_Command MEIJIA_11RX_mix*/
#define COM_RXSIGDoorLockCmdIn    (93U)
#define COM_RXSIGFobCmdIn    (94U)
#define COM_RXSIGPEPSKeyreminderUnlock    (95U)
#define COM_RXSIGPEPSSATOIndicationLEDControl    (96U)
#define COM_RXSIGInEntCmdIn    (97U)
#define COM_RXSIGPEPSWELReq    (98U)
/*Aatilock_Brake_and_TC_Status_HS MEIJIA_11RX_mix*/
#define COM_RXSIGBrkProcInPrgrsIO    (99U)
#define COM_RXSIGABSIO    (100U)
#define COM_RXSIGAnt_Bra_and_Tc_Sta_HSRC    (101U)
#define COM_RXSIGVSESysOffIO    (102U)
#define COM_RXSIGVehSpdAvgDrvnRd    (103U)
#define COM_RXSIGAnt_Bra_and_Tc_Sta_HSCKsm    (104U)
#define COM_RXSIGVehStabEnhmntStat    (105U)
#define COM_RXSIGVehSpdAvgDrvnRdV    (106U)
/*PPEI_Platform_General_Status MEIJIA_11RX_mix*/
#define COM_RXSIGIgnKyPstn    (107U)
#define COM_RXSIGIgnKyInstAtv    (108U)
#define COM_RXSIGPrkBrkSwAtv    (109U)
#define COM_RXSIGTrnsRvsSwSt    (110U)
/*AC_Torque_Status MEIJIA_11RX_mix*/
#define COM_RXSIGThCompTorReqV    (111U)
#define COM_RXSIGThCompWorReq    (112U)
#define COM_RXSIGThCompTorReq    (113U)
/*PEPS_General_Status MEIJIA_11RX_mix*/
#define COM_RXSIGPEPSAuthnSt    (114U)
#define COM_RXSIGSysPowModeV    (115U)
#define COM_RXSIGSysPowMode    (116U)
#define COM_RXSIGBrkPedSwSt    (117U)
#define COM_RXSIGGearInOnParPos    (118U)
#define COM_RXSIGPEPSStrtrR1ySt    (119U)
#define COM_RXSIGPEPSIG2R1ySt    (120U)
#define COM_RXSIGPEPSIG1R1ySt    (121U)
#define COM_RXSIGPEPSACCR1ySt    (122U)
#define COM_RXSIGSSBSW2St    (123U)
#define COM_RXSIGSSBSw1St    (124U)
#define COM_RXSIGPEPSIG1R1yStV    (125U)
#define COM_RXSIGPEPSWELQuitReason    (126U)
#define COM_RXSIGPEPSSATOQuitReason    (127U)
#define COM_RXSIGPEPSGenStaRC    (128U)
#define COM_RXSIGPEPSLmSt    (129U)
#define COM_RXSIGPEPSGenStaCksm    (130U)

/******************************************************************************
*    Receive Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 New_Signal_111R1 : 8;
    uint8 New_Signal_111R101 : 8;
    uint8 New_Signal_111R102 : 8;
    uint8 New_Signal_111R103 : 8;
    uint8 New_Signal_111R104 : 8;
    uint8 New_Signal_111R105 : 8;
    uint8 New_Signal_111R106 : 8;
    uint8 New_Signal_111R107 : 8;
}IpduNew_Message_R1_Type;

typedef struct {
    uint8 New_Signal_111R2 : 8;
    uint8 New_Signal_111R204 : 8;
    uint8 New_Signal_111R203 : 8;
    uint8 New_Signal_111R202 : 8;
    uint8 New_Signal_111R201 : 8;
    uint8 New_Signal_111R205 : 8;
    uint8 New_Signal_111R206 : 8;
    uint8 New_Signal_111R207 : 8;
}IpduNew_Message_R2_Type;

typedef struct {
    uint8 New_Signal_111R3 : 8;
    uint8 New_Signal_111R301 : 8;
    uint8 New_Signal_111R302 : 8;
    uint8 New_Signal_111R303 : 8;
    uint8 New_Signal_111R304 : 8;
    uint8 New_Signal_111R305 : 8;
    uint8 New_Signal_111R306 : 8;
    uint8 New_Signal_111R307 : 8;
}IpduNew_Message_R3_Type;

typedef struct {
    uint8 New_Signal_111R4 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R4_Type;

typedef struct {
    uint8 New_Signal_111R5 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R5_Type;

typedef struct {
    uint8 New_Signal_111R6 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R6_Type;

typedef struct {
    uint8 New_Signal_111R7 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R7_Type;

typedef struct {
    uint8 New_Signal_111R8 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R8_Type;

typedef struct {
    uint8 New_Signal_111R9 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R9_Type;

typedef struct {
    uint8 New_Signal_111R10 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R10_Type;

typedef struct {
    uint8 New_Signal_111R11 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R11_Type;

typedef struct {
    uint8 New_Signal_111R12 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R12_Type;

typedef struct {
    uint8 New_Signal_111R13 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R13_Type;

typedef struct {
    uint8 New_Signal_111R14 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R14_Type;

typedef struct {
    uint8 New_Signal_111R15 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R15_Type;

typedef struct {
    uint8 New_Signal_111R16 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R16_Type;

typedef struct {
    uint8 New_Signal_111R17 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R17_Type;

typedef struct {
    uint8 New_Signal_111R18 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R18_Type;

typedef struct {
    uint8 New_Signal_111R19 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R19_Type;

typedef struct {
    uint8 New_Signal_111R20 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R20_Type;

typedef struct {
    uint8 New_Signal_111R21 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R21_Type;

typedef struct {
    uint8 New_Signal_111R22 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R22_Type;

typedef struct {
    uint8 New_Signal_111R23 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R23_Type;

typedef struct {
    uint8 New_Signal_111R24 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R24_Type;

typedef struct {
    uint8 New_Signal_111R25 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R25_Type;

typedef struct {
    uint8 New_Signal_111R26 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R26_Type;

typedef struct {
    uint8 New_Signal_111R27 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R27_Type;

typedef struct {
    uint8 New_Signal_111R28 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R28_Type;

typedef struct {
    uint8 New_Signal_111R29 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R29_Type;

typedef struct {
    uint8 New_Signal_111R30 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R30_Type;

typedef struct {
    uint8 New_Signal_111R31 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R31_Type;

typedef struct {
    uint8 New_Signal_111R32 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R32_Type;

typedef struct {
    uint8 New_Signal_111R33 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R33_Type;

typedef struct {
    uint8 New_Signal_111R34 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R34_Type;

typedef struct {
    uint8 New_Signal_111R35 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R35_Type;

typedef struct {
    uint8 New_Signal_111R36 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R36_Type;

typedef struct {
    uint8 New_Signal_111R37 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R37_Type;

typedef struct {
    uint8 New_Signal_111R38 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R38_Type;

typedef struct {
    uint8 New_Signal_111R39 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R39_Type;

typedef struct {
    uint8 New_Signal_111R40 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R40_Type;

typedef struct {
    uint8 New_Signal_111R41 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R41_Type;

typedef struct {
    uint8 New_Signal_111R42 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R42_Type;

typedef struct {
    uint8 New_Signal_111R43 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R43_Type;

typedef struct {
    uint8 New_Signal_111R44 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R44_Type;

typedef struct {
    uint8 New_Signal_111R45 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R45_Type;

typedef struct {
    uint8 New_Signal_111R46 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R46_Type;

typedef struct {
    uint8 New_Signal_111R47 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R47_Type;

typedef struct {
    uint8 New_Signal_111R48 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R48_Type;

typedef struct {
    uint8 New_Signal_111R49 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R49_Type;

typedef struct {
    uint8 New_Signal_111R50 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R50_Type;

typedef struct {
    uint8 New_Signal_111R51 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R51_Type;

typedef struct {
    uint8 New_Signal_111R52 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R52_Type;

typedef struct {
    uint8 New_Signal_111R53 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R53_Type;

typedef struct {
    uint8 New_Signal_111R54 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R54_Type;

typedef struct {
    uint8 New_Signal_111R55 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R55_Type;

typedef struct {
    uint8 New_Signal_111R56 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduNew_Message_R56_Type;

typedef struct {
    uint8 EngSpdStat : 2;
    uint8 EngIdlAtv : 1;
    uint8 unused0 : 4;
    uint8 EngRunAtv : 1;
    uint8 EngSpd_Byte1 : 8;
    uint8 EngSpd_Byte0 : 8;
    uint8 unused1 : 4;
    uint8 DrvThrottlOvrrdDet : 1;
    uint8 CrsCntEnbld : 1;
    uint8 CrsCntAtv : 1;
    uint8 AccActPosV : 1;
    uint8 AccActPos : 8;
    uint8 PT_BrkPedDscrtInpStat : 1;
    uint8 PT_BrkPedDscrtInpStatV : 1;
    uint8 unused2 : 4;
    uint8 EngRelSta : 2;
    uint8 unused3 : 6;
    uint8 PPEI_Eng_Gen_Sta_1_ACR : 2;
    uint8 EngGenSta_1Cksm : 8;
}IpduPPEI_Engine_General_Status_1_Type;

typedef struct {
    uint8 VehOdo_Byte3 : 8;
    uint8 VehOdo_Byte2 : 8;
    uint8 VehOdo_Byte1 : 8;
    uint8 VehOdo_Byte0 : 8;
    uint8 VehOdoV : 1;
    uint8 unused0 : 7;
}IpduVehicle_Odometer_Type;

typedef struct {
    uint8 DoorLockCmdIn : 3;
    uint8 unused0 : 5;
    uint8 FobCmdIn : 4;
    uint8 unused1 : 4;
    uint8 PEPSKeyreminderUnlock : 1;
    uint8 unused2 : 1;
    uint8 PEPSSATOIndicationLEDControl : 2;
    uint8 unused3_Byte0 : 4;
    uint8 unused3_Byte1 : 2;
    uint8 InEntCmdIn : 3;
    uint8 PEPSWELReq : 2;
    uint8 unused4_Byte0 : 1;
    uint8 unused4_Byte1 : 8;
    uint8 unused4_Byte2 : 8;
    uint8 unused4_Byte3 : 8;
    uint8 unused4_Byte4 : 8;
}IpduPEPS_Door_Lock_Command_Type;

typedef struct {
    uint8 BrkProcInPrgrsIO : 1;
    uint8 ABSIO : 1;
    uint8 unused0_Byte0 : 6;
    uint8 unused0_Byte1 : 2;
    uint8 Ant_Bra_and_Tc_Sta_HSRC : 2;
    uint8 unused1 : 2;
    uint8 VSESysOffIO : 1;
    uint8 unused2 : 1;
    uint8 VehSpdAvgDrvnRd_Byte2 : 4;
    uint8 unused3 : 4;
    uint8 VehSpdAvgDrvnRd_Byte1 : 8;
    uint8 unused4 : 5;
    uint8 VehSpdAvgDrvnRd_Byte0 : 3;
    uint8 Ant_Bra_and_Tc_Sta_HSCKsm : 8;
    uint8 unused5 : 4;
    uint8 VehStabEnhmntStat : 2;
    uint8 unused6_Byte0 : 2;
    uint8 unused6_Byte1 : 5;
    uint8 VehSpdAvgDrvnRdV : 1;
    uint8 unused7 : 2;
}IpduAatilock_Brake_and_TC_Status_HS_Type;

typedef struct {
    uint8 unused0 : 4;
    uint8 IgnKyPstn : 2;
    uint8 IgnKyInstAtv : 1;
    uint8 unused1_Byte0 : 1;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 4;
    uint8 PrkBrkSwAtv : 1;
    uint8 unused2_Byte0 : 3;
    uint8 unused2_Byte1 : 6;
    uint8 TrnsRvsSwSt : 1;
    uint8 unused3_Byte0 : 1;
    uint8 unused3_Byte1 : 8;
    uint8 unused3_Byte2 : 8;
}IpduPPEI_Platform_General_Status_Type;

typedef struct {
    uint8 unused0 : 6;
    uint8 ThCompTorReqV : 1;
    uint8 ThCompWorReq : 1;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 ThCompTorReq : 8;
    uint8 unused2 : 8;
}IpduAC_Torque_Status_Type;

typedef struct {
    uint8 PEPSAuthnSt : 3;
    uint8 SysPowModeV : 1;
    uint8 SysPowMode : 2;
    uint8 BrkPedSwSt : 1;
    uint8 GearInOnParPos : 1;
    uint8 unused0 : 2;
    uint8 PEPSStrtrR1ySt : 1;
    uint8 PEPSIG2R1ySt : 1;
    uint8 PEPSIG1R1ySt : 1;
    uint8 PEPSACCR1ySt : 1;
    uint8 SSBSW2St : 1;
    uint8 SSBSw1St : 1;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 7;
    uint8 PEPSIG1R1yStV : 1;
    uint8 unused2 : 4;
    uint8 PEPSWELQuitReason : 4;
    uint8 unused3 : 4;
    uint8 PEPSSATOQuitReason : 4;
    uint8 PEPSGenStaRC : 2;
    uint8 unused4 : 4;
    uint8 PEPSLmSt : 2;
    uint8 PEPSGenStaCksm : 8;
}IpduPEPS_General_Status_Type;


/******************************************************************************
*    Receive Message unions                                                       
******************************************************************************/
typedef union {
    IpduNew_Message_R1_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R1_bufType;

typedef union {
    IpduNew_Message_R2_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R2_bufType;

typedef union {
    IpduNew_Message_R3_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R3_bufType;

typedef union {
    IpduNew_Message_R4_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R4_bufType;

typedef union {
    IpduNew_Message_R5_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R5_bufType;

typedef union {
    IpduNew_Message_R6_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R6_bufType;

typedef union {
    IpduNew_Message_R7_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R7_bufType;

typedef union {
    IpduNew_Message_R8_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R8_bufType;

typedef union {
    IpduNew_Message_R9_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R9_bufType;

typedef union {
    IpduNew_Message_R10_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R10_bufType;

typedef union {
    IpduNew_Message_R11_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R11_bufType;

typedef union {
    IpduNew_Message_R12_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R12_bufType;

typedef union {
    IpduNew_Message_R13_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R13_bufType;

typedef union {
    IpduNew_Message_R14_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R14_bufType;

typedef union {
    IpduNew_Message_R15_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R15_bufType;

typedef union {
    IpduNew_Message_R16_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R16_bufType;

typedef union {
    IpduNew_Message_R17_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R17_bufType;

typedef union {
    IpduNew_Message_R18_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R18_bufType;

typedef union {
    IpduNew_Message_R19_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R19_bufType;

typedef union {
    IpduNew_Message_R20_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R20_bufType;

typedef union {
    IpduNew_Message_R21_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R21_bufType;

typedef union {
    IpduNew_Message_R22_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R22_bufType;

typedef union {
    IpduNew_Message_R23_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R23_bufType;

typedef union {
    IpduNew_Message_R24_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R24_bufType;

typedef union {
    IpduNew_Message_R25_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R25_bufType;

typedef union {
    IpduNew_Message_R26_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R26_bufType;

typedef union {
    IpduNew_Message_R27_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R27_bufType;

typedef union {
    IpduNew_Message_R28_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R28_bufType;

typedef union {
    IpduNew_Message_R29_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R29_bufType;

typedef union {
    IpduNew_Message_R30_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R30_bufType;

typedef union {
    IpduNew_Message_R31_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R31_bufType;

typedef union {
    IpduNew_Message_R32_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R32_bufType;

typedef union {
    IpduNew_Message_R33_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R33_bufType;

typedef union {
    IpduNew_Message_R34_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R34_bufType;

typedef union {
    IpduNew_Message_R35_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R35_bufType;

typedef union {
    IpduNew_Message_R36_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R36_bufType;

typedef union {
    IpduNew_Message_R37_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R37_bufType;

typedef union {
    IpduNew_Message_R38_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R38_bufType;

typedef union {
    IpduNew_Message_R39_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R39_bufType;

typedef union {
    IpduNew_Message_R40_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R40_bufType;

typedef union {
    IpduNew_Message_R41_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R41_bufType;

typedef union {
    IpduNew_Message_R42_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R42_bufType;

typedef union {
    IpduNew_Message_R43_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R43_bufType;

typedef union {
    IpduNew_Message_R44_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R44_bufType;

typedef union {
    IpduNew_Message_R45_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R45_bufType;

typedef union {
    IpduNew_Message_R46_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R46_bufType;

typedef union {
    IpduNew_Message_R47_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R47_bufType;

typedef union {
    IpduNew_Message_R48_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R48_bufType;

typedef union {
    IpduNew_Message_R49_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R49_bufType;

typedef union {
    IpduNew_Message_R50_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R50_bufType;

typedef union {
    IpduNew_Message_R51_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R51_bufType;

typedef union {
    IpduNew_Message_R52_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R52_bufType;

typedef union {
    IpduNew_Message_R53_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R53_bufType;

typedef union {
    IpduNew_Message_R54_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R54_bufType;

typedef union {
    IpduNew_Message_R55_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R55_bufType;

typedef union {
    IpduNew_Message_R56_Type  Ipdu;
    uint8  _c[8];
}IpduNew_Message_R56_bufType;

typedef union {
    IpduPPEI_Engine_General_Status_1_Type  Ipdu;
    uint8  _c[8];
}IpduPPEI_Engine_General_Status_1_bufType;

typedef union {
    IpduVehicle_Odometer_Type  Ipdu;
    uint8  _c[5];
}IpduVehicle_Odometer_bufType;

typedef union {
    IpduPEPS_Door_Lock_Command_Type  Ipdu;
    uint8  _c[8];
}IpduPEPS_Door_Lock_Command_bufType;

typedef union {
    IpduAatilock_Brake_and_TC_Status_HS_Type  Ipdu;
    uint8  _c[8];
}IpduAatilock_Brake_and_TC_Status_HS_bufType;

typedef union {
    IpduPPEI_Platform_General_Status_Type  Ipdu;
    uint8  _c[8];
}IpduPPEI_Platform_General_Status_bufType;

typedef union {
    IpduAC_Torque_Status_Type  Ipdu;
    uint8  _c[8];
}IpduAC_Torque_Status_bufType;

typedef union {
    IpduPEPS_General_Status_Type  Ipdu;
    uint8  _c[8];
}IpduPEPS_General_Status_bufType;


/******************************************************************************
*    Databuffer for Receive objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduNew_Message_R1_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R1;
extern VAR(IpduNew_Message_R2_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R2;
extern VAR(IpduNew_Message_R3_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R3;
extern VAR(IpduNew_Message_R4_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R4;
extern VAR(IpduNew_Message_R5_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R5;
extern VAR(IpduNew_Message_R6_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R6;
extern VAR(IpduNew_Message_R7_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R7;
extern VAR(IpduNew_Message_R8_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R8;
extern VAR(IpduNew_Message_R9_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R9;
extern VAR(IpduNew_Message_R10_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R10;
extern VAR(IpduNew_Message_R11_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R11;
extern VAR(IpduNew_Message_R12_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R12;
extern VAR(IpduNew_Message_R13_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R13;
extern VAR(IpduNew_Message_R14_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R14;
extern VAR(IpduNew_Message_R15_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R15;
extern VAR(IpduNew_Message_R16_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R16;
extern VAR(IpduNew_Message_R17_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R17;
extern VAR(IpduNew_Message_R18_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R18;
extern VAR(IpduNew_Message_R19_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R19;
extern VAR(IpduNew_Message_R20_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R20;
extern VAR(IpduNew_Message_R21_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R21;
extern VAR(IpduNew_Message_R22_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R22;
extern VAR(IpduNew_Message_R23_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R23;
extern VAR(IpduNew_Message_R24_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R24;
extern VAR(IpduNew_Message_R25_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R25;
extern VAR(IpduNew_Message_R26_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R26;
extern VAR(IpduNew_Message_R27_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R27;
extern VAR(IpduNew_Message_R28_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R28;
extern VAR(IpduNew_Message_R29_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R29;
extern VAR(IpduNew_Message_R30_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R30;
extern VAR(IpduNew_Message_R31_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R31;
extern VAR(IpduNew_Message_R32_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R32;
extern VAR(IpduNew_Message_R33_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R33;
extern VAR(IpduNew_Message_R34_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R34;
extern VAR(IpduNew_Message_R35_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R35;
extern VAR(IpduNew_Message_R36_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R36;
extern VAR(IpduNew_Message_R37_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R37;
extern VAR(IpduNew_Message_R38_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R38;
extern VAR(IpduNew_Message_R39_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R39;
extern VAR(IpduNew_Message_R40_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R40;
extern VAR(IpduNew_Message_R41_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R41;
extern VAR(IpduNew_Message_R42_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R42;
extern VAR(IpduNew_Message_R43_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R43;
extern VAR(IpduNew_Message_R44_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R44;
extern VAR(IpduNew_Message_R45_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R45;
extern VAR(IpduNew_Message_R46_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R46;
extern VAR(IpduNew_Message_R47_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R47;
extern VAR(IpduNew_Message_R48_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R48;
extern VAR(IpduNew_Message_R49_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R49;
extern VAR(IpduNew_Message_R50_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R50;
extern VAR(IpduNew_Message_R51_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R51;
extern VAR(IpduNew_Message_R52_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R52;
extern VAR(IpduNew_Message_R53_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R53;
extern VAR(IpduNew_Message_R54_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R54;
extern VAR(IpduNew_Message_R55_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R55;
extern VAR(IpduNew_Message_R56_bufType, COM_PRIVATE_DATA)  RxIpduNew_Message_R56;
extern VAR(IpduPPEI_Engine_General_Status_1_bufType, COM_PRIVATE_DATA)  RxIpduPPEI_Engine_General_Status_1;
extern VAR(IpduVehicle_Odometer_bufType, COM_PRIVATE_DATA)  RxIpduVehicle_Odometer;
extern VAR(IpduPEPS_Door_Lock_Command_bufType, COM_PRIVATE_DATA)  RxIpduPEPS_Door_Lock_Command;
extern VAR(IpduAatilock_Brake_and_TC_Status_HS_bufType, COM_PRIVATE_DATA)  RxIpduAatilock_Brake_and_TC_Status_HS;
extern VAR(IpduPPEI_Platform_General_Status_bufType, COM_PRIVATE_DATA)  RxIpduPPEI_Platform_General_Status;
extern VAR(IpduAC_Torque_Status_bufType, COM_PRIVATE_DATA)  RxIpduAC_Torque_Status;
extern VAR(IpduPEPS_General_Status_bufType, COM_PRIVATE_DATA)  RxIpduPEPS_General_Status;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Receive Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduNew_Message_R1_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R1DefaultValue;
extern CONST(IpduNew_Message_R2_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R2DefaultValue;
extern CONST(IpduNew_Message_R3_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R3DefaultValue;
extern CONST(IpduNew_Message_R4_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R4DefaultValue;
extern CONST(IpduNew_Message_R5_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R5DefaultValue;
extern CONST(IpduNew_Message_R6_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R6DefaultValue;
extern CONST(IpduNew_Message_R7_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R7DefaultValue;
extern CONST(IpduNew_Message_R8_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R8DefaultValue;
extern CONST(IpduNew_Message_R9_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R9DefaultValue;
extern CONST(IpduNew_Message_R10_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R10DefaultValue;
extern CONST(IpduNew_Message_R11_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R11DefaultValue;
extern CONST(IpduNew_Message_R12_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R12DefaultValue;
extern CONST(IpduNew_Message_R13_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R13DefaultValue;
extern CONST(IpduNew_Message_R14_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R14DefaultValue;
extern CONST(IpduNew_Message_R15_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R15DefaultValue;
extern CONST(IpduNew_Message_R16_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R16DefaultValue;
extern CONST(IpduNew_Message_R17_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R17DefaultValue;
extern CONST(IpduNew_Message_R18_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R18DefaultValue;
extern CONST(IpduNew_Message_R19_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R19DefaultValue;
extern CONST(IpduNew_Message_R20_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R20DefaultValue;
extern CONST(IpduNew_Message_R21_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R21DefaultValue;
extern CONST(IpduNew_Message_R22_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R22DefaultValue;
extern CONST(IpduNew_Message_R23_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R23DefaultValue;
extern CONST(IpduNew_Message_R24_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R24DefaultValue;
extern CONST(IpduNew_Message_R25_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R25DefaultValue;
extern CONST(IpduNew_Message_R26_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R26DefaultValue;
extern CONST(IpduNew_Message_R27_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R27DefaultValue;
extern CONST(IpduNew_Message_R28_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R28DefaultValue;
extern CONST(IpduNew_Message_R29_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R29DefaultValue;
extern CONST(IpduNew_Message_R30_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R30DefaultValue;
extern CONST(IpduNew_Message_R31_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R31DefaultValue;
extern CONST(IpduNew_Message_R32_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R32DefaultValue;
extern CONST(IpduNew_Message_R33_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R33DefaultValue;
extern CONST(IpduNew_Message_R34_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R34DefaultValue;
extern CONST(IpduNew_Message_R35_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R35DefaultValue;
extern CONST(IpduNew_Message_R36_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R36DefaultValue;
extern CONST(IpduNew_Message_R37_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R37DefaultValue;
extern CONST(IpduNew_Message_R38_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R38DefaultValue;
extern CONST(IpduNew_Message_R39_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R39DefaultValue;
extern CONST(IpduNew_Message_R40_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R40DefaultValue;
extern CONST(IpduNew_Message_R41_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R41DefaultValue;
extern CONST(IpduNew_Message_R42_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R42DefaultValue;
extern CONST(IpduNew_Message_R43_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R43DefaultValue;
extern CONST(IpduNew_Message_R44_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R44DefaultValue;
extern CONST(IpduNew_Message_R45_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R45DefaultValue;
extern CONST(IpduNew_Message_R46_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R46DefaultValue;
extern CONST(IpduNew_Message_R47_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R47DefaultValue;
extern CONST(IpduNew_Message_R48_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R48DefaultValue;
extern CONST(IpduNew_Message_R49_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R49DefaultValue;
extern CONST(IpduNew_Message_R50_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R50DefaultValue;
extern CONST(IpduNew_Message_R51_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R51DefaultValue;
extern CONST(IpduNew_Message_R52_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R52DefaultValue;
extern CONST(IpduNew_Message_R53_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R53DefaultValue;
extern CONST(IpduNew_Message_R54_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R54DefaultValue;
extern CONST(IpduNew_Message_R55_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R55DefaultValue;
extern CONST(IpduNew_Message_R56_bufType, COM_CONFIG_CONST)  RxIpduNew_Message_R56DefaultValue;
extern CONST(IpduPPEI_Engine_General_Status_1_bufType, COM_CONFIG_CONST)  RxIpduPPEI_Engine_General_Status_1DefaultValue;
extern CONST(IpduVehicle_Odometer_bufType, COM_CONFIG_CONST)  RxIpduVehicle_OdometerDefaultValue;
extern CONST(IpduPEPS_Door_Lock_Command_bufType, COM_CONFIG_CONST)  RxIpduPEPS_Door_Lock_CommandDefaultValue;
extern CONST(IpduAatilock_Brake_and_TC_Status_HS_bufType, COM_CONFIG_CONST)  RxIpduAatilock_Brake_and_TC_Status_HSDefaultValue;
extern CONST(IpduPPEI_Platform_General_Status_bufType, COM_CONFIG_CONST)  RxIpduPPEI_Platform_General_StatusDefaultValue;
extern CONST(IpduAC_Torque_Status_bufType, COM_CONFIG_CONST)  RxIpduAC_Torque_StatusDefaultValue;
extern CONST(IpduPEPS_General_Status_bufType, COM_CONFIG_CONST)  RxIpduPEPS_General_StatusDefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_RXIPDUNUM >= 1u)

/******************************************************************************
*    rx Ipdu timeout indication function Declare                               
******************************************************************************/
#ifdef COM_ENABLE_RXTOINDFUN 
extern void AppRxIpduNew_Message_R1_TimeOutInd(void);
extern void AppRxIpduNew_Message_R2_TimeOutInd(void);
extern void AppRxIpduNew_Message_R3_TimeOutInd(void);
extern void AppRxIpduNew_Message_R4_TimeOutInd(void);
extern void AppRxIpduNew_Message_R5_TimeOutInd(void);
extern void AppRxIpduNew_Message_R6_TimeOutInd(void);
extern void AppRxIpduNew_Message_R7_TimeOutInd(void);
extern void AppRxIpduNew_Message_R8_TimeOutInd(void);
extern void AppRxIpduNew_Message_R9_TimeOutInd(void);
extern void AppRxIpduNew_Message_R10_TimeOutInd(void);
extern void AppRxIpduNew_Message_R11_TimeOutInd(void);
extern void AppRxIpduNew_Message_R12_TimeOutInd(void);
extern void AppRxIpduNew_Message_R13_TimeOutInd(void);
extern void AppRxIpduNew_Message_R14_TimeOutInd(void);
extern void AppRxIpduNew_Message_R15_TimeOutInd(void);
extern void AppRxIpduNew_Message_R16_TimeOutInd(void);
extern void AppRxIpduNew_Message_R17_TimeOutInd(void);
extern void AppRxIpduNew_Message_R18_TimeOutInd(void);
extern void AppRxIpduNew_Message_R19_TimeOutInd(void);
extern void AppRxIpduNew_Message_R20_TimeOutInd(void);
extern void AppRxIpduNew_Message_R21_TimeOutInd(void);
extern void AppRxIpduNew_Message_R22_TimeOutInd(void);
extern void AppRxIpduNew_Message_R23_TimeOutInd(void);
extern void AppRxIpduNew_Message_R24_TimeOutInd(void);
extern void AppRxIpduNew_Message_R25_TimeOutInd(void);
extern void AppRxIpduNew_Message_R26_TimeOutInd(void);
extern void AppRxIpduNew_Message_R27_TimeOutInd(void);
extern void AppRxIpduNew_Message_R28_TimeOutInd(void);
extern void AppRxIpduNew_Message_R29_TimeOutInd(void);
extern void AppRxIpduNew_Message_R30_TimeOutInd(void);
extern void AppRxIpduNew_Message_R31_TimeOutInd(void);
extern void AppRxIpduNew_Message_R32_TimeOutInd(void);
extern void AppRxIpduNew_Message_R33_TimeOutInd(void);
extern void AppRxIpduNew_Message_R34_TimeOutInd(void);
extern void AppRxIpduNew_Message_R35_TimeOutInd(void);
extern void AppRxIpduNew_Message_R36_TimeOutInd(void);
extern void AppRxIpduNew_Message_R37_TimeOutInd(void);
extern void AppRxIpduNew_Message_R38_TimeOutInd(void);
extern void AppRxIpduNew_Message_R39_TimeOutInd(void);
extern void AppRxIpduNew_Message_R40_TimeOutInd(void);
extern void AppRxIpduNew_Message_R41_TimeOutInd(void);
extern void AppRxIpduNew_Message_R42_TimeOutInd(void);
extern void AppRxIpduNew_Message_R43_TimeOutInd(void);
extern void AppRxIpduNew_Message_R44_TimeOutInd(void);
extern void AppRxIpduNew_Message_R45_TimeOutInd(void);
extern void AppRxIpduNew_Message_R46_TimeOutInd(void);
extern void AppRxIpduNew_Message_R47_TimeOutInd(void);
extern void AppRxIpduNew_Message_R48_TimeOutInd(void);
extern void AppRxIpduNew_Message_R49_TimeOutInd(void);
extern void AppRxIpduNew_Message_R50_TimeOutInd(void);
extern void AppRxIpduNew_Message_R51_TimeOutInd(void);
extern void AppRxIpduNew_Message_R52_TimeOutInd(void);
extern void AppRxIpduNew_Message_R53_TimeOutInd(void);
extern void AppRxIpduNew_Message_R54_TimeOutInd(void);
extern void AppRxIpduNew_Message_R55_TimeOutInd(void);
extern void AppRxIpduNew_Message_R56_TimeOutInd(void);
extern void AppRxIpduPPEI_Engine_General_Status_1_TimeOutInd(void);
extern void AppRxIpduVehicle_Odometer_TimeOutInd(void);
extern void AppRxIpduPEPS_Door_Lock_Command_TimeOutInd(void);
extern void AppRxIpduAatilock_Brake_and_TC_Status_HS_TimeOutInd(void);
extern void AppRxIpduPPEI_Platform_General_Status_TimeOutInd(void);
extern void AppRxIpduAC_Torque_Status_TimeOutInd(void);
extern void AppRxIpduPEPS_General_Status_TimeOutInd(void);
#endif

/******************************************************************************
*    Rx indication function Declare                                            
******************************************************************************/
#ifdef COM_ENABLE_RXINDICATIONFUN 
extern void AppIpduNew_Message_R1_Ind(void);
extern void AppIpduNew_Message_R2_Ind(void);
extern void AppIpduNew_Message_R3_Ind(void);
extern void AppIpduNew_Message_R4_Ind(void);
extern void AppIpduNew_Message_R5_Ind(void);
extern void AppIpduNew_Message_R6_Ind(void);
extern void AppIpduNew_Message_R7_Ind(void);
extern void AppIpduNew_Message_R8_Ind(void);
extern void AppIpduNew_Message_R9_Ind(void);
extern void AppIpduNew_Message_R10_Ind(void);
extern void AppIpduNew_Message_R11_Ind(void);
extern void AppIpduNew_Message_R12_Ind(void);
extern void AppIpduNew_Message_R13_Ind(void);
extern void AppIpduNew_Message_R14_Ind(void);
extern void AppIpduNew_Message_R15_Ind(void);
extern void AppIpduNew_Message_R16_Ind(void);
extern void AppIpduNew_Message_R17_Ind(void);
extern void AppIpduNew_Message_R18_Ind(void);
extern void AppIpduNew_Message_R19_Ind(void);
extern void AppIpduNew_Message_R20_Ind(void);
extern void AppIpduNew_Message_R21_Ind(void);
extern void AppIpduNew_Message_R22_Ind(void);
extern void AppIpduNew_Message_R23_Ind(void);
extern void AppIpduNew_Message_R24_Ind(void);
extern void AppIpduNew_Message_R25_Ind(void);
extern void AppIpduNew_Message_R26_Ind(void);
extern void AppIpduNew_Message_R27_Ind(void);
extern void AppIpduNew_Message_R28_Ind(void);
extern void AppIpduNew_Message_R29_Ind(void);
extern void AppIpduNew_Message_R30_Ind(void);
extern void AppIpduNew_Message_R31_Ind(void);
extern void AppIpduNew_Message_R32_Ind(void);
extern void AppIpduNew_Message_R33_Ind(void);
extern void AppIpduNew_Message_R34_Ind(void);
extern void AppIpduNew_Message_R35_Ind(void);
extern void AppIpduNew_Message_R36_Ind(void);
extern void AppIpduNew_Message_R37_Ind(void);
extern void AppIpduNew_Message_R38_Ind(void);
extern void AppIpduNew_Message_R39_Ind(void);
extern void AppIpduNew_Message_R40_Ind(void);
extern void AppIpduNew_Message_R41_Ind(void);
extern void AppIpduNew_Message_R42_Ind(void);
extern void AppIpduNew_Message_R43_Ind(void);
extern void AppIpduNew_Message_R44_Ind(void);
extern void AppIpduNew_Message_R45_Ind(void);
extern void AppIpduNew_Message_R46_Ind(void);
extern void AppIpduNew_Message_R47_Ind(void);
extern void AppIpduNew_Message_R48_Ind(void);
extern void AppIpduNew_Message_R49_Ind(void);
extern void AppIpduNew_Message_R50_Ind(void);
extern void AppIpduNew_Message_R51_Ind(void);
extern void AppIpduNew_Message_R52_Ind(void);
extern void AppIpduNew_Message_R53_Ind(void);
extern void AppIpduNew_Message_R54_Ind(void);
extern void AppIpduNew_Message_R55_Ind(void);
extern void AppIpduNew_Message_R56_Ind(void);
extern void AppIpduPPEI_Engine_General_Status_1_Ind(void);
extern void AppIpduVehicle_Odometer_Ind(void);
extern void AppIpduPEPS_Door_Lock_Command_Ind(void);
extern void AppIpduAatilock_Brake_and_TC_Status_HS_Ind(void);
extern void AppIpduPPEI_Platform_General_Status_Ind(void);
extern void AppIpduAC_Torque_Status_Ind(void);
extern void AppIpduPEPS_General_Status_Ind(void);
#endif

#endif /*#if (COM_RXIPDUNUM>=1)*/ 

/******************************************************************************
*    Signal Gateway                                                            
******************************************************************************/
#ifdef COM_ENABLE_ROUTESIGNAL
#define COM_GWIPDUNUM    (0U)
#define COM_GWSIGNUM     (0U)
#endif

/******************************************************************************
*    Ipdu Group                                                                
******************************************************************************/
#if((COM_TXIPDUNUM >= 1u) || (COM_RXIPDUNUM >= 1u))
#define COM_IPDUGROUPNUM    (2U)
#define COM_IPDUGROUP0    (0x1U)
#define COM_IPDUGROUP1    (0x2U)
#define COM_GROUPIPDUNUM    (79U)
#endif

/******************************************************************************
*    data declaration                                                          
******************************************************************************/
extern void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr);
extern void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr);

#if(COM_TXIPDUNUM >= 1u)
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

extern VAR(PduInfoType, COM_APPL_DATA) Com_TxIpdu[COM_TXIPDUNUM];

#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

extern CONST(PduInfoType, COM_CONFIG_CONST)  Com_TxIpduInitTable[COM_TXIPDUNUM]; 
extern CONST(Com_TxSigTableType, COM_CONFIG_CONST)  Com_TxSigTable[COM_TXSIGNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_TxIpduDefaultValue[COM_TXIPDUNUM];

#ifdef COM_ENABLE_TXCONFIRMATIONFUN
extern CONST(Com_TxConfirmationType, COM_CONFIG_CONST)  Com_TxIpduConfirmTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_TXTOINDFUN
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST)  Com_TxIpduTOIndicationTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDUTXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST)  Com_LpduTxErrIndicationTable[COM_TXIPDUNUM];
#endif

extern CONST(uint8, COM_CONFIG_CONST)  Com_TxIpduTable[COM_TXIPDUNUM];

#ifndef COM_ENABLE_NONSENDTYPEONLY

#ifdef COM_ENABLE_ACTIVEPORPERTY 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduFastCycleTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduSigNum[COM_TXIPDUNUM];

extern FUNC(void, COM_PUBLIC_CODE) Com_ActiveSig
(
    Com_SignalIdType SignalId
);

extern FUNC(void, COM_PUBLIC_CODE) Com_DisactiveSig
(
    Com_SignalIdType SignalId
);

extern CONST(Com_SignalIdType, COM_CONFIG_CONST)  Com_TxSigOffsetTable[COM_TXIPDUNUM];

#endif

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTdelayTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduRepNumTable[COM_TXIPDUNUM];
#endif /*#ifndef COM_ENABLE_NONSENDTYPEONLY*/

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduCycleTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTimeOutTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduOffsetTable[COM_TXIPDUNUM];

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM >= 1u)

#ifdef COM_ENABLE_RXEXTEND
extern CONST(uint8, COM_CONFIG_CONST) Com_RxIpduSigNum[COM_RXIPDUNUM];
extern CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_RxSigOffsetTable[COM_RXIPDUNUM];
#endif

extern CONST(PduInfoType, COM_CONFIG_CONST) Com_RxIpduInitTable[COM_RXIPDUNUM];
extern CONST(Com_RxSigTableType, COM_CONFIG_CONST) Com_RxSigTable[COM_RXSIGNUM];
extern CONST(Com_RxIpduTableType, COM_CONFIG_CONST) Com_RxIpduTable[COM_RXIPDUNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduDefaultValue[COM_RXIPDUNUM];

#ifdef COM_ENABLE_RXINDICATIONFUN
extern CONST(Com_RxIndicationType, COM_CONFIG_CONST) Com_RxIpduIndicationTable[COM_RXIPDUNUM]; 
#endif

#ifdef COM_ENABLE_RXTOINDFUN 
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_RxIpduTOIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST) Com_LpduRxErrIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXSTARTINDIFUN
extern CONST(Com_LpduRxStartIndicationType, COM_CONFIG_CONST)  
             Com_LpduRxStartIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_RXTIMEOUTVALUE
extern  CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduTimeoutValue[COM_RXIPDUNUM];
#endif

extern CONST(PduLengthType, COM_CONFIG_CONST)  Com_RxIpduBufferSize[COM_RXIPDUNUM];


#endif /*#if(COM_RXIPDUNUM>=1)*/


#if(COM_TXIPDUNUM >= 1u)
extern CONST(Com_SendSignalType, COM_CONFIG_CONST)  Com_SendSignalTable[COM_TXSIGNUM];
#endif


#if(COM_RXIPDUNUM >= 1u)
extern  CONST(Com_ReceiveSignalType, COM_CONFIG_CONST)   Com_ReceiveSignalTable[COM_RXSIGNUM];
#endif

#ifdef COM_ENABLE_ROUTESIGNAL
#if(COM_GWSIGNUM >= 1u)
extern CONST(Com_SignalGatewayIpduTableType, COM_CONFIG_CONST)  
             Com_SignalGatewayIpduTable[COM_GWIPDUNUM];
             
extern CONST(Com_SignalGatewayTableType, COM_CONFIG_CONST)  Com_SignalGatewayTable[COM_GWSIGNUM];
#endif /*#if(COM_GWSIGNUM>=1)*/
#endif /*#ifdef COM_ENABLE_ROUTESIGNAL*/


#if(COM_IPDUGROUPNUM >= 1u)
extern CONST(Com_GroupIpduTableType, COM_CONFIG_CONST)  Com_GroupIpduTable[COM_GROUPIPDUNUM];
extern CONST(Com_IpduGroupTableType, COM_CONFIG_CONST)  Com_IpduGroupTable[COM_IPDUGROUPNUM];
#endif

#if(COM_TXIPDUNUM >= 1u)
extern CONST(PduIdType, COM_CONFIG_CONST) Com_TxIpduIdMapTable[COM_TXIPDUNUM];
#define Com_TransmitLPDU(ComTxPduId,PduInfoPtr)     CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr) 
#define Com_Transmit(ComTxPduId,PduInfoPtr)	        CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr)
#endif

#endif



