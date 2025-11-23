#ifndef __SYSTEMTYPES_HPP
#define __SYSTEMTYPES_HPP

#include <cstdint>

enum class ErrorCode : uint16_t{
    OK = 0, // 成功
    InvalidParam,   // 参数错误
    Timeout,    // 超时
    Busy,   // 忙碌
    Fail,   // 一般错误
};

/**
 * @brief 通用回调封装类（模板版）
 *
 * 设计目标：
 * - 允许存储一个函数指针，并与一个对象实例绑定。
 * - 之后在调用时，可以像普通函数一样调用，但实际上会自动把对象指针传进去。
 *
 * 模板参数：
 *   T        —— 需要绑定的对象类型
 *   Args...  —— 回调函数的参数列表（可变参数模板）
 */
template<typename T, typename... Args>
class Callback {
public:

	/**
	 * @brief 定义函数指针类型
	 *
	 * - `Func` 表示一种函数类型：void f(T*, Args...)
	 * - 第一个参数必须是 `T*`（即对象指针）
	 * - 后面参数 `Args...` 可以是任意多个（可变参数模板展开）
	 */
	using Func = void (*)(T*, Args...);

	/**
	 * @brief 构造函数，绑定函数和对象
	 *
	 * @param f   要绑定的函数指针，函数形式必须是 `void f(T*, Args...)`
	 * @param obj 需要绑定的对象指针（在调用时会自动传递给函数）
	 *
	 * 例如：
	 *   void onTimerEvent(MyClass* self, int value);
	 *   MyClass obj;
	 *   Callback<MyClass, int> cb(onTimerEvent, &obj);
	 */
	Callback(Func f, T* obj) : _f(f), _obj(obj) {}

	/**
	 * @brief 回调调用操作符（函数对象）
	 *
	 * - 让 Callback 对象可以像函数一样被调用。
	 * - 当执行 cb(args...) 时，实际上会调用：_f(_obj, args...)
	 *
	 * @param args... 调用时传入的参数（会匹配到 Args...）
	 */
	void operator()(Args... args) {
		_f(_obj, args...);
	}

private:
	Func _f; ///< 存储的函数指针
	T* _obj; ///< 存储的对象指针
};


#endif //! __SYSTEMTYPES_HPP
