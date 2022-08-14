#ifndef PIC_H
#define PIC_H

#include <types.h>

#define PIC_MASTER_1    0x20
#define PIC_MASTER_2    0x21
#define PIC_SLAVE_1     0xA0
#define PIC_SLAVE_2     0xA1

#define PIC_IRQ_START   0x20

void pic_init();
void pic_mask(uint16_t bitmask);
void pic_eoi(uint32_t irq);

#endif