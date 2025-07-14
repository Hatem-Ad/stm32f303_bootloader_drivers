#include "Flash.h"
#include "stm32f3xx.h" // needed for Flash erase, give the access to flash registers via CMSIS

void Flash_Unlock(void)
{
    //Check if the Flash control register is locked
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        //Write the two key values to unclock flash programming
// Hard coded values, set by the st engineers 
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void Flash_Lock(void)
{
    // Set the lock bit
    FLASH->CR|= FLASH_CR_LOCK;
}

void Flash_Erase(uint32_t addr)
{
    //Set the Page Erase bit (PER) to configure the the flash memory for the page erase mode.
    FLASH->CR|= FLASH_CR_PER;
    //Write the target address in the flash address register for specifie the which flash page should be erase.
    FLASH->AR = addr;
    //Sets the start bit in the flash control register to begin erase operation.
    FLASH->CR|= FLASH_CR_START;
    //This loop block the CPU until erase finishes (hardware clears BSY)
    while(FLASH_SR & FLASH_SR_BSY);
    //Clear the Page Erase bit in CR to exit the erase mode.
    FLASH->CR &= ~FLASH_CR_PER;
}

void Flash_Write(uint32_t addr, uint8_t *data, uint32_t len)
{
    for (uint32_t i = 0; i < len; i +=2)
    {
        FLASH->CR |= FLASH_CR_PG;
        *
    }
    
}