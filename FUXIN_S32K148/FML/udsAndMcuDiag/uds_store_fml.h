/*
 * flash_fml.h
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef UDSSTORE_FLASH_FML_H_
#define UDSSTORE_FLASH_FML_H_
#include "Cpu.h"

void write_DIDdata_to_EEflash_fml(void);
void read_udsData_fml_api(void);
void read_dtcData_fml_api(void);
void check_did_dtc_status_fml_api(uint8_t status);
void read_DTCdata_from_dflash_fml(void);
status_t write_version_fml(uint8_t *ptr,uint8_t len,uint32_t address);



#endif /* UDSSTORE_FLASH_FML_H_ */
