#include "STM32F3xx.h"      // defines TS_GPIO_TypeDef, SystemCoreClock, etc.
#include "SysTick.h"
#include "GPIO.h"
#include "UART.h"
#include "Core_CortexM4.h"


int main(void)
{
    // Initialize UART for debugging
    UART_Init();
    UART_SendString("Hello from the Application !\r\n");

    // Initialize LED pin (PE9)
    GPIO_InitPort(GPIOE);
    GPIO_Config(GPIOE, C_GPIO_Pin_9, E_GPIO_MODE_OUTPUT, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);
    GPIO_Config(GPIOE, C_GPIO_Pin_8, E_GPIO_MODE_OUTPUT, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);


    while (1)
    {
        UART_SendString("App running OK\r\n");
        GPIO_Toggle(GPIOE, C_GPIO_Pin_9);   // Blink LED
        SysTick_DelayMs(500);
        //GPIO_InitPort(GPIOE);
        GPIO_Toggle(GPIOE, C_GPIO_Pin_8);
        for (volatile int i = 0; i < 1000000; i++);
    }

    return 0;
}
