#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

// Initialize SysTick to generate an interrupt every 1 ms
void SysTick_Init(uint32_t ticks_per_second);

// Returns the current tick count (msà)
uint32_t SysTick_GetTick(void);

// Simple delay function in ms
void SysTick_Delay(uint32_t ms);

#endif // SYSTICK_H