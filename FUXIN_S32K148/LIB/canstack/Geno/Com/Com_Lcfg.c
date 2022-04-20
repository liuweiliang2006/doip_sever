/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Lcfg.c
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

#define COM_START_SEC_PUBLIC_CODE 
#include "MemMap.h"
/*******************************************************************************
*   for Com_SendSignal 
*******************************************************************************/
FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_21
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_21 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_211
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_211 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_212
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_212 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_213
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_213 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_214
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_214 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_215
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_215 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_216
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_216 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_217
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_21.Ipdu.New_Signal_217 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_22
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_22 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_221
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_221 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_222
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_222 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_223
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_223 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_224
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_224 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_225
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_225 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_226
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_226 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_227
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_22.Ipdu.New_Signal_227 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_23
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_23 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_231
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_231 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_232
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_232 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_233
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_233 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_234
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_234 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_235
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_235 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_236
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_236 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_237
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_23.Ipdu.New_Signal_237 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_24
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_24 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_241
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_241 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_242
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_242 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_243
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_243 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_244
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_244 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_245
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_245 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_246
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_246 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_247
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_24.Ipdu.New_Signal_247 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_25
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_25 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_251
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_251 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_252
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_252 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_253
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_253 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_254
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_254 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_255
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_255 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_256
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_256 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_257
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_25.Ipdu.New_Signal_257 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_26
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_26 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_261
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_261 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_262
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_262 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_263
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_263 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_264
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_264 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_265
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_265 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_266
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_266 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_267
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_26.Ipdu.New_Signal_267 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_27
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_27 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_271
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_271 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_272
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_272 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_273
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_273 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_274
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_274 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_275
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_275 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_276
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_276 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_277
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_27.Ipdu.New_Signal_277 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_28
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_28 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_281
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_281 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_282
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_282 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_283
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_283 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_284
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_284 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_285
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_285 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_286
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_286 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_287
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_28.Ipdu.New_Signal_287 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_29
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_29 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_291
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_291 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_292
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_292 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_293
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_293 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_294
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_294 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_295
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_295 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_296
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_296 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_297
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_29.Ipdu.New_Signal_297 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_30
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_30 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_301
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_301 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_302
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_302 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_303
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_303 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_304
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_304 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_305
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_305 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_306
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_306 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_307
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_30.Ipdu.New_Signal_307 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_31
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_31 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_311
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_311 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_312
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_312 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_313
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_313 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_314
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_314 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_315
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_315 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_316
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_316 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_317
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_31.Ipdu.New_Signal_317 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_32
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_32 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_321
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_321 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_322
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_322 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_323
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_323 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_324
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_324 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_325
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_325 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_326
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_326 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_327
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_32.Ipdu.New_Signal_327 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_33
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_33 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_331
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_331 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_332
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_332 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_333
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_333 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_334
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_334 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_335
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_335 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_336
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_336 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_337
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_33.Ipdu.New_Signal_337 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_34
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_34 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_341
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_341 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_342
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_342 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_343
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_343 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_344
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_344 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_345
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_345 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_346
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_346 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigNew_Signal_347
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduNew_Message_34.Ipdu.New_Signal_347 = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGSysMSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGSysMSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGMaxOpePosSSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGMaxOpePosSSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGCrtOpePos
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGCrtOpePos = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGCrtOpePosV
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGCrtOpePosV = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGPwOptCmdAct
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGPwOptCmdAct = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLmSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLmSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtMSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtMSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGFlurAnls
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGFlurAnls = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtPrySglSwSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtPrySglSwSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtScdSglSwSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtScdSglSwSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtPwSglSwSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtPwSglSwSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtRstSglSwSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtRstSglSwSt = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGLtSnwLdIO
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_General_Status.Ipdu.PLGLtSnwLdIO = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGMaxOpePosSRq
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_Setting_Control_Cmd.Ipdu.PLGMaxOpePosSRq = (*(uint8 *)SigValue);

}

