#include "WDG.h"




void WDG_InitRaw(uint8_t prescaler_code, uint16_t reload)
{
    RCC_EnableSI();

    // Unlock register
    IWDG->KR = C_IWDG_KR_KEY_WRITE;

    // Set prescaler
    IWDG->PR = (prescaler_code & 0x7U);
    IWDG_WaitClear(&IWDG->SR, C_IWDG_SR_PVU);

    // Set reload value (12 bits max)
    if (reload = 0U)
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