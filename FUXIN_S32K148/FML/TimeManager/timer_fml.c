/*
 * fml_timer.c
 *
 *  Created on: 2021Äê5ÔÂ7ÈÕ
 *      Author: Administrator
 */
#include "../TimeManager/timer_fml.h"

#include "com_task.h"
#include "ftm_common.h"
#include "flexTimer_mc1.h"
#include "pubsub_demo.h"
#include "Com.h"

#define TICK_MAX_DELAY  0xFFFFFFFFU

extern uint8_t can2DETimes[10];
static RTC_Type * const g_rtcBase_app[RTC_INSTANCE_COUNT] = RTC_BASE_PTRS;
extern uint8_t can2DETimes[10];

volatile uint32_t uwTick;

uint8_t rightLedRead;
uint8_t flooLlight;
uint8_t heaLlight;
uint8_t followme;
uint8_t leftLedRead;

/*******************uwTick every 1ms add 1,It can be used to record run time********************************/
void inc_tick_api(void)
{
  uwTick++;
}

uint32_t get_tick_api(void)
{
  return uwTick;
}

void tick_delay_api(__IO uint32_t Delay)
{
  uint32_t tickstart = get_tick_api();
  uint32_t wait = Delay;

  /* Add a period to guarantee minimum wait */
  if (wait < TICK_MAX_DELAY)
  {
     wait++;
  }
  while((get_tick_api() - tickstart) < wait)
  {
  }
}
/**************************************************************************************/

/**interrupt time:1000us*****/

void FTM0_TimerISR(void)
{
    BaseType_t xResult;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    static uint16_t RTCcnt = 0;
    RTCcnt++;
    rtc_timedate_t getdatatime;

    inc_tick_api();

//    if (RTCcnt == 60000)
//    {
//        RTCcnt =0;
//        rtc_get_timestamp_hal_api(&getdatatime);
//        Printf("%d-%d-%d:%d-%d-%d\r\n",getdatatime.year,getdatatime.month,getdatatime.day,getdatatime.hour,getdatatime.minutes,getdatatime.seconds);
////        Printf("%d-%d-%d\r\n",getdatatime.hour,getdatatime.minutes,getdatatime.seconds);
//    }
    //    PINS_DRV_SetPins(PTA, 1 << 27);
    if(shellCmdData.uartWork == shelluartWorking)
    {
        shellCmdData.recTimeCnt++;
        if (shellCmdData.recTimeCnt >= 5)
        {
            shellCmdData.recbuf[shellCmdData.rCnt] = '\0';
            shellCmdData.rCnt = 0;;
            shellCmdData.uartWork = shelluartNotWork;
//            Printf("rec done\r\n");
            xResult = xSemaphoreGiveFromISR(configQueue, &xHigherPriorityTaskWoken);
            if( xResult != pdFAIL )
            {
//                Printf("sig send OK");
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
            else
            {
//                Printf("sig send error");
            }
        }
    }

    if(upLoadTime.upUploadEn)
    {
        upLoadTime.timeUploadCnt++;
    }
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC1, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);

#if PUBSUB_TEST
    xResult = xEventGroupSetBitsFromISR(pubEventGroup,SUPEVENT ,&xHigherPriorityTaskWoken );
    if( xResult != pdFAIL )
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
#endif
}

void FTM0_init_fml_api(void)
{
    ftm_state_t ftmstateStruct;

    timer_init_hal_api(INST_FLEXTIMER_MC1, &flexTimer_mc1_InitConfig,&ftmstateStruct);

    int_sys_install_handler_hal_api(FTM0_Ovf_Reload_IRQn,&FTM0_TimerISR,(isr_t*) 0U);
    int_sys_set_priority_hal_api( FTM0_Ovf_Reload_IRQn, 3 );

    timer_init_counter_hal_api(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);
//    int_sys_enable_irq_hal_api(FTM0_Ovf_Reload_IRQn);
    timer_counter_start_hal_api(INST_FLEXTIMER_MC1);
#if PUBSUB_TEST
    timer_counter_start_hal_api(INST_FLEXTIMER_MC1);
#endif
}


void LPIT_ISR(void)
{
    /* Clear LPIT channel flag */
    lpit_clear_interrupt_flag_hal_api(INST_LPIT1,LPIT_CHANNEL);
    LPIT_stop_Channel_fml(LPIT_CHANNEL);
}

