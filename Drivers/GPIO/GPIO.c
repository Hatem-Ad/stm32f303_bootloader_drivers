#include "GPIO.h"
#include <stdint.h>

void GPIO_Init(void) {
    
    //Enable the GPIO clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    //Configure PA0 as input(for a button)
    GPIO->MODER &= ~(3U << (0 * 2)); // 00: Input

    //Configure an output LED : PA5
    GPIOA->MODER |= (1U << (5 * 2)); //01: Output
    GPIOA->MODER &= ~(1U << (5 * 2 + 1));
}

uint8_t GPIO_ReadPin(uint8_t pin_number){
    return (GPIOA->IDR & (1 << pin_number)) ? 1 : 0;
}
