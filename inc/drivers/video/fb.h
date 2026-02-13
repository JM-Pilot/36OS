#include <stdint.h>
#ifndef FB_H
#define FB_H

extern uint32_t *fb_addr;
extern uint32_t fb_width;
extern uint32_t fb_height;
void fb_init(uint64_t addr, uint32_t height, uint32_t width);
void fb_plot_pix(int x, int y, uint32_t color);
void clear_fb();
#endif