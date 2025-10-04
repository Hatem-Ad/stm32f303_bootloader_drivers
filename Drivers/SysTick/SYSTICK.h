#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

extern uint32_t V_SystemCoreClock; // CPU freq in Hz

// Initialize SysTick to generate an interrupt every 1 ms
void SYSTICK_Init(uint32_t ticks_per_second);

// Returns the current tick count (ms)
uint32_t SYSTICK_GetTick(void);

// Simple delay function in ms
void SYSTICK_Delay(uint32_t ms);

#endif // SYSTICK_H