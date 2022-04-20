/*
 * SoAd_ConfigTypes.h
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef SOAD_CONFIGTYPES_H
#define SOAD_CONFIGTYPES_H
#include "Platform_Types.h"
#include "SoAd_Types.h"

//typedef Std_ReturnType (*SoAd_CallbackDoIpPowerModeFncType)(SoAd_DoIp_PowerMode* powermode);

// IMPROVEMENT: Where shall these enums be defined?
typedef enum {
	SOAD_SOCKET_PROT_TCP,
	SOAD_SOCKET_PROT_UDP
} SoAd_SocketProtocolType;

typedef enum {
	SOAD_AUTOSAR_CONNECTOR_CDD,
	SOAD_AUTOSAR_CONNECTOR_DOIP,
	SOAD_AUTOSAR_CONNECTOR_PDUR,
	SOAD_AUTOSAR_CONNECTOR_XCP
} SoAd_AutosarConnectorType;

typedef enum {
	SOAD_UL_CDD,
	SOAD_UL_PDUR,
	SOAD_UL_UDPNM,
	SOAD_UL_XCP
} SoAd_ULType;

typedef struct {
	uint16 addressValue;
	uint16 txPdu;
	uint16 rxPdu;
} DoIp_TargetAddressConfigType;

typedef void (*DoIp_AuthenticationCallbackType)(void);
typedef void (*DoIp_ConfirmationCallbackType)(void);

typedef struct {
	uint8 activationNumber;
	DoIp_AuthenticationCallbackType authenticationCallback;
	DoIp_ConfirmationCallbackType confirmationCallback;
} DoIp_RoutingActivationConfigType;

typedef struct {
	uint16 routingActivation;
	uint16 target;
} DoIp_RoutingActivationToTargetAddressMappingType;

typedef struct {
	uint16 address;
	uint16 numBytes;
} DoIp_TesterConfigType;

typedef struct {
	uint16 tester;
	uint16 routingActivation;
} DoIp_TesterToRoutingActivationMapType;
// Information required to receive and transmit data via the TCP/IP stack on a particular connection.
typedef struct {
	uint16						SocketId;					/** @req SOAD016_Conf */ // Static
	char*						SocketLocalIpAddress;		/** @req SOAD017_Conf */
	uint16						SocketLocalPort;			/** @req SOAD018_Conf */ // Static
	char*						SocketRemoteIpAddress;		/** @req SOAD019_Conf */
	uint16						SocketRemotePort;			/** @req SOAD020_Conf */
	SoAd_SocketProtocolType		SocketProtocol;				/** @req SOAD021_Conf */ // Static
	boolean						SocketTcpInitiate;			/** @req SOAD022_Conf */ // Static
	boolean						SocketTcpNoDelay;			/** @req SOAD023_Conf */ // Static
	boolean						SocketUdpListenOnly;		/** @req SOAD024_Conf */ // Static
	SoAd_AutosarConnectorType	AutosarConnectorType;		/** @req SOAD025_Conf */ // Static
	boolean						PduHeaderEnable;			/** @req SOAD027_Conf */ // Static
	boolean						SocketAutosarApi;			/** @req SOAD026_Conf */ // Static
	boolean 					ResourceManagementEnable;	/** @req SOAD067_Conf */ // Static
	boolean						PduProvideBufferEnable; 	/** @req SOAD029_Conf */ // Static
} SoAd_SocketConnectionType;	/** @req SOAD009_Conf */

typedef struct {
	const SoAd_SocketConnectionType*	SourceSocketRef;		/** @req SOAD035_Conf */
	uint32								SourceId;				/** @req SOAD036_Conf */	 /* Only used when having PDU header enabled */
//	???									DestinationPduRef;		/** @req SOAD038_Conf */	// NOTE: Replaced by following line, ok?
	uint16								DestinationPduId;									// NOTE: Ok?
	uint64								DestinationSduLength;	/** @req SOAD037_Conf */
	SoAd_ULType							UserRxIndicationUL;		/** @req SOAD068_Conf */
//	SoAd_CallbackRxIndicationFncType	RxIndicationUL;			/** @req SOAD069_Conf */	// Only used when UserRxIndicationUL = CDD
} SoAd_SocketRouteType;	/** @req SOAD008_Conf */

// 10.2.7 SoAdPduRoute (TX direction)
// Describes the path of a PDU from the PDU Router to the socket in the TCP/IP stack for transmission.
typedef struct {
	uint16									SourcePduId;			/** @req SOAD031_Conf */
	uint16									SourceSduLength;		/** @req SOAD032_Conf */
//	???										SourcePduRef;			/** @req SOAD030_Conf */	// NOTE: Is not SOAD031 enough?
	const SoAd_SocketConnectionType*		DestinationSocketRef;	/** @req SOAD034_Conf */
	uint32									DestinationId;			/** @req SOAD033_Conf */	/* Only used when having PDU header enabled */
	SoAd_ULType								UserTxConfirmationUL;	/** @req SOAD070_Conf */
//	SoAd_CallbackTxConfirmationFncType		TxConfirmationUL;		/** @req SOAD071_Conf */	// Only used when UserTxConfirmationUL = CDD
} SoAd_PduRouteType;	/** @req SOAD007_Conf */

// 10.2.8 SoAdDoIpConfig
// This container contains all global configuration parameters of the DoIP plug-in.
typedef struct {
	uint32		DoIpAliveCheckresponseTimeMs;	/** @req SOAD051_Conf */
	uint32		DoIpControlTimeoutMs;			/** @req SOAD065_Conf */
	uint32		DoIpGenericInactiveTimeMs;		/** @req SOAD052_Conf */
	uint8*		DoIpHostNameOpt;				/** @req SOAD053_Conf */
	uint32		DoIpInitialInactiveTimeMs;		/** @req SOAD054_Conf */
	uint32		DoIpResponseTimeoutMs;			/** @req SOAD066_Conf */
	uint32		DoIpVidAnnounceIntervalMs;		/** @req SOAD055_Conf */
	uint32		DoIpVidAnnounceMaxWaitMs;		/** @req SOAD056_Conf */
	uint32		DoIpVidAnnounceMinWaitMs;		/** @req SOAD057_Conf */
	uint32		DoIpVidAnnounceNum;				/** @req SOAD058_Conf */
//	SoAd_CallbackDoIpPowerModeFncType DoipPowerModeCallback;
} SoAd_DoIpConfigType;	/** @req SOAD050_Conf */

typedef struct {
	const SoAd_SocketConnectionType*	SocketConnection;
	const SoAd_SocketRouteType*			SocketRoute;
	const SoAd_PduRouteType*			PduRoute;
	const SoAd_DoIpConfigType*			DoIpConfig;

	const SoAd_DoIp_ArcNodeTypeType 	DoIpNodeType;
	const uint16 						DoIpNodeLogicalAddress;

	const DoIp_TargetAddressConfigType* 					DoIpTargetAddresses;
	const DoIp_RoutingActivationConfigType*					DoIpRoutingActivations;
	const DoIp_RoutingActivationToTargetAddressMappingType* DoIpRoutingActivationToTargetAddressMap;
	const DoIp_TesterConfigType*							DoIpTesters;
	const DoIp_TesterToRoutingActivationMapType*			DoIpTesterToRoutingActivationMap;
} SoAd_ConfigType;

extern const SoAd_ConfigType SoAd_Config;
#endif /* SOAD_SOAD_CONFIGTYPES_H_ */
