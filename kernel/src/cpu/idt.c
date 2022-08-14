#include <cpu/idt.h>
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

    for(int i=0; i<100; i++)
    {
        idt_set_entry(&entry[i], idt_dummy_handler, 0x08, IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
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