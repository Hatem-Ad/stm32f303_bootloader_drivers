#ifndef WDG_H
#define WDG_H

#include <stdint.h>
#include "STM32F3xx.h"

/**
 * @brief  Initialize and start the Independent Watchdog (IWDG)
 * @param  prescaler_code: prescaler (C_IWDG_PR_DIVx)
 * @param  reload: reload value (0..4095)
 */
void WDG_InitRaw(uint8_t prescaler_code, uint16_t reload);

/**
 * @brief  Initialize the IWDG with a given timeout in milliseconds.
 *         Automatically calculates prescaler + reload combination.
 * @param  timeout_ms: timeout period in milliseconds
 */
void WDG_Init_ms(uint32_t timeout_ms);

/**
 * @brief  Refresh (reload) the watchdog counter.
 *         Call periodically before timeout to avoid system reset.
 */
void WDG_Refresh(void);


#endif // WDG_H