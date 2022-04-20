/*
 * SoAd_Cfg.c
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "SoAd_Cfg.h"
#include "SoAd_ConfigTypes.h"
#include "stddef.h"
#include "Std_Types.h"
static const SoAd_SocketConnectionType SoAd_SocketConnection [SOAD_SOCKET_COUNT] =
{
	{	/* for DCM */
		.SocketId = 0,
		.SocketRemoteIpAddress = "192.168.0.2",
		.SocketRemotePort = 13400,
		.SocketProtocol = SOAD_SOCKET_PROT_UDP,
		.SocketLocalPort = 13400,
		.AutosarConnectorType = SOAD_AUTOSAR_CONNECTOR_DOIP,
	},
	{	/* for COM */
		.SocketId = 1,
		.SocketRemoteIpAddress = "192.168.0.2",
		.SocketRemotePort = 13400,
		.SocketProtocol = SOAD_SOCKET_PROT_TCP,
		.SocketLocalPort = 13400,
		.AutosarConnectorType = SOAD_AUTOSAR_CONNECTOR_DOIP,
	}
};
static const DoIp_TargetAddressConfigType SoAd_DoIpTargetAddresses[DOIP_TARGET_COUNT]=
{
	{
		.addressValue=0x1111,  /* this 16 bit ta */
		.txPdu=SOADTP_ID_SOAD_TX,
//		.rxPdu=PDUR_ID_SOAD_RX
		.rxPdu=SOADTP_ID_SOAD_RX
	},
};
static const DoIp_TesterConfigType SoAd_DoIpTesters[DOIP_TESTER_COUNT] =
{
	{
		.address = 0xbeef,
	}
};
static const DoIp_RoutingActivationConfigType SoAd_DoIpRoutingActivations[DOIP_ROUTINGACTIVATION_COUNT] =
{
	{
		.activationNumber = 0x0,
		.authenticationCallback = NULL,
		.confirmationCallback = NULL
	}
};

static const DoIp_RoutingActivationToTargetAddressMappingType SoAd_DoIpRoutingActivationToTargetAddressMap[DOIP_ROUTINGACTIVATION_TO_TARGET_RELATION_COUNT] =
{
	{
		.routingActivation = 0,
		.target = 0,
	}
};

static const SoAd_PduRouteType SoAd_PduRoute[SOAD_PDU_ROUTE_COUNT] =
{
	{	/* for DCM */
		.DestinationSocketRef = &SoAd_SocketConnection[0],
//		.SourcePduId = PDUR_ID_SOAD_TX,
		.SourcePduId = NULL,
	},
	{	/* for COM */
		.DestinationSocketRef = &SoAd_SocketConnection[1]
	},
};

const SoAd_ConfigType SoAd_Config =
{
	.SocketConnection = SoAd_SocketConnection,
	.DoIpTargetAddresses = SoAd_DoIpTargetAddresses,
	.DoIpTesters= SoAd_DoIpTesters,
	.DoIpRoutingActivations = SoAd_DoIpRoutingActivations,
	.DoIpRoutingActivationToTargetAddressMap = SoAd_DoIpRoutingActivationToTargetAddressMap,
	.PduRoute = SoAd_PduRoute,
	.DoIpNodeLogicalAddress = 0x1111
};

Std_ReturnType SoAd_DoIp_Arc_GetVin(uint8* buf, uint8 len)
{
	for(uint8 i = 0; i<len; i++ )
	{
		*(buf+i) = i;
	}
	return E_OK;
}

Std_ReturnType SoAd_DoIp_Arc_GetEid(uint8* buf, uint8 len)
{
	return E_OK;
}

Std_ReturnType SoAd_DoIp_Arc_GetGid(uint8* buf, uint8 len)
{
	return E_OK;
}

Std_ReturnType SoAd_DoIp_Arc_GetFurtherActionRequired(uint8* buf)
{
	return E_OK;
}

