#ifndef IIC_H
#define IIC_H

#include "stm32h7xx.h"
//#include "stm32h7xx_ll_i2c.h"
#include <cstdint>

#define CTRL_BRD_I2C_ADDR (0x58 << 1)

class IIC {
public:
    explicit IIC(I2C_HandleTypeDef hi2cx);

    ~IIC();

    enum InsuffCmdEnum {
        SET_PRESS = 162,    /// Установка давления
        SET_FLOW,           /// Установка расхода
        START_GAS = 182,    /// Запуск подачи газа
        STOP_GAS,           /// Остановка подачи газа
        ACCEL = 188         /// Кнопка ускорить
    };

    enum InsuffReqEnum {
        GET_PRESS_100 = 166,
        GET_PRESS_10 = 169,
        GET_FLOW_100 = 168,
        GET_FLOW_10 = 170,
        GET_STATE = 186,
    };

    void SendCMD(InsuffCmdEnum cmd, uint16_t value);

    void ReadREQ(InsuffReqEnum req, uint16_t &value);

    inline I2C_HandleTypeDef *GetHandle() {
        return &m_hi2c;
    }

    void HandleInterrupt() {
        HAL_I2C_EV_IRQHandler(&m_hi2c);
    }

    static void IRQHandler() {
        if (Instance != nullptr) {
            Instance->HandleInterrupt();
        }
    }

private:
    static IIC *Instance;

    I2C_HandleTypeDef m_hi2c;

    void Error_Handler();

    unsigned char crc8(unsigned char *buffer, unsigned int len);
};

#endif //IIC_H
