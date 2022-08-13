#include <types.h>
#include <console.h>

void kernel_main()
{
    printf("OSMIUM x86-64 (%s %s)", __DATE__, __TIME__);

    while(1);
}