/*
 * pwrmanage_apl.c
 *
 *  Created on: 2021Äê7ÔÂ12ÈÕ
 *      Author: Administrator
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "com_task.h"
#include "pwrmanage_apl.h"
#include "printflib.h"
#include "pubsub.h"
#include "timer_fml.h"
#include "power_manager_fml.h"

#define PWR_MANAGE_DEBUG 1

//#define ONE_HOUR_RSQ_START_TIME ((9*60+30)*1000)  //1min30seconds
//#define ONE_HOUR_RSQ_STOP_TIME ((10*60)*1000)  //60min

#define FIVE_RSQ_START_TIME ((1*60+30)*1000)  //4min30seconds
#define FIVE_RSQ_STOP_TIME ((2*60)*1000)  //5min

#define ONE_HOUR_RSQ_START_TIME ((7*60+30)*1000)  //59min30seconds
#define ONE_HOUR_RSQ_STOP_TIME ((8*60)*1000)  //60min

#define ONE_HOUR_SPI_REQUEST_TIMES (3) //one hour mode SPI timeout request times max is 3times
#define SELENT_SPI_REQUEST_TIMES (3) //one hour mode SPI timeout request times max is 3times

uint8_t socHeartBeatFlag = 0;

ps_msg_t *igsSwMsg = NULL , *antiThelMsg = NULL, *flDoorMsg = NULL, *DbcMsg = NULL,*TboxMsg = NULL;
ps_subscriber_t *igsSwSub,*antiThelSub,*FLDoorsSub,*DbcSub,*TboxWakeupSub;
ps_msg_t *socResSpiMsg = NULL,*socDoubleClickMsg = NULL,*socFiveTimeoutMsg=NULL;
ps_subscriber_t *socSpiSendSub,*socSpiRecSub,*doubleClickSub,*socFiveTimeOutSub;

socHeartBeatType socHeartValue = SocHeartDisable;
canWorkType canSleepValue = canBusNotSleep;
TboxType TboxWakeValue = TboxWakeupdisable;
doubleClickType doubleClick = DoubleClickdisable;
struct stRequestType oneHourTimeOutRequest = {
        .sendTimes = 0,
        .TimeOutResqut = {
                .TimeOutFlag = TimerCountCanWork,
                .StartTimeCount = 0,
                .CurrentCount = 0
        }
};//MCU side:one hour timeout or five minutes timeout reach,start communication to SOC by SPI interface
struct stRequestType fiveMinutesTimeOutRequest = {
        .sendTimes = 0,
        .TimeOutResqut = {
                .TimeOutFlag = TimerCountCanWork,
                .StartTimeCount = 0,
                .CurrentCount = 0
        }
};//MCU side:one hour timeout or five minutes timeout reach,start communication to SOC by SPI interface
struct stPwrManageType HuPwrmode = {
        .currentMode = NoneMode,
        .turnIntoMode = NoneMode
    };

struct stVehicleType VehicleSig = {
        .IgnSts = ignOff,
        .AntiTheftSts = antiTheftDefaut,
        .FLDoorSts = DoorDefault,
        .dbcSigSts = DbcSigDisable,
        .tboxSigSts = TboxSigDisable
};

struct stVehicleType InitialVehicleSig = {
        .AntiTheftSts = antiTheftDefaut,
        .FLDoorSts = DoorDefault
};

struct stOneHourModeTurnOutType OneHourModeTurnOut = {
        .oneHourModeTurnOutFiveCon = SocFiveMinutedisable,
        .oneHourModeTurnOutOneCon = OneHourDefault,
        .OneHourTime = {
                .TimeOutFlag = TimerCountCanWork,
                .StartTimeCount = 0,
                .CurrentCount = 0
        },
        .stAntiTheftSts = {
                .AntiTheftFlag = AntiTheftStsFlagEnable,
                .LastAntiThetfValue = Disarm,
                .CurrentAntiThetfValue = Disarm,
                .AntiThetfPeriod = 0
        },
        .stDoorSts = {
                .DoorFlag = DoorFlagEnable,
                .LastDoorValue = DoorDefault,
                .CurrentDoorfValue = DoorDefault,
                .DoorPeriod = 0
        }
};

struct stSilentModeTurnOutType SilentModeTurnOut={
        .SilentModeTurnOutClickCon = DoubleClickdisable,
        .SilentModeTurnOutSocHeartBeatCon = SocHeartEnable,
        .SilentModeTurnOutMcuFiveCon = McuFiveMinutedisable,
        .FiveMinutes = {
                .TimeOutFlag = TimerCountCanWork,
                .StartTimeCount = 0,
                .CurrentCount = 0
        },
        .stAntiTheftSts = {
                .AntiTheftFlag = AntiTheftStsFlagEnable,
                .LastAntiThetfValue = Disarm,
                .CurrentAntiThetfValue = Disarm,
                .AntiThetfPeriod = 0
        }
};

struct stPowerSaveModeTurnOutType PowerSaveModeTurnOut = {
        .stAntiTheftSts = {
                .AntiTheftFlag = AntiTheftStsFlagEnable,
                .LastAntiThetfValue = Disarm,
                .CurrentAntiThetfValue = Disarm,
                .AntiThetfPeriod = 0
        }
};

/**************************************************************/

