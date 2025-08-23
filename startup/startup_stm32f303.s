/*-----------------------------------------------------------
 *  Startup file for STM32F303 (Cortex-M4)
 *----------------------------------------------------------*/

/*Tells Assembly to accept modern ARM syntax */
.syntax unified
/*Selects the architecture */
.cpu cortex-m4
/*Ensures 16-bit thumb instructions are used (required for cortex-M)*/
.thumb 

/*-----------------------------------------------------------
 *  Section : Vector Table
 *----------------------------------------------------------*/

.section .isr_vector,"a",%progbits
.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:
  .word _estack                 /* 0 : Top of Stack */
  .word Reset_Handler           /* 1 : Reset Handler */
  .word NMI_Handler             /* 2 : NMI */
  .word HardFault_Handler       /* 3 : Hard Fault */
  .word MemManage_Handler       /* 4 : MPU Fault */
  .word BusFault_Hanfler        /* 5 : Bus Fault */
  .word UsageFault_Handler      /* 6 : Usage Fault */
  .word 0                       /* 7 : Reserved */
  .word 0                       /* 8 : Reserved */
  .word 0                       /* 9 : Reserved */
  .word 0                       /* 10: Reserved */
  .word SVC_Handler             /* 11: SVCall */
  .word DebugMon_Handler        /* 12: Debug Monitor */
  .word 0                       /* 13: Reserved */
  .word PendSV_Handler          /* 14: PendSV */
  .word SysTick_Handler         /* 15: SysTick */

  /* === Specific Interrupts for STM32F303 */
  .word WWDG_IRQHandler         /* Window Watchdog */
  .word PDV_IRQHandler          /* PDV throught EXITI line detect */
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUPHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_TSC_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  /* ... */

  /*-----------------------------------------------------------
 *  Default Handlers (Fake Infinite Loop)
 *----------------------------------------------------------*/

 .section .text.Default_Handler,"ax",%progbits
 Default_Handler:
 Infinite_Loop:
   b Infinite_Loop

/* Definition of weak Handlers (can be redefined in C) */
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Hanfler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

.weak WWDG_IRQHandler
.weak PDV_IRQHandler
.weak TAMP_STAMP_IRQHandler
.weak RTC_WKUPHandler
.weak FLASH_IRQHandler
.weak RCC_IRQHandler
.weak EXTI0_IRQHandler
.weak EXTI1_IRQHandler
.weak EXTI2_IRQHandler
.weak EXTI3_IRQHandler
.weak EXTI4_IRQHandler

/* All point to Default_Handler if not defined elsewhere */
NMI_Handler:           b Default_Handler
HardFault_Handler:     b Default_Handler
MemManage_Handler:     b Default_Handler
BusFault_Hanfler:      b Default_Handler
UsageFault_Handler:    b Default_Handler
SVC_Handler:           b Default_Handler
DebugMon_Handler:      b Default_Handler
PendSV_Handler:        b Default_Handler
SysTick_Handler:       b Default_Handler

WWDG_IRQHandler:       b Default_Handler
PDV_IRQHandler:        b Default_Handler
TAMP_STAMP_IRQHandler: b Default_Handler
RTC_WKUPHandler:       b Default_Handler
FLASH_IRQHandler:      b Default_Handler
RCC_IRQHandler:        b Default_Handler
EXTI0_IRQHandler:      b Default_Handler
EXTI1_IRQHandler:      b Default_Handler
EXTI2_TSC_IRQHandler:  b Default_Handler
EXTI3_IRQHandler:      b Default_Handler
EXTI4_IRQHandler:      b Default_Handler

/*-----------------------------------------------------------
* Reset Handler: Initializes memory and jumps to main()
*----------------------------------------------------------*/
.section .text.Reset_Handler, "ax",%progbits
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
  /* Initialize .data and .bss (simplified) */
  ldr r0, =_sidata
  ldr r1, =_sidata
  ldr r2, =_edata
1:
  cmp r1, r2





