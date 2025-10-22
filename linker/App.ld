/* Application linker script for STM32F303 */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)   : ORIGIN = 0x08004000, LENGTH = 240K /* Starts after 16 KB bootloader */
  RAM   (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K 
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .isr_vector:
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text : {
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data :
  {
    *(.data*)
  } > RAM

  .bss : {
    *(.bss*)
    *(COMMON)
  } > RAM
}
