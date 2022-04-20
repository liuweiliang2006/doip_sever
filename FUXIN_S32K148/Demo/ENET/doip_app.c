/*
 * doip_app.c
 *
 *  Created on: 2022年3月21日
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
#include "SoAd.h"
static ip_addr_t dstaddr;
#define SOCK_TARGET_HOST4  "192.168.0.2"
#define LOCAL_PORT  13400
#define RECV_DATA (100)

void UDP_test_func()
{
	  int sock = -1;
	  char *recv_data;
	  struct sockaddr_in udp_addr,seraddr;
	  int recv_data_len;
	  socklen_t addrlen;

	  Printf("本地端口号是%d\n\n",LOCAL_PORT);

	  while(1)
	  {
	    recv_data = (char *)pvPortMalloc(RECV_DATA);
	    if (recv_data == NULL)
	    {
	        Printf("No memory\n");
	        goto __exit;
	    }

	    sock = socket(AF_INET, SOCK_DGRAM, 0);
	    if (sock < 0)
	    {
	      Printf("Socket error\n");
	      goto __exit;
	    }

	    udp_addr.sin_family = AF_INET;
	    udp_addr.sin_addr.s_addr = INADDR_ANY;
	    udp_addr.sin_port = htons(LOCAL_PORT);
	    memset(&(udp_addr.sin_zero), 0, sizeof(udp_addr.sin_zero));

	    if (bind(sock, (struct sockaddr *)&udp_addr, sizeof(struct sockaddr)) == -1)
	    {
	      Printf("Unable to bind\n");
	      goto __exit;
	    }
	    addrlen = sizeof(struct sockaddr);
	    while(1)
	    {
	      recv_data_len=recvfrom(sock,recv_data,
	                             RECV_DATA,0,
	                             (struct sockaddr*)&seraddr,
	                             &addrlen);

	      /*显示发送端的IP地址*/
	      Printf("receive from %s\n",inet_ntoa(seraddr.sin_addr));

	      /*显示发送端发来的字串*/
	      Printf("recevce:%s",recv_data);

	      /*将字串返回给发送端*/
	      sendto(sock,recv_data,
	             recv_data_len,0,
	             (struct sockaddr*)&seraddr,
	             addrlen);
	    }

	__exit:
	    if (sock >= 0) closesocket(sock);
	    if (recv_data) free(recv_data);
	  }
}

void TCP_test_func()
{
	  int sock = -1,connected;
	  char *recv_data;
	  struct sockaddr_in server_addr,client_addr;
	  socklen_t sin_size;
	  int recv_data_len;

	  Printf("本地端口号是%d\n\n",LOCAL_PORT);

	  recv_data = (char *)pvPortMalloc(RECV_DATA);
	  if (recv_data == NULL)
	  {
	      Printf("No memory\n");
	      goto __exit;
	  }

	  sock = socket(AF_INET, SOCK_STREAM, 0);
	  if (sock < 0)
	  {
	      Printf("Socket error\n");
	      goto __exit;
	  }

	  server_addr.sin_family = AF_INET;
	  server_addr.sin_addr.s_addr = INADDR_ANY;
	  server_addr.sin_port = htons(LOCAL_PORT);
	  memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

	  if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	  {
	      Printf("Unable to bind\n");
	      goto __exit;
	  }

	  if (listen(sock, 5) == -1)
	  {
	      Printf("Listen error\n");
	      goto __exit;
	  }

	  while(1)
	  {
	    sin_size = sizeof(struct sockaddr_in);

	    connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

	    Printf("new client connected from (%s, %d)\n",
	            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	    {
	      int flag = 1;

	      setsockopt(connected,
	                 IPPROTO_TCP,     /* set option at TCP level */
	                 TCP_NODELAY,     /* name of option */
	                 (void *) &flag,  /* the cast is historical cruft */
	                 sizeof(int));    /* length of option value */
	    }

	    while(1)
	    {
	      recv_data_len = recv(connected, recv_data, RECV_DATA, 0);

	      if (recv_data_len <= 0)
	        break;

	      Printf("recv %d len data\n",recv_data_len);

	      write(connected,recv_data,recv_data_len);

	    }
	    if (connected >= 0)
	      closesocket(connected);

	    connected = -1;
	  }
	__exit:
	  if (sock >= 0) closesocket(sock);
	  if (recv_data) free(recv_data);
}

void doip_loop_task( void *pvParameters )
{
//    unsigned long ulReceivedValue;
//    uint16_t len;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    TickType_t xNextWakeTime;

    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();
    while(1)
    {
    	Printf("doip loop\r\n");
    	vTaskDelayUntil(&xNextWakeTime, (100/portTICK_RATE_MS));

    	SoAd_MainFunction();
    	DoIp_MainFunction();
//    	TCP_test_func();
//    	UDP_test_func();

    }
}



void doip_task_init(void)
{

	  IP_SET_TYPE_VAL(dstaddr, IPADDR_TYPE_V4);
	  ip4addr_aton(SOCK_TARGET_HOST4, ip_2_ip4(&dstaddr));
	  SoAd_Init();
	  DoIp_wait_time();
//	  ip4addr_aton(SOCK_TARGET_HOST4, ip_2_ip4(&dstaddr));
//    xTaskCreate( MQTT_test_task, "MQTT_test", 12*configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	  sys_thread_new("creat_doip", doip_loop_task, NULL, 400, DEFAULT_THREAD_PRIO);
//    sys_thread_new("MQTT_send", MQTT_send, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
}
