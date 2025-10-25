#include "FLASH.h"
#include "STM32F3xx.h" // needed for Flash operations, give the access to flash registers via CMSIS

// ================= Internal Helpers =================
// These functions are declared as 'statis' to restrict thier visibiliity to this translation unit only
// Misra-C:2004 rule 8.8 compliant


// Wait until BSY flag clears, or timeout eccurs then check and clear flags
static FlashStatus_t FLASH_WaitBusyAndCheck(void) 
{
    uint32_t spins = 0U;

    while ((FLASH->SR & C_FLASH_SR_BSY) != 0U)
    {
        spins++;
        if (spins > C_FLASH_TIMEOUT_SPINS)
        {
            return E_FLASH_ERR_TIMEOUT;
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
        return E_FLASH_ERR_WRITE;
    }

    // Programming error
    if ((FLASH->SR &C_FLASH_SR_PGERR) != 0)
    {
        FLASH->SR = C_FLASH_SR_PGERR;
        return E_FLASH_ERR_WRITE;
    }

    return E_FLASH_OK;

}

//Validate that address range lies inside app area
static inline uint32_t FLASH_RangeValid(uint32_t addr, uint32_t len)
{
    if (len == 0U) return 0;
    if (addr < C_FLASH_APP_BASE) return 0;
    if (addr > C_FLASH_END_ADDR) return 0;
    if (len > (C_FLASH_END_ADDR - addr + 1U)) return 0;
    return 1;
}

// ================= Public API =================


FlashStatus_t FLASH_Unlock(void)
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

        // Verify unclock success
        if ((FLASH->CR & C_FLASH_CR_LOCK) != 0)
        {
            return E_FLASH_ERR_LOCK; // Unclock fail
        }
    }
    return E_FLASH_OK; // Unlock done
}

void FLASH_Lock(void)
{
    // Set the lock bit
    FLASH->CR |= C_FLASH_CR_LOCK;
}

void FLASH_ClearFlags(void)
{
    FLASH->SR = C_FLASH_SR_EOP | C_FLASH_SR_PGERR | C_FLASH_SR_WRPERR;
}

FlashStatus_t FLASH_ErasePage(uint32_t page_addr)
{
    FlashStatus_t status;
    uint32_t valid;

    if((page_addr % C_FLASH_PAGE_SIZE) != 0)
    {
        return E_FLASH_ERR_ALIGN;
    }

    valid = FLASH_RangeValid(page_addr, C_FLASH_PAGE_SIZE);
    if(valid == 0)
    {
        return E_FLASH_ERR_RANGE;
    }

    status = FLASH_WaitBusyAndCheck();
    if (status != E_FLASH_OK)
    {
        return status;
    }

    // Tells the controller we want to do a page erase operation.
    FLASH->CR |= C_FLASH_CR_PER;
    // Load the page address into the Flash Address Register.
    FLASH->AR = page_addr;
    // Begins the erase operation on the page given at the address in AR.
    FLASH->CR |= C_FLASH_CR_START;

    status = FLASH_WaitBusyAndCheck();

    if (FLASH->SR & C_FLASH_SR_EOP)
    {
        FLASH->SR = C_FLASH_SR_EOP;  // clear EOP after erase
    }

    FLASH->CR &= ~C_FLASH_CR_PER;

    return (status == E_FLASH_OK) ? E_FLASH_OK : E_FLASH_ERR_ERASE;

}

FlashStatus_t FLASH_EraseAppArea(void)
{
    FlashStatus_t status;
    uint32_t pageAddr = C_FLASH_APP_BASE;
    uint32_t valid;

    while (pageAddr < C_FLASH_END_ADDR)
    {
        valid = FLASH_RangeValid(pageAddr, C_FLASH_PAGE_SIZE);
        if (valid == 0U)
        {
            return E_FLASH_ERR_RANGE;
        }

        status = FLASH_WaitBusyAndCheck();
        if (status != E_FLASH_OK) 
        {
            return status;
        }

        // Set page erase bit and page address
        FLASH->CR |= C_FLASH_CR_PER;
        FLASH->AR = pageAddr;
        FLASH->CR |= C_FLASH_CR_START;


        status = FLASH_WaitBusyAndCheck();
        FLASH->CR &= ~C_FLASH_CR_PER;
        if (status != E_FLASH_OK) 
        {
            return E_FLASH_ERR_WRITE;
        }

        // Check errors
        if (FLASH->SR & (C_FLASH_SR_PGERR | C_FLASH_SR_WRPERR))
        {
            FLASH->CR &= ~C_FLASH_CR_PER;
            return E_FLASH_ERR_WRITE;
        }

        pageAddr += C_FLASH_PAGE_SIZE;
    }
    
    return E_FLASH_OK;
}

FlashStatus_t FLASH_Write(uint32_t address, const uint8_t *data, uint32_t length)
{
    FlashStatus_t status;
    uint32_t i;
    uint16_t half;
    uint32_t valid;

    if (((address % 2U) != 0U) || ((length % 2) != 0U))
    {
        return E_FLASH_ERR_ALIGN;
    }

    valid = FLASH_RangeValid(address, length);
    if (valid == 0U)
    {
        return E_FLASH_ERR_RANGE;
    }

    status = FLASH_WaitBusyAndCheck();
    if (status != E_FLASH_OK)
    {
        return status;
    }

    FLASH->CR |= C_FLASH_CR_PG;

    for(i = 0U; i < length; i+=2U)
    {
        half = (uint16_t)(data[i] | ((uint16_t)data[i+1U] << 8U));
        *(__IO uint16_t *)(address + i) = half;

        status = FLASH_WaitBusyAndCheck();
        if (status != E_FLASH_OK)
        {
            FLASH->CR = (FLASH->CR & (~(C_FLASH_CR_PG)));
            return E_FLASH_ERR_WRITE;
        }
    }
    
    FLASH->CR &= ~C_FLASH_CR_PG;
    return E_FLASH_OK;
}
