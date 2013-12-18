/*
 * GCC linker script for STM32 microcontrollers (ARM Cortex-M).
 *
 * Exports the symbols needed for the CMSIS assembler startup script for GCC ARM toolchains (_sidata, _sdata, _edata, _sbss, _ebss) and sets
 * the entry point to handler_reset by default.
 *
 * FLASH/RAM size below must be adapted for the specific target.
 *
 * Based heavily on a sample linker script by Bjørn Forsman.
 */

/* Specify the location of the FLASH and RAM memories of the target within the address space. */
MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

/* Specify the entry point into the code (should normally be the reset handler, or whatever else provides startup functionality). */
ENTRY(handler_reset)

/* Reserve memory for the heap and stack. We reserve zero space; the linker will issue an error if there is not enough memory. */
_heap_size = 0;
_stack_size = 0;

/* NOTE - The reserved heap and stack will be added to the bss column of the binutils size command. */

/* Calculate the location of the end of the stack.  The stack starts at the end of RAM and grows downwards (full-descending); decrement first, then store. */
_estack = ORIGIN(ram) + LENGTH(ram);

/* Define memory sections. */
SECTIONS
{
    /* Reset and ISR vectors (placed into FLASH). */
    .isr_vector :
    {
        __isr_vector_start__ = .;
        KEEP(*(.isr_vector)) /* Without 'KEEP' the linker garbage collector discards this section. */
        ASSERT(. != __isr_vector_start__, "The .isr_vector section is empty.");
    } > flash

    /* Text section (program code and read-only data placed into FLASH). */
    .text :
    {
        . = ALIGN(4);
        _stext = .;
	/* Program code. */
        *(.text*)
	/* Read only data. */
        *(.rodata*)

        /* NOTE - .glue_7 and .glue_7t sections are not needed because Cortex-M only supports Thumb instructions, no ARM/Thumb interworking. */

        /* Static constructors and destructors. */
        KEEP(*(.init))
        KEEP(*(.fini))

        . = ALIGN(4);
        _etext = .;
    } > flash

    /* Stack unwinding and exception handling sections (placed into FLASH). */

    /* ARM compilers emit object files with .ARM.extab and .ARM.exidx sections when using C++ exceptions. Also, at least GCC emits those sections
     * when dividing large numbers (64-bit) in C. So we have to handle them. (ARM uses .ARM.extab and .ARM.exidx instead of the .eh_frame section
     * used on x86.) */

    /* Exception unwinding information. */
    .ARM.extab : 
    {
        *(.ARM.extab*)
    } > flash
    /* Index entries for section unwinding. */
    .ARM.exidx : 
    {
        *(.ARM.exidx*)
    } > flash

    /* Newlib and Eglibc (at least) need these for C++ support. */

    /* NOTE - Copied from Sourcery CodeBench Lite: arm-none-eabi-gcc -V) */

    .preinit_array :
    {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } > flash
    .init_array :
    {
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN(__init_array_end = .);
    } > flash
    .fini_array :
    {
        PROVIDE_HIDDEN(__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN(__fini_array_end = .);
    } > flash

    /* Initialised data section (placed into FLASH, then copied to RAM). */

    /* NOTE - The content of this section is programmed into FLASH (LMA address) and must copied to RAM (VMA address) in startup code. */

    /* LMA address is _sidata (in FLASH) */
    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
	/* Data section VMA address (in RAM). */
        _sdata = .; 
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram

    /* Uninitialized data (BSS) section (zeroed out by startup code) */

    /* NOTE - These values must be zeroed in RAM in startup code. */

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    /* Reserve memory for the heap and stack. The linker will issue an error if there is not enough memory. */
    ._heap :
    {
        . = ALIGN(4);
        . = . + _heap_size;
        . = ALIGN(4);
    } > ram
    ._stack :
    {
        . = ALIGN(4);
        . = . + _stack_size;
        . = ALIGN(4);
    } > ram
}

/* Define variables containing the size of various sections, which may be useful for startup code etc. */
__isr_vector_size__ = SIZEOF(.isr_vector);
__text_size__ = SIZEOF(.text);
__data_size__ = SIZEOF(.data);
__bss_size__ = SIZEOF(.bss);

/* ALL DONE. */

