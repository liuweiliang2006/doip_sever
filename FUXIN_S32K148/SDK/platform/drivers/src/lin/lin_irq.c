/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

/*!
 * @file lin_irq.c
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, A compatible declaration shall be
 * visible when an object or function with external linkage is defined.
 * Folder structure has only C source file for interrupt routine.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.9, An object should be defined at block
 * scope if its identifier only appears in a single function.
 * An object with static storage duration declared at block scope cannot be
 * accessed directly from outside the block.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lin_driver.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (LPUART_INSTANCE_COUNT > 0U)
static void LIN_LPUART0_RxTx_IRQHandler(void)
{
    LIN_DRV_IRQHandler(0U);
}

#ifdef LPUART_ERR_IRQS
static void LIN_LPUART0_ERR_IRQHandler(void)
{
    LIN_DRV_IRQHandler(0U);
}
#endif
#endif /* if (LPUART_INSTANCE_COUNT > 0U) */

#if (LPUART_INSTANCE_COUNT > 1U)
static void LIN_LPUART1_RxTx_IRQHandler(void)
{
    LIN_DRV_IRQHandler(1U);
}

#ifdef LPUART_ERR_IRQS
static void LIN_LPUART1_ERR_IRQHandler(void)
{
    LIN_DRV_IRQHandler(1U);
}
#endif
#endif /* if (LPUART_INSTANCE_COUNT > 1U) */

#if (LPUART_INSTANCE_COUNT > 2U)
static void LIN_LPUART2_RxTx_IRQHandler(void)
{
    LIN_DRV_IRQHandler(2U);
}

#ifdef LPUART_ERR_IRQS
static void LIN_LPUART2_ERR_IRQHandler(void)
{
    LIN_DRV_IRQHandler(2U);
}
#endif
#endif /* if (LPUART_INSTANCE_COUNT > 2U) */

isr_t g_linLpuartIsrs[LPUART_INSTANCE_COUNT] =
{
#if (LPUART_INSTANCE_COUNT > 0U)
    LIN_LPUART0_RxTx_IRQHandler,
#endif
#if (LPUART_INSTANCE_COUNT > 1U)
    LIN_LPUART1_RxTx_IRQHandler,
#endif
#if (LPUART_INSTANCE_COUNT > 2U)
    LIN_LPUART2_RxTx_IRQHandler,
#endif
};

#ifdef LPUART_ERR_IRQS
isr_t g_linLpuartErrIsrs[LPUART_INSTANCE_COUNT] =
{
#if (LPUART_INSTANCE_COUNT > 0U)
    LIN_LPUART0_ERR_IRQHandler,
#endif
#if (LPUART_INSTANCE_COUNT > 1U)
    LIN_LPUART1_ERR_IRQHandler,
#endif
#if (LPUART_INSTANCE_COUNT > 2U)
    LIN_LPUART2_ERR_IRQHandler,
#endif
};
#endif
/******************************************************************************/
/* EOF */
/******************************************************************************/
