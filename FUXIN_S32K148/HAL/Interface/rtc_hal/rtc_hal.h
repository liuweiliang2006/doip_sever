/*
 * rtc_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_RTC_HAL_RTC_HAL_H_
#define INTERFACE_RTC_HAL_RTC_HAL_H_
#include "Cpu.h"
uint32_t rtc_get_time_tpr_hal_api(const RTC_Type * const base);
uint32_t rtc_get_time_seconds_hal_api(const RTC_Type * const base);
void rtc_deinit_hal_api(uint32_t instance);
void rtc_init_hal_api(uint32_t instance);
void set_rtc_alarm_hal_api(uint8_t hour,uint8_t minutes,uint8_t seconds);
void rtc_get_current_date_time_hal_api(rtc_timedate_t tempTime);
void rtc_set_second_interrupt_disable();

#endif /* INTERFACE_RTC_HAL_RTC_HAL_H_ */
