#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdint.h>


#define C_APP_START_ADDRESS       0x08004000U     // App start address after bootloader
#define C_FW_CHUNK_SIZE           256             // Byte per chunk
#define C_BL_TRIGGER_PORT         GPIOA           // Trigger port
#define C_BL_TRIGGER_PIN          0               // Trigger pin
#define C_BL_VALID_SRAM_ADDR      0x20000000UL    // SRAM address
#define C_BL_VALID_SRAM_MASK      0x2FFE0000UL    // SRAM mask

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

/**
 * @brief Executes the main bootloader logic.
 *
 * Initializes peripherals, checks for firmware update trigger,
 * receives new firmware if needed, and jumps to the user application.
 */
void Bootloader_run(void);

#endif 
