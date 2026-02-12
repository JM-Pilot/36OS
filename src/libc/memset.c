#include <libc/string.h>
#include <stddef.h>
#include <stdint.h>
void *memset(void *d, int v, size_t bytes){
	uint8_t *dt = d;
	while (bytes-- > 0)
		*dt = v;
	return d;
}

