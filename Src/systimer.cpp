/*
 * systimer.cpp
 *
 *  Created on: 7 jun. 2022
 *  Author: jesus
 */

#include <systimer.hh>

static volatile uint32_t systick_global_counter = 0;

uint32_t get_tick_counter(){
	return systick_global_counter;
}


extern "C" void SysTick_Handler(void)
{
	systick_global_counter = systick_global_counter + 1; 		// C++20 compatible
}



