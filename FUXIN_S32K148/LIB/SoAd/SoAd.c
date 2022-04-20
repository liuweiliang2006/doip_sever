/*
 * SoAd.c
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/opt.h"

#include "SoAd.h"
#include "SoAd_Cfg.h"
#include "Platform_Types.h"
#include "SoAd_Internal.h"
#include "ack_codes.h"

typedef enum {
  SOAD_UNINITIALIZED = 0,
  SOAD_INITIALIZED
} SoadStateType;

boolean SoAd_BufferGet(uint32 size, uint8** buffPtr)
{
	boolean res;

	*buffPtr = malloc(size);
	res = (*buffPtr != NULL) ? TRUE : FALSE;

	return res;
}
void SoAd_BufferFree(uint8* buffPtr)
{
	free(buffPtr);
}

void SoAd_SocketClose(uint16 sockNr)
{
	uint16 i;

	switch (SocketAdminList[sockNr].SocketState) {
	case SOCKET_UDP_READY:
	case SOCKET_TCP_LISTENING:
		SoAd_SocketCloseImpl(SocketAdminList[sockNr].SocketHandle);
		SocketAdminList[sockNr].SocketHandle = -1;
		SocketAdminList[sockNr].SocketState = SOCKET_INIT;
		break;


	case SOCKET_TCP_READY:
		SoAd_SocketCloseImpl(SocketAdminList[sockNr].ConnectionHandle);
    	SocketAdminList[sockNr].ConnectionHandle = -1;
		SocketAdminList[sockNr].RemoteIpAddress = inet_addr(SoAd_Config.SocketConnection[sockNr].SocketRemoteIpAddress);
		SocketAdminList[sockNr].RemotePort = htons(SoAd_Config.SocketConnection[sockNr].SocketRemotePort);

		SocketAdminList[sockNr].SocketState = SOCKET_TCP_LISTENING;
		for (i = 0; i < SOAD_SOCKET_COUNT; i++) {
			if (i == sockNr) continue;

			if (SocketAdminList[sockNr].SocketHandle == SocketAdminList[i].SocketHandle) {
				if (SocketAdminList[i].SocketState == SOCKET_TCP_LISTENING) {
					SocketAdminList[sockNr].SocketState = SOCKET_DUPLICATE;
					break;
				}
			}
		}

		break;

	default:
		/* This should never happen! */
//		DET_REPORTERROR(MODULE_ID_SOAD, 0, SOAD_SOCKET_CLOSE_ID, SOAD_E_SHALL_NOT_HAPPEN);
		break;

	}

}

void SoAd_SocketStatusCheck(uint16 sockNr, int sockHandle)
{
	int sockErr;

	sockErr = SoAd_SocketStatusCheckImpl(sockHandle);
	if (sockErr != 0) {
//		ASLOG(SOADE, "socket[%d] status not okay, closed!\n", sockNr);
		SoAd_SocketClose(sockNr);
	}
}

uint16 SoAd_SendIpMessage(uint16 sockNr, uint32 msgLen, uint8* buff)
{
	uint16 bytesSent;
	uint8 buffer[200];
//	ASMEM(SOAD,"TX",buff,msgLen);
	memcpy(buffer,buff,msgLen);
	if (SocketAdminList[sockNr].SocketProtocolIsTcp) {

		bytesSent = SoAd_SendImpl(SocketAdminList[sockNr].ConnectionHandle, buff, msgLen, 0);
	} else {
		bytesSent = SoAd_SendToImpl(SocketAdminList[sockNr].SocketHandle, buff, msgLen,
									SocketAdminList[sockNr].RemoteIpAddress,
									SocketAdminList[sockNr].RemotePort);
	}

	return bytesSent;
}

