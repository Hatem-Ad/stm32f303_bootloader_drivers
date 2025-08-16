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

