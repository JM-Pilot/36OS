#include <arch/x86/ints/idt.h>
#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>
#include <drivers/video/vga.h>
#include <libc/stdio.h>
#include <kernel/kernel.h>
extern void *isr_stub_table[];
struct idt_entry {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t reserved;
	uint8_t attr;
	uint16_t offset_high;
}__attribute__((packed));

struct idt_reg {
	uint16_t size;
	uint32_t addr;
}__attribute__((packed));



char* interrupt_messages[32] = {
	"Division Exception",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Detected Overflow",
	"Out Of Bounds",
	"Invalid OpCode",
	"No CoProcessor",
	"Double Fault",
	"CoProcessor Segment Overrun",
	"Bad Tss",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"CoProcessor Fault",
	"Alignment Check",
	"Machine Check",
	"Simd Floating Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Hypervisor Injection Exception",
	"Vmm Communication Exception",
	"Security Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
};

struct idt_entry idt[256];
struct idt_reg idtr;

void idt_set_entry(int n, uint64_t offset, uint16_t selector, uint8_t attr){
	idt[n].offset_low = (offset & 0xFFFF);
	idt[n].offset_high = ((offset >> 16)& 0xFFFF);
	idt[n].selector = selector;
	idt[n].attr = attr;
	idt[n].reserved = 0;
}

void isr_print_error(struct registers *reg){
	vga_write_str("\nInterrupt Reached!\n");
	printf("Interrupt: %s\n", interrupt_messages[reg->int_num]);
	printf("EAX: %x, EBP: %x\n", reg->eax, reg->ebp);
	printf("EBX: %x, ECX: %x\n", reg->ebx, reg->ecx);
	printf("EDI: %x, EDX: %x\n", reg->edi, reg->edx);
	printf("ESI: %x, ESP: %x\n", reg->esi, reg->esp);
	printf("EIP: %x\n", reg->eip);
	kernel_cpu_hang();
}

void idt_init(){
	idtr.size = (sizeof(struct idt_entry) * 256) - 1;
	idtr.addr = (uint32_t)&idt;
	memset(idt, 0, sizeof(idt));
	for (int i = 0; i < 32; i++){
		idt_set_entry(i, (unsigned)isr_stub_table[i], 0x08, 0x8E);
	}
	asm volatile ("lidt %0"
			:	
			: "m" (idtr)
			: "memory");
}