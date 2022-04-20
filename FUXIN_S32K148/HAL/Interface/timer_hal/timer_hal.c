/**@file  timer_hal.c
* @brief  timer give user operation interface
* @details   flash init,flash write,flash read,flash erase
* @author      willianm
* @date        2021-5-25
* @version     V1.0
* @copyright    Copyright (c) 2020 enovate
**********************************************************************************
* @attention
* Hareware:s32k148
* SDK version£º3.0.0
* @par modify data:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2021/5/18   <td>1.0      <td>william   <td>create
* </table>
*
**********************************************************************************
*/

#include "timer_hal.h"


/**@brief S32K1R48 timer_Init
* @param[in]  instance  The FTM peripheral instance number.
* @param[in]  info  Timerx config info,generate from pe tool.
* @param[out]  state  The FTM state structure of the driver.
* @return  Init result
* - STATUS_SUCCESS : Completed successfully.
* - STATUS_ERROR : Error occurred.
*/
status_t timer_init_hal_api(uint32_t instance,
                      const ftm_user_config_t * info,
                      ftm_state_t * state)
{
    status_t status = STATUS_SUCCESS;
    status = FTM_DRV_Init(instance,info,state);
    return status;
}

/**@brief S32K1R48 timer_Dinit
* @param[in]  instance  The FTM peripheral instance number.
* @return  operation status
* - STATUS_SUCCESS : Completed successfully.
* - STATUS_ERROR : Error occurred.
*/
status_t timer_dinit_hal_api(uint32_t instance)
{
    status_t status = STATUS_SUCCESS;
    status = FTM_DRV_Deinit(instance);
    return status;
}

/**@brief S32K1R48 timer_Init_Counter
* @param[in]  instance  The FTM peripheral instance number.
* @param[in]  timer   Timer configuration structure.
* @return  operation status
* - STATUS_SUCCESS : Completed successfully.
* - STATUS_ERROR : Error occurred.
*/
status_t timer_init_counter_hal_api(uint32_t instance,
        const ftm_timer_param_t * timer)
{
    status_t status = STATUS_SUCCESS;
    status = FTM_DRV_InitCounter(instance, timer);
    return status;
}

/**@brief S32K1R48 timer_Counter_Start
 * Starts the FTM counter.
* @param[in]  instance  The FTM peripheral instance number.
* @return  operation status
* - STATUS_SUCCESS : Completed successfully.
* - STATUS_ERROR : Error occurred.
*/
status_t timer_counter_start_hal_api(uint32_t instance)
{
    status_t status = STATUS_SUCCESS;
    status = FTM_DRV_CounterStart(instance);
    return status;
}

/**@brief S32K1R48 timer_Counter_Stop
 * Stops the FTM counter.
* @param[in]  instance  The FTM peripheral instance number.
* @return  operation status
* - STATUS_SUCCESS : Completed successfully.
* - STATUS_ERROR : Error occurred.
*/
status_t timer_counter_stop_hal_api(uint32_t instance)
{
    status_t status = STATUS_SUCCESS;
    status = FTM_DRV_CounterStop(instance);
    return status;
}

/**@brief S32K1R48 timer_Counter_Read
 * Reads back the current value of the FTM counter.
* @param[in]  instance  The FTM peripheral instance number.
* @return
* - The current counter value
*/
uint32_t timer_counter_read_hal_api(uint32_t instance)
{
    uint32_t counter = 0;
    counter = FTM_DRV_CounterRead(instance);
    return counter;
}

