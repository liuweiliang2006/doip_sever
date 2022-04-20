/*
 * com_task.h
 *
 */

#ifndef SOURCES_INCLUDE_COM_TASK_H_
#define SOURCES_INCLUDE_COM_TASK_H_


#include "queue.h"
#include "status.h"
#include "task.h"
#include "Cpu.h"
#include "ringbuffer.h"
#include "utils.h"
#include "Driver_interface.h"
#include "BoardDefines.h"

#include "log_fml.h"
#include "update_fml.h"
#include "uds_store_fml.h"
#include "com_vehicle_fml.h"
#include "ringbuffer_fml.h"
#include "com_soc_fml.h"
#include "timer_fml.h"
#include "power_manager_fml.h"

#define ALIGN_4(d) (((d+3)>>2)<<2)




extern QueueHandle_t uartLogQueue;
extern QueueHandle_t spiQueue;
extern QueueHandle_t spiCallbackQueue;
extern uint8_t spiCanBuffer[];
extern uint8_t spiTxPackage[1024+48];
extern uint16_t canPakageLen;
extern uint8_t nmActive;
/*************************************************/
extern QueueHandle_t xQueue;
extern QueueHandle_t spiRingbufferQueue;

void soc_isr_hander_fml( void );
uint8_t mcu_spi_package_did2001(uint8_t * Buffer);
uint8_t mcu_spi_package_didF187(uint8_t * Buffer);
uint8_t mcu_spi_package_didF18A(uint8_t * Buffer);
uint8_t mcu_spi_package_didF190(uint8_t * Buffer);
void read_voltage_fml(void);
void adc_init_fml_api(void);
void can_ring_write_fml(uint8_t *data,uint16_t len);
uint16_t can_ring_read_fml(uint8_t *p);


typedef struct
{
  uint8_t full;
  uint8_t index;
  uint8_t spiId;
  uint16_t len;
  uint8_t data[1024];
} spi_tx_buffer_t;
typedef struct
{
    uint8_t clear;
    uint8_t full;
    uint8_t spiId;
    uint8_t dataCopy[1024];
    uint16_t frame_len;
} spi_cp_buffer_t;
typedef struct com_packet_header_s {
    uint8_t  signs;
    uint16_t signf;
    uint8_t frameId;
    uint8_t lenH; // payload length
    uint8_t lenL;
    uint8_t headCrc;
} __attribute__( (packed) ) com_packet_header_t;

extern uint8_t spiWork;
extern uint8_t SpiRingBuffwhole[];
extern uint8_t readRingbufferEn;
extern uint8_t mcuVersion[];
extern uint8_t dig2EServiceActive;
extern flash_ssd_config_t flashSSDConfig;

extern uint8_t rightLedRead;
extern uint8_t flooLlight;
extern uint8_t heaLlight;
extern uint8_t followme;
extern uint8_t leftLedRead;
extern uint32_t canFrames;

#endif /* SOURCES_INCLUDE_COM_TASK_H_ */
