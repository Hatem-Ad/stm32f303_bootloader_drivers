#include "STM32F3xx.h"
#include "GPIO.h"
#include "UART.h"
#include "SysTick.h"

int main(void)
{
    SystemInit();
    UART_Init();
    GPIO_InitPort(GPIOE);
    GPIO_Config(GPIOE, 9, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_HIGH, GPIO_NPULL);

    UART_SendString("Hello from the Application !\r\n");
    while (1)
    {
        GPIO_TogglePin(GPIOE, 9);   // Blink LED
        SysTick_DelayMs(500);
        
    }
    
}