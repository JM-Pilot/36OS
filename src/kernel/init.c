#include <drivers/video/vga.h>
#include <arch/x86/gdt.h>
#include <arch/x86/ints/idt.h>
#include <arch/x86/ints/irq.h>
#include <drivers/input/ps2.h>
#include <libc/stdio.h>
void kernel_boot_init(){
	asm volatile ("cli");
	vga_init();
	printf("VGA DRIVER INITIALIZED\n");
	gdt_init();
	printf("GDT INITIALIZED\n");
	idt_init();
	printf("IDT INITIALIZED\n");
	irq_init();
	printf("SETTING UP IRQ\n");
	printf("INTERRUPTS FINISHED\n");
	ps2_init();
	printf("PS2 DRIVER INITIALIZED\n");
	asm volatile ("sti");
	printf("INTERRUPTS ENABLED\n\n\n");
	printf("Welcome to 32OS!\n\n\n");
}