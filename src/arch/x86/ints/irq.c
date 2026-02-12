#include <arch/x86/ints/pic.h>
#include <arch/x86/ints/idt.h>
#include <stdint.h>
#include <arch/x86/asm.h>
#include <drivers/video/vga.h>
#include <libc/stdio.h>
#include <drivers/input/ps2.h>
extern void* irq_stub_table[];

static volatile int irq0_timer = 0;
void irq0_timer_handler(struct registers *reg){
	irq0_timer++;
}

void irq1_keyboard_handler(struct registers *reg){
	uint8_t scancode = inb(0x60);
	int f_head = (ps2_sc_head + 1) % 256;

	if (f_head != ps2_sc_tail){
		ps2_scancodes[ps2_sc_head] = scancode;
		ps2_sc_head = f_head;
	} else {
		printf("\nBuffer Full!\n");
	}
}
void irq_handler(struct registers *reg){
	uint8_t irq = reg->int_num - 32;
    
	switch (irq) {
		case 0:
			irq0_timer_handler(reg);
			break;
		case 1:
			irq1_keyboard_handler(reg);
			break;	
		default:
			break;
	}
	
	if (reg->int_num >= 40) {
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);
}
void irq_init(){
	pic_init();
	for (int i = 0; i < 16; i++)
		idt_set_entry(32 + i, (unsigned)irq_stub_table[i], 0x08, 0x8E);	
}