/*
 * fml_uart.h
 *
 *  Created on: 2021Äê5ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef FML_UART_FML_UART_H_
#define FML_UART_FML_UART_H_
#include "Cpu.h"
#include "ff.h"
#define CMD_BUFF_LEN (100) //shell uart data length

extern QueueHandle_t uartLogQueue;
extern SemaphoreHandle_t configQueue;
extern QueueHandle_t taskLogQueue;
extern void uart_printf_char_fml_api(uint8_t source,const char *function,const char *format);
void uart_log_printf_fml(const char *format, ...);
extern void uart_log_printf_isr_fml(const char *format, ...);
void put_hex_fml( uint8_t hex_data ,uint8_t *p);

void uart_printf_data_fml_api(uint8_t source,uint8_t *data,uint8_t len,const char *function,char *format);

#define UARTTASKPRINT 1
#define UARTISRPRINT  false

typedef enum { shelluartWorking = 1, shelluartNotWork = !shelluartWorking} shellUartWorkTyp;
typedef enum { shellCmdEnable = 1, shellCmdDisable = !shellCmdEnable} shellCmdTyp;

typedef struct stSHELL{
    shellUartWorkTyp uartWork;
    shellCmdTyp shellCmd;
    uint8_t recbuf[CMD_BUFF_LEN];
    uint8_t rCnt;
    uint8_t recTimeCnt;  //use for judge one package whether rec done. use location timer interrupt.
};

//setVIN 1234567
//idDef:VIN
//cmd:set
//data:1234567
typedef struct stAnalysisCmd
{
    char idDef[15];
    char cmd[4]; //get or set
    char data[50];
    char *reserve;
};

/**********************log infomation struct*********************************/
typedef struct
{
    uint16_t year;      /*!< Year       */
    uint16_t month;     /*!< Month      */
    uint16_t day;       /*!< Day        */
    uint16_t hour;      /*!< Hour       */
    uint16_t minutes;   /*!< Minutes    */
    uint8_t seconds;    /*!< Seconds    */
}rtcDateTime;  //this struct same as rtc_timedate_t,define in rtc_driver.h

typedef enum
{
    LOGInfo = 0,
    CommunicatErr, //communication error
    ValidatiErr, // data check is error
    FrameErr,//data frame is error(data incomplete)
    SigReciveErr,// signal receive is error
    SigSendErr,//signal send is error
    FlashReadErr, //oprate flash read is error
    FlashWriteErr,//oprate flash write is error
    McuWaked,  //Mcu waked by source
    McuSleep  //Mcu enter sleep mode
} eventType;

typedef struct stTask_log
{
    rtcDateTime logTime;
    eventType logEvent;
    char fileName[100];
    char functionName[20];
    char inifo[40];  //record main infomation
    void *reserve;
};


typedef struct stUploadTime
{
    uint32_t timeUploadCnt;
    uint8_t upUploadEn;
};
extern struct stUploadTime upLoadTime;
/**************************end log infomation struct***********************************************/
extern struct stSHELL shellCmdData;
extern SemaphoreHandle_t  fatfsInitQueue;
extern void lpuart1_recCallback(void *driverState, uart_event_t event, void *userData);
extern void shell_uart_config_init(void);

/**************************************************************************************************************/

/***********************uart soc start****************************************/
void uart_soc_config_init(void);

#define ONE_FRAME_SHORTEST_LEN (7)
#define UART_SOC_HEAD1 (0x5A)
#define UART_SOC_HEAD2 (0xA5)

typedef enum
{
    uartSocSetCmd = 0x01,
    uartSocgetCmd = 0x02,
    uartSocSetGetEnableCmd = 0x03,
    uartSocUploadCmd = 0x04
}uartSocCmdType;

typedef enum
{
    uartSocParaGetSet       = 0x01,
    uartSocParaVMSPN        = 0x02,
    uartSocParaSSID         = 0x03,
    uartSocParaECUMD        = 0x04,
    uartSocParaECUSND       = 0x05,
    uartSocParaVIN          = 0x06,
    uartSocParaSSECUHWN     = 0x07,
    uartSocParaSSECUHWVN    = 0x08,
    uartSocParaSSECUSWN     = 0x09,
    uartSocParaSSECUSWVN    = 0x0A,
    uartSocParaRSCOTSN      = 0x0B,
    uartSocParaEDID         = 0x0C,
    uartSocParaLog          = 0x0D
}uartSocParaType;

typedef enum
{
    head1Pos    = 0,
    head2Pos    = 1,
    lengthPos   = 2,
    cmdPos      = 3,
    frameNumPos = 4,
    paraPos     = 5,
    dataPos     = 6
}protocolFiledPos;

typedef enum
{
    readBufferEnable = 1,
    readBufferDisable = !readBufferEnable
}readBuffLockType;

typedef struct uartSocReadBuffType
{
    readBuffLockType readBuffFlag;
    uint8_t readBuff[270];
    uint16_t usefullDataCnt;
};

typedef struct stFaultType
{
    uint8_t faultCode;
    char faultReason[500];
};
extern struct stFaultType HardFaultMsg;

extern FRESULT saveFaultFile(struct stFaultType *faultMsg);


/***********************uart soc end****************************************/
#endif /* FML_UART_FML_UART_H_ */
