#ifndef PSF_H
#define PSF_H

#define PSF1_FONT_MAGIC 0x0436

struct PSF1_Header {
	uint16_t magic;
	uint8_t font_mode;
	uint8_t char_size;
};

void psf_init();
void psf_render_char(char c, int x, int y, uint32_t fg, uint32_t bg);

#endif