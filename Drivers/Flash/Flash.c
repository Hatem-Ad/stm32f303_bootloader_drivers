#include "Flash.h"
#include "STM32F3xx.h" // needed for Flash operations, give the access to flash registers via CMSIS

// ================= Internal Helpers =================
// These functions are declared as 'statis' to restrict thier visibiliity to this translation unit only
// Misra-C:2004 rule 8.8 compliant


// Wait until BSY flag clears, or timeout eccurs then check and clear flags
static FlashStatus_t Flash_WaitBusyAndCheck(void) 
{
    uint32_t spins = 0U;

    while ((FLASH->SR & C_FLASH_SR_BSY) != 0U)
    {
        spins++;
        if (spins > FLASH_TIMEOUT_SPINS)
        {
            return FLASH_ERR_TIMEOUT;
        }
    }
    
    // Clear end of operation (write 1 to clear)
    if ((FLASH->SR & C_FLASH_SR_EOP) != 0U)
    {
        FLASH->SR = C_FLASH_SR_EOP;
    }

    // Write Protection error
    if ((FLASH->SR & C_FLASH_SR_WRPERR) != 0)
    {
        FLASH->SR = C_FLASH_SR_WRPERR;
        return FLASH_ERR_WRITE;
    }

    // Programming error
    if ((FLASH->SR &C_FLASH_SR_PGERR) != 0)
    {
        FLASH->SR = C_FLASH_SR_PGERR;
        return FLASH_ERR_WRITE;
    }

    return FLASH_OK;

}

//Validate that address range lies inside app area
static inline int Flash_RangeValid(uint32_t addr, uint32_t len)
{
    int valid = 0;

    if ((addr >= C_FLASH_APP_BASE && ((addr + len) <= C_FLASH_END_ADDR)))
    {
        valid = 1;
    }

    return valid;
}

// ================= Public API =================


FlashStatus_t Flash_Unlock(void)
{
    //Check if the Flash control register is locked
    if (FLASH->CR & C_FLASH_CR_LOCK)
    {
        //Write the two key values to unclock flash programming
        // Hard coded values, set by the status engineers 
        // Key1 : 0x45670123UL
        // Key2 : 0xCDEF89ABUL
        FLASH->KEYR = C_FLASH_KEY1;
        FLASH->KEYR = C_FLASH_KEY2;

        if ((FLASH->CR & C_FLASH_CR_LOCK) != 0)
        {
            return FLASH_ERR_LOCK;
        }
    }
    return FLASH_OK;
}

void Flash_Lock(void)
{
    // Set the lock bit
    FLASH->CR |= C_FLASH_CR_LOCK;
}

void Flash_ClearFlags(void)
{
    FLASH->SR = C_FLASH_SR_EOP | C_FLASH_SR_PGERR | C_FLASH_SR_WRPERR;
}

FlashStatus_t Flash_ErasePage(uint32_t page_addr)
{
    FlashStatus_t status;

    if((page_addr % C_FLASH_PAGE_SIZE) != 0)
    {
        return FLASH_ERR_ALIGN;
    }

    if(Flash_RangeValid(page_addr, C_FLASH_PAGE_SIZE) == 0)
    {
        return FLASH_ERR_RANGE;
    }

    status = Flash_WaitBusyAndCheck();
    if (status != FLASH_OK)
    {
        return status;
    }

    // Tells the controller we want to do a page erase operation.
    FLASH->CR |= C_FLASH_CR_PER;
    // Load the page address into the Flash Address Register.
    FLASH->AR = page_addr;
    // Begins the erase operation on the page given at the address in AR.
    FLASH->CR = C_FLASH_CR_START;

    status = Flash_WaitBusyAndCheck();
    FLASH->CR &= ~C_FLASH_CR_PER;

    return (status == FLASH_OK) ? FLASH_OK : FLASH_ERR_ERASE;

}

FlashStatus_t Flash_EraseAppArea(void)
{
    uint32_t addr;
    FlashStatus_t status;

    for(addr = C_FLASH_APP_BASE; addr < C_FLASH_END_ADDR; addr += C_FLASH_PAGE_SIZE)
    {
        status = Flash_ErasePage(addr);
        if(status != FLASH_OK)
        {
            return status;
        }
    }

    return FLASH_OK;
}

FlashStatus_t Flash_Write(uint32_t addr, const uint8_t *data, uint32_t len)
{
    FlashStatus_t status;
    uint32_t i;
    uint16_t half;

    if (((addr % 2U) != 0U) || ((len % 2) != 0U))
    {
        return FLASH_ERR_ALIGN;
    }

    if (Flash_RangeValid(addr, len) == 0)
    {
        return FLASH_ERR_ALIGN;
    }

    status = Flash_WaitBusyAndCheck();
    if (status != FLASH_OK)
    {
        return status;
    }

    FLASH->CR |= C_FLASH_CR_PG;

    for(i = 0U; i < len; i+=2U)
    {
        half = (uint16_t)(data[i] | ((uint16_t)data[i+1U] << 8U));
        *(__IO uint16_t *)(addr +1) = half;

        status = Flash_WaitBusyAndCheck();
        if (status != FLASH_OK)
        {
            FLASH->CR = (FLASH->CR & (~(C_FLASH_CR_PG)));
            return FLASH_ERR_WRITE;
        }
    }
    FLASH->CR = FLASH->CR & (~C_FLASH_CR_PG);
    return FLASH_OK;
}