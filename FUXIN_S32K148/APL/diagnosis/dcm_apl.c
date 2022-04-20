/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Dcm.c
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
* Include files
********************************************************************************/
#include "Dcm.h"
#if(DCM_SERVICE_28_ENABLED == STD_ON)
#include "Com.h"
#include "OsekNm.h"
#endif
#include <stdint.h>

/*******************************************************************************
* Macros and Typedef
********************************************************************************/

#if(DCM_SERVICE_85_ENABLED == STD_ON)
uint8 gDTCSwitch;
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#define W8(addr, value)              (*((uint8 *) (addr)) = (value))
#define R8(addr)                     (*((uint8 *) (addr)))
#endif

#if(ISO_15031_5 == STD_ON)
/* For 0x01*/
/* For 0x02*/
/* For 0x06*/
/* For 0x09*/
#endif

/* For 0x22*/
#define ReadHandle_0x2001    (0U)
#define ReadHandle_0xF101    (1U)
#define ReadHandle_0xF100    (2U)
#define ReadHandle_0xF112    (3U)
#define ReadHandle_0xF150    (4U)
#define ReadHandle_0xF18A    (5U)
#define ReadHandle_0xF187    (6U)
#define ReadHandle_0xF18B    (7U)
#define ReadHandle_0xF18C    (8U)
#define ReadHandle_0xF190    (9U)
#define ReadHandle_0xF198    (10U)
#define ReadHandle_0xF192    (11U)
#define ReadHandle_0xF193    (12U)
#define ReadHandle_0xF194    (13U)
#define ReadHandle_0xF195    (14U)
#define ReadHandle_0xF19D    (15U)

/* For 0x24*/

/* For 0x28 */
#define Dcm_EnRx_EnTx                (0U)
#define Dcm_DisRx_EnTx               (1U)
#define Dcm_EnRx_DisTx               (2U)
#define Dcm_DisRx_DisTx              (3U)


/* For 0x2A*/

/* For 0x2C*/

/* For 0x2E*/
#define WriteHandle_0x2001    (0U)
#define WriteHandle_0xF190    (1U)
#define WriteHandle_0xF198    (2U)
#define WriteHandle_0xF19D    (3U)

/* For 0x2F*/

/* For 0x31*/
#define RoutineHandle_0x0203    (0U)
#define RoutineHandle_0xFF02    (1U)

extern uint8_t dig2EServiceActive;

/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
#if(ISO_15031_5 == STD_ON)
/* For 0x02*/
/* For 0x03*/
/* For 0x04*/
/* For 0x07*/
/* For 0x08*/
/* For 0x0A*/
#endif

