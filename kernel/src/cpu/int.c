#include <cpu/isr.h>
#include <cpu/pic.h>
#include <console.h>

static uint32_t common_int_count = 0;

void handle_exception(uint32_t vector, uint64_t error)
{
    kernel_panic(vector, error);
}

void handle_interrupt(uint32_t vector)
{
    printf("* INT %x\r\n", vector);
    pic_eoi(vector - PIC_IRQ_START);
}

void handle_keyboard(uint32_t vector)
{
    printf("* KBD\r\n");
    pic_eoi(vector - PIC_IRQ_START);
}