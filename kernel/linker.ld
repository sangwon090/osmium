ENTRY(start32)

SECTIONS
{
	. = 64;

	.boot BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
	}

	. = 1M;

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.ptable)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.gdt)
	}

	. = 2M;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}
 
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
 
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
 
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.bss)
		*(COMMON)
	}
}