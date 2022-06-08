/*
 * arm_m3.h
 *
 *  Created on: 7 jun. 2022
 *  Author: jesus
 */

#ifndef ARM_M3_H_
#define ARM_M3_H_


inline void disable_irq() {
	__asm volatile ("cpsid i");
}

inline void enable_irq() {
	__asm volatile ("cpsie i");
}

inline void breakpoint()
{
	__asm volatile ("bkpt #0");
}




#endif /* ARM_M3_H_ */