static uint8_t getIgnSts(uint8_t value )
{
    igsSwMsg = ps_get(igsSwSub,0);
    if (igsSwMsg != NULL)
    {
        value = (uint8_t)igsSwMsg->int_val;
        if (value == ignOff)
        {
            value = ignOff;
        }
        else if (value == ignACC)
        {
            value = ignACC;
        }
        else if (value == ignON)
        {
            value = ignON;
        }
        else if (value == ignReady)
        {
            value = ignReady;
        }
        ps_unref_msg(igsSwMsg);
    }
    return value;
}

static uint8_t getAntiThelsSts(uint8_t value )
{
//    value = antiTheftDefaut;
    antiThelMsg = ps_get(antiThelSub,0);
    if (antiThelMsg != NULL)
    {
        value = (uint8_t)antiThelMsg->int_val;
        if (value == Disarm)
        {
            return Disarm;
        }
        else if (value == Arm)
        {
            return Arm;
        }
        ps_unref_msg(antiThelMsg);
    }
    return value;
}

static uint8_t getDBCSts(uint8_t value )
{
    DbcMsg = ps_get(DbcSub,0);
    if (DbcMsg != NULL)
    {
        value = (uint8_t)DbcMsg->int_val;
        if (value == DbcSigEnable) // need to mod
        {
            value = DbcSigEnable;  // need to mod
        }
        else if (value == DbcSigDisable) // need to mod
        {
            value = DbcSigDisable; // need to mod
        }
        ps_unref_msg(DbcMsg);
    }
    return value;
}

static uint8_t getTboxSts(void )
{
    uint8_t value = TboxSigDisable;
    TboxMsg = ps_get(TboxWakeupSub,0);
    if (TboxMsg != NULL)
    {
        value = (uint8_t)TboxMsg->int_val;
        if (value == TboxSigEnable) // need to mod
        {
            value = TboxSigEnable;  // need to mod
        }
        else if (value == TboxSigDisable) // need to mod
        {
            value = TboxSigDisable; // need to mod
        }
        ps_unref_msg(TboxMsg);
    }
    return value;
}

static uint8_t getFLDoorSts(uint8_t value )
{
    flDoorMsg = ps_get(FLDoorsSub,0);
    if (flDoorMsg != NULL)
    {
        value = (uint8_t)flDoorMsg->int_val;
        if (value == DoorOpen)
        {
            value = DoorOpen;
        }
        else if (value == DoorClose)
        {
            value = DoorClose;
        }
        ps_unref_msg(flDoorMsg);
    }
    return value;
}

static uint8_t getSPIRecSts( )
{
    uint8_t value = OneHourDefault;
    socResSpiMsg = ps_get(socSpiRecSub,0);
    if (socResSpiMsg != NULL)
    {
        value = (uint8_t)socResSpiMsg->int_val;
        if (value == OneHourEnable)
        {
            value = OneHourEnable;
        }
        else if (value == OneHourDisable)
        {
            value = OneHourDisable;
        }
        ps_unref_msg(socResSpiMsg);
    }
    return value;
}

static uint8_t getDoubleClickSts( )
{
    uint8_t value = DoubleClickdisable;
    socDoubleClickMsg = ps_get(doubleClickSub,0);
    if (socDoubleClickMsg != NULL)
    {
        value = (uint8_t)socDoubleClickMsg->int_val;
        if (value == DoubleClickEnable)
        {
            value = DoubleClickEnable;
        }
        else if (value == DoubleClickdisable)
        {
            value = DoubleClickdisable;
        }
        ps_unref_msg(socDoubleClickMsg);
    }
    return value;
}

static uint8_t getSocFiveTimeOutSts( )
{
    uint8_t value = SocFiveMinutedisable;
    socFiveTimeoutMsg = ps_get(socFiveTimeOutSub,0);
    if (socFiveTimeoutMsg != NULL)
    {
        value = (uint8_t)socFiveTimeoutMsg->int_val;
//        if (value == SocFiveMinuteEnable)
//        {
//            value = SocFiveMinuteEnable;
//        }
//        else if (value == SocFiveMinutedisable)
        if (value == SocFiveMinutedisable)
        {
            value = SocFiveMinuteEnable;
        }
        ps_unref_msg(socFiveTimeoutMsg);
    }
    return value;
}
// get can current work status ,if NmSleepMode si 1, means can not work
extern uint8_t NmSleepMode;
static uint8_t getCanWorkSts()
{
    CanNm_NetworkRelease(0);
    vTaskDelay(100);
    if (NmSleepMode == 1)
    {
        return canBusSleep;
    }
    else
    {
        return canBusNotSleep;
    }
}

