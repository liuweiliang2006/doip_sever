/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
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

#ifndef FLEXIO_COMMON_DRIVER_H
#define FLEXIO_COMMON_DRIVER_H

#include <stddef.h>
#include <stdbool.h>
#include "device_registers.h"
#include "flexio_hw_access.h"
#include "flexio.h"
#include "edma_driver.h"


 /*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for FLEXIO instances. */
extern FLEXIO_Type * const g_flexioBase[FLEXIO_INSTANCE_COUNT];

/* Pointer to device state structures. This structure contains data common to all drivers on one device */
extern flexio_device_state_t *g_flexioDeviceStatePtr[FLEXIO_INSTANCE_COUNT];

/* Table for FLEXIO IRQ numbers */
extern const IRQn_Type g_flexioIrqId[FLEXIO_INSTANCE_COUNT];

/* PCC clock sources, for getting the input clock frequency */
extern const clock_names_t g_flexioClock[FLEXIO_INSTANCE_COUNT];

/* FlexIO DMA request sources */
extern const uint8_t g_flexioDMASrc[FLEXIO_INSTANCE_COUNT][FEATURE_FLEXIO_MAX_SHIFTER_COUNT];

/*******************************************************************************
 * Enumerations.
 ******************************************************************************/


/*******************************************************************************
* Definitions
******************************************************************************/


/*******************************************************************************
 * API
 ******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_DRV_InitDriver
 * Description   : Initializes an instance of FlexIO driver
 *
 *END**************************************************************************/
status_t FLEXIO_DRV_InitDriver(uint32_t instance, flexio_common_state_t *driver);


/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_DRV_DeinitDriver
 * Description   : De-initializes an instance of FlexIO driver
 *
 *END**************************************************************************/
status_t FLEXIO_DRV_DeinitDriver(const flexio_common_state_t *driver);


#if defined(__cplusplus)
}
#endif


#endif /* FLEXIO_COMMON_DRIVER_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
