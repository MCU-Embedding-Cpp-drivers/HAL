#ifndef __UNITCONVERTER_HPP
#define __UNITCONVERTER_HPP

#include <SystemTypes.hpp>

namespace UnitConverter {
	// 时间转换子类
	class Time {
	public:
		constexpr static uint32_t ns2us(uint64_t ns) {
			return (uint32_t)(ns / 1000ULL);
		}
		constexpr static uint64_t us2ns(uint32_t us) {
			return (uint64_t)us * 1000ULL;
		}
		constexpr static uint32_t us2s(uint64_t us) {
			return (uint32_t)(us / 1000000ULL);
		}
		constexpr static uint64_t s2us(uint32_t s) {
			return (uint64_t)s * 1000000ULL;
		}
		constexpr static uint32_t ns2s(uint64_t ns) {
			return (uint32_t)(ns / 1000000000ULL);
		}
		constexpr static uint64_t s2ns(uint32_t s) {
			return (uint64_t)s * 1000000000ULL;
		}
	};

	// 频率转换子类
	class Frequency {
	public:
		constexpr static uint32_t hz2mhz(uint32_t Hz) {
			return Hz / 1000000U;
		}
		constexpr static uint64_t mhz2hz(uint32_t MHz) {
			return static_cast<uint64_t>(MHz) * 1000000ULL;
		}
	};
};

#endif // __UNITCONVERTER_HPP
