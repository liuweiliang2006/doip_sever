/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 1.3,  Taking address of near auto variable.
 * The code is not dynamically linked. An absolute stack address is obtained
 * when taking the address of the near auto variable.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 2.1, A project shall not contain unreachable code.
 * These are safety checks to avoid dereferencing NULL pointers.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.4, A compatible declaration shall be
 * visible when an object or function with external linkage is defined.
 * These are symbols weak symbols defined in platform startup files (.s).
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.13, Pointer parameter could be declared as pointing to const
 * Type definition is done in another file.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.1, Unpermitted operand to operator '&&'
 * Variable is of essential boolean type
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, The value of an expression shall not be assigned to an
 * object with a narrower essential type or a different essential type category.
 * This is a string that will be concatenated to a macro variable to define a new one.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.4, Both operands of an operator in which the usual arithmetic
 * conversions are performed shall have the same essential type category.
 * These are bitwise operations used to enable flags or check their state.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.8, Impermissible cast of composite expression
 * Required in comparisons between constants and numerical types.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.3, Cast performed between a pointer to object type
 * and a pointer to a different object type.
 * This is used to check if transmission is complete.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.2, Conversion between a pointer to incomplete type and another type
 * The is a fake finding
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.5, Conversion from pointer to void to pointer to other type.
 * The conversion is needed to allocate or free the memory.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed between
 * pointer to void and an arithmetic type.
 * The cast is required to comply with the lwip API that mandates passing arguments
 * to threads using a pointer to void type.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 14.3, Controlling expressions shall not be invariant
 * This behaviour is intentional, some functions must always be called in current implementation.
 * Condition is still checked in event of further modifications for other applications.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 14.4, Conditional expression should have essentially Boolean type.
 * This is required for macro constructs in form do {...} while(0).
 *
 * @section [global]
 * Violates MISRA 2012 Mandatory Rule 17.3, Symbol undeclared, assumed
 * to return int.
 * The symbol is defined in another file.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 18.2, Substract operator applied to pointers.
 * Operation is required to compute the aligned address of the memory zone that further
 * needs to be freed.
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 18.3, Relational or substract operator applied
 * to pointers.
 * Substraction is needed to compute a memory address.
 *
 */

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
 *
 * This file is derived from the Ethernet Interface Skeleton in lwIP with the following copyright:
 *
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 */

#include <string.h>
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "lwip/tcpip.h"

#include "lwipcfg.h"
#include "lwip/sys.h"

#include "enetif.h"
#include "enet_driver.h"

#include "osif.h"


#if defined(USING_OS_FREERTOS)
#include "FreeRTOS.h"
#endif /* defined(USING_OS_FREERTOS) */

#define IFNAME0 'e'
#define IFNAME1 'n'

enet_state_t enetState;
ALIGNED(FEATURE_ENET_BUFFDESCR_ALIGNMENT)
enet_buffer_descriptor_t txDescriptor[ENET_TXBD_NUM];
ALIGNED(FEATURE_ENET_BUFFDESCR_ALIGNMENT)
enet_buffer_descriptor_t rxDescriptor[ENET_RXBD_NUM];
ALIGNED(FEATURE_ENET_BUFF_ALIGNMENT)
uint8_t rxBuffer[ENET_RXBD_NUM * ENET_RXBUFF_SIZE];

struct netif * g_netif[ENET_INSTANCE_COUNT];

#ifdef COVERAGE_ENABLED
    struct pbuf dummy_char2;
#endif

#if !NO_SYS

/* In order to support zero-copy operation, on the RX side we are using custom pbufs, with the payload pointing to the
   receive buffer obtained from the driver. When the pbuf is eventually freed, the receive buffer is given back to the driver.
   On the TX side we are incrementing the reference count on the pbuf and giving its payload storage to the driver. Once we
   detect the transmission is complete, we are freeing our reference to the pbuf. */

/* Memory pool for RX custom pbufs
   The pool only holds the pbuf_custom structures, not the storage for actual payload */
