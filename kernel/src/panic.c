#include <panic.h>
#include <console.h>

void kernel_panic(uint32_t vector, uint32_t error)
{
    set_color(0x4F);
    clear_console();

    printf("KERNEL PANIC\r\n\r\n");

    if(vector < 20)
    {
        printf("* reason: %s\r\n*   code: %d", error_messages[vector], error);
    }
    else
    {
        printf("* reason: UNKNOWN\r\n*   code: %d", error);
    }

    while(1);
}