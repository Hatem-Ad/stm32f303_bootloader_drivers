#include "STM32F3xx.h"      // defines TS_GPIO_TypeDef, SystemCoreClock, etc.
#include "SysTick.h"
#include "GPIO.h"
#include "UART.h"
#include "Core_CortexM4.h"


int main(void)
{
    __enable_irq();     // test: 
    // Initialize SysTick (1 ms tick)
    //SysTick_Init(1000);

    RCC->AHBENR |= (1U << 21); // enable horloge of gpioE pin 21
    GPIOE->MODER = (GPIOE->MODER & ~(3U << (9*2))) | (1U << (9*2)); // pin 9 as output

    // Initialize UART for debugging
    /*UART_Init();
    UART_SendString("Hello from the Application !\r\n");

    // Initialize LED pin (PE9)
    GPIO_InitPort(GPIOE);
    GPIO_Config(GPIOE, 9, E_GPIO_MODE_OUTPUT, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);
    GPIO_Config(GPIOE, 8, E_GPIO_MODE_OUTPUT, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);


    while (1)
    {
        UART_SendString("App running OK\r\n");
        GPIO_Toggle(GPIOE, 9);   // Blink LED
        //SysTick_DelayMs(500);
        //GPIO_InitPort(GPIOE);
        //GPIO_Toggle(GPIOE, 8);
        for (volatile int i = 0; i < 1000000; i++);
    }*/

    for (;;){
        GPIOE->BSRR = (1U << 9);         // PE9 = 1
        for (volatile uint32_t i=0; i<800000; i++);
        GPIOE->BSRR = (1U << (9+16));    // PE9 = 0
        for (volatile uint32_t i=0; i<800000; i++);
    }
    return 0;
}
