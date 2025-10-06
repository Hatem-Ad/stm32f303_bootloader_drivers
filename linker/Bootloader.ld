/* Bootloader Linker Script for STM32F303 */

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 16K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 40K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH
}

