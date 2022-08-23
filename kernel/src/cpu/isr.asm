section .text
bits 64

extern handle_exception, handle_interrupt, handle_keyboard, handle_timer

; macros
%macro save_ctx 0
    push rbp
    mov rbp, rsp

    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov ax, ds
    push rax
    mov ax, es
    push rax
    push fs
    push gs
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
%endmacro

%macro load_ctx 0
    pop gs
    pop fs
    pop rax
    mov es, ax
    pop rax
    mov ds, ax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    pop rbp
%endmacro



; exception
extern isr_divide_by_zero
isr_divide_by_zero:
    save_ctx
    mov rdi, 0
    call handle_exception
    load_ctx
    iretq

extern isr_debug
isr_debug:
    save_ctx
    mov rdi, 1
    call handle_exception
    load_ctx
    iretq

extern isr_nmi
isr_nmi:
    save_ctx
    mov rdi, 2
    call handle_exception
    load_ctx
    iretq

extern isr_breakpoint
isr_breakpoint:
    save_ctx
    mov rdi, 3
    call handle_exception
    load_ctx
    iretq

extern isr_overflow
isr_overflow:
    save_ctx
    mov rdi, 4
    call handle_exception
    load_ctx
    iretq

extern isr_bound_range_exceeded
isr_bound_range_exceeded:
    save_ctx
    mov rdi, 5
    call handle_exception
    load_ctx
    iretq

extern isr_invalid_opcode
isr_invalid_opcode:
    save_ctx
    mov rdi, 6
    call handle_exception
    load_ctx
    iretq

extern isr_device_not_available
isr_device_not_available:
    save_ctx
    mov rdi, 7
    call handle_exception
    load_ctx
    iretq

extern isr_double_fault
isr_double_fault:
    save_ctx
    mov rdi, 8
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_coprocessor_segment_overflow
isr_coprocessor_segment_overflow:
    save_ctx
    mov rdi, 9
    call handle_exception
    load_ctx
    iretq

extern isr_invalid_tss
isr_invalid_tss:
    save_ctx
    mov rdi, 10
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_segment_not_present
isr_segment_not_present:
    save_ctx
    mov rdi, 11
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_stack_segment_fault
isr_stack_segment_fault:
    save_ctx
    mov rdi, 12
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_general_protection_fault
isr_general_protection_fault:
    save_ctx
    mov rdi, 13
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_page_fault
isr_page_fault:
    save_ctx
    mov rdi, 14
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_reserved_15
isr_reserved_15:
    save_ctx
    mov rdi, 15
    call handle_exception
    load_ctx
    iretq

extern isr_fp_exception
isr_fp_exception:
    save_ctx
    mov rdi, 16
    call handle_exception
    load_ctx
    iretq

extern isr_alignment_check
isr_alignment_check:
    save_ctx
    mov rdi, 17
    mov rsi, qword [rbp + 8]
    call handle_exception
    load_ctx
    iretq

extern isr_machine_check
isr_machine_check:
    save_ctx
    mov rdi, 18
    call handle_exception
    load_ctx
    iretq

extern isr_simd_fp_error
isr_simd_fp_error:
    save_ctx
    mov rdi, 19
    call handle_exception
    load_ctx
    iretq

extern isr_unknown_exception
isr_unknown_exception:
    save_ctx
    mov rdi, 20
    call handle_exception
    load_ctx
    iretq



; interrupt

extern isr_timer
isr_timer:
    save_ctx
    mov rdi, 32
    call handle_timer
    load_ctx
    iretq

extern isr_keyboard
isr_keyboard:
    save_ctx
    mov rdi, 33
    call handle_keyboard
    load_ctx
    iretq

extern isr_pic
isr_pic:
    save_ctx
    mov rdi, 34
    call handle_interrupt
    load_ctx
    iretq

extern isr_com2
isr_com2:
    save_ctx
    mov rdi, 35
    call handle_interrupt
    load_ctx
    iretq

extern isr_com1
isr_com1:
    save_ctx
    mov rdi, 36
    call handle_interrupt
    load_ctx
    iretq

extern isr_lpt2
isr_lpt2:
    save_ctx
    mov rdi, 37
    call handle_interrupt
    load_ctx
    iretq

extern isr_floppy
isr_floppy:
    save_ctx
    mov rdi, 38
    call handle_interrupt
    load_ctx
    iretq

extern isr_lpt1
isr_lpt1:
    save_ctx
    mov rdi, 39
    call handle_interrupt
    load_ctx
    iretq

extern isr_rtc
isr_rtc:
    save_ctx
    mov rdi, 40
    call handle_interrupt
    load_ctx
    iretq

extern isr_reserved_41
isr_reserved_41:
    save_ctx
    mov rdi, 41
    call handle_interrupt
    load_ctx
    iretq

extern isr_reserved_42
isr_reserved_42:
    save_ctx
    mov rdi, 42
    call handle_interrupt
    load_ctx
    iretq

extern isr_reserved_43
isr_reserved_43:
    save_ctx
    mov rdi, 43
    call handle_interrupt
    load_ctx
    iretq

extern isr_mouse
isr_mouse:
    save_ctx
    mov rdi, 44
    call handle_interrupt
    load_ctx
    iretq

extern isr_coprocessor
isr_coprocessor:
    save_ctx
    mov rdi, 45
    call handle_interrupt
    load_ctx
    iretq

extern isr_ata_1
isr_ata_1:
    save_ctx
    mov rdi, 46
    call handle_interrupt
    load_ctx
    iretq

extern isr_ata_2
isr_ata_2:
    save_ctx
    mov rdi, 47
    call handle_interrupt
    load_ctx
    iretq

extern isr_unknown_interrupt
isr_unknown_interrupt:
    save_ctx
    mov rdi, 48
    call handle_interrupt
    load_ctx
    iretq