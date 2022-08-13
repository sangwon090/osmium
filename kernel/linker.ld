ENTRY(start32)

SECTIONS
{
	. = 1M;

	.boot BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
	}

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