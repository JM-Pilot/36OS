#include <arch/x86/gdt.h>
#include <stdint.h>

struct gdt_reg {
	uint16_t size;
	uint32_t addr;
}__attribute__((packed));

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t gran;
	uint8_t base_high;
}__attribute__((packed));


struct gdt_reg gdtr;
static struct gdt_entry gdt[3];
extern void gdt_flush();

void set_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_mid = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	gdt[num].limit_low = (limit & 0xFFFF);

	gdt[num].gran = ((limit >> 16) & 0x0F) | (gran & 0xF0);
	gdt[num].access = access;
}


void gdt_init(){	
	gdtr.size = (sizeof(struct gdt_entry) * 3) - 1;
	gdtr.addr = (uint32_t)&gdt;
	set_entry(0, 0, 0, 0, 0);
	set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);
	set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);
	gdt_flush();
}