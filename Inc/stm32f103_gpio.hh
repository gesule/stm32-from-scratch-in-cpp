/*
 * stm32f103tx_gpio.hh
 *
 *  Created on: 6 jun. 2022
 *  Author: jesus
 */

#ifndef STM32F103_GPIO_HH_
#define STM32F103_GPIO_HH_

#include "stm32f103.hh"

namespace stm32f103 {

namespace gpio {

constexpr unsigned CRL { 0 };
constexpr unsigned CRH { 4 };
constexpr unsigned IDR { 8 };
constexpr unsigned ODR { 0xc };
constexpr unsigned BSRR { 0x10 };
constexpr unsigned BRR { 0x14 };
constexpr unsigned LCKR { 0x18 };


enum class InputMode { analog, floating, pull_down, pull_up };
enum class OutputMode{ push_pull, open_drain, af_push_pull, af_open_drain };
enum class OutSpeed { medium = 1, low, high };

//enum class AFMode { af0, af1, af2, af3, af4, af5, af6, af7, af8, af9,
//	af10, af11, af12, af13, af14, af15 };



template<mcu_t BASE_ADDRESS, unsigned NUM_IO>
struct IOPin {

	void config(InputMode mode) const {

		ReadWriteSFR<(BASE_ADDRESS + gpio::ODR)> pull_control;

		switch (mode) {
		case InputMode::analog:
			config(0, 0);
			break;
		case InputMode::floating:
			config(1, 0);
			break;
		case InputMode::pull_down:
			pull_control &= ~(1 << NUM_IO);
			config(2, 0);
			break;
		case InputMode::pull_up:
			pull_control |= 1 << NUM_IO;
			config(2, 0);
			break;
		}
	}

	void config(OutputMode mode, OutSpeed speed = OutSpeed::low) const {

		config(static_cast<unsigned>(mode), static_cast<unsigned>(speed));
	}

