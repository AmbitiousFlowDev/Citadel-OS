OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

KERNEL_VMA = 0xffffffff80000000;

PHDRS
{
    text PT_LOAD FLAGS((1 << 0) | (1 << 2));
    data PT_LOAD FLAGS((1 << 1) | (1 << 2));
}

SECTIONS
{
    . = KERNEL_VMA;

    _kernel_start = .;

    .text : ALIGN(4K)
    {
        KEEP(*(.limine_requests_start))
        KEEP(*(.limine_requests))
        KEEP(*(.limine_requests_end))

        *(.text .text.*)
    } :text

    .rodata : ALIGN(4K)
    {
        *(.rodata .rodata.*)
    } :text

    .data : ALIGN(4K)
    {
        *(.data .data.*)
    } :data

    .bss (NOLOAD) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss .bss.*)
    } :data

    _kernel_end = .;
}