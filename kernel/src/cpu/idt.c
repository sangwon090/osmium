#include <cpu/idt.h>
#include <cpu/isr.h>
#include <console.h>

void idt_dummy_handler()
{
    printf(" * dummy IDT handler invoked.\r\n");
    while(1);
}

void idt_init()
{
    idtr_t *idtr = (idtr_t*) IDT_BASE; // 0x1440A0
    idt_entry_t *entry = (idt_entry_t*) (IDT_BASE + sizeof(idtr_t)); // 0x1440B0

    idtr->base_addr = (uint64_t) entry;
    idtr->limit = sizeof(idt_entry_t) * 100 - 1;

    idt_set_entry(&entry[0], isr_divide_by_zero, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[1], isr_debug, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[2], isr_nmi, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[3], isr_breakpoint, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[4], isr_overflow, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[5], isr_bound_range_exceeded, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[6], isr_invalid_opcode, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[7], isr_device_not_available, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[8], isr_double_fault, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[9], isr_coprocessor_segment_overflow, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[10], isr_invalid_tss, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[11], isr_segment_not_present, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[12], isr_stack_segment_fault, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[13], isr_general_protection_fault, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[14], isr_page_fault, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[15], isr_reserved_15, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[16], isr_fp_exception, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[17], isr_alignment_check, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[18], isr_machine_check, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[19], isr_simd_fp_error, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);

    for(int i=20; i<32; i++)
    {
        idt_set_entry(&entry[i], isr_unknown_exception, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }

    idt_set_entry(&entry[32], isr_timer, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[33], isr_keyboard, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[34], isr_pic, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[35], isr_com2, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[36], isr_com1, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[37], isr_lpt2, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[38], isr_floppy, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[39], isr_lpt1, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[40], isr_rtc, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[41], isr_reserved_41, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[42], isr_reserved_42, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[43], isr_reserved_43, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[44], isr_mouse, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[45], isr_coprocessor, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[46], isr_ata_1, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    idt_set_entry(&entry[47], isr_ata_2, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);

    for(int i=48; i<100; i++)
    {
        idt_set_entry(&entry[i], isr_unknown_interrupt, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
}

void idt_set_entry(idt_entry_t *entry, void *handler, uint16_t selector, uint8_t ist, uint8_t flags, uint8_t type)
{
    entry->offset1 = (uint16_t) handler & 0xFFFF;
    entry->segment_selector = selector;
    entry->ist = ist & 0x3;
    entry->type_and_flags = type | flags;
    entry->offset2 = ((uint64_t) handler >> 16) & 0xFFFF;
    entry->offset3 = (uint64_t) handler >> 32;
    entry->reserved = 0;
}