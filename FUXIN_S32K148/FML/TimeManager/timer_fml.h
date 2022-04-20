/*
 * fml_timer.h
 *
 *  Created on: 2021Äê5ÔÂ7ÈÕ
 *      Author: Administrator
 */

#ifndef FML_TIMER_H_
#define FML_TIMER_H_
#include "Cpu.h"

extern void FTM0_init_fml_api(void);

extern void get_current_time_fml(void);
uint32_t get_rtc_seconds_fml(void);
uint32_t get_rtc_micseconds_fml(void);

extern void LPIT_init_fml(void);
void LPIT_start_Channel_fml(uint32_t num);
void LPIT_stop_Channel_fml(uint32_t num);


void inc_tick_api(void);
uint32_t get_tick_api(void);
void tick_delay_api(__IO uint32_t Delay);
#endif /* FML_TIMER_H_ */
