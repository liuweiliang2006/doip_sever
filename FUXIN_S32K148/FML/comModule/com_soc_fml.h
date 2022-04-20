/*
 * fml_spi.h
 *
 *  Created on: 2021Äê5ÔÂ25ÈÕ
 *      Author: Administrator
 */

#ifndef FML_SPI_FML_SPI_H_
#define FML_SPI_FML_SPI_H_
#include <string.h>
#include "Cpu.h"

#define SPI_MIN_LEN 512
#define SPI_MAX_LEN 1024
#define SPICALLBACK 0x88

typedef struct
{
  uint8_t tx[1024];
  uint8_t rx[1024];
} spi_buffer_t;

extern uint8_t blankFrame[6];
extern uint8_t shakeFrame[6];
extern uint8_t ackFrame[6];
extern uint8_t spiRunStep;
void package_spi_nodata_frame_fml(spi_buffer_t * spiBuffer,uint8_t *data);
void package_version_fml(spi_buffer_t * spiBuffer);
uint8_t package_did_fml(spi_buffer_t * spiBuffer);
status_t spi_slave_transfer_fml(uint16_t len);
void process_soc_can_data_fml(uint8_t *pdata);
uint8_t check_re_soc_data_crc_fml(uint8_t *p);
uint16_t copy_slave_buffer_tx_fml(uint8_t data);
uint8_t calculation_crc_fml(const uint8_t *input, uint16_t len);
void start_spi_Transfer_fml_api(uint16_t len);
void spi_timeout_process_fml_api(void);
void read_spi_ringbuffer_fml_api(void);
void spi_data_to_soc_fml_api(void);
void rx_soc_data_process_fml_api(void);
uint16_t shake_step_receive_soc_process_fml_api(uint32_t value);
uint16_t normal_step_receive_soc_process_fml_api(uint32_t value);
void clear_send_data_timeout_fml(void);
void update_start_fml(unsigned long uValue);

void OneHourModeAck(uint8_t data);
void fiveMinutesModeAck(uint8_t data);

#endif /* FML_SPI_FML_SPI_H_ */
