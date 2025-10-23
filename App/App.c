#include <stdio.h>
#include "STM32F3xx.h"      // defines TS_GPIO_TypeDef, SystemCoreClock, etc.
#include "SysTick.h"
#include "GPIO.h"
#include "UART.h"


int main(void)
{
    // Initialize SysTick (1 ms tick)
    SysTick_Init(1000);

    // Initialize UART for debugging
    UART_Init();
    UART_SendString("Hello from the Application !\r\n");

    // Initialize LED pin (PE9)
    GPIO_InitPort(GPIOE);
    GPIO_Config(GPIOE, 9, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO_SPEED_HIGH, GPIO_NPULL);

    while (1)
    {
        GPIO_Toggle(GPIOE, 9);   // Blink LED
        SysTick_DelayMs(500);
    }

    return 0;
}