LWIP_MEMPOOL_DECLARE(RX_POOL, ENET_RXBD_NUM, sizeof(struct pbuf_custom), "Zero-copy RX PBUF pool");
/* Queue for passing RX buffers that need to be released back to the driver.
   The actual operation is performed on the same enetif_poll_thread as reception, thus avoiding additional synchronization for RX side */
static sys_mbox_t rx_buffs;

/* Queue for holding pbufs which have been sent to the driver for transmission. They will be released once transmission is complete
  (detected by polling ENET_DRV_GetTransmitStatus) */
static sys_mbox_t in_flight_tx_pbufs;
/* Lock to synchronize access on TX side, since the frames are sent from different treads */
mutex_t txLock;

static sys_thread_t poll_thread;

/**
 * Callback function called when a custom pbuf is freed
 *
 * @param p - the custom pbuf structure
 * Implements enet_pbuf_free_custom_Activity
 */
static void enet_pbuf_free_custom(struct pbuf *p)
{
    LWIP_ASSERT("NULL pointer", p != NULL);
    struct pbuf_custom* pc = (struct pbuf_custom*)p;
    uint8_t *alignedPtr = &rxBuffer[(((uint32_t)((uint8_t*)pc->pbuf.payload - (uint8_t*)rxBuffer) / (uint32_t)ENET_RXBUFF_SIZE) * (uint32_t)ENET_RXBUFF_SIZE)];
    sys_mbox_post((sys_mbox_t *)&rx_buffs, (void *)alignedPtr);
    LWIP_MEMPOOL_FREE(RX_POOL, pc);
}

/**
 * Transmit a packet.
 * The packet is contained in the pbuf that is passed to the function. This pbuf might be chained.
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * @param p - the pbuf structure
 * Implements enetif_low_level_output_Activity
 */
static err_t enetif_low_level_output(struct netif *netif, struct pbuf *p)
{
    struct pbuf *q;
    status_t status;

    LWIP_ASSERT("Output packet buffer empty", p);
#if defined(LWIP_DEBUG) && LWIP_NETIF_TX_SINGLE_PBUF && !(LWIP_IPV4 && IP_FRAG) && (LWIP_IPV6 && LWIP_IPV6_FRAG)
   LWIP_ASSERT("p->next == NULL && p->len == p->tot_len", p->next == NULL && p->len == p->tot_len);
#endif

    /* Increment our reference on p */
    pbuf_ref(p);
    q = pbuf_coalesce(p, PBUF_RAW);
    /* If p was a single pbuf, nothing special happened: q = p
       If p was a pbuf chain instead, p's ref was decreased and we got another q pbuf with ref 1
       Either way, q has a +1 ref that we need to free in case we're not keeping the buffer - ie in case of errors
    */
    enet_buffer_t bd;

    bd.data = q->payload;
    bd.length = q->tot_len;

    while(1)
    {
        while(OSIF_MutexLock(&txLock, 5) != STATUS_SUCCESS) {}
        status = ENET_DRV_SendFrame(netif->num, ENET_QUEUE, &bd, NULL);
        (void)OSIF_MutexUnlock(&txLock);
        /* Keep trying to send the frame as long as the driver says there is not enough space in the queue */
        if (status != STATUS_ENET_TX_QUEUE_FULL)
        {
            break;
        }
        OSIF_TimeDelay(0);
    }
	if (status == STATUS_SUCCESS)
    {
        /* Post the pbuf to mbox, so that it will be checked for completion in enetif_poll_thread*/
        sys_mbox_post((sys_mbox_t *)&in_flight_tx_pbufs, (void *)q);
    }
    else
    {
       /* Decrement the ref (either p's ref in case it was a single pbuf, or the coalesed q's ref) */
       (void)pbuf_free(q);
    }
    return ERR_OK;
}

