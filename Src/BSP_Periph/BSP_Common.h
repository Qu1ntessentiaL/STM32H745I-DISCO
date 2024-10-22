#ifndef BSP_COMMON_H
#define BSP_COMMON_H

#include "stm32h7xx.h"
#include "system.h"
#include "dma.h"
#include "usart.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_conf.h"
#include "stm32h745i_discovery_errno.h"

class BSP_Common {
public:
    BSP_Common();

    void CheckState(int32_t state);

    void Error_Handler();

    void SendMessage(const char *str);
};

#endif //BSP_COMMON_H