//static uint8_t getSocHeartBeatSts()
//{
//    if (socHeartBeatFlag == 1)
//    {
//        return SocHeartEnable;
//    }
//    else if (socHeartBeatFlag == 0)
//    {
//        return SocHeartDisable;
//    }
//}

uint8_t getInitialFlag = 1;
static void getInitialstate()
{
    if (getInitialFlag == 1)
    {
        getInitialFlag = 0;
        InitialVehicleSig.AntiTheftSts = VehicleSig.AntiTheftSts;
        InitialVehicleSig.FLDoorSts = VehicleSig.FLDoorSts;
        if (InitialVehicleSig.AntiTheftSts == Arm)
        {
            OneHourModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagEnable;
        }
        if (InitialVehicleSig.FLDoorSts == DoorOpen)
        {
            OneHourModeTurnOut.stDoorSts.DoorFlag = DoorFlagEnable;
        }
    }
}

static void timeoutRequest(TimeOutResqutValueType timeOutVal,HuModeStsType mode)
{
    if (mode == OneHourMode)
    {
        if ( oneHourTimeOutRequest.sendTimes < ONE_HOUR_SPI_REQUEST_TIMES)
        {
            if (timeOutVal == oneHourTimeOutVal)
            {
                if (oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag == TimerCountCanWork)
                {
                    oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanNotWork;
                    oneHourTimeOutRequest.TimeOutResqut.StartTimeCount = get_tick_api();
                }
                if ((oneHourTimeOutRequest.sendTimes == 0))
                {
                    ps_flush(socSpiSendSub);
                    PUB_INT_FL("SpiSendRequst", (oneHourTimeOutVal), FL_STICKY);
                    oneHourTimeOutRequest.sendTimes++;
                }
                else if ((get_tick_api() - oneHourTimeOutRequest.TimeOutResqut.StartTimeCount) >= 1000)
                {
                    oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanWork;
                    ps_flush(socSpiSendSub);
                    PUB_INT_FL("SpiSendRequst", (oneHourTimeOutVal), FL_STICKY);
                    oneHourTimeOutRequest.sendTimes++;
                }
            }
        }
    }

    if (mode == SilentMode)
    {
        if (fiveMinutesTimeOutRequest.sendTimes < SELENT_SPI_REQUEST_TIMES)
        {
            if (timeOutVal == fiveMinutesTimeOutVal)
            {
                if (fiveMinutesTimeOutRequest.TimeOutResqut.TimeOutFlag == TimerCountCanWork)
                {
                    fiveMinutesTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanNotWork;
                    fiveMinutesTimeOutRequest.TimeOutResqut.StartTimeCount = get_tick_api();
                }
                if ((fiveMinutesTimeOutRequest.sendTimes == 0))
                {
                    ps_flush(socSpiSendSub);
                    PUB_INT_FL("SpiSendRequst", (fiveMinutesTimeOutVal), FL_STICKY);
                    fiveMinutesTimeOutRequest.sendTimes++;
                }
                else if ((get_tick_api() - fiveMinutesTimeOutRequest.TimeOutResqut.StartTimeCount) >= 1000)
                {
                    fiveMinutesTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanWork;
                    ps_flush(socSpiSendSub);
                    PUB_INT_FL("SpiSendRequst", (fiveMinutesTimeOutVal), FL_STICKY);
                    fiveMinutesTimeOutRequest.sendTimes++;
                }
            }
        }
    }
}

uint8_t get_gpio_level(void)
{
    uint32_t portA_Value = 0;
    portA_Value = PINS_DRV_ReadPins(PTA);
    if(portA_Value & (1<<20))
    {
        return !ignOff; //high level ACC/ON/READY
    }
    else
    {
        return ignOff;//low level OFF
    }
}

void getHuPowerModeDefault(void)
{
//    canSleepValue = getCanWorkSts();
//    socHeartValue = getSocHeartBeatSts();
//    HuPwrmode.currentMode = SilentMode;
//    if(socHeartValue == SocHeartDisable)  //have not heart beat
    if((get_gpio_level()== ignOff))  //have not heart beat
    {
        HuPwrmode.currentMode = PowerStandbyMode;
        HuPwrmode.turnIntoMode = PowerStandbyMode;
#if PWR_MANAGE_DEBUG
               Printf("PowerSaveMode\r\n");
#endif
    }
    else if((get_gpio_level() != ignOff))
    {
        HuPwrmode.currentMode = NormalMode;
        HuPwrmode.turnIntoMode = NormalMode;
//        HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
               Printf("Normal mode\r\n");
#endif
    }
    else
    {
        HuPwrmode.currentMode = SilentMode;
        HuPwrmode.turnIntoMode = SilentMode;
        HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
               Printf("SilentMode\r\n");
#endif
    }
}

