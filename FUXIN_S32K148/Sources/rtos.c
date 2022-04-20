/* 
 * Copyright (c) 2015 - 2016 , Freescale Semiconductor, Inc.                             
 * Copyright 2016-2017 NXP                                                                    
 * All rights reserved.                                                                  
 *                                                                                       
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.                          
 */

/*
 * main-blinky.c is included when the "Blinky" build configuration is used.
 * main-full.c is included when the "Full" build configuration is used.
 *
 * main-blinky.c (this file) defines a very simple demo that creates two tasks,
 * one queue, and one timer.  It also demonstrates how Cortex-M4 interrupts can
 * interact with FreeRTOS tasks/timers.
 *
 * This simple demo project runs 'stand alone' (without the rest of the tower
 * system) on the Freedom Board or Validation Board, which is populated with a
 * S32K144 Cortex-M4 microcontroller.
 *
 * The idle hook function:
 * The idle hook function demonstrates how to query the amount of FreeRTOS heap
 * space that is remaining (see vApplicationIdleHook() defined in this file).
 *
 * The main() Function:
 * main() creates one software timer, one queue, and two tasks.  It then starts
 * the scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  prvQueueSendTask() sits in a loop that causes it to repeatedly
 * block for 200 milliseconds, before sending the value 100 to the queue that
 * was created within main().  Once the value is sent, the task loops back
 * around to block for another 200 milliseconds.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() sits in a loop that causes it to
 * repeatedly attempt to read data from the queue that was created within
 * main().  When data is received, the task checks the value of the data, and
 * if the value equals the expected 100, toggles the green LED.  The 'block
 * time' parameter passed to the queue receive function specifies that the task
 * should be held in the Blocked state indefinitely to wait for data to be
 * available on the queue.  The queue receive task will only leave the Blocked
 * state when the queue send task writes to the queue.  As the queue send task
 * writes to the queue every 200 milliseconds, the queue receive task leaves the
 * Blocked state every 200 milliseconds, and therefore toggles the blue LED
 * every 200 milliseconds.
 *
 * The LED Software Timer and the Button Interrupt:
 * The user button BTN1 is configured to generate an interrupt each time it is
 * pressed.  The interrupt service routine switches the red LED on, and
 * resets the LED software timer.  The LED timer has a 5000 millisecond (5
 * second) period, and uses a callback function that is defined to just turn the
 * LED off again.  Therefore, pressing the user button will turn the LED on, and
 * the LED will remain on until a full five seconds pass without the button
 * being pressed.
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* SDK includes. */
#include "interrupt_manager.h"
#include "clock_manager.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "Cpu.h"
#include "BoardDefines.h"
#include "com_task.h"
#include "utils.h"
#include "string.h"
#include "pwrmanage_apl.h"
/*pubsub*/
#include "pubsub_demo.h"
#include "pwr_manage_test.h"
/*filesystem*/
#include "fatfs_demo.h"
#include "task_info.h"
#include "../FML/TimeManager/timer_fml.h"
#include <cm_backtrace.h>
#include <rtc_cal_fml.h>

#include "enet.h"