/**
 * This function is called when a packet is ready to be read from the interface.
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * @param data - the pointer to the received data buffer
 * @param size - the length of received data buffer
 * @return ERR_OK if the packet is being handled (we take ownership of the data buffer)
 *         ERR_MEM if the packet cannot be handled (we don't take ownership of the data buffer,
 *         therefore the caller should release it)
 * Implements enetif_input_Activity
 */
static err_t enetif_input(struct netif *netif, uint8_t * data, uint16_t size)
{
    err_t ret = ERR_MEM;

    /* Allocate a custom PBUF_REF pointing to the receive buffer */
    struct pbuf_custom* enet_pbuf  = (struct pbuf_custom*)LWIP_MEMPOOL_ALLOC(RX_POOL);
    if (enet_pbuf != NULL)
    {
        ret = ERR_OK;
        enet_pbuf->custom_free_function = enet_pbuf_free_custom;
        struct pbuf* p = pbuf_alloced_custom(PBUF_RAW, size, PBUF_REF, enet_pbuf, data, size);

        if (netif->input(p, netif) != ERR_OK)
        {
            LWIP_DEBUGF(NETIF_DEBUG, ("enetif_input: IP input error\n"));
            (void)pbuf_free(p);
        }
    }
    return ret;
}

/**
 * This function is run on a separate thread and handles communication with the enet interface:
 *  - polls the driver for incoming RX frames
 *  - releases processed receive buffers back to the driver
 *  - polls the driver for outgoing TX frames and subsequently releases user pbufs
 * @param arg - the instance number for this ethernetif
 * Implements enetif_poll_thread_Activity
 */
static void enetif_poll_thread(void *arg)
{
    uint8_t instance = (uint8_t)(uint32_t)arg;
    struct pbuf *p;
    enet_buffer_t bd;
	err_t ret;

    /* Check input parameter */
    LWIP_ASSERT("g_netif[instance] != NULL", g_netif[instance] != NULL);
    uint16_t regVal;
    while (1)
    {
    	regVal = 0;
    	ENET_DRV_MDIORead(ENET_INSTANCE, 0, 2, &regVal, 65536);
    	ENET_DRV_MDIORead(ENET_INSTANCE, 0, 18, &regVal, 65536);
        /* Free any completed receive buffers */
        while (0 == sys_arch_mbox_tryfetch((sys_mbox_t *)&rx_buffs, (void**)&bd.data))
        {
            ENET_DRV_ProvideRxBuff(instance, ENET_QUEUE, &bd);
        }

        /* Check if there are any new RX frames and provide them to lwip stack */
        while (STATUS_SUCCESS == ENET_DRV_ReadFrame(instance, ENET_QUEUE, &bd, NULL))
        {
            ret = enetif_input((struct netif *)g_netif[instance], (uint8_t*)bd.data, (uint16_t)bd.length);
            if (ERR_OK != ret)
            {
                ENET_DRV_ProvideRxBuff(instance, ENET_QUEUE, &bd);
                break;
            }
        }

        /* Check if transmission is complete for any in-flight pbufs */
        while (0 == sys_arch_mbox_tryfetch((sys_mbox_t *)&in_flight_tx_pbufs, (void**)&p))
        {
            if (STATUS_BUSY == ENET_DRV_GetTransmitStatus(instance, ENET_QUEUE, p->payload, NULL))
            {
                /* transmission still in progress for the first buffer, repost to (front of) queue and give up for now */
                sys_mbox_post_to_front((sys_mbox_t *)&in_flight_tx_pbufs, (void *)p);
                break;
            }
            else
            {
                /* request to free the outstanding pbuf on tcpip thread */
                (void)pbuf_free_callback(p);
            }
        }

        OSIF_TimeDelay(0);
    }
}

#else /* !NO_SYS */

/**
 * Transmit a packet.
 * The packet is contained in the pbuf that is passed to the function. This pbuf might be chained.
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * @param p - the pbuf structure
 * Implements enetif_low_level_output_Activity
 */
