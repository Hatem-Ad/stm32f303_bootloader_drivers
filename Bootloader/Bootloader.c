#include <Core_CortexM4.h>  // For Main Stack Pointer 
#include "Bootloader.h"
#include "GPIO.h"           // Use GPIO pin to trigger bootloader
#include "UART.h"           // Receive firmware over UART
#include "FLASH.h"          // For Flash memory
#include "STM32F3xx.h"
#include "SysTick.h"        // SysTick for delay/timeouts
#include "Types.h"          // Defined types

// -------------------- Local helpers --------------------
static Boolean_t Bootloader_IsValidApp(void)
{
    uint32_t AppStack = *(volatile uint32_t *)C_FLASH_APP_BASE;        // APP MSP
    uint32_t AppReset = *(volatile uint32_t *)(C_FLASH_APP_BASE + 4U); // APP ResetHandler

    // 1. Check that the initial stack pinter is in valid SRAM range
    if ((AppStack > 0x20000000U) || (AppStack > 0x2000FFFFU))
    {
        return FALSE;
    }

    // 2. Check that the reset handler is inside FLASH
    if ((AppReset < C_FLASH_APP_BASE) || (AppReset > C_FLASH_END_ADDR))
    {
        return FALSE;
    }
    
    return TRUE;
}

// -------------------- Bootloader API --------------------

void Bootloader_Init(void) {
    // Initialize peripherals needed for bootloader
    GPIO_InitPort(C_BL_TRIGGER_PORT);

    GPIO_Config(C_BL_TRIGGER_PORT, 
                C_BL_TRIGGER_PIN, 
                GPIO_MODE_INPUT, 
                GPIO_OTYPE_PP, 
                GPIO_SPEED_LOW, 
                GPIO_PULLUP);

    UART_Init();
    UART_SendString("UART OK @72MHz\r\n");
    SysTick_Init(1000);     // 1 ms tick for delays and timeouts
}

uint8_t Bootloader_CheckForUpdate(void) {
    // Check if a specific pin is low to enter update mode
    if (GPIO_Read(C_BL_TRIGGER_PORT, C_BL_TRIGGER_PIN) == 0) {
        return 1U;  // Enter bootloader
    }
    
    return 0U; //Jump to app
}

BootStatus_t Bootloader_ReceiveFirmware(void) 
{
    // Local declaration
    uint8_t buffer[C_FW_CHUNK_SIZE];
    uint32_t addr = C_FLASH_APP_BASE;
    uint32_t received = 0U;
    FlashStatus_t status;

    UART_SendString("BL: erase app area...\r\n");

    // 1. Unlock Flash 
    status = FLASH_Unlock();
    if(status != FLASH_OK)
    {
        UART_SendString("BL: unlock fail\r\n");
        return E_BL_ERROR;
    }

    FLASH_ClearFlags();
    
    // 2. Erase application area
    status = FLASH_EraseAppArea();
    if(status != FLASH_OK)
    {
        UART_SendString("BL: erase fail\r\n");
        FLASH_Lock();
        return E_BL_ERROR;
    }

    UART_SendString("BL: receiving...\r\n");

    // 3. Received data chunks
    while (1)
    {
        received = UART_Receive((char *)buffer, (uint32_t)C_FW_CHUNK_SIZE, C_BL_UART_TIMEOUT); // Blocking read
        if (received == 0)
        {
            break; //assume 0 bytes ol less means "End of transmission"
        }

        if((received & 1U) != 0U)
        {
            buffer[received] = 0xFFU;
            received++;
        }

        // 4. Write to flash
        status = FLASH_Write(addr, buffer, received);
        if (status != FLASH_OK)
        {
            UART_SendString("BL: write fail\r\n");
            FLASH_Lock();
            return E_BL_ERROR;
        }

        // Write
        addr += received;
        UART_SendString("Chunk written. \r\n");
    }

    // Lock flash after update
    FLASH_Lock(); // re-lock the flaash memory
    UART_SendString("Firmware update done. \r\n");
    return E_BL_OK;
}

void Bootloader_JumpToApp(void) {
    
    if(Bootloader_IsValidApp() == FALSE)
    {
        UART_SendString("BL: invalid app \r\n");
        while(1);
    }

    UART_SendString("BL: jumping to app\r\n");

    // Disable interrupts
    __disable_irq();

    SysTick->CTRL = 0; // Disable SysTick before jumping

    // Relocate vector table - give the offset
    SCB->VTOR = C_FLASH_APP_BASE & 0xFFFFFF00UL;
    
    // Set MSP from app's vector table to load new stack pointer
    __set_MSP(AppStack);

    // For synchronization barriers
    __DSB();
    __ISB();
    
    // Set reset handler address
    App_reset_handler = (void (*)(void))reset;
    
    // Jump to application
    App_reset_handler(); // if it arrived here, never returns
}

void Bootloader_run() {
    //Init phase 
    Bootloader_Init();
    
    //Check the bootloader update
    if (Bootloader_CheckForUpdate()) {
        // Reciever a new firmware UART
        if (Bootloader_ReceiveFirmware() == E_BL_OK)
        {
            UART_SendString("BL: update successful\r\n");
            Bootloader_JumpToApp(); //Jump to user application in flash
        }
        else
        {
            UART_SendString("BL: update failed, staying in bootloader\r\n");
            while (1)
            {
                GPIO_Toggle(GPIOE, 9);
                SysTick_DelayMs(500);
            }
        } 
    } 
    else 
    {
        UART_SendString("BL: jumping to app\r\n");
        Bootloader_JumpToApp();
    }

}