void LPIT_ISR2(void)
{
    int i;
    lpit_clear_interrupt_flag_hal_api(INST_LPIT1, LPIT_CHANNEL2);
    for(i=0;i<5;i++)
    {
        if(can2DETimes[i] != 0)
        {
            can2DETimes[i]--;
        }
        else
        {
            switch(i)
            {
                case 0:
                    rightLedRead = 0;
                    TxIpduNew_Message_26._c[1] &= 0xF3;
                break;
                case 1 :
                    flooLlight = 0;
                    TxIpduNew_Message_26._c[1] &= 0xcf;
                break;
                case 2 :
                    heaLlight = 0;
                    TxIpduNew_Message_26._c[2] &= 0xFc;
                break;
                case 3 :
                    followme = 0;
                    TxIpduNew_Message_26._c[2] &= 0x3F;
                break;
                case 4 :
                    leftLedRead = 0;
                    TxIpduNew_Message_26._c[1] &= 0xFC;
                break;

                default:
                    break;

            }
        }
    }
}

void LPIT_ISR1(void)
{
    /* Clear LPIT channel flag */
    lpit_clear_interrupt_flag_hal_api(INST_LPIT1, LPIT_CHANNEL1);
}

void LPIT_init_fml(void)
{
    lpit_init_hal_api(INST_LPIT1);

    lpit_init_channe_hal_api(INST_LPIT1, LPIT_CHANNEL);
    /* Install LPIT_ISR as LPIT interrupt handler */
    int_sys_install_handler_hal_api(LPIT_Channel_IRQn, &LPIT_ISR, (isr_t *)0);
    int_sys_set_priority_hal_api(LPIT_Channel_IRQn, 0x03);
    //LPIT_start();
    lpit_init_channe_hal_api(INST_LPIT1, LPIT_CHANNEL1);
    int_sys_install_handler_hal_api(LPIT_Channel_IRQn1, &LPIT_ISR1, (isr_t *)0);
    lpit_start_timer_channels_hal_api(INST_LPIT1, LPIT_CHANNEL1);
    int_sys_set_priority_hal_api(LPIT_Channel_IRQn1, 0x03);

    lpit_init_channe_hal_api(INST_LPIT1, LPIT_CHANNEL2);
    int_sys_install_handler_hal_api(LPIT_Channel_IRQn2, &LPIT_ISR2, (isr_t *)0);
    int_sys_set_priority_hal_api(LPIT_Channel_IRQn2, 0x03);
    LPIT_start_Channel_fml(LPIT_CHANNEL2);
}

void LPIT_start_Channel_fml(uint32_t num)
{
      /* Start LPIT0 channel 0 counter */
    lpit_start_timer_channels_hal_api(INST_LPIT1, num);
}

void LPIT_stop_Channel_fml(uint32_t num)
{
    /* Start LPIT0 channel 0 counter */
    lpit_stop_timer_channels_hal_api(INST_LPIT1, num);
}

void alarmISR(void)
{
    /* Toggle the alarm led */
   // PINS_DRV_TogglePins(LED_GPIO, (1 << LED1));
//    rtc_timedate_t alarmTime ;
//    rtc_get_timestamp_hal_api(&alarmTime);
//    rtc_updata_time_api(&alarmTime);
//    Printf("%d-%d-%d:%d-%d-%d\r\n",alarmTime.year,alarmTime.month,alarmTime.day,alarmTime.hour,alarmTime.minutes,alarmTime.seconds);
//    alarmTime.minutes = alarmTime.minutes+1;
//    set_alarm_Time_hal_api(&alarmTime);
}

//void secondsISR(void)
//{
//    /* Toggle the seconds led */
////    PINS_DRV_TogglePins(LED_GPIO, (1 << LED2));
//    Printf("second\r\n");
//}

void get_current_time_fml(void)
{
    rtc_timedate_t currentTimeS;
    rtc_get_current_date_time_hal_api(currentTimeS);

}

uint32_t get_rtc_seconds_fml(void)
{
    uint32_t seconds;
    seconds = rtc_get_time_seconds_hal_api(g_rtcBase_app[0]);
    return seconds;
}

uint32_t get_rtc_micseconds_fml(void)
{
    uint32_t currentTimetpr;
    currentTimetpr =rtc_get_time_tpr_hal_api(g_rtcBase_app[0]);
    return currentTimetpr;
}


