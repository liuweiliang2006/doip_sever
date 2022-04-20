/*
 * pwr_manage_test.h
 *
 *  Created on: 2021Äê7ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef PWR_MANAGE_TEST_PWR_MANAGE_TEST_H_
#define PWR_MANAGE_TEST_PWR_MANAGE_TEST_H_

#define PWR_TEST (0)

extern QueueHandle_t pwrManageQueue;
extern void pwrmanage_test_task( void *pvParameters );

#endif /* PWR_MANAGE_TEST_PWR_MANAGE_TEST_H_ */
