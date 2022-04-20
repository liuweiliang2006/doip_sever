/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
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
/*!
 * @file ftm_mc_driver.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

#ifndef FTM_MC_DRIVER_H
#define FTM_MC_DRIVER_H

#include "ftm_common.h"

/*!
 * @addtogroup ftm_mc_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief The configuration structure in timer mode
 *
 * Implements : ftm_timer_param_t_Class
 */
typedef struct
{
    ftm_config_mode_t mode;                 /*!< FTM mode */
    uint16_t initialValue;                  /*!< Initial counter value */
    uint16_t finalValue;                    /*!< Final counter value */
} ftm_timer_param_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the FTM counter.
 *
 * Starts the FTM counter. This function provides access to the
 * FTM counter settings. The counter can be run in Up counting and Up-down counting modes.
 * To run the counter in Free running mode, choose Up counting option and provide
 * 0x0 value for the initialValue and 0xFFFF for finalValue. Please call this
 * function only when FTM is used as timer/counter.
 *
 * @param[in] instance The FTM peripheral instance number.
 * @param[in] timer Timer configuration structure.
 * @return operation status
 *        - STATUS_SUCCESS : Initialized successfully.
 */
status_t FTM_DRV_InitCounter(uint32_t instance,
                             const ftm_timer_param_t * timer);

/*!
 * @brief Starts the FTM counter.
 *
 * @param[in] instance The FTM peripheral instance number.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 *        - STATUS_ERROR : Error occurred.
 */
status_t FTM_DRV_CounterStart(uint32_t instance);

/*!
 * @brief Stops the FTM counter.
 *
 * @param[in] instance The FTM peripheral instance number.
 * @return operation status
 *        - STATUS_SUCCESS : Completed successfully.
 */
status_t FTM_DRV_CounterStop(uint32_t instance);

/*!
 * @brief Reads back the current value of the FTM counter.
 *
 * @param[in] instance The FTM peripheral instance number.
 * @return The current counter value
 */
uint32_t FTM_DRV_CounterRead(uint32_t instance);

/*!
 * @brief This function will get the default configuration values
 *        in the structure which is used as a common use-case.
 * @param[out] config Pointer to the structure in which the
 *             configuration will be saved.
 * @return None
 */
void FTM_MC_DRV_GetDefaultConfig(ftm_timer_param_t * const config);

#if defined(__cplusplus)
}
#endif

/*! @}*/

/*! @}*/ /* End of addtogroup ftm_mc_driver */

#endif /* FTM_MC_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
