/* Bootloader Linker Script for STM32F303 */

ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 16K /* Bootloader in first 16 KB */
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 64K /* Full SRAM */
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* top of stack */

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text : 
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
    } > RAM
}