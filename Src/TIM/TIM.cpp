#include "TIM.h"
#include "system.h"

void TIM::Error_Handler() {
    USART3_SendMessage("TIM error!\n\r");
}

TIM::TIM() {
    m_htim.Instance = TIM17;
    m_htim.Init.Prescaler = 0;
    m_htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    m_htim.Init.Period = 65535;
    m_htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    m_htim.Init.RepetitionCounter = 0;
    m_htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    __HAL_RCC_TIM17_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM17_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM17_IRQn);

    if (HAL_TIM_Base_Init(&m_htim) != HAL_OK) {
        Error_Handler();
    }
}

TIM::~TIM() {
    __HAL_RCC_TIM17_CLK_DISABLE();
    HAL_NVIC_DisableIRQ(TIM17_IRQn);
}

void TIM::Start() {
    HAL_TIM_Base_Start_IT(&m_htim);
}

void TIM::Stop() {
    HAL_TIM_Base_Stop_IT(&m_htim);
}

void TIM::TIMX_IRQHandler() {
    HAL_TIM_IRQHandler(&m_htim);
}