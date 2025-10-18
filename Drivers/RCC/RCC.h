#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include "STM32F3xx.h"

/**
 * @brief  Enables the Low-Speed Internal (LSI) oscillator.
 *
 * This function turns on the LSI clock used by peripherals such as
 * the Independent Watchdog (IWDG) and Real-Time Clock (RTC).
 * It waits until the LSI becomes stable before returning.
 *
 * Typical stabilization time: ~100 µs.
 */
void RCC_EnableLSI(void);

#endif