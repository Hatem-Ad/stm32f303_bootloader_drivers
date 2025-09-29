#ifndef CORE_CORTEXM4_H
#define CORE_CORTEXM4_H

#include <stdint.h>
//Set Main Stack Pointer using the assembly function.
static inline void __set_MSP(uint32_t TopOfMainStack)
{ 
    //Move the register value to the MSP.
    __asm volatile ("msr msp, %0" : : "r" (TopOfMainStack):);
}

// to desiable intrrupts when the jump to apps
static inline void _disable_irq(void)
{
    __asm volatile ("cpsid i");
}
#endif

static inline void __DSB(void)
{
    __asm volatile ("dsb 0xF":::"memory");
}

static inline void __ISB(void)
{
    __asm volatile ("isb 0xF":::"memory");
}