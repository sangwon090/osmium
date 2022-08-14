#include <utility.h>

void memset(void *dest, uint8_t data, uint32_t size)
{
    uint64_t data_to_fill = 0;

    for(int i=0; i<8; i++)
    {
        data_to_fill = (data_to_fill << 8) | data;
    }

    for(int i=0; i < (size / 8); i++)
    {
        ((uint64_t*) dest)[i] = data_to_fill;
    }

    uint32_t offset = size - (size % 8);

    for(int i=0; i<(size % 8); i++)
    {
        ((uint8_t*)dest)[offset] = data;
        offset ++;
    }
}