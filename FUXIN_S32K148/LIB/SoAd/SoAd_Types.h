/*
 * SoAd_Type.h
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef SOAD_TYPES_H
#define SOAD_TYPES_H
#include "Platform_Types.h"

typedef enum {
	SOAD_DOIP_NODETYPE_GATEWAY = 0x00,
	SOAD_DOIP_NODETYPE_NODE = 0x01,
	SOAD_DOIP_NODETYPE_NOF_VALID_MODES, // Reserved 2..255
} SoAd_DoIp_ArcNodeTypeType;

typedef uint8 SoAd_DoIp_PowerMode;

#endif /* SOAD_SOAD_TYPE_H_ */
