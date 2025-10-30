#ifndef CORE_CORTEXM4_H
#define CORE_CORTEXM4_H

#include <stdint.h>

/*----------------------------------------------------------
 *  Cortex-M4 Core Control Functions
 *----------------------------------------------------------*/

/**
 * @brief  Set the CONTROL register.
 * @param  control  New CONTROL value to set.
 * @note   Bit 0 = Stack select (0 = MSP, 1 = PSP)
 *         Bit 1 = Privilege (0 = privileged, 1 = unprivileged)
 */
static inline void __set_CONTROL(uint32_t control)
{
    __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
}

//Set Main Stack Pointer using the assembly function.
static inline void __set_MSP(uint32_t TopOfMainStack)
{ 
    //Move the register value to the MSP.
    __asm volatile ("msr msp, %0" : : "r" (TopOfMainStack):);
}

// to desiable intrrupts when the jump to apps
static inline void __disable_irq(void)
{
    __asm volatile ("cpsid i");
}

/**
 * @brief  Data Synchronization Barrier.
 */
static inline void __DSB(void)
{
    __asm volatile ("dsb 0xF":::"memory");
}

/**
 * @brief  Instruction Synchronization Barrier.
 */
static inline void __ISB(void)
{
    __asm volatile ("isb 0xF":::"memory");
}

#endif