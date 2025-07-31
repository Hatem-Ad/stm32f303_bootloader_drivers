#include <stdint.h>
#include "GPIO.h"
#include "STM32F3xx.h"

void GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode) {
    
    //Enable Clock for selcted port
    if (port == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    else if (port == GPIOE) RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
    else if (port == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

    //Clear mode bits 
    port->MODER &= ~(3U << (pin * 2));
}


//This function reads the input data register (IDR) of GPIO Port A and checks the state
//of the requested pin. It returns the logical state (1 or 0) of the pin.
uint8_t GPIO_ReadPin(uint8_t pin_number){
    return (GPIOA->IDR & (1 << pin_number)) ? 1 : 0;
}

void GPIO_WritePin(uint8_t pin_number, uint8_t state)
{
    if(state){
        GPIOA->ODR |= (1U << pin_number); //Set pin hihg
    } else {
        GPIOA->ODR &= ~(1U << pin_number); // set pin low
    }
}

//This function toggles the state of a given output pin on GPIOA.
void GPIO_TogglePin(uint8_t pin_number){
    GPIOA->ODR ^= (1U << pin_number);
}