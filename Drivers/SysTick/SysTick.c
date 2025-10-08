#include "SysTick.h"
#include "STM32F3xx.h"

uint32_t V_SystemCoreClock = 72000000; // 72 MHz default
volatile uint32_t V_g_msTicks = 0;     // Tick counter

void SysTick_Init(uint32_t ticks_per_second)
{
    // Load value  
    SysTick->LOAD = (V_SystemCoreClock / ticks_per_second) - 1UL;

    // Clear current value
    SysTick->VAL = 0UL;

    // Enable SysTck - CPU clock - inpterrupt
    SysTick->CTRL = C_SysTick_CTRL_CLKSOURCE_Msk | C_SysTick_CTRL_TICKINT_Msk | C_SysTick_CTRL_ENABLE_Msk;    
}

void SysTick_Handler(void)
{
    V_g_msTicks++; //Increment tick counter each millisecond
}

uint32_t SysTick_GetTick(void)
{
    return V_g_msTicks;
}

void SysTick_Delay(uint32_t ms)
{
    uint32_t v_start = SysTick_GetTick();
    uint32_t v_current = v_start;
    while ((v_current - v_start) < ms)
    {
        v_current = SysTick_GetTick();
    }
}