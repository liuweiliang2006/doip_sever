/*
 * mqtt_commu_fml.c
 *
 *  Created on: 2021Äê9ÔÂ3ÈÕ
 *      Author: Administrator
 */

#include "mqtt_commu_fml.h"
#include "transport.h"
#include "MQTTPacket.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
//#include "sockets.h"

#include "lwip/opt.h"

#include "lwip/sys.h"
#include "lwip/api.h"

#include "lwip/sockets.h"

#include "mqtt_app.h"

MQTT_USER_MSG  mqtt_user_msg;

uint8_t MQTT_Connect(void)
{
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    uint8_t buf[200];
    int buflen = sizeof(buf);
    int len = 0;
    data.clientID.cstring = CLIENT_ID;
    data.keepAliveInterval = KEEPLIVE_TIME;
    data.username.cstring = USER_NAME;
    data.password.cstring = PASSWORD;
    data.MQTTVersion = MQTT_VERSION;
    data.cleansession = 1;

    len = MQTTSerialize_connect((unsigned char *)buf, buflen, &data);

    transport_sendPacketBuffer(buf, len);

    if (MQTTPacket_read(buf, buflen, transport_getdata) == CONNACK)
    {
        unsigned char sessionPresent, connack_rc;
        if (MQTTDeserialize_connack(&sessionPresent, &connack_rc, buf, buflen) != 1 || connack_rc != 0)
        {
            Printf("errno:%d\n", connack_rc);
            return Connect_NOK;
        }
        else
        {
            Printf("connect sucess\n");
            return Connect_OK;
        }
    }
    else
        Printf("no response\n");
        return Connect_NOTACK;
}

int32_t MQTTSubscribe(int32_t sock,char *topic,enum QoS pos)
{
    static uint32_t PacketID = 0;
    uint16_t packetidbk = 0;
    int32_t conutbk = 0;
    uint8_t buf[100];
    int32_t buflen = sizeof(buf);
    MQTTString topicString = MQTTString_initializer;
    int32_t len;
    int32_t req_qos,qosbk;

    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    FD_ZERO(&readfd);
    FD_SET(sock,&readfd);

    topicString.cstring = (char *)topic;
    req_qos = pos;
    len = MQTTSerialize_subscribe(buf, buflen, 0, PacketID++, 1, &topicString, &req_qos);
    if(transport_sendPacketBuffer(buf, len) < 0)
        return -1;
    if(select(sock+1,&readfd,NULL,NULL,&tv) == 0)
        return -2;
    if(FD_ISSET(sock,&readfd) == 0)
        return -3;
    if(MQTTPacket_read(buf, buflen, transport_getdata) != SUBACK)
        return -4;
    if(MQTTDeserialize_suback(&packetidbk,1, &conutbk, &qosbk, buf, buflen) != 1)
        return -5;
    if((qosbk == 0x80)||(packetidbk != (PacketID-1)))
        return -6;
    return 0;
}


int32_t ReadPacketTimeout(int32_t sock,uint8_t *buf,int32_t buflen,uint32_t timeout)
{
    fd_set readfd;
    struct timeval tv;
    if(timeout != 0)
    {
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(sock,&readfd);

        if(select(sock+1,&readfd,NULL,NULL,&tv) == 0)
            return -1;
        if(FD_ISSET(sock,&readfd) == 0)
            return -1;
    }
    return MQTTPacket_read(buf, buflen, transport_getdata);
}

int32_t MQTT_PingReq(int32_t sock)
{
    int32_t len;
    uint8_t buf[200];
    int32_t buflen = sizeof(buf);
    fd_set readfd;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    FD_ZERO(&readfd);
    FD_SET(sock,&readfd);

    len = MQTTSerialize_pingreq(buf, buflen);
    transport_sendPacketBuffer(buf, len);
    if(select(sock+1,&readfd,NULL,NULL,&tv) == 0)
        return -1;
    if(FD_ISSET(sock,&readfd) == 0)
        return -2;

    if(MQTTPacket_read(buf, buflen, transport_getdata) != PINGRESP)
        return -3;
    return 0;

}
void deliverMessage(MQTTString  *TopicName,MQTTMessage *msg,MQTT_USER_MSG *mqtt_user_msg)
{
        mqtt_user_msg->msgqos = msg->qos;
        memcpy(mqtt_user_msg->msg,msg->payload,msg->payloadlen);
        mqtt_user_msg->msg[msg->payloadlen] = 0;
        mqtt_user_msg->msglenth = msg->payloadlen;
        memcpy((char *)mqtt_user_msg->topic,TopicName->lenstring.data,TopicName->lenstring.len);
        mqtt_user_msg->topic[TopicName->lenstring.len] = 0;
        mqtt_user_msg->packetid = msg->id;
        mqtt_user_msg->valid = 1;
}