static uint8 DTCStatusAvailabilityMask = 0x9U;
uint32 SupportedDTCGroup = 0x00U;
 uint32 SupportedDTC[NUM_OF_DTC] =
{
    0xE20D00U,
    0xC0738AU,
    0xC11187U,
    0xC12187U,
    0xC12287U,
    0xC14087U,
    0xC16487U,
    0xC23587U,
    0xC13987U,
    0xC24387U,
    0xC20887U,
    0xC23087U,
    0xC15687U,
    0xC16087U,
    0xC15787U,
    0xC23287U,
    0xC18287U,
    0xC21387U,
    0xC15987U,
    0xC13187U,
    0xC14687U,
    0xC15587U,
    0xC14587U,
    0xC24987U,
    0xC18087U,
    0xF00317U,
    0xF00316U,
    0x927213U,
    0x911911U,
    0x911912U,
    0x910311U,
    0x910312U,
    0x910313U,
    0x905313U,
    0x910111U,
    0x910112U,
    0x910113U,
    0x905113U,
    0x910411U,
    0x910412U,
    0x910413U,
    0x910543U,
    0x910211U,
    0x910212U,
    0x910213U,
    0x905213U,
    0x910711U,
    0x910712U,
    0x910713U,
    0x905713U,
    0x910511U,
    0x910512U,
    0x910513U,
    0x905513U,
    0x910811U,
    0x910812U,
    0x910813U,
    0x905813U,
    0x910611U,
    0x910612U,
    0x910613U,
    0x905613U,
    0x929B12U,
    0x929B11U,
    0x909D12U,
    0x909D11U,
    0x929C16U,
    0x929C17U,
    0x929C02U,
    0x929C03U,
    0x929C18U,
    0x929C07U,
    0X923018U,
    0x923118U,
    0x923218U,
    0x92330CU,
    0x923418U,
    0x923518U,
    0x923618U,
    0x923718U,
    0x923887U,
    0x923913U,
    0x923911U,
    0x923912U,
    0x923A13U,
    0x923A11U,
    0x923A12U,
    0x923B13U,
    0x923B11U,
    0x923B12U,
    0x923C87U,
    0x923D87U,
};
uint8 DTCStatus[NUM_OF_DTC] =
{
    0x08U,0x08U,0x08U,0x08U,0x08U
};
uint8 DATA_0xF18A[7]={'P','N','0','0','2','6','4'};
uint8 DATA_0xF187[10] = {'3','B','1','9','2','5','4','0','2','C'};
uint8 DATA_0xF18B[4]={'B',0x20,9,1};
uint8 DATA_0xF18C[8]={'C','1','0','0','2','6','4','8'};
uint8 DATA_0xF192[16]={'A','0','D','E','S','0','H','3','B','1','9','2','5','4','0','2'};
uint8 DATA_0xF193[4]={'A','2','0','0'};
uint8 DATA_0xF194[16]={'A','0','D','E','S','0','S','3','B','1','9','2','6','4','0','2'};
uint8 DATA_0xF195[4]={'5','1','9','5'};
uint8 DATA_0x2001[4]={'1',0,0,0};
uint8 DATA_0xF19D[4]={'D',0,0,0};
uint8 DATA_0xF190[17]={'0'};//={'L','S','G','J','A','2','U','2','C','5','0','1','2','4','0','5','9'};
uint8 DATA_0xF198[16]={'8'};//={'1','1','0','0','2','2','3','3','4','4','5','5','9','9','8','8'};
uint8 DATA_0xF101[4]={1,10,12,13};
uint8 DATA_0xF100[1]={8};
uint8 DATA_0xF112[3]={10,1,20};
uint8 DATA_0xF150[12]={10,11,12,13,14,7,1,2,3,4,5,6};

static uint8 ApplicationSoftwareIdentification[32] =
{
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f
};

/* Below codes are demo for 0x27, all of them can be deleted */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
static uint8 MagicSeed = 0x0C;
#endif

#if(DCM_SERVICE_28_ENABLED == STD_ON)
/* if Hirain Com& Nm are used, don't change below codes */
static uint8 Dcm_NmMessage_Status = Dcm_EnRx_EnTx;
static uint8 Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
#endif


/***************************************************************************
* Global Function Implementation
****************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
/****************************************************************************
* Name         :App_DiagnosticActive 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :N/A  
* Return code  :N/A  
* Description  :Check is it possible to enable Dcm module.  
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) App_DiagnosticActive(void)
{
     return E_OK;
}
#endif 

#if(ISO_15031_5 == STD_ON)
#if(DCM_SERVICE_01_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_03_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_04_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_06_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_07_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_08_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_09_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_0A_ENABLED == STD_ON)
#endif
#endif 

/* 0x10 */
#if(DCM_SERVICE_10_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_Default 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*     Dcm 收到 0x10 01/81 服务请求时调用
******************************************************************************/
FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
//        Printf("%d\r\n",__LINE__);
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
//        Printf("%d\r\n",__LINE__);
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_DefaultPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;
    
    if(Result == E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT); 
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE; 
        Clr_S3_Server_Timer(); 
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* Reset the CommunicationControl Flags */
        #if(DCM_SERVICE_28_ENABLED == STD_ON)
        switch(Dcm_NmMessage_Status)
        {
            case Dcm_DisRx_DisTx:
            case Dcm_DisRx_EnTx:
                CanNm_Start(0); /* if neceesary, change Nm Channel Number */
                break;
      
            case Dcm_EnRx_DisTx:
                CanNm_Talk(0);  /* if neceesary, change Nm Channel Number */
                break;
    
            default: 
                break;
        }
        Dcm_NmMessage_Status = Dcm_EnRx_EnTx;
        
        switch(Dcm_ComMessage_Status)
        {
            case Dcm_DisRx_DisTx:
                 Com_TxStart();
                 Com_RxStart();
                 break;
        
            case Dcm_DisRx_EnTx:
                 Com_RxStart();
                 break;
        
            case Dcm_EnRx_DisTx:
                 Com_TxStart();
                 break;
        
            default:
                 break;
        }
        Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_Programming 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_ProgrammingPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_PROGRAMMING);  
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;  
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);  
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_Extended_Diagnostic 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_Extended_DiagnosticPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);  
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}
#endif

