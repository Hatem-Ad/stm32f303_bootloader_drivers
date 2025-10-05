#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

extern uint32_t V_SystemCoreClock; // Global system clock frequency (Hz)

/**
 * @brief  Initializes the SysTick timer to generate an interrupt every N ticks per second.
 * 
 * This function configures the SysTick hardware timer to generate periodic 
 * interrupts at a user-specified rate (typically 1000 Hz → 1 ms period).
 * The SysTick interrupt handler increments an internal counter (g_msTicks)
 * used for timing and delay operations.
 *
 * @param[in] ticks_per_second  Desired interrupt frequency in Hertz (e.g., 1000 for 1 ms tick).
 *
 * @note Must be called once at system startup before using delay or timeout functions.
 *       Uses SystemCoreClock to compute the reload value.
 */
void SYSTICK_Init(uint32_t ticks_per_second);

/**
 * @brief  Returns the current tick count in milliseconds since SysTick initialization.
 *
 * This function reads the global counter incremented by SysTick interrupts.
 * It provides a millisecond-level time base for delay and timeout operations.
 *
 * @return Current system tick count (in milliseconds).
 *
 * @note This value rolls over after approximately 49 days (32-bit overflow).
 */
uint32_t SYSTICK_GetTick(void);

/**
 * @brief  Blocking delay function.
 *
 * This function implements a simple busy-wait delay using the SysTick tick counter.
 * The CPU remains in a polling loop until the specified number of milliseconds has elapsed.
 *
 * @param[in] ms  Delay duration in milliseconds.
 *
 * @note This function is blocking and halts CPU execution during the delay.
 *       Use only for short delays or debugging; prefer timer interrupts for long waits.
 */
void SYSTICK_Delay(uint32_t ms);

/**
 * @brief  SysTick interrupt handler.
 *
 * This function is automatically called every time the SysTick timer
 * reaches zero (i.e., at the configured tick rate, typically every 1 ms).
 * It increments the internal millisecond counter `V_g_msTicks`, which
 * provides a system time base for delays and timeout measurements.
 *
 * @note
 *  - Do not call this function manually; it is invoked by hardware.
 *  - Ensure `SYSTICK_Init()` has been called before interrupts occur.
 *  - The `V_g_msTicks` variable should be declared as `volatile` to prevent compiler optimization.
 */
void SYSTICK_Handler(void);

#endif // SYSTICK_H