static void Normal_Work(void)
{
    if (HuPwrmode.currentMode == NormalMode)
    {
        VehicleSig.IgnSts = getIgnSts(VehicleSig.IgnSts);
        VehicleSig.FLDoorSts = getFLDoorSts(VehicleSig.FLDoorSts);
        VehicleSig.AntiTheftSts = getAntiThelsSts(VehicleSig.AntiTheftSts);
        VehicleSig.dbcSigSts = getDBCSts(VehicleSig.dbcSigSts);
        VehicleSig.tboxSigSts = getTboxSts();
        OneHourModeTurnOut.oneHourModeTurnOutFiveCon = getSocFiveTimeOutSts();
        SilentModeTurnOut.SilentModeTurnOutClickCon = getDoubleClickSts();

//        VehicleSig.IgnSts = getIgnSts(VehicleSig.IgnSts);
        if ((VehicleSig.IgnSts == ignOff))
        {
            HuPwrmode.currentMode = OneHourMode;
            HuPwrmode.turnIntoMode = NormalMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("Current NormalMode,turn OneHourMode\r\n");
            Printf("ignOff\r\n");
#endif
        }
    }
}


static void One_Hour_Work(void)
{
/**********************************ONE Hour Mode start****************************************************/
    if (HuPwrmode.currentMode == OneHourMode)
    {
        getInitialstate();
        VehicleSig.IgnSts = getIgnSts(VehicleSig.IgnSts);
        VehicleSig.AntiTheftSts = getAntiThelsSts(VehicleSig.AntiTheftSts);
        VehicleSig.FLDoorSts = getFLDoorSts(VehicleSig.FLDoorSts);
        VehicleSig.dbcSigSts = getDBCSts(VehicleSig.dbcSigSts);
        VehicleSig.tboxSigSts = getTboxSts();
        OneHourModeTurnOut.oneHourModeTurnOutFiveCon = getSocFiveTimeOutSts();
        SilentModeTurnOut.SilentModeTurnOutClickCon = getDoubleClickSts();
        if ((VehicleSig.IgnSts == ignReady) || (VehicleSig.IgnSts == ignACC) )
        {
            getInitialFlag = 1;
            HuPwrmode.currentMode = NormalMode;
            HuPwrmode.turnIntoMode = OneHourMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("OneHourMode turn to NormalMode\r\n");
            Printf("ACC or Ready\r\n");
#endif
        }
        if (InitialVehicleSig.FLDoorSts == DoorOpen)
        {
            if (OneHourModeTurnOut.stDoorSts.DoorFlag == DoorFlagEnable)
            {
                if (VehicleSig.FLDoorSts == DoorClose)
                {
                    OneHourModeTurnOut.stDoorSts.DoorPeriod = 0;
                    OneHourModeTurnOut.stDoorSts.LastDoorValue = DoorClose;
                    OneHourModeTurnOut.stDoorSts.DoorFlag = DoorStsFlagDisable;
                }
            }
            if ((VehicleSig.FLDoorSts == DoorOpen) && (OneHourModeTurnOut.stDoorSts.DoorFlag == DoorStsFlagDisable))
            {
                getInitialFlag = 1;
                InitialVehicleSig.FLDoorSts = DoorDefault;
                OneHourModeTurnOut.stDoorSts.DoorFlag =DoorFlagEnable;
                OneHourModeTurnOut.stDoorSts.LastDoorValue = DoorDefault;
                HuPwrmode.currentMode = SilentMode;
                HuPwrmode.turnIntoMode = OneHourMode;
                HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
                Printf("OneHourMode turn to SilentMode\r\n");
                Printf("driver DoorOpen\r\n");
#endif
            }
        }
        else if ( (VehicleSig.IgnSts == ignOff) && (VehicleSig.FLDoorSts == DoorOpen))
        {
            getInitialFlag = 1;
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = OneHourMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("OneHourMode turn to SilentMode\r\n");
            Printf("driver DoorOpen\r\n");
#endif
        }
        if (InitialVehicleSig.AntiTheftSts == Arm)
        {
            if (OneHourModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagEnable)
            {
                if (VehicleSig.AntiTheftSts == Disarm)
                {
                    OneHourModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 0;
                    OneHourModeTurnOut.stAntiTheftSts.LastAntiThetfValue = Disarm;
                    OneHourModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagDisable;
                }
            }
            if ( (VehicleSig.AntiTheftSts == Arm) && (OneHourModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagDisable))
            {
                getInitialFlag = 1;
                InitialVehicleSig.AntiTheftSts = antiTheftDefaut;
                OneHourModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 1;
                OneHourModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagEnable;
                OneHourModeTurnOut.stAntiTheftSts.LastAntiThetfValue = antiTheftDefaut;
                HuPwrmode.currentMode = SilentMode;
                HuPwrmode.turnIntoMode = OneHourMode;
                HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
                Printf("OneHourMode turn to SilentMode\r\n");
                Printf("AntiTheftSts Arm\r\n");
#endif
            }
        }
        else if (VehicleSig.AntiTheftSts == Arm)
        {
            getInitialFlag = 1;
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = OneHourMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("OneHourMode turn to SilentMode\r\n");
            Printf("AntiTheftSts Arm\r\n");
#endif
        }

        if (OneHourModeTurnOut.oneHourModeTurnOutFiveCon == SocFiveMinuteEnable) //?who enanble SocFiveMinute event
        {
            getInitialFlag = 1;
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = OneHourMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("OneHourMode turn to SilentMode\r\n");
            Printf("SocFiveMinuteEnable\r\n");
#endif
        }

        if (OneHourModeTurnOut.OneHourTime.TimeOutFlag == TimerCountCanWork)
        {
            OneHourModeTurnOut.OneHourTime.TimeOutFlag = TimerCountCanNotWork;
            OneHourModeTurnOut.OneHourTime.StartTimeCount = get_tick_api();
        }
        OneHourModeTurnOut.OneHourTime.CurrentCount = get_tick_api();
        if ( ((OneHourModeTurnOut.OneHourTime.CurrentCount - OneHourModeTurnOut.OneHourTime.StartTimeCount)
                >= ONE_HOUR_RSQ_START_TIME )
                &&
             ((OneHourModeTurnOut.OneHourTime.CurrentCount - OneHourModeTurnOut.OneHourTime.StartTimeCount)
                <= ONE_HOUR_RSQ_STOP_TIME ))
        {
            timeoutRequest(oneHourTimeOutVal,OneHourMode); //send enter silent mode request
            OneHourModeTurnOut.oneHourModeTurnOutOneCon = getSPIRecSts();
//            if (OneHourModeTurnOut.oneHourModeTurnOutOneCon == OneHourEnable)
            if (OneHourModeTurnOut.oneHourModeTurnOutOneCon == OneHourEnable)
            {
                getInitialFlag = 1;
                oneHourTimeOutRequest.sendTimes = 0;
                oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanWork;
                HuPwrmode.currentMode = SilentMode;
                HuPwrmode.turnIntoMode = OneHourMode;
                HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
                Printf("OneHourMode turn to SilentMode\r\n");
                Printf("oneHourMode timeout ack allow\r\n");
#endif
            }
            else if (OneHourModeTurnOut.oneHourModeTurnOutOneCon == OneHourDisable)
            {
                getInitialFlag = 1;
                oneHourTimeOutRequest.sendTimes = 0;
                oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanWork;
                OneHourModeTurnOut.oneHourModeTurnOutOneCon = OneHourDefault;
                OneHourModeTurnOut.OneHourTime.TimeOutFlag = TimerCountCanWork;
                HuPwrmode.currentMode = OneHourMode;
                HuPwrmode.turnIntoMode = OneHourMode;
                HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
                Printf("OneHourMode turn to OneHourMode\r\n");
                Printf("oneHourMode timeout ack not allow\r\n");
#endif
            }
        }
        else if ( (OneHourModeTurnOut.OneHourTime.CurrentCount - OneHourModeTurnOut.OneHourTime.StartTimeCount)
                > ONE_HOUR_RSQ_STOP_TIME)
        {
            getInitialFlag = 1;
            oneHourTimeOutRequest.sendTimes = 0;
            oneHourTimeOutRequest.TimeOutResqut.TimeOutFlag = TimerCountCanWork;
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = OneHourMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("OneHourMode turn to SilentMode\r\n");
            Printf("oneHourMode timeout no ack\r\n");
#endif
        }
        /*if turn out other mode, restart One hour timeout and five minute flag*/
        if ( (HuPwrmode.currentMode == SilentMode) || (HuPwrmode.currentMode == NormalMode) )
        {
            oneHourTimeOutRequest.sendTimes = 0;
            OneHourModeTurnOut.OneHourTime.TimeOutFlag = TimerCountCanWork;
            OneHourModeTurnOut.oneHourModeTurnOutFiveCon = SocFiveMinutedisable;
            OneHourModeTurnOut.oneHourModeTurnOutOneCon = OneHourDefault;
            OneHourModeTurnOut.OneHourTime.TimeOutFlag = TimerCountCanWork;
        }
   }
/**********************************ONE Hour Mode end****************************************************/
}

