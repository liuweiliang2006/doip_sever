/*
 * rtc_cal.c
 *
 *  Created on: 2021Äê7ÔÂ16ÈÕ
 *      Author: Administrator
 */
#include "Driver_interface.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"

#define REF_TIMER_FREQ  31250
//#define REF_TIMER_FREQ  62500
#define REF_TIMER_MOD  62500  /*FTM0 counter mode value*/
#define REF_TIMER_SECOND_CNT 31250  /*FTM0 counter value for 1 second*/
//#define REF_TIMER_SECOND_CNT 62500  /*FTM0 counter value for 1 second*/
#define DELTA_RTC_SEC_CNT_COMP_US  (1000000/32768)

QueueHandle_t RCT_Cal_Queue = NULL;
uint32_t RTC_Start_Flag = 0;
uint8_t RTC_SecondCnt_MeasureComplte_Flag = 0;
static uint32_t RefTimer_CountVal_Buffer[5];
static uint32_t Average_Second_Cnt = 0;
static uint32_t RTC_Second_Cnt[5] = {0};
/*used to LPO_RTC clock frequency measurement result backup*/
float Last_Measured_LPO_RTC_ClkFreq = 0.0f;


void Timer1_ISR(void)
{
//    Printf("time1\r\n");
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC2, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}

