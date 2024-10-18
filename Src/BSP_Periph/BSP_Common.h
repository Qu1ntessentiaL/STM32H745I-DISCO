#ifndef BSP_COMMON_H
#define BSP_COMMON_H

#include "stm32h7xx.h"
#include "system.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_conf.h"
#include "stm32h745i_discovery_errno.h"

class BSP_Common {
protected:
    static void CheckState(int32_t state);

    static void Error_Handler();
};

#endif //BSP_COMMON_H
