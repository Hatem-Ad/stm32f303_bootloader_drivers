#include <Core_CortexM4.h>  // For Main Stack Pointer 
#include "Bootloader.h"
#include "GPIO.h"  // Use GPIO pin to trigger bootloader
#include "UART.h"  // Receive firmware over UART
#include "Flash.h" // For Flash memory

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
    
    uint8_t buffer[FW_CHUNK_SIZE];
    uint32_t addr = APP_START_ADDRESS;
    uint32_t received;

    UART_SendString("Starting firmware update ...\r\n");

    //1. Erase the application aera before writing 
    FLASH_Unlock();
    for(uint32_t currentAddress = APP_START_ADDRESS; currentAddress < (APP_START_ADDRESS + 0x2000); currentAddress += 0x800)
    {
        Flash_Erase(currentAddress); //Erase one page (0x800 = 2KB for STM32f3)
    }

    //2. Received data chunks and write to flash
    while (1)
    {
        received = UART_Received(buffer, FW_CHUNK_SIZE); // Blocking read
        if (received == 0) break; //assume 0 bytes means "End of transmission"

        Flash_Write(addr, buffer, received);
        addr += received; // update address

        UART_SendString("Chunk written. \r\n");
    }    
    
    FLASH_Lock(); // Disable Flash programming
    UART_SendString("Firmware update complete. \r\n");
}

void Bootloader_JumpToApp(void) {
    // Function pointer to application's reset handler
    void (*App_reset_handler)(void);
    
    // Disable interrupts if needed
    __disable_irq();
    
    // Set MSP from app's vector table
    __set_MSP(*(volatile uint32_t *)APP_START_ADDRESS);
    
    // Set reset handler address
    App_reset_handler = (void (*)(void)) (*(volatile uint32_t *)(APP_START_ADDRESS + 4));
    
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

