#include "QSPI_Mem.h"

QSPI_Mem::QSPI_Mem() {
    m_qspi_init.InterfaceMode = MT25TL01G_QPI_MODE;
    m_qspi_init.TransferRate = MT25TL01G_DTR_TRANSFER;
    m_qspi_init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    CheckState(BSP_QSPI_Init(QSPI_INSTANCE, &m_qspi_init));
    CheckState(BSP_QSPI_EnableMemoryMappedMode(QSPI_INSTANCE));
}

QSPI_Mem::~QSPI_Mem() {
    CheckState(BSP_QSPI_DeInit(QSPI_INSTANCE));
}
