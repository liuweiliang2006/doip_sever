/*
 * pubsub_demo.h
 *
 *  Created on: 2021Äê6ÔÂ3ÈÕ
 *      Author: Administrator
 */

#ifndef PUBSUB_PUBSUB_DEMO_H_
#define PUBSUB_PUBSUB_DEMO_H_


#include "event_groups.h"
//#define PUBSUB_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2 )
//#define PUBSUBL_STACK_SIZE                 ( ( unsigned short ) 60 )
#define PUBSUB_TEST 0

extern TaskHandle_t PubsubTask_Handle;  //pubsub task instance
extern void pubsub_Task( void *pvParameters );
extern EventGroupHandle_t pubEventGroup;

enum subtasknum{
    SUBTASK1 = 1,
    SUBTASK2 = 2,
    SUBTASK3 = 3,
    SUBTASK4 = 4,
    SUBTASK5 = 5,
    SUBTASK6 = 6,
    SUBTASK7 = 7,
    SUBTASK8 = 8,
    SUBTASK9 = 9,
    SUBTASK10 = 10,
    SUBTASK11 = 11,
    SUBTASK12 = 12,
    SUBTASK13 = 13,
    SUBTASK14 = 14,
    SUBTASK15 = 15,
    SUPEVENT = 0xff,
    RECERROR = 100
};

#endif /* PUBSUB_PUBSUB_DEMO_H_ */