static void Silent_Work(void)
{
/**********************************silent mode start****************************************************/
    if (HuPwrmode.currentMode == SilentMode)
    {
        VehicleSig.AntiTheftSts = getAntiThelsSts(VehicleSig.AntiTheftSts);
        VehicleSig.FLDoorSts = getFLDoorSts(VehicleSig.FLDoorSts);
        VehicleSig.IgnSts = getIgnSts(VehicleSig.IgnSts);
        VehicleSig.dbcSigSts = getDBCSts(VehicleSig.dbcSigSts);
        VehicleSig.tboxSigSts = getTboxSts();
        OneHourModeTurnOut.oneHourModeTurnOutFiveCon = getSocFiveTimeOutSts();
        SilentModeTurnOut.SilentModeTurnOutClickCon = getDoubleClickSts();
        if (SilentModeTurnOut.FiveMinutes.TimeOutFlag == TimerCountCanWork)
        {
            SilentModeTurnOut.FiveMinutes.TimeOutFlag = TimerCountCanNotWork;
            SilentModeTurnOut.FiveMinutes.StartTimeCount = get_tick_api();
        }

        SilentModeTurnOut.FiveMinutes.CurrentCount = get_tick_api();
        if (( (SilentModeTurnOut.FiveMinutes.CurrentCount - SilentModeTurnOut.FiveMinutes.StartTimeCount) >= (FIVE_RSQ_START_TIME))
                &&
                ( (SilentModeTurnOut.FiveMinutes.CurrentCount - SilentModeTurnOut.FiveMinutes.StartTimeCount) <= (FIVE_RSQ_STOP_TIME)))
        {
            timeoutRequest(fiveMinutesTimeOutVal,SilentMode); //send enter silent mode request
            SilentModeTurnOut.SilentModeTurnOutMcuFiveCon = getSPIRecSts();

            if (SilentModeTurnOut.SilentModeTurnOutMcuFiveCon == OneHourEnable)
            {
                fiveMinutesTimeOutRequest.sendTimes = 0;
                SilentModeTurnOut.FiveMinutes.TimeOutFlag = TimerCountCanWork;
                SilentModeTurnOut.SilentModeTurnOutMcuFiveCon = McuFiveMinutedisable;
                HuPwrmode.currentMode = PowerStandbyMode;
                HuPwrmode.turnIntoMode = SilentMode;
                HuPwrmode.mcuCurrentMode = McuStandbyMode;
#if PWR_MANAGE_DEBUG
                Printf("SilentMode turn to PowerStandbyMode\r\n");
                Printf("SilentMode timeout ack allow\r\n");
#endif
            }
            else if (SilentModeTurnOut.SilentModeTurnOutMcuFiveCon== OneHourDisable)
            {
                fiveMinutesTimeOutRequest.sendTimes = 0;
                SilentModeTurnOut.FiveMinutes.TimeOutFlag = TimerCountCanWork;
                SilentModeTurnOut.SilentModeTurnOutMcuFiveCon = McuFiveMinutedisable;
                HuPwrmode.currentMode = SilentMode;
                HuPwrmode.turnIntoMode = SilentMode;
#if PWR_MANAGE_DEBUG
                Printf("SilentMode turn to SilentMode\r\n");
                Printf("SilentMode timeout ack not allow\r\n");
#endif
            }
        }
        else if ( (SilentModeTurnOut.FiveMinutes.CurrentCount - SilentModeTurnOut.FiveMinutes.StartTimeCount) > (FIVE_RSQ_STOP_TIME) )
        {
            fiveMinutesTimeOutRequest.sendTimes = 0;
            SilentModeTurnOut.FiveMinutes.TimeOutFlag = TimerCountCanWork;
            SilentModeTurnOut.SilentModeTurnOutMcuFiveCon = McuFiveMinutedisable;
            HuPwrmode.currentMode = PowerStandbyMode;
            HuPwrmode.turnIntoMode = SilentMode;
            HuPwrmode.mcuCurrentMode = McuStandbyMode;
#if PWR_MANAGE_DEBUG
            Printf("SilentMode turn to PowerStandbyMode\r\n");
            Printf("SilentMode timeout no ack\r\n");
#endif
        }

        if (SilentModeTurnOut.SilentModeTurnOutClickCon == DoubleClickEnable)  //?who enanble doubleclick event
        {
            HuPwrmode.currentMode = OneHourMode;
            HuPwrmode.turnIntoMode = SilentMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("SilentMode turn to OneHourMode\r\n");
            Printf("doubleClick enable\r\n");
#endif
        }

        if ( SilentModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagEnable)
        {
            if (VehicleSig.AntiTheftSts == Arm)
            {
                SilentModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 0;
                SilentModeTurnOut.stAntiTheftSts.LastAntiThetfValue = Arm;
                SilentModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagDisable;
            }
        }
        if ((VehicleSig.AntiTheftSts == Disarm) && (SilentModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagDisable))
        {
            SilentModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 1;
            SilentModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagEnable;
        }

        if ( (VehicleSig.FLDoorSts == DoorOpen) && (SilentModeTurnOut.stAntiTheftSts.AntiThetfPeriod == 1) )
        {
            HuPwrmode.currentMode = OneHourMode;
            HuPwrmode.turnIntoMode = SilentMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("SilentMode turn to OneHourMode\r\n");
            Printf("AntiThetfPeriod DoorOpen\r\n");
#endif
        }

        if ((VehicleSig.IgnSts == ignReady) || (VehicleSig.IgnSts == ignACC) )
        {
            HuPwrmode.currentMode = NormalMode;
            HuPwrmode.turnIntoMode = SilentMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("SilentMode turn to NormalMode\r\n");
            Printf("ready or ACC\r\n");
#endif
        }

        if ( (HuPwrmode.currentMode == NormalMode) ||
                (HuPwrmode.currentMode == OneHourMode) ||
                (HuPwrmode.currentMode == PowerStandbyMode) )
        {
            getInitialFlag = 1;
            SilentModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagEnable;
            SilentModeTurnOut.SilentModeTurnOutClickCon == DoubleClickdisable;
            SilentModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 0;
            SilentModeTurnOut.FiveMinutes.TimeOutFlag = TimerCountCanWork;
        }
    }
/**********************************silent mode end****************************************************/
}