void UserMsgCtl(MQTT_USER_MSG  *msg)
{
    if(msg->msglenth > 2)
    {
        switch(msg->msgqos)
        {
          case 0:
//              Printf("MQTT>>QoS0\n");
              break;
          case 1:
//              Printf("MQTT>>QoS1\n");
              break;
          case 2:
//              Printf("MQTT>>QoS2\n");
              break;
          default:
//              Printf("MQTT>>error\n");
              break;
         }
//         Printf("MQTT>>Topic%s\n",msg->topic);
//         Printf("MQTT>>Msg%s\n",msg->msg);
//         Printf("MQTT>>Len%d\n",msg->msglenth);
        Proscess(msg->msg);
    }
      msg->valid  = 0;
}

void mqtt_pktype_ctl(uint8_t packtype,uint8_t *buf,uint32_t buflen)
{
    MQTTMessage msg;
    int32_t rc;
    MQTTString receivedTopic;
    uint32_t len;
    switch(packtype)
    {
        case PUBLISH:
            if(MQTTDeserialize_publish(&msg.dup,(int*)&msg.qos, &msg.retained, &msg.id, &receivedTopic,
                (unsigned char **)&msg.payload, &msg.payloadlen, buf, buflen) != 1)
                return;
            deliverMessage(&receivedTopic,&msg,&mqtt_user_msg);

            if(msg.qos == QOS0)
            {
                UserMsgCtl(&mqtt_user_msg);
                return;
            }
            if(msg.qos == QOS1)
            {
                len =MQTTSerialize_puback(buf,buflen,mqtt_user_msg.packetid);
                if(len == 0)
                    return;
                if(transport_sendPacketBuffer(buf,len)<0)
                    return;
                UserMsgCtl(&mqtt_user_msg);
                    return;
            }

            if(msg.qos == QOS2)
            {
                len = MQTTSerialize_ack(buf, buflen, PUBREC, 0, mqtt_user_msg.packetid);
                if(len == 0)
                    return;
                transport_sendPacketBuffer(buf,len);
            }
            break;
        case  PUBREL:
            rc = MQTTDeserialize_ack(&msg.type,&msg.dup, &msg.id, buf,buflen);
            if((rc != 1)||(msg.type != PUBREL)||(msg.id != mqtt_user_msg.packetid))
                return ;
            if(mqtt_user_msg.valid == 1)
            {
                UserMsgCtl(&mqtt_user_msg);
            }
            len = MQTTSerialize_pubcomp(buf,buflen,msg.id);
            if(len == 0)
                return;
            transport_sendPacketBuffer(buf,len);
            break;
        case   PUBACK:
            break;
        case   PUBREC:
            break;
        case   PUBCOMP:
            break;
        default:
            break;
    }
}

uint16_t GetNextPackID(void)
{
    static uint16_t pubpacketid = 0;
    return pubpacketid++;
}

int32_t WaitForPacket(int32_t sock,uint8_t packettype,uint8_t times)
{
    int32_t type;
    uint8_t buf[MSG_MAX_LEN];
    uint8_t n = 0;
    int32_t buflen = sizeof(buf);
    do
    {
        type = ReadPacketTimeout(sock,buf,buflen,2);
        if(type != -1)
            mqtt_pktype_ctl(type,buf,buflen);
        n++;
    }while((type != packettype)&&(n < times));
    if(type == packettype)
        return 0;
    else
        return -1;
}

int32_t MQTTMsgPublish(int32_t sock, char *topic, int8_t qos, uint8_t* msg)
{
    int8_t retained = 0;
    uint32_t msg_len;
    uint8_t buf[MSG_MAX_LEN] = {0};
    int32_t buflen = sizeof(buf),len;
    MQTTString topicString = MQTTString_initializer;
    uint16_t packid = 0,packetidbk;

    topicString.cstring = (char *)topic;
    if((qos == QOS1)||(qos == QOS2))
    {
        packid = GetNextPackID();
    }
    else
    {
        qos = QOS0;
        retained = 0;
        packid = 0;
    }

    msg_len = strlen((char *)msg);

    len = MQTTSerialize_publish(buf, buflen, 0, qos, retained, packid, topicString, (unsigned char*)msg, msg_len);
    if(len <= 0)
        return -1;
    if(transport_sendPacketBuffer(buf, len) < 0)
        return -2;

    if(qos == QOS0)
    {
        return 0;
    }

    if(qos == QOS1)
    {
        if(WaitForPacket(sock,PUBACK,5) < 0)
            return -3;
        return 1;
    }

    if(qos == QOS2)
    {
        if(WaitForPacket(sock,PUBREC,5) < 0)
            return -3;
        len = MQTTSerialize_pubrel(buf, buflen,0, packetidbk);
        if(len == 0)
            return -4;
        if(transport_sendPacketBuffer(buf, len) < 0)
            return -6;
        if(WaitForPacket(sock,PUBREC,5) < 0)
            return -7;
        return 2;
    }
    return -8;
}