static void socketCreate(uint16 sockNr)
{
    int sockFd;
    int sockType;
	int r;

    if (SocketAdminList[sockNr].SocketProtocolIsTcp) {
    	sockType = SOCK_STREAM;
    } else {
    	sockType = SOCK_DGRAM;
    }

    sockFd = SoAd_CreateSocketImpl(AF_INET, sockType, 0);
    if (sockFd >= 0) {
//        ASLOG(SOAD,"SoAd create socket[%d] okay.\n",sockNr);
    	Printf("SoAd create socket[%d] okay.\n",sockNr);
		r = SoAd_BindImpl(sockFd, SocketAdminList[sockNr].SocketConnectionRef->SocketLocalPort);
		if(r >= 0) {
//			ASLOG(SOAD,"SoAd bind socket[%d] on port %d okay.\n",sockNr,
//                SocketAdminList[sockNr].SocketConnectionRef->SocketLocalPort);
			Printf("SoAd bind socket[%d] on port %d okay.\n",sockNr,
					                SocketAdminList[sockNr].SocketConnectionRef->SocketLocalPort);
            if (!SocketAdminList[sockNr].SocketProtocolIsTcp) {
            	// Now the UDP socket is ready for receive/transmit
            	SocketAdminList[sockNr].SocketHandle = sockFd;
            	SocketAdminList[sockNr].SocketState = SOCKET_UDP_READY;
            } else {
                if  ( SoAd_ListenImpl(sockFd, 20) == 0 ){	// NOTE: What number of the backlog?
                	// Now the TCP socket is ready for receive/transmit
//                    ASLOG(SOAD,"SoAd listen socket[%d] okay.\n",sockNr);
                	Printf("SoAd listen socket[%d] okay.\n",sockNr);
                	SocketAdminList[sockNr].SocketHandle = sockFd;
                	SocketAdminList[sockNr].SocketState = SOCKET_TCP_LISTENING;
                } else {
//                    ASLOG(SOADE,"SoAd listen socket[%d] failed.\n",sockNr);
                	Printf("SoAd listen socket[%d] failed.\n",sockNr);
                	SoAd_SocketCloseImpl(sockFd);
                }
            }
    	} else {
//            ASLOG(SOADE,"SoAd bind socket[%d] failed.\n",sockNr);
    		Printf("SoAd bind socket[%d] failed.\n",sockNr);
    		SoAd_SocketCloseImpl(sockFd);
    	}
    } else {
    	// Socket creation failed
    	// Do nothing, try again later
//        ASLOG(SOADE,"SoAd create socket[%d] failed! try again later.\n",sockNr);
    	Printf("SoAd create socket[%d] failed! try again later.\n",sockNr);
    }
}


static void socketAccept(uint16 sockNr)
{
	uint16 i;
	int clientFd;
	uint32 RemoteIpAddress;
	uint16 RemotePort;

	clientFd = SoAd_AcceptImpl(SocketAdminList[sockNr].SocketHandle, &RemoteIpAddress, &RemotePort);

	if( clientFd != (-1))
	{
    	SocketAdminList[sockNr].ConnectionHandle = clientFd;
		SocketAdminList[sockNr].RemotePort = RemotePort;
		SocketAdminList[sockNr].RemoteIpAddress = RemoteIpAddress;
		SocketAdminList[sockNr].SocketState = SOCKET_TCP_READY;

		// Check if there is any free duplicate of this socket
		for (i = 0; i < SOAD_SOCKET_COUNT; i++) {
			if ((SocketAdminList[i].SocketState == SOCKET_DUPLICATE)
				&& (SoAd_Config.SocketConnection[i].SocketProtocol == SoAd_Config.SocketConnection[sockNr].SocketProtocol)
				&& (SoAd_Config.SocketConnection[i].SocketLocalPort == SoAd_Config.SocketConnection[sockNr].SocketLocalPort)) {
				// Yes, move the old socket to this
				SocketAdminList[i].SocketHandle = SocketAdminList[sockNr].SocketHandle;
				SocketAdminList[i].SocketState = SOCKET_TCP_LISTENING;

				// SocketAdminList[sockNr].SocketHandle = -1;
				break;
			}
		}
	}
}

uint8 SoAd_GetNofCurrentlyUsedTcpSockets() {
	uint8 count = 0;
	uint16 i;

	for (i = 0; i < SOAD_SOCKET_COUNT; i++) {
		if ((SOCKET_TCP_READY == SocketAdminList[i].SocketState) && SocketAdminList[i].SocketProtocolIsTcp) {
			count++;
		}
	}

	return count;
}



static void socketTcpRead(uint16 sockNr)
{
	DoIp_HandleTcpRx(sockNr);
}

static void socketUdpRead(uint16 sockNr)
{
	DoIp_HandleUdpRx(sockNr);
}
SocketAdminType SocketAdminList[SOAD_SOCKET_COUNT];
static SoadStateType ModuleStatus = SOAD_UNINITIALIZED;
PduAdminListType PduAdminList[SOAD_PDU_ROUTE_COUNT];