extern uint8_t MonitorHeartFlag;
uint8_t send_MCU_mode_fml_api(void);
uint8_t send_MCU_sleep_mode_fml_api(void);
uint32_t SocWakeupTime = 0,CanWakeUpTime = 0;
uint8_t CanWakeupSource = 0;
static void Power_Save_Work(void)
{
/**********************************power save mode start***************************************************/
    if (HuPwrmode.currentMode == PowerStandbyMode)
    {
        getInitialstate();
//        VehicleSig.AntiTheftSts = antiTheftDefaut,
        VehicleSig.AntiTheftSts = getAntiThelsSts(VehicleSig.AntiTheftSts);
        VehicleSig.IgnSts = getIgnSts(VehicleSig.IgnSts);
        VehicleSig.FLDoorSts = getFLDoorSts(VehicleSig.FLDoorSts);
        VehicleSig.dbcSigSts = getDBCSts(VehicleSig.dbcSigSts);
//        VehicleSig.tboxSigSts = getTboxSts(VehicleSig.tboxSigSts);
        VehicleSig.tboxSigSts = getTboxSts();
        OneHourModeTurnOut.oneHourModeTurnOutFiveCon = getSocFiveTimeOutSts();
        SilentModeTurnOut.SilentModeTurnOutClickCon = getDoubleClickSts();
        getSPIRecSts();

        if (InitialVehicleSig.AntiTheftSts == Disarm)
        {
            if (PowerSaveModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagEnable)
            {
                if (VehicleSig.AntiTheftSts == Arm)
                {
                    PowerSaveModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 0;
                    PowerSaveModeTurnOut.stAntiTheftSts.LastAntiThetfValue = Arm;
                    PowerSaveModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagDisable;
                }
            }
            if ( (VehicleSig.AntiTheftSts == Disarm) && (PowerSaveModeTurnOut.stAntiTheftSts.AntiTheftFlag == AntiTheftStsFlagDisable))
            {
//                getInitialFlag = 1;
                InitialVehicleSig.AntiTheftSts = antiTheftDefaut;
                PowerSaveModeTurnOut.stAntiTheftSts.AntiThetfPeriod = 1;
                PowerSaveModeTurnOut.stAntiTheftSts.AntiTheftFlag = AntiTheftStsFlagEnable;
                PowerSaveModeTurnOut.stAntiTheftSts.LastAntiThetfValue = antiTheftDefaut;
                HuPwrmode.currentMode = SilentMode;
                HuPwrmode.turnIntoMode = OneHourMode;
                HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
                Printf("PowerStandbyMode turn to SilentMode\r\n");
                Printf("AntiTheftSts Disarm\r\n");
#endif
            }
        }
        else if (VehicleSig.AntiTheftSts == Disarm)
//        if (VehicleSig.AntiTheftSts == Disarm)
        {
            // wake_up_soc_interface();
//            getInitialFlag = 1;
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = PowerStandbyMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("PowerStandbyMode turn to SilentMode\r\n");
            Printf("Disarm\r\n");
#endif
        }

        if ( VehicleSig.dbcSigSts == DbcSigEnable)
        {
            // wake_up_soc_interface();
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = PowerStandbyMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("PowerStandbyMode turn to SilentMode\r\n");
            Printf("Dbc Sig\r\n");
#endif
        }
        //TBOX wakeup interface  reserve interface
        if (VehicleSig.tboxSigSts == TboxWakeupEnable)  //who enanble TboxWake event
        {
            // wake_up_soc_interface();
            HuPwrmode.currentMode = SilentMode;
            HuPwrmode.turnIntoMode = PowerStandbyMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("PowerStandbyMode turn to SilentMode\r\n");
            Printf("tbox\r\n");
#endif
        }

        if (( VehicleSig.IgnSts == ignReady ) || ( VehicleSig.IgnSts == ignACC ) )
        {
            HuPwrmode.currentMode = NormalMode;
            HuPwrmode.turnIntoMode = PowerStandbyMode;
            HuPwrmode.mcuCurrentMode = McuRunMode;
#if PWR_MANAGE_DEBUG
            Printf("PowerStandbyMode turn to NormalMode\r\n");
            Printf("ready or ACC\r\n");
#endif
        }

//        if(MonitorHeartFlag == 1)
        {
            MonitorHeartFlag = 0;
//            if (getSocHeartBeatSts() == SocHeartDisable)
            {
                if ((get_gpio_level() == ignOff) && (VehicleSig.IgnSts == ignOff) && (CanWakeupSource ==0))
                {
                    Printf("CAN sleep\r\n");
                    canSleepValue = getCanWorkSts();
                }

                if ((canSleepValue == canBusSleep) && (HuPwrmode.currentMode == PowerStandbyMode) )   //MCU enter deepsleep mode,
                {
                    HuPwrmode.currentMode = PowerSleepMode;
                    HuPwrmode.turnIntoMode = SilentMode;
                    HuPwrmode.mcuCurrentMode = McuSleepMode;

//                    SocWakeupTime = get_tick_api();
//                    Printf("time start\r\n");
//                    while((get_tick_api() - SocWakeupTime) <= 5000)
//                    {
//                        ;
//                    }
#if PWR_MANAGE_DEBUG
                    Printf("PowerSleepMode\r\n");
                    Printf("no can no heart\r\n");
#endif
//                    send_MCU_sleep_mode_fml_api();
                    mcu_halt_set_fml_api();
                    NmSleepMode = 0;
                    mcu_wakeup_set_fml_api();
                    getHuPowerModeDefault();
                    canSleepValue = canBusNotSleep;
                    CanWakeUpTime = get_tick_api();
    //                pins_set_pins_hal_api(PTD,1<<31);
    //                SocWakeupTime = get_tick_api();
                }
            }
        }

        if ((HuPwrmode.currentMode == NormalMode) ||
                (HuPwrmode.currentMode == SilentMode) )
        {
            canstack_wakeup_init_fml_api();
            pins_set_pins_hal_api(PTD,1<<31);
            SocWakeupTime = get_tick_api();
            getInitialFlag = 1;
            TboxWakeValue = 0;
        }
    }
/**********************************power save mode end****************************************************/
}

