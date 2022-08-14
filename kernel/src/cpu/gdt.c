#include <cpu/gdt.h>
#include <cpu/tss.h>
#include <console.h>

void gdt_init()
{
    gdtr_t *gdtr = (gdtr_t*) GDT_BASE; // 0x144000
    gdt_entry_64_t *entry = (gdt_entry_64_t*) (GDT_BASE + sizeof(gdtr_t)); // 0x144010
    tss_segment_t *tss = (tss_segment_t*)(((uint64_t) entry) + ((sizeof(gdt_entry_64_t) * 3) + sizeof(gdt_entry_128_t))); // 0x144038

    gdtr->limit = (sizeof(gdt_entry_64_t) * 3) + sizeof(gdt_entry_128_t) - 1;
    gdtr->base_addr = (uint64_t) entry;

    gdt_set_entry_64(&entry[0], 0, 0, 0, 0, 0);
    gdt_set_entry_64(&entry[1], 0, 0xFFFF, GDT_FLAGS_UPPER_CODE, GDT_FLAGS_LOWER_KERNEL_CODE, GDT_TYPE_CODE);
    gdt_set_entry_64(&entry[2], 0, 0xFFFF, GDT_FLAGS_UPPER_DATA, GDT_FLAGS_LOWER_KERNEL_DATA, GDT_TYPE_DATA);
    gdt_set_entry_128((gdt_entry_128_t*)&entry[3], (uint64_t) tss, sizeof(tss_segment_t) - 1, GDT_FLAGS_UPPER_TSS, GDT_FLAGS_LOWER_TSS, GDT_TYPE_TSS);

    tss_init(tss);
}

void gdt_set_entry_64(gdt_entry_64_t *entry, uint32_t base_addr, uint32_t limit, uint8_t upper_flags, uint8_t lower_flags, uint8_t type)
{
    entry->limit1 = limit & 0xFFFF;
    entry->base1 = base_addr & 0xFFFF;
    entry->base2 = (base_addr >> 16) & 0xFF;
    entry->access_byte = lower_flags | type;
    entry->limit2_and_flags = ((limit >> 16) & 0xFF) | upper_flags;
    entry->base3 = (base_addr >> 24) & 0xFF;
}

void gdt_set_entry_128(gdt_entry_128_t *entry, uint64_t base_addr, uint32_t limit, uint8_t upper_flags, uint8_t lower_flags, uint8_t type)
{
    entry->limit1 = limit & 0xFFFF;
    entry->base1 = base_addr & 0xFFFF;
    entry->base2 = (base_addr >> 16) & 0xFF;
    entry->access_byte = lower_flags | type;
    entry->limit2_and_flags = ((limit >> 16) & 0xFF) | upper_flags;
    entry->base3 = (base_addr >> 24) & 0xFF;
    entry->base4 = base_addr >> 32;
    entry->reserved = 0;
}