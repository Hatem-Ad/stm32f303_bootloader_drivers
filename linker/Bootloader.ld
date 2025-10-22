/* ============================================================
 * Bootloader Linker Script for STM32F303
 * Flash:  0x08000000 → 0x08003FFF  (16 KB)
 * SRAM:   0x20000000 → 0x2000FFFF  (64 KB)
 * ============================================================ */

ENTRY(Reset_Handler)

/* ------------ Memory Map ------------ */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 16K     /* Bootloader */
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K     /* Full SRAM */
}

/* ------------ Stack Pointer ------------ */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* ------------ Sections ------------ */
SECTIONS
{
    /* Interrupt Vector Table */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* Code + Read-only data */
    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* Initialized data: stored in Flash, copied to RAM at startup */
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    /* Uninitialized (zeroed) data */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    /* Flash load address for .data copy */
    _sidata = LOADADDR(.data);
}