/* 0x11 */
#if(DCM_SERVICE_11_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Hard_Reset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :Hard_Reset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_Hard_Reset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_ResetPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_KeyOffOnReset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :KeyOffOnReset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_KeyOffOnReset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_KeyOffOnReset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_KeyOffOnReset_ResetPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_Soft_Reset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :Soft_Reset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Soft_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_Soft_Reset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_Soft_Reset_ResetPost(Std_ReturnType Result)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
#endif

/* 0x14 */
#if(DCM_SERVICE_14_ENABLED == STD_ON)
/************************************************************************
* Name         :App_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;

    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_1], pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3]);
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if(Dtc == SupportedDTC[i])
        {
            i = NUM_OF_DTC;                                
        }
        else
        {
            if(i == (NUM_OF_DTC - 1U))
            {
                if((Dtc != 0xffffff) && (Dtc != SupportedDTCGroup))
                {
                    error = 1U;
                    DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                }
                else
                {
                }
            }
            else
            {
            }
        }
    }
    if(error == 0U)
    {
        for(i = 0U; i < NUM_OF_DTC; i++)
        {
           DTCStatus[i] = 0U;        
        }
        pMsgContext->resDataLen = 1U; 
        DsdInternal_ProcessingDone(pMsgContext);

        /* Add your code here to clear DTC information */
    }
    else
    {
    }
}
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Read0x0120 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x2001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x2001].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0x2001[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0120].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0120].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF101 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF101(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF101].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF101[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF101].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF101].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF102 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF100(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF100].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF100[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF102].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF102].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF17F 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF112(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //112
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF112].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF112[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF17F].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF17F].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF180 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF150(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //150
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF150].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF150[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF181 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{//18A
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF18A[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF181].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF181].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF187 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF187[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF189 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18B(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{//18B
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18B].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF18B[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF189].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF18E 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //18C
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF18C[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF1B2 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //190
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF190[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //198
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF198[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF192
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF192(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //192
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF192].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF192[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF193
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF193(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //193
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF193[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF194
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF194(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //194
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF194].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF194[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF195
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF195(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //195
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF195[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 //19D
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF19D].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DATA_0xF19D[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1B2].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
#endif
#endif
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#endif

/* 0x23 */

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Write0x0120
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x2001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    dig2EServiceActive = 1;
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x2001].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0x2001[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF102
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    dig2EServiceActive = 1;
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF190].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF190[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    dig2EServiceActive = 1;
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF198].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF198[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Write0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    dig2EServiceActive = 1;
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF19D].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        DATA_0xF19D[i] = pMsgContext->resData[2U + i];
    }
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
#endif

/* 0x19 */
#if(DCM_SERVICE_19_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Report number of DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
//    Printf("%d\r\n",__LINE__);
    uint8 i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];

    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            counter++;
        }
        else
        {  
        }
    }

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    /* Change below data if necessary */
    /* 0x00 ISO15031-6Format,0x01 ISO14229-1Format,0x02 J1939 Format */
    pMsgContext->resData[DCM_INDEX_3] = 0x00U;
    pMsgContext->resData[DCM_INDEX_4] = (uint8)(counter >> 8U);
    pMsgContext->resData[DCM_INDEX_5] = (uint8)(counter);
    /* Always equals 6, don't change it */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_identified_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8  i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];
   
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            pMsgContext->resData[DCM_INDEX_3 + counter * 4U] = (uint8)(SupportedDTC[i] >> 16U);
            pMsgContext->resData[DCM_INDEX_4 + counter * 4U] = (uint8)(SupportedDTC[i] >> 8U);
            pMsgContext->resData[DCM_INDEX_5 + counter * 4U] = (uint8)SupportedDTC[i];
            pMsgContext->resData[DCM_INDEX_6 + counter * 4U] = DTCStatus[i]; 
            counter++;
        }
        else
        {
        }
    }

    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    pMsgContext->resDataLen = DCM_INDEX_3 + (counter * 4U);
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCSnapshortRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_snapshot(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;
    uint8 DTCSnapshotRecordNumber;
    uint8 DTCSnapshotRecordLength = 0U;

    DTCSnapshotRecordNumber = pMsgContext->reqData[DCM_INDEX_5];
    
    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3], pMsgContext->reqData[DCM_INDEX_4]);

    /* Check DTC */
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if(Dtc == SupportedDTC[i])
        {
            pMsgContext->resData[DCM_INDEX_5] = DTCStatus[i]; 
            i = NUM_OF_DTC;                                
        }
        else
        {
            if(i == (NUM_OF_DTC - 1U))
            {
                error = 1U;
                DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
            }
            else
            {
                /* Do nothing */
            }
        }
    }

    if(error == 0U)
    {
        switch(DTCSnapshotRecordNumber)
        {
            /* Add your code here. Below codes should be changed as Spec */
            case 0xFF: /*return all DTCSnapshotRecordnumber*/
            case 0x01:
                pMsgContext->resData[6] = 0x01;  /* DTCSnapshotRecordNumber #2 */
                pMsgContext->resData[7] = 0x01;  /* DTCSnapshotRecordNumberOfIdentifiers #2 */

                /*the first Identifier 0x9abc*/
                pMsgContext->resData[8] = 0x9a; /*Dataidentifier#1  byte#1(MSB)*/
                pMsgContext->resData[9] = 0xbc; /*Dataidentifier#1  byte#1(LSB)*/
                pMsgContext->resData[10] = 0x13;/*SnapshotData#1     byte#1*/    
                pMsgContext->resData[11] = 0x13;/*SnapshotData#1     byte#2*/    
                pMsgContext->resData[12] = 0x13;/*SnapshotData#1     byte#3*/            
                /* change below length according to App*/
                /* if the current DTCSnapshotRecordNumber is not available the length should 0 */
                DTCSnapshotRecordLength = 13U;
                break;

            default:
                DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                error = 1U;
                break;
        }
    }
    else
    {
        /* Do nothing */
    }
    if(error == 0U)
    {
        pMsgContext->resDataLen = DTCSnapshotRecordLength;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        
    }
}