#define HARDWARE_VERSION               "V1.0.0"
#define SOFTWARE_VERSION               "V0.1.0"
/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY        ( tskIDLE_PRIORITY + 2 )
#define    mainQUEUE_SEND_TASK_PRIORITY        ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue, specified in milliseconds, and
converted to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS            ( 100 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH                    ( 1 )

/*
 * Setup the NVIC, LED outputs, and button inputs.
 */
static void setup_hardware( void );

/*
 * The tasks as described in the comments at the top of this file.
 */
void spi_transfer_task_fml( void *pvParameters );
void mcu_test_task( void *pvParameters );
void uart_log_task_fml( void *pvParameters );
void spi_prv_send_task_apl( void *pvParameters );
void can_run_task_apl( void *pvParameters );
void uds_store_task_apl( void *pvParameters );

QueueHandle_t spiCallbackQueue = NULL;
QueueHandle_t spiQueue = NULL;
uint8_t socResetFlag;
/*
 * The LED timer callback function.  This does nothing but switch off the
 * LED defined by the mainTIMER_CONTROLLED_LED constant.
 */
static void prvButtonLEDTimerCallback( TimerHandle_t xTimer );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
QueueHandle_t xQueue = NULL;
QueueHandle_t spiRingbufferQueue = NULL;

/* The LED software timer.  This uses prvButtonLEDTimerCallback() as its callback
function. */
/*-----------------------------------------------------------*/
TimerHandle_t xButtonLEDTimer = NULL;
TaskHandle_t pxSpiReceiveTask;
TaskHandle_t pxSpiSendTask;
TaskHandle_t spi_complte_Task_mcu;
TaskHandle_t pxSpiSendTask_mcu;
TaskHandle_t  pxSpierrTask;
/*-----------------------------------------------------------*/
void get_reset_source(void)
{
    uint16_t reset_source = 0;
    uint8_t reset_value[4];
    int i;
    for(i=0;i<13;i++)
    {
        if(POWER_SYS_GetResetSrcStatusCmd(RCM,(rcm_source_names_t)(i+1)))
        {
            reset_source |= (1<<i);
        }
        //reset_source[i] = POWER_SYS_GetResetSrcStatusCmd(RCM,(rcm_source_names_t)(i+1));
    }
    socResetFlag = 0;
    reset_value[0] = reset_source>>8;
    reset_value[1] = reset_source>>0;
    reset_value[2] = 0XF1;
    reset_value[3] = 0XE1;
	uart_printf_data_fml_api(UARTTASKPRINT,reset_value,4,__FUNCTION__,",rcm");
}

#if PUBSUB_TEST
void power_mode_select(uint8_t powerModeIndex)
{
 if(powerModeIndex == HSRUN)
  POWER_SYS_SetMode(HSRUN, POWER_MANAGER_POLICY_AGREEMENT);
 else if (powerModeIndex == RUN)
  POWER_SYS_SetMode(RUN, POWER_MANAGER_POLICY_AGREEMENT);
}
#endif
uint8_t uartmsg[32];
void rtos_start( void )
{
    rtc_timedate_t updatatime;
    rtc_timedate_t currentTime ;
    /* Configure the NVIC, LED outputs and button inputs. */
    setup_hardware();
//    CLOCK_DRV_GetFreq();
    cm_backtrace_init("FUXIN_S32K148", HARDWARE_VERSION, SOFTWARE_VERSION);
//    saveFaultFile(test);
    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ));
    spiCallbackQueue = xQueueCreate(mainQUEUE_LENGTH, sizeof( unsigned long ));
    spiRingbufferQueue = xQueueCreate(128, 1);
    spiQueue =  xQueueCreate( 1, sizeof( unsigned long ) );
    uartLogQueue = xQueueCreate(10,32);
    taskLogQueue = xQueueCreate(10,sizeof(struct stTask_log));
    configQueue = xSemaphoreCreateBinary(); //deal shell cmd.when has shellcmd, send this queue ,and task will receive this queue,then deal.
    fatfsInitQueue = xSemaphoreCreateBinary();
    ringbuffer_creat_fml();
    uartsoc_ringbuffer_creat_fml();
    can_ringbuffer_creat_fml();
    whole_package_spiring_creat_fml();
    get_reset_source();
    ps_init(); //pubsub lib init,add by william
    getHuPowerModeDefault();//add by ::awilliam
//    lwip_comm_init();
    start_example();
//    PHY_FrameworkInit(phyConfig, phyDrivers);
//    ENET_DRV_MDIORead(0,0,2,&extCtrl,65535);
//    PHY_Init(0);
//    PHY_Read(0, 2, &extCtrl);


#if 0
    if(xQueueReceive(uartLogQueue, &uartmsg[0], 0))
    {

    }
#endif

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
        file. */
    xTaskCreate( spi_transfer_task_fml, "RX", 2*configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY+2, (TaskHandle_t*  )&pxSpiReceiveTask );
    xTaskCreate( spi_prv_send_task_apl, "TX", configMINIMAL_STACK_SIZE, NULL, mainQUEUE_RECEIVE_TASK_PRIORITY+1,    (TaskHandle_t*  )&pxSpiSendTask );
    xTaskCreate( can_run_task_apl, "CAN", 4*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_RECEIVE_TASK_PRIORITY+2 , NULL );
//    xTaskCreate( mcu_test_task, "Power", 3*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY+1 , NULL );
    xTaskCreate( uart_log_task_fml, "uart_log", 4*configMINIMAL_STACK_SIZE+4096, NULL,mainQUEUE_SEND_TASK_PRIORITY+1 , NULL );
    xTaskCreate( uds_store_task_apl, "uds", 2*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY+1 , NULL );
//    xTaskCreate( pwrmanage_task_apl, "pwrmanage", 3*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY , NULL );
#if RTC_CAL
    xTaskCreate( Task_RTC_Cal, "RTC_cal", 2*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY , RtcTask_Handle );
#endif

#if TASK_INFO
    xTaskCreate( taskinfo_task_apl, "taskinfi", 5*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY , NULL );
#endif

#if PWR_TEST
    xTaskCreate( pwrmanage_test_task, "pwrmanagetest", 5*configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY , NULL );
#endif

#if FILESYS_TEST //enable in "fatfs_demo.h"
    xTaskCreate( fatfsTest_Task, "fatfs", configMINIMAL_STACK_SIZE+200, NULL,mainQUEUE_SEND_TASK_PRIORITY+1 , fatfsTask_Handle );
#endif

#if PUBSUB_TEST //enable in "pubsub_demo.h"
    FTM0_init_fml_api();
    xTaskCreate( pubsub_Task, "pubsub", configMINIMAL_STACK_SIZE, NULL,mainQUEUE_SEND_TASK_PRIORITY+1 , PubsubTask_Handle );
