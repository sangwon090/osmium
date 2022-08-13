; .multiboot
section .multiboot
align 8

multiboot_start:
    dd 0xE85250D6
    dd 0
    dd multiboot_end - multiboot_start
    dd 0x100000000 - (0xE85250D6 + 0 + (multiboot_end - multiboot_start))

    dw 0
    dw 0
    dd 8
multiboot_end:



; .text
section .text
bits 32

global start32
start32:
    ; set stack
    mov esp, stack_end
    
    ; enable paging
    call init_paging
    call enable_paging

    ; enable gdt
    lgdt [gdt.pointer]

    ; enable long mode
    jmp gdt.code:start64

init_paging:
    mov eax, ptable.pdp
    or eax, 0b11
    mov [ptable.pml4], eax

    mov ecx, 0

    .map_pdp:
        mov eax, 0x1000
        mul ecx
        add eax, ptable.pd
        or eax, 0b11
        mov [ptable.pdp + ecx * 8], eax

        inc ecx
        cmp ecx, 64
        jne .map_pdp

    mov ecx, 0

    .map_pd:
        mov eax, 0x200000
        mul ecx
        or eax, 0b10000011
        mov [ptable.pd + ecx * 8], eax

        mov eax, 2
        mul ecx
        shr eax, 12
        and eax, 0xFF
        mov [ptable.pd + ecx * 8 + 4], eax

        inc ecx
        cmp ecx, 512 * 64
        jne .map_pd
    
    ret

enable_paging:
    ; enable PAE
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; set page table
    mov eax, ptable.pml4
    mov cr3, eax

    ; enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000100
    wrmsr

    ; enable caching and paging
    mov eax, cr0
    or eax, 0xE0000000
    xor eax, 0x60000000
    mov cr0, eax

    ret

bits 64
extern kernel_main

global start64
start64:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kernel_main
    hlt

; .bss
section .bss
align 4096

stack_start:
    resb 4096
stack_end:



; .ptable
section .ptable
ptable:
    .pml4:
        resb 4096
    .pdp:
        resb 4096
    .pd:
        resb 4096 * 64



; .gdt
section .gdt
gdt:
    .null:
        dq 0
    
    .code: equ $ - gdt
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x9A
        db 0xAF
        db 0x00
    
    .data: equ $ - gdt
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0x92
        db 0xAF
        db 0x00

    .pointer:
        dw $ - gdt - 1
        dq gdt