#include "transport.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"
#include "string.h"

static int mysock;

int32_t transport_sendPacketBuffer( uint8_t* buf, int32_t buflen)
{
    int32_t rc;
    rc = write(mysock, buf, buflen);
    return rc;
}

int32_t transport_getdata(uint8_t* buf, int32_t count)
{
    int32_t rc;
  rc = recv(mysock, buf, count, 0);
    return rc;
}

int32_t transport_open(ip_addr_t *ipaddr, int32_t port)
{
    int32_t *sock = &mysock;
    int32_t ret;
    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = PP_HTONS(port);
//    addr.sin_addr.s_addr = inet_addr((const char*)servip);
    inet_addr_from_ip4addr(&addr.sin_addr, ip_2_ip4(ipaddr));

    *sock = socket(AF_INET,SOCK_STREAM,0);
    ret = connect(*sock,(struct sockaddr*)&addr,sizeof(addr));
//    ret = write(*sock, "test", 4);
    if(ret != 0)
    {
         close(*sock);
         return -1;
    }
    return *sock;
}



int32_t transport_close(void)
{

    int rc;
    rc = shutdown(mysock, SHUT_WR);
    rc = recv(mysock, NULL, (size_t)0, 0);
    rc = close(mysock);
    return rc;
}
