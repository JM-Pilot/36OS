#include <stdint.h>
#ifndef VGA_H
#define VGA_H

void vga_init();
void vga_write_char(char c);
void vga_write_str(const char *s);
void vga_write_hex(uint32_t h);
void vga_write_int(int i);
void vga_insert_backspace();
void vga_clear_screen(); 
void vga_scroll_up();
#endif