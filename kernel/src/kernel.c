#include <types.h>
#include <console.h>
#include <drivers/keyboard.h>
#include <cpu/cpu.h>

void print_ptable(uint64_t addr)
{

    uint64_t entry = *(volatile uint64_t*)(addr);
    printf("PHYS: %X\r\n", ((entry >> 11) & 0x7FFFFFFFFF));
    printf("FLAG:");

    if(entry & 1) printf(" IS_PRESENT");
    if(entry & 2) printf(" IS_WRITABLE");
    if(entry & 4) printf(" IS_USER_ACCESSIBLE");
    if(entry & 8) printf(" IS_WRITE_THROUGH_CACHING");
    if(entry & 16) printf(" DISABLE_CACHE");
    if(entry & 32) printf(" ACCESSED");
    if(entry & 64) printf(" DIRTY");
    if(entry & 128) printf(" HUGE_PAGE");
    if(entry & 256) printf(" GLOBAL");
    printf("\r\n\r\n");
}

void kernel_main()
{
    set_color(0x0F);
    clear_console();
    printf("OSMIUM x86-64 (%s %s)\r\n\n", __DATE__, __TIME__);
    set_color(0x07);

    printf("* initializing keyboard...");

    if(kbd_init())
    {
        printf(" DONE!\r\n");
    }
    else
    {
        printf(" ERROR!\r\n");
    }

    printf("* initializing GDT and TSS...");
    gdt_init();
    gdt_load(GDT_BASE);
    tss_load(0x18);
    printf(" DONE!\r\n");

    printf("* initializing IDT...");
    idt_init();
    idt_load(IDT_BASE);
    printf(" DONE!\r\n");

    printf("* initializing PIC...");
    pic_init();
    pic_mask(0);
    int_enable();
    printf(" DONE!\r\n");

    /*
    while(1)
    {
        if(kbd_is_output_full())
        {
            uint8_t code, ascii, flags;
            code = kbd_get_key();
            printf("key pressed: %X (%c)\r\n", code, code);

            if(kbd_code_to_ascii(code, &ascii, &flags))
            {
                if(flags & KEY_FLAGS_DOWN)
                {
                    putchar(ascii);
                }
            }
        }
    }
    */

    while(1);
}