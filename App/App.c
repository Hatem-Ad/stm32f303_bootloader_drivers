#include "STM32F3xx.h"
#include "GPIO.h"
#include "UART.h"

int main(void)
{
    GPIO_Init();
    UART_Init();

    UART_SendString("Hello from the Application !\r\n");
    while (1)
    {
        GPIO_TogglePin(GPIOE, 9);   // Blink LED
        for (volatile uint32_t i = 0; i < 500000; i++);
        
    }
    
}