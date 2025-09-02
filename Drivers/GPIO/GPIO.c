#include <stdint.h>
#include "GPIO.h"
#include "STM32F3xx.h"


void GPIO_Init(GPIO_TypeDef   *port, 
               uint8_t         pin, 
               GPIO_mode_t     mode,
               GPIO_otype_t    otype,
               GPIO_speed_t    speed,
               GPIO_pull_t     pull) 
{ 
    //Enable Clock for selcted port
    if (port == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    else if (port == GPIOE) RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
    else if (port == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

    //Clear mode bits 
    port->MODER &= ~(3U << (pin * 2));

    if (mode == 1){
        port->MODER |= (1U << (pin * 2)); //output mode
    } else {
        //Input mode: already cleared above
    }
}

//This function reads the input data register (IDR) of X Port  and checks the state
//of the requested pin. It returns the logical state (1 or 0) of the pin.
uint8_t GPIO_Read(GPIO_TypeDef *port, 
                  uint8_t       pin)
{
    return (port->IDR & (1 << pin)) ? 1 : 0;
}

void GPIO_Write(GPIO_TypeDef *port, 
                uint8_t       pin, 
                uint8_t       state)
{
    if(state){
        port->ODR |= (1U << pin); //Set pin hihg
    } else {
        port->ODR &= ~(1U << pin); // set pin low
    }
}

//This function toggles the state of a given output pin on GPIOA.
void GPIO_Toggle(GPIO_TypeDef *port, 
                 int8_t        pin)
{
    port->ODR ^= (1U << pin);
}
