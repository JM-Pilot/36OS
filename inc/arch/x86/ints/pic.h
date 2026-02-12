#include <stdint.h>
#ifndef PIC_H
#define PIC_H
void PIC_disable(void);
void PIC_sendEOI(uint8_t irq);
void IRQ_set_mask(uint8_t IRQline);
void IRQ_clear_mask(uint8_t IRQline); 
void pic_init();
#endif