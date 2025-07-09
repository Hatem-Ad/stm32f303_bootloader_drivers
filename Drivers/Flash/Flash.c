#include "Flash.h"
#include "stm32f3xx.h" // needed for Flash erase, give the access to flash registers via CMSIS

void Flash_Unlock(void)
{
    //Check if the Flash control register is locked
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        //Write the two key values to unclock flash programming
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}
