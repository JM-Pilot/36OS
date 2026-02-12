#include <stdint.h>
#ifndef IDT_H
#define IDT_H
struct registers {
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_num;
	uint32_t code;
	uint32_t eip, cs, eflags, useresp, ss;
};
void idt_set_entry(int n, uint64_t offset, uint16_t selector, uint8_t attr);
void idt_init();
#endif