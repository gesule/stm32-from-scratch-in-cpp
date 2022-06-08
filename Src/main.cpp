/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Jesús F. García
 * @brief          : Ensayo de una alternativa c++ al HAL de STM32.
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Jesús F. García
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <systimer.hh>
#include "stm32f103_gpio.hh"
#include "stm32f103.hh"
#include "arm_m3.h"

using namespace stm32f103;


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void mcu_setup();
mcu_t get_tick_counter();


int main(void)
{
	mcu_setup();

	auto& pcbLed = gpio::PC13;
	pcbLed = true;

	TimeOut timeout {200};
	for(;;) {
		if(timeout){
			timeout.reset();
			pcbLed.toogle();
		}
	}
}


void mcu_setup()
{
	// Enable bus CLK for GPIOC, and configure PC13
	rcc::APB2ENR |= rcc::apb2enr::IOPCEN;
	gpio::PC13.config(gpio::OutputMode::push_pull);

	// Set SysTick to 1ms with 8Mhz System clock
	systick::STRVR = 7999;
	systick::STCVR = 0;
	systick::STCSR = systick::stcsr_bit::ENABLE
			+ systick::stcsr_bit::TICINT
			+ systick::stcsr_bit::CLKSOURCE;

}

