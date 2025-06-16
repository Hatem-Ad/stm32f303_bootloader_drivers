#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdint.h>

/* Bootloader public API */

/**
 * @brief Initialize bootloader hardware (e.g., clock, peripherals).
 */
void Bootloader_Init(void);

/**
 * @brief Check for update conditions (e.g., pin state, magic value).
 * @return 1 if update mode requested, 0 otherwise.
 */
uint8_t Bootloader_CheckForUpdate(void);

/**
 * @brief Receive firmware image over UART or other comm.
 */
void Bootloader_ReceiveFirmware(void);

/**
 * @brief Jump to main application.
 */
void Bootloader_JumpToApp(void);

#endif /* BOOTLOADER_H */
