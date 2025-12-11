/*-----------------------------------------------------------
 *  Startup file for STM32F303 (Cortex-M4 Bootloader)
 *----------------------------------------------------------*/

.syntax unified
.cpu cortex-m4
.thumb

/*-----------------------------------------------------------
 *  Vector Table
 *----------------------------------------------------------*/
.section .isr_vector,"a",%progbits
.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:
    .word   _estack
    .word   Reset_Handler
    .word   NMI_Handler
    .word   HardFault_Handler
    .word   MemManage_Handler
    .word   BusFault_Handler
    .word   UsageFault_Handler
    .word   0
    .word   0
    .word   0
    .word   0
    .word   SVC_Handler
    .word   DebugMon_Handler
    .word   0
    .word   PendSV_Handler
    .word   SysTick_Handler

/*-----------------------------------------------------------
 *  Default Handlers
 *----------------------------------------------------------*/
.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b Infinite_Loop

.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

NMI_Handler:           b Default_Handler
HardFault_Handler:     b Default_Handler
MemManage_Handler:     b Default_Handler
BusFault_Handler:      b Default_Handler
UsageFault_Handler:    b Default_Handler
SVC_Handler:           b Default_Handler
DebugMon_Handler:      b Default_Handler
PendSV_Handler:        b Default_Handler
SysTick_Handler:       b Default_Handler

/*-----------------------------------------------------------
 *  External Symbols
 *----------------------------------------------------------*/
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss

.extern SystemInit
.extern main          /* <-- ENTRYPOINT correct */

/*-----------------------------------------------------------
 *  Reset Handler
 *----------------------------------------------------------*/
.section .text.Reset_Handler,"ax",%progbits
.global Reset_Handler
.type Reset_Handler,%function

.thumb_func
Reset_Handler:

    /* Copy .data from FLASH to RAM */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
CopyData:
    cmp r1, r2
    bcc DoCopy
    b   InitBSS
DoCopy:
    ldr r3, [r0], #4
    str r3, [r1], #4
    b   CopyData

/* Zero .bss */
InitBSS:
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
ZeroLoop:
    cmp r0, r1
    bcc DoZero
    b   CallSystemInit
DoZero:
    str r2, [r0], #4
    b   ZeroLoop

/* Call SystemInit() */
CallSystemInit:
    bl  SystemInit

/* Jump to main() */
    bl  main

/* If main() returns, loop forever */
Forever:
    b Forever

.size Reset_Handler, .-Reset_Handler
