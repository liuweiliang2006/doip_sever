/*
 * spi_hal.h
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */

#ifndef INTERFACE_SPI_HAL_SPI_HAL_H_
#define INTERFACE_SPI_HAL_SPI_HAL_H_
#include "Cpu.h"

status_t lpspi_slave_init_hal_api(uint32_t instance);
status_t lpspi_slave_deinit_hal_api(uint32_t instance);
status_t lpspi_slave_get_transfer_status_hal_api(uint32_t instance,uint32_t * bytesRemained);
status_t lpspi_slave_transfer_hal_api(uint32_t instance,const uint8_t *sendBuffer,uint8_t *receiveBuffer,uint16_t transferByteCount);



#endif /* INTERFACE_SPI_HAL_SPI_HAL_H_ */
