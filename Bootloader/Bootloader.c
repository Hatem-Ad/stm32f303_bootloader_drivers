#include <Core_CortexM4.h>  // For Main Stack Pointer 
#include "Bootloader.h"
#include "GPIO.h"  // Use GPIO pin to trigger bootloader
#include "UART.h"  // Receive firmware over UART
#include "FLASH.h" // For Flash memory
#include "STM32F3xx.h"

#define APP_START_ADDRESS 0x08004000U  // App start address after bootloader
#define FW_CHUNK_SIZE 256 //Byte per chunk

void Bootloader_Init(void) {
    // Initialize peripherals needed for bootloader
    GPIO_Init();
    UART_Init();
}

uint8_t Bootloader_CheckForUpdate(void) {
    // Check if a specific pin is low to enter update mode
    if (GPIO_ReadPin(0) == 0) {
        return 1;  // Enter bootloader
    }
    
    return 0; //Jump to app
}

void Bootloader_ReceiveFirmware(void) {
    // Local declaration
    uint8_t buffer[FW_CHUNK_SIZE];
    uint32_t addr = C_FLASH_APP_BASE;
    uint32_t received = 0U;
    FlashStatus_t status;

    UART_SendString("BL: erase app area...\r\n");

    //1. Erase the application aera before writing 
    status = FLASH_Unlock();
    if(status != FLASH_OK)
    {
        UART_SendString("BL: unlock fail\r\n");
        return;
    }

    FLASH_ClearFlags();
    
    // Erase all application pages
    status = FLASH_EraseAppArea();
    if(status != FLASH_OK)
    {
        UART_SendString("BL: erase fail\r\n");
        FLASH_Lock();
        return;
    }

    UART_SendString("BL: receiving...\r\n");

    //2. Received data chunks and write to flash
    while (1)
    {
        received = UART_Received((char *)buffer, (uint32_t)FW_CHUNK_SIZE, C_BL_UART_TIMEOUT); // Blocking read
        if (received == 0)
        {
            break; //assume 0 bytes ol less means "End of transmission"
        }

        if((received & 1U) != 0U)
        {
            buffer[received] = 0xFFU;
            received++;
        }

        // Write to flash
        status = FLASH_Write(addr, buffer, received);
        if (status != FLASH_OK)
        {
            UART_SendString("BL: write fail\r\n");
            FLASH_Lock();
            return;
        }

        // Write
        addr += received;
        UART_SendString("Chunk written. \r\n");
    }

    // Lock flash after update
    FLASH_Lock(); // re-lock the flaash memory
    UART_SendString("Firmware update done. \r\n");
}

void Bootloader_JumpToApp(void) {

    uint32_t msp0 = *(volatile uint32_t *)C_FLASH_APP_BASE; // APP MSP
    uint32_t reset = *(volatile uint32_t *)(C_FLASH_APP_BASE + 4U); // APP ResetHandler
    // Function pointer to application's reset handler
    void (*App_reset_handler)(void);
    
    // Baseic validation
    if ((msp0 & 0x2FFE0000UL) != 0x20000000UL)
    {
        UART_SendString("BL: invalid MSP\r\n");
        return;
    }

    if ((reset < C_FLASH_APP_BASE) || (reset > C_FLASH_END_ADDR))
    {
        UART_SendString("BL: invalid reset vector\r\n");
        return;
    }

    UART_SendString("BL: jumping to app\r\n");

    // Disable interrupts if needed
    __disable_irq();

    // Relocate vector table
    SCB->VTOR = C_FLASH_APP_BASE & 0xFFFFFF00UL;
    
    // Set MSP from app's vector table to load app stack
    __set_MSP(msp0);

    __DSB();
    __ISB();
    
    // Set reset handler address
    App_reset_handler = (void (*)(void))reset;
    
    // Jump to application
    App_reset_handler();
}

void Bootloader_run() {
    //Init phase 
    Bootloader_Init();
    
    //Check the bootloader update
    if (Bootloader_CheckForUpdate()) {
        Bootloader_ReceiveFirmware(); // Reciever a new firmware UART
    }
    
    Bootloader_JumpToApp(); //Jump to user application in flash
}