static err_t enetif_low_level_output(struct netif *netif, struct pbuf *p)
{
    struct pbuf *q;
    status_t status;

    LWIP_ASSERT("Output packet buffer empty", p);
#if defined(LWIP_DEBUG) && LWIP_NETIF_TX_SINGLE_PBUF && !(LWIP_IPV4 && IP_FRAG) && (LWIP_IPV6 && LWIP_IPV6_FRAG)
   LWIP_ASSERT("p->next == NULL && p->len == p->tot_len", p->next == NULL && p->len == p->tot_len);
#endif

    /* Increment our reference on p */
    pbuf_ref(p);
    q = pbuf_coalesce(p, PBUF_RAW);
    /* If p was a single pbuf, nothing special happened: q = p
       If p was a pbuf chain instead, p's ref was decreased and we got another q pbuf with ref 1
       Either way, q has a +1 ref that we need to free in case we're not keeping the buffer - ie in case of errors
    */
    enet_buffer_t bd;

    bd.data = q->payload;
    bd.length = q->tot_len;

    /* Keep trying to send the frame as long as the driver says there is not enough space in the queue */
    do
    {
        status = ENET_DRV_SendFrame(netif->num, ENET_QUEUE, &bd, NULL);
    }
    while (status == STATUS_ENET_TX_QUEUE_FULL);

    if (status == STATUS_SUCCESS)
    {
        /* Wait for the frame to be trnasmitted - TODO: improve this! */
        while (STATUS_BUSY == ENET_DRV_GetTransmitStatus(netif->num, ENET_QUEUE, &bd, NULL)) {}
    }
    /* Decrement the ref (either p's ref in case it was a single pbuf, or the coalesed q's ref) */
    (void)pbuf_free(q);

    return ERR_OK;
}

/**
 * This function is called when a packet is ready to be read from the interface.
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * @param data - the pointer to the received data buffer
 * @param size - the length of received data buffer
 * @return ERR_OK if the packet is being handled (we take ownership of the data buffer)
 *         ERR_MEM if the packet cannot be handled (we don't take ownership of the data buffer,
 *         therefore the caller should release it)
 * Implements enetif_input_Activity
 */
static err_t enetif_input(struct netif *netif, uint8_t * data, uint16_t size)
{
    err_t ret = ERR_MEM;

    /* Allocate a PBUF_REF pointing to the receive buffer */
    struct pbuf* p  = pbuf_alloc(PBUF_RAW, size, PBUF_REF);
    if (p != NULL)
    {
        ret = ERR_OK;
        p->payload = data;
        if (netif->input(p, netif) != ERR_OK)
        {
            LWIP_DEBUGF(NETIF_DEBUG, ("enetif_input: IP input error\n"));
            (void)pbuf_free(p);
        }
    }

    return ret;
}

/**
 * This function polls the driver for received frames
 * Implements enetif_poll_thread_Activity
 */
err_t enet_poll_interface(struct netif *netif)
{
    uint8_t instance = netif->num;
    enet_buffer_t bd;

    /* Check input parameter */
    LWIP_ASSERT("g_netif[instance] != NULL", g_netif[instance] != NULL);

    /* Check if there are any new RX frames and provide them to lwip stack */
    if (STATUS_SUCCESS == ENET_DRV_ReadFrame(instance, ENET_QUEUE, &bd, NULL))
    {
        (void)enetif_input((struct netif *)g_netif[instance], (uint8_t*)bd.data, (uint16_t)bd.length);
        ENET_DRV_ProvideRxBuff(instance, ENET_QUEUE, &bd);
    }

    return ERR_OK;
}

#endif /* !NO_SYS */

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif - the already initialized lwip network interface structure
 *        for this ethernetif
 * Implements enetif_low_level_init_Activity
 */
