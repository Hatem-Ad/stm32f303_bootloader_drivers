#include "WDG.h"
#include "RCC.h"
#include "STM32F3xx.h"

/*-----------------------------------------------------------
 *                      Private helpers
 *----------------------------------------------------------*/

 static void IWDG_WaitClear(volatile uint32_t *reg, uint32_t mask)
 {
    for (volatile uint32_t i = 0; i < 100000U; ++i)
    {
        if (((*reg) & mask) == 0U)
        {
            break;
        }
    }
 }

 /*-----------------------------------------------------------
 *                       Public functions
 *----------------------------------------------------------*/

void WDG_InitRaw(uint8_t prescaler_code, uint16_t reload)
{
    RCC_EnableLSI();

    // Unlock register
    IWDG->KR = C_IWDG_KR_KEY_WRITE;

    // Set prescaler
    IWDG->PR = (prescaler_code & 0x7U);
    IWDG_WaitClear(&IWDG->SR, C_IWDG_SR_PVU);

    // Set reload value (12 bits max)
    if (reload == 0U)
    {
        reload = 1;
    }

    if (reload > 0x0FFFU)
    {
        reload = 0x0FFFU;
    }

    IWDG->RLR = reload;
    IWDG_WaitClear(&IWDG->SR, C_IWDG_SR_RVU);

    // Reload and start
    IWDG->KR = C_IWDG_KR_KEY_RELOAD;
    IWDG->KR = C_IWDG_KR_KEY_ENABLE;

}

void WDG_Init_ms(uint32_t timeout_ms)
{
    static const uint16_t div_tbl[7] = {4, 8, 16, 32, 64, 128, 256};
    uint8_t best_pr = C_IWDG_PR_DIV256;
    uint16_t best_rlr = 0x0FFF;

    // Find prescaler that fits reload ≤ 4095
    for (int i = 6; i >= 0; --i)
    {
        uint32_t div = div_tbl[i];
        uint32_t ticks = (uint32_t)((((uint64_t)timeout_ms) * C_LSI_HZ) / (1000ULL * div));
        if (ticks == 0U)
        {
            ticks = 1U;
        }

        if (ticks <= 0x0FFFU)
        {
            best_pr = (uint8_t)i;
            best_rlr = (uint16_t)ticks;
            break;
        }
    }
    
    if(best_rlr == 0U)
    {
        best_rlr = 1U;
    }

    // Hardware counts from RLR+1 -> sbstract 1 for accurancy
    WDG_InitRaw(best_pr, (uint16_t)(best_rlr - 1U));
}

void WDG_Refresh(void)
{
    IWDG->KR = C_IWDG_KR_KEY_RELOAD;
}