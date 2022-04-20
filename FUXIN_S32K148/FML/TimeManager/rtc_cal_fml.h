/*
 * rtc_cal.h
 *
 *  Created on: 2021Äê7ÔÂ16ÈÕ
 *      Author: Administrator
 */

#ifndef TIMEMANAGER_RTC_CAL_FML_H_
#define TIMEMANAGER_RTC_CAL_FML_H_
#include "Cpu.h"

#define RTC_CAL 0

void rtc_Cali(void);
extern TaskHandle_t RtcTask_Handle;  //Rtc task instance
extern void Task_RTC_Cal(void *pvParameters);

#endif /* TIMEMANAGER_RTC_CAL_FML_H_ */
