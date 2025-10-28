#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

// Flash memory layout (adjust for the STM32f303 variant)
//---#define C_FLASH_PAGE_SIZE     (0x800U)          // 2KB per page
//---#define C_FLASH_APP_BASE      (0x08004000UL)    // User app start (16 KB offset)
#define C_FLASH_END_ADDR      (0x0803FFFFUL)    // End of 256KB flash
#define C_FLASH_TIMEOUT_SPINS (500000UL)        // Simple busy-wait timeout

// ================= Status codes =================
typedef enum 
{
    E_FLASH_OK = 0,        /* Operation successful */
    E_FLASH_ERR_TIMEOUT,   /* Busy flag did not clear in time */
    E_FLASH_ERR_WRITE,     /* Programming or write-protect error */
    E_FLASH_ERR_ERASE,     /* Page erase failed */
    E_FLASH_ERR_ALIGN,     /* Address or length not aligned (half-word) */
    E_FLASH_ERR_RANGE,     /* Address out of allowed app flash area */
    E_FLASH_ERR_LOCK       /* Could not unlock flash control register */
} FlashStatus_t;

// ================= Public API =================

/**
 * @brief Unlocks flash control register.
 * @return FLASH_OK if unlocked, FLASH_ERR_LOCK if still locked.
 */
FlashStatus_t FLASH_Unlock(void);

/**
 * @brief Locks flash control register (sets LOCK bit).
 */
void FLASH_Lock(void);


/**
 * @brief Clears all relevant flash status flags (EOP, PGERR, WRPERR).
 */
void FLASH_ClearFlags(void);

/**
 * @brief Erases one flash page at given address.
 * @param page_addr Must be page-aligned and inside application area.
 * @return Status code.
 */
FlashStatus_t FLASH_ErasePage(uint32_t page_addr);

 /**
 * @brief Erases all flash pages in the application area.
 * @return Status code.
 */
FlashStatus_t FLASH_EraseAppArea(void);

/**
 * @brief Writes data to flash in half-word (16-bit) units.
 * @param addr Start address (must be half-word aligned).
 * @param data Pointer to data buffer.
 * @param len  Length in bytes (must be even).
 * @return Status code.
 */
FlashStatus_t FLASH_Write(uint32_t address, uint8_t *data, uint32_t length);

#endif