static void enetif_low_level_init(struct netif *netif)
{
    enet_config_t enetConfig;
    /* Use only one ring */
    enet_buffer_config_t enetBufferConfigs[ENET_QUEUE + 1];
    uint8_t macAddr[NETIF_MAX_HWADDR_LEN] = { LWIP_MAC_ADDR_BASE };
    uint8_t i;

    /* set MAC hardware address length */
    netif->hwaddr_len = NETIF_MAX_HWADDR_LEN;

    /* set MAC hardware address */
    for (i = 0; i < NETIF_MAX_HWADDR_LEN; i++)
    {
      netif->hwaddr[i] = macAddr[i];
    }

    /* maximum transfer unit */
    netif->mtu = 1500;

    netif->num = ENET_INSTANCE;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = (u8_t)(NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET);
#if LWIP_IGMP
  netif->flags = netif->flags | (u8_t)NETIF_FLAG_IGMP;
  /*Will add the function igmp_mac_filter to the netif*/
  (netif)->igmp_mac_filter = igmp_enet_filter;

#endif /*LWIP_IGMP*/

    ENET_DRV_GetDefaultConfig(&enetConfig);

    enetConfig.miiMode = ENET_MIIMODE;
    enetConfig.miiSpeed = ENET_MIISPEED;

#if FEATURE_ENET_RX_CONFIG_PAYLOAD_LEN_CHECK
    enetConfig.rxConfig |= (uint32_t)(ENET_RX_CONFIG_ENABLE_PAYLOAD_LEN_CHECK);
#endif /* FEATURE_ENET_RX_CONFIG_PAYLOAD_LEN_CHECK */

#if FEATURE_ENET_RX_CONFIG_STRIP_CRC_FIELD
    enetConfig.rxConfig |= (uint32_t)(ENET_RX_CONFIG_STRIP_CRC_FIELD);
#endif /* FEATURE_ENET_RX_CONFIG_STRIP_CRC_FIELD */

#if FEATURE_ENET_RX_CONFIG_REMOVE_PADDING
    enetConfig.rxConfig |= (uint32_t)(ENET_RX_CONFIG_REMOVE_PADDING);
#endif /* FEATURE_ENET_RX_CONFIG_REMOVE_PADDING */

    enetConfig.rxConfig |= (uint32_t)(ENET_RX_CONFIG_ENABLE_FLOW_CONTROL);

#if FEATURE_ENET_HAS_TX_CONFIG
    enetConfig.txConfig = 0;
#endif /* FEATURE_ENET_HAS_TX_CONFIG */

#if FEATURE_ENET_HAS_ACCELERATOR
    enetConfig.rxAccelerConfig = (uint8_t)(ENET_RX_ACCEL_ENABLE_IP_CHECK | ENET_RX_ACCEL_ENABLE_PROTO_CHECK | ENET_RX_ACCEL_REMOVE_PAD);
    enetConfig.txAccelerConfig = (uint8_t)(ENET_TX_ACCEL_INSERT_IP_CHECKSUM | ENET_TX_ACCEL_INSERT_PROTO_CHECKSUM);
#endif /* FEATURE_ENET_HAS_ACCELERATOR */

    enetConfig.ringCount = sizeof(enetBufferConfigs) / sizeof (enet_buffer_config_t);
    enetBufferConfigs[ENET_QUEUE].rxRingSize = ENET_RXBD_NUM;
    enetBufferConfigs[ENET_QUEUE].txRingSize = ENET_TXBD_NUM;
    enetBufferConfigs[ENET_QUEUE].rxRingAligned = rxDescriptor;
    enetBufferConfigs[ENET_QUEUE].txRingAligned = txDescriptor;
    enetBufferConfigs[ENET_QUEUE].rxBufferAligned = rxBuffer;

    NETIF_SET_CHECKSUM_CTRL(netif, NETIF_CHECKSUM_SETTING);

    g_netif[ENET_INSTANCE] = netif;
    ENET_DRV_Init(ENET_INSTANCE, &enetState, &enetConfig, enetBufferConfigs, netif->hwaddr);
    ENET_DRV_EnableMDIO(ENET_INSTANCE, false);
    uint16_t regVal = 0;
    ENET_DRV_MDIORead(ENET_INSTANCE, 0, 15, &regVal, 65536);
    ENET_DRV_MDIORead(ENET_INSTANCE, 0, 17, &regVal, 65536);
    regVal |= 0x4;
    ENET_DRV_MDIOWrite(ENET_INSTANCE, 0, 17, regVal, 65536);

    regVal = 0;
    ENET_DRV_MDIORead(ENET_INSTANCE, 0, 18, &regVal, 65536);
    ENET_DRV_MDIOWrite(ENET_INSTANCE, 0, 18, 0x5A11, 65536);
    regVal = 0;
    ENET_DRV_MDIORead(ENET_INSTANCE, 0, 18, &regVal, 65536);
#if LWIP_IPV6 && LWIP_IPV6_MLD
    netif->flags = netif->flags | (u8_t)NETIF_FLAG_MLD6;
    /*If flag MLD6 flag is set, add mdl_enet_filter function to netif*/
    (netif)->mld_mac_filter = mld_enet_filter;
   /*
    * For hardware/netifs that implement MAC filtering.
    * All-nodes link-local is handled by default, so we must let the hardware know
    * to allow multicast packets in.
    * Should set mld_mac_filter previously. */
     ip6_addr_t ip6_allnodes_ll;
     ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
     (void)netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);

