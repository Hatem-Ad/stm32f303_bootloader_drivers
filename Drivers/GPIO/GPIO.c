#include <stdint.h>
#include "GPIO.h"
#include "STM32F3xx.h"

void GPIO_Init(void) {
    
    //Enable the GPIO clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    //Configure PA0 as input(for a button)
    GPIOA->MODER &= ~(3U << (0 * 2)); // 00: Input

    //Configure an output LED : PA5
    GPIOA->MODER |= (1U << (5 * 2)); //01: Output
    GPIOA->MODER &= ~(1U << (5 * 2 + 1));
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