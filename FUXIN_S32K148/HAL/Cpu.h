/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.h
**     Project     : FUXIN_S32K148
**     Processor   : S32K148_176
**     Component   : S32K148_176
**     Version     : Component 01.197, Driver 01.00, CPU db: 3.00.000
**     Datasheet   : S32K14XRM Rev. 2, 02/2017
**     Compiler    : GNU C Compiler
**     Date/Time   : 2022-03-17, 14:54, # CodeGen: 0
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         SystemInit            - void SystemInit(void);
**         SystemCoreClockUpdate - void SystemCoreClockUpdate(void);
**         SystemSoftwareReset   - void SystemSoftwareReset(void);
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc. 
**     Copyright 2016-2017 NXP 
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file Cpu.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

#ifndef Cpu_H
#define Cpu_H


/* MODULE Cpu. */


/*Include shared modules, which are used for whole project*/
#include "device_registers.h"

#include "interrupt_manager.h"
#include "clock.h"
#include "osif.h"
#include "edma_driver.h"
#include "lpspi_master_driver.h"
#include "lpspi_slave_driver.h"
#include "lpspi_shared_function.h"
#include "lpuart_driver.h"
#include "rtc_driver.h"
#include "flash_driver.h"
#include "power_manager.h"
#include "lpit_driver.h"
#include "ftm_mc_driver.h"
#include "adc_pal.h"
#include "i2c_pal.h"
#include "lin_driver.h"
#include "lin_common_api.h"
#include "wdog_driver.h"
#include "enet_driver.h"
#include "system_S32K148.h"

/* Including needed modules to compile this module/procedure */
#include "pin_mux.h"
#include "clockMan1.h"
#include "FreeRTOS.h"
#include "master.h"
#include "dmaController1.h"
#include "slave.h"
#include "lpuart1.h"
#include "rtcTimer1.h"
#include "Flash1.h"
#include "pwrMan1.h"
#include "lpit1.h"
#include "flexTimer_mc1.h"
#include "adc_pal1.h"
#include "i2c1.h"
#include "lin_cfg.h"
#include "lin1.h"
#include "UARTSOC.h"
#include "flexTimer_mc2.h"
#include "watchdog1.h"
#include "ethernet1.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TBD Cpu configuration will be declared here. */




#ifdef __cplusplus
}
#endif

/* END Cpu. */

#endif
/* Cpu_H */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
