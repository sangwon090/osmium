#ifndef IDT_H
#define IDT_H

#include <types.h>

#define IDT_BASE    0x1440A0

#define IDT_TYPE_INTERRUPT  0x0E
#define IDT_TYPE_TRAP       0x0F
#define IDT_FLAGS_DPL0      0x00
#define IDT_FLAGS_DPL1      0x20
#define IDT_FLAGS_DPL2      0x40
#define IDT_FLAGS_DPL3      0x60
#define IDT_FLAGS_P         0x80
#define IDT_FLAGS_IST0      0
#define IDT_FLAGS_IST1      1

#define IDT_FLAGS_KERNEL    (IDT_FLAGS_DPL0 | IDT_FLAGS_P)
#define IDT_FLAGS_USER      (IDT_FLAGS_DPL3 | IDT_FLAGS_P)

typedef struct __attribute__((__packed__)) idtr
{
    uint16_t limit;
    uint64_t base_addr;
    uint16_t padding1;
    uint32_t padding2;
} idtr_t;

typedef struct __attribute__((__packed__)) idt_entry
{
    uint16_t offset1;
    uint16_t segment_selector;
    uint8_t ist;
    uint8_t type_and_flags;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t reserved;
} idt_entry_t;

void idt_init();
void idt_load(uint64_t address);
void idt_set_entry(idt_entry_t *entry, void *handler, uint16_t selector, uint8_t ist, uint8_t flags, uint8_t type);

#endif