#include <kernel/kernel.h>
#include <libc/stdio.h>
#include <drivers/video/vga.h>
#include <libc/string.h>

void execute_command(char *cmd){
	if (strcmp(cmd, "clear") == 0){
		vga_clear_screen();
		return;
	}
	if (strcmp(cmd, "help") == 0){
		printf("\nMINI_SHELL (c) 2026 JM-Pilot\n");
		printf("This shell is licensed under the MIT LICENSE\nAnd not using user space\n\n");
		printf("'help'    -- Lists commands\n");
		printf("'clear'   -- Clears the screen\n");
		printf("'sysinfo' -- Give system's information\n\n");
		printf("Do not add spaces after command\n\n");
		return;
	}
	if (strcmp(cmd, "sysinfo") == 0){
		printf("  \\  /       ARCH: X86\n");
		printf("   \\/        VERSION: 0.1\n");
		printf("   /\\        SHELL: MINI_SHELL (KERNEL)\n");
		printf("  /  \\       KERNEL: 36OS KERNEL\n");
		return;
	}
}
void run_kernel_shell(){
	printf("MINI_SHELL (c) 2026 JM-Pilot\n");
	char input_buffer[32];
	while (1){
		memset(input_buffer, 0, 32);
		printf("$ ");
		getstr(input_buffer);
		execute_command(input_buffer);
	}
}