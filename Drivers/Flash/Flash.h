#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

// Flash memory layout (adjust for the STM32f303 variant)
#define FLASH_PAGE_SIZE     2048U //2KB

void FLASH_Unlock(void);
void FLASH_Lock(void);
void Flash_EraseAppArea(void);
void Flash_Write(uint32_t address, uint8_t *data, uint32_t length);

#endif