#include "Cpu.h"
#include "com_task.h"

//status_t lpuart_init__hal_api(uint32_t instance)
//{
//    return LPUART_DRV_Init(instance,&lpuart1_State, &lpuart1_InitConfig0);
//}

status_t lpuart_init__hal_api(uint32_t instance, lpuart_state_t * lpuartStatePtr,
        const lpuart_user_config_t * lpuartUserConfig)
{
    return LPUART_DRV_Init(instance,lpuartStatePtr, lpuartUserConfig);
}

status_t lpuart_deinit_hal_api(uint32_t instance)
{
    return LPUART_DRV_Deinit(instance);
}
status_t lpuart_send_data__hal_api(uint32_t instance,const uint8_t * txBuff,uint32_t txSize)
{
    return LPUART_DRV_SendData(instance,txBuff,txSize);
}
status_t lpuart_get_transmit_status__hal_api(uint32_t instance, uint32_t * bytesRemaining)
{
    return LPUART_DRV_GetTransmitStatus(instance,bytesRemaining);
}

uart_callback_t lpuart_drv_install_rx_callback_hal_api(uint32_t instance,uart_callback_t function,void * callbackParam)
{
    LPUART_DRV_InstallRxCallback(instance, function, callbackParam);
}

status_t lpuart_drv_receive_data_hal_api(uint32_t instance,
                                uint8_t * rxBuff,
                                uint32_t rxSize)
{
    LPUART_DRV_ReceiveData(instance,rxBuff,rxSize);
}

status_t lpuart_drv_senddatapolling_api(uint32_t instance,
                                const uint8_t *txBuff,
                                uint32_t txSize)
{
    LPUART_DRV_SendDataPolling(instance,txBuff, txSize);
}


