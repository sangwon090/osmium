#ifndef INT_H
#define INT_H

#include <types.h>

void int_enable();
void int_disable();
uint64_t read_rflags();

void handle_exception(uint32_t vector, uint64_t error);
void handle_interrupt(uint32_t vector);
void handle_keyboard(uint32_t vector);

#endif