/*
 * pins_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"
pin_settings_config_t g_pin_mux_InitConfigArr_canhalt[1] =
{
    {
        .base          = PORTE,
        .pinPortIdx    = 4u,
        .pullConfig    = PORT_INTERNAL_PULL_UP_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_AS_GPIO,
        .pinLock       = false,
        .intConfig     = PORT_INT_FALLING_EDGE,
        .clearIntFlag  = true,
        .gpioBase      = PTE,
        .direction     = GPIO_INPUT_DIRECTION,
        .digitalFilter = false,
    },
//    {
//        .base          = PORTA,
//        .pinPortIdx    = 6u,
//        .pullConfig    = PORT_INTERNAL_PULL_UP_ENABLED,
//        .passiveFilter = false,
//        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
//        .mux           = PORT_MUX_AS_GPIO,
//        .pinLock       = false,
//        .intConfig     = PORT_INT_FALLING_EDGE,
//        .clearIntFlag  = true,
//        .gpioBase      = PTA,
//        .direction     = GPIO_INPUT_DIRECTION,
//        .digitalFilter = false,
//    },
};
pin_settings_config_t g_pin_mux_InitConfigArr_canwake[1] =
{
    {
        .base          = PORTE,
        .pinPortIdx    = 4u,
        .pullConfig    = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect   = PORT_LOW_DRIVE_STRENGTH,
        .mux           = PORT_MUX_ALT5,
        .pinLock       = false,
        .intConfig     = PORT_INT_RISING_EDGE,
        .clearIntFlag  = true,
        .gpioBase      = NULL,
        .digitalFilter = false,
    },
};
status_t pins_init__hal_api(void)
{
    return PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
}
status_t pins_set_canrx_halt_api(void)
{
    return PINS_DRV_Init(1, g_pin_mux_InitConfigArr_canhalt);
}
status_t pins_set_canrx_wake_api(void)
{
    return PINS_DRV_Init(1, g_pin_mux_InitConfigArr_canwake);
}
void pins_set_pins_direction_hal_api(GPIO_Type * const base,pins_channel_type_t pins)
{
    PINS_DRV_SetPinsDirection(base,pins);
}
void pins_set_pins_hal_api(GPIO_Type * const base,pins_channel_type_t pins)
{
    PINS_DRV_SetPins(base,pins);
}
void pins_clear_pins_hal_api(GPIO_Type * const base,pins_channel_type_t pins)
{
    PINS_DRV_ClearPins(base,pins);
}
void pins_toggle_pins_hal_api(GPIO_Type * const base,
                         pins_channel_type_t pins)
{
    PINS_DRV_TogglePins(base, pins);
}
uint32_t pins_read_pins_hal_api(const GPIO_Type * const base)
{
    return PINS_DRV_ReadPins(base);
}


