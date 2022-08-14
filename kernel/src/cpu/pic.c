#include <cpu/pic.h>
#include <drivers/io.h>

void pic_init()
{
    // init master
    outb(PIC_MASTER_1, 0x11);
    outb(PIC_MASTER_2, PIC_IRQ_START);
    outb(PIC_MASTER_2, 0x04);
    outb(PIC_MASTER_2, 0x01);

    // init slave
    outb(PIC_SLAVE_1, 0x11);
    outb(PIC_SLAVE_2, PIC_IRQ_START + 8);
    outb(PIC_SLAVE_2, 0x02);
    outb(PIC_SLAVE_2, 0x01);
}

void pic_mask(uint16_t bitmask)
{
    outb(PIC_MASTER_2, (uint8_t) bitmask);
    outb(PIC_SLAVE_2, (uint8_t)(bitmask >> 8));
}

void pic_eoi(uint32_t irq)
{
    outb(PIC_MASTER_1, 0x20);

    if(irq >= 8)
    {
        outb(PIC_SLAVE_1, 0x20);
    }
}