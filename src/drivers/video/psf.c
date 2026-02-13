#include <stdint.h>
#include <drivers/video/psf.h>
#include <drivers/video/fb.h>
extern char _binary_src_drivers_video_fonts_default8x16_psf_start;
extern char _binary_src_drivers_video_fonts_default8x16_psf_end; 
struct PSF1_Header *font;
void psf_init(){
	font = (struct PSF1_Header* )&_binary_src_drivers_video_fonts_default8x16_psf_start;
	if (font->magic != PSF1_FONT_MAGIC){
		return;
	}
}
void psf_render_char(char c, int x, int y, uint32_t fg, uint32_t bg){
	uint8_t *glyph = (uint8_t*)&_binary_src_drivers_video_fonts_default8x16_psf_start + 
		sizeof(struct PSF1_Header) + ((uint8_t)c * font->char_size);
	uint8_t width = 8;
    	uint8_t height = font->char_size;

	for (uint32_t y1 = 0; y1 < height; y1++){
		uint8_t row = glyph[y1];
		for (uint32_t x1 = 0; x1 < width; x1++){
			if ((row & (0x80 >> x1)) != 0){
				fb_plot_pix(x + x1, y + y1, fg);
			} else {
				fb_plot_pix(x + x1, y + y1, bg);
			}
		}
	}
}