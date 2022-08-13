  C_FILES = $(wildcard src/*.c) $(wildcard src/*/*.c)
ASM_FILES = $(wildcard src/*.asm) $(wildcard src/*/*.asm)
OBJ_FILES = $(C_FILES:%.c=%.c.o) $(ASM_FILES:%.asm=%.asm.o)

TOOLCHAIN = /home/sangwon/.cross_compiler/bin
GCC_FLAGS = -O2 -Wall -Wextra -ffreestanding -nostdinc -nostdlib -nostartfiles -Iinclude -g
ASM_FLAGS = -f elf64
 LD_FLAGS = 

.PHONY: clean

%.c.o: %.c
	$(TOOLCHAIN)/gcc $(GCC_FLAGS) -c $< -o $@

%.asm.o: %.asm
	nasm $(ASM_FLAGS) -o $@ $<

kernel.elf:	linker.ld $(OBJ_FILES)
	$(TOOLCHAIN)/ld $(LD_FLAGS) -T $< -o $@ $(OBJ_FILES)

clean:
	rm -f kernel.elf *.o */*.o