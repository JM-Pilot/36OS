#include <kernel/kernel.h>
void kernel_cpu_hang(){
	asm volatile("cli");
	for (;;) asm volatile ("hlt");
}