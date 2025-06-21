#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

void FLASH_Unlock(void);
void FLASH_Lock(void);
void Flash_EraseAppArea(void);
void Flash_Write(uint32_t address, uint8_t *data, uint32_t length);

#endif;