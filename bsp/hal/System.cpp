#include "System.hpp"
#include "stm32g4xx_hal_gpio.h"


namespace System {

void delay(uint32_t ms) {
	HAL_Delay(ms); // 调用 STM32 HAL
}

uint32_t millis() {
	return HAL_GetTick(); // SysTick ms
}

void GPIO_WritePin(void* port, uint16_t pin, GPIO_PIN_State state) {
	HAL_GPIO_WritePin((GPIO_TypeDef*)port, pin, (state == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

GPIO_PIN_State GPIO_ReadPin(void* port, uint16_t pin) {
	GPIO_PinState s = HAL_GPIO_ReadPin((GPIO_TypeDef*)port, pin);
	return (s == GPIO_PIN_SET) ? 1 : 0;
}

GPIO_PIN_State GPIO_Toggle(void* port, uint16_t pin){
	HAL_GPIO_TogglePin((GPIO_TypeDef*)port, pin);
	return GPIO_ReadPin(port, pin);
}

} // namespace System
