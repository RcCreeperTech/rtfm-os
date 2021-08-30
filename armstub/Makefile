# Binaries
CC=aarch64-linux-gnu-gcc-8
LD=aarch64-linux-gnu-ld
OBJ=aarch64-linux-gnu-objcopy

CFLAGS=-Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -mgeneral-regs-only -Iinclude

SRC=src
BUILD=build
SRCS=$(wildcard $(SRC)/*.S)
OBJS=$(patsubst $(SRC)%,$(BUILD)%,$(SRCS:.S=.asm.o))
IMG=armstub-new.bin

.PHONY: all clean log
all: clean $(IMG)

# Compile all translation units to .o files
$(BUILD)/%.asm.o: $(SRC)/%.S
	$(CC) $(CFLAGS) -c $< -o $@

log:
	-@echo $(SRCS)
	-@echo $(OBJS)

$(IMG): $(OBJS)
	$(LD) --section-start=.text=0 -nostdlib -nostartfiles $(OBJS) -o $(BUILD)/$(IMG:.bin=.elf)
	$(OBJ) -O binary $(BUILD)/$(IMG:.bin=.elf) $@

clean:
	rm -rf build/*
	rm -f $(IMG)
