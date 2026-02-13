#include <stdint.h>
#ifndef CONSOLE_H
#define CONSOLE_H

extern int cursor_x;
extern int cursor_y;
extern uint32_t console_fg;
extern uint32_t console_bg;
void init_console();
void write_char(char c);
void write_str(const char *s);
void write_int(int i);
void write_hex(uint32_t h);
void insert_newline();
void insert_backspace();
#endif