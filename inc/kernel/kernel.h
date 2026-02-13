#include <boot/multiboot.h>
#ifndef KERNEL_H
#define KERNEL_H
void kernel_boot_init(struct multiboot_header* mb_info);
void kernel_cpu_hang();
void run_kernel_shell();
#endif