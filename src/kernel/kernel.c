#include <kernel/kernel.h>

#include <drivers/input/ps2.h>
#include <libc/stdio.h>
#include <boot/multiboot.h>
void kernel_main(struct multiboot_header* mb_info){
	kernel_boot_init(mb_info);
	run_kernel_shell();
	kernel_cpu_hang();
}