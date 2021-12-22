ENTRY(bytes)

SECTIONS
{
	. = 0x401000;
	.text : { *(.text) }
	. = 0x402000;
	.data : { *(.data) }
}