#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

    netif_set_link_up(netif);

}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 * Implements enet_ethernetif_init_Activity
 */
err_t enet_ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if !NO_SYS
    LWIP_MEMPOOL_INIT(RX_POOL);
    (void)sys_mbox_new((sys_mbox_t *)&rx_buffs, ENET_RXBD_NUM);
    (void)sys_mbox_new((sys_mbox_t *)&in_flight_tx_pbufs, 2 * ENET_TXBD_NUM);

    status_t status = OSIF_MutexCreate(&txLock);
    LWIP_ASSERT("status == STATUS_SUCCESS", status == STATUS_SUCCESS);
    (void)status;
#endif /* !NO_SYS */

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;

#if LWIP_IPV4
#if LWIP_ARP
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
#else /* LWIP_ARP */
    netif->output = NULL; /* not used for PPPoE */
#endif /* LWIP_ARP */
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
    netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
    netif->linkoutput = enetif_low_level_output;
#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = LWIP_NETIF_HOSTNAME_TEXT;
#endif /* LWIP_NETIF_HOSTNAME */

#if LWIP_SNMP
    /*
    * Initialize the snmp variables and counters inside the struct netif.
    * The last argument should be replaced with your link speed, in units
    * of bits per second.
    */
    NETIF_INIT_SNMP(netif, (u8_t)snmp_ifType_ethernet_csmacd, (u32_t)100000000);
#endif /* LWIP_SNMP */

    /* initialize the hardware */
    enetif_low_level_init(netif);

#if !NO_SYS
    /* Start the polling thread */
    poll_thread = sys_thread_new("enetif_poll_thread", enetif_poll_thread, (void*)((uint32_t)netif->num), DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO);
#endif /* !NO_SYS */

    return ERR_OK;
}

/**
 * Clean up network interface and internal structures
 *
 * @param netif - the lwip network interface structure for this ethernetif
 * Implements enet_ethernetif_shutdown_Activity
 */
void enet_ethernetif_shutdown(struct netif *netif)
{
#if !NO_SYS
    struct pbuf *p;
    uint8_t *ptr;

    LWIP_ASSERT("netif != NULL", (netif != NULL));

    /* Kill the polling thread */
    sys_thread_delete(poll_thread);

    /* Empty and free the mboxes */
    while (0 == sys_arch_mbox_tryfetch((sys_mbox_t *)&in_flight_tx_pbufs, (void**)&p))
    {
        (void)pbuf_free_callback(p);
    }
    sys_mbox_free((sys_mbox_t *)&in_flight_tx_pbufs);
    while (0 == sys_arch_mbox_tryfetch((sys_mbox_t *)&rx_buffs, (void**)&ptr)) {}
    sys_mbox_free((sys_mbox_t *)&rx_buffs);

    ENET_DRV_Deinit(netif->num);

    (void)OSIF_MutexDestroy(&txLock);

#else

    ENET_DRV_Deinit(netif->num);

#endif /* !NO_SYS */
}

