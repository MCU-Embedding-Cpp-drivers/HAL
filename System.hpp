#ifndef __SYSTEM_HPP
#define __SYSTEM_HPP


// 这里可以加入ifdef 预编译命令，用于区分不同平台

#include "main.h"
#include "stm32g4xx_hal.h"
#include <SystemTypes.hpp>

namespace System {

#define PLATFORM_STM32  //! 非常重要，不同平台的库函数实现不同（虽然现在我只对STM32进行开发）

// GPIO 高低电平用 bool 或 0/1
using GPIO_PIN_State = bool; // true = HIGH, false = LOW

/**
 * @brief 硬延时 ms
 * @param ms 毫秒
 */
void delay(uint32_t ms);

/**
 * @brief 带操作系统的延时 ms
 * @param ms 毫秒
 */
void os_delay(uint32_t ms);

/**
 * @brief 获取系统嘀嗒计时 ms
 * @return uint32_t 当前系统 ms
 */
uint32_t millis();

/**
 * @brief GPIO 写入
 */
void GPIO_WritePin(void* port, uint16_t pin, GPIO_PIN_State state);

/**
 * @brief GPIO 读取
 */
GPIO_PIN_State GPIO_ReadPin(void* port, uint16_t pin);

/**
 * @brief GPIO 翻转
 */
GPIO_PIN_State GPIO_Toggle(void* port, uint16_t pin);

} // namespace System

#endif // !__SYSTEM_HPP
