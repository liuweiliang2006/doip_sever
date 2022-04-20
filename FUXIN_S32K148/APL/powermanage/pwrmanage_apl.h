/*
 * pwrmanage_apl.h
 *
 *  Created on: 2021年7月12日
 *      Author: Administrator
 */

#ifndef POWERMANAGE_PWRMANAGE_APL_H_
#define POWERMANAGE_PWRMANAGE_APL_H_

#include "pubsub.h"

extern void pwrmanage_task_apl( void *pvParameters );

extern ps_subscriber_t *igsSwSub,*antiThelSub,*FLDoorsSub,*DbcSub,*TboxWakeupSub;

extern ps_subscriber_t *socSpiSendSub,*socSpiRecSub,*doubleClickSub,*socFiveTimeOutSub;

//点火开关(Ignition Switch)
typedef enum
{
    ignOff = 0x00,
    ignACC = 0x01,
    ignON = 0x02,
    ignReady = 0x03,
    ignDefaut = 0x04
}ignStsType;

//HU power mode
typedef enum
{
    NormalMode = 0x00,
    OneHourMode = 0x01,
    SilentMode =0x02,
    PowerStandbyMode = 0x03,
    PowerSleepMode = 0x04,
    NoneMode = 0x05
}HuModeStsType;

//MCU power mode
typedef enum
{
    McuNoneMode = 0x00,
    McuRunMode = 0x01,
    McuStandbyMode = 0x02,
    McuSleepMode = 0x03
}McuModeStsType;

//Vehicle left front door status
typedef enum
{
    DoorDefault = 0x00,
    DoorOpen = 0x01,
    DoorClose = 0x02,
    DoorInvalid = 0x03
}driverDoorType;

//soc FiveMinutes signal status ,when HU in OneHourMode,can use this signal
typedef enum
{
    SocFiveMinutedisable = 0x00,
    SocFiveMinuteEnable = 0x01
}socFiveMinuteTpye;

//MCU FiveMinutes signal status ,when HU in silent mode,can use this signal
typedef enum
{
    McuFiveMinutedisable = 0x00,
    McuFiveMinuteEnable = 0x01
}mcuFiveMinuteTpye;

// MCU 1 hour timeout signal,when HU in OneHourMode,can use this signal
typedef enum
{
    OneHourDisable = 0x00,
    OneHourEnable = 0x01,
    OneHourDefault = 0x03
}OneHourTpye;

//Vehicle antitheft status
typedef enum
{
    Disarm = 0x00,
    Arm = 0x01,
    Prearm = 0x02,
    Warning = 0x03,
    antiTheftDefaut = 0x04
}antiTheftType;

typedef enum
{
    DoubleClickdisable = 0x00,
    DoubleClickEnable = 0x01
}doubleClickType;

typedef enum
{
    TboxWakeupdisable = 0x00,
    TboxWakeupEnable = 0x01
}TboxType;

typedef enum
{
    SocHeartDisable = 0x00,
    SocHeartEnable = 0x01
}socHeartBeatType;

typedef enum
{
    DbcSigDisable = 0x00,
    DbcSigEnable = 0x01
}dbcSigType;

typedef enum
{
    TboxSigDisable = 0x00,
    TboxSigEnable = 0x01
}TboxSigType;

typedef enum
{
    canBusSleep = 0x01,
    canBusNotSleep = !canBusSleep

}canWorkType;

typedef enum
{
    TimerCountCanWork = 1,
    TimerCountCanNotWork = !TimerCountCanWork
}TimeCountFlagType;

typedef enum
{
    AntiTheftStsFlagEnable = 1,
    AntiTheftStsFlagDisable = !AntiTheftStsFlagEnable
}AntiTheftFlagType;
typedef enum
{
    DoorFlagEnable = 1,
    DoorStsFlagDisable = !DoorFlagEnable
}DoorFlagType;

typedef struct stTimeOutType
{
    TimeCountFlagType TimeOutFlag;
    uint32_t StartTimeCount;
    uint32_t CurrentCount;
};

typedef struct stAntiTheftStsType
{
    AntiTheftFlagType AntiTheftFlag;
    antiTheftType LastAntiThetfValue;
    antiTheftType CurrentAntiThetfValue;
    uint8_t AntiThetfPeriod;
};

typedef struct stDoorStsType
{
    DoorFlagType DoorFlag;
    driverDoorType LastDoorValue;
    driverDoorType CurrentDoorfValue;
    uint8_t DoorPeriod;
};

typedef struct stOneHourModeTurnOutType
{
    socFiveMinuteTpye oneHourModeTurnOutFiveCon;
    OneHourTpye oneHourModeTurnOutOneCon;
    struct stTimeOutType OneHourTime;
    struct stAntiTheftStsType stAntiTheftSts;
    struct stDoorStsType stDoorSts;
};

typedef enum
{
    oneHourTimeOutVal = 1,
    fiveMinutesTimeOutVal = 2
}TimeOutResqutValueType;

typedef struct stRequestType
{
    struct stTimeOutType TimeOutResqut;
    uint8_t sendTimes;
};


typedef struct stSilentModeTurnOutType
{
    mcuFiveMinuteTpye SilentModeTurnOutMcuFiveCon;  //si to power condition
    socHeartBeatType SilentModeTurnOutSocHeartBeatCon;//si to power condition
    struct stTimeOutType FiveMinutes;//si to power condition

    doubleClickType SilentModeTurnOutClickCon;  //si to one condition
    struct stAntiTheftStsType stAntiTheftSts;
};

typedef struct stPowerSaveModeTurnOutType
{
    struct stAntiTheftStsType stAntiTheftSts;
};

typedef struct stVehicleType
{
    ignStsType IgnSts;
    driverDoorType FLDoorSts;
    antiTheftType  AntiTheftSts;
    dbcSigType dbcSigSts;
    TboxSigType tboxSigSts;
};

typedef struct stPwrManageType
{
    HuModeStsType currentMode;
    HuModeStsType turnIntoMode;
    McuModeStsType mcuCurrentMode;
};

extern struct stPwrManageType HuPwrmode;
void getHuPowerModeDefault(void);
HuModeStsType getPowerManageSts(void);
uint8_t getSocHeartBeatSts();
extern uint8_t socHeartBeatFlag;
extern uint8_t CanWakeupSource;
#endif /* POWERMANAGE_PWRMANAGE_APL_H_ */
