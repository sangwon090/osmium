#ifndef GDT_H
#define GDT_H

#include <types.h>

#define GDT_BASE    0x144000

#define GDT_TYPE_CODE           0x0A
#define GDT_TYPE_DATA           0x02
#define GDT_TYPE_TSS            0x09
#define GDT_FLAGS_LOWER_S       0x10
#define GDT_FLAGS_LOWER_DPL0    0x00
#define GDT_FLAGS_LOEWR_DPL1    0x20
#define GDT_FLAGS_LOWER_DPL2    0x40
#define GDT_FLAGS_LOEWR_DPL3    0x60
#define GDT_FLAGS_LOWER_P       0x80
#define GDT_FLAGS_UPPER_L       0x20
#define GDT_FLAGS_UPPER_DB      0x40
#define GDT_FLAGS_UPPER_G       0x80

#define GDT_FLAGS_LOWER_KERNEL_CODE (GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_KERNEL_DATA (GDT_TYPE_DATA | GDT_FLAGS_LOWER_S | GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_USER_CODE   (GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | GDT_FLAGS_LOWER_DPL3 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_USER_DATA   (GDT_TYPE_CODE | GDT_FLAGS_LOWER_S | GDT_FLAGS_LOWER_DPL3 | GDT_FLAGS_LOWER_P)
#define GDT_FLAGS_LOWER_TSS         (GDT_FLAGS_LOWER_DPL0 | GDT_FLAGS_LOWER_P)

#define GDT_FLAGS_UPPER_CODE        (GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L)
#define GDT_FLAGS_UPPER_DATA        (GDT_FLAGS_UPPER_G | GDT_FLAGS_UPPER_L)
#define GDT_FLAGS_UPPER_TSS         (GDT_FLAGS_UPPER_G)


typedef struct __attribute__((__packed__)) gdtr
{
    uint16_t limit;
    uint64_t base_addr;
    uint16_t padding1;
    uint32_t padding2;
} gdtr_t;

typedef struct __attribute__((__packed__)) gdt_entry_64
{
    uint16_t limit1;
    uint16_t base1;
    uint8_t base2;
    uint8_t access_byte;
    uint8_t limit2_and_flags;
    uint8_t base3;
} gdt_entry_64_t;

typedef struct __attribute__((__packed__)) gdt_entry_128
{
    uint16_t limit1;
    uint16_t base1;
    uint8_t base2;
    uint8_t access_byte;
    uint8_t limit2_and_flags;
    uint8_t base3;
    uint32_t base4;
    uint32_t reserved;
} gdt_entry_128_t;

void gdt_init();
void gdt_load(uint64_t address);
void gdt_set_entry_64(gdt_entry_64_t *entry, uint32_t base_addr, uint32_t limit, uint8_t upper_flags, uint8_t lower_flags, uint8_t type);
void gdt_set_entry_128(gdt_entry_128_t *entry, uint64_t base_addr, uint32_t limit, uint8_t upper_flags, uint8_t lower_flags, uint8_t type);

#endif