AS32 = i686-elf-as
CC32 = i686-elf-gcc
NASM32 = nasm -felf32

BIN = bin
SRC = src
INC = inc
ISO_DIR = iso_root
OUTPUT = 32OS

C_OBJS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(shell find $(SRC) -iname "*.c"))
AS_OBJS = $(patsubst $(SRC)/%.s, $(BIN)/%.o, $(shell find $(SRC) -iname "*.s"))
ASM_OBJS = $(patsubst $(SRC)/%.asm, $(BIN)/%.o, $(shell find $(SRC) -iname "*.asm"))
OBJS = $(C_OBJS) $(AS_OBJS) $(ASM_OBJS)

C_FLAGS = -ffreestanding \
	-nostdlib \
	-Wall \
	-Wextra \
	-fno-pic \
	-fno-pie \
	-mno-red-zone \
	-m32 \
	-mno-sse \
	-mno-sse2 \
	-mno-mmx \
	-std=gnu11 \
	-O2 \
	-I$(INC)

LD_FLAGS = -ffreestanding \
	-nostdlib \
	-g \
	-static \
	-T $(SRC)/boot/linker.ld

all: $(BIN)/$(OUTPUT).iso

$(BIN):
	mkdir -p $@

$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	mkdir -p $(dir $@)
	$(CC32) $(C_FLAGS) -c $< -o $@

$(BIN)/%.o: $(SRC)/%.s | $(BIN)
	mkdir -p $(dir $@)
	$(AS32) $< -o $@

$(BIN)/%.o: $(SRC)/%.asm | $(BIN)
	mkdir -p $(dir $@)
	$(NASM32) $< -o $@

$(BIN)/$(OUTPUT).elf: $(OBJS) | $(BIN)
	$(CC32) $(LD_FLAGS) $^ -o $@

$(BIN)/$(OUTPUT).iso: $(BIN)/$(OUTPUT).elf
	mkdir -p $(ISO_DIR)/boot/grub/
	cp $< $(ISO_DIR)/boot
	cp grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $@ $(ISO_DIR)

run: $(BIN)/$(OUTPUT).iso 
	qemu-system-i386 -cdrom $< -d int,cpu_reset \
					-D $(BIN)/QEMU_LOGS.txt \
					-no-reboot -no-shutdown

clean:
	rm -rf $(BIN)
	rm -rf $(ISO_DIR)