FUNC(void, COM_PUBLIC_CODE) Com_SendSigPLGMaxOpePosSRqSt
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    TxIpduPLG_Setting_Control_Cmd.Ipdu.PLGMaxOpePosSRqSt = (*(uint8 *)SigValue);

}


/*******************************************************************************
*   for Com_ReceiveSignal 
*******************************************************************************/
FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R1
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R1;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R101
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R101;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R102
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R102;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R103
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R103;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R104
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R104;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R105
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R105;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R106
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R106;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R107
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R1.Ipdu.New_Signal_111R107;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R2
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R2;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R204
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R204;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R203
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R203;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R202
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R202;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R201
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R201;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R205
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R205;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R206
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R206;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R207
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R2.Ipdu.New_Signal_111R207;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R3
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R3;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R301
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R301;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R302
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R302;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R303
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R303;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R304
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R304;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R305
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R305;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R306
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R306;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R307
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R3.Ipdu.New_Signal_111R307;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R4
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R4.Ipdu.New_Signal_111R4;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R5
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R5.Ipdu.New_Signal_111R5;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R6
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R6.Ipdu.New_Signal_111R6;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R7
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R7.Ipdu.New_Signal_111R7;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R8
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R8.Ipdu.New_Signal_111R8;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R9
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R9.Ipdu.New_Signal_111R9;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R10
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R10.Ipdu.New_Signal_111R10;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R11
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R11.Ipdu.New_Signal_111R11;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R12
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R12.Ipdu.New_Signal_111R12;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R13
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R13.Ipdu.New_Signal_111R13;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R14
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R14.Ipdu.New_Signal_111R14;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R15
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R15.Ipdu.New_Signal_111R15;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R16
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R16.Ipdu.New_Signal_111R16;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R17
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R17.Ipdu.New_Signal_111R17;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R18
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R18.Ipdu.New_Signal_111R18;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R19
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R19.Ipdu.New_Signal_111R19;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R20
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R20.Ipdu.New_Signal_111R20;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R21
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R21.Ipdu.New_Signal_111R21;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R22
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R22.Ipdu.New_Signal_111R22;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R23
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R23.Ipdu.New_Signal_111R23;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R24
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R24.Ipdu.New_Signal_111R24;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R25
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R25.Ipdu.New_Signal_111R25;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R26
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R26.Ipdu.New_Signal_111R26;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R27
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R27.Ipdu.New_Signal_111R27;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R28
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R28.Ipdu.New_Signal_111R28;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R29
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R29.Ipdu.New_Signal_111R29;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R30
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R30.Ipdu.New_Signal_111R30;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R31
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R31.Ipdu.New_Signal_111R31;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R32
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R32.Ipdu.New_Signal_111R32;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R33
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R33.Ipdu.New_Signal_111R33;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R34
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R34.Ipdu.New_Signal_111R34;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R35
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R35.Ipdu.New_Signal_111R35;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R36
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R36.Ipdu.New_Signal_111R36;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R37
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R37.Ipdu.New_Signal_111R37;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R38
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R38.Ipdu.New_Signal_111R38;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R39
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R39.Ipdu.New_Signal_111R39;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R40
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R40.Ipdu.New_Signal_111R40;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R41
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R41.Ipdu.New_Signal_111R41;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R42
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R42.Ipdu.New_Signal_111R42;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R43
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R43.Ipdu.New_Signal_111R43;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R44
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R44.Ipdu.New_Signal_111R44;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R45
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R45.Ipdu.New_Signal_111R45;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R46
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R46.Ipdu.New_Signal_111R46;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R47
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R47.Ipdu.New_Signal_111R47;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R48
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R48.Ipdu.New_Signal_111R48;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R49
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R49.Ipdu.New_Signal_111R49;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R50
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R50.Ipdu.New_Signal_111R50;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R51
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R51.Ipdu.New_Signal_111R51;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R52
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R52.Ipdu.New_Signal_111R52;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R53
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R53.Ipdu.New_Signal_111R53;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R54
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R54.Ipdu.New_Signal_111R54;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R55
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R55.Ipdu.New_Signal_111R55;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigNew_Signal_111R56
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduNew_Message_R56.Ipdu.New_Signal_111R56;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngSpdStat
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.EngSpdStat;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngIdlAtv
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.EngIdlAtv;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngRunAtv
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.EngRunAtv;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngSpd
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint16 *)SigValue) = (((uint32) RxIpduPPEI_Engine_General_Status_1.Ipdu.EngSpd_Byte1) << 8)
                            |(((uint32) RxIpduPPEI_Engine_General_Status_1.Ipdu.EngSpd_Byte0) << 0);
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigDrvThrottlOvrrdDet
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.DrvThrottlOvrrdDet;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigCrsCntEnbld
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.CrsCntEnbld;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigCrsCntAtv
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.CrsCntAtv;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigAccActPosV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.AccActPosV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigAccActPos
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.AccActPos;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPT_BrkPedDscrtInpStat
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.PT_BrkPedDscrtInpStat;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPT_BrkPedDscrtInpStatV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.PT_BrkPedDscrtInpStatV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngRelSta
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.EngRelSta;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPPEI_Eng_Gen_Sta_1_ACR
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.PPEI_Eng_Gen_Sta_1_ACR;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigEngGenSta_1Cksm
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Engine_General_Status_1.Ipdu.EngGenSta_1Cksm;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVehOdo
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint32 *)SigValue) = (((uint32) RxIpduVehicle_Odometer.Ipdu.VehOdo_Byte3) << 24)
                            |(((uint32) RxIpduVehicle_Odometer.Ipdu.VehOdo_Byte2) << 16)
                            |(((uint32) RxIpduVehicle_Odometer.Ipdu.VehOdo_Byte1) << 8)
                            |(((uint32) RxIpduVehicle_Odometer.Ipdu.VehOdo_Byte0) << 0);
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVehOdoV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduVehicle_Odometer.Ipdu.VehOdoV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigDoorLockCmdIn
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.DoorLockCmdIn;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigFobCmdIn
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.FobCmdIn;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSKeyreminderUnlock
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.PEPSKeyreminderUnlock;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSSATOIndicationLEDControl
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.PEPSSATOIndicationLEDControl;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigInEntCmdIn
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.InEntCmdIn;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSWELReq
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_Door_Lock_Command.Ipdu.PEPSWELReq;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigBrkProcInPrgrsIO
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.BrkProcInPrgrsIO;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigABSIO
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.ABSIO;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigAnt_Bra_and_Tc_Sta_HSRC
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.Ant_Bra_and_Tc_Sta_HSRC;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVSESysOffIO
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VSESysOffIO;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVehSpdAvgDrvnRd
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint16 *)SigValue) = (((uint32) RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VehSpdAvgDrvnRd_Byte2) << 11)
                            |(((uint32) RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VehSpdAvgDrvnRd_Byte1) << 3)
                            |(((uint32) RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VehSpdAvgDrvnRd_Byte0) << 0);
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigAnt_Bra_and_Tc_Sta_HSCKsm
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.Ant_Bra_and_Tc_Sta_HSCKsm;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVehStabEnhmntStat
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VehStabEnhmntStat;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigVehSpdAvgDrvnRdV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAatilock_Brake_and_TC_Status_HS.Ipdu.VehSpdAvgDrvnRdV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigIgnKyPstn
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Platform_General_Status.Ipdu.IgnKyPstn;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigIgnKyInstAtv
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Platform_General_Status.Ipdu.IgnKyInstAtv;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPrkBrkSwAtv
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Platform_General_Status.Ipdu.PrkBrkSwAtv;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigTrnsRvsSwSt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPPEI_Platform_General_Status.Ipdu.TrnsRvsSwSt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigThCompTorReqV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAC_Torque_Status.Ipdu.ThCompTorReqV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigThCompWorReq
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAC_Torque_Status.Ipdu.ThCompWorReq;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigThCompTorReq
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduAC_Torque_Status.Ipdu.ThCompTorReq;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSAuthnSt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSAuthnSt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigSysPowModeV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.SysPowModeV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigSysPowMode
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.SysPowMode;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigBrkPedSwSt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.BrkPedSwSt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigGearInOnParPos
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.GearInOnParPos;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSStrtrR1ySt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSStrtrR1ySt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSIG2R1ySt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSIG2R1ySt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSIG1R1ySt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSIG1R1ySt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSACCR1ySt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSACCR1ySt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigSSBSW2St
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.SSBSW2St;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigSSBSw1St
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.SSBSw1St;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSIG1R1yStV
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSIG1R1yStV;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSWELQuitReason
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSWELQuitReason;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSSATOQuitReason
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSSATOQuitReason;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSGenStaRC
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSGenStaRC;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSLmSt
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSLmSt;
}

