#ifndef TSS_H
#define TSS_H

#include <types.h>

typedef struct __attribute__((__packed__)) tss_segment
{
    uint32_t reserved1;
    uint64_t rsp[3];
    uint64_t reserved2;
    uint64_t ist[7];
    uint64_t reserved3;
    uint16_t reserved4;
    uint16_t iobp;
} tss_segment_t;

void tss_init();
void tss_load(uint16_t offset);
#endif