static void scanSockets(void)
{
	uint16 i;

	for (i = 0; i < SOAD_SOCKET_COUNT; i++) {
		switch (SocketAdminList[i].SocketState) {
		case SOCKET_INIT:
			socketCreate(i);
			break;

		case SOCKET_TCP_LISTENING:
			socketAccept(i);
			break;

		case SOCKET_TCP_READY:
			socketTcpRead(i);
			break;

		case SOCKET_UDP_READY:
			socketUdpRead(i);
			break;

		case SOCKET_DUPLICATE:
			/* Do nothing */
			break;

		default:
			/* This should never happen! */
//			DET_REPORTERROR(MODULE_ID_SOAD, 0, SOAD_SCAN_SOCKETS_ID, SOAD_E_SHALL_NOT_HAPPEN);
			break;
		} /* End of switch */
	} /* End of for */


}


/** @req SOAD092 */
Std_ReturnType SoAd_Shutdown(void)
{
	return E_OK;
}


/** @req SOAD121 */
void SoAd_MainFunction(void)
{
	if (ModuleStatus != SOAD_UNINITIALIZED) {
		scanSockets();
//		handleTx();

	}
}


/** @req SOAD093 */
void SoAd_Init(void)
{
	sint16 i, j;
	// Initiate the socket administration list
	for (i = 0; i < SOAD_SOCKET_COUNT; i++) {
		SocketAdminList[i].SocketNr = i;
		SocketAdminList[i].SocketState = SOCKET_INIT;
		SocketAdminList[i].SocketConnectionRef = &SoAd_Config.SocketConnection[i];
		SocketAdminList[i].RemoteIpAddress = inet_addr(SoAd_Config.SocketConnection[i].SocketRemoteIpAddress);
		SocketAdminList[i].RemotePort = htons(SoAd_Config.SocketConnection[i].SocketRemotePort);
		SocketAdminList[i].SocketHandle = -1;
		SocketAdminList[i].ConnectionHandle = -1;

		SocketAdminList[i].SocketProtocolIsTcp = FALSE;
		if (SoAd_Config.SocketConnection[i].SocketProtocol == SOAD_SOCKET_PROT_TCP) {
			SocketAdminList[i].SocketProtocolIsTcp = TRUE;
		} else if (SoAd_Config.SocketConnection[i].SocketProtocol != SOAD_SOCKET_PROT_UDP) {
			// Configuration error!!!
//			DET_REPORTERROR(MODULE_ID_SOAD, 0, SOAD_INIT_ID, SOAD_E_CONFIG_INVALID);
		}

		// Check if several connections are expected on this port.
		for (j = 0; j < i; j++) {
			if ((SoAd_Config.SocketConnection[i].SocketProtocol == SoAd_Config.SocketConnection[j].SocketProtocol)
				&& (SoAd_Config.SocketConnection[i].SocketLocalPort == SoAd_Config.SocketConnection[j].SocketLocalPort)) {
				SocketAdminList[i].SocketState = SOCKET_DUPLICATE;
				break;
			}
		}
	}
	// Cross reference from SocketAdminList to SocketRoute
	for (i = 0; i < SOAD_SOCKET_ROUTE_COUNT; i++) {
		if (SoAd_Config.SocketRoute[i].SourceSocketRef != NULL) {
			if (SoAd_Config.SocketRoute[i].SourceSocketRef->SocketId < SOAD_SOCKET_COUNT) {
				SocketAdminList[SoAd_Config.SocketRoute[i].SourceSocketRef->SocketId].SocketRouteRef = &SoAd_Config.SocketRoute[i];
			} else {
//				DET_REPORTERROR(MODULE_ID_SOAD, 0, SOAD_INIT_ID, SOAD_E_CONFIG_INVALID);
			}
		} else {
//			DET_REPORTERROR(MODULE_ID_SOAD, 0, SOAD_INIT_ID, SOAD_E_CONFIG_INVALID);
		}
	}

	// Initialize PduStatus of PduAdminList
	for (i = 0; i < SOAD_PDU_ROUTE_COUNT; i++) {
		PduAdminList[i].PduStatus = PDU_IDLE;
	}

	DoIp_Init();
	ModuleStatus = SOAD_INITIALIZED;

}


