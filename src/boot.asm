BITS 64

global _start
extern kernel_main

section .text

_start:
    mov rsp, stack_top

    call kernel_main

.hang:
    cli
    hlt
    jmp .hang

section .bss
align 16

stack_bottom:
    resb 16384

stack_top: