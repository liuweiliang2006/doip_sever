/*
 * mqtt_app.h
 *
 *  Created on: 2021Äê9ÔÂ1ÈÕ
 *      Author: Administrator
 */

#ifndef MQTT_MQTT_APP_H_
#define MQTT_MQTT_APP_H_

#define   HOST_NAME       "192.168.0.2"
#define   HOST_PORT     61613
//#define   HOST_NAME       "a1d0Yb0wigV.iot-as-mqtt.cn-shanghai.aliyuncs.com" 101.133.196.109
//#define   HOST_NAME       "101.133.196.109"
//#define   HOST_PORT     1883

//#define   USER_NAME     "admin"
//#define   PASSWORD      "password"
//#define   TOPIC         "lwltest1"
void mqtt_init(void);

extern uint16_t app_rec_data;

typedef struct stCjsonMsg
{
    int id;
    char data[2048];
};
extern struct stCjsonMsg CjsonMsg;

#endif /* MQTT_MQTT_APP_H_ */
