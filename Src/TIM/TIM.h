#ifndef TIM_H
#define TIM_H

#include "stm32h7xx.h"

class TIM {
public:
    TIM();

    ~TIM();

    void Start();

    void Stop();

    void TIMX_IRQHandler();

private:
    static void Error_Handler();

    TIM_HandleTypeDef m_htim{};
};

#endif //TIM_H
