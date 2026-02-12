#include <stdint.h>
#ifndef PS2_H
#define PS2_H
extern uint8_t ps2_scancodes[256];
extern volatile int ps2_sc_head;
extern volatile int ps2_sc_tail; 

char ps2_get_char();

void ps2_init();
#endif