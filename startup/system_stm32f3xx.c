#include <stdint.h>
#include "STM32F3xx.h"

void SystemInit(void) {

    // Use HSI (8MHz) as system clock
    RCC->CR |= C_RCC_CR_HSION;
    while(!(RCC->CR & C_RCC_CR_HSIRDY));
    RCC->CFGR = 0x0;
    // Called before main, configure clock here later
}