#endif
        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    for( ;; );
}
/*-----------------------------------------------------------*/

static void prvButtonLEDTimerCallback( TimerHandle_t xTimer )
{
    /* Casting xTimer to void because it is unused */
    (void)xTimer;
    /* The timer has expired - so no button pushes have occurred in the last
    five seconds - turn the LED off. */
    //PINS_DRV_SetPins(LED_GPIO, (1 << LED1));
}


/*-----------------------------------------------------------*/
void delay(volatile int cycles)
{
    /* Delay function - do nothing for a number of cycles */
    while(cycles--);
}
/* WatchDog IRQ handler */
void WDOG_ISR(void)
{
    /* Turn off both LEDs */
//    Printf("dead\r\n");
//    PINS_DRV_ClearPins(LED_GPIO, (1 << LED0) | (1 << LED1));
    /* Disable the SysTick timer */
//    SysTick_Disable();
}

void clock_Monitor_init()
{
    //SOSC
//    SCG->SOSCCSR |= (1<<16); //SOSCCM System OSC Clock Monitor is enabled
//    SCG->SOSCCSR |= (1<<17); //SOSCCMRE Clock Monitor generates reset when error detected

    //PLL
    SCG->SPLLCSR |= (1<<16); //SPLLCM System PLL Clock Monitor is enabled
    SCG->SPLLCSR |= (1<<17); //SPLLCMRE Clock Monitor generates reset when error detected

}

 void setup_hardware( void )
{
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
//    NVIC_SetGroup(2);
    pins_init__hal_api();
    clock_Monitor_init();
//    *(uint32_t *)(0x4003F000) = 0x01;
    /* Change LED1, LED2 to outputs. */
    pins_set_pins_direction_hal_api(LED_GPIO,  (1 << LED1) | (1 << LED2)|(1<<17)|(1<<23));
    /* Start with LEDs off. */
    pins_set_pins_hal_api(LED_GPIO, (1 << LED1) | (1 << LED2)|(1<<17)|(1<<23));
    flash_app_set_fml();
    int_sys_install_handler_hal_api(BTN_PORT_IRQn, soc_isr_hander_fml, (isr_t *)NULL);
    int_sys_install_handler_hal_api(PORTA_IRQn, PTA_ISR, (isr_t *)0);
//    INT_SYS_InstallHandler(WDOG_EWM_IRQn, WDOG_ISR, (isr_t *)0);
    INT_SYS_EnableIRQ(PORTA_IRQn);
    int_sys_set_priority_hal_api( BTN_PORT_IRQn, 2 );
    int_sys_set_priority_hal_api( PORTA_IRQn, 2 );
    int_sys_set_priority_hal_api(DMA2_IRQn, 2);
    int_sys_set_priority_hal_api(LPSPI1_IRQn, 0x02);
    edma_init_hal_api();
    lpspi_slave_init_hal_api(SPISLAVE);
    shell_uart_config_init(); //mod by william
    uart_soc_config_init();//add by william
    FTM0_init_fml_api();//add by william
    Printf("start\r\n");
    power_manager_init_hal_api();
    rtc_init_hal_api(RTCTIMER1);

//    while(1)
//    {
//        pins_set_pins_hal_api(PTD,1<<31);
        pins_clear_pins_hal_api(PTD,1<<31);
//    }
//    INT_SYS_EnableIRQ(WDOG_EWM_IRQn);
    /* Initialize WDOG */
//    WDOG_DRV_Init(INST_WATCHDOG1, &watchdog1_Config0);
//    rtc_Cali();
    LPIT_init_fml();
    int_sys_enable_irq_hal_api(BTN_PORT_IRQn);
    delay(720000);
    delay(720000);
    delay(720000);
    delay(720000);
    delay(720000);
    delay(720000);
    fatfs_init_fml_api(); //filesystem init
//    uint32_t PA_Value = 0 ;
//    while(1)
//        PA_Value = PINS_DRV_ReadPins(PTA);
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    Printf("heap fail!\r\n");
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    Printf("stack over:%s\r\n",pcTaskName);
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
                                                                                    {
    volatile size_t xFreeHeapSpace;

    /* This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    if( xFreeHeapSpace > 100 )
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }

}
/*-----------------------------------------------------------*/

/* The Blinky build configuration does not include run time stats gathering,
however, the Full and Blinky build configurations share a FreeRTOSConfig.h
file.  Therefore, dummy run time stats functions need to be defined to keep the
linker happy. */
void vMainConfigureTimerForRunTimeStats( void ) {}
unsigned long ulMainGetRunTimeCounterValue( void ) { return 0UL; }

/* A tick hook is used by the "Full" build configuration.  The Full and blinky
build configurations share a FreeRTOSConfig.h header file, so this simple build
configuration also has to define a tick hook - even though it does not actually
use it for anything. */
void vApplicationTickHook( void ) {}

/*-----------------------------------------------------------*/
