/*
 * ack_codes.h
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef DOIP_ACK_CODES_H_
#define DOIP_ACK_CODES_H_


#define DOIP_PROTOCOL_VERSION	2

#define AS_LOG_DOIP 0

// Generic doip header negative acknowledge codes
#define DOIP_E_INCORRECT_PATTERN_FORMAT	0x00
#define DOIP_E_UNKNOWN_PAYLOAD_TYPE		0x01
#define DOIP_E_MESSAGE_TO_LARGE			0x02
#define DOIP_E_OUT_OF_MEMORY			0x03
#define DOIP_E_INVALID_PAYLOAD_LENGTH	0x04

// Diagnostic message negative acknowledge codes
// 0x00-0x01  Reserved by document
#define DOIP_E_DIAG_INVALID_SA			0x02	// Invalid Source Address
#define DOIP_E_DIAG_UNKNOWN_TA			0x03	// Unknown Target Address
#define DOIP_E_DIAG_MESSAGE_TO_LARGE	0x04	// Diagnostic Message too large
#define DOIP_E_DIAG_OUT_OF_MEMORY		0x05	// Out of memory
#define DOIP_E_DIAG_TARGET_UNREACHABLE	0x06	// Target unreachable
#define DOIP_E_DIAG_UNKNOWN_NETWORK		0x07	// Unknown network
#define DOIP_E_DIAG_TP_ERROR			0x08	// Transport protocol error

#endif /* DOIP_ACK_CODES_H_ */
