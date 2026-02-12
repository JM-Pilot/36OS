#include <kernel/kernel.h>
#include <drivers/video/vga.h>
#include <drivers/input/ps2.h>
void kernel_main(){
	kernel_boot_init();
	run_kernel_shell();
	kernel_cpu_hang();
}