
#include <arch/x86/gdt.h>
#include <arch/x86/ints/idt.h>
#include <arch/x86/ints/irq.h>
#include <drivers/input/ps2.h>
#include <libc/stdio.h>
#include <boot/multiboot.h>
#include <drivers/video/fb.h>
#include <drivers/video/psf.h>
#include <drivers/video/console.h>
void kernel_boot_init(struct multiboot_header* mb_info){

	asm volatile ("cli");

	if (mb_info->flags & 0x1000) {
		fb_init(mb_info->framebuffer_addr,
			mb_info->framebuffer_height, 
			mb_info->framebuffer_width);
	}
	psf_init();
	init_console();

	printf("CHECKING MB_INFO\n");
	printf("FLAGS: %x\n", mb_info->flags);
	
	if (mb_info->flags & 0x01){
		printf("MEM LOWER: %x\n", mb_info->mem_lower);
		printf("MEM HIGHER: %x\n", mb_info->mem_upper);
		printf("TOTAL RAM: %u MB\n", (mb_info->mem_upper + 1024) / 1024);
	}
	if (mb_info->flags & 0x40){
		printf("MMAP ADDR: %x\n", mb_info->mmap_addr);
		printf("MMAP LENGTH: %x\n", mb_info->mmap_length);
	}
	if (mb_info->flags & 0x02){
		printf("BOOTED BY: %s\n", mb_info->boot_loader_name);
		printf("BOOT DEV: %x\n", mb_info->boot_device);
	}
	

	gdt_init();
	printf("GDT INITIALIZED\n");

	idt_init();
	printf("IDT INITIALIZED\n");

	irq_init();
	printf("SETTING UP IRQ\n");
	printf("INTERRUPTS FINISHED\n");

	ps2_init();
	printf("PS2 DRIVER INITIALIZED\n\n");
	
	asm volatile ("sti");
	printf("INTERRUPTS ENABLED\n\n\n");
	printf("Welcome to 32OS!\n\n\n");
}