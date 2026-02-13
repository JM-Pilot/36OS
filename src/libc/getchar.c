#include <libc/stdio.h>
#include <stdint.h>
#include <drivers/input/ps2.h>
#include <drivers/video/console.h>
int getchar(){
	return (int)ps2_get_char();
}

char* getstr(char *buf){
	int i = 0;
	char c;
	while ((c = getchar()) != '\n'){
		if (c == '\b' && i > 0){
			i--;
			insert_backspace();
		} else if (c >= 32 && c <= 126) {
			buf[i++] = c;
			write_char(c);
		}
	}
	buf[i] = '\0';
	insert_newline();
	return buf;
}