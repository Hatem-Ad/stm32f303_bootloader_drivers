/* Application linker script for STM32F303 */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)   : ORIGIN = 0x08004000, LENGTH = 240K
  RAM   (rwx)  : ORIGIN = 0x20000000, LENGTH = 40K
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
    _etext = .;
  } > FLASH

  .data : AT (ADDR(.text) + SIZEOF(.text))
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  .bss : {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM
}
