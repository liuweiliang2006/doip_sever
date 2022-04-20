/*
 * fatfs_demo.h
 *
 *  Created on: 2021Äê5ÔÂ19ÈÕ
 *      Author: Administrator
 */

#ifndef FATFS_FATFS_DEMO_H_
#define FATFS_FATFS_DEMO_H_

#define FILESYS_TEST  0
//int fatfs_test(void);
extern void fatfsTest_Task( void *pvParameters );

extern TaskHandle_t fatfsTask_Handle;

#endif /* FATFS_FATFS_DEMO_H_ */
