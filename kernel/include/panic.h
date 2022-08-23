#ifndef PANIC_H
#define PANIC_H

#include <types.h>

const uint8_t *error_messages[] = {
    "DIVIDE_BY_ZERO",
    "DEBUG",
    "NON_MASKABLE_INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND_RANGE_EXCEEDED",
    "INVALID_OPCODE",
    "DEVICE_NOT_AVAILABLE",
    "DOUBLE_FAULT",
    "COPROCESSOR_SEGMENT_OVERFLOW",
    "INVALID_TSS",
    "SEGMENT_NOT_PRESENT",
    "STACK_SEGMENT_FAULT",
    "GENERAL_PROTECTION_ERROR",
    "PAGE_FAULT",
    "RESERVED_15",
    "FLOATING_POINT_EXCEPTION",
    "ALIGNMENT_CHECK",
    "MACHINE_CHECK",
    "SIMD_FLOATING_POINT_ERROR"
};

void kernel_panic(uint32_t vector, uint32_t error);

#endif