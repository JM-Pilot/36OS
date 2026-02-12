.code32
.globl gdt_flush
.extern gdtr
gdt_flush:
	lgdt gdtr
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x08, $rcs
rcs:
	ret
