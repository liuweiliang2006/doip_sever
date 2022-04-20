#ifndef __TRANSPORT_H
#define __TRANSPORT_H
#include <stdint.h>
#include "lwip/sockets.h"
int32_t transport_sendPacketBuffer( uint8_t* buf, int32_t buflen);

int32_t transport_getdata(uint8_t* buf, int32_t count);

int32_t transport_open(ip_addr_t *ipaddr, int32_t port);

int32_t transport_close(void);



#endif
