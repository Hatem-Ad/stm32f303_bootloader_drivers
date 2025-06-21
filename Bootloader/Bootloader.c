#include <core_cm4.h>  // For __set_MSP()
#include "Bootloader.h"
#include "GPIO.h"  // Use GPIO pin to trigger bootloader
#include "UART.h"  // Receive firmware over UART

#define APP_START_ADDRESS 0x08004000U  // App start address after bootloader

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
    return 0;      // Jump to app
}

void Bootloader_ReceiveFirmware(void) {
    // Placeholder: Receive and write firmware to flash
    // Implement UART receive, flash erase/write here
    UART_SendString("Receiving firmware...\r\n");
    // TODO: Add code to receive and program flash
}

void Bootloader_JumpToApp(void) {
    // Function pointer to application's reset handler
    void (*app_reset_handler)(void);
    
    // De-initialize peripherals if needed
    // Disable interrupts if necessary
    
    // Set main stack pointer
    __set_MSP(*(volatile uint32_t *)APP_START_ADDRESS);
    
    // Set reset handler address
    app_reset_handler = (void (*)(void)) (*(volatile uint32_t *)(APP_START_ADDRESS + 4));
    
    // Jump to application
    app_reset_handler();
}
