/*
 * systimer.h
 *
 *  Created on: 7 jun. 2022
 *  Author: jesus
 */

#ifndef SYSTIMER_HH_
#define SYSTIMER_HH_

#include <stdint.h>

uint32_t get_tick_counter();

class TimeOut {
public:
	TimeOut(uint32_t p) : period{p} {
		reset();
	}

	void reset() {
		timestamp = get_tick_counter();
	}

	operator bool() const {
		return (get_tick_counter() - timestamp) > period;
	}

private:
	uint32_t period;
	uint32_t timestamp;
};





#endif /* SYSTIMER_HH_ */
