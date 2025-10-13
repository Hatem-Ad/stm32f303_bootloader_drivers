#include "RCC.h"
#include "STM32F3xx.h"

void RCC_EnableLSI(void)
{
    RCC->CSR |= C_RCC_CSR_LSION;
    while ((RCC->CSR & C_RCC_CSR_LSIRDY) == 0U)
    {
        // wait
    }
    
}