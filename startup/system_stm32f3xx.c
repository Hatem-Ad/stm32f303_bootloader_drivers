#include <stdint.h>
#include "STM32F3xx.h"

uint32_t SystemCoreClock = 8000000U;        //default HSI frequency before PLL setup

void SystemInit(void)
{
    /* 1. Enable HSE (8 MHz internal oscillator) */
    RCC->CR |= C_RCC_CR_HSEON;
    while ((RCC->CR & C_RCC_CR_HSERDY) == 0);   // Wait until HSI ready

    /* 2. Flash latency : 72 MHz → 2 WS + prefetch */
    FLASH->ACR = C_FLASH_ACR_PRFTBE | C_FLASH_ACR_LATENCY_2;

    /* 3. PLL configuration: HSE / PREDIV(=1) * 9 = 72 MHz */
    RCC->CFGR2 = 0x00000000;    // IMPORTANT: PREDIV = 1 (needed for PLL)
    RCC->CFGR &= ~(C_RCC_CFGR_PLLSRC | C_RCC_CFGR_PLLMUL_Msk);
    RCC->CFGR |= C_RCC_CFGR_PLLSRC_HSE_PREDIV;
    RCC->CFGR |=  C_RCC_CFGR_PLLMUL9; // 8 MHz * 9 = 72 MHz

     /* 4. Enable PLL */
    RCC->CR |= C_RCC_CR_PLLON;
    while ((RCC->CR & C_RCC_CR_PLLRDY) == 0); // Wait until PLL locked

    /* 5. Select PLL as system clock */
    RCC->CFGR &= ~C_RCC_CFGR_SW_Msk;
    RCC->CFGR |=  C_RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & C_RCC_CFGR_SWS_Msk) != C_RCC_CFGR_SWS_PLL);

    /* 7. Set Vector Table offset */
    #ifdef BOOTLOADER
    SCB->VTOR = 0x08000000;  // bootloader vector table
    #endif

    /* Update System Core Clock variable */
    SystemCoreClock = 72000000; // 72 MHz default
}

