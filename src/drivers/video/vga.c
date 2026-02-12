#include <drivers/video/vga.h>
#include <arch/x86/asm.h>
#include <stdint.h>
#define VGA_TXT_ADDR 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint16_t *vga_ptr;
int cursor_x;
int cursor_y;


void vga_init(){
	vga_ptr = (uint16_t *)VGA_TXT_ADDR;
	cursor_y = 0;
	cursor_x = 0;
}

static void move_phys_cursor(int x, int y){
	uint16_t pos = y * VGA_WIDTH + x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static uint16_t vga_make_entry(char c, uint8_t fg, uint8_t bg){
	return c | ((fg | bg << 4) << 8);
}

void vga_scroll_up() {
	for (int y = 0; y < VGA_HEIGHT - 1; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			vga_ptr[y * VGA_WIDTH + x] = vga_ptr[(y + 1) * VGA_WIDTH + x];
		}
	}
	for (int x = 0; x < VGA_WIDTH; x++) {
		vga_ptr[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = ' ' | (0x0F << 8);
	}
}

void vga_clear_screen() {
	uint16_t blank = vga_make_entry(' ', 0xF, 0x0);
	
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga_ptr[i] = blank;
	}
	
	cursor_x = 0;
	cursor_y = 0;
	move_phys_cursor(0, 0);
}

static void add_newline(){
	cursor_y += 1;
	cursor_x = 0;
	move_phys_cursor(cursor_x, cursor_y);
}

void vga_write_char(char c){
	if (c == '\n') {
		add_newline();
		if (cursor_y >= VGA_HEIGHT) {
			vga_scroll_up();
			cursor_y = VGA_HEIGHT - 1;
		}
		
		return;
	}
	if (c == '\t') {
		cursor_x += 8;
		move_phys_cursor(cursor_x, cursor_y);
		return;
	}
	if (cursor_x >= VGA_WIDTH){
		add_newline();
	}
	if (cursor_y >= VGA_HEIGHT){
		vga_scroll_up();
		return;
	}
	vga_ptr[cursor_y * VGA_WIDTH + cursor_x++] = vga_make_entry(c, 0xF, 0x0);
	move_phys_cursor(cursor_x, cursor_y);
}

void vga_write_str(const char *s){
	for (int i = 0; s[i] != 0; i++)
		vga_write_char(s[i]);
}

void vga_write_hex(uint32_t h){
	const char* hex_vals = "0123456789ABCDEF";
	vga_write_str("0x");
	for (int i = 60; i >= 0; i -= 4)
       		vga_write_char(hex_vals[(h >> i) & 0xF]);
}

void vga_write_int(int i){
	int totl_num[256];
	int ptr = 0;

	if (i < 0) {
		vga_write_char('-');
		i = -i;
	} 
	if (i == 0) {
		vga_write_char('0');
		return;
	}   
    	while (i != 0) {
		totl_num[ptr++] = i % 10;
		i = i / 10;
    	}
	while (ptr-- != 0){
		vga_write_char('0' + totl_num[ptr]);
	}
}

void vga_insert_backspace(){
	cursor_x--;
	vga_write_char(' ');
	cursor_x--;
}