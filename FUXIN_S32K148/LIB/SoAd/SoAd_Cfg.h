/*
 * SoAd_Cfg.h
 *
 *  Created on: 2022Äê3ÔÂ21ÈÕ
 *      Author: Administrator
 */

/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef COM_AS_APPLICATION_COMMON_CONFIG_SOAD_CFG_H_
#define COM_AS_APPLICATION_COMMON_CONFIG_SOAD_CFG_H_
/* ============================ [ INCLUDES  ] ====================================================== */

/* ============================ [ MACROS    ] ====================================================== */
#define SOAD_DEV_ERROR_DETECT STD_ON

#define SOADTP_ID_SOAD_RX 1
#define SOADTP_ID_SOAD_TX 0
#define SOADIF_ID_SOAD_RX 1
#define SOADIF_ID_SOAD_TX 1
#define SOAD_PDU_ROUTE_COUNT 2

#define SOAD_SOCKET_COUNT 2

#define SOAD_DOIP_ANNOUNCE_WAIT 100

#define SOAD_RX_BUFFER_SIZE 1500

#define SOAD_DOIP_NODE_TYPE 0

#define SOAD_DOIP_ANNOUNCE_NUM 5

#define SOAD_DOIP_ANNOUNCE_INTERVAL 10

#define SOAD_DOIP_ANNOUNCE_SOCKET 0

#define SOAD_SOCKET_ROUTE_COUNT 0


#define DOIP_MAX_TESTER_CONNECTIONS 1
#define DOIP_TARGET_COUNT 1
#define DOIP_TESTER_COUNT 1
#define DOIP_ROUTINGACTIVATION_COUNT 1
#define DOIP_ROUTINGACTIVATION_TO_TARGET_RELATION_COUNT 1

#define DOIP_MAINFUNCTION_PERIOD_TIME 10
#define DOIP_ALIVECHECK_RESPONSE_TIMEOUT 1000
#define DOIP_GENERAL_INACTIVITY_TIMEOUT 1000




/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif /* COM_AS_APPLICATION_COMMON_CONFIG_SOAD_CFG_H_ */