#ifdef COVERAGE_ENABLED
void send_tx_pbuffs_dummy_char(void)
{
    struct pbuf* dummy  = pbuf_alloc(PBUF_RAW, ENET_RXBUFF_SIZE, PBUF_RAM);
    sys_mbox_post((sys_mbox_t *)&in_flight_tx_pbufs, dummy);
}

void send_rx_pbuffs_dummy_char(void)
{

    sys_mbox_post((sys_mbox_t *)&rx_buffs, &dummy_char2);
}
#endif /*COVERAGE_ENABLED*/

#if LWIP_IPV6
/**
 * @ingroup netif_ip6
 * Modify/Configure enet driver setting  to forward (or stop forwarding) multicast packet for MLD (ICMPv6)
 * if "action" = NETIF_ADD_MAC_FILTER , enet module will forward multicast packet of the group corresponding to "group"
 * if "action" = NETIF_DEL_MAC_FILTER , enet module will stop forwarding multicast packet of the group corresponding to "group"
 *
 * @param netif the network interface
 * @*group IP address of the Multicast group the message have to be forwarded by the enet module
 * @action action to be done (remove group from the forwarded packet or add group)
 * Implements design_id_IPv6_Activity
 */
err_t mld_enet_filter (struct netif *netif,
                       const ip6_addr_t *group,
                       enum netif_mac_filter_action action)
{
    /*Generate MAC address based on IP address*/
    uint8_t group_MAC[6];
    group_MAC[0] = 0x33;
    group_MAC[1] = 0x33;
    group_MAC[2] = (uint8_t)((IP6_ADDR_BLOCK7(group)) >> 8);
    group_MAC[3] = (uint8_t)(IP6_ADDR_BLOCK7(group));
    group_MAC[4] = (uint8_t)((IP6_ADDR_BLOCK8(group)) >> 8);
    group_MAC[5] = (uint8_t)(IP6_ADDR_BLOCK8(group));

    /*call function modifying the enet driver*/
    ENET_DRV_SetMulticastForward(netif->num, group_MAC, (action != NETIF_DEL_MAC_FILTER));
    return ERR_OK;

}
#endif /*LWIP_IPV6*/

#if LWIP_IGMP && LWIP_IPV4
/**
 * @ingroup netif_ip4
 * Modify/Configure enet driver setting  to forward (or stop forwarding) multicast packet for IGMP (IPv4)
 * if "action" = NETIF_ADD_MAC_FILTER , enet module will forward multicast packet of the group corresponding to "group"
 * if "action" = NETIF_DEL_MAC_FILTER , enet module will stop forwarding multicast packet of the group corresponding to "group"
 *
 * @param netif the network interface
 * @*group IP address of the Multicast group the message have to be forwarded by the enet module
 * @action action to be done (remove group from the forwarded packet or add group)
 * Implements design_id_IGMP_Activity
 */

err_t igmp_enet_filter (struct netif *netif,
                        const ip4_addr_t *group,
                        enum netif_mac_filter_action action)
{
    /*Generate MAC address based on IP address*/
    uint8_t group_MAC[6];
    group_MAC[0] = 0x01;
    group_MAC[1] = 0x00;
    group_MAC[2] = 0x5e;
    group_MAC[3] = (0x7f & ip4_addr2(group));
    group_MAC[4] = ip4_addr3(group);
    group_MAC[5] = ip4_addr4(group);

    /*call function modifying the enet driver*/
    ENET_DRV_SetMulticastForward(netif->num, group_MAC, (action != NETIF_DEL_MAC_FILTER));
    return ERR_OK;

}
#endif /*LWIP_IGMP && LWIP_IPV4*/