void secondsISR(void)
{
    /* Toggle the seconds led */
    portBASE_TYPE xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    static uint32_t Current_RefTimer_Cnt = 0;
    static uint32_t Last_RefTimer_Cnt = 0;
    static uint8_t i = 0;

    if(1 == RTC_Start_Flag)/*wait for RTC start flag*/
    {
        Current_RefTimer_Cnt = FTM_DRV_CounterRead(INST_FLEXTIMER_MC2);
        RefTimer_CountVal_Buffer[i] = Current_RefTimer_Cnt;/*buffer it for further test*/

        if(Current_RefTimer_Cnt<Last_RefTimer_Cnt)/*reload happened*/
        {
            RTC_Second_Cnt[i++] = (Current_RefTimer_Cnt + REF_TIMER_MOD)- Last_RefTimer_Cnt;/*get the time error and store it*/
        }
        else
        {
            RTC_Second_Cnt[i++] = Current_RefTimer_Cnt - Last_RefTimer_Cnt;/*get the time error and store it*/
        }

        Last_RefTimer_Cnt = Current_RefTimer_Cnt; /*save current time stamp*/

        if(i==3)
        {
            i = 0;  /*reset the buffer index*/
            Average_Second_Cnt = (RTC_Second_Cnt[1] + RTC_Second_Cnt[2])/2;/*get the average as final result*/
            RTC_SecondCnt_MeasureComplte_Flag = 1;/*send complete flag to notice APP*/
            xQueueSendFromISR( RCT_Cal_Queue, &RTC_SecondCnt_MeasureComplte_Flag, &xHigherPriorityTaskWoken );
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/*******************************************************************************
 *
 * Functions: set the LPO clock trim with TrimSet, wait FTM measurement complete
 *            and return the trim result by *Trim_Result
 *
 *******************************************************************************/
static status_t Do_LPO_Trim(int8_t TrimSet, uint32_t *Trim_Result)
{
    uint32_t receiveValue= 0;
    PMC->LPOTRIM = TrimSet;/*set the new LPO trim value to LPOTRM register to generate new frequency*/

    RTC_Start_Flag = 1;/*start the trim*/
    /*wait for RTC second measure complete, timeout need to longer than 6 seconds to get trim result*/
//    if(STATUS_SUCCESS == OSIF_SemaWait(&RTC_SecondCnt_MeasureComplte_Flag, MEASURE_TIMEOUT_MS))
//    if (RTC_SecondCnt_MeasureComplte_Flag == 1)
//    while (RTC_SecondCnt_MeasureComplte_Flag != 1);
    if (xQueueReceive ( RCT_Cal_Queue, &receiveValue,portMAX_DELAY))
    {
        RTC_SecondCnt_MeasureComplte_Flag = 0;
        *Trim_Result = Average_Second_Cnt;/*get the LPO trim result*/
        Average_Second_Cnt = 0;          /*clean the LPO trim result*/
        RTC_Start_Flag = 0;
        return STATUS_SUCCESS;
    }
    else
         return STATUS_ERROR;
}

static status_t LPO_Trim(float *Freq)
{

    uint32_t RTC_Measure_LastTrim = 0;    /* backup the last trim result */
    uint32_t RTC_Measure_CurrentTrim = 0; /* the current trim result */

    uint32_t RTC_Measure_TrimResult = 0; /* the trim result */

    int8_t LPO_Trim_SetVal = 0;    /* the LPO trim register set value */
    int8_t LPO_Trim_LastVal = 0;    /* the last LPO trim register set value */

    status_t Trim_State = STATUS_ERROR;
    uint32_t i;

    /*get current LPO trim configuration,it's reset to zero by default*/
    LPO_Trim_SetVal = PMC->LPOTRIM;/*read the register PMC->LPOTRIM*/

    for(i=0;i<16;i++) /*the trimable LPO period is from -16 to +15*/
    {
        if(STATUS_SUCCESS==Do_LPO_Trim(LPO_Trim_SetVal,&RTC_Measure_CurrentTrim))
        {
            if(RTC_Measure_CurrentTrim>REF_TIMER_SECOND_CNT)/*the LPO CLK is faster than expected*/
            {
                if((RTC_Measure_LastTrim<REF_TIMER_SECOND_CNT)&&(i>0))
                {
                    Trim_State = STATUS_SUCCESS;
                    break;
                }
                else
                {
                    LPO_Trim_LastVal = LPO_Trim_SetVal;/*backup the trim value*/

                    LPO_Trim_SetVal--; /*decrease the LPO CLK period*/
                    RTC_Measure_LastTrim = RTC_Measure_CurrentTrim;/*buffer the trim result*/
                }
            }
            else /*the LPO CLK is slower than expected*/
            {
                if((RTC_Measure_LastTrim>REF_TIMER_SECOND_CNT)&&(i>0))
                {
                    Trim_State = STATUS_SUCCESS;
                    break;
                }
                else
                {
                    LPO_Trim_LastVal = LPO_Trim_SetVal;/*backup the trim value*/

                    LPO_Trim_SetVal++; /*increase the LPO CLK period*/
                    RTC_Measure_LastTrim = RTC_Measure_CurrentTrim;/*buffer the trim result*/
                }
            }
        }
    }
    if(i>=16) /*it¡®s beyond the trim scope*/
    {
        Trim_State = STATUS_SUCCESS;
    }

    if(STATUS_SUCCESS==Trim_State)
    {
        RTC_Measure_TrimResult = abs(RTC_Measure_CurrentTrim-REF_TIMER_SECOND_CNT)<abs(RTC_Measure_LastTrim-REF_TIMER_SECOND_CNT)?\
                RTC_Measure_CurrentTrim:\
                RTC_Measure_LastTrim;

        if(RTC_Measure_TrimResult == RTC_Measure_LastTrim)/*if the last trim is more accuracy*/
            Do_LPO_Trim(LPO_Trim_LastVal,&RTC_Measure_CurrentTrim);/*use the last trim*/

        *Freq = ((float)REF_TIMER_FREQ*32768.0f)/RTC_Measure_TrimResult;/*convert to frequency in HZ*/
    }
    return Trim_State;
}

/******************************************************************************************************
 * Do the RTC trim according to user input Trim_Ctrl
 * main functions:
 *    1) call LPO_Trim() to trim the LPO/4 clock to approach 32.768KHz as RTC clock reference
 *    2) do RTC second compensation, calculate interval and compensate value based on Trimmed_LPO_Freq;
 *    3) if Trim_Ctrl = RESET_DEFAULT, reset the LPO trim and RTC second compensation to default 0
 *
 * Return: STATUS_SUCCESS if trim OK; STATUS_ERROR if any error
 ******************************************************************************************************/
status_t RTC_App_TRIM( )
{
    status_t statusCode = STATUS_SUCCESS;

    float Trimmed_LPO_Freq = 0;
    uint32_t RTC_compInterval;
    int32_t RTC_compensation;

    float Delta_Freq = 0.0f;

//    if(ENABLE == Trim_Ctrl)/*do LPO clock trim and RTC compensation*/
    {
        statusCode = LPO_Trim(&Trimmed_LPO_Freq);/*start LPO trim*/

        Last_Measured_LPO_RTC_ClkFreq = Trimmed_LPO_Freq;/*backup the measured result*/

         Delta_Freq = fabs(Trimmed_LPO_Freq-32768.0f);

         if(Delta_Freq != 0)/*if there is still error*/
         {
            if(Delta_Freq >= 127)/*if error bigger than abs(127/32768) second*/
            {
                RTC_compInterval = 0;/*compensate every 1 second*/

                if(Trimmed_LPO_Freq<32768)    /*if over the max compensation*/
                    RTC_compensation = 127; /*use the MAX configuration*/

                if(Trimmed_LPO_Freq>32768)   /*if over the minimum compensation*/
                    RTC_compensation = -128; /*use the MIN configuration*/

                /*call rtcTimer API to set RTC second compensation parameters*/
                statusCode = RTC_DRV_ConfigureTimeCompensation(RTCTIMER1,RTC_compInterval,(0xFF&RTC_compensation));
            }
            else if((Delta_Freq < 127)&&(Delta_Freq>=1))
            {
                RTC_compInterval = 0;/*compensate every 1 second*/
                RTC_compensation = round(32768-Trimmed_LPO_Freq);

                /*call rtcTimer API to set RTC second compensation parameters*/
                statusCode = RTC_DRV_ConfigureTimeCompensation(RTCTIMER1,RTC_compInterval,(0xFF&RTC_compensation));
            }
            else /*error smaller than 1/32768 second*/
            {
                if(Trimmed_LPO_Freq<32768)
                    RTC_compensation = 1;  /* compensate only one 32.768KHz clock cycle per second in each interval*/
                else
                    RTC_compensation = -1;  /* compensate only one 32.768KHz clock cycle per second in each interval*/

                RTC_compInterval = DELTA_RTC_SEC_CNT_COMP_US/Delta_Freq;

                if(RTC_compInterval>255)    /*if over the max compensation interval*/
                    RTC_compInterval = 255; /*use the MAX configuration interval*/

                /*call rtcTimer API to set RTC second compensation parameters*/
                statusCode = RTC_DRV_ConfigureTimeCompensation(RTCTIMER1,(0xFF&RTC_compInterval),RTC_compensation);
            }
         }
    }

    return statusCode;
}

//void rtc_Cali(void)
//{
//    ftm_state_t FTM1_State ;
//
//    timer_init_hal_api(INST_FLEXTIMER_MC2,&flexTimer_mc2_InitConfig,&FTM1_State);
////    int_sys_install_handler_hal_api(FTM1_Ovf_Reload_IRQn,&Timer1_ISR,(isr_t*) 0U);
////    int_sys_set_priority_hal_api( FTM1_Ovf_Reload_IRQn, 2 );
//    timer_init_counter_hal_api(INST_FLEXTIMER_MC2,&flexTimer_mc2_TimerConfig);
//    timer_counter_start_hal_api(INST_FLEXTIMER_MC2);
//
//    RTC_App_TRIM( );
//
//
//}

TaskHandle_t RtcTask_Handle;  //Rtc task instance

void Task_RTC_Cal(void *pvParameters)
{
    ftm_state_t FTM1_State ;

    RCT_Cal_Queue = xQueueCreate( 1, sizeof( unsigned long ));
    timer_init_hal_api(INST_FLEXTIMER_MC2,&flexTimer_mc2_InitConfig,&FTM1_State);
    timer_init_counter_hal_api(INST_FLEXTIMER_MC2,&flexTimer_mc2_TimerConfig);
    timer_counter_start_hal_api(INST_FLEXTIMER_MC2);
    RTC_App_TRIM();
    vTaskDelete(RtcTask_Handle);
}
