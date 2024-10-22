#include "main.h"

int main() {
    HAL_Init();
    SystemClock_Config();
    BSP_Common com;
    Display disp;
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    /*
    BSP_QSPI_Init_t qspi_init;
    qspi_init.InterfaceMode = MT25TL01G_QPI_MODE;
    qspi_init.TransferRate = MT25TL01G_DTR_TRANSFER;
    qspi_init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0, &qspi_init);
    BSP_QSPI_EnableMemoryMappedMode(0);
    */
    disp.DrawObjects();
    while (1) {
        com.SendMessage("77\n\r");
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(1000);
    }
}
