#include <cpu/tss.h>
#include <utility.h>

void tss_init(tss_segment_t *tss)
{
    memset(tss, 0, sizeof(tss_segment_t));
    tss->ist[0] = 0x800000;
    tss->iobp = 0xFFFF;
}