 /*-----------------------------------------------------------*/
 /*  Startup file for STM32F303 (Cortex-M4)*/
 /*----------------------------------------------------------*/

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
  .word BusFault_Handler        /* 5 : Bus Fault */
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
  .word PVD_IRQHandler          /* PVD throught EXITI line detect */
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUP_IRQHandler
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
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

.weak WWDG_IRQHandler
.weak PVD_IRQHandler
.weak TAMP_STAMP_IRQHandler
.weak RTC_WKUP_IRQHandler
.weak FLASH_IRQHandler
.weak RCC_IRQHandler
.weak EXTI0_IRQHandler
.weak EXTI1_IRQHandler
.weak EXTI2_TSC_IRQHandler
.weak EXTI3_IRQHandler
.weak EXTI4_IRQHandler

/* All point to Default_Handler if not defined elsewhere */
NMI_Handler:           b Default_Handler
HardFault_Handler:     b Default_Handler
MemManage_Handler:     b Default_Handler
BusFault_Handler:      b Default_Handler
UsageFault_Handler:    b Default_Handler
SVC_Handler:           b Default_Handler
DebugMon_Handler:      b Default_Handler
PendSV_Handler:        b Default_Handler
SysTick_Handler:       b Default_Handler

WWDG_IRQHandler:       b Default_Handler
PVD_IRQHandler:        b Default_Handler
TAMP_STAMP_IRQHandler: b Default_Handler
RTC_WKUP_IRQHandler:   b Default_Handler
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

// extern symbils must appear BEFORE lable
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern SystemInit
.extern main

.thumb_func
Reset_Handler:
  /* Copy .data from FLASH to RAM */
  ldr r0, =_sidata
  ldr r1, =_sdata // start
  ldr r2, =_edata // enc
1:
  cmp r1, r2
  ittt lt
  ldrlt r3, [r0], #4 // load
  strlt r3, [r1], #4 // load
  blt 1b

  // Zero .bss
  ldr r0, =_sbss   // r0 = start of .bss
  ldr r1, =_ebss   // r1 = end of .bss
  movs r2, #0      // r2 = 0 constant

  2:
  cmp r0, r1
  it lt
  strlt r2, [r0], #4  // store 0 and increment pointer
  blt 2b


/* Blink très tôt sur PE9 pour prouver que Reset_Handler s’exécute */
  //ldr r3, =0x40021014      /* RCC->AHBENR */
  //ldr r2, =0x00200000      /* bit21: GPIOEEN */
  //ldr r1, [r3]
  //orr r1, r1, r2
  //str r1, [r3]

  //ldr r3, =0x48001000      /* GPIOE base */
  //ldr r1, [r3, #0x00]      /* MODER */
  //ldr r2, =(1<<(10*2))      /* PE9 en sortie */
  //ldr r0, =(3<<(10*2))
  //bic r1, r1, r0
  //orr r1, r1, r2
  //str r1, [r3, #0x00]

  //ldr r2, =(1<<10)          /* BSRR set */
  //str r2, [r3, #0x18]
  //movs r0, #0
//1:
  //adds r0, r0, #1
  //cmp  r0, #0
  //bne 1b
  //ldr r2, =(1<<(10+16))     /* BSRR reset */
  //str r2, [r3, #0x18]


  /* Call SystemInit and main() */
bl SystemInit
bl main

/* If main returns → infinite loop */
b .

.size Reset_Handler, .-Reset_Handler
