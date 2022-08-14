#ifndef ISR_H
#define ISR_H

#include <types.h>

// exception
void isr_divide_by_zero();
void isr_debug();
void isr_nmi();
void isr_breakpoint();
void isr_overflow();
void isr_bound_range_exceeded();
void isr_invalid_opcode();
void isr_device_not_available();
void isr_double_fault();
void isr_coprocessor_segment_overflow();
void isr_invalid_tss();
void isr_segment_not_present();
void isr_stack_segment_fault();
void isr_general_protection_fault();
void isr_page_fault();
void isr_reserved_15();
void isr_fp_exception();
void isr_alignment_check();
void isr_machine_check();
void isr_simd_fp_error();
void isr_unknown_exception();

// interrupt
void isr_timer();
void isr_keyboard();
void isr_pic();
void isr_com2();
void isr_com1();
void isr_lpt2();
void isr_floppy();
void isr_lpt1();
void isr_rtc();
void isr_reserved_41();
void isr_reserved_42();
void isr_reserved_43();
void isr_mouse();
void isr_coprocessor();
void isr_ata_1();
void isr_ata_2();
void isr_unknown_interrupt();

#endif