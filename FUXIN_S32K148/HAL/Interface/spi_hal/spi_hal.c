/*
 * spi_hal.c
 *
 *  Created on: 2021��5��28��
 *      Author: Administrator
 */
#include "Cpu.h"
#include "com_task.h"
status_t lpspi_slave_init_hal_api(uint32_t instance)
{
    return LPSPI_DRV_SlaveInit(instance, &slaveState, &slave_SlaveConfig0);
}
status_t lpspi_slave_deinit_hal_api(uint32_t instance)
{
    return LPSPI_DRV_SlaveDeinit(instance);
}
status_t lpspi_slave_get_transfer_status_hal_api(uint32_t instance,uint32_t * bytesRemained)
{
    return LPSPI_DRV_SlaveGetTransferStatus(instance,bytesRemained);
}
status_t lpspi_slave_transfer_hal_api(uint32_t instance,
                                   const uint8_t *sendBuffer,
                                   uint8_t *receiveBuffer,
                                   uint16_t transferByteCount)
{
    return LPSPI_DRV_SlaveTransfer(instance, sendBuffer,receiveBuffer, transferByteCount);
}




