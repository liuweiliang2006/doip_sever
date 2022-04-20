/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

 /**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.1, function has no explicit type
 * The type is defined in some place.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.2, function has no explicit type or class, int assumed
 * This is a fake finding.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.3, All declarations or an object or function shall use the
 * same names and type qualifiers.
 * Argument of function has the same name and type qualifier in both files. This is a fake finding.
 *
 */

#ifndef ENETIF_H
#define ENETIF_H

#include "lwip/err.h"

/*! @brief The ENET instance that you want to work on */
#define ENET_INSTANCE       0
#define ENET_QUEUE          0

/*! @brief Media-Independent Interface (MII) default setting */
#ifndef ENET_MIIMODE
#define ENET_MIIMODE        ENET_RMII_MODE
#endif
#ifndef ENET_MIISPEED
#define ENET_MIISPEED       ENET_MII_SPEED_100M
#endif

/*! @brief Number of Rx and Tx descriptors */
#ifndef ENET_RXBD_NUM
#define ENET_RXBD_NUM       6
#endif
#ifndef ENET_TXBD_NUM
#define ENET_TXBD_NUM       2
#endif

/*! @brief Receive buffer descriptors */
#define ENET_RXBUFF_SIZE    ENET_BUFF_ALIGN(ENET_FRAME_MAX_FRAMELEN)

err_t enet_ethernetif_init(struct netif *netif);
void enet_ethernetif_shutdown(struct netif *netif);

#if LWIP_IPV6
err_t mld_enet_filter (struct netif *netif, const ip6_addr_t *group, enum netif_mac_filter_action action);
#endif /*LWIP_IPV6*/

#if LWIP_IGMP
err_t igmp_enet_filter (struct netif *netif, const ip4_addr_t *group, enum netif_mac_filter_action action);
#endif /*LWIP_IGMP*/

#if NO_SYS
err_t enet_poll_interface(struct netif *netif);
#endif /* NO_SYS */

#ifdef COVERAGE_ENABLED
/*!
 * @brief Send one byte to transfer buffer
 *
 * This function sends one byte to transfer buffer
 */
void send_tx_pbuffs_dummy_char(void);
/*!
 * @brief Send one byte to receive buffer
 *
 * This function sends one byte to receive buffer
 */
void send_rx_pbuffs_dummy_char(void);
#endif /*COVERAGE_ENABLED*/
#endif /* ENETIF_H */
