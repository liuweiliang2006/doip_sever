/*
 * cjson_process_fml.c
 *
 *  Created on: 2021Äê9ÔÂ17ÈÕ
 *      Author: Administrator
 */

#include "cjson_process_fml.h"
#include "mqtt_app.h"



void Proscess(void* data)
{
  cJSON *root,*json_name,*json_temp_num,*json_hum_num;
  cJSON * ch, *key_ch;
  uint8_t size = 0;
  uint8_t kye_size;
  uint8_t i , j;

  root = cJSON_Parse((char*)data);
  size = cJSON_GetArraySize(root);

  json_name = cJSON_GetObjectItem(root,"id");
  CjsonMsg.id = json_name->valueint;
//  Printf("id:%d\r\n",json_name->valueint);

  json_name = cJSON_GetObjectItem(root,"testdata");
  memcpy(CjsonMsg.data,json_name->valuestring,1024);
//  ch = root->child;
//  for (i = 0; i<size;i++)
//  {
//      Printf("[num=%d] [type=%d]\n", i, ch->type);
//      ch = ch->next;client.publish
//  }
//  ch = root->child;
//  for(i = 0; i < size; i++){
//      if(cJSON_IsObject(ch)){
//          kye_size = cJSON_GetArraySize(ch);
//          key_ch = ch->child;
//          Printf("[num=%d          ]\n", i);
//          Printf("[key=%s]\n", ch->string);
//          Printf("----------------------\n");
//          for(j = 0; j < kye_size; j++){
//              Printf("[value_num=%d          ]\n", j);
//              Printf("[key=%s]\n[value=%s]\n", key_ch->string, key_ch->valuestring);
//              key_ch = key_ch->next;
//          }
//          Printf("----------------------\n");
//
//      }else{
//          Printf("[num=%d          ]\n", i);
//          Printf("[key=%s]\n[value=%s]\n", ch->string, ch->valuestring);
//      }
//      ch = ch->next;
//  }


  cJSON_Delete(root);
}


