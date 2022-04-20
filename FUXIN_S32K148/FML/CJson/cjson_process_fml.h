/*
 * cjson_process_fml.h
 *
 *  Created on: 2021��9��17��
 *      Author: Administrator
 */

#ifndef CJSON_CJSON_PROCESS_FML_H_
#define CJSON_CJSON_PROCESS_FML_H_

#include "cJSON.h"
#include "stdint.h"

#define   NAME            "name"
#define   TEMP_NUM        "temp"
#define   HUM_NUM         "hum"

#define   DEFAULT_NAME          "fire"
#define   DEFAULT_TEMP_NUM       25.0
#define   DEFAULT_HUM_NUM        50.0


#define   UPDATE_SUCCESS       1
#define   UPDATE_FAIL          0

//cJSON* cJSON_Data_Init(void);
//uint8_t cJSON_Update(const cJSON * const object,const char * const string,void * d);
void Proscess(void* data);
#endif /* CJSON_CJSON_PROCESS_FML_H_ */
