#ifndef QSPI_MEM_H
#define QSPI_MEM_H

#include "stm32h7xx.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_conf.h"
#include "stm32h745i_discovery_errno.h"
#include "stm32h745i_discovery_qspi.h"
#include "BSP_Common.h"

#define QSPI_INSTANCE (QSPI_INSTANCES_NUMBER - 1)

class QSPI_Mem : public BSP_Common {
public:
    explicit QSPI_Mem();

    ~QSPI_Mem();

private:
    BSP_QSPI_Init_t m_qspi_init{};
};

#endif //QSPI_MEM_H
