/*
 * stm32f103.hh
 *
 *  Created on: 6 jun. 2022
 *  Author: Jesús F. García
 */

#ifndef STM32F103_HH_
#define STM32F103_HH_
#include <stdint.h>

namespace stm32f103 {

using mcu_t = uint32_t;
using sfr_t = volatile mcu_t;


template<mcu_t ADDRESS> struct ReadWriteSFR {

	// Write operator
	mcu_t operator=(mcu_t value) const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");

		*reinterpret_cast<sfr_t*>(ADDRESS) = value;
		return value;
	}

	// Read operator
	operator mcu_t() const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");
		return *reinterpret_cast<const sfr_t*>(ADDRESS);
	}

	void operator &=(mcu_t value) const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");
		*this = *this & value;       // C++20 compatible
	}

	void operator |=(mcu_t x) const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");
		*this = *this | x;          // C++20 compatible
	}
};

template<mcu_t ADDRESS> struct WriteOnlySFR {

	// Write operator
	mcu_t operator=(mcu_t value) const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");
		*reinterpret_cast<sfr_t*>(ADDRESS) = value;
		return value;
	}
};

template<mcu_t ADDRESS> struct ReadOnlySFR {

	// Read operator
	operator mcu_t() const {
		static_assert(ADDRESS != 0, "The SFR address can't be 0");
		return *reinterpret_cast<const sfr_t*>(ADDRESS);
	}
};

namespace base_address {
//---------------------------------------------------------------- ARM M3 ----
// SysTick
constexpr mcu_t STCSR { 0xe000e010 }; // SysTick Control and status register.
constexpr mcu_t STRVR { 0xe000e014 }; // RW, Systick reload value register.
constexpr mcu_t STCVR { 0xe000e018 }; // RW, Systick current value register.
constexpr mcu_t STCR  { 0xe000e01c }; // RO, Systick calibration value register.

//---------------------------------------------------------- MCU specific ----

constexpr mcu_t GPIOA { 0x4001'0800 };
constexpr mcu_t GPIOB { 0x4001'0c00 };
constexpr mcu_t GPIOC { 0x4001'1000 };
constexpr mcu_t GPIOD { 0x4001'1400 };
constexpr mcu_t GPIOE { 0x4001'1800 };
constexpr mcu_t GPIOF { 0x4001'1c00 };
constexpr mcu_t GPIOG { 0x4001'2000 };

constexpr mcu_t RCC { 0x4002'1000 };

};

namespace systick {
ReadWriteSFR<(base_address::STCSR)> STCSR;	// RW, SysTick Control and status register.
ReadWriteSFR<(base_address::STRVR)> STRVR;  // RW, Systick reload value register.
ReadWriteSFR<(base_address::STCVR)> STCVR;  // RW, Systick current value register.
ReadOnlySFR<(base_address::STCR)> STCR;     // RO, Systick calibration value register.

namespace stcsr_bit {
constexpr mcu_t ENABLE { 1 };
constexpr mcu_t TICINT { 2 };
constexpr mcu_t CLKSOURCE { 4 };
constexpr mcu_t COUNTFLAG { 0x00010000 };
} // namespace stcsr_bit
} // namespace systick

namespace rcc_offset {
constexpr unsigned CR { 0 };
constexpr unsigned CFGR { 4 };
constexpr unsigned CIR { 8 };
constexpr unsigned APB2RSTR { 0xc };
constexpr unsigned APB1RSTR { 0x10 };
constexpr unsigned AHBENR { 0x14 };
constexpr unsigned APB2ENR { 0x18 };
constexpr unsigned APB1ENR { 0x1C };
constexpr unsigned BDCR { 0x20 };
constexpr unsigned CSR { 0x24 };

} // namespace rcc_offset

namespace rcc {

constexpr ReadWriteSFR<(base_address::RCC + rcc_offset::APB2ENR)> APB2ENR;

namespace apb2enr {

constexpr mcu_t AFIOEN { 1 };
constexpr mcu_t IOPAEN { 1<<2 };
constexpr mcu_t IOPBEN { 1<<3 };
constexpr mcu_t IOPCEN { 1<<4 };
constexpr mcu_t IOPDEN { 1<<5 };
constexpr mcu_t IOPEEN { 1<<6 };
constexpr mcu_t IOPFEN { 1<<7 };
constexpr mcu_t IOPGEN { 1<<8 };
constexpr mcu_t ADC1EN { 1<<9 };
constexpr mcu_t ADC2EN { 1<<10 };
constexpr mcu_t TIM1EN { 1<<11 };
constexpr mcu_t SPI1EN { 1<<12 };
constexpr mcu_t TIM8EN { 1<<13 };
constexpr mcu_t USART1EN { 1<<14 };
constexpr mcu_t ADC3EN { 15 };
constexpr mcu_t TIM9EN { 19 };
constexpr mcu_t TIM10EN { 20 };
constexpr mcu_t TIM11EN { 21 };

} // namespace apb2enr
} // namespace rcc


}
#endif /* STM32F103_HH_ */
