/*
 * power_manager.c
 *
 *  Created on: 2021Äê6ÔÂ18ÈÕ
 *      Author: Administrator
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "com_task.h"
#include "CanNm.h"
#include "Com.h"
void porte_interrupt_fml( void );
extern uint8_t tempTestData[20];
extern uint8_t socResetFlag;
void mcu_goto_halt(void)
{
    POWER_SYS_SetMode(VLPS, POWER_MANAGER_POLICY_AGREEMENT);//VLPS
//    POWER_SYS_SetMode(STOP1, POWER_MANAGER_POLICY_AGREEMENT);
//    POWER_SYS_SetMode(STOP2, POWER_MANAGER_POLICY_AGREEMENT);
}
void mcu_leave_halt(void)
{
    POWER_SYS_SetMode(RUN, POWER_MANAGER_POLICY_AGREEMENT);//VLPS
}

/* Interrupt service routine for PTA6 */
void PTA_ISR(void)
{
    /* Clear button IRQ flag */
//    Printf("PTA20\r\n");
    PINS_DRV_ClearPortIntFlagCmd(PORTA);
}

void mcu_halt_set_fml_api(void)
{
    pins_clear_pins_hal_api(LED_GPIO,1 << LED2);
    pins_clear_pins_hal_api(LED_GPIO,1 << LED1);
    pins_clear_pins_hal_api(LED_GPIO,1 << 23);
    can_controller_init_fml_api(0);
    set_can_controller_mode_fml_api(CANFML_CS_SLEEP);
    vTaskSuspendAll();
    lpspi_slave_deinit_hal_api(SPISLAVE);
    timer_dinit_hal_api(INST_FLEXTIMER_MC1);
    lpuart_deinit_hal_api(INST_LPUART1);
    lpuart_deinit_hal_api(INST_UARTSOC);
    rtc_set_second_interrupt_disable();
    pins_set_canrx_halt_api();
    int_sys_install_handler_hal_api(63, porte_interrupt_fml, (isr_t *)NULL);
    int_sys_install_handler_hal_api(PORTA_IRQn, PTA_ISR, (isr_t *)0);
    int_sys_enable_irq_hal_api(63);
    int_sys_enable_irq_hal_api(PORTA_IRQn);
    INT_SYS_DisableIRQ(PORTC_IRQn);
    INT_SYS_DisableIRQGlobal();
    mcu_goto_halt();
}

void mcu_wakeup_set_fml_api(void)
{
    mcu_leave_halt();
//    pins_init__hal_api();
    pins_set_canrx_wake_api();
//    canstack_init_fml_api();
//    canstack_init_fml_api();
//    set_can_controller_mode_fml_api(CANFML_CS_STOPPED);
//    can_controller_init_fml_api(0);
//    set_can_controller_mode_fml_api(CANFML_CS_STARTED);
//    Com_TxStart();
//    Com_RxStart();
//    CanNm_NetworkRequest(0);
    lpspi_slave_init_hal_api(SPISLAVE);
    lpuart_init__hal_api(INST_LPUART1,&lpuart1_State, &lpuart1_InitConfig0);
    lpuart_init__hal_api(INST_UARTSOC,&UARTSOC_State, &UARTSOC_InitConfig0);
//    rtc_init_hal_api(RTCTIMER1);
    shell_uart_config_init(); //mod by william
    uart_soc_config_init();
    canstack_wakeup_init_fml_api();
    FTM0_init_fml_api();//add by william
    int_sys_enable_irq_hal_api(PORTC_IRQn);
    ENABLE_IRQ_GLOBAL;
    xTaskResumeAll();

    socResetFlag = 1;
    //uart_printf_data_fml_api(tempTestData,1,",halt",UARTTASKPRINT);
}




