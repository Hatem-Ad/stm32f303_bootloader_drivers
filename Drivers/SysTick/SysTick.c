#include "SysTick.h"
#include "STM32F3xx.h"

//uint32_t SystemCoreClock = 72000000; // 72 MHz default
volatile uint32_t V_TickCount = 0;     // Tick counter

void SysTick_Init(uint32_t ticks_per_second)
{
    // Load value - configure SysTick to interrupt every 1 ms
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1UL;
    // Clear current value - reset counter
    SysTick->VAL = 0UL; 
    // Enable SysTck - CPU clock - inpterrupt = 0x07
    SysTick->CTRL = C_SysTick_CTRL_ENABLE_Msk | C_SysTick_CTRL_TICKINT_Msk | C_SysTick_CTRL_CLKSOURCE_Msk;    
}

void SysTick_Handler(void)
{
    V_TickCount++; //Increment tick counter each millisecond
}

void SysTick_DelayMs(uint32_t delay)
{
    uint32_t start = V_TickCount;
    while ((V_TickCount - start) < delay);
}

void SysTick_Disable()
{
    // Disable SysTck
    SysTick->CTRL = ~C_SysTick_CTRL_ENABLE_Msk;
}