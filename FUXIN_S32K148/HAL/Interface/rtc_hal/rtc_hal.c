/*
 * rtc_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"

uint32_t rtc_get_time_tpr_hal_api(const RTC_Type * const base)
{
    uint32_t tmp = base->TPR;
    tmp = (tmp & RTC_TSR_TSR_MASK) >> 5;
    return (uint32_t) (tmp);
}
uint32_t rtc_get_time_seconds_hal_api(const RTC_Type * const base)
{
    uint32_t tmp = base->TSR;
    tmp = (tmp & RTC_TSR_TSR_MASK) >> RTC_TSR_TSR_SHIFT;
    return (uint32_t) (tmp);
}
void rtc_deinit_hal_api(uint32_t instance)
{
    RTC_DRV_Deinit(instance);
}

void rtc_init_hal_api(uint32_t instance)
{
    /* Initialize RTC instance
     *  - See RTC configuration component for options
     */
    RTC_DRV_Init(instance, &rtcTimer1_Config0);
    /* Configure RTC Time Seconds Interrupt */
    RTC_DRV_ConfigureSecondsInt(instance, &rtcTimer1_SecIntConfig0);

    /* Set the time and date */
    RTC_DRV_SetTimeDate(instance, &rtcTimer1_StartTime0);
    int_sys_set_priority_hal_api( RTC_Seconds_IRQn, 3 );
    /* Start the RTC counter */
    RTC_DRV_StartCounter(instance);
}
void set_rtc_alarm_hal_api(uint8_t hour,uint8_t minutes,uint8_t seconds)
{
    rtc_timedate_t tempTime;
    /* Get current time */
    RTC_DRV_GetCurrentTimeDate(RTCTIMER1, &tempTime);
    /* Add to current time 5 seconds */
    tempTime.hour += hour;
    tempTime.minutes += minutes;
    tempTime.seconds += seconds;
    /* Set new alarm time and date */
    rtcTimer1_AlarmConfig0.alarmTime = tempTime;
    /* Configure the alarm */
    RTC_DRV_ConfigureAlarm(RTCTIMER1, &rtcTimer1_AlarmConfig0);
}

void set_alarm_Time_hal_api(rtc_timedate_t *alarmTime)
{
    rtcTimer1_AlarmConfig0.alarmTime.year = alarmTime->year;
    rtcTimer1_AlarmConfig0.alarmTime.month = alarmTime->month;
    rtcTimer1_AlarmConfig0.alarmTime.day = alarmTime->day;
    rtcTimer1_AlarmConfig0.alarmTime.hour = alarmTime->hour;
    rtcTimer1_AlarmConfig0.alarmTime.minutes = alarmTime->minutes;
    rtcTimer1_AlarmConfig0.alarmTime.seconds = alarmTime->seconds;
    /* Configure the alarm */
    RTC_DRV_ConfigureAlarm(RTCTIMER1, &rtcTimer1_AlarmConfig0);
}

void rtc_updata_time_api(rtc_timedate_t *updatatime)
{
    status_t ret;
    /* Initialize RTC instance
     *  - See RTC configuration component for options
     */
    RTC_DRV_StopCounter(RTCTIMER1);
    /* Set the time and date */
    ret = RTC_DRV_SetTimeDate(RTCTIMER1, updatatime);
    /* Start the RTC counter */
    RTC_DRV_StartCounter(RTCTIMER1);
}

void rtc_get_current_date_time_hal_api(rtc_timedate_t tempTime)
{
	RTC_DRV_GetCurrentTimeDate(RTCTIMER1, &tempTime);
}

void rtc_get_timestamp_hal_api(rtc_timedate_t *tempTime)
{
    RTC_DRV_GetCurrentTimeDate(RTCTIMER1, tempTime);
}


void rtc_set_second_interrupt_disable()
{
//    uint32_t tmp = base->IER;
    RTC->IER &= ~(1<<4);
}