HuModeStsType getPowerManageSts()
{
    return HuPwrmode.currentMode;
}

void pwrmanage_task_apl( void *pvParameters )
{
    TickType_t xNextWakeTime;
//    static uint16_t extCtrl = 0;
    xNextWakeTime = xTaskGetTickCount();
    igsSwSub = ps_new_subscriber(10, STRLIST("systemPowerMode"));  //ACC ON OFF READY
    antiThelSub = ps_new_subscriber(10, STRLIST("antiThelfStatus"));  //Disarm = 0x00,  Arm = 0x01,
    FLDoorsSub = ps_new_subscriber(10, STRLIST("FLDoorStatus"));  //open = 0x01,  close = 0x02,
    DbcSub = ps_new_subscriber(10, STRLIST("DbcWakeUp"));
    socSpiSendSub = ps_new_subscriber(10, STRLIST("SpiSendRequst"));
    socSpiRecSub = ps_new_subscriber(10, STRLIST("SpiRec"));
    TboxWakeupSub = ps_new_subscriber(10, STRLIST("TboxWakeUp"));
    doubleClickSub = ps_new_subscriber(10, STRLIST("DoubleClick"));
    socFiveTimeOutSub = ps_new_subscriber(10, STRLIST("SocFiveTimeOut"));

    static uint32_t count = 0,pwrmode= 0;
    while(1)
    {
//       ENET_DRV_MDIORead(0,0,2,&extCtrl,65535);
       vTaskDelayUntil(&xNextWakeTime, (40/portTICK_RATE_MS));
       count++;
#if PWR_MANAGE_DEBUG
       pwrmode++;
       if (pwrmode >= 1500)
       {
           pwrmode = 0;
           Printf("pwrmode:%d,NM:%d\r\n",HuPwrmode.currentMode,NmSleepMode);
       }
#endif
       if( get_tick_api()-SocWakeupTime >=1000 )
       {
           pins_clear_pins_hal_api(PTD,1<<31);
       }
       if (get_tick_api() -CanWakeUpTime >= 10000)
       {
           CanWakeupSource = 0;
       }
       Normal_Work();
       One_Hour_Work();
       Silent_Work();
       if (count >= 12) //Adapt SPI communication time ,at least 400ms
       {
           count = 0;
           Power_Save_Work();
       }
    }
}
