#include <stdint.h>
#include <drivers/video/fb.h>
#include <libc/string.h>
uint32_t fb_width;
uint32_t fb_height;
uint32_t *fb_addr;

void fb_init(uint64_t addr, uint32_t height, uint32_t width){
	fb_addr = (uint32_t*)addr;
	fb_height = height;
	fb_width = width;
}
void fb_plot_pix(int x, int y, uint32_t color){
	fb_addr[y * fb_width + x] = color;
}

void clear_fb(){
	for (int x = 0; x < fb_width; x++)
		for (int y = 0; y < fb_height; y++)
			fb_plot_pix(x, y, 0x000000);
}