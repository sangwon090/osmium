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