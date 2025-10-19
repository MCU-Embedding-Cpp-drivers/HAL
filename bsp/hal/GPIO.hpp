#ifndef __GPIO_HPP
#define __GPIO_HPP

#include "System.hpp"
#include <SystemTypes.hpp>

class GPIO
{
  public:
	/**	@brief GPIO配置模式，参照芯片手册选择 */
	enum class Mode : uint8_t {
		INPUT = 0,			// 输入模式
		OUTPUT_PUSHPULL,	// 推挽输出
		OUTPUT_OPENDRAIN,	// 开漏输出
		AF_PUSHPULL,		// 复用推挽输出
		AF_OPENDRAIN,		// 复用开漏输出
		ANALOG,				// 模拟输入
		IT_RISING,			// 上升沿中断
		IT_FALLING,			// 下降沿中断
		IT_RISING_FALLING,	// 双边沿中断
		EVT_RISING,			// 上升沿事件
		EVT_FALLING,		// 下降沿事件
		EVT_RISING_FALLING, // 双边沿事件
	};

	/** @brief GPIO输出的最大速率，具体速率参照芯片手册 */
	enum class Speed : uint8_t {
		LOW = 0,   // 低频
		MEDIUM,	   // 中等频率
		HIGH,	   // 高频
		VERY_HIGH, // 非常高频
	};

	/** @brief GPIO上下拉模式 */
	enum class Pull : uint8_t {
		NO = 0,	  // 无上下拉
		PULLUP,	  // 上拉
		PULLDOWN, // 下拉
	};

	/**
	 * @brief 构造一个GPIO对象
	 *
	 * @param port
	 * @param pin
	 * @note 由于只设定了IO位置，所以可以作为全局变量初始化
	 */
	GPIO(void* port, uint16_t pin);

	/* 一般也不会用到下面几个函数，这个库的设计思路就是在CubeMX基础上配置好了IO的
		如果一定要使用就自行实现一下，感觉如果把init都重新封装一下就有点，抽象程度不够高了？
		而且写起来可能会有误区，不过最好就是像XRobot那样，直接解析.ioc，然后从那里面直接读出来init，配置到自己的工程中
		但是目前没有这个技术能力，就先只适配到这一层吧
	*/
	ErrorCode init(Mode mode,Speed speed,Pull pull);	// GPIO初始化
	ErrorCode init(Mode mode,Speed speed,Pull pull,uint32_t alternate);	// 带复用功能的GPIO初始化
	ErrorCode deinit();

	/**
	 * @brief GPIO写入
	 *
	 * @param level 高低电平(0/1)
	 */
	void write(bool level);

	/**
	 * @brief GPIO读取
	 *
	 * @return true 高
	 * @return false
	 */
	bool read();

	/**
	 * @brief GPIO电平翻转
	 *
	 */
	void toggle();

  private:
	void*	 _port;
	uint16_t _pin;
};

#endif //! __GPIO_HPP
