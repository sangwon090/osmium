#ifndef CONSOLE_H
#define CONSOLE_H

#include <types.h>

#define CONSOLE_WIDTH   80
#define CONSOLE_HEIGHT  25

void printf(int8_t *str, ...);
void putchar(uint8_t c);
void putstr(uint8_t *str);
void set_color(uint8_t color);
uint8_t get_color();

#endif