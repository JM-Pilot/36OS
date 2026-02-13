#include <drivers/input/ps2.h>
#include <stdint.h>
uint8_t ps2_scancodes[256];
volatile int ps2_sc_head;
volatile int ps2_sc_tail;

unsigned char scancode_to_ascii[128] = {
    0,   27,  '1', '2', '3',  '4', '5', '6',
    '7', '8', '9', '0', '-',  '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't',  'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', 0,   'a', 's',
    'd', 'f', 'g', 'h', 'j',  'k', 'l', ';',
    '\'','`', 0,   '\\','z',  'x', 'c', 'v',
    'b', 'n', 'm', ',', '.',  '/', 0,   '*',
    0,   ' ', 0,   0,   0,    0,   0,   0, 
    0,   0,   0,   0,   0,    0,   0,   '7',
    '8', '9', '-', '4', '5',  '6', '+', '1',
    '2', '3', '0', '.',  0,   0,   0,   0,
    0,   0,   0,   0,   0,    0,   0,   0 
};


uint8_t pop_scancode() {
	if (ps2_sc_head == ps2_sc_tail) return 0;
	uint8_t sc = ps2_scancodes[ps2_sc_tail];
	ps2_sc_tail = (ps2_sc_tail + 1) % 256;
	return sc;
}

char ps2_get_char(){
	while (1) {
		uint8_t scancode = pop_scancode();
		if (scancode == 0) continue; 
		if (scancode & 0x80) continue;
		char c = scancode_to_ascii[scancode];
		if (scancode < 128) {
			char c = scancode_to_ascii[scancode];
			if (c != 0) return c;
		}
	}
	return 0;
}

void ps2_init(){
	ps2_sc_head = 0;
	ps2_sc_tail = 0;	
}