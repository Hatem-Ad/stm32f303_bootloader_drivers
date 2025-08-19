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