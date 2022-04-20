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

#ifndef _BOARD_DEFINES_H_
#define _BOARD_DEFINES_H_

#include <stdint.h>
#include <stdbool.h>

/* This file defines the specific ports and pins for Evaluation Board and
 * Validation Board. To use with Validation Board uncomment the following 
 * line
 */
 
#define EVB 

#ifdef EVB
    #define LED1            21U
    #define LED2            22U
    #define SOCLINE            17U
    #define LED_GPIO        PTE
    #define LED_PORT        PORTE
    #define LED_PORT_PCC    PCC_PORTE_CLOCK
    #define BTN_GPIO        PTC
    #define BTN_PIN         13U
    #define BTN_PORT        PORTC
    #define BTN_PORT_PCC    PCC_PORTC_CLOCK
    #define BTN_PORT_IRQn   PORTC_IRQn
    #define LPIT_CHANNEL        0UL
    #define LPIT_Channel_IRQn   LPIT0_Ch0_IRQn
    #define LPIT_CHANNEL1        1UL
    #define LPIT_Channel_IRQn1 LPIT0_Ch1_IRQn
    #define LPIT_CHANNEL2        2UL
    #define LPIT_Channel_IRQn2 LPIT0_Ch2_IRQn
    #define UARTlog 0

    #define HSRUN (0u) /* High speed run      */
    #define RUN   (1u) /* Run                 */
    #define VLPR  (2u) /* Very low power run  */
    #define STOP1 (3u) /* Stop option 1       */
    #define STOP2 (4u) /* Stop option 2       */
    #define VLPS  (5u) /* Very low power stop */

#else
    #define LED1            0U
    #define LED2            1U
    #define LED_GPIO        PTC
    #define LED_PORT        PORTC
    #define LED_PORT_PCC    PCC_PORTC_CLOCK
    #define BTN_GPIO        PTC
    #define BTN_PIN         13U
    #define BTN_PORT        PORTC
    #define BTN_PORT_PCC    PCC_PORTC_CLOCK
    #define BTN_PORT_IRQn   PORTC_IRQn
#endif

#include "pins_driver.h"

#endif
