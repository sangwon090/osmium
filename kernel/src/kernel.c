#include <types.h>
#include <console.h>
#include <drivers/keyboard.h>
#include <cpu/gdt.h>
#include <cpu/tss.h>
#include <cpu/idt.h>

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

    while(1);

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

    while(1);
}

void kernel_panic()
{
    set_color(0x4F);
    clear_console();

    printf("KERNEL PANIC\r\n");
}