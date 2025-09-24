#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

// Flash memory layout (adjust for the STM32f303 variant)
#define FLASH_PAGE_SIZE     (2048U) //2KB
#define FLASH_APP_BASE      (0x08004000UL) // User app start (16 KB offset)
#define FLASH_END_ADDR      (0x08040000UL) // End of 256KB flash

// Spin timeout for Flash operations
#define FLASH_TIMEOUT_SPINS (500000UL)

// ================= Status codes =================
typedef enum 
{
    FLASH_OK = 0,
    FLASH_ERR_LOCK,
    FLASH_ERR_ALIGN,
    FLASH_ERR_RANGE,
    FLASH_ERR_TIMEOUT,
    FLASH_ERR_WRITE,
    FLASH_ERR_ERASE
} FlashStatus_t;

// ================= Public API =================

/**
 * @brief Unlocks flash control register.
 * @return FLASH_OK if unlocked, FLASH_ERR_LOCK if still locked.
 */
FlashStatus_t Flash_Unlock(void);

/**
 * @brief Locks flash control register (sets LOCK bit).
 */
void Flash_Lock(void);


/**
 * @brief Clears all relevant flash status flags (EOP, PGERR, WRPERR).
 */
void Flash_ClearFlags(void);

/**
 * @brief Erases one flash page at given address.
 * @param page_addr Must be page-aligned and inside application area.
 * @return Status code.
 */
FlashStatus_t Flash_ErasePage(uint32_t page_addr);

 /**
 * @brief Erases all flash pages in the application area.
 * @return Status code.
 */
FlashStatus_t Flash_EraseAppArea(void);

/**
 * @brief Writes data to flash in half-word (16-bit) units.
 * @param addr Start address (must be half-word aligned).
 * @param data Pointer to data buffer.
 * @param len  Length in bytes (must be even).
 * @return Status code.
 */
FlashStatus_t Flash_Write(uint32_t address, uint8_t *data, uint32_t length);

#endif