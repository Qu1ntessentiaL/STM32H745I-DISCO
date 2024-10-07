#include "IIC.h"

/// Инициализация статической переменной
IIC* IIC::Instance = nullptr;
uint8_t ack_resp = 0;

void IIC::Error_Handler() {

}

unsigned char IIC::crc8(unsigned char *buffer, unsigned int len) {
    unsigned char crc = 0x82;
    unsigned int i;

    while (len--) {
        crc ^= *buffer++;

        for (i = 0; i < 8; i++)
            crc = (crc & 1) ? (crc >> 1) ^ 0x8c : crc >> 1;
    }
    return crc;
}

IIC::IIC(I2C_HandleTypeDef hi2cx) : m_hi2c(hi2cx) {
    Instance = this;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
    PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_D3PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    __HAL_RCC_I2C4_CLK_ENABLE();

    HAL_NVIC_SetPriority(I2C4_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C4_EV_IRQn);

    m_hi2c.Instance = I2C4;
    m_hi2c.Init.Timing = 0x307077B2;
    m_hi2c.Init.OwnAddress1 = 176;
    m_hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    m_hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    m_hi2c.Init.OwnAddress2 = 0;
    m_hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    m_hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    m_hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&m_hi2c) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_I2CEx_ConfigAnalogFilter(&m_hi2c, I2C_ANALOGFILTER_DISABLE) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_I2CEx_ConfigDigitalFilter(&m_hi2c, 0) != HAL_OK) {
        Error_Handler();
    }
}

IIC::~IIC() {
    __HAL_RCC_I2C4_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_12 | GPIO_PIN_13);
    HAL_NVIC_DisableIRQ(I2C4_EV_IRQn);
}

/**
 *
 * @brief Функция, передающая по I2C плате управления команды и параметры
 * @param cmd [uint8_t]
 * @param value [uint16_t]
 */

void IIC::SendCMD(InsuffCmdEnum cmd, uint16_t value) {
    uint8_t data_tx[4] = {0}, data_crc[4] = {0};

    data_tx[0] = cmd;
    data_tx[1] = value & 0xFF;
    data_tx[2] = (value >> 8) & 0xFF;

    data_crc[0] = CTRL_BRD_I2C_ADDR;
    data_crc[1] = cmd;
    data_crc[2] = data_tx[1];
    data_crc[3] = data_tx[2];

    data_tx[3] = crc8(data_crc, sizeof(data_crc));

    //HAL_I2C_Master_Transmit_IT(&m_hi2c, CTRL_BRD_I2C_ADDR, data_tx, sizeof(data_tx));
    HAL_I2C_Master_Seq_Transmit_IT(&m_hi2c, CTRL_BRD_I2C_ADDR, data_tx, sizeof(data_tx), I2C_FIRST_FRAME);
}

/**
 *
 * @brief Функция, считывающая по I2C от платы управления показания датчиков
 * @param req
 * @param value
 */

void IIC::ReadREQ(InsuffReqEnum req, uint16_t &value) {
    uint8_t data_tx[2] = {0}, data_rx[4] = {0};

    if (req <= 0xFF) {
        data_tx[0] = req;
    } else {
        return;
    }

    HAL_I2C_Master_Transmit(&m_hi2c, CTRL_BRD_I2C_ADDR, data_tx, 2, HAL_MAX_DELAY);

    HAL_I2C_Master_Receive(&m_hi2c, CTRL_BRD_I2C_ADDR, data_rx, 3, HAL_MAX_DELAY);

    data_rx[3] = data_rx[2];
    data_rx[2] = data_rx[1];
    data_rx[1] = data_rx[0];
    data_rx[0] = CTRL_BRD_I2C_ADDR;

    if (!crc8(data_rx, sizeof(data_rx))) {
        value = (static_cast<uint16_t>(data_rx[1]) << 8) | static_cast<uint16_t>(data_rx[0]);
    } else {
        return;
    }

}

extern "C" void I2C4_EV_IRQHandler(void) {
    IIC::IRQHandler();
}

extern "C" void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C4) {
        HAL_I2C_Master_Seq_Receive_IT(hi2c, CTRL_BRD_I2C_ADDR, &ack_resp, sizeof(ack_resp), I2C_LAST_FRAME);
    }
}
/*
extern "C" void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C4) {
        if ()
    }
}
*/