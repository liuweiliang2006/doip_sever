/*
 * can_fml.h
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef COMMUNICATION_CAN_FML_H_
#define COMMUNICATION_CAN_FML_H_
#include "Cpu.h"

typedef enum
{
    CANFML_CS_UNINIT = 0,
    CANFML_CS_SLEEP = 1,
    CANFML_CS_STARTED = 2,
    CANFML_CS_STOPPED = 3
}canControllerModeTypeFml;
extern uint8_t canRingLock;
uint8_t read_can_Ringbuffer_fml_api(void);
void push_can_data_fml(uint16_t id,uint8_t *ptr);
void can_run_function_fml_api(void);
void canstack_init_fml_api(void);
void canstack_wakeup_init_fml_api(void);
uint8_t set_can_controller_mode_fml_api(canControllerModeTypeFml mode);
void can_controller_init_fml_api(uint8_t channel);


#endif /* COMMUNICATION_CAN_FML_H_ */
