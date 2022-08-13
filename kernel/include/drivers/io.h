#ifndef IO_H
#define IO_H

#include <types.h>

inline void outb(uint16_t port, uint8_t value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

inline uint8_t inb(uint16_t port)
{
    uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));

    return result;
}

#endif