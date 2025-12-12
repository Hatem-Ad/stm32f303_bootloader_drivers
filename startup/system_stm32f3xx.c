#include <stdint.h>
#include "STM32F3xx.h"

uint32_t SystemCoreClock = 8000000U;        //default HSI frequency before PLL setup
//volatile uint32_t sysdbg = 0;
__attribute__((section(".debugvars"))) volatile uint32_t sysdbg;

void SystemInit(void)
{

sysdbg = 0xAAAA5555;  // DEBUG FLAG

/* 1. Enable HSI (always present) */
RCC->CR |= C_RCC_CR_HSION;
while (!(RCC->CR & C_RCC_CR_HSIRDY));

/* 2. Flash latency for 64 MHz */
FLASH->ACR = C_FLASH_ACR_PRFTBE | C_FLASH_ACR_LATENCY_2;

/* 3. PLL config: HSI/2 = 4 MHz → 4 * 16 = 64 MHz */
RCC->CFGR2 = 0x00000000;        // PREDIV = 1
RCC->CFGR &= ~(C_RCC_CFGR_PLLSRC | C_RCC_CFGR_PLLMUL_Msk);
/* PLL source = HSI/2 (PLLSRC = 0) */
RCC->CFGR |= C_RCC_CFGR_PLLMUL16;

/* 4. Enable PLL */
RCC->CR |= C_RCC_CR_PLLON;
while (!(RCC->CR & C_RCC_CR_PLLRDY));

/* 5. SYSCLK = PLL */
RCC->CFGR &= ~C_RCC_CFGR_SW_Msk;
RCC->CFGR |=  C_RCC_CFGR_SW_PLL;
while ((RCC->CFGR & C_RCC_CFGR_SWS_Msk) != C_RCC_CFGR_SWS_PLL);

#ifdef BOOTLOADER
    SCB->VTOR = 0x08000000;
#endif

/* 6. Update clock */
SystemCoreClock = 64000000;

}




