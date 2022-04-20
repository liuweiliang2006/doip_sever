/*
 * mqtt_app.c
 *
 *  Created on: 2021Äê9ÔÂ1ÈÕ
 *      Author: Administrator
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "cJSON.h"
#include "mqtt_app.h"
#include "MQTTPacket.h"
#include "transport.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

#include "lwip/sockets.h"
#include "mqtt_commu_fml.h"

#define DES_IP "192.168.0.12"

#define PUBTOPIC_HEAD "icm/test/PubTopic"
#define TOPIC_HEAD "icm/test/topic"
#define TOPIC_NUM  100
int32_t MQTT_Socket = 0;

struct stCjsonMsg CjsonMsg;

uint8_t Sub_Topic_Fun(void)
{
    char topic_buf[100];
    char topic_num[5];
    uint16_t i = 0;
    int ret = 0;

    for (i = 0; i < TOPIC_NUM; i++)
    {
        memset(topic_buf,0,100);
        memset(topic_num,0,5);
        sprintf(topic_num,"%d",i);
        strcat(topic_buf,TOPIC_HEAD);
        strcat(topic_buf,topic_num);
//        Printf("%s\r\n",topic_buf);

        if(MQTTSubscribe(MQTT_Socket,(char *)topic_buf,QOS1) < 0)
        {
            Printf("Sub failed\r\n");
            transport_close();
            ret = 1;
            break;
//            goto MQTT_START;
        }
    }
    return ret;
}


int32_t pubFunc(void)
{
    char topic_buf[100] = {0};
    char topic_num[5] = {0};
    char *p=NULL;
    int32_t ret = 0;

    cJSON* cjson_test = NULL;
    cJSON* cjson_data = NULL;

    cjson_test = cJSON_CreateObject();
    if (cjson_test == NULL)
    {
        return NULL;
    }


    cJSON_AddStringToObject(cjson_test, "action","tabSequence");
//    cJSON_AddNumberToObject(cjson_test, "id", 100.1);
    cJSON_AddNumberToObject(cjson_test, "id", CjsonMsg.id);
    cJSON_AddStringToObject(cjson_test, "testdata",CjsonMsg.data);
    cjson_data = cJSON_CreateObject();
    cJSON_AddNumberToObject(cjson_data, "first", CjsonMsg.id*10);
    cJSON_AddNumberToObject(cjson_data, "second", CjsonMsg.id*20);
    cJSON_AddNumberToObject(cjson_data, "third", CjsonMsg.id*30);
    cJSON_AddNumberToObject(cjson_data, "fourth", CjsonMsg.id*40);
    cJSON_AddNumberToObject(cjson_data, "fifth", CjsonMsg.id*50);
    cJSON_AddItemToObject(cjson_test,"data",cjson_data);

    p = cJSON_Print(cjson_test);
    sprintf(topic_num,"%d",CjsonMsg.id);
    strcat(topic_buf,PUBTOPIC_HEAD);
    strcat(topic_buf,topic_num);

    ret = MQTTMsgPublish(MQTT_Socket,(char*)topic_buf,QOS1,(uint8_t*)p);
//    p = pvPortMalloc(100);
//    memset(p,1,100);
    vPortFree(p);
//    cJSON_Delete(cjson_data);
    cJSON_Delete(cjson_test);
    CjsonMsg.id =0;

    return ret;
}

void Client_Connect(void)
{
    char* host_ip;
    ip_addr_t dstaddr;
    ip4_addr_t dns_ip;
    char hostname[]="www.baidu.com";
    err_t     err = ERR_OK;
//    netconn_gethostbyname(HOST_NAME, &dns_ip);
//    host_ip = ip_ntoa(&dns_ip);

    IP_SET_TYPE_VAL(dstaddr, IPADDR_TYPE_V4);
    ip4addr_aton(HOST_NAME, ip_2_ip4(&dstaddr));
//    host_ip = ip4addr_ntoa(&dns_ip);
    MQTT_START:
    while(1)
    {
        Printf("open...\r\n");
        MQTT_Socket = transport_open(&dstaddr,HOST_PORT);
        if(MQTT_Socket >= 0)
        {
            break;
        }
        vTaskDelay(3000);
    }

    if(MQTT_Connect() != Connect_OK)
    {
        Printf("re connect\r\n");
        transport_close();
        goto MQTT_START;
    }

    if(Sub_Topic_Fun() == 1)
    {
        goto MQTT_START;
    }
    Printf("sub done\r\n");
}

uint16_t app_rec_data = 0;
void MQTT_test_task( void *pvParameters )
{
    TickType_t xNextWakeTime;
    xNextWakeTime = xTaskGetTickCount();

    uint8_t no_mqtt_msg_exchange = 1;
    static uint32_t count = 0,pwrmode= 0;
    uint32_t curtick;
    uint8_t buf[MSG_MAX_LEN];
    int32_t buflen = sizeof(buf);
    int32_t type;
    fd_set readfd;
    uint8_t ret;
//    TaskHandle_t TaskHandle;
//    TaskStatus_t TaskStatus;

    struct timeval tv;
    static uint32_t runtimes = 0;
    tv.tv_sec = 0;
    tv.tv_usec = 10;

    MQTT_START:
    Client_Connect();
    Printf("connect ...");
    curtick = get_tick_api();
    while(1)
    {
//        TaskHandle=xTaskGetHandle("MQTT_test");
        runtimes++;
//        vTaskDelayUntil(&xNextWakeTime, (100/portTICK_RATE_MS));

        no_mqtt_msg_exchange = 1;

        FD_ZERO(&readfd);
        FD_SET(MQTT_Socket,&readfd);

        select(MQTT_Socket+1,&readfd,NULL,NULL,&tv);
        if(FD_ISSET(MQTT_Socket,&readfd) != 0)
        {
            type = ReadPacketTimeout(MQTT_Socket,buf,buflen,50);
            if(type != -1)
            {
                mqtt_pktype_ctl(type,buf,buflen);
//                Printf("_____\r\n");
//                Printf("%d\r\n",xPortGetFreeHeapSize());
//                Printf("%d\r\n",xPortGetMinimumEverFreeHeapSize()); //heap3/4
                no_mqtt_msg_exchange = 0;
                curtick = get_tick_api();

                ret =pubFunc();
//                Printf("%d\r\n",xPortGetMinimumEverFreeHeapSize());//heap3/4
//                Printf("%d\r\n",xPortGetFreeHeapSize());
//                Printf("______\r\n");
//                ret = MQTTMsgPublish(MQTT_Socket,(char*)PUBTOPIC,QOS0,(uint8_t*)mqtt_user_msg.msg);
                if (ret >= 0)
                {
                    no_mqtt_msg_exchange = 0;
                    curtick = xTaskGetTickCount();
                }
            }
        }

        if((get_tick_api() - curtick) >(KEEPLIVE_TIME/2*1000))
        {
            curtick = get_tick_api();
            if(no_mqtt_msg_exchange == 0)
            {
                continue;
            }

            if(MQTT_PingReq(MQTT_Socket) < 0)
            {
//               Printf("Ping failed....\r\n");
               goto CLOSE;
            }
            no_mqtt_msg_exchange = 0;
        }
    }
    CLOSE:
    Printf("close...\r\n");
    transport_close();
    Printf("Start...\r\n");
    goto MQTT_START;
}

void MQTT_send( void *pvParameters )
{
    TickType_t xNextWakeTime;
    int32_t ret;
    uint8_t no_mqtt_msg_exchange = 1;
    uint32_t curtick;
    uint8_t res;

    xNextWakeTime = xTaskGetTickCount();
    MQTT_SEND_START:
    while(1)
    {
        char* p = "123456789";
        ret = MQTTMsgPublish(MQTT_Socket,(char*)TOPIC,QOS0,(uint8_t*)p);
        if (ret >= 0)
        {
            no_mqtt_msg_exchange = 0;
            curtick = xTaskGetTickCount();
        }

        if((xTaskGetTickCount() - curtick) >(KEEPLIVE_TIME/2*1000))
        {
            curtick = xTaskGetTickCount();
            if(no_mqtt_msg_exchange == 0)
            {
                continue;
            }
            if(MQTT_PingReq(MQTT_Socket) < 0)
            {
                goto MQTT_SEND_CLOSE;
            }
            no_mqtt_msg_exchange = 0;
        }
        vTaskDelayUntil(&xNextWakeTime, (5000/portTICK_RATE_MS));
    }
    MQTT_SEND_CLOSE:
    transport_close();
    Client_Connect();
    goto MQTT_SEND_START;
}

void mqtt_init(void)
{
//    xTaskCreate( MQTT_test_task, "MQTT_test", 12*configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    sys_thread_new("MQTT_test", MQTT_test_task, NULL, 400, DEFAULT_THREAD_PRIO);
//    sys_thread_new("MQTT_send", MQTT_send, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
