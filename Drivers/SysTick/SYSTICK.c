#include "SYSTICK.h"
#include "STM32F3xx.h"

uint32_t V_SystemCoreClock = 72000000; // 72 MHz default
volatile uint32_t V_g_msTicks = 0;     // Tick counter

void SYSTICK_Init(uint32_t ticks_per_second)
{
    // Load value
    SYSTICK->LOAD = (V_SystemCoreClock / ticks_per_second) - 1UL;

    // Clear current value
    SYSTICK->VAL = 0UL;

    // Enable SysTck - CPU clock - inpterrupt
    SYSTICK->CTRL = C_SYSTICK_CTRL_CLKSOURCE_Msk | C_SYSTICK_CTRL_TICKINIT_Msk | C_SYSTICK_CTRL_ENABLE_Msk;    
}

void SYSTICK_Handler(void)
{
    V_g_msTicks++; //Increment tick counter each millisecond
}

uint32_t SYSTICK_GetTick(void)
{
    return V_g_msTicks;
}

void SYSTICK_Delay(uint32_t ms)
{
    uint32_t v_start = SYSTICK_GetTick();
    uint32_t v_current = v_start;
    while ((v_current - v_start) < ms)
    {
        v_current = SYSTICK_GetTick();
    }
}