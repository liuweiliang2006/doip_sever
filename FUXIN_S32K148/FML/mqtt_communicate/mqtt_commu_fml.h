/*
 * mqtt_commu_fml.h
 *
 *  Created on: 2021年9月3日
 *      Author: Administrator
 */

#ifndef MQTT_COMMUNICATE_MQTT_COMMU_FML_H_
#define MQTT_COMMUNICATE_MQTT_COMMU_FML_H_
#include <stdint.h>

//#define CLIENT_ID "12345|securemode=3,signmethod=hmacsha1|"
//#define KEEPLIVE_TIME 50
//#define USER_NAME "fire_temp_hum&a1d0Yb0wigV"
//#define PASSWORD "7B3D00AD8FD99808A1448AF3DD2EFF6A2E3FD872"
//#define MQTT_VERSION 4
//#define TOPIC  "/a1d0Yb0wigV/fire_temp_hum/user/temp_num"

#define CLIENT_ID "Client555"
#define KEEPLIVE_TIME 60
#define USER_NAME "admin"
#define PASSWORD "password"
#define MQTT_VERSION 4
#define TOPIC  "icm/reply/hu/upgrade"
#define TOPIC1  "icm/reply/hu/display"
#define PUBTOPIC  "PUB_TOPIC"



#define   MSG_MAX_LEN     2048
#define   MSG_TOPIC_LEN   50

enum MQTT_Connect
{
  Connect_OK = 0,
  Connect_NOK,
  Connect_NOTACK
};

enum QoS
{ QOS0 = 0,
  QOS1,
  QOS2
};

typedef struct __MQTTMessage
{
    uint32_t qos;
    uint8_t retained;
    uint8_t dup;
    uint16_t id;
    uint8_t type;
    void *payload;
    int32_t payloadlen;
}MQTTMessage;

typedef struct __MQTT_MSG
{
    uint8_t  msgqos;
    uint8_t  msg[MSG_MAX_LEN];
    uint32_t msglenth;
    uint8_t  topic[MSG_TOPIC_LEN];
    uint16_t packetid;
    uint8_t  valid;
}MQTT_USER_MSG;

uint8_t MQTT_Connect(void);
int32_t MQTTSubscribe(int32_t sock,char *topic,enum QoS pos);
int32_t ReadPacketTimeout(int32_t sock,uint8_t *buf,int32_t buflen,uint32_t timeout);
int32_t MQTT_PingReq(int32_t sock);
void mqtt_pktype_ctl(uint8_t packtype,uint8_t *buf,uint32_t buflen);
int32_t MQTTMsgPublish(int32_t sock, char *topic, int8_t qos, uint8_t* msg);

extern MQTT_USER_MSG  mqtt_user_msg;
#endif /* MQTT_COMMUNICATE_MQTT_COMMU_FML_H_ */
