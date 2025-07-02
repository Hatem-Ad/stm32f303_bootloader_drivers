#ifndef CORE_CORTEXM4_H
#define CORE_CORTEXM4_H

#include <stdint.h>
//Set Main Stack Pointer using the assembly function.
static inline void __set_MSP(uint32_t TopOfMainStack)
{   //Move the register value to the MSP.
    __asm volatile ("msr msp, %0" : : "r" (TopOfMainStack):);
}

#endif