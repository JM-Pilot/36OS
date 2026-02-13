#include <stdint.h>
#include <drivers/video/console.h>
#include <drivers/video/fb.h>
#include <drivers/video/psf.h>
#include <libc/string.h>
int cursor_x;
int cursor_y;
uint32_t console_fg;
uint32_t console_bg;
void init_console(){
	cursor_x = 0;
	cursor_y = 0;
	console_fg = 0xFFFFFF;
	console_bg = 0x000000;
}

void insert_newline(){
	cursor_x = 0;
	cursor_y += 16;
}

void write_char(char c){
	if (c == '\n'){
		insert_newline();
		return;
	}
	if (c == '\t'){
		cursor_x += (8 * 4);
		return;
	}
	if ((uint32_t)cursor_x + 8 > fb_width){
		insert_newline();
	}
	psf_render_char(c, cursor_x, cursor_y, console_fg, console_bg);
	cursor_x += 8;
}

void write_str(const char *s){
	for (int i = 0; s[i] != '\0'; i++)
		write_char(s[i]);
}

void write_int(int i) {
	int totl_num[256];
	int ptr = 0;

	if (i < 0) {
		write_char('-');
		i = -i;
	} 
	if (i == 0) {
		write_char('0');
		return;
	}   
    	while (i != 0) {
		totl_num[ptr++] = i % 10;
		i = i / 10;
    	}
	while (ptr-- != 0){
		write_char('0' + totl_num[ptr]);
	}
}
void write_hex(uint32_t h) {
	const char* hex_vals = "0123456789ABCDEF";
	write_str("0x");
	for (int i = 60; i >= 0; i -= 4)
       		write_char(hex_vals[(h >> i) & 0xF]);
}

void insert_backspace(){
	cursor_x -= 8;
	write_char(' ');
	cursor_x -= 8;
}