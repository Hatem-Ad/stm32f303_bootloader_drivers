#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

// Flash memory layout (adjust for the STM32f303 variant)
#define FLASH_PAGE_SIZE     2048U //2KB
#define FLASH_APP_BASE      (0x08004000UL) // User app start (16 KB offset)
#define FLASH_END_ADDR      (0x08040000UL) // End of 256KB flash

// Spin timeout for Flash operations
#define FLASH_TIMEOUT_SPINS (500000UL)


void FLASH_Lock(void);
void Flash_EraseAppArea(void);
void Flash_Write(uint32_t address, uint8_t *data, uint32_t length);

#endif