	/**
	 * La asignación de un valor lógico al PIN, escribe en
	 * el registro de salida.
	 */
	bool operator=(bool state) const {
		WriteOnlySFR<BASE_ADDRESS + gpio::BSRR> bitSetResetReg;
		bitSetResetReg = (state ? 0x01 : 0x0001'0000) << NUM_IO;
		return state;
	}
	/**
	 * Al obtener el valor lógico del pin, se lee el estado del
	 * registro de entrada.
	 */
	operator bool() const {
		ReadOnlySFR<BASE_ADDRESS+gpio::IDR> inputReg;
		return 0 != (inputReg & (1<<NUM_IO));
	}
	/**
	 * Invierte el estado de la salida
	 */
	void toogle() const {
		ReadOnlySFR<BASE_ADDRESS + gpio::ODR> outputReg;
		WriteOnlySFR<BASE_ADDRESS + gpio::BSRR> bitSetReset;

		bitSetReset = (outputReg & (0x01<<NUM_IO) ? 0x01'0000 : 0x0001) << NUM_IO;
	}

private:

	void config(unsigned cnf, unsigned mode) const {

		ReadWriteSFR<(BASE_ADDRESS + (NUM_IO > 7 ? gpio::CRH : gpio::CRL))> config_reg;
		config_reg &= ~(0xF << (4*(NUM_IO % 8)));
		config_reg |= ((cnf<<2) + mode) << (4*(NUM_IO % 8));
	}
};

constexpr IOPin<base_address::GPIOA, 0> PA0;
constexpr IOPin<base_address::GPIOA, 1> PA1;
constexpr IOPin<base_address::GPIOA, 2> PA2;
constexpr IOPin<base_address::GPIOA, 3> PA3;
constexpr IOPin<base_address::GPIOA, 4> PA4;
constexpr IOPin<base_address::GPIOA, 5> PA5;
constexpr IOPin<base_address::GPIOA, 6> PA6;
constexpr IOPin<base_address::GPIOA, 7> PA7;
constexpr IOPin<base_address::GPIOA, 8> PA8;
constexpr IOPin<base_address::GPIOA, 9> PA9;
constexpr IOPin<base_address::GPIOA, 10> PA10;
constexpr IOPin<base_address::GPIOA, 11> PA11;
constexpr IOPin<base_address::GPIOA, 12> PA12;
constexpr IOPin<base_address::GPIOA, 13> PA13;
constexpr IOPin<base_address::GPIOA, 14> PA14;
constexpr IOPin<base_address::GPIOA, 15> PA15;

constexpr IOPin<base_address::GPIOB, 0> PB0;
constexpr IOPin<base_address::GPIOB, 1> PB1;
constexpr IOPin<base_address::GPIOB, 2> PB2;
constexpr IOPin<base_address::GPIOB, 3> PB3;
constexpr IOPin<base_address::GPIOB, 4> PB4;
constexpr IOPin<base_address::GPIOB, 5> PB5;
constexpr IOPin<base_address::GPIOB, 6> PB6;
constexpr IOPin<base_address::GPIOB, 7> PB7;
constexpr IOPin<base_address::GPIOB, 8> PB8;
constexpr IOPin<base_address::GPIOB, 9> PB9;
constexpr IOPin<base_address::GPIOB, 10> PB10;
constexpr IOPin<base_address::GPIOB, 11> PB11;
constexpr IOPin<base_address::GPIOB, 12> PB12;
constexpr IOPin<base_address::GPIOB, 13> PB13;
constexpr IOPin<base_address::GPIOB, 14> PB14;
constexpr IOPin<base_address::GPIOB, 15> PB15;

constexpr IOPin<base_address::GPIOC, 0> PC0;
constexpr IOPin<base_address::GPIOC, 1> PC1;
constexpr IOPin<base_address::GPIOC, 2> PC2;
constexpr IOPin<base_address::GPIOC, 3> PC3;
constexpr IOPin<base_address::GPIOC, 4> PC4;
constexpr IOPin<base_address::GPIOC, 5> PC5;
constexpr IOPin<base_address::GPIOC, 6> PC6;
constexpr IOPin<base_address::GPIOC, 7> PC7;
constexpr IOPin<base_address::GPIOC, 8> PC8;
constexpr IOPin<base_address::GPIOC, 9> PC9;
constexpr IOPin<base_address::GPIOC, 10> PC10;
constexpr IOPin<base_address::GPIOC, 11> PC11;
constexpr IOPin<base_address::GPIOC, 12> PC12;
constexpr IOPin<base_address::GPIOC, 13> PC13;
constexpr IOPin<base_address::GPIOC, 14> PC14;
constexpr IOPin<base_address::GPIOC, 15> PC15;

constexpr IOPin<base_address::GPIOD, 0> PD0;
constexpr IOPin<base_address::GPIOD, 1> PD1;
constexpr IOPin<base_address::GPIOD, 2> PD2;
constexpr IOPin<base_address::GPIOD, 3> PD3;
constexpr IOPin<base_address::GPIOD, 4> PD4;
constexpr IOPin<base_address::GPIOD, 5> PD5;
constexpr IOPin<base_address::GPIOD, 6> PD6;
constexpr IOPin<base_address::GPIOD, 7> PD7;
constexpr IOPin<base_address::GPIOD, 8> PD8;
constexpr IOPin<base_address::GPIOD, 9> PD9;
constexpr IOPin<base_address::GPIOD, 10> PD10;
constexpr IOPin<base_address::GPIOD, 11> PD11;
constexpr IOPin<base_address::GPIOD, 12> PD12;
constexpr IOPin<base_address::GPIOD, 13> PD13;
constexpr IOPin<base_address::GPIOD, 14> PD14;
constexpr IOPin<base_address::GPIOD, 15> PD15;

constexpr IOPin<base_address::GPIOE, 0> PE0;
constexpr IOPin<base_address::GPIOE, 1> PE1;
constexpr IOPin<base_address::GPIOE, 2> PE2;
constexpr IOPin<base_address::GPIOE, 3> PE3;
constexpr IOPin<base_address::GPIOE, 4> PE4;
constexpr IOPin<base_address::GPIOE, 5> PE5;
constexpr IOPin<base_address::GPIOE, 6> PE6;
constexpr IOPin<base_address::GPIOE, 7> PE7;
constexpr IOPin<base_address::GPIOE, 8> PE8;
constexpr IOPin<base_address::GPIOE, 9> PE9;
constexpr IOPin<base_address::GPIOE, 10> PE10;
constexpr IOPin<base_address::GPIOE, 11> PE11;
constexpr IOPin<base_address::GPIOE, 12> PE12;
constexpr IOPin<base_address::GPIOE, 13> PE13;
constexpr IOPin<base_address::GPIOE, 14> PE14;
constexpr IOPin<base_address::GPIOE, 15> PE15;

constexpr IOPin<base_address::GPIOF, 0> PF0;
constexpr IOPin<base_address::GPIOF, 1> PF1;
constexpr IOPin<base_address::GPIOF, 2> PF2;
constexpr IOPin<base_address::GPIOF, 3> PF3;
constexpr IOPin<base_address::GPIOF, 4> PF4;
constexpr IOPin<base_address::GPIOF, 5> PF5;
constexpr IOPin<base_address::GPIOF, 6> PF6;
constexpr IOPin<base_address::GPIOF, 7> PF7;
constexpr IOPin<base_address::GPIOF, 8> PF8;
constexpr IOPin<base_address::GPIOF, 9> PF9;
constexpr IOPin<base_address::GPIOF, 10> PF10;
constexpr IOPin<base_address::GPIOF, 11> PF11;
constexpr IOPin<base_address::GPIOF, 12> PF12;
constexpr IOPin<base_address::GPIOF, 13> PF13;
constexpr IOPin<base_address::GPIOF, 14> PF14;
constexpr IOPin<base_address::GPIOF, 15> PF15;

constexpr IOPin<base_address::GPIOG, 0> PG0;
constexpr IOPin<base_address::GPIOG, 1> PG1;
constexpr IOPin<base_address::GPIOG, 2> PG2;
constexpr IOPin<base_address::GPIOG, 3> PG3;
constexpr IOPin<base_address::GPIOG, 4> PG4;
constexpr IOPin<base_address::GPIOG, 5> PG5;
constexpr IOPin<base_address::GPIOG, 6> PG6;
constexpr IOPin<base_address::GPIOG, 7> PG7;
constexpr IOPin<base_address::GPIOG, 8> PG8;
constexpr IOPin<base_address::GPIOG, 9> PG9;
constexpr IOPin<base_address::GPIOG, 10> PG10;
constexpr IOPin<base_address::GPIOG, 11> PG11;
constexpr IOPin<base_address::GPIOG, 12> PG12;
constexpr IOPin<base_address::GPIOG, 13> PG13;
constexpr IOPin<base_address::GPIOG, 14> PG14;
constexpr IOPin<base_address::GPIOG, 15> PG15;


} // namespace gpio
} // namespace stm32f103

#endif /* STM32F103_GPIO_HH_ */