FUNC(void, COM_PUBLIC_CODE) Com_ReceiveSigPEPSGenStaCksm
(
    P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue 
)
{
    (*(uint8 *)SigValue) = RxIpduPEPS_General_Status.Ipdu.PEPSGenStaCksm;
}


#define COM_STOP_SEC_PUBLIC_CODE 
#include "MemMap.h"

/*******************************************************************************
*   Signal Interface Structure 
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

#if (COM_TXSIGNUM >= 1u)
CONST(Com_SendSignalType, COM_CONFIG_CONST) Com_SendSignalTable[COM_TXSIGNUM] =
{
    &Com_SendSigNew_Signal_21,
    &Com_SendSigNew_Signal_211,
    &Com_SendSigNew_Signal_212,
    &Com_SendSigNew_Signal_213,
    &Com_SendSigNew_Signal_214,
    &Com_SendSigNew_Signal_215,
    &Com_SendSigNew_Signal_216,
    &Com_SendSigNew_Signal_217,
    &Com_SendSigNew_Signal_22,
    &Com_SendSigNew_Signal_221,
    &Com_SendSigNew_Signal_222,
    &Com_SendSigNew_Signal_223,
    &Com_SendSigNew_Signal_224,
    &Com_SendSigNew_Signal_225,
    &Com_SendSigNew_Signal_226,
    &Com_SendSigNew_Signal_227,
    &Com_SendSigNew_Signal_23,
    &Com_SendSigNew_Signal_231,
    &Com_SendSigNew_Signal_232,
    &Com_SendSigNew_Signal_233,
    &Com_SendSigNew_Signal_234,
    &Com_SendSigNew_Signal_235,
    &Com_SendSigNew_Signal_236,
    &Com_SendSigNew_Signal_237,
    &Com_SendSigNew_Signal_24,
    &Com_SendSigNew_Signal_241,
    &Com_SendSigNew_Signal_242,
    &Com_SendSigNew_Signal_243,
    &Com_SendSigNew_Signal_244,
    &Com_SendSigNew_Signal_245,
    &Com_SendSigNew_Signal_246,
    &Com_SendSigNew_Signal_247,
    &Com_SendSigNew_Signal_25,
    &Com_SendSigNew_Signal_251,
    &Com_SendSigNew_Signal_252,
    &Com_SendSigNew_Signal_253,
    &Com_SendSigNew_Signal_254,
    &Com_SendSigNew_Signal_255,
    &Com_SendSigNew_Signal_256,
    &Com_SendSigNew_Signal_257,
    &Com_SendSigNew_Signal_26,
    &Com_SendSigNew_Signal_261,
    &Com_SendSigNew_Signal_262,
    &Com_SendSigNew_Signal_263,
    &Com_SendSigNew_Signal_264,
    &Com_SendSigNew_Signal_265,
    &Com_SendSigNew_Signal_266,
    &Com_SendSigNew_Signal_267,
    &Com_SendSigNew_Signal_27,
    &Com_SendSigNew_Signal_271,
    &Com_SendSigNew_Signal_272,
    &Com_SendSigNew_Signal_273,
    &Com_SendSigNew_Signal_274,
    &Com_SendSigNew_Signal_275,
    &Com_SendSigNew_Signal_276,
    &Com_SendSigNew_Signal_277,
    &Com_SendSigNew_Signal_28,
    &Com_SendSigNew_Signal_281,
    &Com_SendSigNew_Signal_282,
    &Com_SendSigNew_Signal_283,
    &Com_SendSigNew_Signal_284,
    &Com_SendSigNew_Signal_285,
    &Com_SendSigNew_Signal_286,
    &Com_SendSigNew_Signal_287,
    &Com_SendSigNew_Signal_29,
    &Com_SendSigNew_Signal_291,
    &Com_SendSigNew_Signal_292,
    &Com_SendSigNew_Signal_293,
    &Com_SendSigNew_Signal_294,
    &Com_SendSigNew_Signal_295,
    &Com_SendSigNew_Signal_296,
    &Com_SendSigNew_Signal_297,
    &Com_SendSigNew_Signal_30,
    &Com_SendSigNew_Signal_301,
    &Com_SendSigNew_Signal_302,
    &Com_SendSigNew_Signal_303,
    &Com_SendSigNew_Signal_304,
    &Com_SendSigNew_Signal_305,
    &Com_SendSigNew_Signal_306,
    &Com_SendSigNew_Signal_307,
    &Com_SendSigNew_Signal_31,
    &Com_SendSigNew_Signal_311,
    &Com_SendSigNew_Signal_312,
    &Com_SendSigNew_Signal_313,
    &Com_SendSigNew_Signal_314,
    &Com_SendSigNew_Signal_315,
    &Com_SendSigNew_Signal_316,
    &Com_SendSigNew_Signal_317,
    &Com_SendSigNew_Signal_32,
    &Com_SendSigNew_Signal_321,
    &Com_SendSigNew_Signal_322,
    &Com_SendSigNew_Signal_323,
    &Com_SendSigNew_Signal_324,
    &Com_SendSigNew_Signal_325,
    &Com_SendSigNew_Signal_326,
    &Com_SendSigNew_Signal_327,
    &Com_SendSigNew_Signal_33,
    &Com_SendSigNew_Signal_331,
    &Com_SendSigNew_Signal_332,
    &Com_SendSigNew_Signal_333,
    &Com_SendSigNew_Signal_334,
    &Com_SendSigNew_Signal_335,
    &Com_SendSigNew_Signal_336,
    &Com_SendSigNew_Signal_337,
    &Com_SendSigNew_Signal_34,
    &Com_SendSigNew_Signal_341,
    &Com_SendSigNew_Signal_342,
    &Com_SendSigNew_Signal_343,
    &Com_SendSigNew_Signal_344,
    &Com_SendSigNew_Signal_345,
    &Com_SendSigNew_Signal_346,
    &Com_SendSigNew_Signal_347,
    &Com_SendSigPLGSysMSt,
    &Com_SendSigPLGMaxOpePosSSt,
    &Com_SendSigPLGCrtOpePos,
    &Com_SendSigPLGCrtOpePosV,
    &Com_SendSigPLGPwOptCmdAct,
    &Com_SendSigPLGLmSt,
    &Com_SendSigPLGLtMSt,
    &Com_SendSigPLGFlurAnls,
    &Com_SendSigPLGLtPrySglSwSt,
    &Com_SendSigPLGLtScdSglSwSt,
    &Com_SendSigPLGLtPwSglSwSt,
    &Com_SendSigPLGLtRstSglSwSt,
    &Com_SendSigPLGLtSnwLdIO,
    &Com_SendSigPLGMaxOpePosSRq,
    &Com_SendSigPLGMaxOpePosSRqSt,
};
#endif

#if (COM_RXIPDUNUM >= 1u)
CONST(Com_ReceiveSignalType, COM_CONFIG_CONST) Com_ReceiveSignalTable[COM_RXSIGNUM] =
{
    &Com_ReceiveSigNew_Signal_111R1,
    &Com_ReceiveSigNew_Signal_111R101,
    &Com_ReceiveSigNew_Signal_111R102,
    &Com_ReceiveSigNew_Signal_111R103,
    &Com_ReceiveSigNew_Signal_111R104,
    &Com_ReceiveSigNew_Signal_111R105,
    &Com_ReceiveSigNew_Signal_111R106,
    &Com_ReceiveSigNew_Signal_111R107,
    &Com_ReceiveSigNew_Signal_111R2,
    &Com_ReceiveSigNew_Signal_111R204,
    &Com_ReceiveSigNew_Signal_111R203,
    &Com_ReceiveSigNew_Signal_111R202,
    &Com_ReceiveSigNew_Signal_111R201,
    &Com_ReceiveSigNew_Signal_111R205,
    &Com_ReceiveSigNew_Signal_111R206,
    &Com_ReceiveSigNew_Signal_111R207,
    &Com_ReceiveSigNew_Signal_111R3,
    &Com_ReceiveSigNew_Signal_111R301,
    &Com_ReceiveSigNew_Signal_111R302,
    &Com_ReceiveSigNew_Signal_111R303,
    &Com_ReceiveSigNew_Signal_111R304,
    &Com_ReceiveSigNew_Signal_111R305,
    &Com_ReceiveSigNew_Signal_111R306,
    &Com_ReceiveSigNew_Signal_111R307,
    &Com_ReceiveSigNew_Signal_111R4,
    &Com_ReceiveSigNew_Signal_111R5,
    &Com_ReceiveSigNew_Signal_111R6,
    &Com_ReceiveSigNew_Signal_111R7,
    &Com_ReceiveSigNew_Signal_111R8,
    &Com_ReceiveSigNew_Signal_111R9,
    &Com_ReceiveSigNew_Signal_111R10,
    &Com_ReceiveSigNew_Signal_111R11,
    &Com_ReceiveSigNew_Signal_111R12,
    &Com_ReceiveSigNew_Signal_111R13,
    &Com_ReceiveSigNew_Signal_111R14,
    &Com_ReceiveSigNew_Signal_111R15,
    &Com_ReceiveSigNew_Signal_111R16,
    &Com_ReceiveSigNew_Signal_111R17,
    &Com_ReceiveSigNew_Signal_111R18,
    &Com_ReceiveSigNew_Signal_111R19,
    &Com_ReceiveSigNew_Signal_111R20,
    &Com_ReceiveSigNew_Signal_111R21,
    &Com_ReceiveSigNew_Signal_111R22,
    &Com_ReceiveSigNew_Signal_111R23,
    &Com_ReceiveSigNew_Signal_111R24,
    &Com_ReceiveSigNew_Signal_111R25,
    &Com_ReceiveSigNew_Signal_111R26,
    &Com_ReceiveSigNew_Signal_111R27,
    &Com_ReceiveSigNew_Signal_111R28,
    &Com_ReceiveSigNew_Signal_111R29,
    &Com_ReceiveSigNew_Signal_111R30,
    &Com_ReceiveSigNew_Signal_111R31,
    &Com_ReceiveSigNew_Signal_111R32,
    &Com_ReceiveSigNew_Signal_111R33,
    &Com_ReceiveSigNew_Signal_111R34,
    &Com_ReceiveSigNew_Signal_111R35,
    &Com_ReceiveSigNew_Signal_111R36,
    &Com_ReceiveSigNew_Signal_111R37,
    &Com_ReceiveSigNew_Signal_111R38,
    &Com_ReceiveSigNew_Signal_111R39,
    &Com_ReceiveSigNew_Signal_111R40,
    &Com_ReceiveSigNew_Signal_111R41,
    &Com_ReceiveSigNew_Signal_111R42,
    &Com_ReceiveSigNew_Signal_111R43,
    &Com_ReceiveSigNew_Signal_111R44,
    &Com_ReceiveSigNew_Signal_111R45,
    &Com_ReceiveSigNew_Signal_111R46,
    &Com_ReceiveSigNew_Signal_111R47,
    &Com_ReceiveSigNew_Signal_111R48,
    &Com_ReceiveSigNew_Signal_111R49,
    &Com_ReceiveSigNew_Signal_111R50,
    &Com_ReceiveSigNew_Signal_111R51,
    &Com_ReceiveSigNew_Signal_111R52,
    &Com_ReceiveSigNew_Signal_111R53,
    &Com_ReceiveSigNew_Signal_111R54,
    &Com_ReceiveSigNew_Signal_111R55,
    &Com_ReceiveSigNew_Signal_111R56,
    &Com_ReceiveSigEngSpdStat,
    &Com_ReceiveSigEngIdlAtv,
    &Com_ReceiveSigEngRunAtv,
    &Com_ReceiveSigEngSpd,
    &Com_ReceiveSigDrvThrottlOvrrdDet,
    &Com_ReceiveSigCrsCntEnbld,
    &Com_ReceiveSigCrsCntAtv,
    &Com_ReceiveSigAccActPosV,
    &Com_ReceiveSigAccActPos,
    &Com_ReceiveSigPT_BrkPedDscrtInpStat,
    &Com_ReceiveSigPT_BrkPedDscrtInpStatV,
    &Com_ReceiveSigEngRelSta,
    &Com_ReceiveSigPPEI_Eng_Gen_Sta_1_ACR,
    &Com_ReceiveSigEngGenSta_1Cksm,
    &Com_ReceiveSigVehOdo,
    &Com_ReceiveSigVehOdoV,
    &Com_ReceiveSigDoorLockCmdIn,
    &Com_ReceiveSigFobCmdIn,
    &Com_ReceiveSigPEPSKeyreminderUnlock,
    &Com_ReceiveSigPEPSSATOIndicationLEDControl,
    &Com_ReceiveSigInEntCmdIn,
    &Com_ReceiveSigPEPSWELReq,
    &Com_ReceiveSigBrkProcInPrgrsIO,
    &Com_ReceiveSigABSIO,
    &Com_ReceiveSigAnt_Bra_and_Tc_Sta_HSRC,
    &Com_ReceiveSigVSESysOffIO,
    &Com_ReceiveSigVehSpdAvgDrvnRd,
    &Com_ReceiveSigAnt_Bra_and_Tc_Sta_HSCKsm,
    &Com_ReceiveSigVehStabEnhmntStat,
    &Com_ReceiveSigVehSpdAvgDrvnRdV,
    &Com_ReceiveSigIgnKyPstn,
    &Com_ReceiveSigIgnKyInstAtv,
    &Com_ReceiveSigPrkBrkSwAtv,
    &Com_ReceiveSigTrnsRvsSwSt,
    &Com_ReceiveSigThCompTorReqV,
    &Com_ReceiveSigThCompWorReq,
    &Com_ReceiveSigThCompTorReq,
    &Com_ReceiveSigPEPSAuthnSt,
    &Com_ReceiveSigSysPowModeV,
    &Com_ReceiveSigSysPowMode,
    &Com_ReceiveSigBrkPedSwSt,
    &Com_ReceiveSigGearInOnParPos,
    &Com_ReceiveSigPEPSStrtrR1ySt,
    &Com_ReceiveSigPEPSIG2R1ySt,
    &Com_ReceiveSigPEPSIG1R1ySt,
    &Com_ReceiveSigPEPSACCR1ySt,
    &Com_ReceiveSigSSBSW2St,
    &Com_ReceiveSigSSBSw1St,
    &Com_ReceiveSigPEPSIG1R1yStV,
    &Com_ReceiveSigPEPSWELQuitReason,
    &Com_ReceiveSigPEPSSATOQuitReason,
    &Com_ReceiveSigPEPSGenStaRC,
    &Com_ReceiveSigPEPSLmSt,
    &Com_ReceiveSigPEPSGenStaCksm,
};
#endif

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