/******************************************************************************
* Name         :App_ReportDTCExtendedDataRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_DTC_Extended_Data_Records_By_DTC_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;
    /* change below length according to App*/
    if(((pMsgContext->reqData[DCM_INDEX_5] >= 1U) && (pMsgContext->reqData[DCM_INDEX_5] <= 0x8fU)) || (pMsgContext->reqData[DCM_INDEX_5] == 0xffU))
    {
        Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3], pMsgContext->reqData[DCM_INDEX_4]);
        for(i = 0U; i < NUM_OF_DTC; i++)
        {
            if(Dtc == SupportedDTC[i])
            {
                i = NUM_OF_DTC;                                
            }
            else
            {
                if(i == (NUM_OF_DTC - 1U))
                {
                    if(Dtc != 0xffffff)
                    {
                        error = 1U;
                        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }
        }
    }
    else
    {
        error = 1U;
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }

    if(error == 0U)
    {
        pMsgContext->resDataLen = 29U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_supported_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint32 i;

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        pMsgContext->resData[DCM_INDEX_3 + i * 4U] = (uint8)(SupportedDTC[i] >> 16U);
        pMsgContext->resData[DCM_INDEX_4 + i * 4U] = (uint8)(SupportedDTC[i] >> 8U);
        pMsgContext->resData[DCM_INDEX_5 + i * 4U] = (uint8)(SupportedDTC[i]);
        pMsgContext->resData[DCM_INDEX_6 + i * 4U] = DTCStatus[i]; 
    }
    pMsgContext->resDataLen = 3U + NUM_OF_DTC * 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Fault_Memory_ReadOBDDTCOUNT 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_ReadOBDDTCOUNT(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    pMsgContext->resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Fault_Memory_ReadOBDDTCINFO 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_ReadOBDDTCINFO(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    pMsgContext->resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x27 */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Request_Seed_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
uint32 UDS_Seed_LX[2] ={0x12345678,0x12345678};
FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    UDS_Seed_LX[0] = xTaskGetTickCount();
    for(i = 0U; i < 4; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = (uint8)(UDS_Seed_LX[0]>>((3-i)*8));
    }
    pMsgContext->resDataLen = 6U;/*seed size + 2*/ 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
unsigned int SeedToKey(int64_t seed, unsigned int MASK)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    unsigned int key = 0;
    if(seed!=0)
    {
        for (int i=0; i<35; i++)
        {
            if (seed & 0x80000000)
            {
                seed = seed << 1;
                seed = seed ^ MASK;
            }
            else
            {
                seed = seed << 1;
                }
        }
        key=seed;
    }
    Printf("key:%x\r\n",key);
    return key;
}
FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here, check key according last Seed */
    uint32 UDS_Key = 0;
    unsigned int key = 0;
    UDS_Key = ((uint32)(pMsgContext->reqData[2U + 0]))<<24;
    UDS_Key = UDS_Key + (((uint32)(pMsgContext->reqData[2U + 1]))<<16);
    UDS_Key = UDS_Key + (((uint32)(pMsgContext->reqData[2U + 2]))<<8);
    UDS_Key = UDS_Key + pMsgContext->reqData[2U + 3];
    
    key = SeedToKey(UDS_Seed_LX[0], 0xEBCAFE17);
    if(key == UDS_Key)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
    }
/*
    if(temp != 0U)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
    }   */
}
/******************************************************************************
* Name         :App_Request_Seed_L2 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;

    for(i = 0U; i < 4; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = MagicSeed;
    }
    pMsgContext->resDataLen = 6U;/*seed size + 2*/ 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L2 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    uint16 temp = 0U;
    
    /* Add your code here, check key according last Seed */
    
    for(i = 0U; i < 4; i++)
    {
        /*Compare Key Demo*/
        if(pMsgContext->reqData[2U + i] != 0)
        {
            temp++;
        } 
    }

    if(temp != 0U)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L2,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L2,KEY_IS_NOT_VALID);
    }    
}
/******************************************************************************
* Name         :App_Request_Seed_L3 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L3(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;

    for(i = 0U; i < 4; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = MagicSeed;
    }
    pMsgContext->resDataLen = 6U;/*seed size + 2*/ 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L3 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L3(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    uint16 i;
    uint16 temp = 0U;
    
    /* Add your code here, check key according last Seed */
    
    for(i = 0U; i < 4; i++)
    {
        /*Compare Key Demo*/
        if(pMsgContext->reqData[2U + i] != 0)
        {
            temp++;
        } 
    }

    if(temp != 0U)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L3,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L3,KEY_IS_NOT_VALID);
    }    
}
#endif

/* 0x28 */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_EnableRxAndEnableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_EnableRxAndDisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndEnableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndDisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */
    
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_StartRoutine0x0203 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0x0203 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0x0203 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StartRoutine0xFF02 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xFF02 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xFF02 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xFF02(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xFF02].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#endif

/* 0x85 */
#if(DCM_SERVICE_85_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ON_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ON_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */

    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_OFF_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_OFF_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Printf("%s,%d\r\n",__func__,__LINE__);
    /* Add your code here */

    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x86 */
#if(DCM_SERVICE_86_ENABLED == STD_ON)
#endif
