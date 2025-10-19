#include "GPIO.hpp"
#include "System.hpp"
#include "SystemTypes.hpp"


GPIO::GPIO(void* port, uint16_t pin) : _port(port), _pin(pin) {

}

#ifdef PLATFORM_STM32
#include "stm32g4xx_hal_gpio.h"
// GPIO初始化
ErrorCode GPIO::init(Mode mode, Speed speed, Pull pull){
	
	if (mode == Mode::AF_PUSHPULL || mode == Mode::AF_OPENDRAIN) {
		return ErrorCode::InvalidParam;
	}	// 若使用复用功能，则需要使用带复用功能的GPIO初始化

	GPIO_InitTypeDef GPIO_InitStruct = {
		_pin,
		static_cast<uint32_t>(mode),
		static_cast<uint32_t>(pull),
		static_cast<uint32_t>(speed),
		0
	};
	HAL_GPIO_Init((GPIO_TypeDef*)_port, &GPIO_InitStruct);
	
	return ErrorCode::OK;
}

// 带复用功能的GPIO初始化
ErrorCode GPIO::init(Mode mode, Speed speed, Pull pull, uint32_t alternate){

	GPIO_InitTypeDef GPIO_InitStruct = {
		_pin,
		static_cast<uint32_t>(mode),
		static_cast<uint32_t>(pull),
		static_cast<uint32_t>(speed),
		alternate
	};
	HAL_GPIO_Init((GPIO_TypeDef*)_port, &GPIO_InitStruct);
	return ErrorCode::OK;
}

// 失能
ErrorCode GPIO::deinit(){
	HAL_GPIO_DeInit((GPIO_TypeDef*)_port, _pin);
	return ErrorCode::OK;
}
#endif //! PLATFORM_STM32

/**
 * @brief GPIO写入
 *
 * @param level 高/低电平(1/0)
 */
void GPIO::write(bool level) {
	System::GPIO_WritePin(_port, _pin, level ? 1 : 0);
}

/**
 * @brief GPIO读取
 * 
 * @return 1 高
 * @return 0 低 
 */
bool GPIO::read() {
	return System::GPIO_ReadPin(_port, _pin);
}

/**
 * @brief GPIO电平翻转
 *
 */
void GPIO::toggle() {
	System::GPIO_Toggle(_port, _pin);
}
