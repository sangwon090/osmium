#include <cpu/isr.h>
#include <cpu/pic.h>
#include <console.h>
#include <drivers/io.h>
#include <drivers/keyboard.h>

void handle_exception(uint32_t vector, uint64_t error)
{
    kernel_panic(vector, error);
}

void handle_interrupt(uint32_t vector)
{
    if(vector != 0x20) printf("* INT %x\r\n", vector);
    pic_eoi(vector - PIC_IRQ_START);
}

void handle_timer(uint32_t vector)
{
    pic_eoi(vector - PIC_IRQ_START);
}

void handle_keyboard(uint32_t vector)
{
    uint8_t code = inb(0x60);
    uint8_t ascii = 0, flags = 0;
    kbd_code_to_ascii(code, &ascii, &flags);

    printf("* KBD (%c)\r\n", ascii);
    pic_eoi(vector - PIC_IRQ_START);
}