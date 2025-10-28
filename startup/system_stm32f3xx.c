#include <stdint.h>
#include "STM32F3xx.h"

uint32_t SystemCoreClock = 8000000U;        //default HSI frequency before PLL setup

void SystemInit(void)
{
    /* Enable HSI (8 MHz internal oscillator) */
    RCC->CR |= C_RCC_CR_HSION;
    while (!(RCC->CR & C_RCC_CR_HSIRDY));   // Wait until HSI ready

    /* Configure Flash latency for 72 MHz */
    FLASH->ACR |= C_FLASH_ACR_PRFTBE;       // Enable prefetch buffer
    FLASH->ACR &= ~C_FLASH_ACR_LATENCY;     // Clear latency bits
    FLASH->ACR |= C_FLASH_ACR_LATENCY_2;    // Set 2 wait states

    /* Configure the PLL: source = HSI/2 = 4 MHz, multiply by 18 → 72 MHz */
    RCC->CFGR &= ~(C_RCC_CFGR_PLLSRC | C_RCC_CFGR_PLLXTPRE | C_RCC_CFGR_PLLMUL_Msk);
    RCC->CFGR |=  (C_RCC_CFGR_PLLSRC_HSI_Div2 | C_RCC_CFGR_PLLMUL18);

    /* Enable PLL */
    RCC->CR |= C_RCC_CR_PLLON;
    while (!(RCC->CR & C_RCC_CR_PLLRDY));   // Wait until PLL locked

    /* Select PLL as system clock */
    RCC->CFGR &= ~C_RCC_CFGR_SW_Msk;
    RCC->CFGR |=  C_RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & C_RCC_CFGR_SWS_Msk) != C_RCC_CFGR_SWS_PLL);

    /* Update System Core Clock variable */
    SystemCoreClock = 72000000; // 72 MHz default
}

