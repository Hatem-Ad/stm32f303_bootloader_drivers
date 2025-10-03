#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdint.h>


#define C_APP_START_ADDRESS       0x08004000U     // App start address after bootloader
#define C_APP_END_ADDRESS         0x0803FFFFUL    // App end address after bootloader (256KB flash)
#define C_FW_CHUNK_SIZE           256             // Byte per chunk
#define C_BL_TRIGGER_PORT         GPIOA           // Trigger port
#define C_BL_TRIGGER_PIN          0               // Trigger pin
#define C_BL_VALID_SRAM_ADDR      0x20000000UL    // SRAM address
#define C_BL_VALID_SRAM_MASK      0x2FFE0000UL    // SRAM mask

// Bootloader jumpReceive status
typedef enum
{
    E_BL_OK = 0,
    E_BL_ERROR
} BootStatus_t;


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
 * @brief  Receives a new firmware image over UART and programs it into Flash.
 *
 * This function:
 *   - Unlocks and erases the application area in Flash
 *   - Receives the firmware in chunks from UART
 *   - Programs each chunk into Flash memory
 *   - Locks the Flash again after the update
 *
 * @note  Firmware data is received in fixed-size chunks (FW_CHUNK_SIZE).
 *        Transfer ends when no more data is received (timeout or 0 bytes).
 *        Function ensures half-word alignment for Flash writes.
 *
 * @retval BL_OK     Firmware update completed successfully
 * @retval BL_ERROR  An error occurred (unlock, erase, write, or UART failure)
 */
BootStatus_t Bootloader_ReceiveFirmware(void);

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
