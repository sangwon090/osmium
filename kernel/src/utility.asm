section .text
bits 64

global gdt_load
gdt_load:
    lgdt [rdi]
    ret

global tss_load
tss_load:
    ltr di
    ret

global idt_load
idt_load:
    lidt [rdi]
    ret

global int_enable
int_enable:
    sti
    ret

global int_disable
int_disable:
    cli
    ret

global read_rflags
read_rflags:
    pushfq
    pop rax

    ret